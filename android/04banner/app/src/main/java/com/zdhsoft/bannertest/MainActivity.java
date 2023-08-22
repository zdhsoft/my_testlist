package com.zdhsoft.bannertest;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager.widget.PagerAdapter;
import androidx.viewpager.widget.ViewPager;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    private View m_view1, m_view2, m_view3;
    private ViewPager m_viewPager;

    private List<View> m_list;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        m_viewPager = findViewById(R.id.viewpager);
        LayoutInflater inflater=getLayoutInflater();
        m_view1 = inflater.inflate(R.layout.layout1, null);
        m_view2 = inflater.inflate(R.layout.layout2, null);
        m_view3 = inflater.inflate(R.layout.layout3, null);

        m_list = new ArrayList<View>();
        m_list.add(m_view1);
        m_list.add(m_view2);
        m_list.add(m_view3);

        PagerAdapter pa = new PagerAdapter() {
            @Override
            public int getCount() {
                return m_list.size();
            }

            @Override
            public boolean isViewFromObject(@NonNull View view, @NonNull Object object) {
                return view == object;
            }

            @Override
            public void destroyItem(ViewGroup container, int position,
                                    Object object) {
                // TODO Auto-generated method stub
                container.removeView(m_list.get(position));
            }

            @Override
            public Object instantiateItem(ViewGroup container, int position) {
                // TODO Auto-generated method stub
                container.addView(m_list.get(position));


                return m_list.get(position);

            }
        };

        m_viewPager.setAdapter(pa);
    }
}