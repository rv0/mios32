// $Id$
/*
 * Header file for LFO routines
 *
 * ==========================================================================
 *
 *  Copyright (C) 2008 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

#ifndef _SEQ_LFO_H
#define _SEQ_LFO_H

#include "seq_layer.h"

/////////////////////////////////////////////////////////////////////////////
// Global definitions
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Global Types
/////////////////////////////////////////////////////////////////////////////

typedef enum {
  SEQ_LFO_WAVEFORM_Off,
  SEQ_LFO_WAVEFORM_Sine,
  SEQ_LFO_WAVEFORM_Triangle,
  SEQ_LFO_WAVEFORM_Saw,
  SEQ_LFO_WAVEFORM_Rec05,
  SEQ_LFO_WAVEFORM_Rec10,
  SEQ_LFO_WAVEFORM_Rec15,
  SEQ_LFO_WAVEFORM_Rec20,
  SEQ_LFO_WAVEFORM_Rec25,
  SEQ_LFO_WAVEFORM_Rec30,
  SEQ_LFO_WAVEFORM_Rec35,
  SEQ_LFO_WAVEFORM_Rec40,
  SEQ_LFO_WAVEFORM_Rec45,
  SEQ_LFO_WAVEFORM_Rec50,
  SEQ_LFO_WAVEFORM_Rec55,
  SEQ_LFO_WAVEFORM_Rec60,
  SEQ_LFO_WAVEFORM_Rec65,
  SEQ_LFO_WAVEFORM_Rec70,
  SEQ_LFO_WAVEFORM_Rec75,
  SEQ_LFO_WAVEFORM_Rec80,
  SEQ_LFO_WAVEFORM_Rec85,
  SEQ_LFO_WAVEFORM_Rec90,
  SEQ_LFO_WAVEFORM_Rec95,
} seq_lfo_waveform_t;


typedef union {
  struct {
    unsigned ALL:5;
  };
  struct {
    unsigned ONE_SHOT:1;
    unsigned NOTE:1;
    unsigned VELOCITY:1;
    unsigned LENGTH:1;
    unsigned CC:1;
  };
} seq_lfo_enable_flags_t;


/////////////////////////////////////////////////////////////////////////////
// Prototypes
/////////////////////////////////////////////////////////////////////////////

extern s32 SEQ_LFO_Init(u32 mode);

extern s32 SEQ_LFO_ResetTrk(u8 track);
extern s32 SEQ_LFO_HandleTrk(u8 track, u32 bpm_tick);
extern s32 SEQ_LFO_Event(u8 track, seq_layer_evnt_t *e);
extern s32 SEQ_LFO_FastCC_Event(u8 track, u32 bpm_tick, mios32_midi_package_t *p);


/////////////////////////////////////////////////////////////////////////////
// Export global variables
/////////////////////////////////////////////////////////////////////////////

#endif /* _SEQ_LFO_H */