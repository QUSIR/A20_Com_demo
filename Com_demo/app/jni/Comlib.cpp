//
// Created by liang on 2016/7/20.
//

#include"com_example_liang_com_demo_Com.h"
#include"Logger.h"
#include"Com.h"

JNIEXPORT jint JNICALL Java_com_example_liang_com_1demo_Com_Init_1COM
  (JNIEnv *env, jobject obj){

    LOGD("Com Init %s \n", "");
}


JNIEXPORT jint JNICALL Java_com_example_liang_com_1demo_Com_Send_1COM
  (JNIEnv *env, jobject obj, jstring data){
    LOGD("Com send %s \n", "");

}


JNIEXPORT jint JNICALL Java_com_example_liang_com_1demo_Com_Read_1COM
  (JNIEnv *env, jobject obj, jstring data){
    LOGD("Com read %s \n", "");
}