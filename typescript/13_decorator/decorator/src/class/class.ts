export class SimpleClass {
    public constructor() {
        //
    }
}
interface IGirl {
    faceValue(): void;
}
// 女孩子
class Girl implements IGirl {
    public faceValue() {
        console.log('我原本的脸');
    }
}

class ThinFace implements IGirl {
    constructor(private girl: IGirl) {
        this.girl = girl;
    }
    public faceValue() {
        this.girl.faceValue();
        console.log('开启瘦脸');
    }
}

class IncreasingEyes implements IGirl {
    constructor(private girl: IGirl) {
        this.girl = girl;
    }
    public faceValue() {
        this.girl.faceValue();
        console.log('增大眼睛');
    }
}

export function testClass() {
    let girl = new Girl();
    girl = new ThinFace(girl);
    girl = new IncreasingEyes(girl);

    // 闪瞎你的眼
    girl.faceValue(); //
}
