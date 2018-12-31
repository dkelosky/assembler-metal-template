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
    memset(dcb->dcbddnam, ' ', sizeof(dcb->dcbddnam));
    strcpy(dcb->dcbddnam, "SYSPRINT");
    dcb->dcbblksi = 80;
    dcb->dcblrecl = 80;
    dcb->dcbrecfm = dcbrecf + dcbrecbr;

    int openRc = open(dcb);

    int closeRc = close(dcb);

    char *message = "openRc: %x, closeRc: %x";
    WTO_BUF buf = {0};
    buf.len = sprintf(buf.msg, message, openRc, closeRc);
    wto(&buf);
    storageRelease24(dcb, sizeof(IHADCB));
    return;
}