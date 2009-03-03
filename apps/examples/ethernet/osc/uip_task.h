// $Id$
/*
 * Header file for uIP Task
 *
 * ==========================================================================
 *
 *  Copyright (C) 2008 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

#ifndef _UIP_TASK_H
#define _UIP_TASK_H


/////////////////////////////////////////////////////////////////////////////
// Global definitions
/////////////////////////////////////////////////////////////////////////////

#include <FreeRTOS.h>
#include <semphr.h>

extern xSemaphoreHandle xUIPSemaphore;
# define MUTEX_UIP_TAKE { while( xSemaphoreTake(xUIPSemaphore, (portTickType)1) != pdTRUE ); }
# define MUTEX_UIP_GIVE { xSemaphoreGive(xUIPSemaphore); }


/////////////////////////////////////////////////////////////////////////////
// Global Types
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Prototypes
/////////////////////////////////////////////////////////////////////////////

extern s32 UIP_TASK_Init(u32 mode);


/////////////////////////////////////////////////////////////////////////////
// Export global variables
/////////////////////////////////////////////////////////////////////////////


#endif /* _UIP_TASK_H */
