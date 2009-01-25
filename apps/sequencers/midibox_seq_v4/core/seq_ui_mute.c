// $Id$
/*
 * Mute page
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
#include "tasks.h"

#include "seq_lcd.h"
#include "seq_ui.h"

#include "seq_core.h"


/////////////////////////////////////////////////////////////////////////////
// Local LED handler function
/////////////////////////////////////////////////////////////////////////////
static s32 LED_Handler(u16 *gp_leds)
{
  u8 track;

  // TODO: requires handling for more than 16 tracks
  for(track=0; track<16; ++track)
    if( seq_core_trk[track].state.MUTED )
      *gp_leds |= (1 << track);

  return 0; // no error
}


/////////////////////////////////////////////////////////////////////////////
// Local encoder callback function
// Should return:
//   1 if value has been changed
//   0 if value hasn't been changed
//  -1 if invalid or unsupported encoder
/////////////////////////////////////////////////////////////////////////////
static s32 Encoder_Handler(seq_ui_encoder_t encoder, s32 incrementer)
{
#if 0
  // leads to: comparison is always true due to limited range of data type
  if( (encoder >= SEQ_UI_ENCODER_GP1 && encoder <= SEQ_UI_ENCODER_GP16) ) {
#else
  if( encoder <= SEQ_UI_ENCODER_GP16 ) {
#endif
    // access to seq_core_trk[] must be atomic!
    portENTER_CRITICAL();
    seq_core_trk[encoder].state.MUTED = incrementer >= 0;
    portEXIT_CRITICAL();

    return 1; // value changed
  }

  return -1; // invalid or unsupported encoder
}


/////////////////////////////////////////////////////////////////////////////
// Local button callback function
// Should return:
//   1 if value has been changed
//   0 if value hasn't been changed
//  -1 if invalid or unsupported button
/////////////////////////////////////////////////////////////////////////////
static s32 Button_Handler(seq_ui_button_t button, s32 depressed)
{
  if( depressed ) return 0; // ignore when button depressed

#if 0
  // leads to: comparison is always true due to limited range of data type
  if( button >= SEQ_UI_BUTTON_GP1 && button <= SEQ_UI_BUTTON_GP16 ) {
#else
  if( button <= SEQ_UI_BUTTON_GP16 ) {
#endif
    // access to seq_core_trk[] must be atomic!
    portENTER_CRITICAL();
    seq_core_trk[button].state.MUTED ^= 1;
    portEXIT_CRITICAL();

    return 1; // value always changed
  }

  return -1; // invalid or unsupported button
}


/////////////////////////////////////////////////////////////////////////////
// Local Display Handler function
// IN: <high_prio>: if set, a high-priority LCD update is requested
/////////////////////////////////////////////////////////////////////////////
static s32 LCD_Handler(u8 high_prio)
{
  // layout:
  // 00000000001111111111222222222233333333330000000000111111111122222222223333333333
  // 01234567890123456789012345678901234567890123456789012345678901234567890123456789
  // <--------------------------------------><-------------------------------------->
  //  > 1<   2    3    4    5    6    7    8    9   10   11   12   13   14   15   16 
  // ...horizontal VU meters...

  if( high_prio ) {
    ///////////////////////////////////////////////////////////////////////////
    // frequently update VU meters
    SEQ_LCD_CursorSet(0, 1);

    u8 track;
    seq_core_trk_t *t = &seq_core_trk[0];
    for(track=0; track<16; ++t, ++track) {
      if( seq_core_trk[track].state.MUTED )
	SEQ_LCD_PrintString("Mute ");
      else
	SEQ_LCD_PrintHBar(t->vu_meter >> 3);
    }
  } else {
    ///////////////////////////////////////////////////////////////////////////
    SEQ_LCD_CursorSet(0, 0);

    u8 track;
    for(track=0; track<16; ++track) {
      if( SEQ_UI_IsSelectedTrack(track) )
	SEQ_LCD_PrintFormattedString(" >%2d<", track+1);
      else
	SEQ_LCD_PrintFormattedString("  %2d ", track+1);
    }
  }

  return 0; // no error
}


/////////////////////////////////////////////////////////////////////////////
// Initialisation
/////////////////////////////////////////////////////////////////////////////
s32 SEQ_UI_MUTE_Init(u32 mode)
{
  // install callback routines
  SEQ_UI_InstallButtonCallback(Button_Handler);
  SEQ_UI_InstallEncoderCallback(Encoder_Handler);
  SEQ_UI_InstallLEDCallback(LED_Handler);
  SEQ_UI_InstallLCDCallback(LCD_Handler);

  // we want to show horizontal VU meters
  SEQ_LCD_InitSpecialChars(SEQ_LCD_CHARSET_HBars);

  return 0; // no error
}
