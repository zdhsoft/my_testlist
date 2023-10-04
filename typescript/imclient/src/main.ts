import * as tencentcloud from 'tencentcloud-sdk-nodejs';
import { clientConfig, chatOptions } from './config';
import TencentCloudChat, { Message, UserInfo } from '@tencentcloud/chat';
import TIMUploadPlugin from 'tim-upload-plugin';
// eslint-disable-next-line @typescript-eslint/no-var-requires
const TIMProfanityFilterPlugin = require('tim-profanity-filter-plugin');

// tencentcloud.im.v20190318.Client;
// console.log('hello world!');

// async function main() {
//     const t = tencentcloud;

//     const ImClient = t.cim.v20190318.Client;

//     const client = new ImClient(clientConfig);
//     const params = {};

//     const data = await client.DescribeSdkAppid(null, (err, desp) => {
//         console.log(err, desp);
//     });

//     console.log(data);
// }

// main();

async function chattest() {
    //
    const chat = TencentCloudChat.create(chatOptions); // SDK 实例通常用 chat 表示
    chat.setLogLevel(0);
    chat.registerPlugin({ 'tim-upload-plugin': TIMUploadPlugin });
    chat.registerPlugin({ 'tim-profanity-filter-plugin': TIMProfanityFilterPlugin });
    const userInfo: UserInfo = {
        avatar: '',
        nick: '',
        userID: '',
    };
    const msg: Message = {
        ID: '',
        type: TencentCloudChat.TYPES.MSG_TEXT,
        payload: undefined,
        conversationID: '',
        conversationType: TencentCloudChat.TYPES.MSG_TEXT,
        to: '',
        from: '',
        flow: '',
        time: 0,
        status: '',
        isRevoked: false,
        priority: TencentCloudChat.TYPES.MSG_TEXT,
        nick: '',
        avatar: '',
        isPeerRead: false,
        nameCard: '',
        atUserList: [],
        cloudCustomData: '',
        isDeleted: false,
        isModified: false,
        needReadReceipt: false,
        readReceiptInfo: undefined,
        isBroadcastMessage: false,
        isSupportExtension: false,
        revoker: '',
        revokerInfo: userInfo,
        revokeReason: '',
        sequence: 0,
        hasRiskContent: true,
    };
    const r = await chat.sendMessage(msg, null);
    console.log(r);
}

async function main() {
    chattest();
}

main();
