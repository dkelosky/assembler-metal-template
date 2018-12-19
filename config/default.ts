import defaultAssemblyOptions from "./default-imports/assembly/defaultAssemblyOptions";
import defaultAssemblyMaclibs from "./default-imports/assembly/defaultAssemblyMaclibs";
import defaultBindOptions from "./default-imports/bind/defaultBindOptions";
import defaultDataSets from "./default-imports/defaultDataSets";
import defaultUploads from "./default-imports/defaultUploads";
import defaultMetalOptions from "./default-imports/metal/defaultMetalOptions";
import defaultMetalIncludes from "./default-imports/metal/defaultMetalIncludes";

export default {

    // settings for all other sections
    settings: {
        hlq: "PUBLIC.TEMPLATE"
    },

    // working data sets to allocate
    dataSets: defaultDataSets,

    // mapping local z/OS to LLQ data sets
    uploads: defaultUploads,

    // job info
    job: {
        name: "TEMPLATE",
        account: "#ACCT",
        description: "ASM/BIND/RUN",

        // example
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
                options: defaultAssemblyOptions,
                maclibs: defaultAssemblyMaclibs,
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