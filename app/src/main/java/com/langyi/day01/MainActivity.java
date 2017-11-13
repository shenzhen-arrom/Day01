package com.langyi.day01;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.io.UnsupportedEncodingException;
import java.util.Arrays;


public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    EditText et_account;
    TextView tv_account;
    Button btn_save,btn_get_accont;

    private void initView(){
        et_account=findViewById(R.id.et_account);
        tv_account=findViewById(R.id.tv_account);
        btn_save= findViewById(R.id.btn_save);
        btn_get_accont=findViewById(R.id.btn_get_accont);
        btn_save.setOnClickListener(this);
        btn_get_accont.setOnClickListener(this);
    }

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();

    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native void setAccount(byte[] src);
    public native String getAccount();


    @Override
    public void onClick(View view) {
        switch (view.getId()){
            case R.id.btn_save:
                String name=et_account.getText().toString().trim();
                byte[] src=null;
                try {
                    src=name.getBytes("utf-8");
                } catch (UnsupportedEncodingException e) {
                    e.printStackTrace();
                }
                System.out.println("---->>>>xujie"+Arrays.toString(src));
                setAccount(src);
                break;
            case R.id.btn_get_accont:
                tv_account.setText("账户是:"+getAccount());
                break;
        }
    }
}
