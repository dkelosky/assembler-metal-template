#! /bin/env node
import * as config from "config";
import { exec } from "child_process";
import { DataSets } from "./doc/IDataSets";

const hlq: string = config.get<string>('settings.hlq');
const dataSets: DataSets = config.get<DataSets>('dataSets');

Object.keys(dataSets).forEach((key) => {
    const cmd = `zowe files delete ds ` +
        `"${hlq}.${key}" ` +
        `-f`;
    console.log(cmd)
    exec(cmd, (err, stdout, stderr) => {
        if (err) console.log(err)
        if (stdout) console.log(stdout.toString());
        if (stderr) console.log(stderr.toString());
    });
});
