// $Id$
/*
 * Patch Layer for MIDIO128 V3
 *
 * ==========================================================================
 *
 *  Copyright (C) 2011 Thorsten Klose (tk@midibox.org)
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

#include "midio_patch.h"
#include "midio_dout.h"
#include "midio_file.h"
#include "midio_file_p.h"


/////////////////////////////////////////////////////////////////////////////
// Preset patch
/////////////////////////////////////////////////////////////////////////////

midio_patch_din_entry_t  midio_patch_din[MIDIO_PATCH_NUM_DIN] = {
  // ports   mode     ON event           OFF event           SR/Pin
  {  0x1011,  0,   0x90, 0x30, 0x7f,  0x90, 0x30, 0x00 }, // 1.D0
  {  0x1011,  0,   0x90, 0x31, 0x7f,  0x90, 0x31, 0x00 }, // 1.D1
  {  0x1011,  0,   0x90, 0x32, 0x7f,  0x90, 0x32, 0x00 }, // 1.D2
  {  0x1011,  0,   0x90, 0x33, 0x7f,  0x90, 0x33, 0x00 }, // 1.D3
  {  0x1011,  0,   0x90, 0x34, 0x7f,  0x90, 0x34, 0x00 }, // 1.D4
  {  0x1011,  0,   0x90, 0x35, 0x7f,  0x90, 0x35, 0x00 }, // 1.D5
  {  0x1011,  0,   0x90, 0x36, 0x7f,  0x90, 0x36, 0x00 }, // 1.D6
  {  0x1011,  0,   0x90, 0x37, 0x7f,  0x90, 0x37, 0x00 }, // 1.D7

  // ports   mode     ON event           OFF event           SR/Pin
  {  0x1011,  0,   0x90, 0x38, 0x7f,  0x90, 0x38, 0x00 }, // 2.D0
  {  0x1011,  0,   0x90, 0x39, 0x7f,  0x90, 0x39, 0x00 }, // 2.D1
  {  0x1011,  0,   0x90, 0x3a, 0x7f,  0x90, 0x3a, 0x00 }, // 2.D2
  {  0x1011,  0,   0x90, 0x3b, 0x7f,  0x90, 0x3b, 0x00 }, // 2.D3
  {  0x1011,  0,   0x90, 0x3c, 0x7f,  0x90, 0x3c, 0x00 }, // 2.D4
  {  0x1011,  0,   0x90, 0x3d, 0x7f,  0x90, 0x3d, 0x00 }, // 2.D5
  {  0x1011,  0,   0x90, 0x3e, 0x7f,  0x90, 0x3e, 0x00 }, // 2.D6
  {  0x1011,  0,   0x90, 0x3f, 0x7f,  0x90, 0x3f, 0x00 }, // 2.D7

  // ports   mode     ON event           OFF event           SR/Pin
  {  0x1011,  0,   0x90, 0x40, 0x7f,  0x90, 0x40, 0x00 }, // 3.D0
  {  0x1011,  0,   0x90, 0x41, 0x7f,  0x90, 0x41, 0x00 }, // 3.D1
  {  0x1011,  0,   0x90, 0x42, 0x7f,  0x90, 0x42, 0x00 }, // 3.D2
  {  0x1011,  0,   0x90, 0x43, 0x7f,  0x90, 0x43, 0x00 }, // 3.D3
  {  0x1011,  0,   0x90, 0x44, 0x7f,  0x90, 0x44, 0x00 }, // 3.D4
  {  0x1011,  0,   0x90, 0x45, 0x7f,  0x90, 0x45, 0x00 }, // 3.D5
  {  0x1011,  0,   0x90, 0x46, 0x7f,  0x90, 0x46, 0x00 }, // 3.D6
  {  0x1011,  0,   0x90, 0x47, 0x7f,  0x90, 0x47, 0x00 }, // 3.D7

  // ports   mode     ON event           OFF event           SR/Pin
  {  0x1011,  0,   0x90, 0x48, 0x7f,  0x90, 0x48, 0x00 }, // 4.D0
  {  0x1011,  0,   0x90, 0x49, 0x7f,  0x90, 0x49, 0x00 }, // 4.D1
  {  0x1011,  0,   0x90, 0x4a, 0x7f,  0x90, 0x4a, 0x00 }, // 4.D2
  {  0x1011,  0,   0x90, 0x4b, 0x7f,  0x90, 0x4b, 0x00 }, // 4.D3
  {  0x1011,  0,   0x90, 0x4c, 0x7f,  0x90, 0x4c, 0x00 }, // 4.D4
  {  0x1011,  0,   0x90, 0x4d, 0x7f,  0x90, 0x4d, 0x00 }, // 4.D5
  {  0x1011,  0,   0x90, 0x4e, 0x7f,  0x90, 0x4e, 0x00 }, // 4.D6
  {  0x1011,  0,   0x90, 0x4f, 0x7f,  0x90, 0x4f, 0x00 }, // 4.D7

  // ports   mode     ON event           OFF event           SR/Pin
  {  0x1011,  0,   0x90, 0x50, 0x7f,  0x90, 0x50, 0x00 }, // 5.D0
  {  0x1011,  0,   0x90, 0x51, 0x7f,  0x90, 0x51, 0x00 }, // 5.D1
  {  0x1011,  0,   0x90, 0x52, 0x7f,  0x90, 0x52, 0x00 }, // 5.D2
  {  0x1011,  0,   0x90, 0x53, 0x7f,  0x90, 0x53, 0x00 }, // 5.D3
  {  0x1011,  0,   0x90, 0x54, 0x7f,  0x90, 0x54, 0x00 }, // 5.D4
  {  0x1011,  0,   0x90, 0x55, 0x7f,  0x90, 0x55, 0x00 }, // 5.D5
  {  0x1011,  0,   0x90, 0x56, 0x7f,  0x90, 0x56, 0x00 }, // 5.D6
  {  0x1011,  0,   0x90, 0x57, 0x7f,  0x90, 0x57, 0x00 }, // 5.D7

  // ports   mode     ON event           OFF event           SR/Pin
  {  0x1011,  0,   0x90, 0x58, 0x7f,  0x90, 0x58, 0x00 }, // 6.D0
  {  0x1011,  0,   0x90, 0x59, 0x7f,  0x90, 0x59, 0x00 }, // 6.D1
  {  0x1011,  0,   0x90, 0x5a, 0x7f,  0x90, 0x5a, 0x00 }, // 6.D2
  {  0x1011,  0,   0x90, 0x5b, 0x7f,  0x90, 0x5b, 0x00 }, // 6.D3
  {  0x1011,  0,   0x90, 0x5c, 0x7f,  0x90, 0x5c, 0x00 }, // 6.D4
  {  0x1011,  0,   0x90, 0x5d, 0x7f,  0x90, 0x5d, 0x00 }, // 6.D5
  {  0x1011,  0,   0x90, 0x5e, 0x7f,  0x90, 0x5e, 0x00 }, // 6.D6
  {  0x1011,  0,   0x90, 0x5f, 0x7f,  0x90, 0x5f, 0x00 }, // 6.D7

  // ports   mode     ON event           OFF event           SR/Pin
  {  0x1011,  0,   0x90, 0x60, 0x7f,  0x90, 0x60, 0x00 }, // 7.D0
  {  0x1011,  0,   0x90, 0x61, 0x7f,  0x90, 0x61, 0x00 }, // 7.D1
  {  0x1011,  0,   0x90, 0x62, 0x7f,  0x90, 0x62, 0x00 }, // 7.D2
  {  0x1011,  0,   0x90, 0x63, 0x7f,  0x90, 0x63, 0x00 }, // 7.D3
  {  0x1011,  0,   0x90, 0x64, 0x7f,  0x90, 0x64, 0x00 }, // 7.D4
  {  0x1011,  0,   0x90, 0x65, 0x7f,  0x90, 0x65, 0x00 }, // 7.D5
  {  0x1011,  0,   0x90, 0x66, 0x7f,  0x90, 0x66, 0x00 }, // 7.D6
  {  0x1011,  0,   0x90, 0x67, 0x7f,  0x90, 0x67, 0x00 }, // 7.D7

  // ports   mode     ON event           OFF event           SR/Pin
  {  0x1011,  0,   0x90, 0x68, 0x7f,  0x90, 0x68, 0x00 }, // 8.D0
  {  0x1011,  0,   0x90, 0x69, 0x7f,  0x90, 0x69, 0x00 }, // 8.D1
  {  0x1011,  0,   0x90, 0x6a, 0x7f,  0x90, 0x6a, 0x00 }, // 8.D2
  {  0x1011,  0,   0x90, 0x6b, 0x7f,  0x90, 0x6b, 0x00 }, // 8.D3
  {  0x1011,  0,   0x90, 0x6c, 0x7f,  0x90, 0x6c, 0x00 }, // 8.D4
  {  0x1011,  0,   0x90, 0x6d, 0x7f,  0x90, 0x6d, 0x00 }, // 8.D5
  {  0x1011,  0,   0x90, 0x6e, 0x7f,  0x90, 0x6e, 0x00 }, // 8.D6
  {  0x1011,  0,   0x90, 0x6f, 0x7f,  0x90, 0x6f, 0x00 }, // 8.D7

  // ports   mode     ON event           OFF event           SR/Pin
  {  0x1011,  0,   0xb0, 0x10, 0x7f,  0xb0, 0x10, 0x00 }, // 9.D0
  {  0x1011,  0,   0xb0, 0x11, 0x7f,  0xb0, 0x11, 0x00 }, // 9.D1
  {  0x1011,  0,   0xb0, 0x12, 0x7f,  0xb0, 0x12, 0x00 }, // 9.D2
  {  0x1011,  0,   0xb0, 0x13, 0x7f,  0xb0, 0x13, 0x00 }, // 9.D3
  {  0x1011,  0,   0xb0, 0x14, 0x7f,  0xb0, 0x14, 0x00 }, // 9.D4
  {  0x1011,  0,   0xb0, 0x15, 0x7f,  0xb0, 0x15, 0x00 }, // 9.D5
  {  0x1011,  0,   0xb0, 0x16, 0x7f,  0xb0, 0x16, 0x00 }, // 9.D6
  {  0x1011,  0,   0xb0, 0x17, 0x7f,  0xb0, 0x17, 0x00 }, // 9.D7

  // ports   mode     ON event           OFF event           SR/Pin
  {  0x1011,  0,   0xb0, 0x18, 0x7f,  0xb0, 0x18, 0x00 }, // 10.D0
  {  0x1011,  0,   0xb0, 0x19, 0x7f,  0xb0, 0x19, 0x00 }, // 10.D1
  {  0x1011,  0,   0xb0, 0x1a, 0x7f,  0xb0, 0x1a, 0x00 }, // 10.D2
  {  0x1011,  0,   0xb0, 0x1b, 0x7f,  0xb0, 0x1b, 0x00 }, // 10.D3
  {  0x1011,  0,   0xb0, 0x1c, 0x7f,  0xb0, 0x1c, 0x00 }, // 10.D4
  {  0x1011,  0,   0xb0, 0x1d, 0x7f,  0xb0, 0x1d, 0x00 }, // 10.D5
  {  0x1011,  0,   0xb0, 0x1e, 0x7f,  0xb0, 0x1e, 0x00 }, // 10.D6
  {  0x1011,  0,   0xb0, 0x1f, 0x7f,  0xb0, 0x1f, 0x00 }, // 10.D7

  // ports   mode     ON event           OFF event           SR/Pin
  {  0x1011,  0,   0xb0, 0x20, 0x7f,  0xb0, 0x20, 0x00 }, // 11.D0
  {  0x1011,  0,   0xb0, 0x21, 0x7f,  0xb0, 0x21, 0x00 }, // 11.D1
  {  0x1011,  0,   0xb0, 0x22, 0x7f,  0xb0, 0x22, 0x00 }, // 11.D2
  {  0x1011,  0,   0xb0, 0x23, 0x7f,  0xb0, 0x23, 0x00 }, // 11.D3
  {  0x1011,  0,   0xb0, 0x24, 0x7f,  0xb0, 0x24, 0x00 }, // 11.D4
  {  0x1011,  0,   0xb0, 0x25, 0x7f,  0xb0, 0x25, 0x00 }, // 11.D5
  {  0x1011,  0,   0xb0, 0x26, 0x7f,  0xb0, 0x26, 0x00 }, // 11.D6
  {  0x1011,  0,   0xb0, 0x27, 0x7f,  0xb0, 0x27, 0x00 }, // 11.D7

  // ports   mode     ON event           OFF event           SR/Pin
  {  0x1011,  0,   0xb0, 0x28, 0x7f,  0xb0, 0x28, 0x00 }, // 12.D0
  {  0x1011,  0,   0xb0, 0x29, 0x7f,  0xb0, 0x29, 0x00 }, // 12.D1
  {  0x1011,  0,   0xb0, 0x2a, 0x7f,  0xb0, 0x2a, 0x00 }, // 12.D2
  {  0x1011,  0,   0xb0, 0x2b, 0x7f,  0xb0, 0x2b, 0x00 }, // 12.D3
  {  0x1011,  0,   0xb0, 0x2c, 0x7f,  0xb0, 0x2c, 0x00 }, // 12.D4
  {  0x1011,  0,   0xb0, 0x2d, 0x7f,  0xb0, 0x2d, 0x00 }, // 12.D5
  {  0x1011,  0,   0xb0, 0x2e, 0x7f,  0xb0, 0x2e, 0x00 }, // 12.D6
  {  0x1011,  0,   0xb0, 0x2f, 0x7f,  0xb0, 0x2f, 0x00 }, // 12.D7

  // ports   mode     ON event           OFF event           SR/Pin
  {  0x1011,  0,   0xb0, 0x30, 0x7f,  0xb0, 0x30, 0x00 }, // 13.D0
  {  0x1011,  0,   0xb0, 0x31, 0x7f,  0xb0, 0x31, 0x00 }, // 13.D1
  {  0x1011,  0,   0xb0, 0x32, 0x7f,  0xb0, 0x32, 0x00 }, // 13.D2
  {  0x1011,  0,   0xb0, 0x33, 0x7f,  0xb0, 0x33, 0x00 }, // 13.D3
  {  0x1011,  0,   0xb0, 0x34, 0x7f,  0xb0, 0x34, 0x00 }, // 13.D4
  {  0x1011,  0,   0xb0, 0x35, 0x7f,  0xb0, 0x35, 0x00 }, // 13.D5
  {  0x1011,  0,   0xb0, 0x36, 0x7f,  0xb0, 0x36, 0x00 }, // 13.D6
  {  0x1011,  0,   0xb0, 0x37, 0x7f,  0xb0, 0x37, 0x00 }, // 13.D7

  // ports   mode     ON event           OFF event           SR/Pin
  {  0x1011,  0,   0xb0, 0x38, 0x7f,  0xb0, 0x38, 0x00 }, // 14.D0
  {  0x1011,  0,   0xb0, 0x39, 0x7f,  0xb0, 0x39, 0x00 }, // 14.D1
  {  0x1011,  0,   0xb0, 0x3a, 0x7f,  0xb0, 0x3a, 0x00 }, // 14.D2
  {  0x1011,  0,   0xb0, 0x3b, 0x7f,  0xb0, 0x3b, 0x00 }, // 14.D3
  {  0x1011,  0,   0xb0, 0x3c, 0x7f,  0xb0, 0x3c, 0x00 }, // 14.D4
  {  0x1011,  0,   0xb0, 0x3d, 0x7f,  0xb0, 0x3d, 0x00 }, // 14.D5
  {  0x1011,  0,   0xb0, 0x3e, 0x7f,  0xb0, 0x3e, 0x00 }, // 14.D6
  {  0x1011,  0,   0xb0, 0x3f, 0x7f,  0xb0, 0x3f, 0x00 }, // 14.D7

  // ports   mode     ON event           OFF event           SR/Pin
  {  0x1011,  0,   0xb0, 0x40, 0x7f,  0xb0, 0x40, 0x00 }, // 15.D0
  {  0x1011,  0,   0xb0, 0x41, 0x7f,  0xb0, 0x41, 0x00 }, // 15.D1
  {  0x1011,  0,   0xb0, 0x42, 0x7f,  0xb0, 0x42, 0x00 }, // 15.D2
  {  0x1011,  0,   0xb0, 0x43, 0x7f,  0xb0, 0x43, 0x00 }, // 15.D3
  {  0x1011,  0,   0xb0, 0x44, 0x7f,  0xb0, 0x44, 0x00 }, // 15.D4
  {  0x1011,  0,   0xb0, 0x45, 0x7f,  0xb0, 0x45, 0x00 }, // 15.D5
  {  0x1011,  0,   0xb0, 0x46, 0x7f,  0xb0, 0x46, 0x00 }, // 15.D6
  {  0x1011,  0,   0xb0, 0x47, 0x7f,  0xb0, 0x47, 0x00 }, // 15.D7

  // ports   mode     ON event           OFF event           SR/Pin
  {  0x1011,  0,   0xb0, 0x48, 0x7f,  0xb0, 0x48, 0x00 }, // 16.D0
  {  0x1011,  0,   0xb0, 0x49, 0x7f,  0xb0, 0x49, 0x00 }, // 16.D1
  {  0x1011,  0,   0xb0, 0x4a, 0x7f,  0xb0, 0x4a, 0x00 }, // 16.D2
  {  0x1011,  0,   0xb0, 0x4b, 0x7f,  0xb0, 0x4b, 0x00 }, // 16.D3
  {  0x1011,  0,   0xb0, 0x4c, 0x7f,  0xb0, 0x4c, 0x00 }, // 16.D4
  {  0x1011,  0,   0xb0, 0x4d, 0x7f,  0xb0, 0x4d, 0x00 }, // 16.D5
  {  0x1011,  0,   0xb0, 0x4e, 0x7f,  0xb0, 0x4e, 0x00 }, // 16.D6
  {  0x1011,  0,   0xb0, 0x4f, 0x7f,  0xb0, 0x4f, 0x00 }, // 16.D7
};

midio_patch_dout_entry_t midio_patch_dout[MIDIO_PATCH_NUM_DOUT] = {
  // ports   event           SR/Pin
  {  0x1011, 0x90, 0x30 }, // 1.D7
  {  0x1011, 0x90, 0x31 }, // 1.D6
  {  0x1011, 0x90, 0x32 }, // 1.D5
  {  0x1011, 0x90, 0x33 }, // 1.D4
  {  0x1011, 0x90, 0x34 }, // 1.D3
  {  0x1011, 0x90, 0x35 }, // 1.D2
  {  0x1011, 0x90, 0x36 }, // 1.D1
  {  0x1011, 0x90, 0x37 }, // 1.D0

  // ports   event           SR/Pin
  {  0x1011, 0x90, 0x38 }, // 2.D7
  {  0x1011, 0x90, 0x39 }, // 2.D6
  {  0x1011, 0x90, 0x3a }, // 2.D5
  {  0x1011, 0x90, 0x3b }, // 2.D4
  {  0x1011, 0x90, 0x3c }, // 2.D3
  {  0x1011, 0x90, 0x3d }, // 2.D2
  {  0x1011, 0x90, 0x3e }, // 2.D1
  {  0x1011, 0x90, 0x3f }, // 2.D0

  // ports   event           SR/Pin
  {  0x1011, 0x90, 0x40 }, // 3.D7
  {  0x1011, 0x90, 0x41 }, // 3.D6
  {  0x1011, 0x90, 0x42 }, // 3.D5
  {  0x1011, 0x90, 0x43 }, // 3.D4
  {  0x1011, 0x90, 0x44 }, // 3.D3
  {  0x1011, 0x90, 0x45 }, // 3.D2
  {  0x1011, 0x90, 0x46 }, // 3.D1
  {  0x1011, 0x90, 0x47 }, // 3.D0

  // ports   event           SR/Pin
  {  0x1011, 0x90, 0x48 }, // 4.D7
  {  0x1011, 0x90, 0x49 }, // 4.D6
  {  0x1011, 0x90, 0x4a }, // 4.D5
  {  0x1011, 0x90, 0x4b }, // 4.D4
  {  0x1011, 0x90, 0x4c }, // 4.D3
  {  0x1011, 0x90, 0x4d }, // 4.D2
  {  0x1011, 0x90, 0x4e }, // 4.D1
  {  0x1011, 0x90, 0x4f }, // 4.D0

  // ports   event           SR/Pin
  {  0x1011, 0x90, 0x50 }, // 5.D7
  {  0x1011, 0x90, 0x51 }, // 5.D6
  {  0x1011, 0x90, 0x52 }, // 5.D5
  {  0x1011, 0x90, 0x53 }, // 5.D4
  {  0x1011, 0x90, 0x54 }, // 5.D3
  {  0x1011, 0x90, 0x55 }, // 5.D2
  {  0x1011, 0x90, 0x56 }, // 5.D1
  {  0x1011, 0x90, 0x57 }, // 5.D0

  // ports   event           SR/Pin
  {  0x1011, 0x90, 0x58 }, // 6.D7
  {  0x1011, 0x90, 0x59 }, // 6.D6
  {  0x1011, 0x90, 0x5a }, // 6.D5
  {  0x1011, 0x90, 0x5b }, // 6.D4
  {  0x1011, 0x90, 0x5c }, // 6.D3
  {  0x1011, 0x90, 0x5d }, // 6.D2
  {  0x1011, 0x90, 0x5e }, // 6.D1
  {  0x1011, 0x90, 0x5f }, // 6.D0

  // ports   event           SR/Pin
  {  0x1011, 0x90, 0x60 }, // 7.D7
  {  0x1011, 0x90, 0x61 }, // 7.D6
  {  0x1011, 0x90, 0x62 }, // 7.D5
  {  0x1011, 0x90, 0x63 }, // 7.D4
  {  0x1011, 0x90, 0x64 }, // 7.D3
  {  0x1011, 0x90, 0x65 }, // 7.D2
  {  0x1011, 0x90, 0x66 }, // 7.D1
  {  0x1011, 0x90, 0x67 }, // 7.D0

  // ports   event           SR/Pin
  {  0x1011, 0x90, 0x68 }, // 8.D7
  {  0x1011, 0x90, 0x69 }, // 8.D6
  {  0x1011, 0x90, 0x6a }, // 8.D5
  {  0x1011, 0x90, 0x6b }, // 8.D4
  {  0x1011, 0x90, 0x6c }, // 8.D3
  {  0x1011, 0x90, 0x6d }, // 8.D2
  {  0x1011, 0x90, 0x6e }, // 8.D1
  {  0x1011, 0x90, 0x6f }, // 8.D0

  // ports   event           SR/Pin
  {  0x1011, 0xb0, 0x10 }, // 9.D7
  {  0x1011, 0xb0, 0x11 }, // 9.D6
  {  0x1011, 0xb0, 0x12 }, // 9.D5
  {  0x1011, 0xb0, 0x13 }, // 9.D4
  {  0x1011, 0xb0, 0x14 }, // 9.D3
  {  0x1011, 0xb0, 0x15 }, // 9.D2
  {  0x1011, 0xb0, 0x16 }, // 9.D1
  {  0x1011, 0xb0, 0x17 }, // 9.D0

  // ports   event           SR/Pin
  {  0x1011, 0xb0, 0x18 }, // 10.D7
  {  0x1011, 0xb0, 0x19 }, // 10.D6
  {  0x1011, 0xb0, 0x1a }, // 10.D5
  {  0x1011, 0xb0, 0x1b }, // 10.D4
  {  0x1011, 0xb0, 0x1c }, // 10.D3
  {  0x1011, 0xb0, 0x1d }, // 10.D2
  {  0x1011, 0xb0, 0x1e }, // 10.D1
  {  0x1011, 0xb0, 0x1f }, // 10.D0

  // ports   event           SR/Pin
  {  0x1011, 0xb0, 0x20 }, // 11.D7
  {  0x1011, 0xb0, 0x21 }, // 11.D6
  {  0x1011, 0xb0, 0x22 }, // 11.D5
  {  0x1011, 0xb0, 0x23 }, // 11.D4
  {  0x1011, 0xb0, 0x24 }, // 11.D3
  {  0x1011, 0xb0, 0x25 }, // 11.D2
  {  0x1011, 0xb0, 0x26 }, // 11.D1
  {  0x1011, 0xb0, 0x27 }, // 11.D0

  // ports   event           SR/Pin
  {  0x1011, 0xb0, 0x28 }, // 12.D7
  {  0x1011, 0xb0, 0x29 }, // 12.D6
  {  0x1011, 0xb0, 0x2a }, // 12.D5
  {  0x1011, 0xb0, 0x2b }, // 12.D4
  {  0x1011, 0xb0, 0x2c }, // 12.D3
  {  0x1011, 0xb0, 0x2d }, // 12.D2
  {  0x1011, 0xb0, 0x2e }, // 12.D1
  {  0x1011, 0xb0, 0x2f }, // 12.D0

  // ports   event           SR/Pin
  {  0x1011, 0xb0, 0x30 }, // 13.D7
  {  0x1011, 0xb0, 0x31 }, // 13.D6
  {  0x1011, 0xb0, 0x32 }, // 13.D5
  {  0x1011, 0xb0, 0x33 }, // 13.D4
  {  0x1011, 0xb0, 0x34 }, // 13.D3
  {  0x1011, 0xb0, 0x35 }, // 13.D2
  {  0x1011, 0xb0, 0x36 }, // 13.D1
  {  0x1011, 0xb0, 0x37 }, // 13.D0

  // ports   event           SR/Pin
  {  0x1011, 0xb0, 0x38 }, // 14.D7
  {  0x1011, 0xb0, 0x39 }, // 14.D6
  {  0x1011, 0xb0, 0x3a }, // 14.D5
  {  0x1011, 0xb0, 0x3b }, // 14.D4
  {  0x1011, 0xb0, 0x3c }, // 14.D3
  {  0x1011, 0xb0, 0x3d }, // 14.D2
  {  0x1011, 0xb0, 0x3e }, // 14.D1
  {  0x1011, 0xb0, 0x3f }, // 14.D0

  // ports   event           SR/Pin
  {  0x1011, 0xb0, 0x40 }, // 15.D7
  {  0x1011, 0xb0, 0x41 }, // 15.D6
  {  0x1011, 0xb0, 0x42 }, // 15.D5
  {  0x1011, 0xb0, 0x43 }, // 15.D4
  {  0x1011, 0xb0, 0x44 }, // 15.D3
  {  0x1011, 0xb0, 0x45 }, // 15.D2
  {  0x1011, 0xb0, 0x46 }, // 15.D1
  {  0x1011, 0xb0, 0x47 }, // 15.D0

  // ports   event           SR/Pin
  {  0x1011, 0xb0, 0x48 }, // 16.D7
  {  0x1011, 0xb0, 0x49 }, // 16.D6
  {  0x1011, 0xb0, 0x4a }, // 16.D5
  {  0x1011, 0xb0, 0x4b }, // 16.D4
  {  0x1011, 0xb0, 0x4c }, // 16.D3
  {  0x1011, 0xb0, 0x4d }, // 16.D2
  {  0x1011, 0xb0, 0x4e }, // 16.D1
  {  0x1011, 0xb0, 0x4f }, // 16.D0
};

midio_patch_ain_entry_t midio_patch_ain[MIDIO_PATCH_NUM_AIN] = {
  // ports   event           AIN Pin
  {  0x0000, 0xb0, 0x07 }, // 0
  {  0x0000, 0xb1, 0x07 }, // 1
  {  0x0000, 0xb2, 0x07 }, // 2
  {  0x0000, 0xb3, 0x07 }, // 3
  {  0x0000, 0xb4, 0x07 }, // 4
  {  0x0000, 0xb5, 0x07 }, // 5
#if MIDIO_PATCH_NUM_AIN >= 7
  {  0x0000, 0xb6, 0x07 }, // 6
#endif
#if MIDIO_PATCH_NUM_AIN >= 8
  {  0x0000, 0xb7, 0x07 }, // 7
#endif
};

midio_patch_ain_entry_t midio_patch_ainser[MIDIO_PATCH_NUM_AINSER] = {
  // ports   event           AINSER Pin
  {  0x1011, 0xb0, 0x10 }, // 1_J6.A0
  {  0x1011, 0xb0, 0x11 }, // 1_J6.A1
  {  0x1011, 0xb0, 0x12 }, // 1_J6.A2
  {  0x1011, 0xb0, 0x13 }, // 1_J6.A3
  {  0x1011, 0xb0, 0x14 }, // 1_J6.A4
  {  0x1011, 0xb0, 0x15 }, // 1_J6.A5
  {  0x1011, 0xb0, 0x16 }, // 1_J6.A6
  {  0x1011, 0xb0, 0x17 }, // 1_J6.A7

  {  0x1011, 0xb0, 0x18 }, // 1_J7.A0
  {  0x1011, 0xb0, 0x19 }, // 1_J7.A1
  {  0x1011, 0xb0, 0x1a }, // 1_J7.A2
  {  0x1011, 0xb0, 0x1b }, // 1_J7.A3
  {  0x1011, 0xb0, 0x1c }, // 1_J7.A4
  {  0x1011, 0xb0, 0x1d }, // 1_J7.A5
  {  0x1011, 0xb0, 0x1e }, // 1_J7.A6
  {  0x1011, 0xb0, 0x1f }, // 1_J7.A7

  {  0x1011, 0xb0, 0x20 }, // 1_J8.A0
  {  0x1011, 0xb0, 0x21 }, // 1_J8.A1
  {  0x1011, 0xb0, 0x22 }, // 1_J8.A2
  {  0x1011, 0xb0, 0x23 }, // 1_J8.A3
  {  0x1011, 0xb0, 0x24 }, // 1_J8.A4
  {  0x1011, 0xb0, 0x25 }, // 1_J8.A5
  {  0x1011, 0xb0, 0x26 }, // 1_J8.A6
  {  0x1011, 0xb0, 0x27 }, // 1_J8.A7

  {  0x1011, 0xb0, 0x28 }, // 1_J9.A0
  {  0x1011, 0xb0, 0x29 }, // 1_J9.A1
  {  0x1011, 0xb0, 0x2a }, // 1_J9.A2
  {  0x1011, 0xb0, 0x2b }, // 1_J9.A3
  {  0x1011, 0xb0, 0x2c }, // 1_J9.A4
  {  0x1011, 0xb0, 0x2d }, // 1_J9.A5
  {  0x1011, 0xb0, 0x2e }, // 1_J9.A6
  {  0x1011, 0xb0, 0x2f }, // 1_J9.A7

  {  0x1011, 0xb0, 0x30 }, // 1_J10.A0
  {  0x1011, 0xb0, 0x31 }, // 1_J10.A1
  {  0x1011, 0xb0, 0x32 }, // 1_J10.A2
  {  0x1011, 0xb0, 0x33 }, // 1_J10.A3
  {  0x1011, 0xb0, 0x34 }, // 1_J10.A4
  {  0x1011, 0xb0, 0x35 }, // 1_J10.A5
  {  0x1011, 0xb0, 0x36 }, // 1_J10.A6
  {  0x1011, 0xb0, 0x37 }, // 1_J10.A7

  {  0x1011, 0xb0, 0x38 }, // 1_J11.A0
  {  0x1011, 0xb0, 0x39 }, // 1_J11.A1
  {  0x1011, 0xb0, 0x3a }, // 1_J11.A2
  {  0x1011, 0xb0, 0x3b }, // 1_J11.A3
  {  0x1011, 0xb0, 0x3c }, // 1_J11.A4
  {  0x1011, 0xb0, 0x3d }, // 1_J11.A5
  {  0x1011, 0xb0, 0x3e }, // 1_J11.A6
  {  0x1011, 0xb0, 0x3f }, // 1_J11.A7

  {  0x1011, 0xb0, 0x40 }, // 1_J12.A0
  {  0x1011, 0xb0, 0x41 }, // 1_J12.A1
  {  0x1011, 0xb0, 0x42 }, // 1_J12.A2
  {  0x1011, 0xb0, 0x43 }, // 1_J12.A3
  {  0x1011, 0xb0, 0x44 }, // 1_J12.A4
  {  0x1011, 0xb0, 0x45 }, // 1_J12.A5
  {  0x1011, 0xb0, 0x46 }, // 1_J12.A6
  {  0x1011, 0xb0, 0x47 }, // 1_J12.A7

  {  0x1011, 0xb0, 0x48 }, // 1_J13.A0
  {  0x1011, 0xb0, 0x49 }, // 1_J13.A1
  {  0x1011, 0xb0, 0x4a }, // 1_J13.A2
  {  0x1011, 0xb0, 0x4b }, // 1_J13.A3
  {  0x1011, 0xb0, 0x4c }, // 1_J13.A4
  {  0x1011, 0xb0, 0x4d }, // 1_J13.A5
  {  0x1011, 0xb0, 0x4e }, // 1_J13.A6
  {  0x1011, 0xb0, 0x4f }, // 1_J13.A7

  {  0x1011, 0xb1, 0x10 }, // 2_J6.A0
  {  0x1011, 0xb1, 0x11 }, // 2_J6.A1
  {  0x1011, 0xb1, 0x12 }, // 2_J6.A2
  {  0x1011, 0xb1, 0x13 }, // 2_J6.A3
  {  0x1011, 0xb1, 0x14 }, // 2_J6.A4
  {  0x1011, 0xb1, 0x15 }, // 2_J6.A5
  {  0x1011, 0xb1, 0x16 }, // 2_J6.A6
  {  0x1011, 0xb1, 0x17 }, // 2_J6.A7

  {  0x1011, 0xb1, 0x18 }, // 2_J7.A0
  {  0x1011, 0xb1, 0x19 }, // 2_J7.A1
  {  0x1011, 0xb1, 0x1a }, // 2_J7.A2
  {  0x1011, 0xb1, 0x1b }, // 2_J7.A3
  {  0x1011, 0xb1, 0x1c }, // 2_J7.A4
  {  0x1011, 0xb1, 0x1d }, // 2_J7.A5
  {  0x1011, 0xb1, 0x1e }, // 2_J7.A6
  {  0x1011, 0xb1, 0x1f }, // 2_J7.A7

  {  0x1011, 0xb1, 0x20 }, // 2_J8.A0
  {  0x1011, 0xb1, 0x21 }, // 2_J8.A1
  {  0x1011, 0xb1, 0x22 }, // 2_J8.A2
  {  0x1011, 0xb1, 0x23 }, // 2_J8.A3
  {  0x1011, 0xb1, 0x24 }, // 2_J8.A4
  {  0x1011, 0xb1, 0x25 }, // 2_J8.A5
  {  0x1011, 0xb1, 0x26 }, // 2_J8.A6
  {  0x1011, 0xb1, 0x27 }, // 2_J8.A7

  {  0x1011, 0xb1, 0x28 }, // 2_J9.A0
  {  0x1011, 0xb1, 0x29 }, // 2_J9.A1
  {  0x1011, 0xb1, 0x2a }, // 2_J9.A2
  {  0x1011, 0xb1, 0x2b }, // 2_J9.A3
  {  0x1011, 0xb1, 0x2c }, // 2_J9.A4
  {  0x1011, 0xb1, 0x2d }, // 2_J9.A5
  {  0x1011, 0xb1, 0x2e }, // 2_J9.A6
  {  0x1011, 0xb1, 0x2f }, // 2_J9.A7

  {  0x1011, 0xb1, 0x30 }, // 2_J10.A0
  {  0x1011, 0xb1, 0x31 }, // 2_J10.A1
  {  0x1011, 0xb1, 0x32 }, // 2_J10.A2
  {  0x1011, 0xb1, 0x33 }, // 2_J10.A3
  {  0x1011, 0xb1, 0x34 }, // 2_J10.A4
  {  0x1011, 0xb1, 0x35 }, // 2_J10.A5
  {  0x1011, 0xb1, 0x36 }, // 2_J10.A6
  {  0x1011, 0xb1, 0x37 }, // 2_J10.A7

  {  0x1011, 0xb1, 0x38 }, // 2_J11.A0
  {  0x1011, 0xb1, 0x39 }, // 2_J11.A1
  {  0x1011, 0xb1, 0x3a }, // 2_J11.A2
  {  0x1011, 0xb1, 0x3b }, // 2_J11.A3
  {  0x1011, 0xb1, 0x3c }, // 2_J11.A4
  {  0x1011, 0xb1, 0x3d }, // 2_J11.A5
  {  0x1011, 0xb1, 0x3e }, // 2_J11.A6
  {  0x1011, 0xb1, 0x3f }, // 2_J11.A7

  {  0x1011, 0xb1, 0x40 }, // 2_J12.A0
  {  0x1011, 0xb1, 0x41 }, // 2_J12.A1
  {  0x1011, 0xb1, 0x42 }, // 2_J12.A2
  {  0x1011, 0xb1, 0x43 }, // 2_J12.A3
  {  0x1011, 0xb1, 0x44 }, // 2_J12.A4
  {  0x1011, 0xb1, 0x45 }, // 2_J12.A5
  {  0x1011, 0xb1, 0x46 }, // 2_J12.A6
  {  0x1011, 0xb1, 0x47 }, // 2_J12.A7

  {  0x1011, 0xb1, 0x48 }, // 2_J13.A0
  {  0x1011, 0xb1, 0x49 }, // 2_J13.A1
  {  0x1011, 0xb1, 0x4a }, // 2_J13.A2
  {  0x1011, 0xb1, 0x4b }, // 2_J13.A3
  {  0x1011, 0xb1, 0x4c }, // 2_J13.A4
  {  0x1011, 0xb1, 0x4d }, // 2_J13.A5
  {  0x1011, 0xb1, 0x4e }, // 2_J13.A6
  {  0x1011, 0xb1, 0x4f }, // 2_J13.A7

};

midio_patch_matrix_entry_t midio_patch_matrix[MIDIO_PATCH_NUM_MATRIX] = {
  // ports  matrix mode                     chn arg    DINSR  DOUTSR
  { 0x1011, MIDIO_PATCH_MATRIX_MODE_COMMON,  1, 0x30,     0,     0 },
  { 0x1011, MIDIO_PATCH_MATRIX_MODE_COMMON,  1, 0x30,     0,     0 },
  { 0x1011, MIDIO_PATCH_MATRIX_MODE_COMMON,  1, 0x30,     0,     0 },
  { 0x1011, MIDIO_PATCH_MATRIX_MODE_COMMON,  1, 0x30,     0,     0 },
  { 0x1011, MIDIO_PATCH_MATRIX_MODE_COMMON,  1, 0x30,     0,     0 },
  { 0x1011, MIDIO_PATCH_MATRIX_MODE_COMMON,  1, 0x30,     0,     0 },
  { 0x1011, MIDIO_PATCH_MATRIX_MODE_COMMON,  1, 0x30,     0,     0 },
  { 0x1011, MIDIO_PATCH_MATRIX_MODE_COMMON,  1, 0x30,     0,     0 },
  { 0x1011, MIDIO_PATCH_MATRIX_MODE_COMMON,  1, 0x30,     0,     0 },
  { 0x1011, MIDIO_PATCH_MATRIX_MODE_COMMON,  1, 0x30,     0,     0 },
  { 0x1011, MIDIO_PATCH_MATRIX_MODE_COMMON,  1, 0x30,     0,     0 },
  { 0x1011, MIDIO_PATCH_MATRIX_MODE_COMMON,  1, 0x30,     0,     0 },
  { 0x1011, MIDIO_PATCH_MATRIX_MODE_COMMON,  1, 0x30,     0,     0 },
  { 0x1011, MIDIO_PATCH_MATRIX_MODE_COMMON,  1, 0x30,     0,     0 },
  { 0x1011, MIDIO_PATCH_MATRIX_MODE_COMMON,  1, 0x30,     0,     0 },
  { 0x1011, MIDIO_PATCH_MATRIX_MODE_COMMON,  1, 0x30,     0,     0 },

  // Note: map_chn and map_evnt1 are initialized in MIDIO_PATCH_Init()
};


midio_patch_cfg_t midio_patch_cfg = {
#if 0
  // TK: doesn't work, these values are initialized in PATCH_Init()
  .flags = { .MERGER_MODE = 0,
	     .ALT_PROGCHNG = 0,
	     .FORWARD_IO = 0,
	     .INVERSE_DIN = 0,
	     .INVERSE_DOUT = 0,
  },
#endif
  .debounce_ctr = 20,
  .ts_sensitivity = 3,
  .global_chn = 0,
  .all_notes_off_chn = 0,
  .convert_note_off_to_on0 = 1,
};


/////////////////////////////////////////////////////////////////////////////
// This function initializes the patch structure
/////////////////////////////////////////////////////////////////////////////
s32 MIDIO_PATCH_Init(u32 mode)
{
  if( mode != 0 )
    return -1; // only mode 0 supported

  // init remaining config values
  midio_patch_cfg.flags.ALL = 0;
  midio_patch_cfg.flags.FORWARD_IO = 1;
  midio_patch_cfg.flags.INVERSE_DIN = 1;

  int matrix;
  midio_patch_matrix_entry_t *m = (midio_patch_matrix_entry_t *)&midio_patch_matrix[0];
  for(matrix=0; matrix<MIDIO_PATCH_NUM_MATRIX; ++matrix, ++m) {
    int i;
    for(i=0; i<64; ++i) {
      m->map_chn[i] = 1;
      m->map_evnt1[i] = 0x30 + i;
    }
  }

  return 0; // no error
}


/////////////////////////////////////////////////////////////////////////////
// This function returns a byte from patch structure in RAM
/////////////////////////////////////////////////////////////////////////////
u8 MIDIO_PATCH_ReadByte(u16 addr)
{
  if( addr >= MIDIO_PATCH_SIZE )
    return 0;

  // Note: this patch structure only exists for compatibility reasons with MIDIO128 V2
  // Don't enhance it! Meanwhile the complete patch can only be edited via SD Card!
  if( addr < 0x100 ) {
    u8 dout = addr / 2;
    if( dout < MIDIO_PATCH_NUM_DOUT ) {
      switch( addr & 1 ) {
      case 0: return midio_patch_dout[dout].evnt0 & 0x7f;
      case 1: return midio_patch_dout[dout].evnt1 & 0x7f;
      }
    }
  } else if( addr < 0x400 ) {
    u8 din = (addr-0x100) / 6;
    if( din < MIDIO_PATCH_NUM_DIN ) {
      switch( (addr-0x100) % 6 ) {
      case 0: return midio_patch_din[din].evnt0_on & 0x7f;
      case 1: return midio_patch_din[din].evnt1_on & 0x7f;
      case 2: return midio_patch_din[din].evnt2_on & 0x7f;
      case 3: return midio_patch_din[din].evnt0_off & 0x7f;
      case 4: return midio_patch_din[din].evnt1_off & 0x7f;
      case 5: return midio_patch_din[din].evnt2_off & 0x7f;
      }
    }
  } else {
    if( addr >= 0x420 && addr < (0x420+(MIDIO_PATCH_NUM_DIN/2)) ) {
      u8 dinx2 = 2*(addr-0x420);
      u8 value = 0;
      value |= (midio_patch_din[dinx2+0].mode & 0x0f) << 0;
      value |= (midio_patch_din[dinx2+1].mode & 0x0f) << 4;
      return value;
    } else {
      switch( addr ) {
      case 0x400: return midio_patch_cfg.flags.MERGER_MODE;
      case 0x402: return midio_patch_cfg.debounce_ctr;
      case 0x404: return midio_patch_cfg.flags.ALT_PROGCHNG;
      case 0x406: return midio_patch_cfg.flags.FORWARD_IO;
      case 0x408: return midio_patch_cfg.flags.INVERSE_DIN;
      case 0x40a: return midio_patch_cfg.flags.INVERSE_DOUT;
      case 0x40c: return midio_patch_cfg.ts_sensitivity;
      case 0x40e: return midio_patch_cfg.global_chn;
      case 0x410: return midio_patch_cfg.all_notes_off_chn;
      }
    }
  }

  return 0x00;
}


/////////////////////////////////////////////////////////////////////////////
// This function writes a byte into patch structure in RAM
/////////////////////////////////////////////////////////////////////////////
s32 MIDIO_PATCH_WriteByte(u16 addr, u8 byte)
{
  if( addr >= MIDIO_PATCH_SIZE )
    return -1; // invalid address

  if( addr >= MIDIO_PATCH_SIZE )
    return 0;

  // Note: this patch structure only exists for compatibility reasons with MIDIO128 V2
  // Don't enhance it! Meanwhile the complete patch can only be edited via SD Card!
  if( addr < 0x100 ) {
    u8 dout = addr / 2;
    if( dout < MIDIO_PATCH_NUM_DOUT ) {
      switch( addr & 1 ) {
      case 0: midio_patch_dout[dout].evnt0 = byte & 0x7f; return 0;
      case 1: midio_patch_dout[dout].evnt1 = byte & 0x7f; return 0;
      }
    }
  } else if( addr < 0x400 ) {
    u8 din = (addr-0x100) / 6;
    if( din < MIDIO_PATCH_NUM_DIN ) {
      switch( (addr-0x100) % 6 ) {
      case 0: midio_patch_din[din].evnt0_on = byte & 0x7f; return 0;
      case 1: midio_patch_din[din].evnt1_on = byte & 0x7f; return 0;
      case 2: midio_patch_din[din].evnt2_on = byte & 0x7f; return 0;
      case 3: midio_patch_din[din].evnt0_off = byte & 0x7f; return 0;
      case 4: midio_patch_din[din].evnt1_off = byte & 0x7f; return 0;
      case 5: midio_patch_din[din].evnt2_off = byte & 0x7f; return 0;
      }
    }
  } else {
    if( addr >= 0x420 && addr < (0x420+(MIDIO_PATCH_NUM_DIN/2)) ) {
      u8 dinx2 = 2*(addr-0x420);
      midio_patch_din[dinx2+0].mode = (byte >> 0) & 0x0f;
      midio_patch_din[dinx2+1].mode = (byte >> 4) & 0x0f;
      return 0;
    } else {
      switch( addr ) {
      case 0x400: midio_patch_cfg.flags.MERGER_MODE = byte; return 0;
      case 0x402: midio_patch_cfg.debounce_ctr = byte; return 0;
      case 0x404: midio_patch_cfg.flags.ALT_PROGCHNG = byte; return 0;
      case 0x406: midio_patch_cfg.flags.FORWARD_IO = byte; return 0;
      case 0x408: midio_patch_cfg.flags.INVERSE_DIN = byte; return 0;
      case 0x40a: {
	u8 old_polarity = midio_patch_cfg.flags.INVERSE_DOUT;
	midio_patch_cfg.flags.INVERSE_DOUT = byte;
	u8 new_polarity = midio_patch_cfg.flags.INVERSE_DOUT;
	MIDIO_DOUT_UpdatePolarity(old_polarity, new_polarity);
	return 0;
      } break;
      case 0x40c: midio_patch_cfg.ts_sensitivity = byte; return 0;
      case 0x40e: midio_patch_cfg.global_chn = byte; return 0;
      case 0x410: midio_patch_cfg.all_notes_off_chn = byte; return 0;
      }
    }
  }

  return -2; // value not mapped
}


/////////////////////////////////////////////////////////////////////////////
// This function loads the patch from SD Card
// Returns != 0 if Load failed
/////////////////////////////////////////////////////////////////////////////
s32 MIDIO_PATCH_Load(char *filename)
{
  MUTEX_SDCARD_TAKE;
  s32 status = MIDIO_FILE_P_Read(filename);
  MUTEX_SDCARD_GIVE;

  return status;
}


/////////////////////////////////////////////////////////////////////////////
// This function stores the patch on SD Card
// Returns != 0 if Store failed
/////////////////////////////////////////////////////////////////////////////
s32 MIDIO_PATCH_Store(char *filename)
{
  MUTEX_SDCARD_TAKE;
  s32 status = MIDIO_FILE_P_Write(filename);
  MUTEX_SDCARD_GIVE;

  return status;
}
