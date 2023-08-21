package com.banner.superbanner.callback;

import android.view.View;

import java.util.List;
/**
  *@Description banner内部，适配器中加载图片的接口
  *
 */
public interface OnLoadImageAdapterListener {
    //加载图片,适配器中回调给SuperBanner
    void loadAdapterImage(List imageData, int position, View imageView);
}
