package com.zdhsoft.openbanner3.banner.ui;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.youth.banner.Banner;
import com.youth.banner.indicator.CircleIndicator;
import com.youth.banner.util.BannerUtils;
import com.zdhsoft.openbanner3.R;
import com.zdhsoft.openbanner3.banner.adapter.ImageNetAdapter;
import com.zdhsoft.openbanner3.banner.bean.DataBean;

public class BlankFragment extends Fragment {

    public static Fragment newInstance() {
        return new BlankFragment();
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.test,null);
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        LinearLayout linearLayout = getView().findViewById(R.id.ll_view);

        //通过new的方式创建banner
        Banner banner = new Banner(getActivity());
        banner.setAdapter(new ImageNetAdapter(DataBean.getTestData3()));
        banner.addBannerLifecycleObserver(this);
        banner.setIndicator(new CircleIndicator(getActivity()));

        //将banner加入到父容器中，实际使用不一定一样
        linearLayout.addView(banner, LinearLayout.LayoutParams.MATCH_PARENT, (int) BannerUtils.dp2px(120));
    }
}

