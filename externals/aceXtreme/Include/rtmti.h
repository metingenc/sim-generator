#ifndef __RTMTI_H__
#define __RTMTI_H__

/* ========================================================================== */
/*                        FUNCTION POINTER PROTOTYPES                         */
/* ========================================================================== */
typedef struct _API_RTMTI_FUNCTIONS
{
    S16BIT (_DECL *aceRTMTIConfigure)       (S16BIT DevNum, U16BIT wRTCmdStkSize, U32BIT u32DevBufByteSize, U32BIT u32NumBufBlks,
                                                U32BIT u32BufBlkByteSize, BOOLEAN fZeroCopyEnable, U32BIT u32IrqDataLen, U32BIT u32IrqMsgCnt,
                                                U16BIT u16IrqTimeInterval, U32BIT u32IntConditions, U16BIT u16Ch10ChnlId, U8BIT u8HdrVer,
                                                U8BIT u8RelAbsTime, U8BIT u8Ch10Checksum, U32BIT dwOptions);
    S16BIT (_DECL *aceRTMTIStart)           (S16BIT DevNum);
    S16BIT (_DECL *aceRTMTIStop)            (S16BIT DevNum);
} API_RTMTI_FUNCTIONS;

/* ========================================================================== */
/*                        EXTERNAL FUNCTION PROTOTYPES                        */
/* ========================================================================== */
_EXTERN S16BIT _DECL aceRTMTIConfigure(S16BIT DevNum, U16BIT wRTCmdStkSize, U32BIT u32DevBufByteSize, U32BIT u32NumBufBlks,
                                            U32BIT u32BufBlkByteSize, BOOLEAN fZeroCopyEnable, U32BIT u32IrqDataLen, U32BIT u32IrqMsgCnt,
                                            U16BIT u16IrqTimeInterval, U32BIT u32IntConditions, U16BIT u16Ch10ChnlId, U8BIT u8HdrVer,
                                            U8BIT u8RelAbsTime, U8BIT u8Ch10Checksum, U32BIT dwOptions);
_EXTERN S16BIT _DECL aceRTMTIStart(S16BIT DevNum);
_EXTERN S16BIT _DECL aceRTMTIStop(S16BIT DevNum);

#endif
