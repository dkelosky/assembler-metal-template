         MACRO ,
.*
.*       Minimum metal C entry macro
.*
.*       Restore regsters & return to caller
.*
.*       Conventions:
.*         R10 address DSA
.*         R13 save area
.*
.*       Environment:
.*         ASCENV=P
.*         AMODE64=YES
.*
.*       Requires:
.*         NAB set on entry
.*         DSA DSECT
.*         SAVER SAVF4SA DSECT
.*         Register equates
.*
         #EXIT
*
*        Exit linkage
*
         LG    R13,SAVF4SAPREV         -> caller's save area
         RETURN (14,12),,RC=(15)       Return to caller
*
         MEND  ,                       Exit macro