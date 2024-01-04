package ws

import okhttp3.*
import okio.ByteString
import java.util.concurrent.TimeUnit
import com.google.gson.Gson
import com.zdhsoft.ws.GetReplyMap
import com.zdhsoft.ws.WSReply
import kotlin.reflect.javaType

enum class ClientStatus {
    Unknown,
    Connecting,
    Connected,
    Disconnected,
}
data class TextMessage(val type: Int, val body: String)

data class CommonRet(var ret: Int = 0, var msg: String = "")

interface IReplyCallBack {
    fun Callback(rep: WSReply<Any>): Unit
}

class WsClient(serverURL: String) {
    private var mOkHttpClient: OkHttpClient? = null
    private var mRequest: Request? = null
    private var mWebSocket: WebSocket? = null
    private var mStatus = ClientStatus.Unknown
    private var mReplyData = GetReplyMap()
    private var mReplyCallBack = mutableMapOf<Int, IReplyCallBack>()
    init {
        println("Constructor --->")
        println("WSClient init!!!!!!")
        //初始化okhttpClient
        val mBuilder: OkHttpClient.Builder = OkHttpClient.Builder()
        //设置读取超时时间
        mBuilder.readTimeout(120, TimeUnit.SECONDS)
        //设置写的超时时间
        mBuilder.writeTimeout(120, TimeUnit.SECONDS)
        //设置连接超时时间
        mBuilder.connectTimeout(120, TimeUnit.SECONDS)
        //心跳时间
        mBuilder.pingInterval(10, TimeUnit.SECONDS)
        mOkHttpClient = mBuilder.build()
        //初始化request
        // mRequest = Request.Builder().url("ws://local.zdhsoft.com/ws/").build()
        mRequest = Request.Builder().url(serverURL).build()
    }

    fun registerCallBack(type: Int, callback: IReplyCallBack) : CommonRet {
        val ret = CommonRet()
        if (mReplyCallBack.contains(type)) {
            ret.ret = -1
            ret.msg = "type=${type}的回调已经存在了"
        } else {
            mReplyCallBack[type] = callback
        }
       return ret
    }

    fun getStatus(): ClientStatus {
        return mStatus
    }

    fun isConnected(): Boolean {
        return mStatus == ClientStatus.Connected
    }

    private fun sendMessage(paramMessage: String) {
        mWebSocket?.send(paramMessage)
    }

    fun <T>sendMsg(type: Int, body: T) {
        val gson = Gson()
        val msg = TextMessage(type, gson.toJson(body))
        println("发送消息:type=$type, body:${msg.body}")
        sendMessage(gson.toJson(msg))
    }
    @OptIn(ExperimentalStdlibApi::class)
    fun connect() {
        mStatus = ClientStatus.Connecting
        mWebSocket = mOkHttpClient!!.newWebSocket(mRequest!!, object : WebSocketListener() {
            override fun onOpen(webSocket: WebSocket, response: Response) {
                super.onOpen(webSocket, response)
                println("socket 连接成功（需要自己切换到主线程）")
                mStatus = ClientStatus.Connected
            }

            override fun onMessage(webSocket: WebSocket, text: String) {
                super.onMessage(webSocket, text)
                val gson = Gson()
                val msg = gson.fromJson(text, TextMessage::class.java)

                val ktype = mReplyData.get(msg.type)
                if (ktype == null) {
                    println("没有找到msgId=${msg.type}的消息:${msg.body}")
                    return
                }

                val rep = gson.fromJson<WSReply<Any>>(msg.body, ktype.javaType)
                println("--->收到响应：code=${rep.code}, info=${rep.info}, data=${gson.toJson(rep.data)}")

                val callBack = mReplyCallBack.get(msg.type)
                if (callBack == null) {
                    println("没有找到msgId=${msg.type}的消息:${msg.body} 的回调函数!")
                } else {
                    callBack.Callback(rep)
                }
            }

            override fun onMessage(webSocket: WebSocket, bytes: ByteString) {
                super.onMessage(webSocket, bytes)
                println("onMessage:binary:")
            }

            override fun onClosing(webSocket: WebSocket, code: Int, reason: String) {
                super.onClosing(webSocket, code, reason)
                println("on Closing:$code")
            }

            override fun onClosed(webSocket: WebSocket, code: Int, reason: String) {
                super.onClosed(webSocket, code, reason)
                mStatus = ClientStatus.Disconnected
                println("onClosed：$code")
            }

            override fun onFailure(webSocket: WebSocket, t: Throwable, response: Response?) {
                super.onFailure(webSocket, t, response)
                println("onFailure：$t")
                mStatus = ClientStatus.Disconnected
            }
        })
    }
}
