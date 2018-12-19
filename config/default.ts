import defaultBindOptions from "./imports/bind/defaultBindOptions";
import dataSets from "./imports/dataSets";
import uploads from "./imports/uploads";
import assemblyOptions from "./imports/assembly/assemblyOptions";
import assemblyMaclibs from "./imports/assembly/assemblyMaclibs";

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

        // metal c compilations
        // metalCompilations: [
        //     {
        //         name: "TEMPLATE",
        //         options: defaultMetalOptions,
        //         includes: defaultMetalIncludes,
        //     }
        // ],

        // assemblies
        assemblies: [
            {
                name: "TEMPLATE",
                options: assemblyOptions,
                maclibs: assemblyMaclibs,
            },
        ],

        // binds
        binds: [
            {
                name: "TEMPLATE",
                options: defaultBindOptions,
            }
        ],

        // executables
        execs: [
            {
                name: "TEMPLATE",
                parm: "'Hello World'",
            }
        ]
    }
}