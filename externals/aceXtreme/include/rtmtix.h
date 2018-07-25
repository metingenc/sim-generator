#ifndef __RTMTIX_H__
#define __RTMTIX_H__

/* ========================================================================== */
/*                                DATA TYPES                                  */
/* ========================================================================== */

/* ========================================================================== */
/*                            ACEX FUNCTION PROTOTYPES                             */
/* ========================================================================== */
_EXTERN S16BIT _DECL _acexRTMTIConfigure(S16BIT DevNum, U16BIT wRTCmdStkSize, U32BIT u32DevBufByteSize, U32BIT u32NumBufBlks,
                                            U32BIT u32BufBlkByteSize, BOOLEAN fZeroCopyEnable, U32BIT u32IrqDataLen, U32BIT u32IrqMsgCnt,
                                            U16BIT u16IrqTimeInterval, U32BIT u32IntConditions, U16BIT u16Ch10ChnlId, U8BIT u8HdrVer,
                                            U8BIT u8RelAbsTime, U8BIT u8Ch10Checksum, U32BIT dwOptions);
_EXTERN S16BIT _DECL _acexRTMTIStart(S16BIT DevNum);
_EXTERN S16BIT _DECL _acexRTMTIStop(S16BIT DevNum);

#endif


