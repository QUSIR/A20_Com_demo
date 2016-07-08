#ifndef COM_H
#define COM_H

#include "Subject.h"
#include "ThreadDefine.h"
#include "Lock.h"

#define CardMax  50

class Com : public Subject
{
public:
	Com();
	bool start();
	void stop();
	void openDoor();
	THREAD_TYPE ReceiveThread(void);
	THREAD_TYPE OpenDoorThread();

private:
	int fd_tty;
	bool isRunning;
	Lock lockOfOpenDoor;

	int set_tty();

};

#endif // COM_H
