#ifndef __TEST_H__
#define __TEST_H__

/* ========================================================================== */
/*                        FUNCTION POINTER PROTOTYPES                         */
/* ========================================================================== */
typedef struct _API_TEST_FUNCTIONS
{
    S16BIT (_DECL *aceTestRegisters)        (S16BIT DevNum, TESTRESULT *pTest);
    S16BIT (_DECL *aceTestMemory)           (S16BIT DevNum, TESTRESULT *pTest, U16BIT wValue);
    S16BIT (_DECL *aceTestIrqs)             (S16BIT DevNum, TESTRESULT *pTest);
    S16BIT (_DECL *aceTestLoopBack)         (S16BIT DevNum, TESTRESULT *pTest);
    S16BIT (_DECL *aceTestProtocol)         (S16BIT DevNum, TESTRESULT *pTest);
    S16BIT (_DECL *aceTestVectors)          (S16BIT DevNum, TESTRESULT *pTest, char *pFileName);
    S16BIT (_DECL *aceTestConfigure)        (S16BIT DevNum, U32BIT dwOptions);
    S16BIT (_DECL *aceTestVectorsStatic)    (S16BIT DevNum, TESTRESULT *pTest);
    S16BIT (_DECL *aceTestLoopBackInt)      (S16BIT DevNum, TESTRESULT *pTest);
    S16BIT (_DECL *aceTestEBRLoopBack)      (S16BIT DevNum, TESTRESULT *pTest, U16BIT wHubNumTx, U16BIT wHubNumRx);
} API_TEST_FUNCTIONS;

/* ========================================================================== */
/*                        EXTERNAL FUNCTION PROTOTYPES                        */
/* ========================================================================== */
_EXTERN S16BIT _DECL aceTestRegisters(S16BIT DevNum, TESTRESULT *pTest);
_EXTERN S16BIT _DECL aceTestMemory(S16BIT DevNum, TESTRESULT *pTest, U16BIT wValue);
_EXTERN S16BIT _DECL aceTestIrqs(S16BIT DevNum, TESTRESULT *pTest);
_EXTERN S16BIT _DECL aceTestLoopBack(S16BIT DevNum, TESTRESULT *pTest);
_EXTERN S16BIT _DECL aceTestProtocol(S16BIT DevNum, TESTRESULT *pTest);
_EXTERN S16BIT _DECL aceTestVectors(S16BIT DevNum, TESTRESULT *pTest, char *pFileName);
_EXTERN S16BIT _DECL aceTestConfigure(S16BIT DevNum, U32BIT dwOptions);
_EXTERN S16BIT _DECL aceTestVectorsStatic(S16BIT DevNum, TESTRESULT *pTest);
_EXTERN S16BIT _DECL aceTestLoopBackInt(S16BIT DevNum, TESTRESULT *pTest);
_EXTERN S16BIT _DECL aceTestEBRLoopBack(S16BIT DevNum, TESTRESULT *pTest, U16BIT wHubNumTx, U16BIT wHubNumRx);

#endif
