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

describe("AMS tests", () => {

    beforeAll(() => {

        // build and run jcl to compile and bind all source
        const gen = execSync(`npm run genjcl:build`);
        console.log(gen.toString());
        const customCmd = "zowe jobs submit lf \"./build/custom.jcl\" --directory \"./output\" --rfj"

        buildResponse = JSON.parse(execSync(customCmd).toString());

        // build and run jcl to test service
        const jcl = fs.readFileSync("./zossrc/jcl/amstest.jcl").toString();
        const compiled = handlebars.compile(jcl);
        const rendered = compiled(config);

        if (!fs.existsSync("./build")) fs.mkdirSync("./build");
        fs.writeFileSync("./build/amstest.jcl", rendered);
        console.log("Generated custom JCL to ./build/amstest.jcl");

        const asmTestCmd = "zowe jobs submit lf \"./build/amstest.jcl\" --directory \"./output\" --rfj"
        testResponse = JSON.parse(execSync(asmTestCmd).toString());

    }, TIMEOUT)

    describe("build tests", () => {
        it("should build without errors", () => {
            expect(buildResponse.data.retcode).toBe("CC 0000");
        });
    });

    describe("execution tests", () => {
        it("should read all input lines", () => {
            test.forEach((testData, index) => {
                const file = fs.readFileSync(`output/${testResponse.data.jobid}/RUN${index}/SYSPRINT.txt`).toString().trim();
                expect(file).toBe(testData.in);
            });
        });

        it("show our control block is built correctly", () => {
            const responses = fs.readFileSync(`output/${testResponse.data.jobid}/RUN0/SNAP.txt`).toString().split('\n');
            let index;
            responses.forEach((response, x) => {
                if (response.indexOf("Important Control Block") > -1) {
                    index = x + 1;
                }
            });

            expect(index).toBeDefined();

            if (index) expect(responses[index].substr(9, responses[index].length)).toMatchSnapshot();
        });
    });
});
