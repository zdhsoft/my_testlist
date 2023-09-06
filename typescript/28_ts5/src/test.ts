import { XCommRet } from '@zdhsoft/commret';
import { default as axios } from 'axios';

const host = 'https://test.zdhsoft.com.cn';
const banner_list = '/toc/v1/banner_list';

export async function test_banner_list() {
    const url = host + banner_list;
    const result = await axios.get(url);
    const r = new XCommRet();
    if (result.status >= 200 && result.status < 300) {
        const data = { data: result.data, status: result.status };
        r.setOK(data);

        // if (data.error) {
        //     r.setError(-1, `error:${data.error}, error_description:${data.error_description}`);
        // } else {
        //     r.setOK({
        //         access_token: data.access_token as string,
        //         expires_in: data.expires_in as number,
        //     });
        // }
    } else {
        r.setError(-1, `status: ${result.status}, statusText: ${result.statusText}`);
    }
    console.log(JSON.stringify(r, null, 2));
}
