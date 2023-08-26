package com.zdhsoft.openbanner;

import android.view.ViewGroup;
import android.widget.ImageView;

import com.youth.banner.adapter.BannerAdapter;
import com.zdhsoft.openbanner.bean.DataBean;
import com.zdhsoft.openbanner.viewHolder.ImageHolder;

import java.util.List;

public class ImageAdapter extends BannerAdapter<DataBean, ImageHolder> {
    public ImageAdapter(List<DataBean> dataList) {
        super(dataList);
    }

    @Override
    public ImageHolder onCreateHolder(ViewGroup parent, int viewType) {
        ImageView imageView = new ImageView(parent.getContext());
        //注意，必须设置为match_parent，这个是viewpager2强制要求的
        imageView.setLayoutParams(new ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT));
        imageView.setScaleType(ImageView.ScaleType.CENTER_CROP);
        return new ImageHolder(imageView);
    }

    @Override
    public void onBindView(ImageHolder holder, DataBean data, int position, int size) {
        holder.imageView.setImageResource(data.imageRes);
    }

}
