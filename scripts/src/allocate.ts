#! /bin/env node
import * as config from "config";
import { exec } from "child_process";
import { DataSets } from "./doc/IDataSets";

const hlq: string = config.get<string>('settings.hlq');
const dataSets: DataSets = config.get<DataSets>('dataSets');

Object.keys(dataSets).forEach((key) => {
  let cmd = `zowe files create pds ` +
    `"${hlq}.${key}" ` +
    `--bs ${dataSets[key].blockSize} ` +
    `--db ${dataSets[key].directoryBlocks} ` +
    `--rf ${dataSets[key].recordFormat} ` +
    `--dst ${dataSets[key].dataSetType} ` +
    `--rl ${dataSets[key].recordLength} ` +
    `--sz ${dataSets[key].size} `;

  // add volume if specified
  if (dataSets[key].volumeSerial) cmd += `--vs ${dataSets[key].volumeSerial}`

  // log command and run it
  console.log(cmd)
  exec(cmd, (err, stdout, stderr) => {
    if (err) console.log(err)
    if (stdout) console.log(stdout.toString());
    if (stderr) console.log(stderr.toString());
  });
});
