// FG3_STD.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

//
void TestGenerate_n()
{
	
	//�����������������
	auto vec = std::vector<UINT>{};
	std::generate_n(std::back_inserter(vec), 10000, [=]() {
		UINT num = 0;
		_rdrand32_step(&num);
		return num;
	});
	
}

int main()
{
	TestGenerate_n();
	return 0;
}

