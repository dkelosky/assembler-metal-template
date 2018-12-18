#! /bin/env node
import * as config from "config";
import { execSync } from "child_process";
import { DataSets } from "./doc/IDataSets";

const hlq: string = config.get<string>('settings.hlq');
const dataSets: DataSets = config.get<DataSets>('dataSets');

Object.keys(dataSets).forEach((key) => {
    const cmd = `zowe files create pds ` +
        `"${hlq}.${key}" ` +
        `--bs ${dataSets[key].blockSize} ` +
        `--db ${dataSets[key].directoryBlocks} ` +
        `--rf ${dataSets[key].recordFormat} ` +
        `--rl ${dataSets[key].recordLength} ` +
        `--dt ${dataSets[key].recordLength} ` +
        `--sz ${dataSets[key].size}`;
    console.log(cmd)
    const resp = execSync(cmd).toString();
    console.log(resp.toString())
});
