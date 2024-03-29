package com.zdhsoft.calc;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.zdhsoft.activity.ButtonClickActivity;
import com.zdhsoft.activity.ButtonEnableActivity;
import com.zdhsoft.activity.ButtonLongclickActivity;
import com.zdhsoft.activity.ButtonStyleActivity;
import com.zdhsoft.activity.CalculatorActivity;
import com.zdhsoft.activity.ImageButtonActivity;
import com.zdhsoft.activity.ImageScaleActivity;
import com.zdhsoft.activity.ImageTextActivity;
import com.zdhsoft.activity.RelativeLayoutActivity;
import com.zdhsoft.activity.ScrollViewActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.btn_text_view).setOnClickListener(this::onClick);
        findViewById(R.id.btn_text_size).setOnClickListener(this::onClick);
        findViewById(R.id.btn_text_color).setOnClickListener(this::onClick);
        findViewById(R.id.btn_view_border).setOnClickListener(this::onClick);
        findViewById(R.id.btn_view_margin).setOnClickListener(this::onClick);
        findViewById(R.id.btn_view_gravity).setOnClickListener(this::onClick);
        findViewById(R.id.btn_linear_layout).setOnClickListener(this::onClick);
        findViewById(R.id.btn_linear_weight).setOnClickListener(this::onClick);
        findViewById(R.id.btn_grid_layout).setOnClickListener(this::onClick);
        findViewById(R.id.btn_relative_layout).setOnClickListener(this::onClick);
        findViewById(R.id.btn_calculator).setOnClickListener(this::onClick);

        findViewById(R.id.btn_scroll_view).setOnClickListener(this::onClick);
        findViewById(R.id.btn_button_style).setOnClickListener(this::onClick);
        findViewById(R.id.btn_button_click).setOnClickListener(this::onClick);
        findViewById(R.id.btn_button_longclick).setOnClickListener(this::onClick);
        findViewById(R.id.btn_button_enable).setOnClickListener(this::onClick);
        findViewById(R.id.btn_image_scale).setOnClickListener(this::onClick);
        findViewById(R.id.btn_image_button).setOnClickListener(this::onClick);
        findViewById(R.id.btn_image_text).setOnClickListener(this::onClick);

        // do finish!!! yes
    }

    // @Override
    private void setView(Class<?> cls) {
        Intent intent = new Intent(this, cls);
        startActivity(intent);
    }
    public void onClick(View v) {
        final int id = v.getId();
        if (id == R.id.btn_text_view) {
            Log.d("prompt", "-----> onClick");
            setView(TextViewActivity.class);
        } else if(id == R.id.btn_text_size) {
            setView(TextSizeActivity.class);
        } else if(id == R.id.btn_text_color) {
            setView(TextColorActivity.class);
        } else if(id == R.id.btn_view_border) {
            setView(ViewBorderActivity.class);
        } else if(id == R.id.btn_view_gravity) {
            setView(ViewGravityActivity.class);
        } else if(id == R.id.btn_view_margin) {
            setView(ViewMarginActivity.class);
        } else if(id == R.id.btn_linear_weight) {
            setView(LinearWeightActivity.class);
        }else if (id == R.id.btn_linear_layout) {
            setView(LinearLayoutActivity.class);
        } else if(id == R.id.btn_grid_layout) {
            setView(GridLayoutActivity.class);
        } else if(id == R.id.btn_calculator) {
            setView(CalculatorActivity.class);
        } else if(id == R.id.btn_relative_layout) {
            setView(RelativeLayoutActivity.class);
        } else if(id == R.id.btn_scroll_view) {
            setView(ScrollViewActivity.class);
        } else if(id == R.id.btn_button_style) {
            setView(ButtonStyleActivity.class);
        } else if(id == R.id.btn_button_click) {
            setView(ButtonClickActivity.class);
        } else if(id == R.id.btn_button_longclick) {
            setView(ButtonLongclickActivity.class);
        } else if(id == R.id.btn_button_enable) {
            setView(ButtonEnableActivity.class);
        } else if(id == R.id.btn_image_button) {
            setView(ImageButtonActivity.class);
        } else if(id == R.id.btn_image_scale) {
            setView(ImageScaleActivity.class);
        } else if(id == R.id.btn_image_text) {
            setView(ImageTextActivity.class);
        } else {
            Log.d("prompt", "没有找到对应的窗口");
        }
    }
}