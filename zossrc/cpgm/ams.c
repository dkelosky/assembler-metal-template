#include "ams.h"
#include "dcbd.h"

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

int check(CHECK_PL *cpl)
{
    int rc = 0;
    CHECK(*cpl, rc)
    return rc;
}

int read(IHADCB *dcb, READ_PL *rpl, char *buffer)
{
    int rc = 0;
    READ(*dcb, *rpl, *buffer, rc);
    return rc;
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
    READ_PL rpl = {0};
    rc = read(dcb, &rpl, buffer);
    if (rc)
    {
        return rc;
    }

    return check(&rpl);
}