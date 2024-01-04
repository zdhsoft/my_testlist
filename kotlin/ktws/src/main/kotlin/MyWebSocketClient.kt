import java.net.http.WebSocket


class MyWebSocketClient(private val url: String) {
    private var webSocket: WebSocket? = null

    init {
        val request = Request.Builder().url(url).build()
        val client = OkHttpClient()
        webSocket = client.newWebSocket(request, object : WebSocketListener() {
            override fun onOpen(webSocket: WebSocket, response: Response) {
                println("WebSocket 连接已打开")
            }

            override fun onMessage(webSocket: WebSocket, text: String) {
                println("收到消息： $text")
            }

            override fun onClosed(webSocket: WebSocket, code: Int, reason: String) {
                println("WebSocket 连接已关闭，原因：$reason")
            }

            override fun onFailure(webSocket: WebSocket, t: Throwable, response: Response?) {
                println("WebSocket 连接失败，原因：${t.message}")
            }
        })
    }

    fun sendMessage(message: String) {
        webSocket?.send(message)
    }

    fun close() {
        webSocket?.close(1000, "正常关闭")
    }
}
