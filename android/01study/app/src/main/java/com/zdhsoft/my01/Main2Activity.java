package com.zdhsoft.my01;

import android.os.Bundle;
import android.text.format.DateUtils;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class Main2Activity extends AppCompatActivity {
    private int m = 0;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);
    }

    public void doClick(View view) {
        Log.i("prompt", "按钮按了一下");
        TextView t = findViewById(R.id.textView3);
        m++;
        String s = String.format("%d 您按了一下!", m);
        t.setText(s);
    }
}
