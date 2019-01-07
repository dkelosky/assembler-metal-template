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
int main()
{
    WTO_BUF buf = {0};

    IHADCB *sysprint = storageObtain24(sizeof(IHADCB));
    IHADCB *snapDcb = storageObtain24(sizeof(IHADCB));

    memset(sysprint, 0x00, sizeof(IHADCB));
    memcpy(sysprint, &model, sizeof(IHADCB));

    memset(snapDcb, 0x00, sizeof(IHADCB));
    memcpy(snapDcb, &model, sizeof(IHADCB));

    sysprint->dcbblksi = 132;
    sysprint->dcblrecl = 132;
    sysprint->dcbrecfm = dcbrecf + dcbrecbr; // FB
    memset(sysprint->dcbddnam, ' ', sizeof(sysprint->dcbddnam));
    strcpy(sysprint->dcbddnam, "SYSPRINT");

    snapDcb->dcbblksi = 1632;
    snapDcb->dcblrecl = 125;
    snapDcb->dcbrecfm = dcbrecv + dcbrecbr + dcbrecca; // VBA
    memset(snapDcb->dcbddnam, ' ', sizeof(snapDcb->dcbddnam));
    strcpy(snapDcb->dcbddnam, "SNAPDDDD");

    int openRc = open(sysprint);
    if (openRc)
        return openRc;
    if (dcbofopn == sysprint->dcboflgs)
        return 9;

    int snapOpenRc = open(snapDcb);
    if (snapOpenRc)
        return snapOpenRc;
    if (dcbofopn == snapDcb->dcboflgs)
        return 13;

    SNAP_HEADER header = {3, {"hey"}};
    snap(snapDcb, &header, (void *)0, (void *)16);

    char writeBuf[132] = {0};
    memset(writeBuf, ' ', 132);
    char *helloMessage = "Hello world from metal c";
    memcpy(writeBuf, helloMessage, strlen(helloMessage));
    int writeRc = writeSync(sysprint, writeBuf);

    int closeRc = close(sysprint);

    char *message = "openRc: %x, writeRc: %x, closeRc: %x";
    buf.len = sprintf(buf.msg, message, openRc, writeRc, closeRc);
    wto(&buf);
    storageRelease24(sysprint, sizeof(IHADCB));
    return 0;
}