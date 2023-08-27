package com.zdhsoft.openbanner3.banner.ui;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.viewpager2.adapter.FragmentStateAdapter;
import androidx.viewpager2.widget.ViewPager2;

import com.google.android.material.tabs.TabLayout;
import com.google.android.material.tabs.TabLayoutMediator;
import com.youth.banner.Banner;
import com.youth.banner.indicator.CircleIndicator;
import com.zdhsoft.openbanner3.R;
import com.zdhsoft.openbanner3.banner.adapter.ImageAdapter;
import com.zdhsoft.openbanner3.banner.bean.DataBean;

public class Vp2FragmentRecyclerviewActivity extends AppCompatActivity {

    // @BindView(R.id.vp2)
    ViewPager2 viewPager2;
    // @BindView(R.id.tab_layout)
    TabLayout mTabLayout;
    // @BindView(R.id.banner)
    Banner mBanner;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_vp2_fragment_recyclerview);
        viewPager2 = findViewById(R.id.vp2);
        mTabLayout = findViewById(R.id.tab_layout);
        mBanner = findViewById(R.id.banner);
        // ButterKnife.bind(this);

        viewPager2.setAdapter(new FragmentStateAdapter(this) {
            @NonNull
            @Override
            public Fragment createFragment(int position) {
                if (position == 0) {
                    return BannerListFragment.newInstance(position);
                } else if (position == 1) {
                    return BlankFragment.newInstance();
                } else {
                    return BannerFragment.newInstance();
                }
            }

            @Override
            public int getItemCount() {
                return 3;
            }
        });

        new TabLayoutMediator(mTabLayout, viewPager2, (tab, position) -> {
            tab.setText("页面" + position);
        }).attach();


        mBanner.addBannerLifecycleObserver(this)
                .setAdapter(new ImageAdapter(DataBean.getTestData()))
                .setIntercept(false)
                .setIndicator(new CircleIndicator(this));
    }
}
