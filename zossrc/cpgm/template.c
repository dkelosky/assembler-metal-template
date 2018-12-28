#include <stdio.h>
#include "wto.h"
#include "storage.h"
#include "load.h"

// using default prolog
void main()
{
    void *data = storageGet64(1000);
    storageFree64(data);
    char *message = "Hello World from Metal C";
    WTO_BUF buf = {0};
    buf.len = sprintf(buf.msg, message);
    wto(&buf);
    return;
}