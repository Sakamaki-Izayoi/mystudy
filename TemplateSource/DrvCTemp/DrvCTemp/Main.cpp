#include "stdafx.h"
#include "Driver.h"


VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
	//do something when driver unload
	UNICODE_STRING ucLinkName = { 0 };
	RtlInitUnicodeString(&ucLinkName, LINK_NAME);
	IoDeleteSymbolicLink(&ucLinkName);
	IoDeleteDevice(pDriverObject->DeviceObject);
	DbgPrint("Driver unloaded\r\n");
}

#pragma INITCODE
extern "C"
NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT  pDriverObject,_In_ PUNICODE_STRING RegistryPathName)
{
	UNREFERENCED_PARAMETER(RegistryPathName);
	NTSTATUS status = STATUS_SUCCESS;
	//�����豸
	status = CreateDevice(pDriverObject);
	
	DbgPrint("Driver load ok!\r\n", status);
	return status;
}

NTSTATUS CreateDevice(IN PDRIVER_OBJECT pDriverObject)
{
	NTSTATUS status = 0;
	UNICODE_STRING ucDeviceName = { 0 };
	UNICODE_STRING ucLinkName = { 0 };
	PDEVICE_OBJECT pDevObj = NULL;
	RtlInitUnicodeString(&ucDeviceName, DEVICE_NAME);
	RtlInitUnicodeString(&ucLinkName, LINK_NAME);

	//1.�����豸
	status = IoCreateDevice(pDriverObject,
		0,
		&ucDeviceName,
		FILE_DEVICE_UNKNOWN,
		0, FALSE,
		&pDevObj);

	if (!NT_SUCCESS(status))
	{
		DbgPrint("IoCreateDevice failed:%x", status);
		return status;
	}

	//2.������������
	status = IoCreateSymbolicLink(&ucLinkName, &ucDeviceName);

	if (!NT_SUCCESS(status))
	{
		IoDeleteDevice(pDevObj);
		DbgPrint("IoCreateSymblic failed:%x\n", status);
		return status;
	}

	//3.ָ���ַ�����
	pDevObj->Flags |= DO_BUFFERED_IO;

	for (int i = 0; i < IRP_MJ_MAXIMUM_FUNCTION + 1; i++)
	{
		pDriverObject->MajorFunction[i] = DispatchCommon;
	}
	pDriverObject->MajorFunction[IRP_MJ_CREATE] = DispatchCreate;
	pDriverObject->MajorFunction[IRP_MJ_READ] = DispatchRead;
	pDriverObject->MajorFunction[IRP_MJ_WRITE] = DispatchWrite;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchIoCtl;
	pDriverObject->MajorFunction[IRP_MJ_CLEANUP] = DispatchClean;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = DispatchClose;
	pDriverObject->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}


NTSTATUS DispatchCommon(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	//ʲôҲ����ģ��
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;
	DbgPrint("common call");
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS DispatchCreate(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	//do something
	DbgPrint("create call");
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;

	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	//ending
	return STATUS_SUCCESS;
}

NTSTATUS DispatchRead(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	//��ǰ�������ڶ�ȡ�����ļ�ʲô��   2016.4.9

	PVOID pReadBuffer = NULL;	//R0��R3ͨѶ��buffer����pstack�л��
	ULONG uReadLength = 0;		//R3ָ����ȡ�����ֽڣ���pstack�л��
	PIO_STACK_LOCATION pStack = NULL;	//����R3�ɹ���ʧ�ܣ��ɹ����ض����ֽ�

	pStack = IoGetCurrentIrpStackLocation(pIrp);

	pReadBuffer = pIrp->AssociatedIrp.SystemBuffer;
	uReadLength = pStack->Parameters.Read.Length;	//R3��ָ��

													//begin read...
	DbgPrint("read call");
	//end read.....

	pIrp->IoStatus.Status = STATUS_SUCCESS;		//�����жϺ���򷵻سɹ���ʧ��
	pIrp->IoStatus.Information = 0;				//�ں���ʵ��ȡ�˶�������,���Լ�д

	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS DispatchWrite(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	PVOID pWriteBuffer = NULL;
	ULONG uWriteLength = 0;
	PIO_STACK_LOCATION pStack = NULL;

	pStack = IoGetCurrentIrpStackLocation(pIrp);

	pWriteBuffer = pIrp->AssociatedIrp.SystemBuffer;
	uWriteLength = pStack->Parameters.Write.Length;	//R3��ָ��

													//begin write...
	DbgPrint("write call");
	//end write.....

	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}
NTSTATUS DispatchIoCtl(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	ULONG uIoctrlCode = 0;
	PVOID pInputBuffer = NULL;
	PVOID pOutputBuffer = NULL;
	ULONG uInputLength = 0;
	ULONG uOutputLength = 0;
	PIO_STACK_LOCATION pStack = IoGetCurrentIrpStackLocation(pIrp);

	pInputBuffer = pOutputBuffer = pIrp->AssociatedIrp.SystemBuffer;
	uInputLength = pStack->Parameters.DeviceIoControl.InputBufferLength;
	uOutputLength = pStack->Parameters.DeviceIoControl.OutputBufferLength;

	uIoctrlCode = pStack->Parameters.DeviceIoControl.IoControlCode;

	switch (uIoctrlCode)
	{
	case IOCTL_SEND_RESULT_TO_R0:
		//do something you want
		DbgPrint("io_ctl your code call");
		//ending
		break;;
	default:
		break;
	}

	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS DispatchClean(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	//do something
	DbgPrint("clean call");
	//ending
	return STATUS_SUCCESS;
}

NTSTATUS DispatchClose(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	//do something
	DbgPrint("close call");
	//ending
	return STATUS_SUCCESS;
}

