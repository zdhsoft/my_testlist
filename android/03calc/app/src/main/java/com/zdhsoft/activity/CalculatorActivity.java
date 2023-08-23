package com.zdhsoft.activity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.zdhsoft.calc.R;

public class CalculatorActivity extends AppCompatActivity {
    private final static String TAG = "CalculatorActivity";
    private TextView tv_result;
    private String operator = "";
    private String firstNum = "";
    private String secondNum = "";
    private String result = "";
    private String showText = "";
    @Override
    public void onCreate(Bundle saveInst) {
        super.onCreate(saveInst);
        setContentView(R.layout.activity_calculator);

        init();
    }

    private void init() {
        tv_result = findViewById(R.id.tv_result);
        findViewById(R.id.btn_cancel).setOnClickListener(this::onClick); // “取消”按钮
        findViewById(R.id.btn_divide).setOnClickListener(this::onClick); // “除法”按钮
        findViewById(R.id.btn_multiply).setOnClickListener(this::onClick); // “乘法”按钮
        findViewById(R.id.btn_clear).setOnClickListener(this::onClick); // “清除”按钮
        findViewById(R.id.btn_seven).setOnClickListener(this::onClick); // 数字7
        findViewById(R.id.btn_eight).setOnClickListener(this::onClick); // 数字8
        findViewById(R.id.btn_nine).setOnClickListener(this::onClick); // 数字9
        findViewById(R.id.btn_plus).setOnClickListener(this::onClick); // “加法”按钮
        findViewById(R.id.btn_four).setOnClickListener(this::onClick); // 数字4
        findViewById(R.id.btn_five).setOnClickListener(this::onClick); // 数字5
        findViewById(R.id.btn_six).setOnClickListener(this::onClick); // 数字6
        findViewById(R.id.btn_minus).setOnClickListener(this::onClick); // “减法”按钮
        findViewById(R.id.btn_one).setOnClickListener(this::onClick); // 数字1
        findViewById(R.id.btn_two).setOnClickListener(this::onClick); // 数字2
        findViewById(R.id.btn_three).setOnClickListener(this::onClick); // 数字3
        findViewById(R.id.btn_reciprocal).setOnClickListener(this::onClick); // 求倒数按钮
        findViewById(R.id.btn_zero).setOnClickListener(this::onClick); // 数字0
        findViewById(R.id.btn_dot).setOnClickListener(this::onClick); // “小数点”按钮
        findViewById(R.id.btn_equal).setOnClickListener(this::onClick); // “等号”按钮
        findViewById(R.id.ib_sqrt).setOnClickListener(this::onClick); // “开平方”按钮
    }

    private boolean verify(View v) {
        if (v.getId() == R.id.btn_cancel) { // 点击了取消按钮
            if (operator.equals("") && (firstNum.equals("") || firstNum.equals("0"))) { // 无运算符，则表示逐位取消第一个操作数
                Toast.makeText(this, "没有可取消的数字了", Toast.LENGTH_SHORT).show();
                return false;
            }
            if (!operator.equals("") && secondNum.equals("")) { // 有运算符，则表示逐位取消第二个操作数
                Toast.makeText(this, "没有可取消的数字了", Toast.LENGTH_SHORT).show();
                return false;
            }
        } else if (v.getId() == R.id.btn_equal) { // 点击了等号按钮
            if (operator.equals("")) { // 无运算符
                Toast.makeText(this, "请输入运算符", Toast.LENGTH_SHORT).show();
                return false;
            }
            if (firstNum.equals("") || secondNum.equals("")) { // 无操作数
                Toast.makeText(this, "请输入数字", Toast.LENGTH_SHORT).show();
                return false;
            }
            if (operator.equals("÷") && Double.parseDouble(secondNum) == 0) { // 除数为零
                Toast.makeText(this, "除数不能为零", Toast.LENGTH_SHORT).show();
                return false;
            }
        } else if (v.getId() == R.id.btn_plus || v.getId() == R.id.btn_minus // 点击了加、减、乘、除按钮
                || v.getId() == R.id.btn_multiply || v.getId() == R.id.btn_divide) {
            if (firstNum.equals("")) { // 缺少第一个操作数
                Toast.makeText(this, "请输入数字", Toast.LENGTH_SHORT).show();
                return false;
            }
            if (!operator.equals("")) { // 已有运算符
                Toast.makeText(this, "请输入数字", Toast.LENGTH_SHORT).show();
                return false;
            }
        } else if (v.getId() == R.id.ib_sqrt) { // 点击了开根号按钮
            if (firstNum.equals("")) { // 缺少底数
                Toast.makeText(this, "请输入数字", Toast.LENGTH_SHORT).show();
                return false;
            }
            if (Double.parseDouble(firstNum) < 0) { // 不能对负数开平方
                Toast.makeText(this, "开根号的数值不能小于零", Toast.LENGTH_SHORT).show();
                return false;
            }
        } else if (v.getId() == R.id.btn_reciprocal) { // 点击了求倒数按钮
            if (firstNum.equals("")) { // 缺少底数
                Toast.makeText(this, "请输入数字", Toast.LENGTH_SHORT).show();
                return false;
            }
            if (Double.parseDouble(firstNum) == 0) { // 不能对零求倒数
                Toast.makeText(this, "不能对零求倒数", Toast.LENGTH_SHORT).show();
                return false;
            }
        } else if (v.getId() == R.id.btn_dot) { // 点击了小数点
            if (operator.equals("") && firstNum.contains(".")) { // 无运算符，则检查第一个操作数是否已有小数点
                Toast.makeText(this, "一个数字不能有两个小数点", Toast.LENGTH_SHORT).show();
                return false;
            }
            if (!operator.equals("") && secondNum.contains(".")) { // 有运算符，则检查第二个操作数是否已有小数点
                Toast.makeText(this, "一个数字不能有两个小数点", Toast.LENGTH_SHORT).show();
                return false;
            }
        }
        return true;
    }

    private void clear() {
        refreshOperate("");
        refreshText("");
    }

    private void cancel() {
        if(operator.equals("")) {
            if(firstNum.length() == 1) {
                firstNum = "0";
            } else {
                firstNum = firstNum.substring(0, firstNum.length() - 1);
            }
        } else {
            if(secondNum.length() == 1) {
                secondNum = "";
            } else if(secondNum.length() >1) {
                secondNum = secondNum.substring(0, secondNum.length() - 1);
            }
            refreshText(showText.substring(0, showText.length() - 1));
        }
    }

    private void refreshText(String txt) {
        showText = txt;
        tv_result.setText(txt);
    }

    private void refreshOperate(String newResult) {
        result = newResult;
        firstNum = result;
        secondNum = "";
        operator = "";
    }

    private double calcFour() {
        double r = 0;
        if (operator.equals("＋")) {
            r = Double.parseDouble(firstNum) + Double.parseDouble(secondNum);
        } else if (operator.equals("－")) {
            r = Double.parseDouble(firstNum) - Double.parseDouble(secondNum);
        } else if (operator.equals("×")) {
            r = Double.parseDouble(firstNum) * Double.parseDouble(secondNum);
        } else if (operator.equals("÷")) {
            double v1 = Double.parseDouble(firstNum);
            double v2 = Double.parseDouble(secondNum);
            if (v2 == 0 || v2 == 0.0 || v2 == -0.0 ||v2 == -0) {
            } else {
                r = v1 / v2;
            }
        }
        Log.d(TAG, "计算结果:" + r);
        return r;
    }

    public void onClick(View v) {
        if(!verify(v)) {
            return;
        }
        String inputText;
        final int vid = v.getId();
        if (vid == R.id.ib_sqrt) {
            inputText = "√";
        } else {
            inputText = ((TextView) v).getText().toString();
        }
        Log.d(TAG, "inputText=" + inputText);

        if (vid == R.id.btn_clear) {
            clear();
        } else if(vid == R.id.btn_cancel) {
            cancel();
        } else if(vid == R.id.btn_plus || vid == R.id.btn_minus || vid == R.id.btn_multiply || vid == R.id.btn_divide) {
            operator = inputText;
            refreshText(showText + operator);
        } else if(vid == R.id.btn_equal) {
            double calcResult = calcFour();
            refreshOperate(String.valueOf(calcResult));
            refreshText(showText + "=" + result);
        } else if(vid == R.id.ib_sqrt) {
            double calcResult = Math.sqrt(Double.parseDouble(firstNum)); // 开平方运算
            refreshOperate(String.valueOf(calcResult));
            refreshText(showText + "√=" + result);
        } else if(vid == R.id.btn_reciprocal) {
            double calsResult = 1.0 / Double.parseDouble(firstNum); // 求倒数运算
            refreshOperate(String.valueOf(calsResult));
            refreshText(showText + "/=" + result);
        } else {
            if (result.length() > 0 && operator.equals("")) { // 上次的运算结果已经出来了
                clear();
            }
            if (operator.equals("")) { // 无运算符，则继续拼接第一个操作数
                firstNum = firstNum+inputText;
            } else { // 有运算符，则继续拼接第二个操作数
                secondNum = secondNum + inputText;
            }
            if (showText.equals("0") && !inputText.equals(".")) { // 整数不需要前面的0
                refreshText(inputText);
            } else {
                refreshText(showText + inputText);
            }
        }
    }
}
