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

    IHADCB *sysprintDcb = newDcb("SYSPRINT", 132, 132, dcbrecf + dcbrecbr, "w");
    IHADCB *snapDcb = newDcb("SNAP", 125, 1632, dcbrecv + dcbrecbr + dcbrecca, "w");
    IHADCB *inDcb = newDcb("IN", 80, 80, dcbrecf + dcbrecbr, "r");

    openOutputAssert(sysprintDcb);
    openOutputAssert(snapDcb);
    openInputAssert(inDcb);

    SNAP_HEADER header = {3, {"hey"}};
    snap(snapDcb, &header, (void *)0, (void *)16);

    char writeBuf[132] = {0};
    memset(writeBuf, ' ', 132);
    char *helloMessage = "Hello world from metal c";
    memcpy(writeBuf, helloMessage, strlen(helloMessage));
    int writeRc = writeSync(sysprintDcb, writeBuf);

    int closeRc = close(sysprintDcb);
    int closeSnapRc = close(snapDcb);

    char *message = "writeRc: %x, closeRc: %x";
    buf.len = sprintf(buf.msg, message, writeRc, closeRc);
    wto(&buf);

    storageRelease24(sysprintDcb, sizeof(IHADCB));
    storageRelease24(snapDcb, sizeof(IHADCB));
    return 0;
}