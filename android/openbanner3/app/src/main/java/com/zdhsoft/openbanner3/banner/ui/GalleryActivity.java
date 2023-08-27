package com.zdhsoft.openbanner3.banner.ui;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.youth.banner.Banner;
import com.youth.banner.indicator.CircleIndicator;
import com.youth.banner.indicator.DrawableIndicator;
import com.zdhsoft.openbanner3.R;
import com.zdhsoft.openbanner3.banner.adapter.ImageAdapter;
import com.zdhsoft.openbanner3.banner.bean.DataBean;

public class GalleryActivity extends AppCompatActivity {

    // @BindView(R.id.banner1)
    Banner mBanner1;
    // @BindView(R.id.banner2)
    Banner mBanner2;
    // @BindView(R.id.indicator)
    DrawableIndicator indicator;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gallery);
        // ButterKnife.bind(this);
        mBanner1 = findViewById(R.id.banner1);
        mBanner2 = findViewById(R.id.banner2);
        indicator = findViewById(R.id.indicator);

        /**
         * 画廊效果
         */
        mBanner1.setAdapter(new ImageAdapter(DataBean.getTestData2()));
        mBanner1.setIndicator(new CircleIndicator(this));
        //添加画廊效果
        mBanner1.setBannerGalleryEffect(50, 10);
        //(可以和其他PageTransformer组合使用，比如AlphaPageTransformer，注意但和其他带有缩放的PageTransformer会显示冲突)
        //添加透明效果(画廊配合透明效果更棒)
        //mBanner1.addPageTransformer(new AlphaPageTransformer());


        /**
         * 魅族效果
         */
        mBanner2.setAdapter(new ImageAdapter(DataBean.getTestData()));
        mBanner2.setIndicator(indicator,false);
        //添加魅族效果
        mBanner2.setBannerGalleryMZ(20);



    }


}