#include "stdafx.h"
#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <numeric>
#include <ctime>


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
void Demo04()
{
	std::vector<int> init{ 10, 2, 10, 4, 16, 6, 14, 8, 12, 10 };
	std::ostream_iterator<int> output(std::cout, " ");

	//replace
	std::vector<int> vec1(init);
	std::cout << "vec1��ʼ��\n";
	std::copy(vec1.begin(), vec1.end(), output);

	replace(vec1.begin(), vec1.end(), 10, 100);
	std::cout << "\n����relplace֮��\n";
	std::copy(vec1.begin(), vec1.end(), output);
	std::cout << "\n###################################\n\n";
	//////////////////////////////////////////////////////////////////////////

	//relace_copy
	std::vector<int> vec2(init);
	std::vector<int> cp2(10);
	std::cout << "vec2��ʼ��\n";
	std::copy(vec2.begin(), vec2.end(), output);

	replace_copy(vec2.cbegin(), vec2.cend(), cp2.begin(), 10, 100);
	std::cout << "\n����relplace_copy֮��";
	std::cout << "\nvec2����Ϊ:\n";
	std::copy(vec2.begin(), vec2.end(), output);
	std::cout << "\ncp2����Ϊ:\n";
	std::copy(cp2.begin(), cp2.end(), output);
	std::cout << "\n###################################\n\n";
	//////////////////////////////////////////////////////////////////////////

	//replace_if
	std::vector<int> vec3(init);
	std::cout << "vec3��ʼ��\n";
	std::copy(vec3.begin(), vec3.end(), output);
	
	replace_if(vec3.begin(), vec3.end(), [&](int x) {
		return x > 9;
	}, 100);
	std::cout << "\n����relplace_if(�滻����9������)֮��";
	std::cout << "\nvec3����Ϊ��\n";
	std::copy(vec3.begin(), vec3.end(), output);
	std::cout << "\n###################################\n\n";
	//////////////////////////////////////////////////////////////////////////

	//replace_copy_if
	std::vector<int> vec4(init);
	std::vector<int> cp4(10);
	std::cout << "vec4��ʼ��\n";
	std::copy(vec4.begin(), vec4.end(), output);

	replace_copy_if(vec4.cbegin(), vec4.cend(), cp4.begin(), [&](int x) {
		return x > 9;
	}, 100);
	std::cout << "\n����relplace_copy_if֮��";
	std::cout << "\nvec4����Ϊ:\n";
	std::copy(vec4.begin(), vec4.end(), output);
	std::cout << "\ncp4����Ϊ:\n";
	std::copy(cp4.begin(), cp4.end(), output);
	std::cout << std::endl;
}
void Demo05()
{
	std::ostream_iterator<int> output(std::cout, " ");
	std::vector<int> vec1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> vec2{ 100, 2, 8, 1, 50, 3, 8, 8, 9, 10 };

	//random_shuffle
	std::cout << "����random_shuffle֮ǰ��\n";
	copy(vec1.cbegin(), vec1.cend(), output);
	random_shuffle(vec1.begin(), vec1.end());
	std::cout << "\n����random_shuffle֮��\n";
	copy(vec1.cbegin(), vec1.cend(), output);
	std::cout << "\n#############################\n\n";

	//count�� count_if
	std::cout << "vec2Ԫ��Ϊ����\n";
	std::copy(vec2.begin(), vec2.end(), output);
	
	auto result = std::count(vec2.cbegin(), vec2.cend(), 8);
	std::cout << "\nʹ�ü���vec2��8�ĸ�����" << result;

	result = std::count_if(vec2.cbegin(), vec2.cend(), [=](int x) {
		return x > 9;
	});
	std::cout << "\nʹ�ü���vect�д���9�ĸ�����" << result;
	std::cout << "\n#############################\n\n";

	//min_element
	std::cout << "vec2����СֵΪ:" << *std::min_element(vec2.cbegin(), vec2.cend());
	//max_element
	std::cout << "\nvec2�����ֵΪ" <<* std::max_element(vec2.cbegin(), vec2.cend());
	//minmax_element
	auto minAndMax = minmax_element(vec2.cbegin(), vec2.cend());
	std::cout << "\nһ���������ֵ��������СֵΪ:" << *minAndMax.first << "  ���ֵΪ:" << *minAndMax.second;
	std::cout << "\n#############################\n\n";

	//accumulate,����������Ϊ��ʼֵ
	std::cout << "vec1��Ϊ��" << std::accumulate(vec1.cbegin(), vec1.cend(), 10);
	std::cout << "\nvec2��Ϊ��" << std::accumulate(vec2.cbegin(), vec2.cend(), 0);
	std::cout << "\n#############################\n\n";

	//for_each����
	std::cout << "��vec2��Ԫ����ƽ���������\n";
	for_each(vec2.cbegin(), vec2.cend(), [](int x) {
		std::cout << x * x << " ";
	});
	
	//transform
	//������������һ��������������������Լ�
	//���ĸ�����ʹ�õ�ǰԪ����Ϊʵ�Σ������ܸı䣬���ص��Ǳ任���ֵ
	std::vector<int> transVec;
	std::map<int, int> map1;
	auto index = 0;
	std::transform(vec1.cbegin(), vec1.cend(), std::inserter(transVec, transVec.end()), [=](int x) {
		return x * x * x;
	});
	//vectorתmap������
	std::transform(vec1.cbegin(), vec1.cend(), std::inserter(map1, map1.end()), [&](int x) {
		index += 2;
		return std::make_pair(index, x);
	});

	std::cout << "\n����transform��transVec��Ԫ��Ϊ��\n";
	copy(transVec.cbegin(), transVec.cend(), output);
}
void Demo06()
{
	std::vector<int> vec{ 10, 2, 17, 5, 16, 8, 13, 11, 20, 7 };
	std::ostream_iterator<int> output(std::cout, " ");
	std::cout << "vecԪ�����£�\n";
	std::copy(vec.cbegin(), vec.cend(), output);

	//find
	auto location = std::find(vec.cbegin(), vec.cend(), 16);
	if (location != vec.end())
		std::cout << "\n��һ��16�����������±�Ϊ��" << location - vec.cbegin() << std::endl;
	else
		std::cout << "û���ҵ�16" << std::endl;

	location = std::find(vec.cbegin(), vec.cend(), 100);
	if (location != vec.end())
		std::cout << "\n��һ��100�����������±�Ϊ��" << location - vec.cbegin() << std::endl;
	else
		std::cout << "û���ҵ�100" << std::endl;

	//find_if ��true
	location = std::find_if(vec.cbegin(), vec.cend(), [=](int x) {
		return x > 10;
	});
	if (location != vec.cend())
		std::cout << "��һ������10��������" << *location << ", �±�Ϊ" << location - vec.cbegin() << "��λ��\n";
	else
		std::cout << "û���ҵ�����10������";

	//find_if_not  ��false
	location = find_if_not(vec.cbegin(), vec.cend(), [](int x) {
		return x > 10;
	});
	if (location != vec.cend())
		std::cout << "��һ��������10������" << *location << ", λ����" << location - vec.cbegin() << std::endl;
	else
		std::cout << "�Ҳ���������10����\n";

	//sort
	//std::sort(vec.begin(), vec.end());
	std::sort(vec.begin(), vec.end(), [](int a, int b) {//a��ǰ��ģ�b�Ǻ����
		return a < b;	//С��Ϊ��������С��Ϊ���ǽ���
	});
	std::cout << "�����Ԫ�����£�\n";
	std::copy(vec.cbegin(), vec.cend(), output);

	//binary_search  �����Ҵ��ڲ������ٶ�����
	if (std::binary_search(vec.cbegin(), vec.cend(), 13))
		std::cout << "\n��13\n";
	else
		std::cout << "û��13\n";

	if (std::binary_search(vec.cbegin(), vec.cend(), 100))
		std::cout << "��100\n";
	else
		std::cout << "û��100\n";

	//all_of
	if (all_of(vec.cbegin(), vec.cend(), [&](int x) {
		return x > 10;
	}))
		std::cout << "all_of:���е�Ԫ�ض�����10\n";
	else
		std::cout << "all_of:��������Ԫ�ض�����10\n";

	//any_of
	if (any_of(vec.cbegin(), vec.cend(), [&](int x) {
		return x > 10;
	}))
		std::cout << "any_of:��ЩԪ�ش���10\n";
	else
		std::cout << "any_of:����Ԫ�ض�������10\n";

	//none_of
	if (none_of(vec.cbegin(), vec.cend(), [&](int x) {
		return x > 10;
	}))
		std::cout << "none_of:û��һ��Ԫ�ش���10\n";
	else
		std::cout << "none_of:��ЩԪ�ش���10\n";
}
void TestAlgorithmDemo()
{
	//fill,fill_n,generate,generate_n
	//Demo01();

	//equal, mismatch, lexicographical_compare
	//Demo02();

	//remove��remove_if��remove_copy��remove_copy_if
	//Demo03();

	//replace, replace_if, replace_copy, replace_copy_if
	//Demo04();

	//random_shuffle, count, count_if, min_element, max_element, 
	//minmax_element, accumulate, for_each, transform
	//Demo05();

	//find, find_if, sort, binary_search, all_of, any_of, none_of, find_if_not
	//Demo06();

	//swap, iter_swap, swap_rangs

}