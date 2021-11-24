const { getLogger, datetimeUtils, utils, XCommonRet } = require('xmcommon');
const log = getLogger(__filename);
const path = require('path');
const fs = require('fs');
const template = require('art-template');
const { Command } = require('commander');

const TEMPLATE_DIR = 'template';
const PROJECT_DIR  = 'project';
const OUT_DIR      = 'out';

const ret = new XCommonRet();

/** 工程配置信息 */
class XProjectConfig {
    /** 模板名称 */
    m_templateName = 'sample';
    /** 目标目录 */
    m_destDir = 'demo';
    /** 工程配置名称 */
    m_projectConfigName = 'demo.json'

    m_cfg = { config:{}, info: {}};
    constructor(paramProjectConfigName) {
        let ext = path.extname(paramProjectConfigName);
        if (utils.isNull(ext) || ext === '' ) {
            this.m_projectConfigName = paramProjectConfigName + '.json';
        } else {
            this.m_projectConfigName = paramProjectConfigName;
        }
        const fullName = XProjectConfig._getFullProjectConfigName(this.m_projectConfigName);
        if (!fs.existsSync(fullName)) {
            ret.setError(-1, `${paramProjectConfigName}对应的文件名为${fullName}的文件不存在!`);
        }
        else {
            this.m_cfg = this._init();
        }
    }

    _init() {
        let cfg = this._loadConfig();
        log.info(JSON.stringify(cfg, null, 2));
        this.m_destDir      = cfg.config.dest;
        this.m_templateName = cfg.config.template;
        return cfg;
    }

    get cfg() {
        return this.m_cfg;
    }

    get templateName() {
        return this.m_templateName;
    }

    get destName() {
        return this.m_destDir;
    }

    get projectConfigName() {
        return path.join(process.cwd(), PROJECT_DIR, this.m_projectConfigName);
    }

    static _getFullProjectConfigName(paramConfigName) {
        return path.join(process.cwd(), PROJECT_DIR, paramConfigName);
    }

    /**
        * 加载配置信息
    */
    _loadConfig() {
        let cfg = {
            config: this._getDefaultCfg(),
            info  : this._getDefaultInfo()
        };

        const config = require(this.projectConfigName);
        if (utils.isNotNull(config?.info)) {
            utils.dataAssign(cfg.info, config.info);
        }
        if (utils.isNotNull(config?.config)) {
            utils.dataAssign(cfg.config, config.config);
        }
        return cfg;
    }

    _getDefaultCfg() {
        return {
            /** 模板目录 */
            template : 'ts_sample',
            /** 输出目标目录 */
            dest: 'dest',
            /** 主类型 */
            main_type: 'node',
            /** 次类型 */
            second_type: 'typescript'
        };
    }

    _getDefaultInfo() {
        let   d     = new Date();
        // 缺省的日期
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

/** 模板配置文件名名称 */
const TEMPLATE_CONFIG_NAME = 'template.json';

/** 模板配置信息类 */
class XTemplateConfig {
    /** @type {string[]} 文件列表 */
    m_fileList = [];
    /** @type {string[]} 目录列表 */
    m_dirList = [];
    /** @type {string[]} 仅复制文件列表 */
    m_fileListByCopy = [];
    /** @type {string[]} 多余重复的文件 */
    m_overFile = [];
    /** @type {string[]} 多余重复的目录 */
    m_overDir = [];
    /** 模板的根目录 */
    m_templatePath = './template';

    constructor(paramTemplatePath) {
        this.m_templatePath = paramTemplatePath || './template';
        this._init();
    }

    get fileList() {
        return this.m_fileList;
    }

    get dirList() {
        return this.m_dirList;
    }

    get fileListByCopy() {
        return this.m_fileListByCopy;
    }

    get templatePath() {
        return this.m_templatePath;
    }

    get overFile() {
        return this.m_overFile;
    }

    get overDir() {
        return this.m_overDir;
    }

    get hasOver() {
        return this.m_overDir.length > 0 || this.m_overFile.length > 0;
    }

    get templateConfigName() {
        return path.join(process.cwd(), TEMPLATE_DIR, this.m_templatePath, TEMPLATE_CONFIG_NAME);
    }
    /**
     * 加载配置信息
     * @return {{dirList: string[], fileList: string[], fileListByCopy: string[]}}
     */
    _loadConfig() {
        // log.info('...>>' + this.templateConfigName);
        return require(this.templateConfigName);
    }

    _init() {
        const cfg = this._loadConfig();

        this.m_dirList        = [];
        this.m_fileList       = [];
        this.m_fileListByCopy = [];
        this.m_overDir        = [];
        this.m_overFile       = [];

        /** @type {Set<string>} */
        let fileSet = new Set();
        /** @type {Set<string>} */
        let dirSet = new Set();


        cfg?.dirList?.forEach(d => {
            const dd = d.trim();
            if (dirSet.has(dd)) {
                this.m_overDir.push(dd);
            } else {
                this.m_dirList.push(dd);
                dirSet.add(dd);
            }
        });

        cfg?.fileList?.forEach( f => {
            const ff = f.trim();
            if (fileSet.has(ff)) {
                this.m_overFile.push(ff);
            } else {
                this.m_fileList.push(ff);
                fileSet.add(ff);
            }
        });

        cfg?.fileListByCopy?.forEach( f => {
            const ff = f.trim();
            if (fileSet.has(ff)) {
                this.m_overFile.push(ff);
            } else {
                this.m_fileListByCopy.push(ff);
                fileSet.add(ff);
            }
        });

        log.info('目录列表:', this.m_dirList);
        log.info('要过滤文件列表:', this.m_fileList);
        log.info('仅复制文件列表:', this.m_fileListByCopy);

        if (this.m_overDir.length > 0) {
            log.info('重复的目录列表:', this.m_overDir);
        }

        if (this.m_overFile.length > 0) {
            log.info('重复的文件列表:', this.m_overFile);
        }
    }
}


async function main() {

    const program = new Command();
    program.version('0.0.1', '-v, --version', '显示当前版本号')
    .argument('<project_name>', '指创建一个指定project目录下指定工程配置的项目名称')
    .action(async (project_name) => {
        return await createProject(project_name);
    }).exitOverride((err)=>{
        if(err) {
            ret.setError(-9, String(err));
        }
    });

    await program.parseAsync(process.argv);
    if (ret.err !== 0) {
        log.error(ret.getErrorInfo());
        process.exitCode = ret.err;
    } else {
        process.exitCode = 0;
    }


    // let opts = program.opts();
    // if (opts.help) {
    //     log.info(opts);
    // } else {
    //     log.info(opts);
    // }
    return 0;

}

async function createProject(paramProjectName) {

    let projectConfig = new XProjectConfig(paramProjectName);
    if (ret.isNotOK) {
        return ret.err;
    }

    let tempCfg = new XTemplateConfig(projectConfig.templateName);

    if (tempCfg.hasOver) {
        ret.setError(-3, "存在重复的文件或目录！");
        log.error();
        return ret.err;
    }


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


    tempCfg.fileListByCopy.forEach(f => {
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
        ret.setError(-1, '发现有不存在的文件或目录');
        return ret.err;
    }

    log.info('最终目录列表：\n', finalDirList);
    log.info('最终文件列表：\n', finalFileList);

    const lastProjectDest = path.join(process.cwd(), OUT_DIR, projectConfig.destName);
    if (fs.existsSync(lastProjectDest)) {
        const bak_name = `${lastProjectDest}_${datetimeUtils.dateStringByFile(new Date(), false)}`;
        fs.renameSync(lastProjectDest, bak_name);
    }

    const makeResult = utils.mkdirsSyncEx(lastProjectDest);
    if (!makeResult.ret) {
        ret.setError(-2, makeResult.msg);
        return ret.err;
    }

    tempCfg.dirList.forEach(d => {
        log.info('准备目录:' + d);

        const fullPath = path.join(process.cwd(), OUT_DIR, projectConfig.destName, d);
        const makeResult = utils.mkdirsSyncEx(fullPath);

        if (!makeResult.ret) {
            ret.setError(-4, makeResult.msg);
            log.error(makeResult.msg);
        }
    });



    tempCfg.fileList.forEach(f => {
        log.info('过滤文件:' + f);

        const srcFile = path.join(process.cwd(), TEMPLATE_DIR, tempCfg.templatePath, f);
        const destFile = path.join(process.cwd(), OUT_DIR, projectConfig.destName, f);
        const destPath = path.dirname(destFile);
        const makeResult = utils.mkdirsSyncEx(destPath);

        if (!makeResult.ret) {
            ret.setError(-5, makeResult.msg);
            log.error(makeResult.msg);
            return;
        }
        const data = fs.readFileSync(srcFile);
        const result = template.render(data.toString('utf-8'), projectConfig.m_cfg.info);
        fs.writeFileSync(destFile, result);
    });

    tempCfg.fileListByCopy.forEach(f => {
        log.info('复制文件:' + f);
        const srcFile = path.join(process.cwd(), TEMPLATE_DIR, tempCfg.templatePath, f);
        const destFile = path.join(process.cwd(), OUT_DIR, projectConfig.destName, f);
        fs.copyFileSync(srcFile, destFile);
    });

    return 0;
}

main();
