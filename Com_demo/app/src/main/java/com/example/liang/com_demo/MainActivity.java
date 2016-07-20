package com.example.liang.com_demo;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity implements OnClickListener {

    private Button mybutton1;
    private Button mybutton2;

    private Button mybutton3;

    private Com mecom=null;

    private TextView mytextview;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mybutton1=(Button)findViewById(R.id.Init_com);
        mybutton1.setOnClickListener(this);

        mybutton2=(Button)findViewById(R.id.Read_com);
        mybutton2.setOnClickListener(this);

        mybutton3=(Button)findViewById(R.id.Send_com);
        mybutton3.setOnClickListener(this);

        mytextview=(TextView)findViewById(R.id.textView);

        mecom=new Com();
    }
    public void onClick(View v){
        switch (v.getId()){
            case R.id.Init_com:
                mytextview.setText("Init_com");
                mecom.Init_COM();
                break;
            case R.id.Read_com:
                mecom.Read_COM("test");
                mytextview.setText("Read_com");
                break;
            case R.id.Send_com:
                mecom.Send_COM("test");
                mytextview.setText("Send_com");
                break;
        }
    }
}
