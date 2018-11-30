#ifndef __ACE_H__
#define __ACE_H__

/* ========================================================================== */
/*                        FUNCTION POINTER PROTOTYPES                         */
/* ========================================================================== */
typedef struct _API_ACE_FUNCTIONS
{
    S16BIT (_DECL *aceBCOpCodeCreateEx) (S16BIT DevNum, S16BIT nOpCodeID, U16BIT wOpCodeType, U16BIT wCondition, U32BIT dwParameter1, U32BIT dwParameter2, U32BIT dwReserved);
    S16BIT (_DECL *aceBCOpCodeDeleteEx) (S16BIT DevNum, S16BIT nOpCodeID);
    S16BIT (_DECL *aceBCFrameCreateEx) (S16BIT DevNum, S16BIT nFrameID, U16BIT wFrameType, S16BIT aOpCodeIDs[], U16BIT wOpCodeCount, U16BIT wMnrFrmTime, U16BIT wFlags);
    S16BIT (_DECL *aceBCFrameDeleteEx) (S16BIT DevNum, S16BIT nFrameID);
    U16BIT (_DECL *aceMemReadEx) (S16BIT DevNum, U16BIT wMemAddr);
    U32BIT (_DECL *aceMemRead32Ex) ( S16BIT DevNum, U16BIT wMemAddr );
    S16BIT (_DECL *aceMemWriteEx) (S16BIT DevNum, U16BIT wMemAddr, U16BIT wValue);
    S16BIT (_DECL *aceMTGetActiveStk) (S16BIT DevNum);
    S16BIT (_DECL *aceMTSetActiveStk) (S16BIT DevNum, U16BIT StkLoc);
    S16BIT (_DECL *aceRTDataBlkGetAddr) (S16BIT DevNum, S16BIT nDataBlkID, U16BIT wSA, U16BIT wBlkType, U16BIT wMsgType);
    S16BIT (_DECL *aceRTDataBlkSetCircBufOffsets) (S16BIT DevNum, S16BIT nDataBlkID, U16BIT Offset);
    S16BIT (_DECL *aceRTDataBlkCreateEx) (S16BIT DevNum, S16BIT nDataBlkID, U16BIT wDataBlkType, U16BIT *pBuffer, U16BIT wBufferSize);
    S16BIT (_DECL *aceRTDataBlkDeleteEx) (S16BIT DevNum, S16BIT nDataBlkID);
    S16BIT (_DECL *aceRTBrdcst) (S16BIT DevNum, U16BIT Value);
    S16BIT (_DECL *aceRTIllegal) (S16BIT DevNum, U16BIT Value);
    S16BIT (_DECL *aceRTAltStatusEna) (S16BIT DevNum, U16BIT Value);
    S16BIT (_DECL *aceSetIrqConditionsEx) (S16BIT DevNum, U16BIT bEnable, U32BIT dwIrqMask, void(_DECL *funcExternalIsr)(S16BIT DevNum, U32BIT dwIrqStatus));
    S16BIT (_DECL *acexSetValidBusyBitNoData)(S16BIT DevNum, U16BIT wValue);
} API_ACE_FUNCTIONS;

_EXTERN S16BIT _DECL aceBCOpCodeCreateEx(S16BIT DevNum,
                                         S16BIT nOpCodeID,
                                         U16BIT wOpCodeType,
                                         U16BIT wCondition,
                                         U32BIT dwParameter1,
                                         U32BIT dwParameter2,
                                         U32BIT dwReserved);

_EXTERN S16BIT _DECL aceBCOpCodeDeleteEx(S16BIT DevNum,
                                         S16BIT nOpCodeID);

_EXTERN S16BIT _DECL aceBCFrameCreateEx(S16BIT DevNum,
                                        S16BIT nFrameID,
                                        U16BIT wFrameType,
                                        S16BIT aOpCodeIDs[],
                                        U16BIT wOpCodeCount,
                                        U16BIT wMnrFrmTime,
                                        U16BIT wFlags);

_EXTERN S16BIT _DECL aceBCFrameDeleteEx(S16BIT DevNum,
                                        S16BIT nFrameID);

_EXTERN U16BIT _DECL aceMemReadEx(S16BIT DevNum,U16BIT wMemAddr);

_EXTERN U32BIT _DECL aceMemRead32Ex( S16BIT DevNum,U16BIT wMemAddr );

_EXTERN S16BIT _DECL aceMemWriteEx(S16BIT DevNum, U16BIT wMemAddr, U16BIT wValue);

_EXTERN S16BIT _DECL aceMTGetActiveStk( S16BIT DevNum );

_EXTERN S16BIT _DECL aceMTSetActiveStk( S16BIT DevNum, U16BIT StkLoc );

_EXTERN S16BIT _DECL aceRTDataBlkGetAddr(S16BIT DevNum,
                                         S16BIT nDataBlkID,
                                         U16BIT wSA,
                                         U16BIT wBlkType,
                                         U16BIT wMsgType);

_EXTERN S16BIT _DECL aceRTDataBlkSetCircBufOffsets(S16BIT DevNum,
                                                   S16BIT nDataBlkID,
                                                   U16BIT Offset);

_EXTERN S16BIT _DECL aceRTDataBlkCreateEx(S16BIT DevNum,
                                          S16BIT nDataBlkID,
                                          U16BIT wDataBlkType,
                                          U16BIT *pBuffer,
                                          U16BIT wBufferSize);

_EXTERN S16BIT _DECL aceRTDataBlkDeleteEx(S16BIT DevNum,
                                          S16BIT nDataBlkID);

_EXTERN S16BIT _DECL aceRTBrdcst( S16BIT DevNum, U16BIT Value );

_EXTERN S16BIT _DECL aceRTIllegal( S16BIT DevNum, U16BIT Value );

_EXTERN S16BIT _DECL aceRTAltStatusEna( S16BIT DevNum, U16BIT Value );

_EXTERN S16BIT _DECL aceSetIrqConditionsEx(S16BIT DevNum,
                                           U16BIT bEnable,
                                           U32BIT dwIrqMask,
                                           void(_DECL *funcExternalIsr)(S16BIT DevNum, U32BIT dwIrqStatus));

_EXTERN S16BIT _DECL acexSetValidBusyBitNoData( S16BIT DevNum,
                                                U16BIT wValue);
#endif
