#pragma once
//���ͷ�ļ�ֱ���õ�Ӧ�ò�
#ifndef _NTDDK_
#include <winioctl.h>
#endif

//Ϊ�������������Ҫһ��
#define  DEVICE_NAME L"\\Device\\FGDrv"
#define  LINK_NAME   L"\\Dosdevices\\FGDrv"

//ʹ��ʱ�ڶ���������˳�����ӣ���С��0x0800-0x0FFF
static const auto DEVICE_CODE = 0x8000ul;
static const auto FG_IOCTL_HELLO = CTL_CODE(DEVICE_CODE, 0x0800, METHOD_BUFFERED, FILE_ANY_ACCESS);
static const auto FG_IOCTL_HELLO2 = CTL_CODE(DEVICE_CODE, 0x0801, METHOD_BUFFERED, FILE_ANY_ACCESS);

