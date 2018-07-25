#ifndef __DEVICEOP_H__
#define __DEVICEOP_H__

#include <winioctl.h>

/* DDC Registry Key Base */
#define DDC_REG_KEY_BASE "System\\CurrentControlSet\\Control\\DDC1553Devices\\%d"
#define DDC_REG_KEY_SIZE 128
#define DDC_REG_ITEM_DEVICE  "DeviceID"
#define DDC_REG_ITEM_CHANNEL "Channel"
#define DDC_REG_ITEM_FAMILY  "Family"

#define DDC_SYMBOLIC_LINK_SIZE 128

/* Single Processor Affinity Mask */
#define SINGLE_PROC_AFFINTIY_MASK   0x1L

#define ACE_DISPATCH    0 /* Index of irq dispatch thread handle */
#define ACE_WORKER      1 /* Index of irq worker thread handle   */
#define ACE_REPLAY      2 /* Index of replay worker thread handle   */

/* Queue ISR Data Structure */
typedef struct _APC_QUEUE_DATA
{
    SHORT wDevNum;
    DWORD dwIrqStatus;
} APC_QUEUE_DATA, *PAPC_QUEUE_DATA;

/* The following functions are used to Queue ISR calls */
WINBASEAPI DWORD WINAPI QueueUserAPC(PAPCFUNC pfnAPC, HANDLE hThread, ULONG_PTR  dwData);

/* Libraries default interrupt hook...calls internal & external handlers*/
void _DECL _dvSystemIsr(ULONG_PTR pApcQueueData);

/* Interrupt init, free, and processing functions */
S16BIT _DECL _dvInstallIrq(SHORT wDevNum);
U32BIT _DECL _dvIrqDispatcher(SHORT wDevNum);
U32BIT _DECL _dvIrqWorker(SHORT wDevNum);
S16BIT _DECL _dvUninstallIrq(SHORT wDevNum);

/* IOCTL_CMD - Defines a common structure for device functions used to hold various data and pointers */
typedef struct _IOCTL_CMD
{
    U32BIT  Channel;
    U32BIT  Param1;
    U32BIT  Param2;
    U32BIT  Param3;
    U32BIT  Param4;
} IOCTL_CMD, *PIOCTL_CMD;

typedef struct _BC_DATA_BLOCK_ADDR
{
    U32BIT  Address;
    U16BIT  OpCode;
} BC_DATA_BLOCK_ADDR, *PBC_DATA_BLOCK_ADDR;

typedef struct _ACEINFO
{
    /* Physical Card Addr */
    ULONG   ulPhysicalAddress;
    ULONG   ulLength;   /* it's free, use as Flexcore DMA transfer length */
    ULONG   ulChannel;

    /* Memory Window */
    PVOID   pMappedWindow;
    LONG    lWindowLength;

    /* Reg Window */
    PVOID   pMappedRegisters;
    LONG    lRegisterLength;

    /* Interrupt */
    LONG    lInterrupt;

    /* Version Info */
    UCHAR   cDriverMajor;
    UCHAR   cDriverMinor;
    UCHAR   cDriverType;
    LONG    cDriverBuild;
    UCHAR   cLibMajor;
    UCHAR   cLibMinor;

    /* Options */
    ULONG   fOptions;

    HWVERSIONINFO  HwVersionInfo;

} ACEINFO, *PACEINFO;


typedef struct _ACE_OSCONTEXT
{
   DDC_HANDLE hDriverApp;
   DDC_HANDLE hDriverIrq;
   DDC_HANDLE hDriverMtiData;
   DDC_HANDLE hDriverMtiTime;
   DDC_HANDLE hBlockEvent;
   DDC_HANDLE hExitEvent;
   DDC_HANDLE hThread[2];
   U32BIT     dwThreadID[2];
} ACE_OSCONTEXT;

typedef struct _ACE_IOINFO
{
    U16BIT          bInitialized;      /* Initialization status.                */
    ACE_OSCONTEXT  *pContext;          /* OS specific information.              */
    U32BIT          dwCardType;        /* The card being accessed               */
    DDC_HANDLE      hDriverLib;        /* Driver handle for library             */
    CHANCOUNT_t     strChanCount;      /* structure that holds number of IO's.  */

}ACE_IOINFO, *PACE_IOINFO;

/* BC external trigger information */
#define ACE_BC_EXT_TRIGGER_NOT_AVAIL            0x00000000
#define ACE_BC_EXT_TRIGGER_AVAIL                0x00000001
#define ACE_BC_EXT_TRIGGER_USING_DIO            0x00010000
#define ACE_BC_EXT_TRIGGER_USING_DIRECT_INPUT   0x00020000

S16BIT _DECL _dvDriverResourceAllocation
(
    S16BIT DevNum
);

S16BIT _DECL _dvDriverResourceRelease
(
    S16BIT DevNum
);

U16BIT _DECL _dvRegRead
(
    S16BIT DevNum,
    U16BIT wRegAddr,
    U16BIT wMask
);

VOID _DECL _dvRegWrite
(   S16BIT DevNum,
    U16BIT wRegAddr,
    U16BIT wValue,
    U16BIT wMask
);

U32BIT _DECL _dvRegRead32
(
    S16BIT DevNum,
    U32BIT wRegAddr,
    U32BIT wMask
);

VOID _DECL _dvRegWrite32
(   S16BIT DevNum,
    U32BIT wRegAddr,
    U32BIT wValue,
    U32BIT wMask
);

U16BIT _DECL _dvMemRead
(
    S16BIT  DevNum,
    U32BIT  dwMemAddr
);

S16BIT _DECL _dvMemWrite
(
    S16BIT DevNum,
    U32BIT dwMemAddr,
    U16BIT wValue
);

S16BIT _DECL _dvMemWrite32
(
    S16BIT DevNum,
    U32BIT dwMemAddr,
    U32BIT dwValue
);

VOID _DECL _dvCmdStackRead
(
    S16BIT  DevNum,
    U32BIT  dwMemAddr,
    U16BIT  *pBuffer,
    U16BIT  wLength
);

VOID _DECL _dvCmdStackWrite
(
    S16BIT  DevNum,
    U32BIT  dwMemAddr,
    U16BIT  *pBuffer,
    U16BIT  wLength
);

VOID _DECL _dvDataStackRead
(
    S16BIT  DevNum,
    U32BIT  dwMemAddr,
    U16BIT  *pBuffer,
    U16BIT  wLength,
    U16BIT  wOffset
);

VOID _DECL _dvDataStackWrite
(
    S16BIT  DevNum,
    U32BIT  dwMemAddr,
    U16BIT  *pBuffer,
    U16BIT  wLength,
    U16BIT  wOffset
);

VOID _DECL _dvCmdStackRead32
(
    S16BIT  DevNum,
    U32BIT  dwMemAddr,
    U32BIT  *pBuffer,
    U16BIT  wLength
);

VOID _DECL _dvDataStackRead32
(
    S16BIT  DevNum,
    U32BIT  dwMemAddr,
    U32BIT  *pBuffer,
    U16BIT  wLength,
    U16BIT  wOffset
);

S16BIT _DECL _dvClearMemory
(
    S16BIT DevNum,
    U32BIT dwMemAddr,
    U32BIT dwMemLength
);

VOID _DECL _dvDeviceInit
(
    S16BIT DevNum
);

VOID _DECL _dvGetTimeTagValue
(
    S16BIT  DevNum,
    U64BIT  *ullTTValue
);

VOID _DECL _dvSetTimeTagValue
(
    S16BIT  DevNum,
    U64BIT  ullTTValue
);

U16BIT _DECL _dvGetCommandStkArea
(
    S16BIT DevNum
);

U32BIT _DECL _dvGetBcDataBlockAddr
(
    S16BIT  DevNum,
    U32BIT  XqfAddress,
    U16BIT  *pOpCode
);

S16BIT _DECL _dvGetBcExtTriggerAvail
(
    S16BIT  DevNum,
    U32BIT  *pu32Avail
);

U32BIT _DECL _dvGetMtCommandStkPointer
(
    S16BIT DevNum,
    U32BIT StackLocation
);

VOID _DECL _dvGetMtCommandStkNext
(
    S16BIT DevNum,
    U32BIT dwCmdStkAddr,
    U16BIT *pBuffer,
    U16BIT Length
);

VOID _DECL _dvGetMtCommandStkNext32
(
    S16BIT DevNum,
    U32BIT dwCmdStkAddr,
    U32BIT *pBuffer,
    U16BIT Length
);

VOID _DECL _dvGetMtCommandStkLatest
(
    S16BIT DevNum,
    U32BIT dwCmdStkAddr,
    U16BIT *pBuffer,
    U16BIT Length
);

VOID _DECL _dvGetMtCommandStkData
(
    S16BIT DevNum,
    U32BIT dwAddress,
    U32BIT dwDataStkBase,
    U16BIT *pBuffer,
    U16BIT Length,
    U16BIT RolloverLength
);

VOID _DECL _dvGetMtCommandStkData32
(
    S16BIT DevNum,
    U32BIT dwAddress,
    U32BIT dwDataStkBase,
    U32BIT *pBuffer,
    U16BIT Length,
    U16BIT RolloverLength
);

U16BIT _DECL _dvGetMtCommandStkDataCount
(
    S16BIT DevNum,
    U32BIT dwCmdStkAddr,
    U32BIT dwDataStkAddr,
    U32BIT dwDataStkAddrNext,
    U16BIT wDataStkSize,
    U16BIT wTotalDataLength
);

U32BIT _DECL _dvGetRtCommandStkPointer
(
    S16BIT DevNum,
    U32BIT StackLocation
);

VOID _DECL _dvGetRtCommandStkNext
(
    S16BIT DevNum,
    U32BIT dwCmdStkAddr,
    U16BIT *pBuffer,
    U16BIT Length
);

VOID _DECL _dvGetRtCommandStkNext32
(
    S16BIT DevNum,
    U32BIT dwCmdStkAddr,
    U32BIT *pBuffer,
    U16BIT Length
);

VOID _DECL _dvGetRtCommandStkLatest
(
    S16BIT DevNum,
    U32BIT dwCmdStkAddr,
    U16BIT *pBuffer,
    U16BIT Length
);

VOID _DECL _dvSetBcMessageBlk
(
    S16BIT  DevNum,
    U32BIT  MsgAddress,
    U16BIT  *pBuffer,
    U16BIT  Length
);

VOID _DECL _dvSetBcMessageDataPtr
(
    S16BIT  DevNum,
    U32BIT  MsgAddress,
    U32BIT  DataBlkPtr
);

VOID _DECL _dvSetRtCommandStkPurge
(
    S16BIT DevNum,
    U32BIT StackLocation,
    U16BIT PurgeData
);

VOID _DECL _dvGetRtCommandStkData
(
    S16BIT DevNum,
    U32BIT dwAddress,
    U32BIT dwDataStkBase,
    U16BIT *pBuffer,
    U16BIT Length,
    U16BIT RolloverLength
);

VOID _DECL _dvGetRtCommandStkData32
(
    S16BIT DevNum,
    U32BIT dwAddress,
    U32BIT dwDataStkBase,
    U32BIT *pBuffer,
    U16BIT Length,
    U16BIT RolloverLength
);

U16BIT _DECL _dvGetRtCommandStkDataCount
(
    S16BIT DevNum,
    U32BIT dwCmdStkAddr,
    U32BIT dwDataStkAddr,
    U32BIT dwDataStkAddrNext,
    U16BIT wDataStkSize,
    U16BIT wTotalDataLength
);

U32BIT _DECL _dvGetRtDataBlkOffset
(
    S16BIT DevNum,
    U16BIT LookupTableAddr,
    U32BIT DataBlkBaseAddr
);

U32BIT _DECL _dvGetRtDataBlkPointer
(
    S16BIT DevNum,
    U16BIT LookupTableAddr
);

U16BIT _DECL _dvGetRtSubAddrCtrlWord
(
    S16BIT DevNum,
    U16BIT SubAddress
);

S16BIT _DECL _dvGetHwVersionInfo
(
    S16BIT          DevNum,
    PHWVERSIONINFO  pHwVersionInfo
);

VOID _DECL _dvSetMtCommandStkPurge
(
    S16BIT DevNum,
    U32BIT StackLocation,
    U16BIT PurgeData
);

VOID _DECL _dvSetMtCommandStkPointer
(
    S16BIT DevNum,
    U32BIT StackLocation,
    U32BIT StackPtr
);

VOID _DECL _dvSetMtDataStkPointer
(
    S16BIT DevNum,
    U32BIT StackLocation,
    U32BIT StackPtr

);

VOID _DECL _dvSetMtCommandStkSize
(
    S16BIT DevNum,
    U16BIT wCmdStkSize,
    U16BIT wMask

);

VOID _DECL _dvSetMtDataStkSize
(
    S16BIT DevNum,
    U16BIT wCmdStkSize,
    U16BIT wMask

);

VOID _DECL _dvSetRtCommandStkPurge
(
    S16BIT DevNum,
    U32BIT StackLocation,
    U16BIT PurgeData
);

VOID _DECL _dvSetRtCommandStkPointer
(
    S16BIT DevNum,
    U32BIT StackLocation,
    U32BIT StackPtr
);

VOID _DECL _dvSetRtDataBlkPointer
(
    S16BIT DevNum,
    U16BIT LookupTableAddr,
    U32BIT DataBlkPtr
);

VOID _DECL _dvSetRtSubAddrCtrlWord
(
    S16BIT DevNum,
    U16BIT SubAddress,
    U16BIT SubAddressCtrlWord
);

VOID _DECL _dvSetRtCommandStkSize
(
    S16BIT DevNum,
    U16BIT wCmdStkSize,
    U16BIT wMask

);

S16BIT _DECL _dvGetMtiCh10DataPkt
(
    S16BIT DevNum,
    PMTI_CH10_DATA_PKT *ppCh10Pkt,
    S16BIT Timeout
);

S16BIT _DECL _dvGetMtiCh10TimePkt
(
    S16BIT DevNum,
    PMTI_CH10_TIME_PKT *ppCh10Pkt,
    S16BIT Timeout
);

S16BIT _DECL _dvSetMtiConfig
(
    S16BIT      DevNum,
    PMTI_CONFIG MtiConfig
);

VOID _DECL _dvSetMtiState
(
    S16BIT DevNum,
    U16BIT State
);

VOID _DECL _dvSetMtiDmaBufferAddr
(
    S16BIT DevNum,
    U32BIT Address
);

VOID _DECL _dvSetMtiDmaBufferSize
(
    S16BIT DevNum,
    U32BIT Size
);

S16BIT _DECL _dvSetMtiCh10DataPktFree
(
    S16BIT              DevNum,
    PMTI_CH10_DATA_PKT  *ppCh10Pkt
);

S16BIT _DECL _dvSetMtiCh10TimePktFree
(
    S16BIT              DevNum,
    PMTI_CH10_TIME_PKT  *ppCh10Pkt
);

VOID _DECL _dvSetMtiFree
(
    S16BIT DevNum
);

DISC_LEVEL _DECL _dvGetDiscOut
(
    S16BIT  DevNum,
    S16BIT  Discrete
);

S16BIT _DECL _dvGetDiscDir
(
    S16BIT  DevNum,
    S16BIT  Discrete
);

DISC_LEVEL _DECL _dvGetDiscIn
(
    S16BIT  DevNum,
    S16BIT  Discrete
);

S16BIT _DECL _dvSetDiscOut
(
    S16BIT      DevNum,
    S16BIT      Discrete,
    DISC_LEVEL  Level
);

S16BIT _DECL _dvSetDiscDir
(
    S16BIT      DevNum,
    S16BIT      Discrete,
    DISC_DIR    Direction
);

S16BIT _DECL _dvGetDiscAll
(
    S16BIT  DevNum,
    U16BIT  *Directions,
    U16BIT *Levels
);

S16BIT _DECL _dvSetDiscAll
(
    S16BIT  DevNum,
    U16BIT  Directions,
    U16BIT  Levels
);

S16BIT _DECL _dvGetChannelCount
(
    S16BIT DevNum,
    CHANCOUNT_t *pChanCount
);

S16BIT _DECL _dvSetAioDir
(
    S16BIT DevNum,
    S16BIT Channel,
    AVIONIC_DIRECTION Direction
);

S16BIT _DECL _dvSetAioOutput
(
    S16BIT DevNum,
    S16BIT Channel,
    AVIONIC_LEVEL Level
);

AVIONIC_DIRECTION _DECL _dvGetAioDir
(
    S16BIT DevNum,
    S16BIT Channel
);

AVIONIC_LEVEL _DECL _dvGetAioOutput
(
    S16BIT DevNum,
    S16BIT Channel
);

AVIONIC_LEVEL _DECL _dvGetAioInput
(
    S16BIT DevNum,
    S16BIT Channel
);

S16BIT _DECL _dvGetAioAll
(
    S16BIT DevNum,
    U16BIT *Directions,
    U16BIT *Levels
);

S16BIT _DECL _dvSetAioAll
(
    S16BIT DevNum,
    U16BIT Directions,
    U16BIT Levels
);
BOOLEAN _DECL _dvFlashMemBlockErase
(
    S16BIT DevNum,
    U32BIT Address
);

BOOLEAN _DECL _dvFlashMemRead
(
    S16BIT DevNum,
    U32BIT Address,
    U8BIT *pBuffer,
    U32BIT ByteCount
);

BOOLEAN _DECL _dvFlashMemWrite
(
    S16BIT DevNum,
    U32BIT Address,
    U8BIT *pBuffer,
    U32BIT ByteCount
);

BOOLEAN _DECL _dvFlashMemWriteProtected
(
    S16BIT DevNum
);

VOID _DECL _dvFlashMemInfo
(
    S16BIT  DevNum,
    U32BIT  *StartAddress,
    U32BIT  *SectorCount,
    U32BIT  *MinSectorSize
);

U32BIT _DECL _dvGpRegRead
(
    S16BIT  DevNum,
    U32BIT  dwRegAddr
);

VOID _DECL _dvGpRegWrite
(
    S16BIT DevNum,
    U32BIT dwRegAddr,
    U32BIT dwValue,
    U32BIT dwMask
);

S16BIT _DECL _dvIODriverResourceAllocation
(
    S16BIT DevNum
);

S16BIT _DECL _dvIODriverResourceRelease
(
    S16BIT DevNum
);

//-----------------------------------------------------------------------------
//
// OS Specific Host Buffer Thread Synchronization Mutex
//
//-----------------------------------------------------------------------------
VOID _DECL _dvInitializeCriticalSection
(
    S16BIT DevNum
);

VOID _DECL _dvDeleteCriticalSection
(
    S16BIT DevNum
);

VOID _dvEnterCriticalSection
(
    S16BIT DevNum
);

VOID _dvLeaveCriticalSection
(
    S16BIT DevNum
);

U32BIT _DECL _dvIrqDispatcher
(
    SHORT wDevNum
);

U32BIT _DECL _dvIrqWorker
(
    SHORT wDevNum
);

void APIENTRY _dvSystemIsr
(
    ULONG_PTR pApcQueueData
);

S16BIT _DECL _osFreeIO
(
    S16BIT DevNum
);

S16BIT _DECL _osInitIO
(
    S16BIT DevNum,
    S16BIT wOptions
);

S16BIT _DECL _dvGetIRIGTx
(
    S16BIT          DevNum,
    PACE_IRIG_TX    pstructIRIG
);

S16BIT _DECL _dvSetIRIGTx
(
    S16BIT          DevNum,
    ACE_IRIG_TX structIRIG
);

S16BIT _DECL _dvMTISetCh10TimePktId
(
    S16BIT DevNum,
    U16BIT u16ChannelId
);

#endif /* __DEVICEOP_H_ */
