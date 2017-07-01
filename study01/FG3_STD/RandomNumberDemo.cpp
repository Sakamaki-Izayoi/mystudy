#include "stdafx.h"
#include <windows.h>

void Demo001()
{
	//32λ���޷��ţ�������
	std::vector<UINT> vec1;
	std::generate_n(std::back_inserter(vec1), 100, [=]() {
		UINT num = 0;
		_rdrand32_step(&num);
		return num;
	});

	std::ostream_iterator<UINT> output1(std::cout, " ");
	std::copy(vec1.cbegin(), vec1.cend(), output1);
	std::cout << std::endl;


	//64λ���з��ţ������
	std::vector<LONGLONG> vec2;
	std::generate_n(std::back_inserter(vec2), 100, [=]() {
		ULONGLONG num = 0;
		_rdrand64_step(&num);
		return (LONGLONG)num;
	});

	std::ostream_iterator<LONGLONG> output2(std::cout, " ");
	std::copy(vec2.cbegin(), vec2.cend(), output2);
	std::cout << std::endl;
	getchar();
}
void Demo002()
{
	std::vector<int> vec;
	auto HasSame = [=](int x) {
		auto location = std::find(vec.cbegin(), vec.cend(), x);
		return location != vec.cend() ? TRUE: FALSE;
	};

	auto GenRand = [=]() {
		int num = 0;
		UINT temp = 0;
		while (true)
		{
			_rdrand32_step(&temp);
			num = (int)temp;
			if (!HasSame(num))
			{
				break;
			}
		}
		return num;
	};
	std::generate_n(std::back_inserter(vec), 100, GenRand);
	std::sort(vec.begin(), vec.end());

	for (auto i = 0; i < 100; i++)
	{
		printf("%d %d\n", i, vec[i]);
	}
}

//���������Demo
void TestRandomNumberDemo()
{
	//����N�������
	//Demo001();

	//����N�����ظ��������
	//Demo002();
}