function testLET() {
    for (let i = 0; i < 10; i++) {
        let j = i * i;
        console.log(
            i, j);
    }
    console.log(i, j);
}

function test解构() {
    const list = [1, 'string', true, 'd', 2];
    const [v1, v2, v3, , v4] = list;
    console.log(v1, v2, v3, v4);

    const obj = {
        a: 'aaaa',
        b: 1233,
        c: true,
    }
    const { a, b, c, d } = obj;
    console.log(a, b, c, d);
}

function 测试模板字符串() {
    const s = `你好，当前时间是:${new Date()}`;
    const s1 = `随机一个数：${Math.random()}`;
    console.log(s, s1);

    // 标签模板字符串
    const name = '张三';
    const isMan = true
    const tagFn = function (strings, name, isMan) {
        let sex = isMan ? '男生' : '女生';
        return strings[0] + name + strings[1] + sex + strings[2]
    }
    const result = tagFn`hey, ${name} is a ${isMan}.`
    console.log(result); //hey,张三 is a男生.
}

function test字符串新函数(a,b,c) {
    const s = '这是一个新函数abc哈哈';
    console.log(`s中包含abc吗？` + s.includes('abc'));


}

测试模板字符串(1);
console.log(test字符串新函数.name);
console.log(test字符串新函数.arguments);
console.log(test字符串新函数.length);
