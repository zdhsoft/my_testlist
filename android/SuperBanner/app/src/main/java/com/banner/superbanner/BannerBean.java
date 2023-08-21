package com.banner.superbanner;

import java.io.Serializable;
import java.util.List;

public class BannerBean implements Serializable {
    /**
     * data : ["http://192.168.0.104:8080/pic/one.png","http://192.168.0.104:8080/pic/two.png","http://192.168.0.104:8080/pic/three.png","http://192.168.0.104:8080/pic/four.png","http://192.168.0.104:8080/pic/five.png","http://192.168.0.104:8080/pic/six.png","http://192.168.0.104:8080/pic/eight.png","http://192.168.0.104:8080/pic/seven.png","http://192.168.0.104:8080/pic/nine.png"]
     * desc : listViewData
     * msg : SUCCESS
     * statusCode : 0
     */

    private String desc;
    private String msg;
    private int statusCode;
    private List<String> data;

    public String getDesc() {
        return desc;
    }

    public void setDesc(String desc) {
        this.desc = desc;
    }

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public int getStatusCode() {
        return statusCode;
    }

    public void setStatusCode(int statusCode) {
        this.statusCode = statusCode;
    }

    public List<String> getData() {
        return data;
    }

    public void setData(List<String> data) {
        this.data = data;
    }

    @Override
    public String toString() {
        return "BannerBean{" +
                "desc='" + desc + '\'' +
                ", msg='" + msg + '\'' +
                ", statusCode=" + statusCode +
                ", data=" + data +
                '}';
    }
}
