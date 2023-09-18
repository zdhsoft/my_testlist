class prize(private val name: String, private val count: Int, private val type: Int) {
    companion object {
        var TYPE_REDPACK = 0
        var TYPE_COUPON = 1
        fun isRedpack(p: prize): Boolean {
            return p.type == TYPE_REDPACK
        }
    }
}
