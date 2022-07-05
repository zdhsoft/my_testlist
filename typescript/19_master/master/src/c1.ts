// import { XCommonRet } from 'xmcommon';
// import { MASTER } from './master';

import { XCommonRet } from 'xmcommon';
import { MASTER, MASTER2 } from './master';

// @MASTER('t1')
@MASTER2('aaaaaaaaaaaa')
export class t1 {
    public constructor() {
        console.log('---------t1');
    }
    public m = 100;

    private init() {
        console.log('init t1');
        this.m = 200;
        return new XCommonRet();
    }
}

@MASTER2('cccccccccccc')
export class t2 {
    public name = 'this is t2';
    public initFlag = false;

    public constructor() {
        console.log('---------t2');
    }
    private init() {
        console.log('init t2');
        this.initFlag = true;
        return new XCommonRet();
    }

    public toJSON() {
        return {
            name: this.name,
            initFlag: this.initFlag,
        };
    }
}
