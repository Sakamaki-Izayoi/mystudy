#pragma once
#include "stdafx.h"

//Ϊ�������������Ҫһ��
#define  DEVICE_NAME L"\\device\\DrvCTemp"
#define  LINK_NAME   L"\\dosdevices\\DrvCTemp"

#define IOCTRL_BASE 0X8000
#define FGIOCTRL_CODE(i) \
	CTL_CODE(FILE_DEVICE_UNKNOWN, IOCTRL_BASE + i, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_SEND_RESULT_TO_R0 FGIOCTRL_CODE(0)
#define IOCTL_XXX_ATTACK        FGIOCTRL_CODE(1)

struct _DEVICE_EXTENSION
{
	int abc;
}DEVICE_EXTENSION, *PDEVICE_EXTENSION;


/*ж�غ���*/
VOID DriverUnload(PDRIVER_OBJECT pDriverObject);
NTSTATUS CreateDevice(IN PDRIVER_OBJECT pDriverObject);
/*ͨ�÷ַ�����*/
NTSTATUS DispatchCommon(PDEVICE_OBJECT pDevObj, PIRP pIrp);
/*�����ַ�����*/
NTSTATUS DispatchCreate(PDEVICE_OBJECT pDevObj, PIRP pIrp);
/*���ַ�����*/
NTSTATUS DispatchRead(PDEVICE_OBJECT pDevObj, PIRP pIrp);
/*д�ַ�����*/
NTSTATUS DispatchWrite(PDEVICE_OBJECT pDevObj, PIRP pIrp);
/*���Ʒַ�����*/
NTSTATUS DispatchIoCtl(PDEVICE_OBJECT pDevObj, PIRP pIrp);
/*����ַ�����*/
NTSTATUS DispatchClean(PDEVICE_OBJECT pDevObj, PIRP pIrp);
/*�رշַ�����*/
NTSTATUS DispatchClose(PDEVICE_OBJECT pDevObj, PIRP pIrp);