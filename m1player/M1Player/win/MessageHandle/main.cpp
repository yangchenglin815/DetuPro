#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#include "TESTMessageHandle.h"
#include "TESTMessageQueue.h"

#define TEST_MESSAGE_QUEUE 1
//#define TEST_MESSAGE_HANDLE 1

#ifdef TEST_MESSAGE_QUEUE
int main()
{
	TestUI* manger = new TestUI;
	manger->Start();

	while (true)
	{
		char c;
		scanf("%c", &c);

		if (c == 'q' || c == 'Q'){
			break;
		}
	}

QUIT:
	if (manger){
		delete manger;
	}

	system("pause");
	return 0;
}
#elif TEST_MESSAGE_HANDLE
int main()
{
	CManager* manger = new CManager;
	manger->start();

	while (true)
	{
		char c;
		scanf("%c", &c);

		if (c == 'q' || c == 'Q'){
			break;
		}
	}

QUIT:
	if (manger){
		delete manger;
	}

	system("pause");
	return 0;
}
#endif
