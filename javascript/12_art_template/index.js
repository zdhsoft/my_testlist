const {getLogger} = require ('xmcommon');
const log = getLogger(__filename);
const path = require('path');
const fs = require('fs');
const template = require('art-template');

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
     * @return {{dirList: string[], fileList: stringp[]}}
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

let v = new XTemplateConfig();

const projectConfig = require('./project/demo.json');
log.info('--->' + JSON.stringify(projectConfig, null, 2));

v.fileList.forEach(f=>{
    const fullName = path.join(process.cwd(), v.templatePath, f);
    const data = fs.readFileSync(fullName);
    const result = template.render(data.toString('utf-8'), projectConfig);
    log.info('--->' + fullName);
    log.info('--->' + result);
});


log.info('完成!!!');
