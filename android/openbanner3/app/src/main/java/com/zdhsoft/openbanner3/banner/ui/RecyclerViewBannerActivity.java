package com.zdhsoft.openbanner3.banner.ui;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.zdhsoft.openbanner3.R;
import com.zdhsoft.openbanner3.banner.adapter.MyRecyclerViewAdapter;

public class RecyclerViewBannerActivity extends AppCompatActivity {
    // @BindView(R.id.net_rv)
    RecyclerView recyclerView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recyclerview_banner);

        recyclerView = findViewById(R.id.net_rv_bbb);
        // ButterKnife.bind(this);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        recyclerView.setAdapter(new MyRecyclerViewAdapter(this));
    }

}
