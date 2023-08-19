package com.zdhsoft.calc;

import android.graphics.Color;
import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class TextColorActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_text_color);

        TextView tv_code_system = findViewById(R.id.tv_code_system);
        tv_code_system.setTextColor(Color.GREEN);

        TextView tv_code_six = findViewById(R.id.tv_code_six);
        // 将tv_code_six的文字颜色设置为透明的绿色，透明就是看不到
        tv_code_six.setTextColor(0x6600ff00);

        TextView tv_code_eight = findViewById(R.id.tv_code_eight);
        tv_code_eight.setTextColor(0xff00ff00);

        TextView tv_code_bg = findViewById(R.id.tv_code_background);
        tv_code_bg.setBackgroundColor(Color.GREEN);      // 在代码中定义的色值
        tv_code_bg.setBackgroundResource(R.color.green); // 颜色来自资源文件
    }

}