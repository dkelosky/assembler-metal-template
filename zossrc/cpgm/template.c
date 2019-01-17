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

    IO_CTRL *sysprintIoc = openOutputAssert("SYSPRINT", 132, 132, dcbrecf + dcbrecbr);
    IO_CTRL *snapIoc = openOutputAssert("SNAP", 125, 1632, dcbrecv + dcbrecbr + dcbrecca);
    IO_CTRL *inIoc = openInputAssert("IN", 80, 80, dcbrecf); // + dcbrecbr);

    IHADCB *sysprintDcb = &sysprintIoc->dcb;
    IHADCB *snapDcb = &snapIoc->dcb;
    IHADCB *inDcb = &inIoc->dcb;

    buf.len = sprintf(buf.msg, "open");
    wto(&buf);

    // write
    char writeBuf[132] = {0};
    memset(writeBuf, ' ', 132);
    char *helloMessage = "Hello world from metal c";
    memcpy(writeBuf, helloMessage, strlen(helloMessage));
    int writeRc = writeSync(sysprintIoc, writeBuf);

    int readRc = 0;
    // read

    buf.len = sprintf(buf.msg, "write");
    wto(&buf);

    memset(inbuff, 0x00, 80);
    readRc = readSync(inIoc, inbuff);
    memset(writeBuf, ' ', 132);
    memcpy(writeBuf, inbuff, 80);
    writeRc = writeSync(sysprintIoc, writeBuf);

    // wto
    FILE_CTRL *fc;
    fc = inDcb->dcbdcbe;
    buf.len = sprintf(buf.msg, "hello world %x", fc->eod);
    wto(&buf);

    // read
    memset(inbuff, 0x00, 80);
    readRc = readSync(inIoc, inbuff);
    memset(writeBuf, ' ', 132);
    memcpy(writeBuf, inbuff, 80);
    writeRc = writeSync(sysprintIoc, writeBuf);

    // wto
    fc = inDcb->dcbdcbe;
    buf.len = sprintf(buf.msg, "hello world %x", fc->eod);
    wto(&buf);

    // snap
    SNAP_HEADER header = {3, {"hey"}};
    snap(snapDcb, &header, fc, (unsigned char *)fc + sizeof(FILE_CTRL));

    // close
    closeAssert(sysprintIoc);
    closeAssert(snapIoc);
    closeAssert(inIoc);

    // exit
    return 0;
}