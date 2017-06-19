/**********************************************************************************************//**
 * @file	Services.cpp
 *
 * @brief	�������
 **************************************************************************************************/

#include"stdafx.h"  //������ͷ�ļ�

//����ȫ�ֺ�������
void Init();
BOOL IsInstalled();
BOOL Install();
BOOL Uninstall();
void LogEvent(LPCTSTR pszFormat, ...);
void WINAPI ServiceMain();
void WINAPI ServiceStrl(DWORD dwOpcode);

TCHAR szServiceName[] = _T("WatchDog"); ///< The service name[]
BOOL bInstall;  ///< true to install
SERVICE_STATUS_HANDLE hServiceStatus;   ///< The service status
SERVICE_STATUS status;  ///< The status
DWORD dwThreadID;   ///< Identifier for the thread

/**********************************************************************************************//**
 * @fn	int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
 *
 * @brief	Window main.
 *
 * @author	FrogGod
 * @date	2016/5/19
 *
 * @param	hInstance	 	The instance.
 * @param	hPrevInstance	The previous instance.
 * @param	lpCmdLine	 	The command line.
 * @param	nCmdShow	 	The command show.
 *
 * @return	An APIENTRY.
 **************************************************************************************************/

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR     lpCmdLine,
	int       nCmdShow)
{
	Init();

	dwThreadID = ::GetCurrentThreadId();

	SERVICE_TABLE_ENTRY st[] =
	{
		{ szServiceName, (LPSERVICE_MAIN_FUNCTION)ServiceMain },
		{ NULL, NULL }
	};

	if (_tcsicmp(lpCmdLine, _T("/install")) == 0)
	{
		Install();
	}
	else if (_tcsicmp(lpCmdLine, _T("/uninstall")) == 0)
	{
		Uninstall();
	}
	else
	{
		if (!::StartServiceCtrlDispatcher(st))
		{
			LogEvent(_T("Register Service Main Function Error!"));
		}
	}

	return 0;
}

/**********************************************************************************************//**
 * @fn	void Init()
 *
 * @brief	S this object.
 *
 * @author	FrogGod
 * @date	2016/5/19
 **************************************************************************************************/

void Init()
{
	hServiceStatus = NULL;
	status.dwServiceType = SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS;
	status.dwCurrentState = SERVICE_START_PENDING;
	status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	status.dwWin32ExitCode = 0;
	status.dwServiceSpecificExitCode = 0;
	status.dwCheckPoint = 0;
	status.dwWaitHint = 0;
}

/**********************************************************************************************//**
 * @fn	void WINAPI ServiceMain()
 *
 * @brief	Service main.
 *
 * @author	FrogGod
 * @date	2016/5/19
 *
 * @return	A WINAPI.
 **************************************************************************************************/

void WINAPI ServiceMain()
{
	// Register the control request handler
	status.dwCurrentState = SERVICE_START_PENDING;
	status.dwControlsAccepted = SERVICE_ACCEPT_STOP;

	//ע��������
	hServiceStatus = RegisterServiceCtrlHandler(szServiceName, ServiceStrl);
	if (hServiceStatus == NULL)
	{
		LogEvent(_T("Handler not installed"));
		return;
	}
	SetServiceStatus(hServiceStatus, &status);

	status.dwWin32ExitCode = S_OK;
	status.dwCheckPoint = 0;
	status.dwWaitHint = 0;
	status.dwCurrentState = SERVICE_RUNNING;
	SetServiceStatus(hServiceStatus, &status);

	//ģ���������С�Ӧ��ʱ����Ҫ������ڴ˼���
	//���ڴ�д�Ϸ�����Ҫִ�еĴ��룬һ��Ϊ��ѭ��
	while (1)
	{
		//��������Լ�����
		OutputDebugStringA("haha");
		Sleep(1000);
	}
	status.dwCurrentState = SERVICE_STOPPED;
	SetServiceStatus(hServiceStatus, &status);
	OutputDebugString(_T("Service stopped"));
}

/**********************************************************************************************//**
 * @fn	void WINAPI ServiceStrl(DWORD dwOpcode)
 *
 * @brief	Service strl.
 *
 * @author	FrogGod
 * @date	2016/5/19
 *
 * @param	dwOpcode	The opcode.
 *
 * @return	A WINAPI.
 **************************************************************************************************/

void WINAPI ServiceStrl(DWORD dwOpcode)
{
	switch (dwOpcode)
	{
	case SERVICE_CONTROL_STOP:
		status.dwCurrentState = SERVICE_STOP_PENDING;
		SetServiceStatus(hServiceStatus, &status);
		PostThreadMessage(dwThreadID, WM_CLOSE, 0, 0);
		break;
	case SERVICE_CONTROL_PAUSE:
		break;
	case SERVICE_CONTROL_CONTINUE:
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		break;
	default:
		LogEvent(_T("Bad service request"));
		OutputDebugString(_T("Bad service request"));
	}
}

/**********************************************************************************************//**
 * @fn	BOOL IsInstalled()
 *
 * @brief	Query if this object is installed.
 *
 * @author	FrogGod
 * @date	2016/5/19
 *
 * @return	true if installed, false if not.
 **************************************************************************************************/

BOOL IsInstalled()
{
	BOOL bResult = FALSE;

	//�򿪷�����ƹ�����
	SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (hSCM != NULL)
	{
		//�򿪷���
		SC_HANDLE hService = ::OpenService(hSCM, szServiceName, SERVICE_QUERY_CONFIG);
		if (hService != NULL)
		{
			bResult = TRUE;
			::CloseServiceHandle(hService);
		}
		::CloseServiceHandle(hSCM);
	}
	return bResult;
}

/**********************************************************************************************//**
 * @fn	BOOL Install()
 *
 * @brief	Installs this object.
 *
 * @author	FrogGod
 * @date	2016/5/19
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

BOOL Install()
{
	if (IsInstalled())
		return TRUE;

	//�򿪷�����ƹ�����
	SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		MessageBox(NULL, _T("Couldn't open service manager"), szServiceName, MB_OK);
		return FALSE;
	}

	// Get the executable file path
	TCHAR szFilePath[MAX_PATH];
	::GetModuleFileName(NULL, szFilePath, MAX_PATH);

	//��������
	SC_HANDLE hService = ::CreateService(hSCM, szServiceName, szServiceName,
		SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_NORMAL,
		szFilePath, NULL, NULL, _T(""), NULL, NULL);

	if (hService == NULL)
	{
		::CloseServiceHandle(hSCM);
		MessageBox(NULL, _T("Couldn't create service"), szServiceName, MB_OK);
		return FALSE;
	}

	::CloseServiceHandle(hService);
	::CloseServiceHandle(hSCM);
	return TRUE;
}

/**********************************************************************************************//**
 * @fn	BOOL Uninstall()
 *
 * @brief	Uninstalls this object.
 *
 * @author	FrogGod
 * @date	2016/5/19
 *
 * @return	true if it succeeds, false if it fails.
 **************************************************************************************************/

BOOL Uninstall()
{
	if (!IsInstalled())
		return TRUE;

	SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (hSCM == NULL)
	{
		MessageBox(NULL, _T("Couldn't open service manager"), szServiceName, MB_OK);
		return FALSE;
	}

	SC_HANDLE hService = ::OpenService(hSCM, szServiceName, SERVICE_STOP | DELETE);

	if (hService == NULL)
	{
		::CloseServiceHandle(hSCM);
		MessageBox(NULL, _T("Couldn't open service"), szServiceName, MB_OK);
		return FALSE;
	}
	SERVICE_STATUS status;
	::ControlService(hService, SERVICE_CONTROL_STOP, &status);

	//ɾ������
	BOOL bDelete = ::DeleteService(hService);
	::CloseServiceHandle(hService);
	::CloseServiceHandle(hSCM);

	if (bDelete)
		return TRUE;

	LogEvent(_T("Service could not be deleted"));
	return FALSE;
}

/**********************************************************************************************//**
 * @fn	void LogEvent(LPCTSTR pFormat, ...)
 *
 * @brief	Logs an event.
 *
 * @author	FrogGod
 * @date	2016/5/19
 *
 * @param	pFormat	Describes the format to use.
 * @param	...	   	Variable arguments providing additional information.
 **************************************************************************************************/

void LogEvent(LPCTSTR pFormat, ...)
{
	TCHAR    chMsg[256];
	HANDLE  hEventSource;
	LPTSTR  lpszStrings[1];
	va_list pArg;

	va_start(pArg, pFormat);
	_vstprintf_s(chMsg, pFormat, pArg);
	va_end(pArg);

	lpszStrings[0] = chMsg;

	hEventSource = RegisterEventSource(NULL, szServiceName);
	if (hEventSource != NULL)
	{
		ReportEvent(hEventSource, EVENTLOG_INFORMATION_TYPE, 0, 0, NULL, 1, 0, (LPCTSTR*)&lpszStrings[0], NULL);
		DeregisterEventSource(hEventSource);
	}
}
