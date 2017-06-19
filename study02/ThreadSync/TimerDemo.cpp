#include "stdafx.h"


#define ONE_SECOND 10000000	//һ��

/**************************�ɵȴ���ʱ��Ӧ��*********************************/
void Demo1()
{
	auto hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	LARGE_INTEGER liDueTime;
	liDueTime.QuadPart = -3 * ONE_SECOND;
	SetWaitableTimer(hTimer, &liDueTime, 2000, NULL, NULL, FALSE);
	
	while (TRUE)
	{
		//��һ��3���ִ�У�
		//֮��ÿ2��ִ��һ�Σ�����ѭ����
		if (!WaitForSingleObject(hTimer, INFINITE))
		{
			printf("hoho\n");
		}
	}
	
}
/************************************************************************/

/*************************APC�Ŀɵȴ���ʱ��******************************/
typedef struct _APC_PROC_ARG
{
	CHAR *szText;
	DWORD dwValue;
}APC_PROC_ARG;
VOID CALLBACK TimerAPCProc(LPVOID lpArgToCompletionRoutine, DWORD  dwTimerLowValue, DWORD  dwTimerHighValue)
{
	APC_PROC_ARG *pData = (APC_PROC_ARG *)lpArgToCompletionRoutine;
	printf("Message:%s\nValue:%d\n\n", pData->szText, pData->dwValue);
	MessageBeep(MB_OK);
}
void Demo2()
{
	auto hTimer = CreateWaitableTimer(NULL, FALSE, L"MyTimer");
	APC_PROC_ARG ApcData;
	ApcData.szText = "Message to apc proc";
	ApcData.dwValue = 1;
	//INT64 qwDueTime;
	LARGE_INTEGER liDueTime;

	if (hTimer)
	{
		liDueTime.QuadPart = -5 * ONE_SECOND;
		auto bSuccess = SetWaitableTimer(
			hTimer,
			&liDueTime, //��һ�δ�����ʲôʱ�򣬿��Ը�����ʱ�䣬Ҳ���Ը����ʱ�䣬�����������ʱ��
			2000,		//ÿ�������봥��һ��
			TimerAPCProc,
			&ApcData,
			FALSE);

		for (; ApcData.dwValue <= 4; ApcData.dwValue++)
		{
			printf("��ʼ�ȴ���\n");
			SleepEx(INFINITE, TRUE);
		}
	}
}
/************************************************************************/
void TestTimerDemo()
{
	Demo1();
	//Demo2();
}