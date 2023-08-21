package com.banner.superbanner.activity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;
import com.banner.superbanner.R;
import com.banner.superbanner.SuperBanner;
import com.bumptech.glide.request.RequestOptions;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    private SuperBanner mSuperBanner;
    private LinearLayout mIndicatorLayout;
    private SuperBanner mSuperBanner2;
    private LinearLayout mIndicatorLayout2;
    private List imageList;
    private TextView openActivity;
    private RequestOptions mOptions;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mSuperBanner = findViewById(R.id.view_pager);
        mSuperBanner2 = findViewById(R.id.view_pager2);
        mIndicatorLayout = findViewById(R.id.indicator_ly);
        mIndicatorLayout2 = findViewById(R.id.indicator_ly2);
        openActivity = findViewById(R.id.open);
        initData();
        show1();
        show2();
        openActivity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                DemoActivity.startActivityDemo2(MainActivity.this);
            }
        });
        /* API示例
        mSuperBanner.
                //setDataOrigin(imageList)设置数据源
                // 重载方法，设置指示器布局及指示器样式,不需要就无需调用 后三个参数代表指示器的宽高和间距(可选设置 有默认效果)
                //.setIndicatorLayoutParam(mIndicatorLayout, R.drawable.indicator_select, 6, 6, 10)
                //设置ViewPager的item切换速度,不需要更改速度就无需调用
                //.setViewPagerScroller(1000)
                //设置自动轮播间隔时间，重载方法 默认开始执行定时任务时间为2秒
                //.setAutoIntervalTime(3000, 2000)
                //.closeAutoBanner(true)  关闭自动轮播
                //.closeInfiniteSlide(true)  关闭手指滑动无限循环
                //设置item的padding值(上下左右)
                //.setItemPadding(14)
                //设置圆角半径 一旦设置值(大于0) 就代表item使用圆角样式
                //.setRoundRadius(10)
                //.setSwitchAnimation()  设置ViewPager切换动画
                //实现图片加载回调(一定要在start()之前执行) 一但实现回调就表示图片加载交由调用层处理 否则由适配器内部加载
                .setOnLoadImageListener(new SuperBanner.OnLoadImageListener() {
                    @Override
                    public void onLoadImage(List imageData, int position, View imageView) {
                        if (mOptions == null) {
                            mOptions = RequestOptions.bitmapTransform(new CenterCropRoundCornerTransform(20));
                        }
                        int resourceId = (int) imageData.get(position);
                        Glide.with(MainActivity.this)
                                .load(resourceId)
                                .apply(mOptions)
                                .into((ImageView) imageView);
                    }
                })

                // 实现item点击事件回调(一定要在start()之前执行)
                .setOnItemClickListener(new SuperBanner.OnItemClickListener() {
                    @Override
                    public void onItemClick(int position) {
                        Log.i("BannerItemPosition: ", position + "");
                    }
                })
                // 此函数要最后执行
                //.start();
*/
    }


    /**
     * @Description 经典效果
     */
    private void show1() {
        mSuperBanner.setDataOrigin(imageList)
                .setIndicatorLayoutParam(mIndicatorLayout, R.drawable.indicator_select)
                .start();


    }

    /**
     * @Description 圆角+内边距+延时切换
     */
    private void show2() {
        mSuperBanner2.setDataOrigin(imageList)
                .setIndicatorLayoutParam(mIndicatorLayout2, R.drawable.indicator_select, 6, 6, 10)
                .setViewPagerScroller(1000)
                .setItemPadding(15)
                .setRoundRadius(20)
                .start();


    }

    @Override
    protected void onPause() {
        super.onPause();
        //取消轮播
        if (mSuperBanner != null) {
            mSuperBanner.killDelayedTask();
        }
        if (mSuperBanner2 != null) {
            mSuperBanner2.killDelayedTask();
        }
    }

    @Override
    protected void onStart() {
        super.onStart();
        //开始轮播
        if (mSuperBanner != null) {
            mSuperBanner.executeDelayedTask();
        }
        if (mSuperBanner2 != null) {
            mSuperBanner2.executeDelayedTask();
        }
    }

    private void initData() {
        if (imageList != null) {
            imageList.clear();
        }
        imageList = new ArrayList();
        imageList.add(R.mipmap.banner_01);
        imageList.add(R.mipmap.banner_02);
        imageList.add(R.mipmap.banner_03);
        imageList.add(R.mipmap.banner_04);
        imageList.add(R.mipmap.banner_05);
        imageList.add(R.mipmap.banner_06);

    }
}
