#include "stdafx.h"
#include <windows.h>
//���������Demo

//����N��������������
void Demo001()
{
	//���������
	auto vec = std::vector<UINT>{};
	std::generate_n(std::back_inserter(vec), 10000, [=]() {
		UINT num = 0;
		_rdrand32_step(&num);
		return num;
	});

}

void TestRandomNumberDemo()
{
	Demo001();
}