package com.zb.shopdemo.util;
import android.content.Context;
import android.graphics.Rect;
import android.os.Build;
import android.util.DisplayMetrics;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;

public class Utils {
    // 根据手机的分辨率从 dp 的单位 转成为 px(像素)
    public static int dip2px(Context context, float dpValue) {
        // 获取当前手机的像素密度（1个dp对应几个px）
        float scale = context.getResources().getDisplayMetrics().density;
        return (int) (dpValue * scale + 0.5f); // 四舍五入取整
    }

    // 根据手机的分辨率从 px(像素) 的单位 转成为 dp
    public static int px2dip(Context context, float pxValue) {
        // 获取当前手机的像素密度（1个dp对应几个px）
        float scale = context.getResources().getDisplayMetrics().density;
        return (int) (pxValue / scale + 0.5f); // 四舍五入取整
    }

    // 获得屏幕的宽度
    public static int getScreenWidth(Context ctx) {
        int screenWidth;
        // 从系统服务中获取窗口管理器
        WindowManager wm = (WindowManager) ctx.getSystemService(Context.WINDOW_SERVICE);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            // 获取当前屏幕的四周边界
            Rect rect = wm.getCurrentWindowMetrics().getBounds();
            screenWidth = rect.width();
        } else {
            DisplayMetrics dm = new DisplayMetrics();
            // 从默认显示器中获取显示参数保存到dm对象中
            wm.getDefaultDisplay().getMetrics(dm);
            screenWidth = dm.widthPixels;
        }
        return screenWidth; // 返回屏幕的宽度数值
    }

    /**
     * 取一个指定id的view对象
     * @param paramG 指定的ViewGroup
     * @param paramId 指定的id
     * @return 返回找到的数据
     *  - null 表示没有找到的数据
     *  - not null 表示找到的对象
     */
    public static View getButtonById(ViewGroup paramG, int paramId) {
        int cnt = paramG.getChildCount();
        for(int i = 0; i < cnt; ++i) {
            View item = paramG.getChildAt(i);
            if(item == null) {
                continue;
            }
            if (item.getId() == paramId) {
                return item;
            }
        }
        return null;
    }

    /**
     * 取一个指定id的下标
     * @param paramG 指定的ViewGroup
     * @param paramId 指定的id
     * @return
     * - -1 表示没有找到
     * - >= 0 表示对应的下标s
     */
    public static int getPosById(ViewGroup paramG, int paramId) {
        int cnt = paramG.getChildCount();
        for(int i = 0; i < cnt; ++i) {
            View item = paramG.getChildAt(i);
            if (item == null) {
                continue;
            }
            if (item.getId() == paramId) {
                return i;
            }
        };
        return -1;
    }

    // 获得屏幕的高度
    public static int getScreenHeight(Context ctx) {
        int screenHeight;
        // 从系统服务中获取窗口管理器
        WindowManager wm = (WindowManager) ctx.getSystemService(Context.WINDOW_SERVICE);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            // 获取当前屏幕的四周边界
            Rect rect = wm.getCurrentWindowMetrics().getBounds();
            screenHeight = rect.height();
        } else {
            DisplayMetrics dm = new DisplayMetrics();
            // 从默认显示器中获取显示参数保存到dm对象中
            wm.getDefaultDisplay().getMetrics(dm);
            screenHeight = dm.heightPixels;
        }
        return screenHeight; // 返回屏幕的高度数值
    }

}

