package com.zb.shop.view.view;

import com.wanyue.common.proxy.RxViewProxy;
import com.zb.shop.bean.StoreGoodsBean;

public abstract class BaseGoodsDetailBottomViewProxy extends RxViewProxy {
    protected StoreGoodsBean mStoreGoodsBean;
    public void setStoreGoodsBean(StoreGoodsBean storeGoodsBean) {
        mStoreGoodsBean = storeGoodsBean;
    }
}
