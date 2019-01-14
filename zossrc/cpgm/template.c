#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wto.h"
#include "storage.h"
#include "dcbd.h"
#include "ams.h"

// using default prolog
int main()
{
    WTO_BUF buf = {0};
    char inbuff[80] = {0};

    IHADCB *sysprintDcb = newDcb("SYSPRINT", 132, 132, dcbrecf + dcbrecbr, "w");
    IHADCB *snapDcb = newDcb("SNAP", 125, 1632, dcbrecv + dcbrecbr + dcbrecca, "w");
    IHADCB *inDcb = newDcb("IN", 80, 80, dcbrecf + dcbrecbr, "r");

    // open dcbs
    openOutputAssert(sysprintDcb);
    openOutputAssert(snapDcb);
    openInputAssert(inDcb);

    // snap
    SNAP_HEADER header = {3, {"hey"}};
    snap(snapDcb, &header, (void *)0, (void *)16);

    // write
    char writeBuf[132] = {0};
    memset(writeBuf, ' ', 132);
    char *helloMessage = "Hello world from metal c";
    memcpy(writeBuf, helloMessage, strlen(helloMessage));
    int writeRc = writeSync(sysprintDcb, writeBuf);

    // read
    int readRc = readSync(inDcb, inbuff);
    // char writeBuf[132] = {0};
    memset(writeBuf, ' ', 132);
    // char *helloMessage = "Hello world from metal c";
    memcpy(writeBuf, inbuff, 80);
    writeRc = writeSync(sysprintDcb, writeBuf);

    // close
    int closeSysprintRc = close(sysprintDcb);
    int closeSnapRc = close(snapDcb);
    int closeInRc = close(inDcb);

    // wto
    char *message = "writeRc: %x, closeRc: %x";
    buf.len = sprintf(buf.msg, message, writeRc, closeSysprintRc);
    wto(&buf);

    // storage for dcbs
    storageRelease24(sysprintDcb, sizeof(IHADCB));
    storageRelease24(snapDcb, sizeof(IHADCB));
    storageRelease24(inDcb, sizeof(IHADCB));

    // exit
    return 0;
}