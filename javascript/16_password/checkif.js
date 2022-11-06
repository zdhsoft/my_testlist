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
}
