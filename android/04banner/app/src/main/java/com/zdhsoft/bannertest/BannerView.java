package com.zdhsoft.bannertest;

import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

import androidx.viewpager.widget.ViewPager;

import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.List;

public class BannerView extends RelativeLayout {
    private static final int ITEM_COUNT = 5;
    private Context context;

    private ViewPager viewPager;
    private List<View> viewList;
    private List<Integer> imgResourceList;
    private RotationHandler rotationHandler;
    private LinearLayout dotLayout;    //水平线性布局

    public BannerView(Context context, AttributeSet attrs) {
        super(context, attrs);
        this.context = context;
        init();
    }

    private void init() {
        this.initViewPager();
        this.initDot();
    }

    private void initDot() {
        dotLayout = new LinearLayout(context);
        dotLayout.setOrientation(LinearLayout.HORIZONTAL);   //水平布局
        //添加圆点
        for (int i=0; i<ITEM_COUNT; i++){
            ImageView dotImage = new ImageView(context);
            if (i == 0){
                dotImage.setImageResource(R.drawable.dot_white);
            } else {
                dotImage.setImageResource(R.drawable.dot_gray);
            }

            //为ImageView创建布局参数
            MarginLayoutParams layoutParams = new MarginLayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT,
                    ViewGroup.LayoutParams.WRAP_CONTENT);
            //设置边距
            layoutParams.leftMargin = 10;
            layoutParams.rightMargin = 10;
            //动态
            dotLayout.addView(dotImage, layoutParams);
        }

        //为dotLayout设置布局参数
        LayoutParams layoutParams = new LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        layoutParams.bottomMargin = 30;
        layoutParams.addRule(CENTER_HORIZONTAL);
        layoutParams.addRule(ALIGN_PARENT_BOTTOM);
        addView(dotLayout, layoutParams);
    }

    private void initViewPager() {
        viewPager = new ViewPager(context);
        viewList = new ArrayList<View>();
        imgResourceList = new ArrayList<Integer>();
        imgResourceList.add(R.drawable.a1);
        imgResourceList.add(R.drawable.a2);
        imgResourceList.add(R.drawable.a3);
        imgResourceList.add(R.drawable.a4);
        imgResourceList.add(R.drawable.a5);

        for(int i =0; i < imgResourceList.size(); i++) {
            ImageView imgView = new ImageView(context);
            imgView.setImageResource(imgResourceList.get(i));
            imgView.setScaleType(ImageView.ScaleType.FIT_XY);
            viewList.add(imgView);
        }

        viewPager.setAdapter(new BannerPagerAdapter(viewList));
        addView(viewPager, new LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));

        viewPager.setCurrentItem(1, false);

        viewPager.addOnPageChangeListener(new ViewPager.OnPageChangeListener() {

            @Override
            public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {

            }

            @Override
            public void onPageSelected(int position) {
                Log.d("hahaha", "position = " + position + " size = " + viewList.size());
                int currIdx = -1;
                if (position > viewList.size()){
                    // viewPager.setCurrentItem(1, false);
                    currIdx = 1;
                } else if (position < 0){
                    // viewPager.setCurrentItem(viewList.size() - 1, false);
                    currIdx = viewList.size();
                }
                Log.d("hahaha", "position = " + position + " size = " + viewList.size() + " currIdx = " + currIdx);
                if (currIdx != -1) {
                    viewPager.setCurrentItem(currIdx, false);
                }
            }

            @Override
            public void onPageScrollStateChanged(int state) {

            }
        });

        rotationHandler = new RotationHandler(this);
        rotationHandler.sendEmptyMessageDelayed(1, 2000);

    }

    private static class RotationHandler extends Handler {
        private WeakReference<BannerView> bannerReference;

        public RotationHandler(BannerView bannerView) {
            bannerReference = new WeakReference<>(bannerView);
        }

        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            sendEmptyMessageDelayed(1, 2000);
            BannerView bannerView = bannerReference.get();
            // bannerView.viewPager.setCurrentItem(bannerView.viewPager.getCurrentItem() + 1);
        }
    }
    @Override
    protected void onDetachedFromWindow() {
        super.onDetachedFromWindow();
        rotationHandler.removeCallbacksAndMessages(null);
    }

}
