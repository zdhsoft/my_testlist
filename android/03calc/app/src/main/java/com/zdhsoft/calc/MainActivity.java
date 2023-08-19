package com.zdhsoft.calc;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.btn_text_view).setOnClickListener(this::onClick);
        findViewById(R.id.btn_text_size).setOnClickListener(this::onClick);
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
        }
    }
}