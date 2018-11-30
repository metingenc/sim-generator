/*  Data Device Corporation
 *  105 Wilbur Place
 *  Bohemia N.Y. 11716
 *  (631) 567-5600
 *
 *          AceXtreme 'C' Run Time Library
 *
 *          Copyright (c) 2008 by Data Device Corporation
 *          All Rights Reserved.
 *
 *          axdioop.c (Discrete IO operations module)
 *
 *  Created 11/13/02 KWH
 *          2008 SF+ support added
 *
 * Programmers Note:
 *  The discrete IO ports associated with a particular logical device
 *  are also associated with up to  four other devices.  These ports
 *  are common to cards that have up to four Enhanced Mini-ACE chips
 *  on them.  This must be taken into consideration when working with
 *  multiple channels on the same card while manipulating the ports.
 */

#ifndef __AXDIOOP_H__
#define __AXDIOOP_H__

#define ACEX_DISC_ACTIVE_HI     0
#define ACEX_DISC_ACTIVE_LO     1

#define ACEX_DISC_SW_CTRL       0
#define ACEX_DISC_TRGIMR_CTRL   1

#define ACEX_DISC_SEL_TRG       0
#define ACEX_DISC_SEL_IMR       1

/* discrete configuration informatio for Triggers and IMRs */
typedef struct _ACEX_DISC_CONFIG
{
    U16BIT  u16Polarity;     /* polarity in ACEX_DISC_ACTIVE_HI or ACEX_DISC_ACTIVE_LO   */
    U16BIT  u16Control;      /* control by ACEX_DISC_SW_CTRL or ACEX_DISC_TRGIMR_CTRL */
    U16BIT  u16SelTrgImr;    /* select ACEX_DISC_SEL_TRG or ACEX_DISC_SEL_IMR */
    BOOLEAN bSSFDisable;     /* TRUE if want to disable the SSF in the channel */
} ACEX_DISC_CONFIG;

/* this get/set once bit at a time. */
_EXTERN S16BIT _DECL _acexGetDiscOut(S16BIT DevNum, S16BIT Discrete);
_EXTERN S16BIT _DECL _acexGetDiscDir(S16BIT DevNum, S16BIT Discrete);
_EXTERN S16BIT _DECL _acexGetDiscIn(S16BIT DevNum, S16BIT Discrete);
_EXTERN S16BIT _DECL _acexSetDiscOut(S16BIT DevNum, S16BIT Discrete, DISC_LEVEL Level);
_EXTERN S16BIT _DECL _acexSetDiscDir(S16BIT DevNum, S16BIT Discrete, DISC_DIR Direction);

/* these get/set all the bits at once. */
_EXTERN S16BIT _DECL _acexGetDiscAll(S16BIT DevNum, U16BIT *Directions, U16BIT *Levels);
_EXTERN S16BIT _DECL _acexSetDiscAll(S16BIT DevNum, U16BIT  Directions, U16BIT  Levels);

/* additional discrete configuration for triggers and IMRs */
_EXTERN S16BIT _DECL _acexSetDiscConfigure(S16BIT s16DevNum, S16BIT s16Discrete, ACEX_DISC_CONFIG sDiscConfig);
_EXTERN S16BIT _DECL _acexClrDiscConfigure(S16BIT s16DevNum);

/* Discrete IO time tag */
_EXTERN S16BIT _DECL _acexDioTtCfg(S16BIT s16DevNum, DIO_TT_CFG *psDioCfg, void(_DECL *pfDioTtIsr)(S16BIT DevNum, U32BIT u32IntSts));
_EXTERN S16BIT _DECL _acexDioTtCtl(S16BIT s16DevNum, U32BIT u32DioTtCtl);
_EXTERN S16BIT _DECL _acexDioTtRead(S16BIT s16DevNum, U8BIT *pu8Data, U32BIT *pu32Bytes);

#endif /* __DIOOP_H__ */


