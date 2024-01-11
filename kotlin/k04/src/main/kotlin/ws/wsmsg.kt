package com.zdhsoft.ws

import com.google.gson.annotations.SerializedName
import kotlin.reflect.*

/** websocket的消息id */
object MsgId {
    /** 演示用消息id */
    const val SIMPLE = 0
    /** 登录 */
    const val LOGIN_BY_TOKEN = 10000
    /** 进入直播间 */
    const val ENTER_ROOM = 10001
    /** 离开直播间 */
    const val LEAVE_ROOM = 10002
}
/** 统一返回类型 */
data class WSReply<T>(
    /** 错误码 "0" 表示成功, 其他表示错误 */
    @SerializedName("result_code")
    val code: String = "",
    /** 返回信息 一般指错误信息 */
    @SerializedName("result_info")
    val info: String = "",
    /** 返回的数据 */
    @SerializedName("data")
    val data: T? = null
) {
    val isSuccess: Boolean
        get() = code == "0"
}
/** sample 请求 */
data class WSSampleRequest(var message: String = "", var sender: String = "", var timestamp: String = "")
/** sample 响应数据 */
data class WSSampleReplyData(var message: String = "", var sender: String = "", var timestamp: String = "")

/** 登录请求 */
data class WSCSLoginTokenRequest(var token: String = "")
/** 用户信息 */
data class WSUserInfoV2(
    @SerializedName("app_id")
    var appId: String,
    @SerializedName("user_id")
    var userId: String,
    @SerializedName("name")
    var name: String,
    @SerializedName("role_list")
    var roleList: List<String>,
    @SerializedName("is_admin")
    var isAdmin: Boolean,
    @SerializedName("account")
    var account: String,
    @SerializedName("is_zb")
    var isZb: Boolean,
    @SerializedName("area_code")
    var areaCode: String,
    @SerializedName("mobile")
    var mobile: String,
    @SerializedName("icon")
    var icon: String,
    @SerializedName("login_token")
    var loginToken: String,
    @SerializedName("is_prohibit")
    var isProhibit: Boolean,
    @SerializedName("modify_pwd_count")
    var modifyPwdCount: Int,
    @SerializedName("create_time")
    var createTime: Int,
    @SerializedName("update_time")
    var updateTime: Int,
    @SerializedName("is_cg")
    var isCg: Boolean,
    @SerializedName("is_guest")
    var isGuest: Boolean,
    @SerializedName("cid")
    var cid: String,
)
/** 登录响应数据 */
data class WSCSLoginTokenReplyData(var info: WSUserInfoV2)
/** 进入直播间请求 */
data class WSCSEnterRoomRequest(
    @SerializedName("room_id")
    var roomId: Int
)
/** 进入直播间响应数据 */
data class WSCSEnterRoomReplyData(
    @SerializedName("room_id")
    var roomId: Int
)
/** 离开直播间请求 */
data class WSCSLeaveRoomRequest(
    @SerializedName("room_id")
    var roomId: Int
)
/** 离开直播响应数据 */
data class WSCSLeaveRoomReplyData(
    @SerializedName("room_id")
    var roomId: Int
)

/** 取消息响应数据映射表 */
fun getReplyMap(): Map<Int, KType> {
    val msgIdReplyMap: Map<Int, KType> = mapOf(
        MsgId.SIMPLE to typeOf<WSReply<WSSampleReplyData>>(),
        MsgId.LOGIN_BY_TOKEN to typeOf<WSReply<WSCSLoginTokenReplyData>>(),
        MsgId.ENTER_ROOM to typeOf<WSReply<WSCSEnterRoomReplyData>>(),
        MsgId.LEAVE_ROOM to typeOf<WSReply<WSCSLeaveRoomReplyData>>()
    )
    return msgIdReplyMap
}
