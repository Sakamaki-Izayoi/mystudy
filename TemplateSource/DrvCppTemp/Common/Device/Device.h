#pragma once
namespace ddk
{
	typedef struct _DEVICE_EXTENSION
	{
		DWORD32		Tag;//��ֹ���ⷢ����Tag
		LIST_ENTRY	ListHead;			//�������IRP����
		KSPIN_LOCK  ListLock;			//IRP���������   
		KEVENT      RequestEvent;		//����/�����¼�
		PVOID       ThreadObject;		//�����̶߳���
		BOOLEAN     bTerminateThread;	//�Ƿ���Ҫ��ֹ�߳�
		PSECURITY_CLIENT_CONTEXT SecurityClientCtx;
		PVOID		DeviceThis;
	} DEVICE_EXTENSION, *PDEVICE_EXTENSION;
	using  callback_ioctrl = std::function<NTSTATUS(PVOID, ULONG, PVOID, ULONG, ULONG_PTR *)>;
	using  callback_irp = std::function<NTSTATUS(PDEVICE_OBJECT, PIRP)>;
	class nt_device
	{
	public:
		nt_device();
		~nt_device();
	private:
		PDRIVER_OBJECT driver_object;
		PDEVICE_OBJECT device_object;
		UNICODE_STRING nsDosName;
		UNICODE_STRING nsDeviceName;
		void DrvTerminater();
	public:
		void set_device_code(DWORD dwCode);
	private:
		DWORD dwDeviceCode;
		std::map<DWORD, callback_ioctrl> map_ioctrl;
		std::map<int, callback_irp>map_irp_routine;
	public:
		void set_ioctrl_callback(DWORD code,callback_ioctrl callback);
		void set_irp_callback(int irp, callback_irp callback);
		bool create_device(LPCWSTR device_name, LPCWSTR dos_name,bool b_asyn=false);
		void asyn_thread_work();
	public:
		static NTSTATUS DeviceIrpProc(
			IN PDEVICE_OBJECT DeviceObject,
			IN PIRP Irp);
		NTSTATUS device_irp(PIRP Irp);
		static NTSTATUS default_irp_routine(PDEVICE_OBJECT devobj, PIRP Irp);
		static KSTART_ROUTINE asyn_thread_routine;
	private:
		bool Asyn_able;
	private:
		NTSTATUS
			AdjustPrivilege(
				IN ULONG    Privilege,
				IN BOOLEAN  Enable
				);
	public:
		bool is_asyn();
	};
}


