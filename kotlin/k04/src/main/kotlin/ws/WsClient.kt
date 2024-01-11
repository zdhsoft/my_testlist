package ws

import okhttp3.*
import okio.ByteString
import java.util.concurrent.TimeUnit
import com.google.gson.Gson
import com.zdhsoft.ws.getReplyMap
import com.zdhsoft.ws.WSReply
import kotlin.reflect.javaType
/** ws链接状态 */
enum class WSClientStatus {
    /** 未设置值 */
    Unknown,
    /** 链接中 */
    Connecting,
    /** 链接成功 */
    Connected,
    /** 链接断开 */
    Disconnected,
}

/** Websocket 文本消息 */
data class TextMessage(val type: Int, val body: String)
/** 通用返回 */
data class CommonRet(var ret: Int = 0, var msg: String = "")

/** 消息回调接口 */
interface IReplyCallBack {
    /** 回调接口 */
    fun callback(rep: WSReply<Any>): Unit
}

/** websocket 链接 客户端 */
class WsClient(serverURL: String) {
    /** okhttp链接客户端 */
    private var mOkHttpClient: OkHttpClient? = null
    /** 请求 */
    private var mRequest: Request? = null
    /** websocket链接对象 */
    private var mWebSocket: WebSocket? = null
    /** 当前链接状态 */
    private var mStatus = WSClientStatus.Unknown
    /** 消息响应数据映射表 */
    private var mReplyData = getReplyMap()
    /** 消息回调映射表 */
    private var mReplyCallBack = mutableMapOf<Int, IReplyCallBack>()
    init {
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
        mRequest = Request.Builder().url(serverURL).build()
    }
    /** 注册消息回调 */
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
    /** 当前链接状态 */
    fun getStatus(): WSClientStatus {
        return mStatus
    }
    /** 是否已经连接 */
    fun isConnected(): Boolean  {
        return mStatus == WSClientStatus.Connected
    }
    /** 发送文本消息 */
    private fun sendTextMessage(paramMessage: String) {
        mWebSocket?.send(paramMessage)
    }
    /** 发送指定的消息 */
    fun <T>sendMsg(type: Int, body: T) {
        val gson = Gson()
        val msg = TextMessage(type, gson.toJson(body))
        println("发送消息:type=$type, body:${msg.body}")
        sendTextMessage(gson.toJson(msg))
    }

    fun close() {
        if (isConnected()) {
            mWebSocket?.close(1000, "主动关闭")
        }
    }

    /** 连接 */
    @OptIn(ExperimentalStdlibApi::class)
    fun connect() {
        mStatus = WSClientStatus.Connecting
        mWebSocket = mOkHttpClient!!.newWebSocket(mRequest!!, object : WebSocketListener() {
            override fun onOpen(webSocket: WebSocket, response: Response) {
                super.onOpen(webSocket, response)
                println("socket 连接成功（需要自己切换到主线程）")
                mStatus = WSClientStatus.Connected
            }

            override fun onMessage(webSocket: WebSocket, text: String) {
                super.onMessage(webSocket, text)
                val gson = Gson()
                val msg = gson.fromJson(text, TextMessage::class.java)

                val ktype = mReplyData[msg.type]
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
                    callBack.callback(rep)
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
                mStatus = WSClientStatus.Disconnected
                println("onClosed：$code")
            }

            override fun onFailure(webSocket: WebSocket, t: Throwable, response: Response?) {
                super.onFailure(webSocket, t, response)
                println("onFailure：$t")
                mStatus = WSClientStatus.Disconnected
            }
        })
    }
}
