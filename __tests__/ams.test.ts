process.env.ALLOW_CONFIG_MUTATIONS = "yes"; // value doesn't matter

import { execSync } from "child_process";
import * as config from "config";
import * as fs from "fs";
import * as handlebars from "handlebars";

const TIMEOUT = 20000;

const test = [{
        in: "hello world"
    },
    {
        in: "good bye world"
    }];

(config as any).test = test;

let buildResponse: any;
let testResponse: any;

describe("Build tests", () => {

    beforeAll(() => {

        // build and run jcl to compile and bind all source
        const gen = execSync(`npm run genjcl:build`);
        console.log(gen.toString());
        let cmd = "zowe jobs submit lf \"./build/custom.jcl\" --directory \"./output\" --rfj"

        buildResponse = JSON.parse(execSync(cmd).toString());

        // build and run jcl to test service
        const jcl = fs.readFileSync("./zossrc/jcl/amstest.jcl").toString();
        const compiled = handlebars.compile(jcl);
        const rendered = compiled(config);

        if (!fs.existsSync("./build")) fs.mkdirSync("./build");
        fs.writeFileSync("./build/amstest.jcl", rendered);
        console.log("Generated custom JCL to ./build/amstest.jcl");

        cmd = "zowe jobs submit lf \"./build/amstest.jcl\" --directory \"./output\" --rfj"
        testResponse = JSON.parse(execSync(cmd).toString());

    }, TIMEOUT)

    it("should build without errors", () => {
        expect(buildResponse.data.retcode).toBe("CC 0000");
    });

    it("should read all input lines", () => {
        test.forEach((testData, index) => {
            const file = fs.readFileSync(`output/${testResponse.data.jobid}/RUN${index}/SYSPRINT.txt`).toString().trim();
            expect(file).toBe(testData.in);
        });
    });

});
