#include <ntddk.h>

/*�����ļ�*/
NTSTATUS FGCreateFile(IN PUNICODE_STRING filePath, OUT PHANDLE hFile, OUT PIO_STATUS_BLOCK pios);

/*�����ļ��У�  ��Ҫ�Ż�ѭ����������*/
NTSTATUS FGCreateDirectory(IN PUNICODE_STRING directoryPath, OUT PHANDLE phFile, OUT PIO_STATUS_BLOCK pios);

/*д�ļ�*/
NTSTATUS FGWriteFile(IN PUNICODE_STRING filePath, IN PUNICODE_STRING content, OUT PIO_STATUS_BLOCK pios);

/*���ļ����ѷ��䣬�м��ͷ��ڴ�*/
NTSTATUS FGReadFile(IN PUNICODE_STRING filePath, OUT PUNICODE_STRING content, OUT PIO_STATUS_BLOCK pios);

/*�����ļ�*/
NTSTATUS FGCopyfile(IN PUNICODE_STRING src, IN PUNICODE_STRING dst, OUT PIO_STATUS_BLOCK pios);

/*ɾ���ļ�*/
NTSTATUS FGDeleteFile(IN PUNICODE_STRING filePath, OUT PIO_STATUS_BLOCK pios);

/*�����ļ�*/
NTSTATUS FGMovefile(IN PUNICODE_STRING src, IN PUNICODE_STRING dst, OUT PIO_STATUS_BLOCK pios);

