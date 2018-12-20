//{{{job.name}}} JOB {{{job.account}}},
//             '{{{job.description}}}',
//             MSGCLASS=A,
//             CLASS=A,
//             MSGLEVEL=(1,1),
//             REGION=0M
/*JOBPARM SYSAFF=*
{{#job.metalCompilations}}
//*
//* Metal C {{{name}}}
//*
//         IF (RC = 0) THEN
//METAL    EXEC PGM=CCNDRVR,
//          PARM=('OPTFILE(DD:OPTIONS)', 
//         'LIST(DD:LISTOUT)')
//OPTIONS  DD  *
{{#options}}
{{.}}
{{/options}}
/*
//LISTOUT  DD  SYSOUT=*
//STEPLIB  DD  DISP=SHR,DSN=CEE.SCEERUN2
//         DD  DISP=SHR,DSN=CBC.SCCNCMP
//         DD  DISP=SHR,DSN=CEE.SCEERUN
//USERLIB  DD  DISP=SHR,DSN={{{../settings.hlq}}}.CHDR
{{#includes}}
//         DD  DISP=SHR,DSN={{{.}}}
{{/includes}}
//SYSIN    DD  DISP=SHR,DSN={{{../settings.hlq}}}.CPGM({{{name}}})
//SYSLIN   DD  DISP=SHR,DSN={{{../settings.hlq}}}.ASMPGM({{{name}}})
//SYSPRINT DD  SYSOUT=*
//         ENDIF
{{/job.metalCompilations}}
{{#job.assemblies}}
//*
//* Assemble {{{name}}}
//*
//         IF (RC = 0) THEN
//ASM{{@index}} EXEC PGM=ASMA90
//ASMAOPT  DD  *
{{#options}}
{{{.}}}
{{/options}}
//SYSADATA DD  DISP=SHR,DSN={{{../settings.hlq}}}.ADATA({{{name}}})
//SYSLIB   DD  DISP=SHR,DSN={{{../settings.hlq}}}.ASMMAC
{{#maclibs}}
//         DD  DISP=SHR,DSN={{{.}}}
{{/maclibs}}
//SYSPRINT DD  SYSOUT=*
//SYSIN    DD  DISP=SHR,DSN={{{../settings.hlq}}}.ASMPGM({{{name}}})
//SYSLIN   DD  DISP=SHR,DSN={{{../settings.hlq}}}.OBJLIB({{{name}}})
//         ENDIF
{{/job.assemblies}}
{{#job.binds}}
//*
//* Bind {{{name}}}
//*
//         IF (RC = 0) THEN
//BIND     EXEC PGM=IEWL,PARM='OPTIONS=IEWLOPT'
//IEWLOPT  DD  *
{{#options}}
{{{.}}}
{{/options}}
/*
//OBJECT   DD  DISP=SHR,DSN={{{../settings.hlq}}}.OBJLIB
//SYSLIN   DD  *
 INCLUDE OBJECT({{{name}}})
 {{#includes}}
 INCLUDE OBJECT({{.}})
 {{/includes}}
 SETOPT PARM(REUS=REFR)
 ORDER {{{name}}}(P)
 ENTRY {{{name}}}
 NAME {{{name}}}(R)
/*
//SYSLMOD  DD  DISP=SHR,DSN={{{../settings.hlq}}}.LOADLIB({{{name}}})
//SYSPRINT DD  SYSOUT=*
//         ENDIF
{{/job.binds}}
{{#job.execs}}
//*
//* Exec {{{name}}}
//*
//         IF (RC = 0) THEN
//RUN      EXEC PGM={{{name}}}{{#if parm}},
//             PARM=({{{parm}}}){{/if}}
//STEPLIB  DD  DISP=SHR,DSN={{{../settings.hlq}}}.LOADLIB
//SNAP     DD  SYSOUT=*
//SYSPRINT DD  SYSOUT=*
//SYSMDUMP DD  DUMMY
//         ENDIF
{{/job.execs}}
