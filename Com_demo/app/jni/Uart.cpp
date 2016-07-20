#include "Uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "ThreadDefine.h"
#include <termios.h>
#include <string.h>

#include "Logger.h"

#define UART_DEVICE_NAME "/dev/ttyS1"

static THREAD_TYPE staticReceivethread(void* arg) {
	return ((Uart*)arg)->ReceiveThread();
}

static THREAD_TYPE staticOpenDoorThread(void* arg){
	return ((Uart*)arg)->OpenDoorThread();
}

Uart::Uart(){
	this->fd_tty=-1;
	this->isRunning=false;
}
void Uart::openDoor(){
	this->lockOfOpenDoor.unlock();
}

bool Uart::start() {
//	return true;
	this->fd_tty = open(UART_DEVICE_NAME, O_RDWR);
	if (this->fd_tty <= 0)	{
		LOGD("Com::start - open device %s faild\n", UART_DEVICE_NAME);
		return false;
	}

	if(this->set_tty()!=0){
		LOGD("Com::start - fail to set parity\n");
		this->stop();
		return false;
	}

	this->isRunning=true;
	THREAD_ID threadId;
	CREATE_THREAD_PREPARE
	if(!CREATE_THREAD(&threadId,staticReceivethread,this)){
		LOGD("Com::start - create com thread error\n");
		this->stop();
		return false;
	}
	if(!CREATE_THREAD(&threadId,staticOpenDoorThread,this)){
		LOGD("Com::start - create com open door thread error\n");
		this->stop();
		return false;
	}
	return true;
}

void Uart::stop(){
	this->isRunning=false;
	if(this->fd_tty>0){
		close(this->fd_tty);
		this->fd_tty=-1;
	}
}

static int c2i(char c){
	if(c>='0' && c<='9') return c-48;
	if(c>='a' && c<='z') return c-87;
	if(c>='A'&& c<='Z') return c-55;
	return 0;
}

static int chars2int(char* c){
	int temp;
	int bits;
	int num=0;
	for(int i=0;i<6;++i){
		temp=c2i(*(c+i));
		bits=(5-i)*4;
		temp=temp<<bits;
		num+=temp;
	}
	return num;
}

THREAD_TYPE Uart::ReceiveThread(){
	int nread;
	char buff[64];
	int inputnum;
	int cardid;
//    char cardid[64];

	while(this->isRunning){
		if((nread=read(fd_tty,buff,64))<=0){
			usleep(100);
			continue;
		}
		LOGD("Com.cpp, buff=%s",buff);
/*
		if(strstr(buff,"<key>")!=NULL){
			char cNumber=buff[8];
			bool isNumber=true;
			if(cNumber=='*'){
				inputnum=10;
			}else if(cNumber=='#'){
				inputnum=12;
			}else if(cNumber>='0' && cNumber<='9'){
				inputnum=(int)(cNumber-0x30);
			}else{
				isNumber=false;
			}
                        if(isNumber){
                                //this->sendSignal(SignalType::InputNumber,(void*)inputnum);
                        }
		}
		//input idcard
		else if(strstr(buff,"<IC>")!=NULL){
			char *s=strstr(buff,"IC>");
			char *e=strstr(s,"<IC");
			if(e==NULL) continue;
			if((int)(e-s)<11) continue;
			cardid=chars2int(s+5);
                        //this->sendSignal(SignalType::SwipeCard,(void*)cardid);
		}
		//inpur induction
		else if(strstr(buff,"<SE20000F0BB00S>")!=NULL){
                        //this->sendSignal(SignalType::PeopleiInduction,(void*)0);
		}
                */
		memset(buff,0,64);
	}
	return NULL;
}
int Uart::set_tty()
{
    struct termios cfg;
    if (tcgetattr(this->fd_tty, &cfg))
    {
		LOGD("tcgetattr() failed\r\n");
        close(this->fd_tty);

        return -1;
    }

    cfmakeraw(&cfg);
    //设置波特率
    //cfsetispeed(&cfg, B9600);

    cfsetispeed(&cfg, B115200);

    if (tcsetattr(this->fd_tty, TCSANOW, &cfg))
    {
		LOGD("tcsetattr() failed\r\n");
        close(this->fd_tty);

        return -2;
    }
    return 0;
}

THREAD_TYPE Uart::OpenDoorThread(){
	this->lockOfOpenDoor.lock();
	char str[64]="<open>";
	while(this->isRunning){
		this->lockOfOpenDoor.lock();
		if(!this->isRunning) break;
		write(this->fd_tty,str,64);
                //this->sendSignal(SignalType::LockStatus,(void*)LockStatus::Open);
		usleep(3000000);
	}
	this->lockOfOpenDoor.unlock();
	return NULL;
}
/*
int main(){
	LOGD("main\n");
    Com testCom;
    testCom.start();
    testCom.openDoor();
    for(;;){

    }
    return 0;
}
*/