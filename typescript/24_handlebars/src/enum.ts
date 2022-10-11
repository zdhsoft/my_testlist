enum enumTest {
    t1 = 1,
    t2 = 2,
    t3 = 3,
    t4 = 4,
}

enum enumExt {
    t1 = 99,
    t2 = 100,
    t3 = 101,
    t4 = 102,
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
