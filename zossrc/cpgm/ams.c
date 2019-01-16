#include "ams.h"
#include "dcbd.h"

register FILE_CTRL *fc ASMREG("r2");

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
    WRITE(*dcb, *wpl, *buffer, rc);
    return rc;
}

int check(DECB *cpl)
{
    int rc = 0;
    CHECK(*cpl, rc)
    return rc;
}

void read(IHADCB *dcb, READ_PL *rpl, char *buffer)
{
    // NOTE(Kelosky): READ does not appear to give an RC
    int rc = 0;
    READ(*dcb, *rpl, *buffer, rc);
    // return rc;
}

int close(IHADCB *dcb)
{
    int rc = 0;
    CLOSE_PL cpl = {0};
    cpl.option = OPTION_BYTE;
    CLOSE(*dcb, cpl, rc);
    return rc;
}

int writeSync(IHADCB *dcb, char *buffer)
{
    int rc = 0;
    WRITE_PL wpl = {0};
    rc = write(dcb, &wpl, buffer);
    if (rc)
    {
        return rc;
    }

    return check(&wpl);
}

int readSync(IHADCB *dcb, char *buffer)
{
    int rc = 0;
    IO_CTRL *ioc = (IO_CTRL *)dcb;

    if (dcb->dcbdcbe)
    {
        // file control begins at DCBE address
        fc = (FILE_CTRL *)dcb->dcbdcbe;

        // if (fc->bufferCtrl) // get a record from the buffer
        // {
        // }
        // else // read into buffer
        // {

        // fixed only records until rdjfcb
        if (dcbrecf == dcb->dcbrecfm)
        {
            // NOTE(Kelosky): a call to read will set a NAB so
            // our end of data function (eodad) should be able to advance the
            // stack
            read(dcb, &ioc->decb, buffer);
            // if (fc->eod)
            // {
            //     return -1;
            //     s0c3Abend(13);
            // }
            // if (rc)
            // {
            //     s0c3Abend(15);
            //     return rc;
            // }

            rc = check(&ioc->decb);

            if (rc)
            {
                s0c3Abend(17);
                return rc;
            }
        }
        else
        {
            s0c3Abend(UNSUPPORTED_RECFM);
        }

        // }
    }
    else
    {
        s0c3Abend(DCBE_REQUIRED);
    }
}

// NOTE(Kelosky): registers 2-12 should be the same as the time
// the read/check was called.
void eodad()
{
    s0c3Abend(32);
    fc->eod = 1;
}