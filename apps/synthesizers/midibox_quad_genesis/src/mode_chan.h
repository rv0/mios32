/*
 * MIDIbox Quad Genesis: Channel Mode header
 *
 * ==========================================================================
 *
 *  Copyright (C) 2016 Sauraen (sauraen@gmail.com)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

#ifndef _MODE_CHAN_H
#define _MODE_CHAN_H

#ifdef __cplusplus
extern "C" {
#endif


extern void Mode_Chan_Init();
extern void Mode_Chan_GotFocus();

extern void Mode_Chan_Tick();
extern void Mode_Chan_Background();

extern void Mode_Chan_BtnGVoice(u8 gvoice, u8 state);
extern void Mode_Chan_BtnSoftkey(u8 softkey, u8 state);
extern void Mode_Chan_BtnSelOp(u8 op, u8 state);
extern void Mode_Chan_BtnOpMute(u8 op, u8 state);
extern void Mode_Chan_BtnSystem(u8 button, u8 state);
extern void Mode_Chan_BtnEdit(u8 button, u8 state);

extern void Mode_Chan_EncDatawheel(s32 incrementer);
extern void Mode_Chan_EncEdit(u8 encoder, s32 incrementer);


#ifdef __cplusplus
}
#endif


#endif /* _MODE_CHAN_H */
