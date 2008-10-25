// $Id$
/*
 * COM layer functions for MIOS32
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

// this module can be optionally disabled in a local mios32_config.h file (included from mios32.h)
#if !defined(MIOS32_DONT_USE_COM)


/////////////////////////////////////////////////////////////////////////////
// Global variables
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Local variables
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Initializes COM layer
// IN: <mode>: 0: MIOS32_COM_Send works in blocking mode - function will
//                (shortly) stall if the output buffer is full
//             1: MIOS32_COM_Send works in non-blocking mode - function will
//                return -2 if buffer is full, the caller has to loop if this
//                value is returned until the transfer was successful
//                A common method is to release the RTOS task for 1 mS
//                so that other tasks can be executed until the sender can
//                continue
// OUT: returns < 0 if initialisation failed
/////////////////////////////////////////////////////////////////////////////
s32 MIOS32_COM_Init(u32 mode)
{
  s32 ret = 0;

  // currently only mode 0 and 1 (blocking/non-blocking) supported
  if( mode != 0 && mode != 1 )
    return -1; // unsupported mode

#if !defined(MIOS32_DONT_USE_USB_COM)
  if( MIOS32_USB_COM_Init(mode) < 0 )
    ret |= (1 << 0);
#endif

  return -ret;
}


/////////////////////////////////////////////////////////////////////////////
// This function checks the availability of a COM port
// IN: <port>: COM port 
//             DEFAULT, USB0..USB7, UART0..UART1, IIC0..IIC7
// OUT: 1: port available
//      0: port not available
/////////////////////////////////////////////////////////////////////////////
s32 MIOS32_COM_CheckAvailable(mios32_com_port_t port)
{
  // if default port: select mapped port
  if( !(port & 0xf0) ) {
    port = MIOS32_COM_DEFAULT_PORT;
  }

  // branch depending on selected port
  switch( port >> 4 ) {
    case 1:
#if !defined(MIOS32_DONT_USE_USB) && !defined(MIOS32_DONT_USE_USB_COM)
      return MIOS32_USB_COM_CheckAvailable();
#else
      return 0; // USB has been disabled
#endif

    case 2:
      return 0; // UART COM not implemented yet (but should be easy)
      
    case 3:
      return 0; // IIC COM not implemented yet (but should be easy)

    case 4:
      return 0; // Ethernet not implemented yet
      
    default:
      // invalid port
      return 0;
  }
}


/////////////////////////////////////////////////////////////////////////////
// Sends a package over given port
// IN: <port>: COM port 
//             DEFAULT, USB0..USB7, UART0..UART1, IIC0..IIC7
//     <buffer>: character buffer
//     <len>:    buffer length
// OUT: returns -1 if port not available
//      returns -2 if non-blocking mode activated: buffer is full
//                 caller should retry until buffer is free again
//      returns 0 on success
/////////////////////////////////////////////////////////////////////////////
s32 MIOS32_COM_SendBuffer(mios32_com_port_t port, u8 *buffer, u16 len)
{
  // if default port: select mapped port
  if( !(port & 0xf0) ) {
    port = MIOS32_COM_DEFAULT_PORT;
  }

  // branch depending on selected port
  switch( port >> 4 ) {
    case 1:
#if !defined(MIOS32_DONT_USE_USB) && !defined(MIOS32_DONT_USE_USB_COM)
      return MIOS32_USB_COM_TxBufferPutMore(port & 0xf, buffer, len);
#else
      return -1; // USB has been disabled
#endif

    case 2:
      return -1; // not implemented yet

    case 3:
      return -1; // not implemented yet

    case 4:
      return -1; // Ethernet not implemented yet
      
    default:
      // invalid port
      return -1;
  }
}



/////////////////////////////////////////////////////////////////////////////
// Checks for incoming COM messages, calls the callback function with
// following parameters:
//    callback_event(mios32_com_port_t port, u8 byte)
// OUT: returns < 0 on errors
/////////////////////////////////////////////////////////////////////////////
s32 MIOS32_COM_Receive_Handler(void *_callback)
{
  u8 port;

  void (*callback)(mios32_com_port_t port, u8 byte) = _callback;

  u8 intf = 0; // interface to be checked
  u8 total_bytes_forwarded = 0; // number of forwards - stop after 10 forwards to yield some CPU time for other tasks
  u8 bytes_forwarded = 0;
  u8 again = 1;
  do {
    // Round Robin
    // TODO: maybe a list based approach would be better
    // it would allow to add/remove interfaces dynamically
    // this would also allow to give certain ports a higher priority (to add them multiple times to the list)
    // it would also improve this spagetthi code ;)
    s32 error = -1;
    switch( intf++ ) {
#if !defined(MIOS32_DONT_USE_USB) && !defined(MIOS32_DONT_USE_USB_COM)
      case 0: error = MIOS32_USB_COM_RxBufferGet(0); port = 0; break;
#else
      case 0: error = -1; break;
#endif
      default:
	// allow 64 forwards maximum to yield some CPU time for other tasks
	if( bytes_forwarded && total_bytes_forwarded < 64 ) {
	  intf = 0; // restart with USB
	  bytes_forwarded = 0; // for checking, if bytes still have been forwarded in next round
	} else {
	  again = 0; // no more interfaces to be processed
	}
	error = -1; // empty round - no message
    }

    // message received?
    if( error >= 0 ) {
      // notify that a package has been forwarded
      ++bytes_forwarded;
      ++total_bytes_forwarded;

      // call function
      callback(port, (u8)error);
    }
  } while( again );

  return 0;
}


#endif /* MIOS32_DONT_USE_COM */