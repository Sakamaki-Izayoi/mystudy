#include "stdafx.h"
#include "patchguard.h"

namespace ddk::patchguard
{
	void DisPg()
	{
		if (OsIndex < OsIndex_8)
		{
			Disable_Early();
		}
		else
		{
			dispg_new();
		}
		//ȫ�����ô�����
		//dispg_new();
	}
}