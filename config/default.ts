import defaultBindOptions from "./imports/bind/defaultBindOptions";
import dataSets from "./imports/dataSets";
import uploads from "./imports/uploads";
import assemblyOptions from "./imports/assembly/assemblyOptions";
import assemblyMaclibs from "./imports/assembly/assemblyMaclibs";
import metalOptions64 from "./imports/metal/metalOptions64";
import metalIncludes from "./imports/metal/metalIncludes";

export default {

    // settings for all other sections
    settings: {
        hlq: "PUBLIC.TEMPLATE"
    },

    // working data sets to allocate
    dataSets,

    // mapping local z/OS to LLQ data sets
    uploads,

    // job info
    job: {
        name: "TEMPLATE",
        account: "#ACCT",
        description: "ASM/BIND/RUN",

        // metal c compilation configuration
        compilation: {
            options: metalOptions64,
            includes: metalIncludes,
            sources: {
                TEMPLATE: {
                    // override options here
                },
            },
        },

        // assembly configuration
        assembly: {
            options: assemblyOptions,
            includes: assemblyMaclibs,
            sources: {
                TEMPLATE: {
                    // override options here
                },
                WTO: {},
            },
        },

        // bind configuration
        bind: {
            options: defaultBindOptions,
            // includes: nothing included in every bind right now
            sources: {
                TEMPLATE: {
                    includes: [
                        "WTO"
                    ]
                    // override options here
                }
            }
        },

        // executables
        execute: {
            // options: no parms to every exec right now (options are PARM=)
            sources: {
                TEMPLATE: {
                    // override options here (options are PARM=)
                    // options: '"HELLO WORLD"'
                }
            }
        }
    }
}