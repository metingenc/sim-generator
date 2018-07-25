#ifndef __MT_H__
#define __MT_H__

/* ========================================================================== */
/*                        FUNCTION POINTER PROTOTYPES                         */
/* ========================================================================== */
typedef struct _API_MT_FUNCTIONS
{
    S16BIT (_DECL *aceMTConfigure)        (S16BIT DevNum, U16BIT wMTStkType, U16BIT wCmdStkSize, U16BIT wDataStkSize,
                                           U32BIT dwOptions);
    S16BIT (_DECL *aceMTInstallHBuf)      (S16BIT DevNum, U32BIT dwHBufSize);
    S16BIT (_DECL *aceMTUninstallHBuf)    (S16BIT DevNum);
    S16BIT (_DECL *aceMTSetHBufTrigger)   (S16BIT DevNum, U16BIT wHBufPercent, MTTRIGGER *pTrg);
    S16BIT (_DECL *aceMTClearHBufTrigger) (S16BIT DevNum);
    S16BIT (_DECL *aceMTSwapStks)         (S16BIT DevNum);
    S16BIT (_DECL *aceMTGetHBufMsgCount)  (S16BIT DevNum);
    S16BIT (_DECL *aceMTGetHBufMsgsRaw)   (S16BIT DevNum, U16BIT *pBuffer, U16BIT wBufferSize, U32BIT *pdwMsgCount,
                                           U32BIT *pdwMsgLostStk,U32BIT *pdwMsgLostHBuf);
    S16BIT (_DECL *aceMTGetHBufMsgDecoded)(S16BIT DevNum, MSGSTRUCT *pMsg, U32BIT *pdwMsgCount, U32BIT *pdwMsgLostStk,
                                           U32BIT *pdwMsgLostHBuf, U16BIT wMsgLoc);
    S16BIT (_DECL *aceMTStkToHBuf)        (S16BIT DevNum);
    S16BIT (_DECL *aceMTStkToHBuf32)      (S16BIT DevNum);
    S16BIT (_DECL *aceMTGetInfo)          (S16BIT DevNum,MTINFO *pInfo);
    S16BIT (_DECL *aceMTStart)            (S16BIT DevNum);
    S16BIT (_DECL *aceMTStop)             (S16BIT DevNum);
    S16BIT (_DECL *aceMTPause)            (S16BIT DevNum);
    S16BIT (_DECL *aceMTContinue)         (S16BIT DevNum);
    S16BIT (_DECL *aceMTEnableRTFilter)   (S16BIT DevNum, U16BIT wRT, U16BIT wTR, U32BIT dwSAMask);
    S16BIT (_DECL *aceMTDisableRTFilter)  (S16BIT DevNum, U16BIT wRT, U16BIT wTR, U32BIT dwSAMask);
    S16BIT (_DECL *aceMTGetRTFilter)      (S16BIT DevNum, U16BIT wRT, U16BIT wTR, U32BIT *pSAMask);
    S16BIT (_DECL *aceMTDecodeRawMsg)     (S16BIT DevNum, U16BIT *pBuffer, MSGSTRUCT *pMsg);
    S16BIT (_DECL *aceMTGetStkMsgsRaw)    (S16BIT DevNum, U16BIT *pBuffer, U16BIT wBufferSize, U16BIT wStkLoc);
    S16BIT (_DECL *aceMTGetStkMsgDecoded) (S16BIT DevNum, MSGSTRUCT *pMsg, U16BIT wMsgLoc, U16BIT wStkLoc);
    S16BIT (_DECL *aceMTCreateImageFiles) (S16BIT DevNum, char *pszIFile, char *pszHFile);
    S16BIT (_DECL *aceMTGetHBufMetric)    (S16BIT DevNum, HBUFMETRIC *pMetric, U16BIT bReset);
    S16BIT (_DECL *aceMTGetStkMetric)     (S16BIT DevNum, STKMETRIC *pMetric, U16BIT wStk, U16BIT bReset);

    S16BIT (_DECL *aceMTICh10FileOpen)   ( PMTI_CH10_FILE_HANDLE   *pCh10FileHandle,
                                            const CHAR              *pFilename,
                                            U8BIT                   u8FileAccessMode,
                                            CHAR                    *pFileHeader,
                                            U32BIT                  u32FileHeaderLen);

    S16BIT (_DECL *aceMTICh10FileClose)  ( PMTI_CH10_FILE_HANDLE   *pCh10FileHandle);

    S16BIT (_DECL *aceMTICh10FileRead)   ( PMTI_CH10_FILE_HANDLE   pCh10FileHandle,
                                            U8BIT                   u8PacketReadType,
                                            PMTI_CH10_DATA_PKT      pMtiCh10Header,
                                            VOID                    *pDataPacket,
                                            U32BIT                  u32DataPacketLen);

    S16BIT (_DECL *aceMTICh10FileReadRaw)( PMTI_CH10_FILE_HANDLE   pCh10FileHandle,
                                            U8BIT                   u8PacketReadType,
                                            PMTI_CH10_DATA_PKT      pMtiCh10Header,
                                            VOID                    *pDataPacket,
                                            U32BIT                  u32DataPacketLen);

    S16BIT (_DECL *aceMTICh10FileGetOffset) (  PMTI_CH10_FILE_HANDLE   pCh10FileHandle,
                                                S64BIT                  *pOffset);

    S16BIT (_DECL *aceMTICh10FileSetOffset)(   PMTI_CH10_FILE_HANDLE   pCh10FileHandle,
                                                S64BIT                  s64Offset);

    S16BIT (_DECL *aceMTICh10FileWrite)  ( PMTI_CH10_FILE_HANDLE   pCh10FileHandle,
                                            VOID                    *pPacket,
                                            U32BIT                  u32PktLength);

} API_MT_FUNCTIONS;

/* ========================================================================== */
/*                            FUNCTION PROTOTYPES                             */
/* ========================================================================== */

_EXTERN S16BIT _DECL aceMTConfigure
(
    S16BIT DevNum,
    U16BIT wMTStkType,
    U16BIT wCmdStkSize,
    U16BIT wDataStkSize,
    U32BIT dwOptions
);

_EXTERN S16BIT _DECL aceMTInstallHBuf(S16BIT DevNum, U32BIT dwHBufSize);

_EXTERN S16BIT _DECL aceMTUninstallHBuf(S16BIT DevNum);

_EXTERN S16BIT _DECL aceMTSetHBufTrigger(S16BIT DevNum,
                                         U16BIT wHBufPercent,
                                         MTTRIGGER *pTrg);

_EXTERN S16BIT _DECL aceMTClearHBufTrigger(S16BIT DevNum);

_EXTERN S16BIT _DECL aceMTSwapStks(S16BIT DevNum);

_EXTERN S16BIT _DECL aceMTGetHBufMsgCount(S16BIT DevNum);

_EXTERN S16BIT _DECL aceMTGetHBufMsgsRaw(S16BIT DevNum,
                                         U16BIT *pBuffer,
                                         U16BIT wBufferSize,
                                         U32BIT *pdwMsgCount,
                                         U32BIT *pdwMsgLostStk,
                                         U32BIT *pdwMsgLostHBuf);

_EXTERN S16BIT _DECL aceMTGetHBufMsgDecoded(S16BIT DevNum,
                                            MSGSTRUCT *pMsg,
                                            U32BIT *pdwMsgCount,
                                            U32BIT *pdwMsgLostStk,
                                            U32BIT *pdwMsgLostHBuf,
                                            U16BIT wMsgLoc);

_EXTERN S16BIT _DECL aceMTStkToHBuf(S16BIT DevNum);

_EXTERN S16BIT _DECL aceMTStkToHBuf32(S16BIT DevNum);

_EXTERN S16BIT _DECL aceMTGetInfo(S16BIT DevNum, MTINFO *pInfo);

_EXTERN S16BIT _DECL aceMTStart(S16BIT DevNum);

_EXTERN S16BIT _DECL aceMTStop(S16BIT DevNum);

_EXTERN S16BIT _DECL aceMTPause(S16BIT DevNum);

_EXTERN S16BIT _DECL aceMTContinue(S16BIT DevNum);

_EXTERN S16BIT _DECL aceMTEnableRTFilter(S16BIT DevNum,
                                         U16BIT wRT,
                                         U16BIT wTR,
                                         U32BIT dwSAMask);

_EXTERN S16BIT _DECL aceMTDisableRTFilter(S16BIT DevNum,
                                          U16BIT wRT,
                                          U16BIT wTR,
                                          U32BIT dwSAMask);

_EXTERN S16BIT _DECL aceMTGetRTFilter(S16BIT DevNum,
                                      U16BIT wRT,
                                      U16BIT wTR,
                                      U32BIT *pSAMask);

_EXTERN S16BIT _DECL aceMTDecodeRawMsg(S16BIT DevNum, U16BIT *pBuffer,
                                       MSGSTRUCT *pMsg);

_EXTERN S16BIT _DECL aceMTGetStkMsgsRaw(S16BIT DevNum,
                                        U16BIT *pBuffer,
                                        U16BIT wBufferSize,
                                        U16BIT wStkLoc);

_EXTERN S16BIT _DECL aceMTGetStkMsgDecoded(S16BIT DevNum,
                                           MSGSTRUCT *pMsg,
                                           U16BIT wMsgLoc,
                                           U16BIT wStkLoc);

_EXTERN S16BIT _DECL aceMTCreateImageFiles(S16BIT DevNum,
                                           char *pszIFile,
                                           char *pszHFile);

_EXTERN S16BIT _DECL aceMTGetHBufMetric( S16BIT DevNum,
                                         HBUFMETRIC *pMetric,
                                         U16BIT bReset);

_EXTERN S16BIT _DECL aceMTGetStkMetric( S16BIT DevNum,
                                        STKMETRIC *pMetric,
                                        U16BIT wStk,
                                        U16BIT bReset);

_EXTERN S16BIT _DECL aceMTICh10FileOpen
(
    PMTI_CH10_FILE_HANDLE   *pCh10FileHandle,
    const CHAR              *pFilename,
    U8BIT                   u8FileAccessMode,
    CHAR                    *pFileHeader,
    U32BIT                  u32FileHeaderLen
);

_EXTERN S16BIT _DECL aceMTICh10FileClose
(
    PMTI_CH10_FILE_HANDLE   *pCh10FileHandle
);

_EXTERN S16BIT _DECL aceMTICh10FileRead
(
    PMTI_CH10_FILE_HANDLE   pCh10FileHandle,
    U8BIT                   u8PacketReadType,
    PMTI_CH10_DATA_PKT      pMtiCh10Header,
    VOID                    *pDataPacket,
    U32BIT                  u32DataPacketLen
);

_EXTERN S16BIT _DECL aceMTICh10FileReadRaw
(
    PMTI_CH10_FILE_HANDLE   pCh10FileHandle,
    U8BIT                   u8PacketReadType,
    PMTI_CH10_DATA_PKT      pMtiCh10Header,
    VOID                    *pDataPacket,
    U32BIT                  u32DataPacketLen
);

_EXTERN S16BIT _DECL aceMTICh10FileGetOffset
(
    PMTI_CH10_FILE_HANDLE   pCh10FileHandle,
    S64BIT                  *pOffset
);

_EXTERN S16BIT _DECL aceMTICh10FileSetOffset
(
    PMTI_CH10_FILE_HANDLE   pCh10FileHandle,
    S64BIT                  s64Offset
);

_EXTERN S16BIT _DECL aceMTICh10FileWrite
(
    PMTI_CH10_FILE_HANDLE   pCh10FileHandle,
    VOID                    *pPacket,
    U32BIT                  u32PktLength
);

#endif
