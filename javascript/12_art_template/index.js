const { getLogger, datetimeUtils, utils } = require('xmcommon');
const log = getLogger(__filename);
const path = require('path');
const fs = require('fs');
const template = require('art-template');

const TEMPLATE_DIR = 'template';
const PROJECT_DIR  = 'project';
const OUT_DIR = 'out';

/** 工程目录 */
class XProjectConfig {
    /** 模板名称 */
    #templateName = 'sample';
    /** 目标目录 */
    #destDir = 'demo';
    /** 工程配置名称 */
    #projectConfigName = 'demo.json'

    cfg = { config:{}, info: {}};
    constructor(paramProjectConfigName) {
        this.#projectConfigName = paramProjectConfigName;
        this.cfg = this.#init();
    }

    #init() {
        let cfg = this.#loadConfig();
        log.info(JSON.stringify(cfg, null, 2));
        this.#destDir      = cfg.config.dest;
        this.#templateName = cfg.config.template;
        return cfg;
    }

    get cfg() {
        return this.cfg;
    }

    get templateName() {
        return this.#templateName;
    }

    get destName() {
        return this.#destDir;
    }

    get projectConfigName() {
        return path.join(process.cwd(), PROJECT_DIR, this.#projectConfigName);
    }

    /**
        * 加载配置信息
        * @return
    */
    #loadConfig() {
        let cfg = {
            config: this.#getDefaultCfg(),
            info  : this.#getDefaultInfo()
        };

        const config = require(this.projectConfigName);
        if (utils.isNotNull(config?.info)) {
            utils.dataAssign(cfg.info, config.info);
        }
        return cfg;
    }

    #getDefaultCfg() {
        return {
            /** 模板目录 */
            template : 'ts_sample',
            /** 输出目标目录 */
            dest: 'dest',
        };
    }

    #getDefaultInfo() {
        let   d     = new Date();
        const year  = `${d.getFullYear()}`.padStart(4, 0);
        const month = `${d.getMonth() +1 }`.padStart(2, 0);
        const day   = `${d.getDate()}`.padStart(2,0);
        const date  = `${year}-${month}-${day}`;

        return {
            name   : 'demo',
            author : '',
            version: '0.0.1',
            desc   : '',
            license: '',
            year,
            month,
            day,
            date
        }
    }
}

let p = new XProjectConfig('demo.json');

/** 模板配置文件名名称 */
const TEMPLATE_CONFIG_NAME = 'template.json';
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
        return path.join(process.cwd(), TEMPLATE_DIR, this.#templatePath, TEMPLATE_CONFIG_NAME);
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

let tempCfg = new XTemplateConfig(p.templateName);

const projectConfig = require('./project/demo.json');
log.info('--->' + JSON.stringify(projectConfig, null, 2));

/** @type {string[]} 不存在的文件列表 */
let notExistFile = [];
let notExistDir = [];
/** @type {string[]} 最终的文件列表 */
let finalFileList = [];
let finalDirList = [];

tempCfg.fileList.forEach(f => {
    const fullFileName = path.join(process.cwd(), TEMPLATE_DIR, tempCfg.templatePath, f);
    if (fs.existsSync(fullFileName)) {
        finalFileList.push(fullFileName);
    } else {
        notExistFile.push(f);
    }
});

tempCfg.dirList.forEach(d => {
    const fullPath = path.join(process.cwd(), TEMPLATE_DIR, tempCfg.templatePath, d);
    if (fs.existsSync(fullPath)) {
        finalDirList.push(fullPath);
    } else {
        notExistDir.push(d);
    }
});


if (notExistFile.length > 0) {
    log.info('模板中，下列文件不存在\n fileList:', JSON.stringify(notExistFile, null, 2));
}

if (notExistDir.length > 0) {
    log.info('模板中，下列目录不存在\n dirList:', JSON.stringify(notExistDir, null, 2));
}

if (notExistDir.length > 0 || notExistFile.length > 0) {
    return -1;
}

log.info('最终目录列表', finalDirList);
log.info(finalFileList);

const lastProjectDest = path.join(process.cwd(), OUT_DIR, p.destName);
if (fs.existsSync(lastProjectDest)) {
    const bak_name = `${lastProjectDest}_${datetimeUtils.dateStringByFile(new Date(), false)}`;
    fs.renameSync(lastProjectDest, bak_name);
}

const makeResult = utils.mkdirsSyncEx(lastProjectDest);
if (!makeResult.ret) {
    log.error(makeResult.msg);
    return -2;
}

tempCfg.dirList.forEach(d => {
    log.info('准备目录:' + d);
    const fullPath = path.join(process.cwd(), OUT_DIR, p.destName, d);
    const makeResult = utils.mkdirsSyncEx(fullPath);
    if (!makeResult.ret) {
        log.error(makeResult.msg);
    }
});



tempCfg.fileList.forEach(f => {
    log.info('生成文件:' + f);
    const srcFile = path.join(process.cwd(), TEMPLATE_DIR, tempCfg.templatePath, f);
    const destFile = path.join(process.cwd(), OUT_DIR, p.destName, f);
    const destPath = path.dirname(destFile);
    const makeResult = utils.mkdirsSyncEx(destPath);
    if (!makeResult.ret) {
        log.error(makeResult.msg);
        return;
    }
    const data = fs.readFileSync(srcFile);
    const result = template.render(data.toString('utf-8'), p.cfg.info);
    fs.writeFileSync(destFile, result);
});

log.info('完成!!!');
