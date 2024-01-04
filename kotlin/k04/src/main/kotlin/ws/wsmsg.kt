package com.zdhsoft.ws

import com.google.gson.annotations.SerializedName
import kotlin.reflect.*


object MsgId {
    const val Simple = 0
    const val LoginByToken = 10000
    const val EnterRoom = 10001
    const val LeaveRoom = 10002
}

open class WSReply<T>(
    @SerializedName("result_code")
    val code: String = "",
    @SerializedName("result_info")
    val info: String = "",
    @SerializedName("data")
    val data: T? = null
) {
    val isSuccess: Boolean
        get() = code == "0"
}

data class WSSampleRequest(var message: String = "", var sender: String = "", var timestamp: String = "")
final data class WSSampleReplyData(var message: String = "", var sender: String = "", var timestamp: String = "")


data class WSCSLoginTokenRequest(var token: String = "")
data class WSUserInfoV2(
    var app_id: String,
    var user_id: String,
    var name: String,
    var role_List: Array<String>,
    var is_admin: Boolean,
    var account: String,
    var is_zb: Boolean,
    var area_code: String,
    var mobile: String,
    var icon: String,
    var login_token: String,
    var is_prohibit: Boolean,
    var modify_pwd_count: Int,
    var create_time: Int,
    var update_time: Int,
    var is_cg: Boolean,
    var is_guest: Boolean,
    var cid: String,
)

data class WSCSLoginTokenReplyData(var info: WSUserInfoV2)

data class WSCSEnterRoomRequest(var room_id: Int)
data class WSCSEnterRoomReplyData(var room_id: Int)
data class WSCSLeaveRoomRequest(var room_id: Int)
data class WSCSLeaveRoomReplyData(var room_id: Int)

fun GetReplyMap(): Map<Int, KType> {
    val myMap: Map<Int, KType> = mapOf(
        MsgId.Simple to typeOf<WSReply<WSSampleReplyData>>(),
        MsgId.LoginByToken to typeOf<WSReply<WSCSLoginTokenReplyData>>(),
        MsgId.EnterRoom to typeOf<WSReply<WSCSEnterRoomReplyData>>(),
        MsgId.LeaveRoom to typeOf<WSReply<WSCSLeaveRoomReplyData>>()
    )
    return myMap
}
