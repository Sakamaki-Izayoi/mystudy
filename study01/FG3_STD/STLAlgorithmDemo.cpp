#include "stdafx.h"
#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <vector>


void Demo01()
{
	char letter = 'A';
	std::vector<char> chars(10);
	std::ostream_iterator<char> output(std::cout, ",");
	
	fill(chars.begin(), chars.end(), '5');
	std::cout << "chars after filling with 5s:\n";
	copy(chars.cbegin(), chars.cend(), output);

	fill_n(chars.begin(), 5, 'A');
	std::cout << "\n\nchars after filling five elements with As:\n";
	copy(chars.begin(), chars.end(), output);

	generate(chars.begin(), chars.end(), [&]() {
		return letter++;
	});
	std::cout << "\n\nchars after generating letters A-J:\n";
	copy(chars.begin(), chars.end(), output);

	generate_n(chars.begin(), 5, [&]() {
		return letter++;
	});
	std::cout << "\n\nchars after generating K-O for the first five elements\n";
	copy(chars.cbegin(), chars.cend(), output);
	std::cout << std::endl;
}
void Demo02()
{
	const size_t SIZE = 10;
	std::vector<int> v1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> v2(v1);
	std::vector<int> v3{ 1, 2, 3, 4, 1000, 6, 7, 8, 9, 10 };
	std::ostream_iterator<int> output(std::cout, ", ");

	std::cout << "v1 contains:";
	copy(v1.cbegin(), v1.cend(), output);
	std::cout << "\nv2 contains:";
	copy(v2.cbegin(), v2.cend(), output);
	std::cout << "\nv3 contains:";
	copy(v3.cbegin(), v3.cend(), output);
	std::cout << std::endl;

	auto result = std::equal(v1.cbegin(), v1.cend(), v2.cbegin());
	std::cout << "a1 " << (result ? "is" : "is not") << " equal a2.\n";
	result = std::equal(v1.cbegin(), v1.cend(), v3.cbegin());
	std::cout << "a1 " << (result ? "is" : "is not") << " equal a3.\n";

	auto location = mismatch(v1.cbegin(), v1.cend(), v3.begin());
	std::cout << "a1��a3�ڵ�" << (location.first - v1.begin()) << "λ��һ��\n";
	std::cout << "a1��Ϊ" << *location.first << ", a3��Ϊ" << *location.second;

	char str1[10] = "HELLO";
	char str2[10] = "BYE BYE";
	result = std::lexicographical_compare(std::begin(str1), std::end(str1), std::begin(str2), std::end(str2));
	//ֻҪst1 < str2�򷵻�true, str1>=str2�򷵻�false

}
void Demo03()
{
	std::vector<int> init{ 10, 2, 10, 4, 16, 6, 14, 8, 12, 10 };
	std::ostream_iterator<int> output(std::cout, ",");

	//remove
	std::vector<int> v1(init);
	std::cout << "��ʼv1Ϊ:\n";
	copy(v1.begin(), v1.end(), output);

	//�Ƴ����е�10
	auto newLastElement = remove(v1.begin(), v1.end(), 10);
	std::cout << "\n�Ƴ�10֮��Ϊ��\n";
	copy(v1.begin(), newLastElement, output);//������cbegin
	//////////////////////////////////////////////////////////////////////////

	//remove_copy
	std::vector<int> v2(init);
	std::vector<int> v3(10);
	std::cout << "\n\n��ʼv2Ϊ:\n";
	copy(v2.begin(), v2.end(), output);

	//����v2��v3���в�����10��ֵ
	newLastElement = remove_copy(v2.cbegin(), v2.cend(), v3.begin(), 10);
	std::cout << "\nv3��ֵΪ:\n";
	copy(v3.begin(), newLastElement, output);
	//////////////////////////////////////////////////////////////////////////

	//remove_if
	std::vector<int> v4(init);
	std::cout << "\n\n��ʼv4Ϊ:\n";
	copy(v4.begin(), v4.end(), output);

	//�Ƴ�����if��
	std::cout << "\n�Ƴ�v4�д���9�����֣�\n";
	newLastElement = std::remove_if(v4.begin(), v4.end(), [](int x) {
		return x > 9;
	});
	copy(v4.begin(), newLastElement, output);//������cbegin
	//////////////////////////////////////////////////////////////////////////

	//remove_copy_if
	std::vector<int> v5(init);
	std::vector<int> v6(10);
	std::cout << "\n\n��ʼv5Ϊ:\n";
	copy(v5.begin(), v5.end(), output);
	newLastElement = remove_copy_if(v5.cbegin(), v5.cend(), v6.begin(), [=](int x) {
		return x > 9;
	});
	std::cout << "\nʹ��remove_copy_if��v6Ϊ:\n";
	copy(v6.begin(), newLastElement, output);
	std::cout << std::endl;
}
void TestAlgorithmDemo()
{
	//fill,fill_n,generate,generate_n
	//Demo01();

	//equal, mismatch, lexicographical_compare
	//Demo02();

	//remove��remove_if��remove_copy��remove_copy_if
	Demo03();
}