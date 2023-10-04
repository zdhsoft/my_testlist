import sdk from 'tencentcloud-sdk-nodejs';
import { clientConfig } from './config';
const ImClient = sdk.cim.v20190318.Client;

// tencentcloud.im.v20190318.Client;
// console.log('hello world!');

async function main() {
    const client = new ImClient(clientConfig);

    const params = {};

    const data = await client.DescribeSdkAppid(null, (err, desp) => {
        console.log(err, desp);
    });

    console.log(data);
}

main();
