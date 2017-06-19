#include "stdafx.h"
#include <functional>
using namespace std;

//
/*********************�ļ�ɾ�������ƣ����������ƶ��ļ� ********************/
#define FILE_PATH L"C:\\Users\\killvxk\\Desktop\\123.txt"
#define NEW_PATH  L"C:\\Users\\killvxk\\Desktop\\456.txt"
void Demo1()
{
	BOOL isSuc = FALSE;
	isSuc = CopyFile(FILE_PATH, NEW_PATH, TRUE);
	if (isSuc)
		cout << "copy success" << endl;

	isSuc = DeleteFile(FILE_PATH);
	if (isSuc)
		cout << "delete success!" << endl;

	isSuc = MoveFile(NEW_PATH, L"c:\\Users\\killvxk\\Desktop\\mov.txt");
	if (isSuc)
		cout << "move success" << endl;
}
/************************************************************************/

/*********************��ȡ�ļ���С����ȡ�ļ�����*************************/
DWORD ReadFileContent(LPWSTR szFilePath)
{
	LARGE_INTEGER liFileSize;
	DWORD64 totalRead = 0;
	DWORD dwReadedSize = 0;
	BYTE lpBuf[32];

	auto h_file = CreateFile(szFilePath,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL, OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (h_file == INVALID_HANDLE_VALUE)
	{
		cout << "CreateFileʧ�� :" << GetLastError() << endl;
		return 0;
	}

	if (!GetFileSizeEx(h_file, &liFileSize))//��ȡ�ļ���С
	{

		CloseHandle(h_file);
		cout << "GetFileSizeExʧ��:" << GetLastError() << endl;
		return 0;
	}
	else
	{
		cout << "�ļ���СΪ:" << liFileSize.QuadPart << endl;
	}

	while (true)
	{
		auto isSuc = ReadFile(h_file, lpBuf, 32, &dwReadedSize, NULL);//��ȡ���ݣ�ÿ�ζ�ȡ�����ƶ��ļ�ָ��
		if (!isSuc) break;

		for (DWORD i = 0; i < dwReadedSize; i++)
		{
			printf("%c", lpBuf[i]);
		}

		totalRead += dwReadedSize;

		if (totalRead == liFileSize.QuadPart)
		{
			printf("\n");
			cout << "��ȡ����" << endl;
			break;
		}
	}
	return 0;
}
/************************************************************************/

/****************** �����ļ�ָ�룬д���ݵ��ļ���**************************/
DWORD SaveDataToFile(LPWSTR szFilePath, LPVOID lpData, DWORD dwDataSize)
{
	HANDLE h_file = NULL;
	DWORD dwWriteSize = 0;
	h_file = CreateFile(szFilePath, GENERIC_ALL, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (h_file == INVALID_HANDLE_VALUE)
	{
		cout << "CreateFileʧ�� :" << GetLastError() << endl;
		return 0;
	}
	SetFilePointer(h_file, 0, 0, FILE_END);
	WriteFile(h_file, lpData, dwDataSize, &dwWriteSize, NULL);
	CloseHandle(h_file);
	return dwWriteSize;
}
/************************************************************************/

/*************************Ŀ¼��������********************************/
void DirectoryDemo()
{
	WCHAR szCurDir[MAX_PATH];
	WCHAR szModuleName[MAX_PATH];
	DWORD dwCurlen = GetCurrentDirectory(MAX_PATH, szCurDir);	//��õ�ǰĿ¼
	if (dwCurlen == 0)
		return;
	wcout << szCurDir << "     ���ȣ�" << dwCurlen << endl;

	wcscpy_s(szCurDir, L"E:\\");
	SetCurrentDirectory(szCurDir);	//���õ�ǰĿ¼
	dwCurlen = GetCurrentDirectory(MAX_PATH, szCurDir);
	wcout << szCurDir << "     ���ȣ�" << dwCurlen << endl;
	CreateDirectory(L"hamage", NULL);

	GetModuleFileName(NULL, szModuleName, MAX_PATH);
	wcout << szModuleName << endl;
	GetModuleFileName(LoadLibraryA("kernel32.dll"), szModuleName, MAX_PATH);
	wcout << szModuleName << endl;

}
/************************************************************************/

/***********************����ĳĿ¼�е��ļ�����Ŀ¼**************************/
void EnumFileInDir(LPWSTR szPath)
{
	//��������Ҫʹ��ͨ���
	WIN32_FIND_DATA fileData;
	wcscat_s(szPath, MAX_PATH, L"\\*");
	auto h_find = FindFirstFile(szPath, &fileData);
	if (INVALID_HANDLE_VALUE == h_find)
		return;

	do
	{
		//�����кܶ����ԣ������صȣ��������ɸѡ
		wcout << hex << fileData.dwFileAttributes << "\t";
		wcout << fileData.cFileName << endl;
	} while (FindNextFile(h_find, &fileData));
	FindClose(h_find);
}
//����ĳĿ¼�����е��ļ�����Ŀ¼
void EnumAllInDir(LPCWSTR szPath)
{
	WCHAR szFilePath[MAX_PATH] = {};	
	WCHAR szRecurPath[MAX_PATH] = {};//������ļ��м�����ȥ
	WIN32_FIND_DATA data = {};
	wcscpy_s(szFilePath, MAX_PATH, szPath);
	wcscat_s(szFilePath, MAX_PATH, L"\\*");//ͨ�����APIҪ��
	auto h_find = FindFirstFile(szFilePath, &data);
	if (h_find == INVALID_HANDLE_VALUE)
		return;
	do
	{
		if (wcscmp(L".", data.cFileName) == 0 || wcscmp(L"..", data.cFileName) == 0)
			continue;
		
		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			wsprintf(szRecurPath, L"%s\\%s", szPath, data.cFileName);
			EnumAllInDir(szRecurPath);
		}
		else
		{
			wcout << data.cFileName << endl;
		}
	} while (FindNextFile(h_find, &data));
}
/************************************************************************/

/*************************��ȡ�ļ�����********************************/
void ShowFileAttribute(LPCWSTR szPath)
{
	auto showTime = [=](PFILETIME ptime) {
		FILETIME ftLocal;
		SYSTEMTIME st;
		FileTimeToLocalFileTime(ptime, &ftLocal);
		FileTimeToSystemTime(&ftLocal, &st);
		cout << st.wYear << "��";
		cout << st.wMonth << "��";
		cout << st.wDay << "��";
		cout << "����" << st.wDayOfWeek << "  ";
		cout << st.wHour << ":";
		cout << st.wMinute << ":";
		cout << st.wSecond << endl;
	};
	WIN32_FIND_DATA data;
	if (!GetFileAttributesEx(szPath, GetFileExInfoStandard, &data))
		return;
	cout << "����ʱ�䣺", showTime(&data.ftCreationTime);
	cout << "������ʱ��", showTime(&data.ftLastWriteTime);
	cout << "����޸�ʱ��", showTime(&data.ftLastWriteTime);
	
	LARGE_INTEGER fileSize = {};
	fileSize.HighPart = data.nFileSizeHigh;
	fileSize.LowPart = data.nFileSizeLow;
	cout << "�ļ���С" << fileSize.QuadPart << endl;;
	cout << "����Щ��ʾ��dwFileAttributes" << endl;
}
/************************************************************************/

/*********************�����ļ�����*************************************/
void SetFileAttributesDemo(LPCWSTR szPath)
{
	DWORD dwFlag = GetFileAttributes(szPath);
	dwFlag |= FILE_ATTRIBUTE_READONLY;
	SetFileAttributes(szPath, dwFlag);
}
/************************************************************************/

/**************************�ļ�ӳ��,�޸ļ�ˢ��*******************************/
#define FILE_MAP_START 0x0
void FileMapDemo(LPCWSTR szPath)
{
	SYSTEM_INFO si = {};
	GetSystemInfo(&si);
	DWORD dwSysGran = si.dwAllocationGranularity;
	DWORD dwFileMapStart = (FILE_MAP_START / dwSysGran) *dwSysGran;
	DWORD dwMapViewSize = 0x1000;

	auto h_file = CreateFile(szPath, GENERIC_ALL, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	auto h_mapfile = CreateFileMapping(h_file, NULL, PAGE_EXECUTE_READWRITE, 0, dwMapViewSize, NULL);
	auto lpMapAddr = MapViewOfFile(h_mapfile, FILE_MAP_ALL_ACCESS, 0, dwFileMapStart, dwMapViewSize);

	PBYTE pToFileMap = static_cast<PBYTE>(lpMapAddr);
	for (UINT i = 1; i <= dwMapViewSize; i++)
	{
		printf("%02x ", *pToFileMap);
		pToFileMap++;
		if (i % 0x10 == 0)
			cout << endl;
	}
	//FillMemory(lpMapAddr, 1, 0xff);
	FillMemory(lpMapAddr, 1, 0x4d);
	FlushViewOfFile(lpMapAddr, dwMapViewSize);
	UnmapViewOfFile(lpMapAddr);
	CloseHandle(h_mapfile);
	CloseHandle(h_file);
}
/************************************************************************/

void TestFileFuncDemo()
{
	std::locale::global(std::locale(""));
	//Demo1();

	/*******************�ļ���д*******************************/
	//ReadFileContent(FILE_PATH);
	//CHAR szFoo[] = "\r\n�Ҳ�����";
	//SaveDataToFile(FILE_PATH, szFoo, strlen(szFoo));
	//DirectoryDemo();
	
	/*******************Ŀ¼����*******************************/
	//ö��Ŀ¼
	//WCHAR path[MAX_PATH] = L"E:\\360Downloads\\software";
	//EnumFileInDir(path);
	//EnumAllInDir(L"C:\\360��ȫ���������");

	/*******************�ļ�����******************************/
	//ShowFileAttribute(L"E:\\360Downloads\\software\\AdobeReader_yjzj.exe");
	//SetFileAttributesDemo(L"E:\\360Downloads\\software\\AdobeReader_yjzj.exe");

	/****************************************************/
	FileMapDemo(L"E:\\360Downloads\\software\\1111.exe");

}