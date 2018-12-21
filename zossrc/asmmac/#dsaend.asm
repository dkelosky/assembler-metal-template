         MACRO ,
.*
.*       DSA DSECT end
.*
         #DSAEND
.*
                 ORG   ,               Reset to largest
                 DS    0D              Alignment
DSALEN           EQU   *-DSA           Max length of DSA DSECT
.*
         MEND  ,                       Exit macro