#ifndef AMS_H
#define AMS_H
#include "z.h"
#include "dcbd.h"

#if defined(__IBM_METAL__)
#define OPEN_OUTPUT(dcb, plist, rc)                             \
    __asm(                                                      \
        "*                                                  \n" \
        " OPEN  (%0,(OUTPUT)),"                                 \
        "MODE=31,"                                              \
        "MF=(E,%1)                                          \n" \
        "*                                                  \n" \
        " ST    15,%2     Save RC                           \n" \
        "*                                                    " \
        : "+m"(dcb)                                             \
        : "m"(plist),                                           \
          "m"(rc)                                               \
        : "r0", "r1", "r14", "r15");
#else
#define OPEN_OUTPUT(dcb, plist, rc)
#endif

#if defined(__IBM_METAL__)
#define CLOSE(dcb, plist, rc)                                   \
    __asm(                                                      \
        "*                                                  \n" \
        " CLOSE  (%0),"                                         \
        "MODE=31,"                                              \
        "MF=(E,%1)                                          \n" \
        "*                                                  \n" \
        " ST    15,%2     Save RC                           \n" \
        "*                                                    " \
        : "+m"(dcb)                                             \
        : "m"(plist),                                           \
          "m"(rc)                                               \
        : "r0", "r1", "r14", "r15");
#else
#define CLOSE(dcb, plist, rc)
#endif

#define OPTION_BYTE 0X80

// NOTE(Kelosky): recreating something like this:
// __asm(" OPEN,MODE=31,MF=L" : "DS"(plist));
typedef struct
{
    unsigned char option;
    unsigned char reserved[3];
    IHADCB *PTR32 dcb;
} OPEN_PL;

typedef OPEN_PL CLOSE_PL;

int open(IHADCB *dcb) ATTRIBUTE(amode31);
int close(IHADCB *dcb) ATTRIBUTE(amode31);

#endif