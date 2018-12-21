         MACRO ,
.*
.*       DSA DSECT begin
.*
         #DSABEG
.*
DSA              DSECT ,
DSASAVE          DS    XL(SAVF4SA_LEN) Mainline save area
*
DSAREUS          DS    0D              Begin reusable area
.*
         MEND  ,                       Exit macro