package com.zdhsoft.activity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.zdhsoft.calc.R;
import com.zdhsoft.calc.util.DateUtil;

public class ButtonStyleActivity extends AppCompatActivity {
    private TextView tv_result;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_button_style);

        tv_result = findViewById(R.id.tv_result1);
    }

    public void doClick(View v) {
        String desc =  String.format("%s 您点击了按钮：%s",
                DateUtil.getNowTime(), ((Button) v).getText());
        tv_result.setText(desc);
    }
}
