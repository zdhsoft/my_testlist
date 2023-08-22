package com.zdhsoft.bannertest;

import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.RelativeLayout;

import androidx.viewpager.widget.ViewPager;

import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.List;

public class BannerView extends RelativeLayout {
    private static final int ITEM_COUNT = 3;
    private Context context;

    private ViewPager viewPager;
    private List<View> viewList;
    private List<Integer> imgResourceList;
    private RotationHandler routationHandler;

    public BannerView(Context context, AttributeSet attrs) {
        super(context, attrs);
        this.context = context;
        init();
    }

    private void init() {
        this.initViewPager();
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
                Log.d("hahaha", "position = " + position);
                if (position == viewList.size()-1){
                    viewPager.setCurrentItem(1, false);
                } else if (position == 0){
                    viewPager.setCurrentItem(viewList.size() - 2, false);
                }
            }

            @Override
            public void onPageScrollStateChanged(int state) {

            }
        });

        routationHandler = new RotationHandler(this);
        routationHandler.sendEmptyMessageDelayed(1, 2000);

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
            bannerView.viewPager.setCurrentItem(bannerView.viewPager.getCurrentItem() + 1);
        }
    }
}
