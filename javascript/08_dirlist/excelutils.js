const xlsx = require('xlsx');
const nodeExcel = require('excel-export');

class ExcelUtils {

    /**
     * 读取excel 信息并返回：
     * @param {string} filePath  读取的文件路径
     */
    static async readExcelData(filePath) {
        let book = xlsx.readFileSync(filePath);
        // 取第一个Sheet页面
        let sheet = book.Sheets[book.SheetNames[0]];
        // 默认第一行是key，key不存在时，值也不显示
        let sheetObject = xlsx.utils.sheet_to_json(sheet);
        return sheetObject;
    }

    // let conf: any = {};
    // // 导出数据
    // conf.cols = [
    //     {caption: 'appId', type: 'string', width: 10 },
    //     {caption: '企业名称', type: 'string', width: 56 },
    //     {caption: '用户类型', type: 'string', width: 56 },
    //     {caption: '用户ID', type: 'string', width: 10 },
    //     {caption: '用户名称', type: 'string', width: 15 },
    //     {caption: '用户手机', type: 'string', width: 13},
    //     {caption: '用户邮箱', type: 'string', width: 38},
    //     {caption: '企业注册时间', type: 'string', width: 30 },
    //     {caption: '备注', type: 'string', width: 10 }
    // ];
    // conf.rows = outlist;
    // let result = nodeExcel.execute(conf);
    // let data = new Buffer(result, 'binary');
    // fs.writeFileSync('./userList.xlsx', data);
    // process.exit(0);

    /**
     * 单sheet 下载
     * @param {string} name 名
     * @param {[string]} cols 表头
     * @param {[any]} rows 表内容
     */
    static buildExcel(name, cols, rows) {
        let conf = {};
        conf.name = name;
        conf.cols = cols;
        conf.rows = rows.map((v) => {
            for (let i = 0; i < v.length; ++i) {
                if (v[i] && v[i] !== '') v[i] = v[i].toString();
                else v[i] = v[i] || '';
            }
            return v;
        });
        conf = JSON.parse(JSON.stringify(conf));
        const result = nodeExcel.execute(conf);
        const data = Buffer.from(result, 'binary');
        return data;
    }
};

exports.ExcelUtils = ExcelUtils;

// export {ExcelUtils};
