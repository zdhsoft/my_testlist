package com.banner.superbanner;

import android.content.Context;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.view.ViewPager;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.LinearLayout;

import com.banner.superbanner.adapter.BannerAdapter;
import com.banner.superbanner.banner_definition.SuperBannerScroller;
import com.banner.superbanner.callback.OnItemClickAdapterListener;
import com.banner.superbanner.callback.OnLoadImageAdapterListener;

import java.lang.reflect.Field;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

/**
 * @Description 所有和ViewPager相关的业务逻辑以及布局都内聚了在了本类
 * 并向外提供API
 */
public class SuperBanner extends ViewPager implements OnLoadImageAdapterListener, OnItemClickAdapterListener {
    private final String TAG = "SuperBanner";
    private Timer mTimer;
    private TimerTask mTimerTask;
    //第一次执行的定时器run方法的时间引用(单位:毫秒)
    private long DELAY_START_RUN;
    //执行run方法后 执行任务的间隔时间的引用(单位:毫秒)
    private long INTERVAL_TIME;
    //item切换速度类的引用
    private SuperBannerScroller mSuperBannerScroller;
    //数据源的引用
    private List mImageDataList;
    //自动轮播的开关标记
    private boolean mIsClose = false;
    //手指滑动无限循环的开关标记
    private boolean mIsCloseInfiniteSlide = false;
    //返回给调用层加载图片的回调接口的引用
    public OnLoadImageListener mOnLoadImageListener;
    public OnItemClickListener mOnItemClickListener;
    //适配器的引用
    private BannerAdapter mBannerAdapter;
    //指示器的宽度
    private int mIndicatorWidth;
    //指示器的高度
    private int mIndicatorHeight;
    //指示器的间距
    private int mIndicatorSpace;
    //item View的padding值
    private int mPadding;
    //item圆角半径
    private int mRadius;
    //指示器的父布局
    private LinearLayout mIndicatorLayout;

    @Override
    public void onItemAdapterClick(int position) {
        if (null != mOnItemClickListener) {
            mOnItemClickListener.onItemClick(position);
        }

    }

    /**
      *@Description SuperBanner内部接口 主要用于将适配器加载图片的回调进行二次回调给调用层
      *
     */
    public interface OnLoadImageListener {
        //imageData 数据源
        //position为经过取余处理过后的position 无需再进行取余
        //imageView 具体展示图片的控件
        void onLoadImage(List imageData, int position, View imageView);
    }

    //SuperBanner内部接口 主要用于将适配器条目点击事件的回调二次回调给调用层
    public interface OnItemClickListener {
        void onItemClick(int position);
    }

    public SuperBanner setOnItemClickListener(OnItemClickListener onItemClickListener) {
        this.mOnItemClickListener = onItemClickListener;
        return this;

    }


    /**
     * @Description 适配器的加载图片回调 这里进行二次传递给调用层
     */
    @Override
    public void loadAdapterImage(List imageData, int position, View imageView) {
        if (mOnLoadImageListener != null) {
            //交由调用层处理
            mOnLoadImageListener.onLoadImage(imageData, position, imageView);
        }
    }


    public SuperBanner(@NonNull Context context) {
        this(context, null);
    }

    public SuperBanner(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);

    }

    /**
     * @Description 图片加载的回调监听
     */
    public SuperBanner setOnLoadImageListener(OnLoadImageListener onLoadImageListener) {
        this.mOnLoadImageListener = onLoadImageListener;
        return this;

    }

    /**
     * @Description 接收指示器的布局和指示器背景资源
     */
    public SuperBanner setIndicatorLayoutParam(LinearLayout indicatorLayout, int indicatorDrawable) {
        this.mIndicatorLayout = indicatorLayout;
        initIndicatorView(mIndicatorLayout, indicatorDrawable);
        return this;

    }

    /**
     * @Description 重载方法 接收指示器的布局和指示器背景资源和指示器的宽、高、间距
     */
    public SuperBanner setIndicatorLayoutParam(LinearLayout indicatorLayout, int indicatorDrawable, int indicatorWidth, int indicatorHeight, int indicatorSpace) {
        this.mIndicatorWidth = indicatorWidth;
        this.mIndicatorHeight = indicatorHeight;
        this.mIndicatorSpace = indicatorSpace;
        setIndicatorLayoutParam(indicatorLayout, indicatorDrawable);
        return this;

    }

/**
  *@Description 启动函数 任何情况下 此函数都需要最后执行
  *
 */
    public void start() {
        //初始化适配器
        initBannerAdapter();
        //初始化手指触摸停止轮播 手指松开开启轮播
        setViewPagerTouchListener();
        //初始化ViewPager页面状态改变监听
        initPageChangeListener();
        //设置初始化时默认选中指示器第一个
        updateIndicatorSelectState(0);
        //设置ViewPager索引位置处于总长度的一半,为了无限循环滑动
        setViewPagerCurrentItem();
        //开始执行自动轮播
        executeDelayedTask();
    }

    private void setViewPagerCurrentItem() {
        if (mIsCloseInfiniteSlide) {
            return;
        }
        setCurrentItem(getAdapter() == null ? 0 : (getAdapter().getCount() == 0 ? 0 : ((getAdapter().getCount()) / 2)));
    }

    /**
     * @Description 设置ViewPager数据源
     */
    public SuperBanner setDataOrigin(List dataOrigin) {
        if (dataOrigin == null) {
            throw new RuntimeException("The data source cannot be empty!");
        }
        if (mImageDataList != null) {
            mImageDataList.clear();
        }
        this.mImageDataList = dataOrigin;
        return this;
    }


    /**
     * @Description 设置切换动画
     */
    public SuperBanner setSwitchAnimation(PageTransformer pageTransformer) {
        if (pageTransformer != null) {
            setPageTransformer(true, pageTransformer);
        }
        return this;
    }

    /**
     * @Description 设置轮播间隔时间
     */
    public SuperBanner setAutoIntervalTime(long intervalTime) {
        this.INTERVAL_TIME = intervalTime;
        return this;
    }

    /**
     * @Description 设置开始执行轮播的时间(第一次执行run方法)
     */
    public SuperBanner setAutoIntervalTime(long delay, long intervalTime) {
        this.DELAY_START_RUN = delay;
        setAutoIntervalTime(intervalTime);
        return this;
    }


    /**
     * @Description 设置ViewPager Item切换速度
     * @param scrollDuration 单位(毫秒)
     */
    public SuperBanner setViewPagerScroller(int scrollDuration) {
        if (mSuperBannerScroller == null) {
            mSuperBannerScroller = new SuperBannerScroller(getContext());
        }
        mSuperBannerScroller.setScrollDuration(scrollDuration);
        updateViewPagerScroller();
        return this;

    }
/**
  *@Description 设置item的padding值(上下左右内边距)
  *
 */
    public SuperBanner setItemPadding(int padding) {
        this.mPadding = padding;
        return this;
    }

    private void initBannerAdapter() {
        if (getChildCount() > 0) {
            removeAllViews();
        }
        if (mBannerAdapter == null) {
            mBannerAdapter = new BannerAdapter(mImageDataList, mIsCloseInfiniteSlide, mPadding, mRadius, mOnLoadImageListener == null ? null : this, this);
        }
        setAdapter(mBannerAdapter);
    }

    /**
     * @Description 设置item圆角半径
     */
    public SuperBanner setRoundRadius(int radius) {
        this.mRadius = radius;
        return this;

    }

    /**
     * @Description 通过反射的方式拿到ViewPager的mScroller，然后替换成自己设置的值
     */
    private void updateViewPagerScroller() {
        try {
            Field field = ViewPager.class.getDeclaredField("mScroller");
            field.setAccessible(true);
            //利用反射把mScroller域替换为自己定义的mSuperBannerScroller
            field.set(this, mSuperBannerScroller);
        } catch (NoSuchFieldException e) {
            Log.e(TAG, e.getMessage());
        } catch (IllegalAccessException e) {
            Log.e(TAG, e.getMessage());
        }
    }

    /**
     * @param isClose true 为关闭  默认开启
     * @Description 关闭定时轮播
     */
    public SuperBanner closeAutoBanner(Boolean isClose) {
        this.mIsClose = isClose;
        return this;

    }

    /**
     * @param isCloseInfiniteSlide true表示关闭，默认为开启
     * @Description 关闭手指无限循环滑动
     */
    public SuperBanner closeInfiniteSlide(boolean isCloseInfiniteSlide) {
        this.mIsCloseInfiniteSlide = isCloseInfiniteSlide;
        return this;

    }

    /**
     * 开启一个延时任务并执行
     */
    public void executeDelayedTask() {

        //在创建任务之前 一定要检查清理未回收的任务，保证只有一组Timer+TimerTask
        killDelayedTask();
        if (mIsClose) {
            return;
        }
        mTimer = new Timer();
        mTimerTask = new TimerTask() {
            @Override
            public void run() {
                post(new Runnable() {
                    @Override
                    public void run() {
                        //显示下一页
                        showNextPage();
                    }
                });
            }
        };
        //默认效果为2秒钟后执行run方法 间隔3秒执行一次任务
        if (DELAY_START_RUN == 0 && INTERVAL_TIME == 0) {
            mTimer.schedule(mTimerTask, 2000, 3000);
        } else if (DELAY_START_RUN == 0 && INTERVAL_TIME != 0) {
            //如果不指定何时开始执行run方法 默认2秒钟后执行run方法
            mTimer.schedule(mTimerTask, 2000, INTERVAL_TIME);
        } else if (DELAY_START_RUN != 0 && INTERVAL_TIME == 0) {
            //如果间隔执行时间为0 直接走默认方法
            mTimer.schedule(mTimerTask, DELAY_START_RUN, 3000);
        } else {
            //正常执行
            mTimer.schedule(mTimerTask, DELAY_START_RUN, INTERVAL_TIME);
        }


    }

    /**
     * * @Description 初始化ViewPager底部指示器
     * @param indicatorLayout   指示器的父布局 由调用者提供
     * @param indicatorDrawable 指示器的样式 由调用者提供
     */
    private void initIndicatorView(LinearLayout indicatorLayout, int indicatorDrawable) {
        if (indicatorLayout == null) {
            return;
        }
        if (indicatorLayout.getChildCount() > 0) {
            indicatorLayout.removeAllViews();
        }
        for (int i = 0; i < mImageDataList.size(); i++) {
            //默认指示器的宽高为6dp
            LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(dpToPx(mIndicatorWidth == 0 ? 6 : mIndicatorWidth), dpToPx(mIndicatorHeight == 0 ? 6 : mIndicatorHeight));
            //默认指示器的间距为8dp
            lp.leftMargin = dpToPx(mIndicatorSpace == 0 ? 8 : mIndicatorSpace);
            View ivIndicator = new View(getContext());
            //[R.drawable.indicator_select]为指示器的背景资源 相关样式可替换
            ivIndicator.setBackgroundResource(indicatorDrawable);
            ivIndicator.setLayoutParams(lp);
            indicatorLayout.addView(ivIndicator);
        }

    }


    /**
     * @param position ViewPager中的item的position
     * @Description 随着ViewPager页面滑动 更新指示器选中状态
     */
    private void updateIndicatorSelectState(int position) {
        if (mIndicatorLayout == null) {
            return;
        }
        //此时传入的position还未经过处理 同样的需要对position进行取余数处理
        position = position % mIndicatorLayout.getChildCount();
        //循环获取指示器父布局中所有的子View
        for (int i = 0; i < mIndicatorLayout.getChildCount(); i++) {
            //给每个子view设置选中状态
            //当i == position为True的时候触发选中状态反之则设置成未选中
            mIndicatorLayout.getChildAt(i).setSelected(i == position);

        }
    }


    /**
     * @Description 将dp转为px
     */
    private int dpToPx(int dp) {
        //获取手机屏幕像素密度
        float phoneDensity = getResources().getDisplayMetrics().density;
        //加0.5f是为了四舍五入 避免丢失精度
        return (int) (dp * phoneDensity + 0.5f);

    }

    /**
     * @Description 添加ViewPager页面改变事件的监听
     */
    private void initPageChangeListener() {
        addOnPageChangeListener(new ViewPager.OnPageChangeListener() {
            @Override
            public void onPageScrolled(int position, float v, int position1) {

            }

            @Override
            public void onPageSelected(int position) {
                updateIndicatorSelectState(position);
            }

            @Override
            public void onPageScrollStateChanged(int position) {

            }
        });
    }

    /**
     * 取消(清理)延时任务
     */
    public void killDelayedTask() {
        if (mTimer != null) {
            mTimer.cancel();
            mTimer = null;
        }
        if (mTimerTask != null) {
            mTimerTask.cancel();
            mTimerTask = null;
        }
    }

    /**
     * @Description 显示下一页
     */
    private void showNextPage() {
        //获取到当前页面的位置
        int currentPageLocation = getCurrentItem();
        //设置item位置为: 当前页面的位置+1
        setCurrentItem(currentPageLocation + 1);
    }

    /**
     * @Description 在手指按下和移动时 清除延时任务，待手指松开重新创建任务
     */
    private void setViewPagerTouchListener() {
        setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        killDelayedTask();
                        break;
                    case MotionEvent.ACTION_MOVE:
                        killDelayedTask();
                        break;
                    case MotionEvent.ACTION_UP:
                        executeDelayedTask();
                        break;
                }
                return false;
            }
        });
    }

}
