#include <iostream>
#include <string>
#include "Encryption.h"

using namespace std;

int main(void) {
	string str = "KEVIN";
	cout << "ԭ�ģ�" << str << endl;

	string result;
	// ���þ�̬��������ΪĦ˹����
	Encryption::EnMosi(&str, &result);
	cout << "Ħ˹������ܣ�" << result << endl;
	// ���þ�̬����Ħ˹�������
	string re1;
	Encryption::DeMosi(&result, &re1);
	cout << "Ħ˹������ܣ�" << re1 << endl << endl;

	// �����������
	Encryption::EnKaisa(&str, 5, &result);
	cout << "�����������(ƫ��5λ)��" << result << endl;
	// �����������
	Encryption::DeKaisa(&result, 5, &re1);
	cout << "�����������(ƫ��5λ)��" << re1 << endl << endl;

	// դ���������
	Encryption::EnShanlan(&str, &result);
	cout << "դ��������ܣ�" << result << endl;
	// դ���������
	Encryption::DeShanlan(&result, &re1);
	cout << "դ��������ܣ�" << re1 << endl << endl;

	// �ż���ĸת���ּ���
	Encryption::EnJiujian(&str, &result);
	cout << "�ż���ĸת���ּ��ܣ�" << result << endl;
	// �ż�����ת��ĸ����
	Encryption::DeJiujian(&result, &re1);
	cout << "�ż�����ת��ĸ���ܣ�" << re1 << endl << endl;

	// 26����ĸ���̼���
	Encryption::EnJian26(&str, &result);
	cout << "26����ĸ���̼��ܣ�" << result << endl;
	// 26����ĸ���̽���
	Encryption::DeJian26(&result, &re1);
	cout << "26����ĸ���̽��ܣ�" << re1 << endl << endl;

	return 0;
}