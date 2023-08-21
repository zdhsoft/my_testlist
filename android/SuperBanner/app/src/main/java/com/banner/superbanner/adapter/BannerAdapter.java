package com.banner.superbanner.adapter;

import android.content.Context;
import android.support.annotation.NonNull;
import android.support.v4.view.PagerAdapter;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import com.banner.superbanner.callback.OnItemClickAdapterListener;
import com.banner.superbanner.glide.CenterCropRoundCornerTransform;
import com.banner.superbanner.callback.OnLoadImageAdapterListener;
import com.bumptech.glide.Glide;
import com.bumptech.glide.request.RequestOptions;

import java.util.List;

public class BannerAdapter extends PagerAdapter {
    private List mData;
    public OnLoadImageAdapterListener mOnLoadImageAdapterListener;
    public OnItemClickAdapterListener mOnItemClickAdapterListener;
    private int mPadding;
    private boolean mIsCloseInfiniteSlide;
    private RequestOptions mOptionsAdapter;
    private int mRadius;
    //队列容器(线性表) 用来存放View，它只允许在表的前端进行删除操作，在表的后端进行插入操作
    // private Queue<View> viewPool = new LinkedList<>();


    /**
     * @param data                       装有图片路径的数据源
     * @param isCloseInfiniteSlide       是否开启手指滑动无限循环的标志 默认开启 true为关闭
     * @param padding                    item居上下左右的边距值
     * @param radius                     item圆角半径
     * @param onLoadImageAdapterListener 图片加载的回调 如果为空 Adapter里直接使用Glide加载
     * @param onItemClickAdapterListener item点击事件回调
     */
    public BannerAdapter(List data, boolean isCloseInfiniteSlide, int padding, int radius, OnLoadImageAdapterListener onLoadImageAdapterListener, OnItemClickAdapterListener onItemClickAdapterListener) {
        this.mData = data;
        this.mPadding = padding;
        this.mRadius = radius;
        this.mIsCloseInfiniteSlide = isCloseInfiniteSlide;
        this.mOnLoadImageAdapterListener = onLoadImageAdapterListener;
        this.mOnItemClickAdapterListener = onItemClickAdapterListener;

    }

    @Override
    public int getCount() {
        return mIsCloseInfiniteSlide ? (mData == null ? 0 : mData.size()) : (mData == null ? 0 : mData.size() * 10000 * 100);

    }

    /**
     * @Description 加载图片
     */
    private void loadImage(Context context, int position, View imageView) {
        if (mOnLoadImageAdapterListener != null) {
            //交于SuperBanner 由SuperBanner在转交给调用层处理
            mOnLoadImageAdapterListener.loadAdapterImage(mData, position, imageView);
            return;
        }
        adapterLoadImage(context, position, imageView);


    }

    /**
     * @Description 如果此方法没有被执行，说明调用层并没有实现加载图片的回调 所以直接进行加载
     */
    private void adapterLoadImage(Context context, int position, View imageView) {
        //如果圆角半径0 说明调用层并没有传入半径值 所以无需再创建对象
        if (mRadius != 0 && mOptionsAdapter == null) {
            mOptionsAdapter = RequestOptions.bitmapTransform(new CenterCropRoundCornerTransform(mRadius));

        }
        //一旦对象被创建 说明调用层需要加载圆角item
        if (mOptionsAdapter != null) {
            Glide.with(context)
                    //判断元素是否为String类型
                    .load(mData.get(position) instanceof String ? (String) mData.get(position) : (int) mData.get(position))
                    .apply(mOptionsAdapter)
                    .into((ImageView) imageView);
        } else {
            Glide.with(context)
                    //判断元素是否为String类型
                    .load(mData.get(position) instanceof String ? (String) mData.get(position) : (int) mData.get(position))
                    .into((ImageView) imageView);
        }
    }

    @NonNull
    @Override
    public Object instantiateItem(@NonNull ViewGroup container, int position) {
        //处理position 通过取余数的方式来限定position的取值范围
        position = position % mData.size();
        ImageView iv = new ImageView(container.getContext());
        iv.setPadding(mPadding, mPadding, mPadding, mPadding);
        iv.setScaleType(ImageView.ScaleType.FIT_XY);
       /* View view = View.inflate(container.getContext(), R.layout.item_ly, null);
        RelativeLayout rl = view.findViewById(R.id.iv_ly);
        //圆角ImageView 由于发现在剪切画布时  左上角的圆角剪切效果不自然 遂使用Glide框架效果处理圆角
        CircularBeadImageView cb_iv = view.findViewById(R.id.iv);
        //设置圆角半径  半径值越小 圆角弧度越小
        cb_iv.setAngle(10);
        //设置item布局内边距
        rl.setPadding(12, 12, 12, 12);*/
        //加载图片
        loadImage(container.getContext(), position, iv);
        onItemClick(iv, position);
        container.addView(iv);
        return iv;
        //如果View队列中有view 那就复用
        /*if (viewPool.size() > 0) {
            //获取并弹出此队列的头个View，如果此队列为空，则返回 null
            view = viewPool.poll();
            viewHolder = (ViewHolder) view.getTag();
        } else {
            viewHolder = new ViewHolder();
            view = View.inflate(container.getContext(), R.layout.item_ly, null);
            viewHolder.itemLayout = view.findViewById(R.id.iv_ly);
            viewHolder.cb_iv = view.findViewById(R.id.iv);
            view.setTag(viewHolder);
        }
        viewHolder.itemLayout.setPadding(8, 8, 8, 8);*/


    }

    /**
     * @Description item的View的点击事件
     * @param cb_iv    点击事件的view
     * @param position item的索引(取余过后的)
     */
    private void onItemClick(View cb_iv, final int position) {
        if (cb_iv != null) {
            cb_iv.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    if (mOnItemClickAdapterListener != null) {
                        mOnItemClickAdapterListener.onItemAdapterClick(position);
                    }
                }
            });
        }
    }

    @Override
    public void destroyItem(@NonNull ViewGroup container, int position, @NonNull Object object) {
        container.removeView((View) object);
        //将当前View加入到View池中
        //viewPool.offer((View) object);
    }

    @Override
    public boolean isViewFromObject(@NonNull View view, @NonNull Object o) {
        return view == o;
    }

    /*
    class ViewHolder {
        RelativeLayout itemLayout;
        CircularBeadImageView cb_iv;

    }*/
}
