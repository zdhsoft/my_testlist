function main() {
    const reg = /^-?([1-9]\d*|[1-9]\d*\.\d*|0\.\d*[1-9]\d*|0?\.0+|0)$/;
    const r2 = /^(\-|\+)?\d+(\.\d+)?$/;


    // const reg = /^\w+$/
    const t = ['79690', '79690.1', '-12345', '135.345', '.1345', '-0.1345', '0.123456','*&&^'];
    for(const tv of t) {
        console.log(`value:[${tv}] result:${reg.test(tv)}, :${r2.test(tv)} => ${+tv}`);
    }
}
main();
