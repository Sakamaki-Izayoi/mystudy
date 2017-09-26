#include <ntifs.h>
#include <ntstrsafe.h>
#include <windef.h>

#define MAX_PATH	260

//ͨ������id���ȫ·��
NTSTATUS  FGGetProcessFullNameByPid(IN HANDLE nPid, OUT PUNICODE_STRING  FullPath);


/***************************************��ý���ȫ·��*********************************************/

//���룺\\??\\c:  �����\\device\\\harddiskvolume1
//LinkTarget.Bufferע��Ҫ�ͷ�
NTSTATUS FGGetSymbolicVolume(IN PUNICODE_STRING SymbolicLinkName, OUT PUNICODE_STRING LinkTarget);

//���룺\\Device\\harddiskvolume1    �����C:
//DosName.Buffer���ڴ�ǵ��ͷ�
NTSTATUS FGGetDosVolume(IN PUNICODE_STRING DeviceName, OUT PUNICODE_STRING DosName);

//���룺\\??\\c:\\windows\\hi.txt    ���\\device\\harddiskvolume1\\windows\\hi.txt
BOOLEAN FGGetSymbolicPath(IN WCHAR * filename, OUT WCHAR * ntname);

//����\\device\\harddiskvolume1\\windows\\hi.txt    �����c:\\windows\\hi.txt
BOOLEAN FGGeDosPath(IN WCHAR *wszNTName, OUT WCHAR *wszFileName);

//���룺��\\??\\c:\\windows\\hi.txt    �����c:\\windows\\hi.txt  δ���

/***************************************��ý���ȫ·��*********************************************/


/***************************************��·����·��ת��*****************************************/
//size -->  WCHAR wszLongName[MAX_PATH] = {0}; sizeof(wszLongName)
BOOL FGConverShortToLongPath(OUT WCHAR *wszLongName, IN WCHAR *wszShortName, IN ULONG size);
/***************************************��·����·��ת��*****************************************/



