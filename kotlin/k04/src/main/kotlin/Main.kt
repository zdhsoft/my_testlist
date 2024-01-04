package com.zdhsoft

import com.google.gson.Gson
import com.zdhsoft.ws.*
import ws.IReplyCallBack
import kotlin.concurrent.thread

fun main() {
    println("Hello World!")
    testWS()
}

data class Simple(val message: String, val sender: String, val timestamp: String);

fun SimpleCallBack(rep: WSReply<Any>) {
    val data = rep.data
    if (data is WSSampleReplyData) {
        println("---->sender = ${data.sender}, message=${data.message}, timestamp=${data.timestamp}");
    } else {
        println("0-------未知的类型")
    }
}

class user() {
    var appId: String
    var userId: String
    var roomId: Int

    init {
        appId = ""
        userId = ""
        roomId = 0
    }

    fun onLogin(rep: WSReply<Any>) {
        println("onLogin")
        val data = rep.data
        if (data is WSCSLoginTokenReplyData) {
            appId = data.info.app_id
            userId = data.info.user_id
        }
    }
    fun onEnterRoom(rep: WSReply<Any>) {
        println("onEnterRoom")
        val data = rep.data
        if (data is WSCSEnterRoomReplyData) {
            roomId = data.room_id
        }
    }
    override fun toString(): String {
        return Gson().toJson(this)
    }
}


fun testWS() {
    try {
        val cli = ws.WsClient("ws://127.0.0.1:8001/ws/")
        val u = user()

        cli.registerCallBack(0, object: IReplyCallBack { override fun Callback(rep: WSReply<Any>) { SimpleCallBack(rep) } })
        cli.registerCallBack(MsgId.LoginByToken, object: IReplyCallBack{ override fun Callback(rep: WSReply<Any>) { u.onLogin(rep) } })
        cli.registerCallBack(MsgId.LoginByToken, object: IReplyCallBack{ override fun Callback(rep: WSReply<Any>) { u.onEnterRoom(rep) } })
        // val (ret, msg) = cli.registerCallBack(0, SimpleCallBack)



        cli.connect()
        Thread.sleep(500)
        val msg = WSCSLoginTokenRequest("0s6mrb7-0000-99-941e71f1-4da5-4397-92c1-b508ceafe65b-857078b237b2b")

        cli.sendMsg(MsgId.Simple, WSSampleRequest("hello", "sss", "ddd"))
        cli.sendMsg(MsgId.LoginByToken, msg)
        Thread.sleep(500)
        val msgEnterRoom = WSCSEnterRoomRequest(100000126)
        cli.sendMsg(MsgId.EnterRoom, msgEnterRoom)

        Thread.sleep(1000)
        println("---->user:${u}")

    } catch(e: Exception) {
        e.printStackTrace()
    } finally {
        println("退出！")
    }
}