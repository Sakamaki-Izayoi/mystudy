#include "stdafx.h"

#define THREAD_NUM 3
int g_num = 0;
int g_num1 = 0;
HANDLE hThreads[THREAD_NUM];
HANDLE gMutex = NULL;
/*****************��ʹ�û����ȫ������*********************/
DWORD WINAPI DoAdd(LPVOID lpParam)
{
	for (auto i = 0; i < 100000; i++)
	{
		g_num++;
	}
	return 1;
}

void AddWithoutMutex()
{
	for (auto i = 0; i < THREAD_NUM; i++)
	{
		hThreads[i] = CreateThread(NULL, 0, DoAdd, &i, 0, NULL);
	}
	WaitForMultipleObjects(THREAD_NUM, hThreads, TRUE, INFINITE);
	std::cout << "�����" << g_num << "(����ȷ��δʹ�û�����)" << std::endl;
	getchar();
}
/**********************************************************/

/********************���������߳�ͬ��*********************/
DWORD WINAPI DoAdd1(LPVOID lpParam)
{
	//����wait���������mutex��Ϊ�߳�ӵ�У��������̵߳ȴ�
	//��mutex�ѱ������߳�ӵ�У���ȴ�
	if (!WaitForSingleObject(gMutex, INFINITE))
	{
		for (auto i = 0; i < 100000; i++)
		{
			g_num1++;
		}
		ReleaseMutex(gMutex);
	}
	return 1;
}

void AddWithMutex()
{
	gMutex = CreateMutex(NULL, TRUE, NULL);

	for (auto i = 0; i < THREAD_NUM; i++)
	{
		hThreads[i] = CreateThread(NULL, 0, DoAdd1, NULL, 0, NULL);
	}
	WaitForMultipleObjects(THREAD_NUM, hThreads, TRUE, INFINITE);
	std::cout << "�����" << g_num1 << std::endl;
	getchar();
}
/*********************************************************/

void TestMutexDemo()
{
	AddWithoutMutex();
	AddWithMutex();
}