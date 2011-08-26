// $Id$
/*
 * MIDIbox CV V2 mapping functions
 *
 * ==========================================================================
 *
 *  Copyright (C) 2008 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

/////////////////////////////////////////////////////////////////////////////
// Include files
/////////////////////////////////////////////////////////////////////////////

#include <mios32.h>
#include <aout.h>
#include <seq_bpm.h>


#include "mbcv_map.h"
#include "mbcv_midi.h"
#include "mbcv_patch.h"


/////////////////////////////////////////////////////////////////////////////
// Local variables
/////////////////////////////////////////////////////////////////////////////

// TODO
static u8 seq_core_din_sync_pulse_ctr;


/////////////////////////////////////////////////////////////////////////////
// Initialisation
/////////////////////////////////////////////////////////////////////////////
s32 MBCV_MAP_Init(u32 mode)
{
  int i;

  // initialize J5 pins
#if 0
  // they will be enabled after the .CV2 file has been read
  // as long as this hasn't been done, activate pull-downs
  for(i=0; i<12; ++i)
    MIOS32_BOARD_J5_PinInit(i, MIOS32_BOARD_PIN_MODE_INPUT_PD);
#else
  // LPC17 is robust enough against shorts (measurements show 20 mA max per pin)
  // we can enable J5 pins by default to simplify usage
  for(i=0; i<12; ++i)
    MIOS32_BOARD_J5_PinInit(i, MIOS32_BOARD_PIN_MODE_OUTPUT_PP);
  for(i=0; i<4; ++i) // J5C replacement for LPC17
    MIOS32_BOARD_J28_PinInit(i, MIOS32_BOARD_PIN_MODE_OUTPUT_PP);
#endif

  // initialize AOUT driver
  AOUT_Init(0);

  return 0; // no error
}


/////////////////////////////////////////////////////////////////////////////
// Get/Set/Name AOUT interface
/////////////////////////////////////////////////////////////////////////////
s32 MBCV_MAP_IfSet(aout_if_t if_type)
{
  if( if_type >= AOUT_NUM_IF )
    return -1; // invalid interface

  aout_config_t config;
  config = AOUT_ConfigGet();
  config.if_type = if_type;
  config.if_option = (config.if_type == AOUT_IF_74HC595) ? 0xffffffff : 0x00000000; // AOUT_LC: select 8/8 bit configuration
  config.num_channels = 8;
  //config.chn_inverted = 0; // configurable
  AOUT_ConfigSet(config);
  return AOUT_IF_Init(0);
}

aout_if_t MBCV_MAP_IfGet(void)
{
  aout_config_t config;
  config = AOUT_ConfigGet();
  return config.if_type;
}


// will return 8 characters
const char* MBCV_MAP_IfNameGet(aout_if_t if_type)
{
  return AOUT_IfNameGet(if_type);
}


/////////////////////////////////////////////////////////////////////////////
// Get/Set/Name CV Curve
/////////////////////////////////////////////////////////////////////////////
s32 MBCV_MAP_CurveSet(u8 cv, u8 curve)
{
  if( cv >= MBCV_PATCH_NUM_CV )
    return -1; // invalid cv channel selected

  if( curve >= MBCV_MAP_NUM_CURVES )
    return -2; // invalid curve selected

  u32 mask = 1 << cv;
  aout_config_t config;
  config = AOUT_ConfigGet();

  if( curve & 1 )
    config.chn_hz_v |= mask;
  else
    config.chn_hz_v &= ~mask;

  if( curve & 2 )
    config.chn_inverted |= mask;
  else
    config.chn_inverted &= ~mask;

  return AOUT_ConfigSet(config);
}

u8 MBCV_MAP_CurveGet(u8 cv)
{
  if( cv >= MBCV_PATCH_NUM_CV )
    return 0; // invalid cv channel selected, return default curve

  u32 mask = 1 << cv;
  aout_config_t config;
  config = AOUT_ConfigGet();

  u8 curve = 0;
  if( config.chn_hz_v & mask )
    curve |= 1;
  if( config.chn_inverted & mask )
    curve |= 2;

  return curve;
}

// will return 6 characters
// located outside the function to avoid "core/seq_cv.c:168:3: warning: function returns address of local variable"
static const char curve_desc[3][7] = {
  "V/Oct ",
  "Hz/V  ",
  "Inv.  ",
};
const char* MBCV_MAP_CurveNameGet(u8 cv)
{

  if( cv >= MBCV_PATCH_NUM_CV )
    return "------";

  return curve_desc[MBCV_MAP_CurveGet(cv)];
}


/////////////////////////////////////////////////////////////////////////////
// Get/Set/Name Calibration Mode
/////////////////////////////////////////////////////////////////////////////

s32 MBCV_MAP_CaliModeSet(u8 cv, aout_cali_mode_t mode)
{
  if( cv >= MBCV_PATCH_NUM_CV )
    return -1; // invalid cv channel selected

  if( mode >= MBCV_MAP_NUM_CALI_MODES )
    return -2; // invalid mode selected

  return AOUT_CaliModeSet(cv, mode);

}

aout_cali_mode_t MBCV_MAP_CaliModeGet(void)
{
  return AOUT_CaliModeGet();
}

const char* MBCV_MAP_CaliNameGet(void)
{
  return AOUT_CaliNameGet(MBCV_MAP_CaliModeGet());
}


/////////////////////////////////////////////////////////////////////////////
// Get/Set Slewrate
/////////////////////////////////////////////////////////////////////////////
s32 MBCV_MAP_SlewRateSet(u8 cv, u8 value)
{
  return AOUT_PinSlewRateSet(cv, value);
}

s32 MBCV_MAP_SlewRateGet(u8 cv)
{
  return AOUT_PinSlewRateGet(cv);
}


/////////////////////////////////////////////////////////////////////////////
// Get/Set Pitch Range
/////////////////////////////////////////////////////////////////////////////
s32 MBCV_MAP_PitchRangeSet(u8 cv, u8 value)
{
  return AOUT_PinPitchRangeSet(cv, value);
}

s32 MBCV_MAP_PitchRangeGet(u8 cv)
{
  return AOUT_PinPitchRangeGet(cv);
}


/////////////////////////////////////////////////////////////////////////////
// retrieve the AOUT values of all channels
/////////////////////////////////////////////////////////////////////////////
static s32 MBCV_MAP_UpdateChannels(void)
{
  // prepare gates
  u32 gates = mbcv_midi_gates;

  // set CV voltages depending on MIDI mode
  // force gate to 0 as long as gateclr_ctr > 0
  int cv;
  mbcv_patch_cv_entry_t *cv_cfg = (mbcv_patch_cv_entry_t *)&mbcv_patch_cv[0];
  for(cv=0; cv<MBCV_PATCH_NUM_CV; ++cv, ++cv_cfg) {
    // for MONO and POLO mode: force gate to 0 for <mbcv_patch_gateclr_cycles> cycles
    if( mbcv_midi_gateclr_ctr[cv] ) {
      --mbcv_midi_gateclr_ctr[cv];
      gates &= ~(1 << cv);
    }

    // branch depending on value assignment
    switch( cv_cfg->midi_mode.event ) {
    case MBCV_PATCH_CV_MIDI_EVENT_NOTE: {
      AOUT_PinPitchSet(cv, mbcv_midi_pitch[cv]);
      int note = (int)mbcv_midi_note[cv];
      note += cv_cfg->transpose_oct * 12;
      note += cv_cfg->transpose_semi;
      while( note < 0 ) note += 12; // octavewise saturation
      while( note >= 127 ) note -= 12; // octavewise saturation
      AOUT_PinSet(cv, (u16)note << 9);
    } break;

    case MBCV_PATCH_CV_MIDI_EVENT_VELOCITY:
      AOUT_PinSet(cv, mbcv_midi_velocity[cv] << 9);
      break;

    case MBCV_PATCH_CV_MIDI_EVENT_AFTERTOUCH:
      AOUT_PinSet(cv, mbcv_midi_aftertouch[cv] << 9);
      break;

    case MBCV_PATCH_CV_MIDI_EVENT_CC:
      AOUT_PinSet(cv, mbcv_midi_cc[cv] << 9);
      break;

    case MBCV_PATCH_CV_MIDI_EVENT_NRPN:
      AOUT_PinSet(cv, mbcv_midi_nrpn[cv] << 2);
      break;

    case MBCV_PATCH_CV_MIDI_EVENT_PITCHBENDER:
      AOUT_PinSet(cv, (u16)(mbcv_midi_pitch[cv] + 8192) << 2);
      break;
    }
  }

  // set gates
  AOUT_DigitalPinsSet(gates);

  return 0; // no error
}


/////////////////////////////////////////////////////////////////////////////
// Updates all CV channels and gates
/////////////////////////////////////////////////////////////////////////////
s32 MBCV_MAP_Update(void)
{
  static u8 last_gates = 0xff; // to force an update
  static u8 last_start_stop = 0xff; // to force an update

  // retrieve the AOUT values of all channels
  MBCV_MAP_UpdateChannels();

  // Start/Stop at J5C.A9
  u8 start_stop = SEQ_BPM_IsRunning();
  if( start_stop != last_start_stop ) {
    last_start_stop = start_stop;
#if defined(MIOS32_FAMILY_STM32F10x)
    MIOS32_BOARD_J5_PinSet(9, start_stop);
#elif defined(MIOS32_FAMILY_LPC17xx)
    MIOS32_BOARD_J28_PinSet(1, start_stop);
#else
# warning "please adapt for this MIOS32_FAMILY"
#endif
  }

  // DIN Sync Pulse at J5C.A8
  if( seq_core_din_sync_pulse_ctr > 1 ) {
#if defined(MIOS32_FAMILY_STM32F10x)
    MIOS32_BOARD_J5_PinSet(8, 1);
#elif defined(MIOS32_FAMILY_LPC17xx)
    MIOS32_BOARD_J28_PinSet(0, 1);
#else
# warning "please adapt for this MIOS32_FAMILY"
#endif
    --seq_core_din_sync_pulse_ctr;
  } else if( seq_core_din_sync_pulse_ctr == 1 ) {
#if defined(MIOS32_FAMILY_STM32F10x)
    MIOS32_BOARD_J5_PinSet(8, 0);
#elif defined(MIOS32_FAMILY_LPC17xx)
    MIOS32_BOARD_J28_PinSet(0, 0);
#else
# warning "please adapt for this MIOS32_FAMILY"
#endif

    seq_core_din_sync_pulse_ctr = 0;
  }

  // update AOUTs
  AOUT_Update();

  // update J5 Outputs (forwarding AOUT digital pins for modules which don't support gates)
  u8 gates = AOUT_DigitalPinsGet() ^ mbcv_patch_gate_inverted[0];
  if( gates != last_gates ) {
    int i;

    last_gates = gates;
    for(i=0; i<8; ++i) {
      MIOS32_BOARD_J5_PinSet(i, gates & 1);
      gates >>= 1;
    }

    // for compatibility with MBSEQ V4 where J5B.A6 and J5B.A7 allocated by MIDI OUT3
#if defined(MIOS32_FAMILY_STM32F10x)
    // -> Gate 7 and 8 also routed to J5C.A10 and J5C.A11
    MIOS32_BOARD_J5_PinSet(10, (last_gates & 0x40) ? 1 : 0);
    MIOS32_BOARD_J5_PinSet(11, (last_gates & 0x80) ? 1 : 0);
#elif defined(MIOS32_FAMILY_LPC17xx)
    // -> Gate 7 and 8 also routed to J28.WS and J28.MCLK
    MIOS32_BOARD_J28_PinSet(2, (last_gates & 0x40) ? 1 : 0);
    MIOS32_BOARD_J28_PinSet(3, (last_gates & 0x80) ? 1 : 0);
#else
# warning "please adapt for this MIOS32_FAMILY"
#endif
  }

  return 0; // no error
}

/////////////////////////////////////////////////////////////////////////////
// Called to reset all channels/notes (e.g. after session change)
/////////////////////////////////////////////////////////////////////////////
s32 MBCV_MAP_ResetAllChannels(void)
{
  int cv;

  // reset all notestacks
  MBCV_MIDI_Init(0);

  // reset AOUT voltages
  for(cv=0; cv<MBCV_PATCH_NUM_CV; ++cv) {
    AOUT_PinPitchSet(cv, 0x0000);
    AOUT_PinSet(cv, 0x0000);
  }

  // clear pins 
  AOUT_DigitalPinsSet(0x00);

  int sr;
  for(sr=0; sr<MIOS32_SRIO_NUM_SR; ++sr)
    MIOS32_DOUT_SRSet(sr, mbcv_midi_dout_gate_sr[sr]);

  return 0; // no error
}
