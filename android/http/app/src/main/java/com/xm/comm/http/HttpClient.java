package com.xm.comm.http;
import java.net.HttpURLConnection;
import java.net.URL;
public class HttpClient {
    private String m_url = "";
    public void Post(String paramAPI, String paramJSON) {
        // new HttpPost
    }

    public HttpClient() {
        init();
    }

    private void init() {
        m_url = "http://test.zdhsoft.com.cn";
    }

    private String getURL(String paramAPI) {
        return this.m_url + paramAPI;
    }

    private HttpURLConnection createHttpConnect(String paramURL) {
        URL url = new URL(paramURL);
        return (HttpURLConnection) url.openConnection();
    }
}
