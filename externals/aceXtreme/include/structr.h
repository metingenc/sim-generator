#ifndef __STRUCT_R_H__
#define __STRUCT_R_H__

#define DDC_REMOTE_DEVICES_MAX_NUM 32

#define DDC_CLIENT_REQ_THREAD_MAX_NUM 10

typedef struct _DDC_CLIENT_REQ_INFO
{
    BOOL   bWaiting;               /* TRUE - the thread is waiting for the response msg */
    U32BIT u32ExpectCmd;           /* The expected msg cmd the thread is waiting for */
    U8BIT * pRespMsg;              /* pointer to the location where the thread needs to store the response msg */

    DDC_HANDLE hClntReqWaitEvent;  /* the event handler the thread is waiting for,
                                    it is created at the very first begining, each
                                    thread don't need to create, juse use it*/
}DDC_CLIENT_REQ_INFO, *PDDC_CLIENT_REQ_INFO;

typedef struct _DDC_RT_DATA_ARRAY_INFO
{
    U32 u32BufWdSize;  /* store the buffer size information (in words) for current data array in remoteAcexMRTDataArrayCreate()
                          and used later in remoteAcexMRTDataArraySend() */
}DDC_RT_DATA_ARRAY_INFO, *PDDC_RT_DATA_ARRAY_INFO;

typedef struct _DDC_RT_INFO
{
    DDC_RT_DATA_ARRAY_INFO asDataArrayInfo[4];
}DDC_RT_INFO, *PDDC_RT_INFO;

typedef struct _DDC_REMOTE_DEVICE_INFO
{
    char            aRemoteAddr[20];
    S16BIT          s16RemoteDevNum;
    S32BIT          s32RemoteOsType;    /* Informs server type of OS Remote is running on */

    DDC_MUTEX       hClientReqInfoMutex;
    int             nClntSockInfoMutexUseCount;
    DDC_CLIENT_REQ_INFO clntReqInfo[DDC_CLIENT_REQ_THREAD_MAX_NUM];

    SOCKET          ConnectSocket;
    DDC_HANDLE      hRespDispatcherThread;
    U32BIT          u32RespDispatcherThreadID;
    BOOLEAN         bClientMsgDispatcherUp;

    SOCKET          IrqListenSock;
    DDC_HANDLE      hIrqListenThread;
    U32BIT          u32IrqListenThreadID;
    BOOLEAN         bIrqListenerUp;

    DDC_HANDLE      hIrqProcThread;
    U32BIT          u32IrqProcThreadID;
    BOOLEAN         bIrqProcUp;
    DDC_HANDLE      hExitEvent;

    void      (_DECL *funcExternalIsr)(S16BIT DevNum, U32BIT dwIrqStatus);

    DDC_RT_INFO asRtInfo[32];

}DDC_REMOTE_DEVICE_INFO, *PDDC_REMOTE_DEVICE_INFO;


#endif
