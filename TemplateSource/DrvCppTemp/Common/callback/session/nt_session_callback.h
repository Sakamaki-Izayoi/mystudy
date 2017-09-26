#pragma once
namespace ddk::callback
{
	//��2���x�񣬵�һ�N��ExCallBackģʽ���@���]�ęn��һ�㲻Ҫ
	//L"\\Callback\\IoSessionNotifications"
	//Win10�����]��IoRegisterContainerNotification���F
	//�ڶ��N���@���ӵ�
	class nt_session_callback :public Singleton<nt_session_callback>
	{
	public:
		using pfn_callback = std::function<void(PLUID)>;
		nt_session_callback() { init(); };
		~nt_session_callback() {
			SeUnregisterLogonSessionTerminatedRoutine(ddk::callback::nt_session_callback::SeLoginSessionTerminatedRoutine);
			_lock.wait();
		};
	public:
		bool init()
		{
			auto ns = SeRegisterLogonSessionTerminatedRoutine(ddk::callback::nt_session_callback::SeLoginSessionTerminatedRoutine);
			if (NT_SUCCESS(ns))
			{
				return true;
			}
			return false;
		}
	public:
		static NTSTATUS
			SeLoginSessionTerminatedRoutine(
				_In_ PLUID LogonId
			)
		{
			nt_session_callback::getInstance().onCallBack(LogonId);
			return STATUS_SUCCESS;
		}
	private:
		std::vector<pfn_callback> _callback;
		ddk::nt_rundown_protect _lock;
	public:
		void onCallBack(PLUID LogonId)
		{
			_lock.acquire();
			std::for_each(_callback.cbegin(),
				_callback.cend(), [&](auto _pfn) {
				_pfn(LogonId);
			});
			_lock.release();
		}
	};
}