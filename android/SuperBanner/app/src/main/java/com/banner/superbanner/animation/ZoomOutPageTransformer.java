package com.banner.superbanner.animation;

import android.support.v4.view.ViewPager;
import android.util.Log;
import android.view.View;
/**
  *@Description 与简书文章中直接从官方指南中copy的类不同  此类有所更改
 */
public class ZoomOutPageTransformer implements ViewPager.PageTransformer {
    private static final float MAX_SCALE = 1.0f;

    private static final float MIN_SCALE = 0.87f;

    private static final float MIN_ALPHA = 0.8f;

    @Override
    public void transformPage(View view, float position) {
        if (position < -1) {
            view.setScaleX(MIN_SCALE);
            view.setScaleY(MIN_SCALE);
            view.setAlpha(MIN_ALPHA);
        } else if (position <= 1) {
            float scaleFactor = MIN_SCALE + (1 - Math.abs(position)) * (MAX_SCALE - MIN_SCALE);
            if (position > 0) {
                view.setTranslationX(-scaleFactor);
            } else if (position < 0) {
                view.setTranslationX(scaleFactor);
            }
            view.setScaleY(scaleFactor);
            view.setScaleX(scaleFactor);
            float alpha = MIN_ALPHA + (1 - MIN_ALPHA) * (1 - Math.abs(position));
            view.setAlpha(alpha);

        } else {
            view.setScaleX(MIN_SCALE);
            view.setScaleY(MIN_SCALE);
            view.setAlpha(MIN_ALPHA);
        }
    }
}