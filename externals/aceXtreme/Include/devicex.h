/*****************************************************************************
*                       Data Device Corporation
*                         105 Wilbur Place
*                        Bohemia N.Y. 11716
*
*       AceXtreme 'C' Run Time Library
*
*       Copyright (c) 2008 Data Device Corporation
*       All Rights Reserved.
*
*       Filename: devicex.h
*
******************************************************************************
* Non-Disclosure Statement
* ------------------------
* This software is the sole property of Data Device Corporation.  All
* rights, title, ownership, or other interests in the software remain
* the property of Data Device Corporation.  This software may be used
* in accordance with applicable licenses.  Any unauthorized use,
* duplication, transmission, distribution, or disclosure is expressly
* forbidden.
*
* This non-disclosure statement may not be removed or modified without
* prior written consent of Data Device Corporation.
******************************************************************************
*
*   Description:
*       This is the include file for devicex.c
*
*
******************************************************************************/

#ifndef __DEVICEX_H__
#define __DEVICEX_H__

#define RES_RELEASE_WAIT_TIME   500     /* in ms */

/*============================================================================*/
/*                               S T R U C T S                                */
/*============================================================================*/

typedef struct _ACEX_OSCONTEXT
{
   DDC_HANDLE hDriverApp;
   DDC_HANDLE hDriverIrq;
   DDC_HANDLE hDriverMtiData;
   DDC_HANDLE hDriverMtiTime;
   DDC_HANDLE hDriverReplay;
   DDC_HANDLE hBlockEvent;
   DDC_HANDLE hExitEvent;
   DDC_HANDLE hThread[3];
   U32BIT     dwThreadID[3];
} ACEX_OSCONTEXT;

typedef struct _ACEX_IOINFO
{
    U16BIT          bInitialized;      /* Initialization status.                */
    ACEX_OSCONTEXT  *pContext;         /* OS specific information.              */
    U32BIT          dwCardType;        /* The card being accessed               */
    DDC_HANDLE      hDriverLib;        /* Driver handle for library             */
    CHANCOUNT_t     strChanCount;      /* structure that holds number of IO's.  */
    DDC_HANDLE      hDriverIrq;        /* Device handle for interrupt processing*/
    DDC_HANDLE      hInitEvent;        /* Dispatcher thread init. event.        */
    DDC_HANDLE      hExitEvent;        /* Interrupt terminations event.         */
    DDC_HANDLE      hThread[2];        /* Board IO device interrupt threads.    */
    U32BIT          dwThreadID[2];     /* Interrupt thread ID's.                */
    void            (_DECL *pfIOIsr)(S16BIT DevNum, U32BIT u32IntSts); /* ISR.  */
}ACEX_IOINFO, *PACEX_IOINFO;

/* ========================================================================== */
/*                               IOCTL DEFINITIONS                            */
/* ========================================================================== */

#define IOCTL_ACEX_GETINFO                      CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 0,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BLOCK_ON_IRQ                 CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 3,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_RELEASE_IRQ                  CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 4,  METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_GET_INFOREG                  CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 16, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_GET_CONFIG_DESCRIPTOR        CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 20, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_RESET_DEVICE                 CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 21, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_RESET_PIPE                   CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 22, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_GET_USB_DEVICE_CAPS          CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 25, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_USB_VENDOR_OUT               CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 32, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BOARD_COMPONENT_RESET        CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 33, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_ACEX_REG_READ                     CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 50, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_REG_WRITE                    CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 51, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_MEM_READ                     CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 52, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_MEM_WRITE                    CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 53, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_CMD_STACK_READ               CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 54, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_CMD_STACK_WRITE              CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 55, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_DATA_STACK_READ              CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 56, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_DATA_STACK_WRITE             CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 57, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_DATA_SEND_STREAM             CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 58, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_DATA_RECEIVE_STREAM          CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 59, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_REG_READ32                   CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 60, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_REG_WRITE32                  CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 61, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_ACEX_MEM_READ32                   CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 62, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_MEM_WRITE32                  CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 63, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_ACEX_REG_READ_BLK                 CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 64, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_REG_WRITE_BLK                CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 65, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_MEM_READ_BLK                 CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 66, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_MEM_WRITE_BLK                CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 67, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_GET_TIME_TAG                 CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 70, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_TIME_TAG                 CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 71, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_GET_IRIG_TX                  CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 72, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_IRIG_TX                  CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 73, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_IRIG_ID                  CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 74, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_SET_RESP_TIME_OUT            CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 80, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_WAIT                         CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 85, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_SET_TT_RESOLUTION            CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 90, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_TT_ROLLOVER_POINT        CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 91, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_TT_INTERRUPT             CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 92, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_EXT_TT_CNT_CTRL              CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 93, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_SET_RAM_PARITY_CHECKING      CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 95, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_GET_CMD_STK_AREA             CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 100, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_ACEX_IMP_READ                     CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 110, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_1553_CONFIGURE               CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 119, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_ACEX_BC_GET_ASYNC_COUNT           CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 120, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_GET_DATA_BUFFER           CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 121, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_GET_FRAME_TO_HBUF         CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 122, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_GET_HBUF_MESSAGE          CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 123, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_GET_METRICS               CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 124, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_GET_MESSAGE               CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 125, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_GPQ_CLEAR                 CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 126, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_GPQ_COUNT                 CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 127, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_GPQ_READ                  CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 128, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_POST_ASYNC_MESSAGE        CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 129, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_SET_MSG_BUFFER            CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 130, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_SET_DATA_BUFFER           CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 131, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_STATE                     CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 132, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_DATASTR_INIT              CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 133, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_DATASTR_STATUS            CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 134, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_DATA_ARRAY_INIT           CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 135, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_DATA_ARRAY_STATUS         CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 136, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_EXT_TRIGGER_AVAIL         CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 137, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_ASYNC_QUEUE_INFO          CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 138, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_CMD_STACK_READ            CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 139, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BC_DATA_STACK_READ           CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 140, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_CLEAR_MEMORY                 CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 150, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_DEVICE_INIT                  CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 151, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_ACEX_GET_AIO_OUTPUT               CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 153, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_GET_AIO_DIRECTION            CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 154, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_GET_AIO_INPUT                CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 155, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_GET_AIO_ALL                  CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 156, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_SET_AIO_OUTPUT               CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 157, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_AIO_DIRECTION            CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 158, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_AIO_ALL                  CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 159, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_GET_DIO_OUTPUT               CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 160, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_GET_DIO_DIRECTION            CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 161, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_GET_DIO_INPUT                CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 162, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_GET_DIO_ALL                  CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 163, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_SET_DIO_OUTPUT               CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 164, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_DIO_DIRECTION            CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 165, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_DIO_ALL                  CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 166, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_GET_IO_COUNT                      CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 167, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_GET_MTI_CH10_DATA_PKT        CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 170, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_GET_MTI_CH10_TIME_PKT        CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 171, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_SET_MTI_STATE                CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 181, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_MTI_CH10_DATA_PKT_FREE   CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 182, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_MTI_CH10_TIME_PKT_FREE   CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 183, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_MTI_FREE                 CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 184, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_MTI_STROBE_REG           CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 185, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_GET_MTI_CH10_STATUS          CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 186, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_MTI_FREE_MEM_COUNT           CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 187, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_MTI_INTERUPT_CONFIG          CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 188, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_MTI_GET_METRICS_CONFIG       CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 189, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_IRIG_SET_INT_STATE           CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 190, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_ARINC_LOADTXONE              CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 195, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_ARINC_GET_TT_CONFIG          CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 196, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_ARINC_SET_TT_CONFIG          CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 197, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_ARINC_GET_PGRM_LOOPBACK      CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 198, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_ARINC_SET_PGRM_LOOPBACK      CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 199, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_ARINC_REG_READ               CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 200, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_ARINC_REG_WRITE              CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 201, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_ARINC_MEM_READ               CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 202, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_ARINC_MEM_WRITE              CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 203, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_ARINC_BLOCK_ON_IRQ           CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 204, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_ARINC_RELEASE_IRQ            CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 205, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_ARINC_MEM_READ_MORE          CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 206, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_ARINC_SET_OLD_LOOPBACK       CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 207, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_ARINC_GET_OLD_LOOPBACK       CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 208, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_ARINC_LOADTXMORE             CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 209, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_BLK_READ                     CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 210, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_BLK_WRITE                    CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 211, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_GET_CAPABILITIES             CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 212, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_GET_ENHANCED_CAPABILITIES         CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 213, METHOD_BUFFERED, FILE_ANY_ACCESS)


#define IOCTL_GET_DEV_FEATURE_INFO              CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 215, METHOD_BUFFERED, FILE_ANY_ACCESS)


#define IOCTL_ACEX_ACTEL_REG_READ               CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 220, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_ACEX_ACTEL_REG_WRITE              CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 221, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_ACEX_FLASH_MEM_READ               CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 222, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_FLASH_MEM_WRITE              CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 223, METHOD_IN_DIRECT , FILE_ANY_ACCESS)
#define IOCTL_ACEX_FLASH_MEM_BLOCK_ERASE        CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 224, METHOD_IN_DIRECT,  FILE_ANY_ACCESS)
#define IOCTL_ACEX_FLASH_MEM_WRITE_PROTECTED    CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 225, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_FLASH_MEM_INFO               CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 226, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_GET_INTERRUPT_MSG            CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 227, METHOD_BUFFERED, FILE_ANY_ACCESS)

/* IMPROVEMENTS BLOCK SPECIFIC */
#define IOCTL_IMP_CFG                           CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 228, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_ACEX_GET_HW_VERSION_INFO          CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 230, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_DEVICE_STATUS                CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 231, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_GET_DATA_ARCHIVE             CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 232, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_ACEX_GET_COUPLING                 CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 240, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_COUPLING                 CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 241, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_GET_AMPLITUDE                CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 243, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_AMPLITUDE                CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 244, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_MODULE_INTERRUPT_STATE   CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 250, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_SET_IRQ_CONDITIONS           CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 251, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_RESERVED_01                  CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 255, METHOD_BUFFERED, FILE_ANY_ACCESS)

/* Multi-Function support*/
#define IOCTL_ACEX_CHECK_MF_CAPABLE             CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 260, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_BC_REPLAY_STATUS                  CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 261, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_BC_REPLAY_BLOCK_ON_IRQ            CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 262, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_BC_REPLAY_RELEASE_IRQ             CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 263, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_BC_REPLAY_DMA                     CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 264, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_BC_REPLAY_RAW                     CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 265, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_BC_REPLAY_WRITE                   CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 266, METHOD_IN_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_ACEX_TRG_RESET                    CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 270, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_ACEX_TRG_IRQ_STATUS               CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 271, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

#define IOCTL_DIO_TT_CFG                        CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 275, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_DIO_TT_CTL                        CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 276, METHOD_IN_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_DIO_TT_READ                       CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 277, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_DIO_TT_BLOCK_ON_IRQ               CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 278, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DIO_TT_RELEASE_IRQ                CTL_CODE(IOCTL_DEVICE_TYPE, IOCTL_INDEX + 279, METHOD_BUFFERED, FILE_ANY_ACCESS)

/* ========================================================================== */
/*                                GENERAL DEFINITIONS                         */
/* ========================================================================== */
/* IOCTL failure macro */
#define ACEX_IOCTL_FAILURE       0

/* MRT Improvements IOCTL Command Code */
#define IOCTL_IMP_MRT_CMD        0

/* Generic time delay */
#define WAIT_TIMEOUT_MAX_MS      1000

#define ACE_SLEEP_MS(dwMs) (Sleep(dwMs))

/* 1553 IOCTL ACCESS TYPES */
#define REG_TYPE_ABSOLUTE_ADDR   0
#define REG_TYPE_BD_OFFSET       1
#define REG_TYPE_BC_OFFSET       2
#define REG_TYPE_MRT_OFFSET      3
#define REG_TYPE_MTI_OFFSET      4
#define REG_TYPE_1553_OFFSET     5
#define REG_TYPE_EI_OFFSET       6
#define REG_TYPE_REPLAY_OFFSET   7
#define REG_TYPE_TRG_OFFSET      8

#define ACEX_16_BIT_ACCESS       0
#define ACEX_32_BIT_ACCESS       -1

#define IOCTL_16_BIT_ACCESS      0
#define IOCTL_32_BIT_ACCESS      1

/* Device Family Enumeration - This Device Is DDC_ACEX */
typedef enum _DDC_FAMILY
{
    DDC_EMACE = 0,
    DDC_E2MACE,
    DDC_ACEX
} DDC_FAMILY;

#define ACEX_32_BIT_ACCESS_16_BIT_HW_MEM    -1

/* Dma Cache Line Size Padding Macro - 32 bytes accommodates all possible bus widths */
#define DMA_CACHE_LINE_PAD  32

/* ========================================================================== */
/*                         BUS CONTROLLER DEFINITIONS                         */
/* ========================================================================== */

/*  dwIrqMask parameter can be the following OR'd together */
#define ACE_IMR1_EOM                0x00000001
#define ACE_IMR1_BC_STATUS_SET      0x00000002
#define ACE_IMR1_RT_MODE_CODE       0x00000002
#define ACE_IMR1_MT_PATTERN_TRIG    0x00000002
#define ACE_IMR1_FORMAT_ERR         0x00000004
#define ACE_IMR1_BC_END_OF_FRM      0x00000008
#define ACE_IMR1_BC_MSG_EOM         0x00000010
#define ACE_IMR1_RT_SUBADDR_EOM     0x00000010
#define ACE_IMR1_RT_CIRCBUF_ROVER   0x00000020
#define ACE_IMR1_TT_ROVER           0x00000040
#define ACE_IMR1_RT_ADDR_PAR_ERR    0x00000080
#define ACE_IMR1_BC_RETRY           0x00000100
#define ACE_IMR1_HSHAKE_FAIL        0x00000200
#define ACE_IMR1_MT_DATASTK_ROVER   0x00000400
#define ACE_IMR1_MT_CMDSTK_ROVER    0x00000800
#define ACE_IMR1_BCRT_CMDSTK_ROVER  0x00001000
#define ACE_IMR1_BCRT_TX_TIMEOUT    0x00002000
#define ACE_IMR1_RAM_PAR_ERR        0x00004000
#define ACE_IMR2_IRIG_INTERRUPT     0x00008000
#define ACE_IMR2_BIT_TRIGGER        0x00010000
#define ACE_IMR2_BIT_COMPLETE       0x00020000
#define ACE_IMR2_FLEX_DMA_ENABLE    0x00020000
#define ACE_IMR2_BC_UIRQ0           0x00040000
#define ACE_IMR2_BC_UIRQ1           0x00080000
#define ACE_IMR2_BC_UIRQ2           0x00100000
#define ACE_IMR2_BC_UIRQ3           0x00200000
#define ACE_IMR2_MT_DSTK_50P_ROVER  0x00400000
#define ACE_IMR2_MT_CSTK_50P_ROVER  0x00800000
#define ACE_IMR2_RT_CIRC_50P_ROVER  0x01000000
#define ACE_IMR2_RT_CSTK_50P_ROVER  0x02000000
#define ACE_IMR2_BC_TRAP            0x04000000
#define ACE_IMR2_BC_CALLSTK_ERR     0x08000000
#define ACE_IMR2_GPQ_ISQ_ROVER      0x10000000
#define ACE_IMR2_RT_ILL_CMD         0x20000000
#define ACE_IMR2_BC_OPCODE_PARITY   0x40000000
#define ACE_IMR2_MTI_INTERRUPT      0x80000000

/* ========================================================================== */
/*                         BUS CONTROLLER DEFINITIONS                         */
/* ========================================================================== */

/* ========================================================================== */
/*                         REMOTE TERMINAL DEFINITIONS                        */
/* ========================================================================== */

/* ========================================================================== */
/*                      MULTI REMOTE TERMINAL DEFINITIONS                     */
/* ========================================================================== */
/* ========================================================================== */
/*                          BUS MONITIOR DEFINITIONS                          */
/* ========================================================================== */

/* ========================================================================== */
/*                            FUNCTION PROTOTYPES                             */
/* ========================================================================== */
S16BIT _DECL _dvxGetApiType
(
    S16BIT DevNum
);

S16BIT _DECL _dvxGetFamily
(
    S16BIT DevNum
);

S16BIT _DECL _dvxGetDeviceID
(
    S16BIT DevNum
);

S16BIT _DECL _dvxDriverResourceAllocation
(
    S16BIT DevNum
);

S16BIT _DECL _dvxDriverResourceRelease
(
    S16BIT DevNum
);

U32BIT _DECL _dvxIrqDispatcher
(
    SHORT wDevNum
);

U32BIT _DECL _dvxIrqWorker
(
    SHORT wDevNum
);

void APIENTRY _dvxSystemIsr
(
    ULONG_PTR pApcQueueData
);

S16BIT _DECL _dvxIODriverResourceAllocation
(
    S16BIT DevNum
);

S16BIT _DECL _dvxIODriverResourceRelease
(
    S16BIT DevNum
);

void _DECL _dvxRegRead
(
    S16BIT      DevNum,
    U32BIT      u32RegAddrOffset,
    U32BIT      *pu32Data,
    U32BIT      u32NumBytes,
    U32BIT      u32Type
);

void _DECL _dvxRegWrite
(
    S16BIT      DevNum,
    U32BIT      u32RegAddrOffset,
    U32BIT      *pu32Data,
    U32BIT      u32NumBytes,
    U32BIT      u32Type
);

void _DECL _dvxMemRead
(
    S16BIT      DevNum,
    U32BIT      u32MemAddr,
    S32BIT      s32WdOffset, /* >=0 for 16-bit access, -1 for 32-bit access */
    void        *pData,
    U32BIT      u32NumBytes  /* number of bytes to read */
);

void _DECL _dvxMemWrite
(
    S16BIT      DevNum,
    U32BIT      u32MemAddr,
    S32BIT      s32WdOffset, /* >=0 for 16-bit access */
    void        *pData,
    U32BIT      u32NumBytes  /* number of bytes to read */
);

S16BIT _DECL _dvxBlkRead
(
    S16BIT      DevNum,
    U16BIT      u16Chnl,
    U32BIT      u32RegBA,
    U32BIT      *pu32Data,
    U32BIT      u32DataByteLength,
    U8BIT       u8Type);

S16BIT _DECL _dvxBlkWrite
(
    S16BIT      DevNum,
    U16BIT      u16Chnl,
    U32BIT      u32BA,
    U32BIT      *pu32Data,
    U32BIT      u32DataByteLength,
    U8BIT       u8Type
);

S32BIT _DECL _dvxMrtRead
(
    S16BIT      DevNum,
    U16BIT      u16Chnl,
    U16BIT      RtAddrNumCmds,
    U16BIT      RtSAddr,
    U32BIT      *pu32Data,
    U32BIT      u32DataByteLength,
    U8BIT       u8Type
);

S16BIT _DECL _dvxMrtReadModeCodeData
(
    S16BIT DevNum,
    S8BIT  s8RtAddr,
    U16BIT wModeCode,
    U16BIT *pMCData

);

S16BIT _DECL _dvxMrtWriteModeCodeData
(
    S16BIT DevNum,
    S8BIT  s8RtAddr,
    U16BIT wModeCode,
    U16BIT MCData
);

S32BIT _DECL _dvxMrtControl
(
    S16BIT      DevNum,
    void        *pSnd,
    U32BIT      u32SndByteSize,
    void        *pRcv,
    U32BIT      u32RcvByteSize,
    U32BIT      *pu32Length
);

S16BIT _DECL _dvxMrtSetRespTimeout
(
    S16BIT      s16DevNum,
    S8BIT       s8RtAddr,
    U32BIT      u32RespTimeOut
);
S16BIT _DECL _dvxMrtSendStream
(
    S16BIT                  DevNum,
    ACEX_MRT_STREAM_TYPE    *pMrtStream
);

S16BIT _DECL _dvxMrtReceiveStream
(
    S16BIT                  DevNum,
    ACEX_MRT_STREAM_TYPE    *pMrtStream
);

U32BIT _DECL _dvxFlashMemRead
(
    S16BIT      DevNum,
    U8BIT       u8Chnl,
    U32BIT      u32MemAddr
);

VOID _DECL _dvxFlashMemWrite
(
    S16BIT      DevNum,
    U8BIT       u8Chnl,
    U32BIT      u32MemAddr,
    U32BIT      u32MemData,
    char        *dataBuffer
);

VOID _DECL _dvxFlashMemErase
(
    S16BIT      DevNum,
    U8BIT       u8Chnl,
    U32BIT      u32MemAddr
);

S16BIT _DECL _dvxGetHwVersionInfo
(
    S16BIT         DevNum,
    PHWVERSIONINFO pHwVersionInfo
);

S16BIT _DECL _dvxGetChannelCount
(
    S16BIT DevNum,
    CHANCOUNT_t *pChanCount
);

VOID _DECL _dvxGetTimeTagValue(
                                S16BIT  DevNum,
                                U64BIT  *ullTTValue);

VOID _DECL _dvxSetTimeTagValue(
                                S16BIT  DevNum,
                                U64BIT  ullTTValue);

S16 _DECL _dvxExternalTTCntCtrl(S16BIT s16DevNum, U16BIT u16ExtCtrl);

S16 _DECL _dvxMtiInit
(
    S16 s16DevNum
);

S16 _DECL _dvxSetMtiConfig
(
    S16 s16DevNum,
    ACEX_MTI_CONFIG *pMtiConfig
);

S16 _DECL _dvxSetMtiState
(
    S16 s16DevNum,
    U16 u16State
);

S16 _DECL acexMTiFree
(
    S16 s16DevNum
);

S16 _DECL _dvxSetMTRespTimeOut
(
    S16BIT  s16DevNum,
    U32BIT  u32RespTimeOut
);

S16 _DECL _dvxSetBCRespTimeOut
(
    S16BIT  s16DevNum,
    U32BIT  u32RespTimeOut
);

S16 _DECL _dvxSetIRQCond
(
    S16BIT DevNum,
    U16BIT bEnable,
    U32BIT dwIrqMask
);

S16 _DECL _dvxSetTimeTagRes
(
    S16BIT  DevNum,
    S16BIT  s16DevNum,
    U16BIT  u16TTRes
);

S16 _DECL _dvxSetTimeTagRolloverPoint
(
    S16BIT  DevNum,
    S16BIT  s16DevNum,
    U16BIT  u16TTRolloverPoint
);

S16 _DECL _dvxSetRamParityChecking
(
    S16BIT  DevNum,
    S16BIT  s16DevNum,
    BOOLEAN bEnable
);

S16 _DECL _dvxGetMtiCh10DataPkt
(
    S16BIT              DevNum,
    S16BIT              s16DevNum,
    PMTI_CH10_DATA_PKT  *ppCh10Pkt,
    S16BIT              s16Timeout
);

S16 _DECL _dvxGetMtiCh10TimePkt
(
    S16BIT              DevNum,
    S16BIT              s16DevNum,
    PMTI_CH10_TIME_PKT  *ppCh10Pkt,
    S16BIT              s16Timeout
);

S16 _DECL _dvxMTICh10TimePktEnable
(
    S16BIT  s16DevNum,
    BOOLEAN bEnable
);

S16 _DECL _dvxSetMtiCh10TimePktFree
(
    S16BIT              s16DevNum,
    PMTI_CH10_TIME_PKT  *ppCh10Pkt
);

S16 _DECL _dvxSetMTiStrobeReg
(
    S16BIT  s16DevNum,
    U32BIT  u32MtiFunction
);

S16 _DECL _dvxGetMtiCh10Status
(
    S16BIT          s16DevNum,
    ACEX_MTI_INFO   *pUmtMtiInfo
);

S16 _DECL _dvxSetModuleInterruptState
(
    S16BIT  s16DevNum,
    BOOLEAN bEnable,
    U32BIT  u32Mask
);

S16 _DECL _dvxMtiFreeMemCount
(
    S16BIT  s16DevNum,
    U32BIT  u32WordCount
);

S16 _DECL _dvxMTIFreeConfig
(
    S16BIT          DevNum,
    ACEX_MTI_CONFIG *pMtiConfig
);

S16 _DECL _dvxMtiInterruptConfig
(
    S16BIT          s16DevNum,
    ACEX_MTI_CONFIG *pMtiConfig
);

S16 _DECL _dvxBcInit
(
    S16BIT  DevNum,
    U16BIT  u16Channel
);

S16 _DECL _dvxBcExtTriggerAvail
(
    S16BIT  DevNum,
    U16     u16Channel,
    U32     *pu32Avail
);

S16 _DECL _dvxBcDataArrayInit
(
    S16BIT  DevNum,
    U16BIT  u16Channel,
    S16BIT  s16DataStrId,
    U16BIT  u16MsgCountSend
);

S16 _DECL _dvxBcDataArrayStatus
(
    S16BIT                      DevNum,
    U16BIT                      u16Channel,
    S16BIT                      s16DataArrayId,
    ACEX_BC_DATA_ARRAY_STATUS   *pStatus
);

S16 _DECL _dvxBcDataStreamInit
(
    S16BIT  DevNum,
    U16BIT  u16Channel,
    S16BIT  s16DataStrId,
    U16BIT  u16MsgCountSend,
    U16BIT  u16MsgCountReceive
);

S16 _DECL _dvxBcDataStreamStatus
(
    S16BIT                  DevNum,
    U16BIT                  u16Channel,
    S16BIT                  s16DataStrId,
    U16BIT                  u16Direction,
    ACEX_BC_DATASTR_STATUS  *pStatus
);

S16 _DECL _dvxBcConfig
(
    S16BIT  DevNum,
    U16BIT  u16Channel
);

S16BIT _DECL _dvxChannelInit
(
    S16BIT s16DevNum,
    U16BIT u16Channel
);

S16 _DECL _dvxBcFree
(
    S16BIT  DevNum,
    U16BIT  u16Channel
);

S16 _DECL _dvxBcGetAsyncCount
(
    S16BIT  DevNum,
    U16BIT  u16Channel
);

S16 _DECL _dvxBcGetDataBuffer
(
    S16BIT  DevNum,
    U16BIT  u16Channel,
    U16BIT  u16MsgId,
    U32BIT  u32Size,
    U16BIT  *pBuffer,
    U16BIT  u16Offset
);

S16 _DECL _dvxBcCmdStackRead
(
    S16BIT DevNum,
    U16    u16Channel,
    U32    u32MemAddr,
    U16    *pBuffer,
    U16    u16Length
);

S16 _DECL _dvxBcDataStackRead
(
    S16BIT DevNum,
    U16    u16Channel,
    U32BIT u32MemAddr,
    U16BIT *pBuffer,
    U16BIT u16Length,
    U16BIT u16Offset
);

S16 _DECL _dvxBcGetFrameToHBuf
(
    S16BIT  DevNum,
    U16BIT  u16Channel
);

S16 _DECL _dvxBcGetMessage
(
    S16BIT  DevNum,
    U16BIT  u16Channel,
    U16BIT  u16MsgId,
    U16BIT  u16Type,
    U16BIT  bCheckingImp,
    U16BIT  bBlocking,
    U16BIT  bPurge,
    U16BIT  *pBuffer
);

S16 _DECL _dvxBcGpqClear
(
    S16BIT  DevNum,
    U16BIT  u16Channel
);

S16 _DECL _dvxBcGpqCount
(
    S16BIT  DevNum,
    U16BIT  u16Channel,
    U16BIT  *pu16Count
);

S16 _DECL _dvxBcGpqInit
(
    S16BIT  DevNum,
    U16BIT  u16Channel,
    U32BIT  u32BaseAddr,
    U32BIT  u32QueueSize
);

S16 _DECL _dvxBcGpqGetMetrics
(
    S16BIT      DevNum,
    U16BIT      u16Channel,
    U16BIT      u16Reset,
    GPQMETRIC   *pMetrics

);

S16 _DECL _dvxBcGpqRead
(
    S16BIT      DevNum,
    U16BIT      u16Channel,
    GPQENTRY32  *pGpqEntry
);

S16 _DECL _dvxBcHBufInstall
(
    S16BIT  DevNum,
    U16BIT  u16Channel,
    U32BIT  u32Size
);

S16 _DECL _dvxBcHBufUninstall
(
    S16BIT  DevNum,
    U16BIT  u16Channel
);

S16 _DECL _dvxBcHBufGetMessage
(
    S16BIT  DevNum,
    U16BIT  u16Channel,
    U16BIT  bReturnMsgId,
    U16BIT  u16Type,
    U16BIT  bBlocking,
    U16BIT  bCheckingImp,
    U32BIT  u32Size,
    U16BIT  *pBuffer,
    U32BIT  *pMsgCount
);

S16 _DECL _dvxBcHBufGetMetrics
(
    S16BIT      DevNum,
    U16BIT      u16Channel,
    U16BIT      u16Reset,
    HBUFMETRIC  *pMetrics
);

S16 _DECL _dvxBcHpqInit
(
    S16BIT  DevNum,
    U16BIT  u16Channel,
    U32BIT  u32BaseAddr,
    U32BIT  u32QueueSize
);

S16 _DECL _dvxBcLpqInit
(
    S16BIT  DevNum,
    U16BIT  u16Channel,
    U32BIT  u32BaseAddr,
    U32BIT  u32QueueSize
);

S16 _DECL _dvxBcReplayInit
(
    S16BIT DevNum,
    U16    u16Channel,
    U32    u32BaseAddr,
    U32    u32MemSize
);

S16 _DECL _dvxBcChanMuxInit
(
    S16BIT DevNum,
    U16    u16Channel,
    U32    u32MuxEnable
);

S16 _DECL _dvxBcPostLpAsyncMessage
(
    S16BIT  DevNum,
    U16BIT  u16Channel,
    U32BIT  u32Addr,
    U16BIT  u16MsgTime,
    U16BIT  u16MsgType,
    U16BIT  u16MsgId,
    BOOLEAN bMsgIrq,
    U16     *pu16Count
);

S16 _DECL _dvxBcPostHpAsyncMessage
(
    S16BIT  DevNum,
    U16BIT  u16Channel,
    U32BIT  u32Addr,
    U16BIT  u16MsgType,
    U16BIT  u16MsgId,
    BOOLEAN bMsgIrq,
    U16     *pu16Count
);

S16 _DECL _dvxBcAsyncQueueInfo
(
    S16BIT  DevNum,
    U16     u16Channel,
    U32     u32QueueType,
    ACEX_BC_ASYNC_QUEUE_INFO *psQueueInfo
);

S16 _DECL _dvxBcState
(
    S16BIT  DevNum,
    U16BIT  u16Channel,
    U16BIT  u16State
);

S16 _DECL _dvxBcSetDataBuffer
(
    S16BIT  DevNum,
    U16BIT  u16Channel,
    S16BIT  s16DataIndex,
    U16BIT  u16Size,
    U16BIT  *pBuffer,
    U16BIT  u16Offset
);

S16 _DECL _dvxBcSetMsgBuffer
(
    S16BIT  DevNum,
    U16BIT  u16Channel,
    S16BIT  s16MsgIndex,
    U16BIT  u16Size,
    U32BIT  *pBuffer
);

S16 _DECL _dvxBdReset
(
    S16BIT DevNum
);

S16 _DECL _dvxEnableTimeTagInt
(
    S16BIT DevNum,
    S16BIT mask
);

DISC_LEVEL _DECL _dvxGetDiscOut
(
    S16BIT  DevNum,
    S16BIT  Discrete
);

S16BIT _DECL _dvxGetDiscDir
(
    S16BIT  DevNum,
    S16BIT  Discrete
);

DISC_LEVEL _DECL _dvxGetDiscIn
(
    S16BIT  DevNum,
    S16BIT  Discrete
);

S16BIT _DECL _dvxSetDiscOut
(
    S16BIT      DevNum,
    S16BIT      Discrete,
    DISC_LEVEL  Level
);

S16BIT _DECL _dvxSetDiscDir
(
    S16BIT      DevNum,
    S16BIT      Discrete,
    DISC_DIR    Direction
);

S16BIT _DECL _dvxGetDiscAll
(
    S16BIT  DevNum,
    U16BIT  *Directions,
    U16BIT  *Levels
);

S16BIT _DECL _dvxSetDiscAll
(
    S16BIT  DevNum,
    U16BIT  Directions,
    U16BIT  Levels
);

S16BIT _DECL _dvxWait
(
    S16BIT  DevNum,
    U16BIT  u16Channel,
    U32BIT  Milliseconds
);

S16BIT _DECL _dvxWaitCancel
(
    S16BIT  DevNum,
    U16BIT  u16Channel
);

U16BIT _DECL _dvAxRegRead
(
    S16BIT DevNum,
    U16BIT wRegAddr,
    U16BIT wMask
);

VOID _DECL _dvAxRegWrite
(   S16BIT DevNum,
    U16BIT wRegAddr,
    U16BIT wValue,
    U16BIT wMask
);

U16BIT _DECL _dvAxMemRead
(
    S16BIT  DevNum,
    U32BIT  dwMemAddr
);

S16BIT _DECL _dvAxMemWrite
(
    S16BIT DevNum,
    U32BIT dwMemAddr,
    U16BIT wValue
);

VOID _DECL _dvxSetDevStatus
(
    S16BIT  DevNum,
    U16BIT  Status
);

VOID _DECL _dvxIOSetDevStatus
(
    S16BIT  DevNum,
    U16BIT  Status
);

S16BIT _DECL _dvxClearMemory
(
    S16 DevNum,
    U32 u32Address16,   /* 16bit address */
    U32 u32NumWds       /* number of 16 bit wds */
);

S16 _DECL _dvxGetCoupling
(
    S16                 DevNum,
    CHANNEL_COUPLING    *eCoupling,
    CHANNEL_TERMINATION *eTermination
);

S16 _DECL _dvxSetCoupling
(
    S16BIT              DevNum,
    CHANNEL_COUPLING    eCoupling,
    CHANNEL_TERMINATION eTermination
);

S16 _DECL _dvxGetAmplitude
(
    S16BIT  DevNum,
    U32BIT  *pu32Amplitude
);

S16 _DECL _dvxSetAmplitude
(
    S16BIT  DevNum,
    U32BIT  u32Amplitude
);

S16 _DECL _dvxGetBoardStatus
(
    S16 DevNum,
    U32 cmd,
    void *pdata
);

S16 _DECL _dvxMtiGetMetrics
(
   S16BIT           s16DevNum,
   ACEX_MTI_METRICS *pMtiMerics
);

S16 _DECL _dvxSetRespTimeOut
(
    S16BIT  DevNum,
    U16BIT  u16ModeMask,
    U32BIT  u32Multiple
);

S16BIT _DECL _dvxGetChannelCount
(
    S16BIT DevNum,
    CHANCOUNT_t *pChanCount
);

S16BIT _DECL _dvxBoardReset
(
    S16BIT s16DevNum,
    U32BIT u32BdComponet
);

S16 _DECL _dvxGetIRIGTx
(
    S16BIT          DevNum,
    PACE_IRIG_TX    pstructIRIG
);

S16 _DECL _dvxSetIRIGTx
(
    S16BIT          DevNum,
    ACE_IRIG_TX structIRIG
);

S16 _DECL _dvxCheckMfCapable
(
    S16BIT  DevNum,
    U16     u16Channel,
    BOOLEAN *pbMfCapable
);

S16BIT _DECL _dvxBcReplayThreadCreate
(
    S16BIT DevNum
);

VOID _DECL _dvxBcReplayIrqRelease
(
    S16BIT DevNum
);

U32BIT _DECL _dvxBcReplayDispatcher
(
    S16BIT DevNum
);

S16 _DECL _dvxBcGetReplayInfo
(
    S16BIT DevNum,
    ACEX_BC_REPLAY_STATUS *ReplayStatus
);

S16 _DECL _dvxBcReplayRaw
(
    S16BIT DevNum,
    PVOID *pReplayData,
    U32BIT u32DataLength
);

S16 _DECL _dvxBcReplayMsgDataDma
(
    S16BIT  DevNum,
    U16BIT  u16MemPage,
    U32BIT  u32MemOffset,
    CHAR   *pMemBuffer,
    U32BIT  u32MemDataLen
);

S16 _DECL _dvxBcReplayBlockOnIrq
(
    S16BIT  DevNum,
    U32BIT  *u32IrqStatus
);

AVIONIC_LEVEL _DECL _dvxGetAioOutput(S16BIT DevNum, S16BIT Channel);
AVIONIC_DIRECTION _DECL _dvxGetAioDir(S16BIT DevNum, S16BIT Channel);
AVIONIC_LEVEL _DECL _dvxGetAioInput(S16BIT DevNum, S16BIT Channel);
S16BIT _DECL _dvxSetAioOutput(S16BIT DevNum, S16BIT Channel, AVIONIC_LEVEL Level);
S16BIT _DECL _dvxSetAioDir(S16BIT DevNum, S16BIT Channel, AVIONIC_DIRECTION Direction);
S16BIT _DECL _dvxGetAioAll(S16BIT DevNum, U16BIT *Directions, U16BIT *Levels);
S16BIT _DECL _dvxSetAioAll(S16BIT DevNum, U16BIT Directions, U16BIT Levels);

/* Windows only functions.  Used for MTi mode of operation for retrieval of Ch10 data/time packets */
VOID _DECL _dvFuncAcexMTiFree(S16BIT s16DevNum);
VOID _DECL _dvFuncAcexMTiConfigure(S16BIT s16DevNum);
VOID _DECL _dvFuncAcexMTiStop(S16BIT s16DevNum);

S16BIT _DECL _dvxMTISetCh10TimePktId
(
    S16BIT DevNum,
    U16BIT u16ChannelId
);

void _DECL _ddcFseek64(FILE *pFile, S64BIT s64Offset, int origin);
S64BIT _DECL _ddcFtell64(FILE *pFile);

S16 _DECL _dvxTrgReset
(
    S16BIT  DevNum,
    U16     u16Channel
);

S16 _DECL _dvxTrgStausRead
(
    S16BIT  DevNum,
    U16     u16Channel,
    U32     *pu32Status,
    U32     u32Dwords
);

/* Discrete IO time tag feature. */
S16BIT _DECL _dvxDioTtCfg(S16BIT DevNum, DIO_TT_CFG *psDioTtCfg, void(_DECL *pfDioTtIsr)(S16BIT DevNum, U32BIT u32IntSts));
S16BIT _DECL _dvxDioTtCtl(S16BIT DevNum, U32BIT u32DioTtCtl);
S16BIT _DECL _dvxDioTtRead(S16BIT DevNum, U8BIT *pu8Data, U32BIT *pu32Bytes);

#endif /* __DEVICEX_H__ */

