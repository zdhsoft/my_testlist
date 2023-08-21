package com.banner.superbanner.activity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.AppCompatImageView;
import android.widget.LinearLayout;

import com.banner.superbanner.R;
import com.banner.superbanner.SuperBanner;
import com.banner.superbanner.animation.DepthPageTransformer;
import com.banner.superbanner.animation.ZoomOutPageTransformer;

import java.util.ArrayList;
import java.util.List;

public class DemoActivity extends AppCompatActivity {
    private SuperBanner mSuperBanner3;
    private SuperBanner mSuperBanner4;
    private LinearLayout mIndicatorLayout3;
    private LinearLayout mIndicatorLayout4;
    private List imageList;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_demo);
        mSuperBanner3 = findViewById(R.id.view_pager3);
        mSuperBanner4 = findViewById(R.id.view_pager4);
        mIndicatorLayout3 = findViewById(R.id.indicator_ly3);
        mIndicatorLayout4 = findViewById(R.id.indicator_ly4);
        initData();
        show3();
        show4();
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

    @Override
    protected void onStart() {
        super.onStart();
        if (mSuperBanner3 != null) {
            mSuperBanner3.executeDelayedTask();
        }

        if (mSuperBanner4 != null) {
            mSuperBanner4.executeDelayedTask();
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (mSuperBanner3 != null) {
            mSuperBanner3.killDelayedTask();
        }
        if (mSuperBanner4 != null) {
            mSuperBanner4.killDelayedTask();
        }
    }

    /**
     * @Description 幻灯线性淡出效果
     */
    private void show3() {
        mSuperBanner3.setDataOrigin(imageList)
                .setSwitchAnimation(new DepthPageTransformer())
                .setRoundRadius(20)
                .setViewPagerScroller(1000)
                .setItemPadding(10)
                .setIndicatorLayoutParam(mIndicatorLayout3,R.drawable.indicator_select,6,6,10)
                .start();
    }

    /**
     * @Description 3D画廊效果
     */
    private void show4() {
        //最好加上这段缓存API 否则可能手指滑动时 会有item粘连情况
        mSuperBanner4.setOffscreenPageLimit(imageList.size());
        mSuperBanner4.setDataOrigin(imageList)
                .setSwitchAnimation(new ZoomOutPageTransformer())
                .setIndicatorLayoutParam(mIndicatorLayout4,R.drawable.indicator_select)
                .setViewPagerScroller(1000)
                .start();
    }

    public static void startActivityDemo2(Context context) {
        Intent intent = new Intent(context,DemoActivity.class);
        context.startActivity(intent);

    }

}
