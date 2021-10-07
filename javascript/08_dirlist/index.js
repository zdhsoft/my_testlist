const fs = require("fs");
const path = require("path");
const { exit } = require("process");
const { utils } = require("xmcommon");
const {DBTool} = require('./db');
const {ExcelUtils} = require('./excelutils');


const list = [];
/**
 *
 * @param {string} dir
 * @return {[string]}
 */
function listFile(dir){
	const arr = fs.readdirSync(dir);
	arr.forEach(function(item){
		const fullpath = path.join(dir,item);
		const stats = fs.statSync(fullpath);
		if(stats.isDirectory()){
			listFile(fullpath);
		}else{
			list.push(fullpath);
		}
	});
	return list;
}

// async function waitDB() {
//     for(let i = 0; i < 40; i++) {
//         if (DBTool.getDBFlag()) {
//             return true;
//         }
//         console.log('.......', i);
//         await utils.sleep(1000);
//     }
//     return false;
// }


async function main() {

    let dblist = await DBTool.GetRecordListByQuery('select * from cmmifile where id > 0');

    let mmap = new Map();
    if (utils.isNotNull(dblist)) {
        dblist.forEach((item)=>{
            mmap.set(item.full, item);
        });
    }

    const root = "D:\\work\\svn_doc\\lr\\05-CMMI\\EPG\\最终产出目标\\配置管理目录";
    const root1 = root + '\\';

    const res = listFile(root);
    let maxDep = 0;
    let max = 8;
    /** @type {[{filename: string, dirpath:[string], full: string}]} */
    let newres = [];
    res.forEach((item)=>{
        const it = item.replace(root1, '');
        const itlist = it.split('\\');
        const filename = itlist[itlist.length-1];
        if (filename.search('~$') >= 0) {
            console.log('发现临时文件:'+it);
            return;
        }
        let m = {
            filename: itlist[itlist.length-1],
            dirpath : itlist.slice(0, itlist.length-1),
            full    : it
        }
        newres.push(m);

        if (m.dirpath.length > maxDep) {
            maxDep = m.dirpath.length;
        }
    })


    let last = newres.map((item)=>{
        for(let k = item.dirpath.length; k < maxDep; k++) {
            item.dirpath.push('');
        }

        let dbitem = mmap.get(item.full);
        let code = '';
        if (utils.isNotNull(dbitem)) {
            code = dbitem.code;
        }
        return [...item.dirpath, item.filename, code, item.full];
    });

    for (let item of newres) {
        if (mmap.has(item.full)) {
            continue;
        }
        let obj = {
            path     : path.dirname(item.full),
            filename : item.filename,
            full     : item.full,
        };
        for(let i = 0; i < maxDep; i++) {
            obj['dir' + (i+1)] = item.dirpath[i];
        }
        let result = await DBTool.insertRecord('cmmifile', obj);
        console.log(result);
    }

    /** @type {[string]} 表头 */
    let cols = [];
    for (let i = 0; i < maxDep; i++) {
        cols.push({ caption: '目录' + (i + 1), type: 'string', width: 20 });
    }
    cols.push({ caption: '文件名', type: 'string', width: 40 });
    cols.push({ caption: '编号', type: 'string', width: 20 });
    cols.push({ caption: '全称', type: 'string', width: 150 });

    let d = ExcelUtils.buildExcel('aaaaa', cols, last);
    fs.writeFileSync('./a.xlsx', d);
    console.log('执行完成！');
    await utils.sleep(500);
    exit(0);
}

main();

// console.log(JSON.stringify(newres, null, 2));
