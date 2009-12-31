// $Id$
/*
 * MBSID Lead Engine
 *
 * ==========================================================================
 *
 *  Copyright (C) 2009 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

/////////////////////////////////////////////////////////////////////////////
// Include files
/////////////////////////////////////////////////////////////////////////////

#include <mios32.h>
#include <string.h>

#include <sid.h>

#include "sid_random.h"
#include "sid_se.h"
#include "sid_se_l.h"
#include "sid_patch.h"
#include "sid_par.h"


/////////////////////////////////////////////////////////////////////////////
// for optional debugging messages via DEBUG_MSG (defined in mios32_config.h)
// should be at least 1 for sending error messages
/////////////////////////////////////////////////////////////////////////////
#define DEBUG_VERBOSE_LEVEL 1


/////////////////////////////////////////////////////////////////////////////
// Local definitions
/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
// Type definitions
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Local prototypes
/////////////////////////////////////////////////////////////////////////////

static s32 SID_SE_L_NoteRestart(sid_se_voice_t *v);
static s32 SID_SE_L_LFO_Restart(sid_se_lfo_t *l);
static s32 SID_SE_L_ENV_Restart(sid_se_env_t *e);
static s32 SID_SE_L_ENV_Release(sid_se_env_t *e);

static s32 SID_SE_L_CalcModulation(u8 sid);
static s32 SID_SE_L_LFO(sid_se_lfo_t *l);
static s32 SID_SE_L_LFO_GenWave(sid_se_lfo_t *l, u8 lfo_overrun);
static s32 SID_SE_L_ENV(sid_se_env_t *e);
static s32 SID_SE_L_EnvStep(u16 *ctr, u16 target, u8 rate, u8 curve);
static s32 SID_SE_L_WT(sid_se_wt_t *w);


/////////////////////////////////////////////////////////////////////////////
// Local variables
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Initialisation
/////////////////////////////////////////////////////////////////////////////
s32 SID_SE_L_Init(u32 mode)
{
  return 0; // no error
}


/////////////////////////////////////////////////////////////////////////////
// Sound Engine Update Cycle
/////////////////////////////////////////////////////////////////////////////
s32 SID_SE_L_Update(u8 sid)
{
  int i;
  sid_se_vars_t *vars = &sid_se_vars[sid];


  ///////////////////////////////////////////////////////////////////////////
  // Clock
  ///////////////////////////////////////////////////////////////////////////

  if( sid_se_clk.event.MIDI_START ) {
    // propagate LFO/ENV/WT sync via trigger matrix
    u8 *trg_mask_midi_start = (u8 *)&sid_patch[sid].L.trg_matrix[SID_SE_TRG_MST][0];
    u8 *triggers = (u8 *)&vars->triggers.ALL[0];
    *triggers++ |= *trg_mask_midi_start++;
    *triggers++ |= *trg_mask_midi_start++;
    *triggers++ |= *trg_mask_midi_start++;
  }

  if( sid_se_clk.event.CLK ) {
    // clock propagation
    u8 *trg_mask_clk = (u8 *)&sid_patch[sid].L.trg_matrix[SID_SE_TRG_CLK][0];
    u8 *triggers = (u8 *)&vars->triggers.ALL[0];
    *triggers++ |= *trg_mask_clk++;
    *triggers++ |= *trg_mask_clk++;
    *triggers++ |= *trg_mask_clk++;

    // propagate clock/4 event to trigger matrix on each 6th clock
    if( sid_se_clk.global_clk_ctr6 == 0 ) {
      u8 *trg_mask_cl6 = (u8 *)&sid_patch[sid].L.trg_matrix[SID_SE_TRG_CL6][0];
      u8 *triggers = (u8 *)&vars->triggers.ALL[0];
      *triggers++ |= *trg_mask_cl6++;
      *triggers++ |= *trg_mask_cl6++;
      *triggers++ |= *trg_mask_cl6++;
    }

    // propagate clock/16 event to trigger matrix on each 24th clock
    if( sid_se_clk.global_clk_ctr24 == 0 ) {
      u8 *trg_mask_c24 = (u8 *)&sid_patch[sid].L.trg_matrix[SID_SE_TRG_C24][0];
      u8 *triggers = (u8 *)&vars->triggers.ALL[0];
      *triggers++ |= *trg_mask_c24++;
      *triggers++ |= *trg_mask_c24++;
      *triggers++ |= *trg_mask_c24++;
    }
  }


  ///////////////////////////////////////////////////////////////////////////
  // LFOs
  ///////////////////////////////////////////////////////////////////////////

  sid_se_lfo_t *l = &sid_se_lfo[sid][0];
  for(i=0; i<SID_SE_NUM_VOICES; ++i, ++l)
    SID_SE_L_LFO(l);


  ///////////////////////////////////////////////////////////////////////////
  // ENVs
  ///////////////////////////////////////////////////////////////////////////

  sid_se_env_t *e = &sid_se_env[sid][0];
  for(i=0; i<2; ++i, ++e)
    SID_SE_L_ENV(e);


  ///////////////////////////////////////////////////////////////////////////
  // Modulation Matrix
  ///////////////////////////////////////////////////////////////////////////

  // since this isn't done anywhere else:
  // convert linear frequency of voice1 to 15bit signed value (only positive direction)
  vars->mod_src[SID_SE_MOD_SRC_KEY] = sid_se_voice[sid][0].linear_frq >> 1;

  // do calculations
  SID_SE_L_CalcModulation(sid);


  ///////////////////////////////////////////////////////////////////////////
  // Wavetables
  ///////////////////////////////////////////////////////////////////////////

  sid_se_wt_t *w = &sid_se_wt[sid][0];
  for(i=0; i<4; ++i, ++w)
    SID_SE_L_WT(w);


  ///////////////////////////////////////////////////////////////////////////
  // Arps
  ///////////////////////////////////////////////////////////////////////////
  sid_se_voice_t *v = &sid_se_voice[sid][0];
  for(i=0; i<SID_SE_NUM_VOICES; ++i, ++v)
    SID_SE_Arp(v);


  ///////////////////////////////////////////////////////////////////////////
  // Syncs via Trigger Matrix
  ///////////////////////////////////////////////////////////////////////////
  sid_se_trg_t *trg = &vars->triggers;
  if( trg->ALL[0] ) {
    if( trg->O1L ) SID_SE_L_NoteRestart(&sid_se_voice[sid][0]);
    if( trg->O2L ) SID_SE_L_NoteRestart(&sid_se_voice[sid][1]);
    if( trg->O3L ) SID_SE_L_NoteRestart(&sid_se_voice[sid][2]);
    if( trg->O1R ) SID_SE_L_NoteRestart(&sid_se_voice[sid][3]);
    if( trg->O2R ) SID_SE_L_NoteRestart(&sid_se_voice[sid][4]);
    if( trg->O3R ) SID_SE_L_NoteRestart(&sid_se_voice[sid][5]);
    if( trg->E1A ) SID_SE_L_ENV_Restart(&sid_se_env[sid][0]);
    if( trg->E2A ) SID_SE_L_ENV_Restart(&sid_se_env[sid][1]);
    trg->ALL[0] = 0;
  }

  if( trg->ALL[1] ) {
    if( trg->E1R ) SID_SE_L_ENV_Release(&sid_se_env[sid][0]);
    if( trg->E2R ) SID_SE_L_ENV_Release(&sid_se_env[sid][1]);
    if( trg->L1  ) SID_SE_L_LFO_Restart(&sid_se_lfo[sid][0]);
    if( trg->L2  ) SID_SE_L_LFO_Restart(&sid_se_lfo[sid][1]);
    if( trg->L3  ) SID_SE_L_LFO_Restart(&sid_se_lfo[sid][2]);
    if( trg->L4  ) SID_SE_L_LFO_Restart(&sid_se_lfo[sid][3]);
    if( trg->L5  ) SID_SE_L_LFO_Restart(&sid_se_lfo[sid][4]);
    if( trg->L6  ) SID_SE_L_LFO_Restart(&sid_se_lfo[sid][5]);
    trg->ALL[1] = 0;
  }

  // trg->ALL[2] already handled by WT function
  trg->ALL[2] = 0;


  ///////////////////////////////////////////////////////////////////////////
  // Voices
  ///////////////////////////////////////////////////////////////////////////
  v = &sid_se_voice[sid][0];
  for(i=0; i<SID_SE_NUM_VOICES; ++i, ++v) {
    if( SID_SE_Gate(v) > 0 )
      SID_SE_Pitch(v);
    SID_SE_PW(v);
  }


  ///////////////////////////////////////////////////////////////////////////
  // Filters and Volume
  ///////////////////////////////////////////////////////////////////////////
  sid_se_filter_t *f = &sid_se_filter[sid][0];
  SID_SE_FilterAndVolume(f++);
  SID_SE_FilterAndVolume(f);


  ///////////////////////////////////////////////////////////////////////////
  // Tmp: copy register values directly into SID registers
  ///////////////////////////////////////////////////////////////////////////
  v = &sid_se_voice[sid][0];
  for(i=0; i<6; ++i, ++v) {
    sid_se_voice_waveform_t waveform = (sid_se_voice_waveform_t)v->voice_patch->waveform;
    v->phys_sid_voice->waveform = waveform.WAVEFORM;
    v->phys_sid_voice->sync = waveform.SYNC;
    v->phys_sid_voice->ringmod = waveform.RINGMOD;

    // if ABW (ADSR bug workaround) function active, ADSR registers will be controlled by SID_SE_Gate()
    sid_se_opt_flags_t opt_flags = (sid_se_opt_flags_t)sid_patch[v->sid].opt_flags;
    if( !opt_flags.ABW ) {
      v->phys_sid_voice->ad = v->voice_patch->ad;
      v->phys_sid_voice->sr = v->voice_patch->sr;
    }
  }

  return 0; // no error
}


/////////////////////////////////////////////////////////////////////////////
// Restart Functions (used by Trigger matrix for synching)
/////////////////////////////////////////////////////////////////////////////

static s32 SID_SE_L_NoteRestart(sid_se_voice_t *v)
{
  // request gate if voice is active (and request clear for proper ADSR handling)
  v->state.GATE_CLR_REQ = 1;
  if( v->state.VOICE_ACTIVE )
    v->state.GATE_SET_REQ = 1;

  // check if voice should be delayed - set delay counter to 0x0001 in this case, else to 0x0000
  v->set_delay_ctr = v->voice_patch->delay ? 0x0001 : 0x0000;

  // delay also if ABW (ADSR bug workaround) option is active
  sid_se_opt_flags_t opt_flags = (sid_se_opt_flags_t)sid_patch[v->sid].opt_flags;
  if( opt_flags.ABW ) {
    v->set_delay_ctr = 0x0001;
    // clear ADSR registers, so that the envelope gets completely released
    v->phys_sid_voice->ad = 0x00;
    v->phys_sid_voice->sr = 0x00;
  }

  return 0; // no error
}


static s32 SID_SE_L_LFO_Restart(sid_se_lfo_t *l)
{
  // reset counter (take phase into account)
  l->ctr = l->lfo_patch->phase << 8;

  // clear overrun flag (for oneshot mode)
  sid_se_vars[l->sid].lfo_overrun &= ~(1 << l->lfo);

  // check if LFO should be delayed - set delay counter to 0x0001 in this case
  l->delay_ctr = l->lfo_patch->delay ? 1 : 0;

  // re-calculate waveform
  return SID_SE_L_LFO_GenWave(l, 0);
}


static s32 SID_SE_L_ENV_Restart(sid_se_env_t *e)
{
  // start at attack phase
  e->state = SID_SE_ENV_STATE_ATTACK1;

  // check if ENV should be delayed - set delay counter to 0x0001 in this case
  e->delay_ctr = e->env_patch->delay ? 1 : 0;

  return 0; // no error
}


static s32 SID_SE_L_ENV_Release(sid_se_env_t *e)
{
  // set release phase
  e->state = SID_SE_ENV_STATE_RELEASE1;

  return 0; // no error
}


/////////////////////////////////////////////////////////////////////////////
// Calculate Modulation Path
/////////////////////////////////////////////////////////////////////////////
static s32 SID_SE_L_CalcModulation(u8 sid)
{
  int i;

  s16 *mod_src_array = sid_se_vars[sid].mod_src;
  s32 *mod_dst_array = sid_se_vars[sid].mod_dst;

  // clear all destinations
  s32 *mod_dst_array_clr = mod_dst_array;
  for(i=0; i<SID_SE_NUM_MOD_DST; ++i)
    *mod_dst_array_clr++ = 0; // faster than memset()! (ca. 20 uS) - seems that memset only copies byte-wise

  // calculate modulation pathes
  sid_se_mod_patch_t *mp = (sid_se_mod_patch_t *)&sid_patch[sid].L.mod[0];
  for(i=0; i<8; ++i, ++mp) {
    if( mp->depth != 0 ) {

      // first source
      s32 mod_src1_value;
      if( !mp->src1 ) {
	mod_src1_value = 0;
      } else {
	if( mp->src1 & (1 << 7) ) {
	  // constant range 0x00..0x7f -> +0x0000..0x38f0
	  mod_src1_value = (mp->src1 & 0x7f) << 7;
	} else {
	  // modulation range +/- 0x3fff
	  mod_src1_value = mod_src_array[mp->src1-1] / 2;
	}
      }

      // second source
      s32 mod_src2_value;
      if( !mp->src2 ) {
	mod_src2_value = 0;
      } else {
	if( mp->src2 & (1 << 7) ) {
	  // constant range 0x00..0x7f -> +0x0000..0x38f0
	  mod_src2_value = (mp->src2 & 0x7f) << 7;
	} else {
	  // modulation range +/- 0x3fff
	  mod_src2_value = mod_src_array[mp->src2-1] / 2;
	}
      }

      // apply operator
      s16 mod_result;
      switch( mp->op & 0x0f ) {
        case 0: // disabled
	  mod_result = 0;
	  break;

        case 1: // SRC1 only
	  mod_result = mod_src1_value;
	  break;

        case 2: // SRC2 only
	  mod_result = mod_src2_value;
	  break;

        case 3: // SRC1+SRC2
	  mod_result = mod_src1_value + mod_src2_value;
	  break;

        case 4: // SRC1-SRC2
	  mod_result = mod_src1_value - mod_src2_value;
	  break;

        case 5: // SRC1*SRC2 / 8192 (to avoid overrun)
	  mod_result = (mod_src1_value * mod_src2_value) / 8192;
	  break;

        case 6: // XOR
	  mod_result = mod_src1_value ^ mod_src2_value;
	  break;

        case 7: // OR
	  mod_result = mod_src1_value | mod_src2_value;
	  break;

        case 8: // AND
	  mod_result = mod_src1_value & mod_src2_value;
	  break;

        case 9: // Min
	  mod_result = (mod_src1_value < mod_src2_value) ? mod_src1_value : mod_src2_value;
	  break;

        case 10: // Max
	  mod_result = (mod_src1_value > mod_src2_value) ? mod_src1_value : mod_src2_value;
	  break;

        case 11: // SRC1 < SRC2
	  mod_result = (mod_src1_value < mod_src2_value) ? 0x7fff : 0x0000;
	  break;

        case 12: // SRC1 > SRC2
	  mod_result = (mod_src1_value > mod_src2_value) ? 0x7fff : 0x0000;
	  break;

        case 13: { // SRC1 == SRC2 (with tolarance of +/- 64
	  s32 diff = mod_src1_value - mod_src2_value;
	  mod_result = (diff > -64 && diff < 64) ? 0x7fff : 0x0000;
	} break;

        case 14: { // S&H - SRC1 will be sampled whenever SRC2 changes from a negative to a positive value
	  // check for SRC2 transition
	  u8 old_mod_transition = sid_se_vars[sid].mod_transition;
	  if( mod_src2_value < 0 )
	    sid_se_vars[sid].mod_transition &= ~(1 << i);
	  else
	    sid_se_vars[sid].mod_transition |= (1 << i);

	  if( sid_se_vars[sid].mod_transition != old_mod_transition && mod_src2_value >= 0 ) // only on positive transition
	    mod_result = mod_src1_value; // sample: take new mod value
	  else
	    mod_result = mod_src_array[SID_SE_MOD_SRC_MOD1 + i]; // hold: take old mod value
	} break;

        default:
	  mod_result = 0;
      }

      // store in modulator source array for feedbacks
      // use value w/o depth, this has two advantages:
      // - maximum resolution when forwarding the data value
      // - original MOD value can be taken for sample&hold feature
      // bit it also has disadvantage:
      // - the user could think it is a bug when depth doesn't affect the feedback MOD value...
      mod_src_array[SID_SE_MOD_SRC_MOD1 + i] = mod_result;

      // forward to destinations
      if( mod_result ) {
	s32 scaled_mod_result = ((s32)mp->depth-128) * mod_result / 64; // (+/- 0x7fff * +/- 0x7f) / 128
      
	// invert result if requested
	s32 mod_dst1 = (mp->op & (1 << 6)) ? -scaled_mod_result : scaled_mod_result;
	s32 mod_dst2 = (mp->op & (1 << 7)) ? -scaled_mod_result : scaled_mod_result;

	// add result to modulation target array
	u8 x_target1 = mp->x_target[0];
	if( x_target1 && x_target1 <= SID_SE_NUM_MOD_DST )
	  mod_dst_array[x_target1 - 1] += mod_dst1;
	
	u8 x_target2 = mp->x_target[1];
	if( x_target2 && x_target2 <= SID_SE_NUM_MOD_DST )
	  mod_dst_array[x_target2 - 1] += mod_dst2;

	// add to additional SIDL/R targets
	u8 direct_target_l = mp->direct_target[0];
	if( direct_target_l ) {
	  if( direct_target_l & (1 << 0) ) mod_dst_array[SID_SE_MOD_DST_PITCH1] += mod_dst1;
	  if( direct_target_l & (1 << 1) ) mod_dst_array[SID_SE_MOD_DST_PITCH2] += mod_dst1;
	  if( direct_target_l & (1 << 2) ) mod_dst_array[SID_SE_MOD_DST_PITCH3] += mod_dst1;
	  if( direct_target_l & (1 << 3) ) mod_dst_array[SID_SE_MOD_DST_PW1] += mod_dst1;
	  if( direct_target_l & (1 << 4) ) mod_dst_array[SID_SE_MOD_DST_PW2] += mod_dst1;
	  if( direct_target_l & (1 << 5) ) mod_dst_array[SID_SE_MOD_DST_PW3] += mod_dst1;
	  if( direct_target_l & (1 << 6) ) mod_dst_array[SID_SE_MOD_DST_FIL1] += mod_dst1;
	  if( direct_target_l & (1 << 7) ) mod_dst_array[SID_SE_MOD_DST_VOL1] += mod_dst1;
	}

	u8 direct_target_r = mp->direct_target[1];
	if( direct_target_r ) {
	  if( direct_target_r & (1 << 0) ) mod_dst_array[SID_SE_MOD_DST_PITCH4] += mod_dst2;
	  if( direct_target_r & (1 << 1) ) mod_dst_array[SID_SE_MOD_DST_PITCH5] += mod_dst2;
	  if( direct_target_r & (1 << 2) ) mod_dst_array[SID_SE_MOD_DST_PITCH6] += mod_dst2;
	  if( direct_target_r & (1 << 3) ) mod_dst_array[SID_SE_MOD_DST_PW4] += mod_dst2;
	  if( direct_target_r & (1 << 4) ) mod_dst_array[SID_SE_MOD_DST_PW5] += mod_dst2;
	  if( direct_target_r & (1 << 5) ) mod_dst_array[SID_SE_MOD_DST_PW6] += mod_dst2;
	  if( direct_target_r & (1 << 6) ) mod_dst_array[SID_SE_MOD_DST_FIL2] += mod_dst2;
	  if( direct_target_r & (1 << 7) ) mod_dst_array[SID_SE_MOD_DST_VOL2] += mod_dst2;
	}
      }
    }
  }

  return 0; // no error
}


/////////////////////////////////////////////////////////////////////////////
// LFO
/////////////////////////////////////////////////////////////////////////////
static s32 SID_SE_L_LFO(sid_se_lfo_t *l)
{
  sid_se_lfo_mode_t lfo_mode = (sid_se_lfo_mode_t)l->lfo_patch->mode;

  // set wave register to initial value and skip LFO if not enabled
  if( !lfo_mode.ENABLE ) {
    *l->mod_src_lfo = 0;
  } else {
    if( l->delay_ctr ) {
      int new_delay_ctr = l->delay_ctr + (sid_se_env_table[l->lfo_patch->delay] / sid_se_speed_factor);
      if( new_delay_ctr > 0xffff )
	l->delay_ctr = 0; // delay passed
      else
	l->delay_ctr = new_delay_ctr; // delay not passed
    }

    if( !l->delay_ctr ) { // delay passed?
      u8 lfo_overrun = 0;
      u8 lfo_stalled = 0;

      // in oneshot mode: check if overrun already occured
      if( lfo_mode.ONESHOT ) {
	if( sid_se_vars[l->sid].lfo_overrun & (1 << l->lfo) ) {
	  // set counter to maximum value and skip sweep
	  l->ctr = 0xffff;
	  lfo_stalled = 1;
	}
      }

      // if clock sync enabled: only increment on each 16th clock event
      if( lfo_mode.CLKSYNC && (!sid_se_clk.event.CLK || sid_se_clk.global_clk_ctr6 != 0) )
	lfo_stalled = 1;

      if( !lfo_stalled ) {
	// increment 16bit counter by given rate
	// the rate can be modulated
	s32 lfo_rate = l->lfo_patch->rate + (*l->mod_dst_lfo_rate / 256);
	if( lfo_rate > 255 ) lfo_rate = 255; else if( lfo_rate < 0 ) lfo_rate = 0;

	// if LFO synched via clock, replace 245-255 by MIDI clock optimized incrementers
	u16 inc;
	if( lfo_mode.CLKSYNC && lfo_rate >= 245 )
	  inc = sid_se_lfo_table_mclk[lfo_rate-245] / sid_se_speed_factor;
	else
	  inc = sid_se_lfo_table[lfo_rate] / sid_se_speed_factor;

	// add to counter and check for overrun
	s32 new_ctr = l->ctr + inc;
	if( new_ctr > 0xffff ) {
	  lfo_overrun = 1;

	  if( lfo_mode.ONESHOT )
	    new_ctr = 0xffff; // stop at end position

	  // propagate overrun to trigger matrix
	  l->trg_dst[0] |= l->trg_mask_lfo_period[0];
	  l->trg_dst[1] |= l->trg_mask_lfo_period[1];
	  l->trg_dst[2] |= l->trg_mask_lfo_period[2];

	  // required for oneshot mode
	  sid_se_vars[l->sid].lfo_overrun |= (1 << l->lfo);
	}
	l->ctr = (u16)new_ctr;
      }

      SID_SE_L_LFO_GenWave(l, lfo_overrun);
    }
  }

  return 0; // no error
}


static s32 SID_SE_L_LFO_GenWave(sid_se_lfo_t *l, u8 lfo_overrun)
{
  sid_se_lfo_mode_t lfo_mode = (sid_se_lfo_mode_t)l->lfo_patch->mode;

  // map counter to waveform
  u8 lfo_waveform_skipped = 0;
  s16 wave;
  switch( lfo_mode.WAVEFORM ) {
    case 0: { // Sine
      // sine table contains a quarter of a sine
      // we have to negate/mirror it depending on the mapped counter value
      u8 ptr = l->ctr >> 7;
      if( l->ctr & (1 << 14) )
	ptr ^= 0x7f;
      ptr &= 0x7f;
      wave = sid_se_sin_table[ptr];
      if( l->ctr & (1 << 15) )
	wave = -wave;
    } break;  

    case 1: { // Triangle
      // similar to sine, but linear waveform
      wave = (l->ctr & 0x3fff) << 1;
      if( l->ctr & (1 << 14) )
	wave = 0x7fff - wave;
      if( l->ctr & (1 << 15) )
	wave = -wave;
    } break;  

    case 2: { // Saw
      wave = l->ctr - 0x8000;
    } break;  

    case 3: { // Pulse
      wave = (l->ctr < 0x8000) ? -0x8000 : 0x7fff; // due to historical reasons it's inverted
    } break;  

    case 4: { // Random
      // only on LFO overrun
      if( lfo_overrun )
	wave = SID_RANDOM_Gen_Range(0x0000, 0xffff);
      else
	lfo_waveform_skipped = 1;
    } break;  

    case 5: { // Positive Sine
      // sine table contains a quarter of a sine
      // we have to negate/mirror it depending on the mapped counter value
      u8 ptr = l->ctr >> 8;
      if( l->ctr & (1 << 15) )
	ptr ^= 0x7f;
      ptr &= 0x7f;
      wave = sid_se_sin_table[ptr];
    } break;  

    case 6: { // Positive Triangle
      // similar to sine, but linear waveform
      wave = (l->ctr & 0x7fff);
      if( l->ctr & (1 << 15) )
	wave = 0x7fff - wave;
    } break;  

    case 7: { // Positive Saw
      wave = l->ctr >> 1;
    } break;  

    case 8: { // Positive Pulse
      wave = (l->ctr < 0x8000) ? 0 : 0x7fff; // due to historical reasons it's inverted
    } break;  

    default: // take saw as default
      wave = l->ctr - 0x8000;
  }

  if( !lfo_waveform_skipped ) {
    // scale to LFO depth
    // the depth can be modulated
    s32 lfo_depth = ((s32)l->lfo_patch->depth - 0x80) + (*l->mod_dst_lfo_depth / 256);
    if( lfo_depth > 127 ) lfo_depth = 127; else if( lfo_depth < -128 ) lfo_depth = -128;
    
    // final LFO value
    *l->mod_src_lfo = (wave * lfo_depth) / 128;
  }

  return 0; // no error
}


/////////////////////////////////////////////////////////////////////////////
// ENV
/////////////////////////////////////////////////////////////////////////////
static s32 SID_SE_L_ENV(sid_se_env_t *e)
{
  // if clock sync enabled: only increment on each 16th clock event
  if( (e->env_patch->mode & (1 << 7)) &&
      (!sid_se_clk.event.CLK || sid_se_clk.global_clk_ctr6 != 0) ) {
    if( e->state == SID_SE_ENV_STATE_IDLE )
      return 0; // nothing to do
  } else {
    switch( e->state ) {
      case SID_SE_ENV_STATE_ATTACK1:
        if( e->delay_ctr ) {
  	int new_delay_ctr = e->delay_ctr + (sid_se_env_table[e->env_patch->delay] / sid_se_speed_factor);
  	if( new_delay_ctr > 0xffff )
  	  e->delay_ctr = 0; // delay passed
  	else {
  	  e->delay_ctr = new_delay_ctr; // delay not passed
  	  return 0; // no error
  	}
        }
  
        if( SID_SE_L_EnvStep(&e->ctr, e->env_patch->attlvl << 8, e->env_patch->attack1, e->env_patch->att_curve) )
  	e->state = SID_SE_ENV_STATE_ATTACK2; // TODO: Set Phase depending on e->mode
        break;
  
      case SID_SE_ENV_STATE_ATTACK2:
        if( SID_SE_L_EnvStep(&e->ctr, 0xffff, e->env_patch->attack2, e->env_patch->att_curve) )
  	e->state = SID_SE_ENV_STATE_DECAY1; // TODO: Set Phase depending on e->mode
        break;
  
      case SID_SE_ENV_STATE_DECAY1:
        if( SID_SE_L_EnvStep(&e->ctr, e->env_patch->declvl << 8, e->env_patch->decay1, e->env_patch->dec_curve) )
  	e->state = SID_SE_ENV_STATE_DECAY2; // TODO: Set Phase depending on e->mode
        break;
  
      case SID_SE_ENV_STATE_DECAY2:
        if( SID_SE_L_EnvStep(&e->ctr, e->env_patch->sustain << 8, e->env_patch->decay2, e->env_patch->dec_curve) ) {
  	e->state = SID_SE_ENV_STATE_SUSTAIN; // TODO: Set Phase depending on e->mode
  
  	// propagate sustain phase to trigger matrix
  	e->trg_dst[0] |= e->trg_mask_env_sustain[0];
  	e->trg_dst[1] |= e->trg_mask_env_sustain[1];
  	e->trg_dst[2] |= e->trg_mask_env_sustain[2];
        }
        break;
  
      case SID_SE_ENV_STATE_SUSTAIN:
        // always update sustain level
        e->ctr = e->env_patch->sustain << 8;
        break;
  
      case SID_SE_ENV_STATE_RELEASE1:
        if( SID_SE_L_EnvStep(&e->ctr, e->env_patch->rellvl << 8, e->env_patch->release1, e->env_patch->rel_curve) )
  	e->state = SID_SE_ENV_STATE_RELEASE2; // TODO: Set Phase depending on e->mode
        break;
  
      case SID_SE_ENV_STATE_RELEASE2:
        if( e->ctr )
  	SID_SE_L_EnvStep(&e->ctr, 0x0000, e->env_patch->release2, e->env_patch->rel_curve);
        break;
  
      default: // like SID_SE_ENV_STATE_IDLE
        return 0; // nothing to do...
    }
  }

  // scale to ENV depth
  s32 env_depth = (s32)e->env_patch->depth - 0x80;
    
  // final ENV value (range +/- 0x7fff)
  *e->mod_src_env = ((e->ctr/2) * env_depth) / 128;

  return 0; // no error
}


static s32 SID_SE_L_EnvStep(u16 *ctr, u16 target, u8 rate, u8 curve)
{
  if( target == *ctr )
    return 1; // next state

  // modify rate if curve != 0x80
  u16 inc_rate;
  if( curve != 0x80 ) {
    // this nice trick has been proposed by Razmo
    int abs_curve = curve - 0x80;
    if( abs_curve < 0 )
      abs_curve = -abs_curve;
    else
      abs_curve ^= 0x7f; // invert if positive range for more logical behaviour of positive/negative curve

    int rate_msbs = (rate >> 1); // TODO: we could increase resolution by using an enhanced frq_table
    int feedback = (abs_curve * (*ctr>>8)) >> 8; 
    int ix;
    if( curve > 0x80 ) { // bend up
      ix = (rate_msbs ^ 0x7f) - feedback;
      if( ix < 0 )
	ix = 0;
    } else { // bend down
      ix = (rate_msbs ^ 0x7f) + feedback;
      if( ix >= 127 )
	ix = 127;
    }
    inc_rate = sid_se_frq_table[ix];
  } else {
    inc_rate = sid_se_env_table[rate];
  }

  // positive or negative direction?
  if( target > *ctr ) {
    s32 new_ctr = (s32)*ctr + (inc_rate / sid_se_speed_factor);
    if( new_ctr >= target ) {
      *ctr = target;
      return 1; // next state
    }
    *ctr = new_ctr;
    return 0; // stay in state
  }

  s32 new_ctr = (s32)*ctr - (inc_rate / sid_se_speed_factor);
  if( new_ctr <= target ) {
    *ctr = target;
    return 1; // next state
  }
  *ctr = new_ctr;

  return 0; // stay in state
}


/////////////////////////////////////////////////////////////////////////////
// Wavetable
/////////////////////////////////////////////////////////////////////////////
static s32 SID_SE_L_WT(sid_se_wt_t *w)
{
  s32 step = -1;

  // if key control flag (END[7]) set, control position from current played key
  if( w->wt_patch->end & (1 << 7) ) {
    // copy currently played note to step position
    step = sid_se_voice[w->sid][0].played_note;

  // if MOD control flag (BEGIN[7]) set, control step position from modulation matrix
  } else if( w->wt_patch->begin & (1 << 7) ) {
    step = ((s32)*w->mod_dst_wt + 0x8000) >> 9; // 16bit signed -> 7bit unsigned
  }

  if( step >= 0 ) {
    // use modulated step position
    // scale between begin/end range
    if( w->wt_patch->end > w->wt_patch->begin ) {
      s32 range = (w->wt_patch->end - w->wt_patch->begin) + 1;
      step = w->wt_patch->begin + ((step * range) / 128);
    } else {
      // should we invert the waveform?
      s32 range = (w->wt_patch->begin - w->wt_patch->end) + 1;
      step = w->wt_patch->end + ((step * range) / 128);
    }
  } else {
    // don't use modulated position - normal mode
    u8 next_step_req = 0;

    // check if WT reset requested
    if( w->trg_src[2] & (1 << w->wt) ) {
      // next clock will increment div to 0
      w->div_ctr = 0xff;
      // next step will increment to start position
      w->pos = (w->wt_patch->begin & 0x7f) - 1;
    }

    // check for WT step event
    if( w->trg_src[2] & (1 << (4+w->wt)) ) {
      // increment clock divider
      // reset divider if it already has reached the target value
      if( ++w->div_ctr == 0 || (w->div_ctr > (w->wt_patch->speed & 0x3f)) ) {
	w->div_ctr = 0;
	next_step_req = 1;
      }
    }

    // check for next step request
    // skip if position is 0xaa (notifies oneshot -> WT stopped)
    if( next_step_req && w->pos != 0xaa ) {
      // increment position counter, reset at end position
      if( ++w->pos > w->wt_patch->end ) {
	// if oneshot mode: set position to 0xaa, WT is stopped now!
	if( w->wt_patch->loop & (1 << 7) )
	  w->pos = 0xaa;
	else
	  w->pos = w->wt_patch->loop & 0x7f;
      }
      step = w->pos; // step is positive now -> will be played
    }
  }

  // check if step should be played
  if( step >= 0 ) {
    u8 wt_value = sid_patch[w->sid].L.wt_memory[step & 0x7f];

    // forward to mod matrix
    if( wt_value < 0x80 ) {
      // relative value -> convert to -0x8000..+0x7fff
      *w->mod_src_wt = ((s32)wt_value - 0x40) * 512;
    } else {
      // absolute value -> convert to 0x0000..+0x7f00
      *w->mod_src_wt = ((s32)wt_value & 0x7f) * 256;
    }
    
    // determine SID channels which should be modified
    u8 sidlr = (w->wt_patch->speed >> 6); // SID selection
    u8 ins = w->wt; // preparation for multi engine

    // call parameter handler
    if( w->wt_patch->assign ) {
#if DEBUG_VERBOSE_LEVEL >= 2
      DEBUG_MSG("WT %d: 0x%02x 0x%02x\n", w->wt, step, wt_value);
#endif
      SID_PAR_SetWT(w->sid, w->wt_patch->assign, wt_value, sidlr, ins);
    }
  }

  return 0; // no error
}