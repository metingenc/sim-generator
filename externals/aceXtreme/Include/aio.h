#ifndef __AIO_H__
#define __AIO_H__

/* ========================================================================== */
/*                        FUNCTION POINTER PROTOTYPES                         */
/* ========================================================================== */

typedef struct _API_AIO_FUNCTIONS
{
    S16BIT (_DECL *aceGetAioOut)    (S16BIT DevNum, S16BIT Channel);
    S16BIT (_DECL *aceSetAioDir)    (S16BIT DevNum, S16BIT Channel, AVIONIC_DIRECTION Direction);
    S16BIT (_DECL *aceGetAioDir)    (S16BIT DevNum, S16BIT Channel);
    S16BIT (_DECL *aceGetAioIn)     (S16BIT DevNum, S16BIT Channel);
    S16BIT (_DECL *aceSetAioOut)    (S16BIT DevNum, S16BIT Channel, AVIONIC_LEVEL Level);
    S16BIT (_DECL *aceGetAioAll)    (S16BIT DevNum, U16BIT *Directions, U16BIT *Levels);
    S16BIT (_DECL *aceSetAioAll)    (S16BIT DevNum, U16BIT Directions, U16BIT Levels);
} API_AIO_FUNCTIONS;

/* ========================================================================== */
/*                        EXTERNAL FUNCTION PROTOTYPES                        */
/* ========================================================================== */
_EXTERN S16BIT _DECL aceGetAioOut(S16BIT DevNum, S16BIT Channel);
_EXTERN S16BIT _DECL aceSetAioDir(S16BIT DevNum, S16BIT Channel, AVIONIC_DIRECTION Direction);
_EXTERN S16BIT _DECL aceGetAioDir(S16BIT DevNum, S16BIT Channel);
_EXTERN S16BIT _DECL aceGetAioIn(S16BIT DevNum, S16BIT Channel);
_EXTERN S16BIT _DECL aceSetAioOut(S16BIT DevNum, S16BIT Channel, AVIONIC_LEVEL Level);
_EXTERN S16BIT _DECL aceGetAioAll(S16BIT DevNum, U16BIT *Directions, U16BIT *Levels);
_EXTERN S16BIT _DECL aceSetAioAll(S16BIT DevNum, U16BIT Directions, U16BIT Levels);

#endif
