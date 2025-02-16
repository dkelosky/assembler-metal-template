@echo off
set /P TSO_KEY=<key.txt
zowe tso send as %TSO_KEY% --data "ex %1"