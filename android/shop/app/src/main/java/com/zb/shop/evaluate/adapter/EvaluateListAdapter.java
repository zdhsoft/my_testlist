package com.zb.shop.evaluate.adapter;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.text.TextUtils;
import android.view.View;
import android.widget.TextView;
import androidx.annotation.NonNull;

import com.wanyue.common.adapter.base.BaseReclyViewHolder;
import com.wanyue.common.adapter.base.BaseRecyclerAdapter;
import com.wanyue.common.utils.BitmapUtil;
import com.wanyue.common.utils.DpUtil;
import com.wanyue.common.utils.ViewUtil;
import com.zb.shop.R;
import com.zb.shop.evaluate.bean.EvaluateBean;
import com.zb.shop.view.widet.RatingStar;
import com.zb.shop.view.widet.ViewGroupLayoutBaseAdapter;
import com.zb.shop.view.widet.linear.ListFlexboxLayout;
import com.zb.shop.view.widet.linear.ListPool;
import java.util.List;


public class EvaluateListAdapter  extends BaseRecyclerAdapter<EvaluateBean, BaseReclyViewHolder>   {
    private ListPool mListPool;
    private Bitmap starNormal;
    private Bitmap starFocus;

    private ViewGroupLayoutBaseAdapter.OnItemClickListener<String> mStringOnItemClickListener;
    public EvaluateListAdapter(List<EvaluateBean> data, Resources resources) {
        super(data);
        int size = DpUtil.dp2px(9);
        starNormal = BitmapUtil.thumbImageWithMatrix(resources, R.drawable.icon_evaluate_default, size, size);
        starFocus = BitmapUtil.thumbImageWithMatrix(resources, R.drawable.icon_evaluate_select, size, size);
    }


    @Override
    public int getLayoutId() {
        return R.layout.item_recly_evaluate_list;
    }
    @Override
    protected void convert(@NonNull BaseReclyViewHolder helper, EvaluateBean item) {
        helper.setImageUrl(item.getAvatar(),R.id.img_avator);
        helper.setText(R.id.tv_user_name,item.getNickname())
       .setText(R.id.tv_time,item.getTimeAndSuk())
       .setText(R.id.tv_content,item.getComment());
        List<String>list=item.getPictureList();

        String replyContent=item.getMerchant_reply_content();
        View imgArrowTop=helper.getView(R.id.img_arrow_top);
        TextView tvReply=helper.getView(R.id.tv_reply);
        RatingStar star=helper.getView(R.id.star);
        star.setPosition(item.getStar()-1);
        star.setNormalImg(starNormal);
        star.setFocusImg(starFocus);

           ListFlexboxLayout listView=helper.getView(R.id.list_item);
           if(mListPool==null){
              mListPool=new ListPool();
            }
            listView.setListPool(mListPool);
            if(listView.getAdapter()==null){

              EvaluateListChildAdapter adapter=new EvaluateListChildAdapter(list);
              adapter.setOnItemClickListener(mStringOnItemClickListener);
              listView.setAdapter(adapter);
            }else{
              EvaluateListChildAdapter adapter= (EvaluateListChildAdapter) listView.getAdapter();
              adapter.setData(list);
            }

        if(TextUtils.isEmpty(replyContent)){
           ViewUtil.setVisibility(imgArrowTop,View.GONE);
           ViewUtil.setVisibility(tvReply,View.GONE);
        }else{
            ViewUtil.setVisibility(imgArrowTop,View.VISIBLE);
            ViewUtil.setVisibility(tvReply,View.VISIBLE);
            tvReply.setText(item.getReplyContent2());
        }
    }

    public void setStringOnItemClickListener(ViewGroupLayoutBaseAdapter.OnItemClickListener<String> stringOnItemClickListener) {
        mStringOnItemClickListener = stringOnItemClickListener;
    }
}
