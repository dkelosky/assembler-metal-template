#ifndef AMS_H
#define AMS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "z.h"
#include "dcbd.h"
#include "ihaecb.h"
#include "storage.h"
#include "ihadcbe.h"

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
        "DCBE=*-*,"                                             \
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

// TODO(Kelosky): "TYPE=J,"
#if defined(__IBM_METAL__)
#define OPEN_INPUT(dcb, plist, rc)                              \
    __asm(                                                      \
        "*                                                  \n" \
        " OPEN (%0,(INPUT)),"                                   \
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

// the residual count is the halfword, 14 bytes from the start of the status area
typedef struct
{
    unsigned char filler[14];
    short int residualCount;

} STATUS_AREA;

// must be below 16MB (see Using Data Sets publication)
typedef struct
{
    ECB ecb;
    unsigned char typeField1;
    unsigned char typeField2;
    unsigned short length;
    IHADCB *PTR32 dcb;
    char *PTR32 area;
    STATUS_AREA *PTR32 statusArea;
} DECB;

typedef DECB WRITE_PL;
typedef DECB READ_PL;

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

typedef struct
{
    DCBE dcbe;
    short ctrlLen;
    short bufferLen;
    char *buffer;
    int bufferCtrl;
    unsigned int eod : 1;
} FILE_CTRL;

typedef struct
{
    IHADCB dcb;
    DECB decb;
} IO_CTRL;

typedef OPEN_PL CLOSE_PL;

int openOutput(IHADCB *) ATTRIBUTE(amode31);
int openInput(IHADCB *) ATTRIBUTE(amode31);
int write(IHADCB *, WRITE_PL *, char *) ATTRIBUTE(amode31);
void read(IHADCB *, READ_PL *, char *) ATTRIBUTE(amode31);
int check(DECB *ecb) ATTRIBUTE(amode31);
int writeSync(IHADCB *dcb, char *) ATTRIBUTE(amode31);
int readSync(IHADCB *dcb, char *) ATTRIBUTE(amode31);
int close(IHADCB *) ATTRIBUTE(amode31);
int snap(IHADCB *, SNAP_HEADER *, void *, void *) ATTRIBUTE(amode31);
void eodad();

enum AMS_ERR
{
    UNKOWN_MODE,
    OPEN_OUTPUT_ASSERT_RC,
    OPEN_OUTPUT_ASSERT_FAIL,
    OPEN_INPUT_ASSERT_RC,
    OPEN_INPUT_ASSERT_FAIL,
    CLOSE_ASSERT_RC,
    DCBE_REQUIRED,
    UNSUPPORTED_RECFM
};

// TODO(Kelosky): dbcabend
// TODO(Kelosky): synad
// TODO(Kelosky): rdjfcb

// NODE(Kelosky): IHADCB pointer is the same as an IO_CTRL pointer.  DCBE pointer is the same as
// FILE_CTRL pointer.
static IHADCB *PTR32 newDcb(char *ddname, int lrecl, int blkSize, unsigned char recfm, char *mode)
{
    char ddnam[9] = {0};
    sprintf(ddnam, "%-8.8s", ddname);
    IO_CTRL *ioc = storageObtain24(sizeof(IO_CTRL));
    memset(ioc, 0x00, sizeof(IO_CTRL));
    IHADCB *dcb = &ioc->dcb;

    //open for write
    if (0 == strcmp(mode, "w"))
    {
        memcpy(dcb, &openWriteModel, sizeof(IHADCB));
    }
    //open for read
    else if (0 == strcmp(mode, "r"))
    {
        memcpy(dcb, &openReadModel, sizeof(IHADCB));

        // get space for DCBE + buffer
        short ctrlLen = sizeof(FILE_CTRL) + dcb->dcbblksi;
        FILE_CTRL *fc = storageObtain24(ctrlLen);
        memset(fc, 0x00, ctrlLen);

        // // init file control
        // fc->ctrlLen = ctrlLen;
        // fc->bufferLen = dcb->dcbblksi;
        // fc->buffer = (unsigned char *)fc + sizeof(DCBE);

        // fc->dcbe.dcbelen = 56;
        // memcpy(fc->dcbe.dcbeid, "DCBE", 4);

        // // retain access to DCB / file control
        // fc->dcbe.dcbeeoda = (void *)eodad;
        // dcb->dcbdcbe = &fc->dcbe;
    }
    // abend for unknown mode
    else
    {
        s0c3Abend(UNKOWN_MODE);
    }

    memcpy(dcb->dcbddnam, ddnam, sizeof(dcb->dcbddnam));
    dcb->dcblrecl = lrecl;
    dcb->dcbblksi = blkSize;
    dcb->dcbrecfm = recfm;
    return dcb;
}

static IHADCB *PTR32 newWriteDcb(char *ddname, int lrecl, int blkSize, unsigned char recfm)
{
    return newDcb(ddname, lrecl, blkSize, recfm, "w");
}

static IHADCB *PTR32 newReadDcb(char *ddname, int lrecl, int blkSize, unsigned char recfm)
{
    return newDcb(ddname, lrecl, blkSize, recfm, "r");
}

static IHADCB *openOutputAssert(char *ddname, int lrecl, int blkSize, unsigned char recfm)
{
    IHADCB *dcb = newWriteDcb(ddname, lrecl, blkSize, recfm);
    int rc = 0;
    rc = openOutput(dcb);
    if (rc)
        s0c3Abend(OPEN_OUTPUT_ASSERT_RC);
    if (!(dcbofopn & dcb->dcboflgs))
        s0c3Abend(OPEN_OUTPUT_ASSERT_FAIL);

    return dcb;
}

static IHADCB *openInputAssert(char *ddname, int lrecl, int blkSize, unsigned char recfm)
{
    IHADCB *dcb = newReadDcb(ddname, lrecl, blkSize, recfm);
    int rc = 0;
    rc = openInput(dcb);
    if (rc)
        s0c3Abend(OPEN_INPUT_ASSERT_RC);
    if (!(dcbofopn & dcb->dcboflgs))
        s0c3Abend(OPEN_INPUT_ASSERT_FAIL);
    return dcb;
}

static void closeAssert(IHADCB *dcb)
{
    int rc = close(dcb);
    if (rc)
        s0c3Abend(CLOSE_ASSERT_RC);

    // free DCBE / file control if obtained
    if (dcb->dcbdcbe)
    {
        FILE_CTRL *fc = dcb->dcbdcbe;
        storageRelease(fc, fc->ctrlLen);
    }

    storageRelease(dcb, sizeof(IO_CTRL));
}

#endif