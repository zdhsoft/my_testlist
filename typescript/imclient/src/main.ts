import * as tencentcloud from 'tencentcloud-sdk-nodejs';
import { clientConfig } from './config';

// tencentcloud.im.v20190318.Client;
// console.log('hello world!');

async function main() {
    const t = tencentcloud;

    const ImClient = t.cim.v20190318.Client;

    const client = new ImClient(clientConfig);
    const params = {};

    const data = await client.DescribeSdkAppid(null, (err, desp) => {
        console.log(err, desp);
    });

    console.log(data);
}

main();
