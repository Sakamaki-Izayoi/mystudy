#pragma once
namespace ddk {
	class nt_reg
	{
	public:
		enum DDK_HKEY
		{
			HKEY_CLASSES_ROOT = 1,
			HKEY_CURRENT_USER,
			HKEY_LOCAL_MACHINE,
			HKEY_USERS,
			HKEY_CURRENT_CONFIG,
		};
		nt_reg();
		~nt_reg();
		nt_reg(std::wstring strKey);
		nt_reg(DDK_HKEY key, std::wstring strKey);
		//nt_reg(nt_reg &key);
		//const HANDLE get_handle();
	private:
		HANDLE h_key;
		LONG key_ref;
		std::wstring key_string;
	public:
		bool open(std::wstring strKey);
		bool open(DDK_HKEY key, std::wstring strKey);
		std::wstring get_current_user();
		bool del_key();
		bool del_value(std::wstring val_name);
		bool set_value(std::wstring value_name, ULONG val_type, PVOID value_data, size_t data_size);
		bool get_value(std::wstring value_name, ULONG val_type, PVOID value_buffer, size_t & buffer_size);
		void close();
		nt_reg create_key(std::wstring key_name);
		nt_reg & operator = (nt_reg &_reg)
		{
			this->h_key = _reg.get_handle();
			this->key_ref = 0;
			_reg.set_rel();
			return (*this);
		}
		HANDLE get_handle()
		{
			return h_key;
		}
		void set_rel()
		{
			h_key = nullptr;
		}
	};
};
