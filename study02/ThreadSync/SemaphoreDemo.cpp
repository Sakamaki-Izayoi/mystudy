#include "stdafx.h"
#define  THREAD_NUM 4
HANDLE hSemaThreads[THREAD_NUM];
HANDLE gSem;

//�ź����߳�ͬ��

DWORD WINAPI SemaThreadProc(LPVOID lpParam)
{
	int num = *((int *)lpParam);
	LONG oldCnts;
	for (auto i = 0; i < THREAD_NUM; i++)
	{
		if (!WaitForSingleObject(gSem, INFINITE))
		{
			std::cout << "�߳�" << num << "����ź�����" << std::endl;
			Sleep(500);
			ReleaseSemaphore(gSem, 1, &oldCnts);
		}
	}
	return 1;
}


void Demo()
{
	gSem = CreateSemaphore(NULL, 3, 3, NULL);

	for (auto i = 0; i < THREAD_NUM; i++)
	{
		hSemaThreads[i] = CreateThread(NULL, 0, SemaThreadProc, &i, 0, NULL);
		Sleep(200);	//��΢ͣ�£�Ҫ��Ȼȫ����������Ż��ҵ�����Ϊ���Ǵ����ǵ�ַ
	}
	WaitForMultipleObjects(THREAD_NUM, hSemaThreads, TRUE, INFINITE);
	getchar();
}

void TestSemaphoreDemo()
{
	Demo();
}