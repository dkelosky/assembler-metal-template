#include "ams.h"
#include "dcbd.h"

register FILE_CTRL *fc ASMREG("r2");

static IO_CTRL *PTR32 newIoCtrl()
{
    IO_CTRL *ioc = storageObtain24(sizeof(IO_CTRL));
    memset(ioc, 0x00, sizeof(IO_CTRL));
    return ioc;
}

static void setDcbInfo(IHADCB *PTR32 dcb, char *ddname, int lrecl, int blkSize, unsigned char recfm)
{
    char ddnam[9] = {0};
    sprintf(ddnam, "%-8.8s", ddname);
    memcpy(dcb->dcbddnam, ddnam, sizeof(dcb->dcbddnam));
    dcb->dcblrecl = lrecl;
    dcb->dcbblksi = blkSize;
    dcb->dcbrecfm = recfm;
}

static void setDcbDcbe(IHADCB *PTR32 dcb)
{
    // get space for DCBE + buffer
    short ctrlLen = sizeof(FILE_CTRL) + dcb->dcbblksi;
    FILE_CTRL *fc = storageObtain31(ctrlLen);
    memset(fc, 0x00, ctrlLen);

    // init file control
    fc->ctrlLen = ctrlLen;
    fc->bufferLen = dcb->dcbblksi;
    fc->buffer = (unsigned char *)fc + sizeof(DCBE);

    // init DCBE
    fc->dcbe.dcbelen = 56;
    memcpy(fc->dcbe.dcbeid, "DCBE", 4);

    // retain access to DCB / file control
    fc->dcbe.dcbeeoda = (void *)eodad;
    dcb->dcbdcbe = fc;
}

static IO_CTRL *PTR32 newWriteIoCtrl(char *ddname, int lrecl, int blkSize, unsigned char recfm)
{
    IO_CTRL *ioc = newIoCtrl();
    IHADCB *dcb = &ioc->dcb;
    memcpy(dcb, &openWriteModel, sizeof(IHADCB));
    setDcbInfo(dcb, ddname, lrecl, blkSize, recfm);
    return ioc;
}

static IO_CTRL *PTR32 newReadIoCtrl(char *ddname, int lrecl, int blkSize, unsigned char recfm)
{
    IO_CTRL *ioc = newIoCtrl();
    IHADCB *dcb = &ioc->dcb;
    memcpy(dcb, &openReadModel, sizeof(IHADCB));
    setDcbInfo(dcb, ddname, lrecl, blkSize, recfm);
    setDcbDcbe(dcb);
    return ioc;
}

IO_CTRL *openOutputAssert(char *ddname, int lrecl, int blkSize, unsigned char recfm)
{
    IO_CTRL *ioc = newWriteIoCtrl(ddname, lrecl, blkSize, recfm);
    IHADCB *dcb = &ioc->dcb;
    int rc = 0;
    rc = openOutput(dcb);
    if (rc)
        s0c3Abend(OPEN_OUTPUT_ASSERT_RC);
    if (!(dcbofopn & dcb->dcboflgs))
        s0c3Abend(OPEN_OUTPUT_ASSERT_FAIL);

    return ioc;
}

IO_CTRL *openInputAssert(char *ddname, int lrecl, int blkSize, unsigned char recfm)
{
    IO_CTRL *ioc = newReadIoCtrl(ddname, lrecl, blkSize, recfm);
    IHADCB *dcb = &ioc->dcb;
    int rc = 0;
    rc = openInput(dcb);
    if (rc)
        s0c3Abend(OPEN_INPUT_ASSERT_RC);
    if (!(dcbofopn & dcb->dcboflgs))
        s0c3Abend(OPEN_INPUT_ASSERT_FAIL);
    return ioc;
}

void closeAssert(IO_CTRL *ioc)
{
    IHADCB *dcb = &ioc->dcb;
    int rc = close(dcb);
    if (rc)
        s0c3Abend(CLOSE_ASSERT_RC);

    // free DCBE / file control if obtained
    if (dcb->dcbdcbe)
    {
        FILE_CTRL *fc = dcb->dcbdcbe;
        storageRelease(fc, fc->ctrlLen);
    }

    storageRelease(ioc, sizeof(IO_CTRL));
}

int openOutput(IHADCB *dcb)
{
    int rc = 0;
    OPEN_PL opl = {0};
    opl.option = OPTION_BYTE;

    OPEN_OUTPUT(*dcb, opl, rc);
    return rc;
}

int openInput(IHADCB *dcb)
{
    int rc = 0;
    OPEN_PL opl = {0};
    opl.option = OPTION_BYTE;

    OPEN_INPUT(*dcb, opl, rc);
    return rc;
}

int snap(IHADCB *dcb, SNAP_HEADER *header, void *start, void *end)
{
    int rc = 0;
    SNAP_PLIST plist = {0};
    SNAP(*dcb, *header, *(unsigned char *)start, *(unsigned char *)end, plist, rc);
    return rc;
}

int write(IHADCB *dcb, WRITE_PL *wpl, char *buffer)
{
    int rc = 0;
    memset(wpl, 0x00, sizeof(WRITE_PL));
    WRITE(*dcb, *wpl, *buffer, rc);
    return rc;
}

// NOTE(Kelosky): simple function that is non inline so that when
// it is called, NAB will be set.
void forceNab() ATTRIBUTE(noinline);
void forceNab()
{
    return;
}

int check(DECB *cpl)
{
    int rc = 0;
    forceNab();
    CHECK(*cpl, rc)
    rc = 0;
    return rc;
}

void read(IHADCB *dcb, READ_PL *rpl, char *buffer)
{
    // NOTE(Kelosky): READ does not appear to give an RC
    int rc = 0;
    memset(rpl, 0x00, sizeof(READ_PL));
    READ(*dcb, *rpl, *buffer, rc);
}

int close(IHADCB *dcb)
{
    int rc = 0;
    CLOSE_PL cpl = {0};
    cpl.option = OPTION_BYTE;
    CLOSE(*dcb, cpl, rc);
    return rc;
}

int writeSync(IO_CTRL *ioc, char *buffer)
{
    int rc = 0;
    WRITE_PL *wpl = &ioc->decb;
    rc = write(&ioc->dcb, wpl, buffer);
    if (rc)
    {
        return rc;
    }

    return check(&ioc->decb);
}

int readSync(IO_CTRL *ioc, char *buffer)
{
    int rc = 0;
    READ_PL *rpl = &ioc->decb;
    IHADCB *dcb = &ioc->dcb;

    if (dcb->dcbdcbe)
    {
        // file control begins at DCBE address
        fc = dcb->dcbdcbe;

        // fixed only records until rdjfcb
        if (dcbrecf == dcb->dcbrecfm)
        {
            // TODO(Kelosky): skip read and use buffer for blocked records
            // right now, for non-blocked, there is no buffer
            // read(dcb, rpl, fc->buffer);
            read(dcb, rpl, buffer);

            rc = check(rpl);
            if (fc->eod)
            {
                return -1;
            }
            if (rc)
            {
                return rc;
            }

            // TODO(Kelosky): offset into buffer
            // memcpy(buffer, fc->buffer, dcb->dcblrecl);
        }
        else
        {
            s0c3Abend(UNSUPPORTED_RECFM);
        }
    }
    else
    {
        s0c3Abend(DCBE_REQUIRED);
    }
}

// NOTE(Kelosky): registers 2-13 should be the same as the time
// the read/check was called for non-VSAM end of data exit.
void eodad()
{
    fc->eod = 1;
}