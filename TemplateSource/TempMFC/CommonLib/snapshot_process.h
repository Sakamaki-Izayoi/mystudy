#pragma once
#include "stdafx.h"
namespace usr::util::snapshot
{
	using process_item = struct 
	{
		std::wstring process_name;
		DWORD_PTR ProcessId;
		std::vector<DWORD> tids;
	};
	void get_snapshot_process(std::vector<process_item> &_process);
	//��Ҫִ��process_name��ֵ
	BOOL FindProcessByName(process_item &item);
}