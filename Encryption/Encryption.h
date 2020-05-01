#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

#pragma once
class Encryption
{
public:
	Encryption();

	// ���������
	static const int ERROR = 1;

	// Ħ˹����
	static int EnMosi(string *str, string *result);
	// Ħ˹����
	static int DeMosi(string *str, string *result);

	// ��������
	static int EnKaisa(string *str, int index, string *result);
	// ��������
	static int DeKaisa(string *str, int index, string *result);

	// դ������
	static int EnShanlan(string* str, string* result);
	// դ������
	static int DeShanlan(string* str, string* result);

	// �ż���ĸת���ּ���
	static int EnJiujian(string* str, string* result);
	// �ż�����ת��ĸ����
	static int DeJiujian(string* str, string* result);

	// 26����ĸ���̼���
	static int EnJian26(string* str, string* result);
	// 26����ĸ���̽���
	static int DeJian26(string* str, string* result);


private:
	// ����Ħ˹������ձ�
	static const string Mosi[36];
	// Ħ˹���������תascii
	static char IndexToAbc(int i);
	// �ż���Ӧ��ĸ��
	static const char Jiujian[9][4];
	// 26����Ӧ��ĸ��
	static const char Jian26[26];
};