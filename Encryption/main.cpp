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
	Encryption::Enkaisa(&str, 5, &result);
	cout << "�����������(ƫ��5λ)��" << result << endl;
	// �����������
	Encryption::Dekaisa(&result, 5, &re1);
	cout << "�����������(ƫ��5λ)��" << re1 << endl;


	return 0;
}