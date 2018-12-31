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

    open(dcb);

    char *message = "Hello World from Metal C";
    WTO_BUF buf = {0};
    buf.len = sprintf(buf.msg, message);
    wto(&buf);
    storageRelease24(dcb, sizeof(IHADCB));
    return;
}