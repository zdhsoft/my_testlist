package com.zdhsoft.openbanner;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import com.youth.banner.Banner;
import com.youth.banner.indicator.RoundLinesIndicator;
// import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;
public class MainActivity extends AppCompatActivity {
    // @BindView(R.id.banner)
    Banner banner;
    // @BindView(R.id.indicator)
    RoundLinesIndicator indicator;
    // @BindView(R.id.swipeRefresh)
//     SwipeRefreshLayout refresh;
//
//    public void useBanner() {
//        //--------------------------简单使用-------------------------------
//        banner.addBannerLifecycleObserver(this)//添加生命周期观察者
//                .setAdapter(new BannerExampleAdapter(DataBean.getTestData()))
//                .setIndicator(new CircleIndicator(this));
//
//        //—————————————————————————如果你想偷懒，而又只是图片轮播————————————————————————
//        banner.setAdapter(new BannerImageAdapter<DataBean>(DataBean.getTestData3()) {
//                    @Override
//                    public void onBindView(BannerImageHolder holder, DataBean data, int position, int size) {
//                        //图片加载自己实现
//                        Glide.with(holder.itemView)
//                                .load(data.imageUrl)
//                                .apply(RequestOptions.bitmapTransform(new RoundedCorners(30)))
//                                .into(holder.imageView);
//                    }
//                })
//                .addBannerLifecycleObserver(this)//添加生命周期观察者
//                .setIndicator(new CircleIndicator(this));
//        //更多使用方法仔细阅读文档，或者查看demo
//    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}