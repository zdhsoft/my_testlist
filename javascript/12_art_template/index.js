const {getLogger} = require ('xmcommon');
const log = getLogger(__filename);
const path = require('path');
const fs = require('fs');
const template = require('art-template');

/** 工程目录 */
class XProjectConfig {
    /** 模板名称 */
    #templateName = 'sample';
    /** 目标目录 */
    #destName = 'demo';
    /** 工程配置名称 */
    #projectConfigName = 'demo.json'
    constructor(paramProjectConfigName) {
        this.#projectConfigName = paramProjectConfigName;
        this.#init();
    }

    #init() {

    }

    get templateName() {
        return this.#templateName;
    }

    get destName() {
        return this.#destName;
    }

    get projectConfigName() {
        return this.#projectConfigName;
    }


}
/** 模板配置文件名名称 */
const TemplateConfigName = 'template.json';
class XTemplateConfig {
    /**
     * @type {string[]} 文件列表
     */
    #fileList = [];
    /**
     * @type {string[]} 目录列表
     */
    #dirList = [];
    /** 模板的根目录 */
    #templatePath = './template';

    constructor(paramTemplatePath) {
        this.#templatePath = paramTemplatePath || './template';
        this.#init();
    }

    get fileList() {
        return this.#fileList;
    }

    get dirList() {
        return this.#dirList;
    }

    get templatePath() {
        return this.#templatePath;
    }

    get templateConfigName() {
        return path.join(process.cwd(), this.#templatePath, TemplateConfigName);
    }
    /**
     * 加载配置信息
     * @return {{dirList: string[], fileList: string[]}}
     */
    #loadConfig() {
        // log.info('...>>' + this.templateConfigName);
        return require(this.templateConfigName);
    }

    #init() {
        const cfg = this.#loadConfig();
        this.#dirList = [];
        this.#fileList = [];

        cfg?.dirList?.forEach(p => this.#dirList.push(p));
        cfg?.fileList?.forEach(f => this.#fileList.push(f));

        // log.info(JSON.stringify(cfg, null, 2));
        log.info(this.#dirList);
        log.info(this.#fileList);
    }
}

let tempCfg = new XTemplateConfig();

const projectConfig = require('./project/demo.json');
log.info('--->' + JSON.stringify(projectConfig, null, 2));

/** @type {string[]} 不存在的文件列表 */
let notExistFile = [];
/** @type {string[]} 最终的文件列表 */
let finalFileList = [];
tempCfg.fileList.forEach(f =>
{
    const fullFileName = path.join(process.cwd(), tempCfg.templatePath, f);
    if (fs.existsSync(fullFileName)) {
        finalFileList.push(fullFileName);
    } else {
        notExistFile.push(f);
    }
});
let finalDirList  = tempCfg.dirList.map(d=>path.join(process.cwd(), tempCfg.templatePath, d));

if (notExistFile.length > 0) {
    log.info('模板中，下列文件不存在\n fileList:', JSON.stringify(notExistFile, null, 2));
    return -1;
}

log.info('最终目录列表', finalDirList);
log.info('实际不存在的文件列表', notExistFile);
log.info(finalFileList);



/*
tempCfg.fileList.forEach(f=>{
    const fullName = path.join(process.cwd(), tempCfg.templatePath, f + '.k');
    const data = fs.readFileSync(fullName);
    const result = template.render(data.toString('utf-8'), projectConfig);
    log.info('--->' + fullName);
    log.info('--->' + result);
});
*/

log.info('完成!!!');
