#ifndef LOAD_HY
#define LOAD_HY
#include <stdio.h>

// z/OS LOAD
#if defined(__IBM_METAL__)
#define LOAD(ep, name)                                          \
    __asm(                                                      \
        "*                                                  \n" \
        " LOAD EPLOC=%1,"                                       \
        "ERRET=*+4+4                                        \n" \
        " ST  0,%0        -> Save EP                        \n" \
        "*                                                    " \
        : "=m"(ep)                                              \
        : "m"(name)                                             \
        : "r0", "r1", "r14", "r15");
#else
#define LOAD(ep, name)
#endif

// z/OS DELETE
#if defined(__IBM_METAL__)
#define DELETE(name)                                            \
    __asm(                                                      \
        "*                                                  \n" \
        " DELETE EPLOC=%0                                   \n" \
        "*                                                    " \
        :                                                       \
        : "m"(name)                                             \
        : "r0", "r1", "r14", "r15");
#else
#define DELETE(name)
#endif


// load routine
static void *__ptr32 loadModule(const char *name)
{
    char tempName[9];
    void *__ptr32 ep = NULL;
    sprintf(tempName, "%-8.8s", name);

    LOAD(ep, tempName);

    return ep;
}

// delete routine
static void deleteModule(const char *name)
{
    char tempName[9];
    sprintf(tempName, "%-8.8s", name);

    DELETE(tempName);
}

#endif