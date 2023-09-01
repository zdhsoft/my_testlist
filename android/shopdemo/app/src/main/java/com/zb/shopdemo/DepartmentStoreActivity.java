package com.zb.shopdemo;

import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager.widget.ViewPager;

import android.os.Bundle;
import android.widget.RadioButton;
import android.widget.RadioGroup;

import com.zb.shopdemo.adapter.DepartmentPagerAdapter;
import com.zb.shopdemo.util.Utils;

public class DepartmentStoreActivity extends AppCompatActivity {
    private ViewPager vp_content; // 声明一个翻页视图对象
    // 一个导航栏
    private RadioGroup rg_tabbar; // 声明一个单选组对象
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_department_store);
        vp_content = findViewById(R.id.vp_content);
        // 构建一个翻页适配器
        DepartmentPagerAdapter adapter = new DepartmentPagerAdapter(getSupportFragmentManager());
        vp_content.setAdapter(adapter); // 设置翻页视图的适配器
        // 给翻页视图添加页面变更监听器
        vp_content.addOnPageChangeListener(new ViewPager.SimpleOnPageChangeListener() {
            @Override
            public void onPageSelected(int position) {
                // 选中指定位置的单选按钮
                rg_tabbar.check(rg_tabbar.getChildAt(position).getId());
            }
        });
        rg_tabbar = findViewById(R.id.rg_tabbar);
        // 设置单选组的选中监听器
        rg_tabbar.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                int itemPos = Utils.getPosById(group, checkedId);
                if (itemPos >= 0) {
                    vp_content.setCurrentItem(itemPos);
                }
            }
        });
    }
}