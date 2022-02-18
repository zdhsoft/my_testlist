export function testOpt() {
    let a;
    let b = 0;
    let c = 1;
    // eslint-disable-next-line prefer-const
    a ||= 2;
    b ||= 2;
    c ||= 2;

    let a1 = 1;
    let a2 = 1;
    a1 ||= ++a2;
    console.log(`a=${a},b=${b},c=${c}`);
    console.log(`a1=${a1},a2=${a2}`);
}
