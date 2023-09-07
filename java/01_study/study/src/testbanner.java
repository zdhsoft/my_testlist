import com.alibaba.fastjson.JSON;
import com.google.gson.Gson;
import okhttp3.*;

import java.io.IOException;

public class testbanner {
    public testbanner() {

    }

    public void doTest() {
        String url = "https://test.zdhsoft.com.cn";
        String banner_list = "/toc/v1/banner_list";
        OkHttpClient okHttpClient = new OkHttpClient();
        final Request request = new Request.Builder()
                .url(url + banner_list)
                .get()//默认就是GET请求，可以不写
                .build();
        Call call = okHttpClient.newCall(request);
        call.enqueue(new Callback() {
            @Override
            public void onFailure(Call call, IOException e) {
                System.out.println("onFailure:" + e.toString());
            }

            @Override
            public void onResponse(Call call, Response response) throws IOException {
                Object o = JSON.parse(response.body().string());
                System.out.println(o.toString());
//                Gson g = new Gson();
//                Object o = g.fromJson(response.body().toString());
                System.out.println("onResponse: " + response.body().string());
            }
        });
    }
}
