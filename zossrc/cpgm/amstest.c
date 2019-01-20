#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wto.h"
#include "storage.h"
#include "dcbd.h"
#include "ams.h"
#include "z.h"

int main()
{
    WTO_BUF buf = {0};
    char inbuff[80] = {0};
    char writeBuf[132] = {0};

    IO_CTRL *sysprintIoc = openOutputAssert("SYSPRINT", 132, 132, dcbrecf + dcbrecbr);
    IO_CTRL *inIoc = openInputAssert("IN", 80, 80, dcbrecf);

    while (0 == readSync(inIoc, inbuff))
    {
        memset(writeBuf, ' ', 132);
        memcpy(writeBuf, inbuff, 80);
        writeSync(sysprintIoc, writeBuf);
    }

    closeAssert(sysprintIoc);
    closeAssert(inIoc);

    return 0;
}