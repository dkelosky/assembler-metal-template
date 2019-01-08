#include "ams.h"
#include "dcbd.h"

int open(IHADCB *dcb)
{
    int rc = 0;
    OPEN_PL opl = {0};
    opl.option = OPTION_BYTE;

    OPEN_OUTPUT(*dcb, opl, rc);
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
    // NOTE(Kelosky): first item in WPL is ECB
    WRITE(*dcb, *wpl, *buffer, rc);
    return rc;
}

int check(WRITE_PL *wpl)
{
    int rc = 0;
    // NOTE(Kelosky): first item in WPL is ECB
    CHECK(*wpl, rc)
    return rc;
}

int read(IHADCB *dcb)
{
    dcb->dcbbfaln = 0x84;
    dcb->dcbmacr1 = 0x20; // MACR (MACRO FORMAT)
    dcb->dcbmacr2 = 0x00; // MACR (MACRO FORMAT)
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