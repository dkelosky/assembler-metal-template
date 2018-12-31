#include "ams.h"

int open(IHADCB *dcb)
{
    int rc = 0;
    OPEN_PL opl = {0};
    opl.option = OPTION_BYTE;

    // NOTE(Kelosky): built by hand using this expansion:
    // DCB DDNAME=*-*,DSORG=PS,MACRF=W
    dcb->dcbbufca = 1;         // BUFCB, BUFFER POOL CONTROL BLOCK
    dcb->dcbdsrg1 = 0x40;      // DSORG, DATA SET ORGANIZATION
    dcb->dcbioba = (void *)1;  // IOBAD FOR EXCP OR RESERVED
    dcb->dcbeoda = 1;          // EODAD (END OF DATA ROUTINE ADDRESS)
    dcb->dcboflg = 0x02;       // OFLGS (OPEN FLAGS)
    dcb->dcbmacr2 = 0x20;      // MACR (MACRO FORMAT)
    dcb->dcbchcka = 1;         // CHECK OR INTERNAL QSAM SYNCHRONIZING RTN.
    dcb->dcbsyna = 1;          // SYNAD, SYNCHRONOUS ERROR RTN. (3 BYTES)
    dcb->dcbcicba = 1;         // INTERNAL ACCESS METHOD USE
    dcb->dcbeobra = 1;         // EOBR, INTERNAL ACCESS METHOD USE
    dcb->dcbeobw = (void *)1;  // EOBW, INTERNAL ACCESS METHOD USE
    dcb->dcbpoint = (void *)1; // CNTRL, NOTE, POINT

    OPEN_OUTPUT(*dcb, opl, rc);
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
