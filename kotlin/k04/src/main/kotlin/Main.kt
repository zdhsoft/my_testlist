package com.zdhsoft

import com.google.gson.Gson
import com.zdhsoft.ws.*
import ws.IReplyCallBack

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

class User() {
    private var appId: String
    private var userId: String
    private var roomId: Int

    init {
        appId = ""
        userId = ""
        roomId = 0
    }

    fun onLogin(rep: WSReply<Any>) {
        println("onLogin")
        val data = rep.data
        if (data is WSCSLoginTokenReplyData) {
            appId = data.info.appId
            userId = data.info.userId
        }
    }
    fun onEnterRoom(rep: WSReply<Any>) {
        println("onEnterRoom")
        val data = rep.data
        if (data is WSCSEnterRoomReplyData) {
            roomId = data.roomId
        }
    }

    fun onLeaveRoom(rep: WSReply<Any>) {
        println("onLeaveRoom")
        val data = rep.data
        if (data is WSCSLeaveRoomReplyData) {
            // roomId = data.roomId
        }
    }
    override fun toString(): String {
        return Gson().toJson(this)
    }
}


fun testWS() {
    try {
        val cli = ws.WsClient("ws://127.0.0.1:8001/ws/")
        val u = User()

        cli.registerCallBack(0, object: IReplyCallBack { override fun callback(rep: WSReply<Any>) { SimpleCallBack(rep) } })
        cli.registerCallBack(MsgId.LOGIN_BY_TOKEN, object: IReplyCallBack{ override fun callback(rep: WSReply<Any>) { u.onLogin(rep) } })
        cli.registerCallBack(MsgId.ENTER_ROOM, object: IReplyCallBack{ override fun callback(rep: WSReply<Any>) { u.onEnterRoom(rep) } })
        // val (ret, msg) = cli.registerCallBack(0, SimpleCallBack)



        cli.connect()
        Thread.sleep(500)
        val msg = WSCSLoginTokenRequest("0s6mrb7-0000-99-941e71f1-4da5-4397-92c1-b508ceafe65b-857078b237b2b")

        cli.sendMsg(MsgId.SIMPLE, WSSampleRequest("hello", "sss", "ddd"))
        cli.sendMsg(MsgId.LOGIN_BY_TOKEN, msg)
        Thread.sleep(500)
        val msgEnterRoom = WSCSEnterRoomRequest(100000126)
        cli.sendMsg(MsgId.ENTER_ROOM, msgEnterRoom)

        Thread.sleep(1000)
        println("---->user:${u}")
        cli.close()
    } catch(e: Exception) {
        e.printStackTrace()
    } finally {
        println("退出！")
    }
}