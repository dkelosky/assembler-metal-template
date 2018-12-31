#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wto.h"
#include "storage.h"
#include "load.h"
#include "dcbd.h"
#include "ams.h"

// using default prolog
void main()
{
    IHADCB *dcb = storageObtain24(sizeof(IHADCB));
    memset(dcb, 0x00, sizeof(IHADCB));

    memset(dcb->dcbddnam, ' ', sizeof(dcb->dcbddnam));
    memcpy(dcb->dcbddnam, "SYSPRINT", sizeof(dcb->dcbddnam));

    dcb->dcbblksi = 132;
    dcb->dcblrecl = 132;
    dcb->dcbrecfm = dcbrecf + dcbrecbr;

    int openRc = open(dcb);

    char writeBuf[132] = "Hey from C";
    // writeSync(dcb, writeBuf);

    int closeRc = close(dcb);

    char *message = "openRc: %x, closeRc: %x";
    WTO_BUF buf = {0};
    buf.len = sprintf(buf.msg, message, openRc, closeRc);
    wto(&buf);
    storageRelease24(dcb, sizeof(IHADCB));
    return;
}