package com.zdhsoft.openbanner3.banner.adapter;

import android.view.LayoutInflater;
import android.view.ViewGroup;

import com.youth.banner.adapter.BannerAdapter;
import com.zdhsoft.openbanner3.R;
import com.zdhsoft.openbanner3.banner.bean.DataBean;
import com.zdhsoft.openbanner3.banner.viewholder.ImageTitleHolder;

import java.util.List;

public class ImageTitleAdapter extends BannerAdapter<DataBean, ImageTitleHolder> {

    public ImageTitleAdapter(List<DataBean> mDatas) {
        super(mDatas);
    }

    @Override
    public ImageTitleHolder onCreateHolder(ViewGroup parent, int viewType) {
        return new ImageTitleHolder(LayoutInflater.from(parent.getContext()).inflate(R.layout.banner_image_title, parent, false));
    }

    @Override
    public void onBindView(ImageTitleHolder holder, DataBean data, int position, int size) {
        holder.imageView.setImageResource(data.imageRes);
        holder.title.setText(data.title);
    }

}
