class Study(private var age:Int, private var name:String,private var classNames: String) {
    companion object {
        val ONE_LEVEL = 7

        fun isOne(s: Study): Boolean {
            return s.age == ONE_LEVEL
        }
    }
}
