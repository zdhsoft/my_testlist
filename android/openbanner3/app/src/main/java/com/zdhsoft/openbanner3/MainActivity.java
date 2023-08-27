package com.zdhsoft.openbanner3;

import androidx.appcompat.app.AppCompatActivity;
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.bumptech.glide.Glide;
import com.bumptech.glide.load.resource.bitmap.RoundedCorners;
import com.bumptech.glide.request.RequestOptions;
import com.google.android.material.snackbar.Snackbar;
import com.youth.banner.Banner;
import com.youth.banner.adapter.BannerImageAdapter;
import com.youth.banner.config.BannerConfig;
import com.youth.banner.config.IndicatorConfig;
import com.youth.banner.holder.BannerImageHolder;
import com.youth.banner.indicator.CircleIndicator;
import com.youth.banner.indicator.DrawableIndicator;
import com.youth.banner.indicator.RoundLinesIndicator;
import com.youth.banner.util.BannerUtils;
import com.youth.banner.util.LogUtils;
import com.zdhsoft.openbanner3.banner.adapter.ImageAdapter;
import com.zdhsoft.openbanner3.banner.adapter.ImageTitleAdapter;
import com.zdhsoft.openbanner3.banner.adapter.ImageTitleNumAdapter;
import com.zdhsoft.openbanner3.banner.adapter.MultipleTypesAdapter;
import com.zdhsoft.openbanner3.banner.bean.DataBean;
import com.zdhsoft.openbanner3.banner.ui.ConstraintLayoutBannerActivity;
import com.zdhsoft.openbanner3.banner.ui.GalleryActivity;
import com.zdhsoft.openbanner3.banner.ui.RecyclerViewBannerActivity;
import com.zdhsoft.openbanner3.banner.ui.TVActivity;
import com.zdhsoft.openbanner3.banner.ui.TouTiaoActivity;
import com.zdhsoft.openbanner3.banner.ui.VideoActivity;
import com.zdhsoft.openbanner3.banner.ui.Vp2FragmentRecyclerviewActivity;

public class MainActivity extends AppCompatActivity {
    // @BindView(R.id.banner)
    Banner banner;
    // @BindView(R.id.indicator)
    RoundLinesIndicator indicator;
    // @BindView(R.id.swipeRefresh)
    SwipeRefreshLayout refresh;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        banner = findViewById(R.id.banner);
        indicator = findViewById(R.id.indicator);
        refresh = findViewById(R.id.swipeRefresh);

        bindEvent();

        //自定义的图片适配器，也可以使用默认的BannerImageAdapter
        ImageAdapter adapter = new ImageAdapter(DataBean.getTestData2());

        banner.setAdapter(adapter)
//              .setCurrentItem(0,false)
                .addBannerLifecycleObserver(this)//添加生命周期观察者
                .setIndicator(new CircleIndicator(this))//设置指示器
                .setOnBannerListener((data, position) -> {
                    Snackbar.make(banner, ((DataBean) data).title, Snackbar.LENGTH_SHORT).show();
                    LogUtils.d("position：" + position);
                });

        //添加item之间切换时的间距(如果使用了画廊效果就不要添加间距了，因为内部已经添加过了)
//        banner.addPageTransformer(new MarginPageTransformer( BannerUtils.dp2px(10)));

        //和下拉刷新配套使用
        refresh.setOnRefreshListener(() -> {
            //模拟网络请求需要3秒，请求完成，设置setRefreshing 为false
            new Handler().postDelayed(new Runnable() {
                @Override
                public void run() {
                    refresh.setRefreshing(false);
                    //给banner重新设置数据
                    banner.setDatas(DataBean.getTestData());
                    //对setdatas不满意？你可以自己在adapter控制数据，可以参考setDatas()的实现修改
//                    adapter.updateData(DataBean.getTestData2());
                }
            }, 3000);
        });

//        banner.addBannerLifecycleObserver(this);
//        useBanner();
    }

    private void bindEvent() {
        findViewById(R.id.style_image).setOnClickListener(this::click);
        findViewById(R.id.style_image_title).setOnClickListener(this::click);
        findViewById(R.id.style_image_title_num).setOnClickListener(this::click);
        findViewById(R.id.style_multiple).setOnClickListener(this::click);
        findViewById(R.id.style_net_image).setOnClickListener(this::click);
        findViewById(R.id.change_indicator).setOnClickListener(this::click);
        findViewById(R.id.rv_banner).setOnClickListener(this::click);
        findViewById(R.id.cl_banner).setOnClickListener(this::click);
        findViewById(R.id.vp_banner).setOnClickListener(this::click);
        findViewById(R.id.banner_video).setOnClickListener(this::click);
        findViewById(R.id.banner_tv).setOnClickListener(this::click);
        findViewById(R.id.gallery).setOnClickListener(this::click);
        findViewById(R.id.topLine).setOnClickListener(this::click);
    }

    @Override
    protected void onStart() {
        super.onStart();
        //开始轮播
        banner.start();
    }

    @Override
    protected void onStop() {
        super.onStop();
        //停止轮播
        banner.stop();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        //销毁
        banner.destroy();
    }
    public void useBanner() {
//        //--------------------------简单使用-------------------------------
//        banner.addBannerLifecycleObserver(this)//添加生命周期观察者
//                .setAdapter(new BannerExampleAdapter(DataBean.getTestData()))
//                .setIndicator(new CircleIndicator(this));

        //—————————————————————————如果你想偷懒，而又只是图片轮播————————————————————————
        banner.setAdapter(new BannerImageAdapter<DataBean>(DataBean.getTestData()) {
                    @Override
                    public void onBindView(BannerImageHolder holder, DataBean data, int position, int size) {
                        //图片加载自己实现
                        Log.d(">>>>", "imageURL:" + data.imageUrl + ", dataType:" + data.viewType + ", imageRes:" + data.imageRes + ", title:" + data.title );
                        Glide.with(holder.itemView)
                                .load(data.imageUrl)
                                .apply(RequestOptions.bitmapTransform(new RoundedCorners(30)))
                                .into(holder.imageView);
                    }
                })
                .addBannerLifecycleObserver(this)//添加生命周期观察者
                .setIndicator(new CircleIndicator(this));
        //更多使用方法仔细阅读文档，或者查看demo
    }

    public void click(View view) {
        indicator.setVisibility(View.GONE);
        final int id = view.getId();
        Button b = (Button)view;
        String t = "";
        if (b != null) {
            t = b.getText().toString();
        }
        Log.i("------", "id=" + id + ": 调用了:" + t);
        if(id == R.id.style_image) {
            OnClickStyleImage();
        }else if(id == R.id.style_image_title) {
            OnClickStyleImageTitle();
        } else if(id == R.id.style_image_title_num ) {
            OnClickStyleImageTitleNum();
        } else if(id == R.id.style_multiple ) {
            OnClickStyleMultiple();
        } else if(id == R.id.style_net_image) {
            OnClickStyleNetImage();
        } else if(id == R.id.change_indicator) {
            OnClickChangeIndicator();
        } else if(id == R.id.gallery) {
            startActivity(new Intent(this, GalleryActivity.class));
        } else if(id == R.id.rv_banner) {
            startActivity(new Intent(this, RecyclerViewBannerActivity.class));
        } else if(id== R.id.cl_banner) {
            startActivity(new Intent(this, ConstraintLayoutBannerActivity.class));
        } else if(id == R.id.vp_banner) {
            startActivity(new Intent(this, Vp2FragmentRecyclerviewActivity.class));
        } else if(id == R.id.banner_video) {
            startActivity(new Intent(this, VideoActivity.class));
        } else if(id == R.id.banner_tv) {
            startActivity(new Intent(this, TVActivity.class));
        } else if(id == R.id.topLine) {
                setView(TouTiaoActivity.class);
        }
    }
    private void setView(Class<?> cls) {
        Intent intent = new Intent(this, cls);
        startActivity(intent);
    }
    private void OnClickChangeIndicator() {
        indicator.setVisibility(View.VISIBLE);
        //在布局文件中使用指示器，这样更灵活
        banner.setIndicator(indicator, false);
        banner.setIndicatorSelectedWidth(BannerUtils.dp2px(15));
    }

    private void OnClickStyleNetImage() {
        refresh.setEnabled(false);
        //方法一：使用自定义图片适配器
//                banner.setAdapter(new ImageNetAdapter(DataBean.getTestData3()));

        //方法二：使用自带的图片适配器
        banner.setAdapter(new BannerImageAdapter<DataBean>(DataBean.getTestData3()) {
            @Override
            public void onBindView(BannerImageHolder holder, DataBean data, int position, int size) {
                //图片加载自己实现
                Glide.with(holder.itemView)
                        .load(data.imageUrl)
                        .thumbnail(Glide.with(holder.itemView).load(R.drawable.loading))
                        .apply(RequestOptions.bitmapTransform(new RoundedCorners(30)))
                        .into(holder.imageView);
            }
        });
        banner.setIndicator(new RoundLinesIndicator(this));
        banner.setIndicatorSelectedWidth(BannerUtils.dp2px(15));
    }

    private void OnClickStyleMultiple() {
        refresh.setEnabled(true);
        banner.setIndicator(new DrawableIndicator(this,R.drawable.indicator_normal,R.drawable.indicator_selected));
        banner.setAdapter(new MultipleTypesAdapter(this, DataBean.getTestData()));
    }

    private void OnClickStyleImageTitleNum() {
        refresh.setEnabled(true);
        //这里是将数字指示器和title都放在adapter中的，如果不想这样你也可以直接设置自定义的数字指示器
        banner.setAdapter(new ImageTitleNumAdapter(DataBean.getTestData()));
        banner.removeIndicator();
    }

    private void OnClickStyleImageTitle() {
        refresh.setEnabled(true);
        banner.setAdapter(new ImageTitleAdapter(DataBean.getTestData()));
        banner.setIndicator(new CircleIndicator(this));
        banner.setIndicatorGravity(IndicatorConfig.Direction.RIGHT);
        banner.setIndicatorMargins(new IndicatorConfig.Margins(0, 0,
                BannerConfig.INDICATOR_MARGIN, BannerUtils.dp2px(12)));
    }

    private void OnClickStyleImage() {
        refresh.setEnabled(true);
        banner.setAdapter(new ImageAdapter(DataBean.getTestData()));
        banner.setIndicator(new CircleIndicator(this));
        banner.setIndicatorGravity(IndicatorConfig.Direction.CENTER);
    }
}