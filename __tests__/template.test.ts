process.env.ALLOW_CONFIG_MUTATIONS = "yes"; // value doesn't matter

import { execSync } from "child_process";
import * as fs from "fs";

const TIMEOUT = 20000;

let buildResponse: any;

describe("template tests", () => {

    beforeAll(() => {

        // build and run jcl to compile and bind all source
        const gen = execSync(`npm run genjcl`);
        console.log(gen.toString());
        let cmd = "zowe jobs submit lf \"./build/custom.jcl\" --directory \"./output\" --rfj"

        buildResponse = JSON.parse(execSync(cmd).toString());

    }, TIMEOUT)

    describe("build tests", () => {
        it("should build without errors", () => {
            expect(buildResponse.data.retcode).toBe("CC 0000");
        });
    });

    describe("execution tests", () => {
        it("should read all input lines", () => {
            const file = fs.readFileSync(`output/${buildResponse.data.jobid}/RUN/SYSPRINT.txt`).toString().trim();
            expect(file).toBe("@TEST");
        });

        it("show our control block is built correctly", () => {
            const responses = fs.readFileSync(`output/${buildResponse.data.jobid}/RUN/SNAP.txt`).toString().split('\n');
            let index;
            responses.forEach((response, x) => {
                if (response.indexOf("TEMPLATE SNAP") > -1) {
                    index = x + 1;
                }
            });

            expect(index).toBeDefined();

            if (index) expect(responses[index].substr(9, responses[index].length)).toMatchSnapshot();
        });
    });
});
