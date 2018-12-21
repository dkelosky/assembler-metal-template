         MACRO ,
.*
.*       Minimum metal C entry macro
.*
.*       Save regsters & restores input data
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
         #ENTRY &ROUTINE=
.*
         ENTRY &ROUTINE
&ROUTINE DS    0H
*
*        Save input regs
*
         SAVE  (14,12),,'&ROUTINE. &SYSTIME &SYSDATE' Save regs
C        USING SAVF4SA,R13             Caller's save area
*
*        Clear our DSA
*
         LG    R0,C.SAVF4SANEXT        -> Current NAB
         LGHI  R1,DSALEN               Length of our DSA
         SLGR  R15,R15                 Pad + length
         MVCL  R0,R14                  Clear our DSA
*
*        Address DSA and CONSTANT
*
         LG    R10,C.SAVF4SANEXT       -> Current NAB
         USING DSA,R10                 WTODSA addressability
*
*        Calculate NAB
*
         LG    R0,C.SAVF4SANEXT        -> Current NAB
         AGHI  R0,DSALEN               -> Next NAB
*
*        Chain save areas and set new NAB
*
         LA    R2,DSASAVE              -> Our save area
O        USING SAVF4SA,R2              Caller's save area
         STG   R13,O.SAVF4SAPREV       Save the previous save area
         STG   R0,O.SAVF4SANEXT        -> NAB
*
*        Restore input regs
*
         LMG   R14,R1,C.SAVF4SAG64RS14 -> Restore entry regs R14-R1
         DROP  C,O                     Drop named USINGs of save area
*
*        Set our save area
*
         LGR   R13,R2                  -> Save area
         USING SAVF4SA,R13             Save area addressability
*
         MEND  ,                       Exit macro