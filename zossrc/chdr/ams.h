#ifndef AMS_H
#define AMS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "z.h"
#include "dcbd.h"
#include "ihaecb.h"
#include "storage.h"

#if defined(__IBM_METAL__)
#define DCB_WRITE_MODEL(dcbwm)                                  \
    __asm(                                                      \
        "*                                                  \n" \
        " DCB DDNAME=*-*,"                                      \
        "DSORG=PS,"                                             \
        "MACRF=W                                            \n" \
        "*                                                    " \
        : "DS"(dcbwm));
#else
#define DCB_WRITE_MODEL(dcbwm)
#endif

DCB_WRITE_MODEL(openWriteModel);

#if defined(__IBM_METAL__)
#define DCB_READ_MODEL(dcbrm)                                   \
    __asm(                                                      \
        "*                                                  \n" \
        " DCB DDNAME=*-*,"                                      \
        "DSORG=PS,"                                             \
        "MACRF=R                                            \n" \
        "*                                                    " \
        : "DS"(dcbrm));
#else
#define DCB_READ_MODEL(dcbrm)
#endif

DCB_READ_MODEL(openReadModel);

#if defined(__IBM_METAL__)
#define OPEN_OUTPUT(dcb, plist, rc)                             \
    __asm(                                                      \
        "*                                                  \n" \
        " OPEN (%0,(OUTPUT)),"                                  \
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
#define OPEN_INPUT(dcb, plist, rc)                              \
    __asm(                                                      \
        "*                                                  \n" \
        " OPEN (%0,(INPUT)),"                                   \
        "TYPE=J,"                                               \
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
#define OPEN_INPUT(dcb, plist, rc)
#endif

#if defined(__IBM_METAL__)
#define RDJFCB_INPUT(dcb, plist, rc)                            \
    __asm(                                                      \
        "*                                                  \n" \
        " RDJFCB (%0,(INPUT)),"                                 \
        "MF=(E,%2)                                          \n" \
        "*                                                  \n" \
        " ST    15,%1     Save RC                           \n" \
        "*                                                    " \
        : "+m"(dcb),                                            \
          "=m"(rc)                                              \
        : "m"(plist)                                            \
        : "r0", "r1", "r14", "r15");
#else
#define RDJFCB_INPUT(dcb, plist, rc)
#endif

#if defined(__IBM_METAL__)
#define FIND(dcb, ddname, rc)                                   \
    __asm(                                                      \
        "*                                                  \n" \
        " FIND %0,"                                             \
        "%2,"                                                   \
        "D                                                  \n" \
        "*                                                  \n" \
        " ST    15,%1     Save RC                           \n" \
        "*                                                    " \
        : "+m"(dcb),                                            \
          "=m"(rc)                                              \
        : "m"(ddname)                                           \
        : "r0", "r1", "r14", "r15");
#else
#define FIND(dcb, plist, rc)
#endif

#if defined(__IBM_METAL__)
#define CLOSE(dcb, plist, rc)                                   \
    __asm(                                                      \
        "*                                                  \n" \
        " CLOSE (%0),"                                          \
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
        "MF=E                                               \n" \
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
#define READ(dcb, ecb, buf, rc)                                 \
    __asm(                                                      \
        "*                                                  \n" \
        " READ %0,"                                             \
        "SF,"                                                   \
        "%2,"                                                   \
        "%3,"                                                   \
        "'S',"                                                  \
        "MF=E                                               \n" \
        "*                                                  \n" \
        " ST    15,%1     Save RC                           \n" \
        "*                                                    " \
        : "+m"(ecb),                                            \
          "=m"(rc)                                              \
        : "m"(dcb),                                             \
          "m"(buf)                                              \
        : "r0", "r1", "r14", "r15");
#else
#define READ(dcb, ecb, buf, rc)
#endif

#if defined(__IBM_METAL__)
#define SNAP(dcb, header, start, end, plist, rc)                \
    __asm(                                                      \
        "*                                                  \n" \
        " SNAP DCB=%1,"                                         \
        "ID=1,"                                                 \
        "STORAGE=(%2,%3),"                                      \
        "STRHDR=%4,"                                            \
        "MF=(E,%5)                                          \n" \
        "*                                                  \n" \
        " ST    15,%0     Save RC                           \n" \
        "*                                                    " \
        : "=m"(rc)                                              \
        : "m"(dcb),                                             \
          "m"(start),                                           \
          "m"(end),                                             \
          "m"(header),                                          \
          "m"(plist)                                            \
        : "r0", "r1", "r14", "r15");
#else
#define SNAP(dcb, header, start, end, plist, rc)
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


typedef struct
{
    unsigned char option;
    unsigned char reserved[3];
} RDJFCB_PL;
typedef struct
{
    ECB ecb;
    unsigned char typeField1;
    unsigned char typeField2;
    short int length;
    IHADCB *PTR32 dcb;
    char *PTR32 buffer;
    unsigned char *PTR32 record;
} WRITE_PL;

typedef struct
{
    ECB ecb;
    unsigned char typeField1;
    unsigned char typeField2;
    short int length;
    IHADCB *PTR32 dcb;
    char *PTR32 buffer;
    unsigned char *PTR32 record;
} READ_PL;

#define MAX_HEADER_LEN 100
typedef struct
{
    unsigned char len;
    char title[MAX_HEADER_LEN];
} SNAP_HEADER;

typedef struct
{
    unsigned char id;
    unsigned char flags;
    unsigned char flag2;
    unsigned char reserved;
    unsigned char sdataFlagsOne;
    unsigned char sdataFlagsTwo;
    unsigned char pdataFlags;
    unsigned char reserved2;
    IHADCB *PTR32 dcb;
    void *PTR32 tcb;
    void *list;
    SNAP_HEADER *PTR32 header;
} SNAP_PLIST;

typedef OPEN_PL CLOSE_PL;

int openOutput(IHADCB *) ATTRIBUTE(amode31);
int openInput(IHADCB *) ATTRIBUTE(amode31);
int write(IHADCB *, WRITE_PL *, char *) ATTRIBUTE(amode31);
int read(IHADCB *, READ_PL *, char *) ATTRIBUTE(amode31);
int check(WRITE_PL *ecb) ATTRIBUTE(amode31);
int writeSync(IHADCB *dcb, char *) ATTRIBUTE(amode31);
int close(IHADCB *) ATTRIBUTE(amode31);
int snap(IHADCB *, SNAP_HEADER *, void *, void *) ATTRIBUTE(amode31);

static IHADCB *PTR32 newDcb(char *ddname, int lrecl, int blkSize, unsigned char recfm, char *mode)
{
    //open for write
    if (0 == strcmp(mode, "w"))
    {
        char ddnam[9] = {0};
        sprintf(ddnam, "%-8.8s", ddname);
        IHADCB *dcb = storageObtain24(sizeof(IHADCB));
        memset(dcb, 0x00, sizeof(IHADCB));
        memcpy(dcb, &openWriteModel, sizeof(IHADCB));
        memcpy(dcb->dcbddnam, ddnam, sizeof(dcb->dcbddnam));
        dcb->dcblrecl = lrecl;
        dcb->dcbblksi = blkSize;
        dcb->dcbrecfm = recfm;
        return dcb;
    }
    //open for read
    else if (0 == strcmp(mode, "r"))
    {
        // dbcabend
        // synad
        // rdjfcb
        char ddnam[9] = {0};
        sprintf(ddnam, "%-8.8s", ddname);
        IHADCB *dcb = storageObtain24(sizeof(IHADCB));
        memset(dcb, 0x00, sizeof(IHADCB));
        memcpy(dcb, &openReadModel, sizeof(IHADCB));
        memcpy(dcb->dcbddnam, ddnam, sizeof(dcb->dcbddnam));
        dcb->dcblrecl = lrecl;
        dcb->dcbblksi = blkSize;
        dcb->dcbrecfm = recfm;
        return dcb;
    }
    // abend for unknown mode
    else
    {
        s0c3Abend(1);
    }
}

static void openOutputAssert(IHADCB *dcb)
{
    int rc = 0;
    rc = openOutput(dcb);
    if (rc)
        s0c3Abend(1);
    if (!(dcbofopn & dcb->dcboflgs))
        s0c3Abend(2);
}

static void openInputAssert(IHADCB *dcb)
{
    int rc = 0;
    rc = openInput(dcb);
    if (rc)
        s0c3Abend(1);
    if (!(dcbofopn & dcb->dcboflgs))
        s0c3Abend(2);
}

#endif