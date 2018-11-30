#ifndef __DIO_H__
#define __DIO_H__

/* ========================================================================== */
/*                        FUNCTION POINTER PROTOTYPES                         */
/* ========================================================================== */

typedef struct _API_DIO_FUNCTIONS
{
     S16BIT (_DECL *aceGetDiscOut)      (S16BIT DevNum, S16BIT Discrete);
     S16BIT (_DECL *aceGetDiscDir)      (S16BIT DevNum, S16BIT Discrete);
     S16BIT (_DECL *aceGetDiscIn)       (S16BIT DevNum, S16BIT Discrete);
     S16BIT (_DECL *aceSetDiscOut)      (S16BIT DevNum, S16BIT Discrete, DISC_LEVEL Level);
     S16BIT (_DECL *aceSetDiscDir)      (S16BIT DevNum, S16BIT Discrete, DISC_DIR Direction);
     S16BIT (_DECL *aceGetDiscAll)      (S16BIT DevNum, U16BIT *Directions, U16BIT *Levels);
     S16BIT (_DECL *aceSetDiscAll)      (S16BIT DevNum, U16BIT  Directions, U16BIT  Levels);

     S16BIT (_DECL *acexSetDiscConfigure)  (S16BIT s16DevNum, S16BIT s16Discrete, ACEX_DISC_CONFIG sDiscConfig);
     S16BIT (_DECL *acexClrDiscConfigure)  (S16BIT s16DevNum);

     S16BIT (_DECL *acexDioTtCfg)  (S16BIT s16DevNum, DIO_TT_CFG *psDioCfg, void(_DECL *pfDioTtIsr)(S16BIT DevNum, U32BIT u32IntSts));
     S16BIT (_DECL *acexDioTtCtl)  (S16BIT s16DevNum, U32BIT u32DioTtCtl);
     S16BIT (_DECL *acexDioTtRead)  (S16BIT s16DevNum, U8BIT *pu8Data, U32BIT *pu32Bytes);

} API_DIO_FUNCTIONS;

/* ========================================================================== */
/*                        EXTERNAL FUNCTION PROTOTYPES                        */
/* ========================================================================== */
_EXTERN S16BIT _DECL aceGetDiscOut(S16BIT DevNum, S16BIT Discrete);
_EXTERN S16BIT _DECL aceSetDiscDir(S16BIT DevNum, S16BIT Discrete, DISC_DIR Direction);
_EXTERN S16BIT _DECL aceGetDiscDir(S16BIT DevNum, S16BIT Discrete);
_EXTERN S16BIT _DECL aceGetDiscIn(S16BIT DevNum, S16BIT Discrete);
_EXTERN S16BIT _DECL aceSetDiscOut(S16BIT DevNum, S16BIT Discrete, DISC_LEVEL Level);
_EXTERN S16BIT _DECL aceGetDiscAll(S16BIT DevNum, U16BIT *Directions, U16BIT *Levels);
_EXTERN S16BIT _DECL aceSetDiscAll(S16BIT DevNum, U16BIT  Directions, U16BIT  Levels);
_EXTERN S16BIT _DECL acexSetDiscConfigure(S16BIT s16DevNum, S16BIT s16Discrete, ACEX_DISC_CONFIG sDiscConfig);
_EXTERN S16BIT _DECL acexClrDiscConfigure(S16BIT s16DevNum);
_EXTERN S16BIT _DECL acexDioTtCfg(S16BIT s16DevNum, DIO_TT_CFG *psDioCfg, void(_DECL *pfDioTtIsr)(S16BIT DevNum, U32BIT u32IntSts));
_EXTERN S16BIT _DECL acexDioTtCtl(S16BIT s16DevNum, U32BIT u32DioTtCtl);
_EXTERN S16BIT _DECL acexDioTtRead(S16BIT s16DevNum, U8BIT *pu8Data, U32BIT *pu32Bytes);

#endif
