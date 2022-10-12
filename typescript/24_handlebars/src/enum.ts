export class M {
    public getM() {
        return 'm';
    }
}
export class G {
    public getName() {
        return 'name';
    }
}

declare global {
    const g: G;
}

enum enumTest {
    t1 = 1,
    t2 = 2,
    t3 = 3,
    t4 = 4,
    t5 = 1,
    t6 = '6666666666666',
}

enum enumExt {
    t1 = 99,
    t2 = 100,
    t3 = 101,
    t4 = 102,
    t5 = 9999,
}

function t(paramKey: enumTest) {
    const name = enumTest[paramKey];
    const ext = enumExt[name];
    console.log(`${name}:= ${paramKey}, ext:${ext}`);
}

t(enumTest.t1);
t(enumTest.t2);
t(enumTest.t3);
t(enumTest.t4);
t(enumTest.t5);
t(enumTest.t6);
