//
//  MIOS32_DELAY_Wrapper.m
//
//  Created by Thorsten Klose on 15.12.08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "MIOS32_DELAY_Wrapper.h"

#include <mios32.h>

@implementation MIOS32_DELAY_Wrapper

// local variables to bridge objects to C functions
static NSObject *_self;


//////////////////////////////////////////////////////////////////////////////
// init local variables
//////////////////////////////////////////////////////////////////////////////
- (void) awakeFromNib
{
	_self = self;
}


//////////////////////////////////////////////////////////////////////////////
// stubs for MIOS32 delay functions
//////////////////////////////////////////////////////////////////////////////

s32 MIOS32_DELAY_Init(u32 mode)
{
	return 0; // no error
}

/////////////////////////////////////////////////////////////////////////////
// Waits for a specific number of uS
// IN: delay in uS (1..65535)
// OUT: < 0 on errors
// EXAMPLE:
//
//   // wait for 500 uS
//   MIOS32_DELAY_Wait_uS(500);
//
/////////////////////////////////////////////////////////////////////////////
s32 MIOS32_DELAY_Wait_uS(u16 uS)
{
	[NSThread sleepForTimeInterval:((float)uS/1E6)];
	return 0; // no error
}


@end
