/* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
// $Id$
/*
 * MIDIbox SID Wavetable Sequencer
 *
 * ==========================================================================
 *
 *  Copyright (C) 2010 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

#include <string.h>
#include "MbSidWt.h"


/////////////////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////////////////
MbSidWt::MbSidWt()
{
    init();
}


/////////////////////////////////////////////////////////////////////////////
// Destructor
/////////////////////////////////////////////////////////////////////////////
MbSidWt::~MbSidWt()
{
}



/////////////////////////////////////////////////////////////////////////////
// WT init function
/////////////////////////////////////////////////////////////////////////////
void MbSidWt::init(void)
{
    // clear flags
    restartReq = false;
    clockReq = false;

    // clear variables
    wtBegin = 0;
    wtEnd = 0;
    wtLoop = 0;
    wtSpeed = 0;
    wtOneshotMode = false;

    wtOut = -1;

    wtDrumSpeed = 0;
    wtDrumPar = 0;
    wtPos = 0;
    wtDivCtr = 0;
}


/////////////////////////////////////////////////////////////////////////////
// Wavetable handler
/////////////////////////////////////////////////////////////////////////////
bool MbSidWt::tick(s32 step, const u8 &updateSpeedFactor)
{
    bool restarted = false;

    if( step >= 0 ) {
        // use modulated step position
        // scale between begin/end range

        if( wtEnd > wtBegin ) {
            s32 range = wtEnd - wtBegin + 1;
            step = wtBegin + ((step * range) / 128);
        } else {
            // should we invert the waveform?
            s32 range = wtBegin - wtEnd + 1;
            step = wtEnd + ((step * range) / 128);
        }
    } else {
        // don't use modulated position - normal mode
        bool nextStepReq = false;

        // check if WT reset requested
        if( restartReq ) {
            restartReq = false;
            restarted = true;

            // next clock will increment div to 0
            wtDivCtr = ~0;
            // next step will increment to start position
            wtPos = wtBegin - 1;
        }

        // check for WT clock event
        if( clockReq ) {
            clockReq = false;
            // increment clock divider
            // reset divider if it already has reached the target value
            if( ++wtDivCtr == 0 || (wtDivCtr > wtSpeed) ) {
                wtDivCtr = 0;
                nextStepReq = true;
            }
        }

        // check for next step request
        // skip if position is 0xaa (notifies oneshot -> WT stopped)
        if( nextStepReq && wtPos != 0xaa ) {
            // increment position counter, reset at end position
            if( ++wtPos > wtEnd ) {
                restarted = true;
                // if oneshot mode: set position to 0xaa, WT is stopped now!
                if( wtOneshotMode )
                    wtPos = 0xaa;
                else
                    wtPos = wtLoop;
            }
            step = wtPos; // step is positive now -> will be played
        }
    }

    wtOut = step;

    return restarted;
}


/////////////////////////////////////////////////////////////////////////////
// Wavetable handler from drum models
/////////////////////////////////////////////////////////////////////////////
bool MbSidWt::tick(const sid_se_engine_t &engine, const u8 &updateSpeedFactor,
                   sid_drum_model_t *drumModel, u8 &voiceNote, u8 &voiceWaveform)
{
    bool restarted = false;
    bool nextStepReq = false;

    // exit if no drum model selected
    if( !drumModel )
        return false;

    // check if WT reset requested
    if( restartReq ) {
        restartReq = false;
        // next clock will increment div to 0
        wtDivCtr = ~0;
        // next step will increment to start position
        wtPos = ~0;
    }

    // clock with each update cycle, so that we are independent from the selected BPM rate
    // increment clock divider
    // reset divider if it already has reached the target value
    if( ++wtDivCtr > (wtDrumSpeed * updateSpeedFactor) ) {
        wtDivCtr = 0;
        nextStepReq = true;
    }

    // check for next step request
    // skip if position is 0xaa (notifies oneshot -> WT stopped)
    if( nextStepReq && wtPos != 0xaa ) {
        // increment position counter, reset at end position
        ++wtPos;
        if( drumModel->wavetable[2*wtPos] == 0 ) {
            if( drumModel->wt_loop == 0xff )
                wtPos = 0xaa; // oneshot mode
            else
                wtPos = drumModel->wt_loop;
        }

        if( wtPos != 0xaa ) {
            // "play" the step
            int note = drumModel->wavetable[2*wtPos + 0];
            // transfer to voice
            // if bit #7 of note entry is set: add PAR3/2 and saturate
            if( note & (1 << 7) ) {
                note = (note & 0x7f) + (((int)wtDrumPar - 0x80) / 2);
                if( note > 127 ) note = 127; else if( note < 0 ) note = 0;
            }
            voiceNote = note;

            // set waveform
            voiceWaveform = drumModel->wavetable[2*wtPos + 1];

#if 0
            DEBUG_MSG("WT %d: %d (%02x %02x)\n", wtNum, wtPos, voiceNote, voiceWaveform);
#endif
        }
    }

    return restarted;
}
