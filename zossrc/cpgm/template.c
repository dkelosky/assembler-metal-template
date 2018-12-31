#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wto.h"
#include "storage.h"
#include "load.h"
#include "dcbd.h"
#include "ams.h"

// TODO(Kelosky): snap & read

// using default prolog
void main()
{
    IHADCB *dcb = storageObtain24(sizeof(IHADCB));
    memset(dcb, 0x00, sizeof(IHADCB));

    memset(dcb->dcbddnam, ' ', sizeof(dcb->dcbddnam));
    strcpy(dcb->dcbddnam, "SYSPRINT");

    dcb->dcbblksi = 132;
    dcb->dcblrecl = 132;
    dcb->dcbrecfm = dcbrecf + dcbrecbr;

    int openRc = open(dcb);

    char writeBuf[132] = {0};
    memset(writeBuf, ' ', 132);
    char *helloMessage = "Hello world from metal c";
    memcpy(writeBuf, helloMessage, strlen(helloMessage));
    int writeRc = writeSync(dcb, writeBuf);

    int closeRc = close(dcb);

    char *message = "openRc: %x, writeRc: %x, closeRc: %x";
    WTO_BUF buf = {0};
    buf.len = sprintf(buf.msg, message, openRc, writeRc, closeRc);
    wto(&buf);
    storageRelease24(dcb, sizeof(IHADCB));
    return;
}