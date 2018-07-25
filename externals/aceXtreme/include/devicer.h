#ifndef __DEVICE_R_H__
#define __DEVICE_R_H__

#include "ddccommon.h"

#define DDC_REG_KEY_SIZE 128

S16BIT DDCSockConnectToServer(char * pServerAddr, SOCKET * pClientConnSock);
S16BIT DDCSockDisconnect(SOCKET * pClientConnSock);
void DDCPrepareMsgDispatcher(S16BIT DevNum);
void DDCReleaseMsgDispatcher(S16BIT DevNum);
S16BIT DDCClientSendAndRecv(S16BIT s16DevNum, S32BIT s32TimeOut, PDDC_SOCK_MSG_STRUCT pReqMsg, PDDC_SOCK_MSG_STRUCT pRespMsg);
S16BIT DDCClientRemoteApiCall(S16BIT DevNum, U32BIT u32MsgCmd,
                              U16BIT u16ReqParamCount, DDC_SOCK_DATA_TYPE* psReqParam,
                              U16BIT u16RespInfoCount, DDC_SOCK_DATA_TYPE* psRespInfo,
                              S32BIT s32TimeOut);
S16BIT DDCClientRemoteApiCallOne(U32BIT u32MsgCmd, S16BIT DevNum);
S16BIT DDCClientRemoteApiCallTwo(U32BIT u32MsgCmd, S16BIT DevNum, U16BIT Param2);
S16BIT DDCClientRemoteApiCallTwoS8(U32BIT u32MsgCmd, S16BIT DevNum, S8BIT Param2);
S16BIT DDCClientRemoteApiCallTwoS16(U32BIT u32MsgCmd, S16BIT DevNum, S16BIT Param2);
S16BIT DDCClientRemoteApiCallTwoU32(U32BIT u32MsgCmd, S16BIT DevNum, U32BIT Param2);
U16BIT DDCClientRemoteApiCallTwoU16Ret(U32BIT u32MsgCmd, S16BIT DevNum, U16BIT Param2);
U32BIT DDCClientRemoteApiCallTwoU32Ret(U32BIT u32MsgCmd, S16BIT DevNum, U16BIT Param2);
U32BIT DDCClientRemoteApiCallTwoU32All(U32BIT u32MsgCmd, S16BIT DevNum, U32BIT Param2);
S16BIT DDCClientRemoteApiCallTwoGet(U32BIT u32MsgCmd, S16BIT DevNum, U16BIT *Param2);
S16BIT DDCClientRemoteApiCallTwoU32Get(U32BIT u32MsgCmd, S16BIT DevNum, U32BIT *Param2);
S16BIT DDCClientRemoteApiCallTwoTestGet(U32BIT u32MsgCmd, S16BIT DevNum, TESTRESULT *pTest);
S16BIT DDCClientRemoteApiCallThree(U32BIT u32MsgCmd, S16BIT DevNum, U16BIT Param2, U16BIT Param3);
S16BIT DDCClientRemoteApiCallThreeS8(U32BIT u32MsgCmd, S16BIT DevNum, S8BIT Param2, U16BIT Param3);
S16BIT DDCClientRemoteApiCallThreeS16(U32BIT u32MsgCmd, S16BIT DevNum, S16BIT Param2, U16BIT Param3);
S16BIT DDCClientRemoteApiCallThreeU32(U32BIT u32MsgCmd, S16BIT DevNum, U16BIT Param2, U32BIT Param3);
S16BIT DDCClientRemoteApiCallThreeS8U32(U32BIT u32MsgCmd, S16BIT DevNum, S8BIT Param2, U32BIT Param3);
S16BIT DDCClientRemoteApiCallThreeS16U32(U32BIT u32MsgCmd, S16BIT DevNum, S16BIT Param2, U32BIT Param3);

S16BIT DDCSockSetupIrqListener(S16BIT DevNum);
S16BIT DDCSockCloseIrqListener(S16BIT DevNum);
#endif
