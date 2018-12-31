#ifndef AMS_H
#define AMS_H
#include "z.h"
#include "dcbd.h"
#include "ihaecb.h"

#if defined(__IBM_METAL__)
#define OPEN_OUTPUT(dcb, plist, rc)                             \
    __asm(                                                      \
        "*                                                  \n" \
        " OPEN  (%0,(OUTPUT)),"                                 \
        "MODE=31,"                                              \
        "MF=(E,%2)                                          \n" \
        "*                                                  \n" \
        " ST    15,%1     Save RC                           \n" \
        "*                                                    " \
        : "+m"(dcb),                                            \
          "=m"(rc)                                              \
        : "m"(plist)                                            \
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
        "MF=(E,%2)                                          \n" \
        "*                                                  \n" \
        " ST    15,%1     Save RC                           \n" \
        "*                                                    " \
        : "+m"(dcb),                                            \
          "=m"(rc)                                              \
        : "m"(plist)                                            \
        : "r0", "r1", "r14", "r15");
#else
#define CLOSE(dcb, plist, rc)
#endif

#if defined(__IBM_METAL__)
#define WRITE(dcb, ecb, buf, rc)                                \
    __asm(                                                      \
        "*                                                  \n" \
        " WRITE %0,"                                            \
        "SF,"                                                   \
        "%2,"                                                   \
        "%3,"                                                   \
        "MF=E                                              \n"  \
        "*                                                  \n" \
        " ST    15,%1     Save RC                           \n" \
        "*                                                    " \
        : "+m"(ecb),                                            \
          "=m"(rc)                                              \
        : "m"(dcb),                                             \
          "m"(buf)                                              \
        : "r0", "r1", "r14", "r15");
#else
#define WRITE(dcb, ecb, buf, rc)
#endif

#if defined(__IBM_METAL__)
#define CHECK(ecb, rc)                                          \
    __asm(                                                      \
        "*                                                  \n" \
        " CHECK %0                                          \n" \
        "*                                                  \n" \
        " ST    15,%1     Save RC                           \n" \
        "*                                                    " \
        : "=m"(rc)                                              \
        : "m"(ecb)                                              \
        : "r0", "r1", "r14", "r15");
#else
#define CHECK(ecb, rc)
#endif

#define OPTION_BYTE 0X80

// NOTE(Kelosky): by hand, we're just recreating something like this:
// __asm(" OPEN,MODE=31,MF=L" : "DS"(plist));
typedef struct
{
    unsigned char option;
    unsigned char reserved[3];
    IHADCB *PTR32 dcb;
} OPEN_PL;

typedef struct {
    ECB ecb;
    unsigned char typeField1;
    unsigned char typeField2;
    short int length;
    IHADCB *PTR32 dcb;
    char *PTR32 buffer;
    unsigned char *PTR32 record;
} WRITE_PL;

typedef OPEN_PL CLOSE_PL;

int open(IHADCB *) ATTRIBUTE(amode31);
int write(IHADCB *, WRITE_PL *, char *) ATTRIBUTE(amode31);
int check(WRITE_PL *ecb) ATTRIBUTE(amode31);
int writeSync(IHADCB *dcb, char *) ATTRIBUTE(amode31);
int close(IHADCB *) ATTRIBUTE(amode31);

#endif