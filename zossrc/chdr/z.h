#ifndef Z_H
#define Z_H

#if defined(__IBM_METAL__)

// on z
#define ATTRIBUTE(mode) __attribute__((mode))
#define PTR32 __ptr32

#else

// off z
#define ATTRIBUTE(mode)
#define PTR32

#endif

#if defined(__IBM_METAL__)
#define S0C3(n)                                                   \
    __asm(                                                        \
        "*                                                  \n"   \
        " LLGF  0,%0      = Value passed by caller          \n"   \
        " LARL  14,*+L'*  -> Next instruction               \n"   \
        " EX    0,0(,14)  Execute myself                    \n"   \
        " DC    C'@S0C3(" #n ")' Find by '@S0C3(n)'             " \
        "*                                                    "   \
        :                                                         \
        : "m"(n)                                                  \
        : "r0", "r1", "r15");
#else
#define S0C3(n)
#endif

static void s0c3Abend(int n) { S0C3(n); }

#endif