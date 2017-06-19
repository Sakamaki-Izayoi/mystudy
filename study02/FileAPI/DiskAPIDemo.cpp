#include "stdafx.h"
using namespace std;

//GetLogicalDrive����
void GetLogicalDrivesDemo()
{
	//�������Ϊ1c--->11100
	//���ұ߿�ʼ��A,B,û�У�CDE��
	DWORD dwFlag = GetLogicalDrives();
	cout << hex << dwFlag << endl;
}

//GetLogicalDriveStrings����
void GetLogicalDriveStringsDemo()
{
	//һ������������е��̷�
	WCHAR szStr[MAX_PATH] = {};
	WCHAR* pStr = szStr;
	DWORD dwRet = GetLogicalDriveStrings(MAX_PATH, szStr);
	if (dwRet <= MAX_PATH && dwRet != 0)
	{
		while (*pStr)
		{
			wcout << pStr << endl;
			pStr += wcslen(pStr) + 1;
		}
	}
}

//FindFirstVolume��FindNextVolume������
void FindVolumeDemo()
{
	//���ظ�ʽ "\\\\?\\Volume{GUID}\\"
	WCHAR strVolName[MAX_PATH] = {};
	HANDLE h_vol = NULL;
	h_vol = FindFirstVolume(strVolName, MAX_PATH);
	wcout << strVolName << endl;

	while (FindNextVolume(h_vol, strVolName, MAX_PATH))
	{
		wcout << strVolName << endl;
	}
	FindVolumeClose(h_vol);
}

//GetDriveType����
void GetDriveTypeDemo()
{
	//DRIVE_UNKNOWN(0)     ����ȷ��
	//DRIVE_NO_ROOT_DIR(1) ����·������
	//DRIVE_REMOVABLE(2)   �豸��ж��
	//DRIVE_FIXED(3)	   �̶��豸����Ӳ����������������(U�̣�SD��)
	//DRIVE_REMOTE(4)      ��������
	//DRIVE_CDROM(5)       CD - ROM����
	//DRIVE_RAMDISK(6)     RAM����
	UINT uFlag = GetDriveType(L"c:\\");
	cout << uFlag << endl;
	uFlag = GetDriveType(L"d:\\");
	cout << uFlag << endl;
	uFlag = GetDriveType(L"e:\\");
	cout << uFlag << endl;
}

//GetVolumeInformation����
void GetVolumeInformationDemo()
{
	WCHAR szVolName[MAX_PATH] = {0};
	BOOL isSuc = GetVolumeInformation(L"c:\\", szVolName, MAX_PATH, NULL, NULL, NULL, NULL, NULL);
}

//FindVolumeMountPoint����
void FindVolumeMountPointDemo()
{
	//�ҵ�c�����ж��ٸ����ص�
	WCHAR szVolName[MAX_PATH] = {0};
	HANDLE h_VolMntPoint = FindFirstVolumeMountPoint(L"c:\\",szVolName, MAX_PATH);
	wcout << "c:\\" << szVolName << endl;

	while (FindNextVolumeMountPoint(h_VolMntPoint, szVolName, MAX_PATH))
	{
		wcout << "c:\\" << szVolName << endl;
	}
	FindVolumeMountPointClose(h_VolMntPoint);
}

//GetVolumeNameForVolumeMountPoint����
void GetVolumeNameForVolumeMountPointDemo()
{

	WCHAR szVolName[MAX_PATH] = {};
	//��������"c:\\","c\\mnt"���ص�Ҳ����
	BOOL isSuc = GetVolumeNameForVolumeMountPoint(L"c:\\mnt\\", szVolName, MAX_PATH);
}

void SetVolumeMountPointDemo()
{
	WCHAR szStr[MAX_PATH] = {};
	GetVolumeNameForVolumeMountPoint(L"e:\\", szStr, MAX_PATH);
	SetVolumeMountPoint(L"c:\\mnt2\\", szStr);
}
void TestDiskApiDemo()
{
	//GetLogicalDrivesDemo();
	//GetLogicalDriveStringsDemo();
	//FindVolumeDemo();
	//GetDriveTypeDemo();
	//GetVolumeInformationDemo();
	//FindVolumeMountPointDemo();
	//GetVolumeNameForVolumeMountPointDemo();
	//SetVolumeMountPointDemo();
	
}