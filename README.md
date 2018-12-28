# Zowe Assembler Example

## Setup
1. `git clone` this project
2. `npm install`
3. Create a file `config/local.json` with your project settings, e.g.:
```json
{
    "settings": {
        "hlq": "KELDA16.TEMPLATE"
    },
    "job": {
        "name": "KELDA16$",
        "account": "105300000"
    }
}
```

## Usage

* `npm run allocate` -> Allocate your project data sets
* `npm run delete` -> Delete your project data sets
* `npm run genjcl` -> Generate JCL from template
* `npm run upload` -> Upload source to data sets
* `npm run build` -> Run JCL and download output
* `npm run build:scripts` -> Rebuild scripts
* `npm [run] start` -> upload & build

### Advanced Usage

#### Upload
 * `npm run upload -- asmpgm` -> upload asmpgm folder
 * `npm run upload -- asmpgm asmmac/#entry asmmac/#exit` upload asmpgm folder & #entry / #exit from asmmac

https://medium.com/@dkelosky/zowe-and-hlasm-hello-world-build-deploy-695be1eb13dc
