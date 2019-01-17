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

    void *data = storageGet64(8192);
    storageFree64(data);

    IHADCB *sysprintDcb = openOutputAssert("SYSPRINT", 132, 132, dcbrecf + dcbrecbr);
    IHADCB *snapDcb = openOutputAssert("SNAP", 125, 1632, dcbrecv + dcbrecbr + dcbrecca);
    IHADCB *inDcb = openInputAssert("IN", 80, 80, dcbrecf); // + dcbrecbr);

    // snap
    SNAP_HEADER header = {3, {"hey"}};
    snap(snapDcb, &header, (void *)0, (void *)16);

    // write
    char writeBuf[132] = {0};
    memset(writeBuf, ' ', 132);
    char *helloMessage = "Hello world from metal c";
    memcpy(writeBuf, helloMessage, strlen(helloMessage));
    int writeRc = writeSync(sysprintDcb, writeBuf);

    int readRc = 0;
        // read

    memset(inbuff, 0x00, 80);
    readRc = readSync(inDcb, inbuff);
    memset(writeBuf, ' ', 132);
    memcpy(writeBuf, inbuff, 80);
    writeRc = writeSync(sysprintDcb, writeBuf);

    // wto
    FILE_CTRL *fc;
    fc = (FILE_CTRL *)inDcb->dcbdcbe;
    buf.len = sprintf(buf.msg, "hello world %x", fc->eod);
    wto(&buf);

    // read
    memset(inbuff, 0x00, 80);
    readRc = readSync(inDcb, inbuff);
    memset(writeBuf, ' ', 132);
    memcpy(writeBuf, inbuff, 80);
    writeRc = writeSync(sysprintDcb, writeBuf);

    // wto
    fc = (FILE_CTRL *)inDcb->dcbdcbe;
    buf.len = sprintf(buf.msg, "hello world %x", fc->eod);
    wto(&buf);

    // close
    closeAssert(sysprintDcb);
    closeAssert(snapDcb);
    closeAssert(inDcb);

    // exit
    return 0;
}