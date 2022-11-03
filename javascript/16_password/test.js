function main() {
    const reg = /^\w+$/
    const t = ['aaa', 'aa123', 'Abcdefg123', '_', '___', ' ', '','*&&^'];
    for(const tv of t) {
        console.log(`value:[${tv}] result:${reg.test(tv)}`);
    }
}
main();
