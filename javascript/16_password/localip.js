const os = require('os');
const devNames = ['以太网', 'WLAN'];
function isDevName(paramName) {
    for(const d of devNames) {
        if (paramName && paramName.startsWith(d)) {
            return true;
        }
    }
    return false;
}
function getLocalIPAdress() {
    const interfaces = os.networkInterfaces();
    const ipAddr     = [];

    for (let devName in interfaces) {
        if(!isDevName(devName)) {
            continue;
        }
        let iface = interfaces[devName];
        for (let alias of iface) {
            console.log('-----------------\n', '[' + devName + ']\n', JSON.stringify(alias, null, 2));
            if (alias.family === 'IPv4' && alias.address !== '127.0.0.1' && !alias.internal) {
                console.log('*****' + alias.address);
                ipAddr.push(alias.address);
            }
        }
    }

    return ipAddr;
}

console.log(getLocalIPAdress());
