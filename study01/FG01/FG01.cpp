// fg0.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <memory>

using namespace std;

void example1();
void example2();

int main()
{
	example1();

	return 0;
}

//���������Լ�ת����һЩ����
void example1()
{
	
	//������make_shared�����ڴ�
	typedef struct _my_int
	{
		int a[100];
	}my_int;
	auto my = std::make_shared<my_int>();
	for (int i = 0; i < 100; i++)
		my->a[i] = i + 1;
	printf("%d\r\n", my->a[7]);


	//����ָ��ʹ�� 
	std::shared_ptr<int> my2_p(new int[100]);
	for (int i = 0; i < 100; i++)
	{
		(my2_p.get())[i] = i % 2;
	}
	printf("%d\r\n", my2_p.get()[1]);

	//�ڴ浥ԪӦ���Ǳ��ˣ�����const������push��ʱ����ֱ��push 2
	//�����õ�����a�Ķ���2ֱ�Ӵ�����
	const int a = 2;
	int *b = const_cast<int *>(&a);
	*b = 100;
	int c = a + 2;
	printf("a=%d,b=%d\r\n", a, *b);

	//������������ת��
	float floatValue = 21.7;
	int intValue = 7;
	cout << static_cast<int>(floatValue) / 7 << endl;
	cout << static_cast<double>(intValue) / 3 << endl;

	//�κ�ָ��ת�������͵ĵ�ֵַ
	int ii;
	char *p = "this is a example";
	ii = reinterpret_cast<int>(p);//ָ���ַ
	cout << hex << ii << endl;
}

void example2()
{

}