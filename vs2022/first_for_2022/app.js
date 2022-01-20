"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const xmcommon_1 = require("xmcommon");
const log = (0, xmcommon_1.getLogger)(__filename);
log.log('Hello world');
class a {
    constructor(paramVv) {
        this.vv = 999;
        if (xmcommon_1.utils.isNotNull(paramVv)) {
            this.vv = paramVv;
        }
    }
    getName() {
        return 100;
    }
    getVv() {
        return this.vv;
    }
}
let mm = null;
const v = new a();
log.log('name=' + v.getName() + ',' + v.getVv());
//# sourceMappingURL=app.js.map