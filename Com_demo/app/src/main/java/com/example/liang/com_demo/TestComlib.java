package com.example.liang.com_demo;

/**
 * Created by Administrator on 2016/7/20.
 */
public class TestComlib {

    static {
        System.loadLibrary("Comlib");
        // System.loadLibrary("libstlport_shared");

    }

    public native int Init_COM();
    public native int Send_COM(String data);
    public native int Read_COM(String data);
}
