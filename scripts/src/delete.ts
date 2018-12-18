#! /bin/env node
import * as config from "config";
import { execSync } from "child_process";
import { DataSets } from "./doc/IDataSets";

const hlq: string = config.get<string>('settings.hlq');
const dataSets: DataSets = config.get<DataSets>('dataSets');

Object.keys(dataSets).forEach((key) => {
    const cmd = `zowe files delete ds ` +
        `"${hlq}.${key}" ` +
        `-f`;
    console.log(cmd)
    const resp = execSync(cmd).toString();
    console.log(resp.toString())
});
