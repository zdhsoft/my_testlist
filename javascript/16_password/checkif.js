const v = [
    undefined, null,
    0, '', false, NaN, -0, 0.0, 'aaa', -1, 1, true, [], [123], {}, {a:999}
];
for(const vv of v) {
    console.log(`<${vv}>`);
    if(vv) {
        console.log(`   <${vv}>: is true`);
    } else {
        console.log(`   <${vv}>: is false`);
    }

    if(!!vv) {
        console.log(`   !!<${vv}>: is true`);
    } else {
        console.log(`   !!<${vv}>: is false`);
    }

    console.log('----------->>>', vv ?? '哈哈哈哈哈');
}

const m = v.filter((c, index) => !!c);
console.log('M' + JSON.stringify(m));


let a;
let b = 0;
let c = 1;
a ??= 2;
b ??= 2;
c ??= 2;

let d = { a: 100, b:200, c:300, d: null};
d.d ??= 99;
d.a ??= 99;
d.b ??= 99;
d.c ??= 99;

console.log(`a=${a}, b=${b}, c=${c}, d=${JSON.stringify(d)}`);
