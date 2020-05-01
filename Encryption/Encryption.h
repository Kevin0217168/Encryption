#include <string>
#include <vector>

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

private:
	// ����Ħ˹������ձ�
	static const string Mosi[36];
	// Ħ˹���������תascii
	static char IndexToAbc(int i);
};

