package com.zb.shop.view.view;

import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import com.wanyue.common.proxy.RxViewProxy;
import com.wanyue.common.utils.ListUtil;
import com.zb.shop.R;
import com.zb.shop.bean.GoodsParseBean;
import com.zb.shop.evaluate.activity.EvaluateListActivity;
import com.zb.shop.evaluate.adapter.EvaluateLinearListAdapter;
import com.zb.shop.evaluate.bean.EvaluateBean;
import com.zb.shop.evaluate.bean.EvaluateBean2;
import com.zb.shop.view.dialog.GalleryDialogFragment;
import com.zb.shop.view.widet.LinearLayoutForListView;
import com.zb.shop.view.widet.ViewGroupLayoutBaseAdapter;

import java.util.Arrays;
import java.util.List;

public class GoodsEvaluateViewProxy extends BaseGoodItemViewProxy implements View.OnClickListener, ViewGroupLayoutBaseAdapter.OnItemClickListener<String> {
    private ViewGroup mBtnEvaluate;
    private TextView mTvEvaluateNum;
    private TextView mTvFeedbackRate;
    private TextView mTvEvaluateChangce;
    private String mGoodsId;
    private LinearLayoutForListView mListView;
    private EvaluateLinearListAdapter mEvaluateLinearListAdapter;

    @Override
    protected void initView(ViewGroup contentView) {
        super.initView(contentView);
        mBtnEvaluate =  findViewById(R.id.btn_evaluate);
        mTvEvaluateNum =  findViewById(R.id.tv_evaluate_num);
        mTvFeedbackRate = findViewById(R.id.tv_feedback_rate);
        mTvEvaluateChangce =  findViewById(R.id.tv_evaluate_changce);
        mBtnEvaluate.setOnClickListener(this);
        mListView = (LinearLayoutForListView) findViewById(R.id.listView);
        mEvaluateLinearListAdapter=new EvaluateLinearListAdapter(null,getResources());
        mListView.setAdapter(mEvaluateLinearListAdapter);
        mEvaluateLinearListAdapter.setStringOnItemClickListener(this);
    }

    @Override
    public int getLayoutId() {
        return R.layout.view_goods_evaluate;
    }

    public void setData(GoodsParseBean goodsParseBean){
        if(goodsParseBean==null){
            return;
        }
        mGoodsId=goodsParseBean.getGoodsInfo().getId();
        mTvEvaluateNum.setText(getString(R.string.evaluate_tip,goodsParseBean.getReplyCount()));
        mTvFeedbackRate.setText(goodsParseBean.getReplyChance()+"%");
        EvaluateBean2 evaluateBean=goodsParseBean.getReply();
        if(evaluateBean!=null){
           mEvaluateLinearListAdapter.setData(ListUtil.asList(evaluateBean));
        }
    }

    @Override
    public void onClick(View v) {
        EvaluateListActivity.forward(getActivity(),mGoodsId);
    }

    private void showGally(List<String> urlList, int position) {
        GalleryDialogFragment galleryDialogFragment = new GalleryDialogFragment();
        galleryDialogFragment.setGalleryViewProxy(urlList, position, getViewProxyMannger());
        galleryDialogFragment.show(getActivity().getSupportFragmentManager());

    }

    @Override
    public void onItemClicked(ViewGroupLayoutBaseAdapter<String> adapter, View v, String item, int position) {
        List<String>urlList=adapter.getData();
        showGally(urlList,position);
    }
}
