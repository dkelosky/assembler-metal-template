//{{job.name}} JOB {{job.account}},'ASM/BIND/RUN',MSGCLASS=A,CLASS=A,
//             MSGLEVEL=(1,1),REGION=0M
/*JOBPARM SYSAFF=*
//*
//         SET SRC={{program.name}}
//*
//* *******************************************************************
//* A S S E M B L E
//* *******************************************************************
//*
//ASSEMBLE EXEC PGM=ASMA90
//ASMAOPT  DD  *
{{#assemble.options}}
{{.}}
{{/assemble.options}}
/*
//SYSADATA DD  DISP=SHR,DSN={{settings.hlq}}.ADATA(&SRC)
//SYSLIB   DD  DISP=SHR,DSN={{settings.hlq}}.ASMMAC
{{#assemble.maclib}}
//         DD  DISP=SHR,DSN={{.}}
{{/assemble.maclib}}
//SYSPRINT DD  SYSOUT=*                                   
//SYSIN    DD  DISP=SHR,DSN={{settings.hlq}}.ASMPGM(&SRC)
//SYSLIN   DD  DISP=SHR,DSN={{settings.hlq}}.OBJLIB(&SRC)
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
//OBJECT   DD  DISP=SHR,DSN={{settings.hlq}}.OBJLIB 
//SYSLIN   DD  *                                    
 INCLUDE OBJECT(TEMPLATE)
 SETOPT PARM(REUS=REFR)
 ORDER TEMPLATE(P)
 ENTRY TEMPLATE
 NAME TEMPLATE(R)
/*
//SYSLMOD  DD  DISP=SHR,DSN={{settings.hlq}}.LOADLIB(&SRC)
//SYSPRINT DD  SYSOUT=*                                  
//         ENDIF
//*
//* *******************************************************************
//* L I N K   M O D U L E
//* *******************************************************************
//*
//         IF (RC = 0) THEN
//RUN      EXEC PGM=&SRC,PARM=('HELLO WORLD')
//STEPLIB  DD  DISP=SHR,DSN={{settings.hlq}}.LOADLIB
//SNAP     DD  SYSOUT=*
//SYSPRINT DD  SYSOUT=*
//SYSMDUMP DD  DUMMY
//         ENDIF
