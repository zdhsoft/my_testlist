const {utils} = require('xmcommon');

/** 密码字符集 */
const passwdChar = [
    `ABCDEFGHIJKLMNOPQRSTUVWXYZ`,
    `abcdefghijklmnopqrstuvwxyz`,
    `0123456789`,
    `~!@#$%^&*()_+-=[]{}\\|:;'",.<>/?`,
];
const weightList = [0, 0, 0, 0, 0, 1, 1, 1, 1, 1,  2, 2, 3, 3, 3];
function createPassword(paramLength = 32) {
    const baseIndex = [0,1,2,3];
    for(let i = baseIndex.length; i < paramLength; i++) {
        const idx = utils.randomScope(weightList.length);
        baseIndex.push(weightList[idx]);
    }

    console.log(`len=${baseIndex.length}, ${JSON.stringify(baseIndex)}`);
    const charList = [];
    for(const b of baseIndex) {
        const s = passwdChar[b];
        const len = s.length;
        const idx = utils.randomScope(len);
        charList.push(s.substring(idx, idx + 1));
    }

    const lastChar = [];
    while (charList.length > 1) {
        const idx = utils.randomScope(charList.length);
        lastChar.push(charList[idx]);
        charList.splice(idx, 1);
    }

    lastChar.push(charList[0]);

    console.log('charList', JSON.stringify(charList.join('')));
    console.log('lastChar' + lastChar.length, JSON.stringify(lastChar.join('')));
}

for(let i = 0; i < 10; i++) {
    console.log('----------------------------------->' + i);
    createPassword(32);
}
