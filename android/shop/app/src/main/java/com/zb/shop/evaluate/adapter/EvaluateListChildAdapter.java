package com.zb.shop.evaluate.adapter;

import com.wanyue.common.adapter.base.BaseReclyViewHolder;
import com.zb.shop.R;
import com.zb.shop.view.widet.ViewGroupLayoutBaseAdapter;
import java.util.List;

public class EvaluateListChildAdapter extends ViewGroupLayoutBaseAdapter<String> {
    public EvaluateListChildAdapter(List<String> list) {
        super(list);
    }
    @Override
    public void convert(BaseReclyViewHolder helper, String item) {
        helper.setImageUrl(item,R.id.img);
    }
    @Override
    protected int getLayoutId(String s) {
        return R.layout.item_recly_evaluate_child;
    }
}
