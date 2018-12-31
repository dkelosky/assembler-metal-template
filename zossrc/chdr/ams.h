#ifndef AMS_H
#define AMS_H
#include "z.h"
#include "dcbd.h"

#if defined(__IBM_METAL__)
#define OPEN_OUTPUT(dcb, plist)                                 \
    __asm(                                                      \
        "*                                                  \n" \
        " OPEN  (%0,(OUTPUT)),"                                 \
        "MODE=31,"                                              \
        "MF=(E,%1)                                          \n" \
        "*                                                    " \
        : "+m"(dcb)                                             \
        : "m"(plist)                                            \
        : "r0", "r1", "r14", "r15");
#else
#define OPEN_OUTPUT(dcb, plist)
#endif

#define OPEN_FLAG 0X80

// NOTE(Kelosky): recreating something like this:
// __asm(" OPEN,MODE=31,MF=L" : "DS"(plist));
typedef struct
{
    unsigned char option;
    unsigned char reserved[3];
    IHADCB *PTR32 dcb;
} OPEN_PL;

void open(IHADCB *dcb) ATTRIBUTE(amode31);

#endif