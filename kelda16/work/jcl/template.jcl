//TEMPL8$$ JOB 105300000,'ASM/BIND/RUN',MSGCLASS=A,CLASS=A,
//             MSGLEVEL=(1,1),REGION=0M
/*JOBPARM SYSAFF=*
//*
//         SET SRC=TEMPLATE
//*
//* *******************************************************************
//* A S S E M B L E
//* *******************************************************************
//*
//ASSEMBLE EXEC PGM=ASMA90
//ASMAOPT  DD  *
ADATA
RENT
MACHINE(ZSERIES-5)
LIST(133)
/*
//SYSADATA DD  DISP=SHR,DSN=KELDA16.WORK.ADATA(&SRC)          ADATAS
//SYSLIB   DD  DISP=SHR,DSN=KELDA16.WORK.ASMMAC               MACRO'S
//         DD  DISP=SHR,DSN=CAI.S910.MACLIB
//         DD  DISP=SHR,DSN=SYS1.MACLIB
//         DD  DISP=SHR,DSN=SYS1.MODGEN
//         DD  DISP=SHR,DSN=ASMA.SASMMAC2
//         DD  DISP=SHR,DSN=CBC.SCCNSAM
//         DD  DISP=SHR,DSN=TCPIP.AEZAMAC1
//SYSPRINT DD  SYSOUT=*                                       Listing
//SYSIN    DD  DISP=SHR,DSN=KELDA16.WORK.ASMPGM(&SRC)         GEN'D ASM
//SYSLIN   DD  DISP=SHR,DSN=KELDA16.WORK.OBJLIB(&SRC)         OBJECT
//*
//* *******************************************************************
//* B I N D   M O D U L E
//* *******************************************************************
//*
//         IF (RC = 0) THEN
//BIND     EXEC PGM=IEWL,PARM='OPTIONS=IEWLOPT'
//IEWLOPT  DD  *
 LIST
 MAP
 XREF
/*
//OBJECT   DD  DISP=SHR,DSN=KELDA16.WORK.OBJLIB               OBJECT
//SYSLIN   DD  *                                              LNKINC
 INCLUDE OBJECT(TEMPLATE)
 SETOPT PARM(REUS=REFR)
 ORDER TEMPLATE(P)
 ENTRY TEMPLATE
 NAME TEMPLATE(R)
/*
//SYSLMOD  DD  DISP=SHR,DSN=KELDA16.WORK.LOADLIB(&SRC)        LOAD MOD
//SYSPRINT DD  SYSOUT=*                                       Listing
//         ENDIF
//*
//* *******************************************************************
//* L I N K   M O D U L E
//* *******************************************************************
//*
//         IF (RC = 0) THEN
//RUN      EXEC PGM=&SRC,PARM=('HELLO WORLD')
//STEPLIB  DD  DISP=SHR,DSN=KELDA16.WORK.LOADLIB
//SNAP     DD  SYSOUT=*
//SYSPRINT DD  SYSOUT=*
//SYSMDUMP DD  DUMMY
//         ENDIF
