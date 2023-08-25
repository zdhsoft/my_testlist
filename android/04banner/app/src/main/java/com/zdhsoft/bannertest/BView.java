package com.zdhsoft.bannertest;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.viewpager.widget.PagerAdapter;
import androidx.viewpager.widget.ViewPager;

import java.util.ArrayList;
import java.util.List;

public class BView extends ViewPager {
    private List<Integer> imageList;
    public BView(@NonNull Context context) {
        super(context);
        List<Integer> v = new ArrayList<Integer>();
        v.add(R.drawable.a1);
        v.add(R.drawable.a2);
        v.add(R.drawable.a3);
        v.add(R.drawable.a4);
        v.add(R.drawable.a5);
        setImageList(v);
    }

    public BView(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public void setImageList(List<Integer> paramImgList) {
        this.imageList = paramImgList;
        setAdapter(new BAdapter());
        // setAdapter(new );
    }

    private class BAdapter extends PagerAdapter {

        @Override
        public int getCount() {
            return imageList.size();
        }

        @Override
        public boolean isViewFromObject(@NonNull View paramView, @NonNull Object paramObject) {
            return paramView == paramObject;
        }

        @NonNull
        @Override
        public Object instantiateItem(@NonNull ViewGroup container, int position) {
            ImageView imageView = new ImageView(getContext());
            imageView.setImageResource(imageList.get(position));
            imageView.setScaleType(ImageView.ScaleType.CENTER_CROP);
            container.addView(imageView);
            return imageView;
        }
        @Override
        public void destroyItem(@NonNull ViewGroup container, int position, @NonNull Object object) {
            container.removeView((View) object);
        }
    }

}
