package com.zdhsoft.openbanner3.banner.ui;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.youth.banner.Banner;
import com.youth.banner.indicator.RectangleIndicator;
import com.youth.banner.util.BannerUtils;
import com.zdhsoft.openbanner3.R;
import com.zdhsoft.openbanner3.banner.adapter.ImageNetAdapter;
import com.zdhsoft.openbanner3.banner.bean.DataBean;

//import butterknife.BindView;
//import butterknife.ButterKnife;

public class BannerFragment extends Fragment {
    Banner banner;

    public static Fragment newInstance(Banner paramBanner) {
        return new BannerFragment(paramBanner);
    }

    public BannerFragment(Banner paramBanner) {
        super();
        banner = paramBanner;
    }
    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.banner, container, false);
        // ButterKnife.bind(this, view);
        return view;
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        banner.setAdapter(new ImageNetAdapter(DataBean.getTestData3()));
        banner.setIndicator(new RectangleIndicator(getActivity()));
        banner.setIndicatorSpace((int) BannerUtils.dp2px(4));
        banner.setIndicatorRadius(0);
    }

    @Override
    public void onStart() {
        super.onStart();
        banner.start();
    }

    @Override
    public void onStop() {
        super.onStop();
        banner.stop();
    }
}
