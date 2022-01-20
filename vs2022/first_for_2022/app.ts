import { getLogger, utils} from 'xmcommon';

const log = getLogger(__filename);
log.log('Hello world');

class a {
    private vv = 999;
    public constructor(paramVv?: number) {
        if (utils.isNotNull(paramVv)) {
            this.vv = paramVv;
        }

    }
    public getName() {
        return 100;
    }

    public getVv() {
        return this.vv;
    }
}

const mm: string | null = null;

const v = new a();
log.log('name=' + v.getName() + ',' + v.getVv() + mm);