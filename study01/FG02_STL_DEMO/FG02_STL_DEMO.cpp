/**************************************************************************
Author: FrogGod
Date:2017-05-26
Description:STL�ĺ����Ĳ���
**************************************************************************/

#include "stdafx.h"
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

class Person
{
public:
	Person(){}
	Person(int num) :m_nNum(num){}
	int m_nNum;
public:
	//����������
	bool operator ==(int num);
private:
	
};

void ForEachDemo();
void ForEachFun1(Person &p);
void FindDemo();
void FindIfDemo();

vector<Person> g_vecPer;
void initData()
{
	//��ȫ�ֱ���vector��Ԫ�أ���ʵ�Ǹ���һ����ȥ
	Person p1(123);
	Person p2(10);
	Person p21(10);
	Person p22(10);
	Person p3(200);
	Person p4(1987);
	Person p5(999);
	g_vecPer.push_back(p1);
	g_vecPer.push_back(p2);
	g_vecPer.push_back(p21);
	g_vecPer.push_back(p22);
	g_vecPer.push_back(p3);
	g_vecPer.push_back(p4);
	g_vecPer.push_back(p5);
	
}

int main()
{
	initData();
	ForEachDemo();
	FindDemo();
	//FindIfDemo();
	
    return 0;
}

/************************************************************************/
/*            ����for_eachDemo                                         */
void ForEachDemo()
{
	for_each(g_vecPer.begin(), g_vecPer.end(), ForEachFun1);
}
void ForEachFun1(Person &p)
{
	//������һЩ�ı����ݵĲ���
	//p.m_nNum += 10000;
	cout << p.m_nNum << endl;
}
/************************************************************************/


/************************************************************************/
/*                    ����findDemo                                   */
void FindDemo()
{
	vector<Person>::iterator it = find(g_vecPer.begin(), g_vecPer.end(), 10);
	if (it == g_vecPer.end())
	{
		cout << "û�ҵ�" << endl;
		return;
	}
	g_vecPer.erase(it);
}
bool Person::operator==(int num)
{
	if (m_nNum != num)
		return false;
	return true;
}
/************************************************************************/


/************************************************************************/
/*                   ����find_ifDemo                                  */
bool FindIfFun(Person& p)
{
	return p.m_nNum == 10 ? true : false;
}
void FindIfDemo()
{
	for (auto it = g_vecPer.begin(); it != g_vecPer.end(); it++)
	{
		it = find_if(it, g_vecPer.end(), FindIfFun);
		if (it == g_vecPer.end())break;
		cout << it->m_nNum << endl;
	}
}
/************************************************************************/

/************************************************************************/
/*                                                                      */




/************************************************************************/










