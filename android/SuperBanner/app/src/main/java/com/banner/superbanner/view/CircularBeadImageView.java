package com.banner.superbanner.view;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.PaintFlagsDrawFilter;
import android.graphics.Path;
import android.os.Build;
import android.support.v7.widget.AppCompatImageView;
import android.util.AttributeSet;
import android.view.View;

/**
 * @Description 通过绘出一个圆角矩形的路径，然后用ClipPath裁剪，
 * 画布的方式对ImageView的边角进行剪裁实现圆角
 */
public class CircularBeadImageView extends AppCompatImageView {
    float width, height;
    //此值代表圆角的半径
    int mAngle;

    public CircularBeadImageView(Context context) {
        this(context, null);
    }

    public CircularBeadImageView(Context context, AttributeSet attrs) {
        this(context, attrs, -1);
    }

    public CircularBeadImageView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);

        //Android4.0及之前的手机中，因为硬件加速等原因，在使用clipPath时很有可能会发生UnsupportedOperationException异常
        if (Build.VERSION.SDK_INT < 18) {
            setLayerType(View.LAYER_TYPE_SOFTWARE, null);
        }
    }

   public void setAngle(int angle) {
        this.mAngle = angle;
    }

    @Override
    protected void onLayout(boolean changed, int left, int top, int right, int bottom) {
        super.onLayout(changed, left, top, right, bottom);

        width = getWidth();
        height = getHeight();
    }


    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);

    }

    @Override
    protected void onDraw(Canvas canvas) {
        if (width > mAngle && height > mAngle) {
            Path path = new Path();
            path.moveTo(mAngle, 0);
            path.lineTo(width - mAngle, 0);
            path.quadTo(width, 0, width, mAngle);
            path.lineTo(width, height - mAngle);
            path.quadTo(width, height, width - mAngle, height);
            path.lineTo(mAngle, height);
            path.quadTo(0, height, 0, height - mAngle);
            path.lineTo(0, mAngle);
            path.quadTo(0, 0, 40, 0);
            canvas.clipPath(path);
        }

        super.onDraw(canvas);


    }

}
