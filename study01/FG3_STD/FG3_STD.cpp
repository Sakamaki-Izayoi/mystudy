// FG3_STD.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
extern void TestIteratordemo();
extern void TestAlgorithmDemo();
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
	//�ļ���
	//TestGenerate_n();

	//�����ļ���
	TestIteratordemo();
	TestAlgorithmDemo();
	return 0;
}

