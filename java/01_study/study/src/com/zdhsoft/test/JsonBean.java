package com.zdhsoft.test;
public class JsonBean {
    public String result_code;
    public String result_info;
    public Object data;

    public String getRet() {
        return result_code;
    }

    public void setRet(String ret) {
        this.result_code = ret;
    }

    public String getMsg() {
        return result_info;
    }

    public void setMsg(String msg) {
        this.result_info = msg;
    }

    public Object getData() {
        return data;
    }

    public void setData(Object data) {
        this.data = data;
    }
}
