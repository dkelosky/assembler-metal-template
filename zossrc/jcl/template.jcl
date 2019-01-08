//{{{settings.name}}} JOB {{{settings.account}}},
//             '{{{settings.description}}}',
//             MSGCLASS={{{settings.messageClass}}},
//             CLASS={{{settings.jobClass}}},
//             MSGLEVEL=(1,1),
//             REGION=0M
/*JOBPARM SYSAFF=*
{{#each job.compile.sources}}
//*
//* Metal C {{{@key}}}
//*
//         IF (RC = 0) THEN
//MTL{{@index}} EXEC PGM=CCNDRVR,
//          PARM=('OPTFILE(DD:OPTIONS)', 
//         'LIST(DD:LISTOUT)')
//OPTIONS  DD  *
{{!-- if options at this object level, use them  --}}
{{#if options}}
{{#each options}}
{{{.}}}
{{/each}}
{{!-- else use options at the higher context level  --}}
{{else}}
{{#each ../job.compile.options}}
{{{.}}}
{{/each}}
{{/if}}
/*
//LISTOUT  DD  SYSOUT=*
//STEPLIB  DD  DISP=SHR,DSN=CEE.SCEERUN2
//         DD  DISP=SHR,DSN=CBC.SCCNCMP
//         DD  DISP=SHR,DSN=CEE.SCEERUN
//USERLIB  DD  DISP=SHR,DSN={{{../settings.hlq}}}.CHDR
{{#if includes}}
{{#each includes}}
//         DD  DISP=SHR,DSN={{{.}}}
{{/each}}
{{else}}
{{#each ../job.compile.includes}}
//         DD  DISP=SHR,DSN={{{.}}}
{{/each}}
{{/if}}
//SYSIN    DD  DISP=SHR,DSN={{{../settings.hlq}}}.CPGM({{{@key}}})
//SYSLIN   DD  DISP=SHR,DSN={{{../settings.hlq}}}.ASMPGM({{{@key}}})
//SYSPRINT DD  SYSOUT=*
//         ENDIF
{{/each}}
{{#each job.assemble.sources}}
//*
//* Assemble {{{@key}}}
//*
//         IF (RC = 0) THEN
//ASM{{@index}} EXEC PGM=ASMA90
//ASMAOPT  DD  *
{{!-- if options at this object level, use them  --}}
{{#if options}}
{{#each options}}
{{{.}}}
{{/each}}
{{!-- else use options at the higher context level  --}}
{{else}}
{{#each ../job.assemble.options}}
{{{.}}}
{{/each}}
{{/if}}
/*
//SYSADATA DD  DISP=SHR,DSN={{{../settings.hlq}}}.ADATA({{{@key}}})
//SYSLIB   DD  DISP=SHR,DSN={{{../settings.hlq}}}.ASMMAC
{{#if includes}}
{{#each includes}}
//         DD  DISP=SHR,DSN={{{.}}}
{{/each}}
{{else}}
{{#each ../job.assemble.includes}}
//         DD  DISP=SHR,DSN={{{.}}}
{{/each}}
{{/if}}
//SYSPRINT DD  SYSOUT=*
//SYSIN    DD  DISP=SHR,DSN={{{../settings.hlq}}}.ASMPGM({{{@key}}})
//SYSLIN   DD  DISP=SHR,DSN={{{../settings.hlq}}}.OBJLIB({{{@key}}})
//         ENDIF
{{/each}}
{{#each job.bind.sources}}
//*
//* Bind {{{@key}}}
//*
//         IF (RC = 0) THEN
//BND{{@index}}    EXEC PGM=IEWL,PARM='OPTIONS=IEWLOPT'
//IEWLOPT  DD  *
{{!-- if options at this object level, use them  --}}
{{#if options}}
{{#each options}}
{{{.}}}
{{/each}}
{{!-- else use options at the higher context level  --}}
{{else}}
{{#each ../job.bind.options}}
{{{.}}}
{{/each}}
{{/if}}
/*
//OBJECT   DD  DISP=SHR,DSN={{{../settings.hlq}}}.OBJLIB
//SYSLIN   DD  *
 INCLUDE OBJECT({{{@key}}})
 {{#if includes}}
 {{#each includes}}
 INCLUDE OBJECT({{{.}}})
 {{/each}}
 {{else}}
 {{#each ../job.bind.includes}}
 INCLUDE OBJECT({{{.}}})
 {{/each}}
 {{/if}}
 SETOPT PARM(REUS=REFR)
 ORDER {{{@key}}}(P)
 ENTRY {{{@key}}}
 NAME {{{@key}}}(R)
/*
//SYSLMOD  DD  DISP=SHR,DSN={{{../settings.hlq}}}.LOADLIB({{{@key}}})
//SYSPRINT DD  SYSOUT=*
//         ENDIF
{{/each}}
{{#each job.execute.sources}}
//*
//* Execute {{{@key}}}
//*
//         IF (RC = 0) THEN
//RUN      EXEC PGM={{{@key}}}{{#if options}},
//             PARM=({{{options}}}){{/if}}
//STEPLIB  DD  DISP=SHR,DSN={{{../settings.hlq}}}.LOADLIB
//SNAP     DD  SYSOUT=*
//SYSPRINT DD  SYSOUT=*
//SYSMDUMP DD  DUMMY
//SNAP     DD  SYSOUT=*
//IN       DD  *
CAN YOU SEE ME
/*
//         ENDIF
{{/each}}
