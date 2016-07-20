//
// Created by liang on 2016/7/20.
//
#include "Logger.h"
#include <stdio.h>

#include"com_example_liang_com_demo_TestComlib.h"


JNIEXPORT jint JNICALL Java_com_example_liang_com_1demo_TestComlib_Init_1COM
  (JNIEnv *env, jobject obj){

    LOGD("Com Init %s \n", "");

    printf("Com send  \n");
/*
    LOGD("main\n");
    Uart testCom;
    testCom.start();
    testCom.openDoor();*/
}


JNIEXPORT jint JNICALL Java_com_example_liang_com_1demo_TestComlib_Send_1COM
  (JNIEnv *env, jobject obj, jstring data){
    printf("Com send  \n");

}


JNIEXPORT jint JNICALL Java_com_example_liang_com_1demo_TestComlib_Read_1COM
  (JNIEnv *env, jobject obj, jstring data){
    LOGD("Com read %s \n", "");
}