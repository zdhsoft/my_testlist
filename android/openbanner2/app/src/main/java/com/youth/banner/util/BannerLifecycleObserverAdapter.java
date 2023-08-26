package com.youth.banner.util;

import androidx.lifecycle.LifecycleObserver;
import androidx.lifecycle.LifecycleOwner;

import androidx.lifecycle.DefaultLifecycleObserver ;

public class BannerLifecycleObserverAdapter implements LifecycleObserver, DefaultLifecycleObserver  {
    private final BannerLifecycleObserver mObserver;
    private final LifecycleOwner mLifecycleOwner;

    public BannerLifecycleObserverAdapter(LifecycleOwner lifecycleOwner, BannerLifecycleObserver observer) {
        mLifecycleOwner = lifecycleOwner;
        mObserver = observer;
    }

    // @LifecycleEventObserver(Lifecycle.Event.ON_START)
    public void onStart() {
        LogUtils.i("onStart");
        mObserver.onStart(mLifecycleOwner);
    }

    // @OnLifecycleEvent(Lifecycle.Event.ON_STOP)
    public void onStop() {
        LogUtils.i("onStop");
        mObserver.onStop(mLifecycleOwner);
    }

    // @OnLifecycleEvent(Lifecycle.Event.ON_DESTROY)
    public void onDestroy() {
        LogUtils.i("onDestroy");
        mObserver.onDestroy(mLifecycleOwner);
    }
}