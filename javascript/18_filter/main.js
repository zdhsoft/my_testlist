const {data, filterdata} = require('./data')
/** @type {Map:<string, {orgType: number, appId: string, extName: string}>} */
const filterMap = new Map();
filterdata.forEach((item) => {
    filterMap.set(item.appId, item);
})

for(const d of data) {
    const f = filterMap.get(d.appId);
    if (f) {
        if (f.orgType === d.orgType) {
            d.orgName = d.orgName + f.extName;
        }
    }
}

console.log(JSON.stringify(data, null, 2));