async function test() {

}
async function main() {
    let p = test();
    await p;
    p.finally();
}

main();
