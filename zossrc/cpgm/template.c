#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wto.h"
#include "storage.h"
#include "dcbd.h"
#include "ams.h"
#include "z.h"

// using default prolog
int main(IN_PARM parm)
{
    WTO_BUF buf = {0};
    char inbuff[80] = {0};

    IO_CTRL *sysprintIoc = openOutputAssert("SYSPRINT", 132, 132, dcbrecf + dcbrecbr);
    IO_CTRL *snapIoc = openOutputAssert("SNAP", 125, 1632, dcbrecv + dcbrecbr + dcbrecca);
    IO_CTRL *inIoc = openInputAssert("IN", 80, 80, dcbrecf); // + dcbrecbr);

    parm.data.value &= HI_BIT_MASK; // clear input parms for 64-bit reading

    IHADCB *sysprintDcb = &sysprintIoc->dcb;
    IHADCB *snapDcb = &snapIoc->dcb;
    IHADCB *inDcb = &inIoc->dcb;

    buf.len = sprintf(buf.msg, "input '%.*s'", parm.data.addr->length, parm.data.addr->parms);
    wto(&buf);

    // write
    char writeBuf[132] = {0};
    memset(writeBuf, ' ', 132);
    char *helloMessage = "Hello world from metal c";
    memcpy(writeBuf, helloMessage, strlen(helloMessage));
    int writeRc = writeSync(sysprintIoc, writeBuf);

    memset(inbuff, 0x00, 80);
    readSync(inIoc, inbuff);
    memset(writeBuf, ' ', 132);
    memcpy(writeBuf, inbuff, 80);
    writeRc = writeSync(sysprintIoc, writeBuf);

    // read
    memset(inbuff, 0x00, 80);
    readSync(inIoc, inbuff);
    memset(writeBuf, ' ', 132);
    memcpy(writeBuf, inbuff, 80);
    writeSync(sysprintIoc, writeBuf);

    // close
    closeAssert(sysprintIoc);
    closeAssert(inIoc);

    // exit
    return 0;
}