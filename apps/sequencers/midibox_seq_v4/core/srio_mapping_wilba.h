// $Id$
/*
 * Temporary file which describes the DIN/DOUT mapping (later part of setup_* file)
 *
 * ==========================================================================
 *
 *  Copyright (C) 2008 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

#ifndef _SRIO_MAPPING_V4_H
#define _SRIO_MAPPING_V4_H

/////////////////////////////////////////////////////////////////////////////
// Global definitions
/////////////////////////////////////////////////////////////////////////////


// === Shift Register Matrix ===
//
// set this value to 1 if each track has its own set of 16 LEDs to display unmuted steps and current sequencer position
// or if you are using a button/led matrix for misc. button/LED functions
#define DEFAULT_SRM_ENABLED     1
//
// define the shift registers to which the anodes of these LEDs are connected
// Note: they can be equal to DEFAULT_GP_DOUT_SR_[LH], this saves two shift registers, but doesn't allow a separate view of UI selections
#define DEFAULT_SRM_DOUT_L1	0
#define DEFAULT_SRM_DOUT_R1	0
//
// for misc. LED functions
#define DEFAULT_SRM_DOUT_M	2
//
// define the shift register to which the cathodes of these LEDs are connected
// Note that the whole shift register (8 pins) will be allocated! The 4 select lines are duplicated (4 for LED matrix, 4 for button matrix)
// The second DOUT_CATHODES2 selection is optional if LEDs with high power consumption are used - set this to 0 if not used
#define DEFAULT_SRM_DOUT_CATHODES1	0
#define DEFAULT_SRM_DOUT_CATHODES2	0
//
// another select line for misc. button/led functions - all 8 select pins are used for a 8x8 button/led matrix
#define DEFAULT_SRM_DOUT_CATHODESM	1
//
// 0: no mapping of Misc LEDs
// 1: enable GP LED -> DOUT_M mapping for Wilba's MB-SEQ PCB
#define DEFAULT_SRM_DOUT_M_MAPPING      1
//
// set an inversion mask for the DOUT shift registers if sink drivers (transistors)
// have been added to the cathode lines
// Settings: 0x00 - no sink drivers
//           0xf0 - sink drivers connected to D0..D3
//           0x0f - sink drivers connected to D7..D4
#define DEFAULT_SRM_CATHODES_INV_MASK   0x00
//
// same for misc. button/led functions
#define DEFAULT_SRM_CATHODES_INV_MASK_M 0x00
//
// set this to 1, if DUO colour LEDs are connected to the LED matrix
#define DEFAULT_SRM_DOUT_DUOCOLOUR	0
//
// define the shift registers to which the anodes of the "second colour" (red) LEDs are connected
#define DEFAULT_SRM_DOUT_L2	0
#define DEFAULT_SRM_DOUT_R2	0
//
// set this to 1 if a button matrix is connected
#define DEFAULT_SRM_BUTTONS_ENABLED 1
// set this to 1 if these buttons should only control the "step triggers" (gate, and other assigned triggers) - and no UI functions
#define DEFAULT_SRM_BUTTONS_NO_UI   1
// define the DIN shift registers to which the button matrix is connected
#define DEFAULT_SRM_DIN_L	0
#define DEFAULT_SRM_DIN_R	0
//
// 8x8 matrix for misc. button functions
#define DEFAULT_SRM_DIN_M	2


#endif /* _SRIO_MAPPING_V4_H */
