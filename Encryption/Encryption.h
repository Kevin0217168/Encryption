#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

#pragma once
class Encryption
{
public:
	Encryption();

	// 定义错误码
	static const int ERROR = 1;

	// 摩斯加密
	static int EnMosi(string *str, string *result);
	// 摩斯解密
	static int DeMosi(string *str, string *result);

	// 凯撒加密
	static int EnKaisa(string *str, int index, string *result);
	// 凯撒解密
	static int DeKaisa(string *str, int index, string *result);

	// 栅栏加密
	static int EnShanlan(string* str, string* result);
	// 栅栏解密
	static int DeShanlan(string* str, string* result);

	// 九键字母转数字加密
	static int EnJiujian(string* str, string* result);
	// 九键数字转字母解密
	static int DeJiujian(string* str, string* result);

	// 26键字母键盘加密
	static int EnJian26(string* str, string* result);
	// 26键字母键盘解密
	static int DeJian26(string* str, string* result);


private:
	// 定义摩斯电码对照表
	static const string Mosi[36];
	// 摩斯电码表索引转ascii
	static char IndexToAbc(int i);
	// 九键对应字母表
	static const char Jiujian[9][4];
	// 26键对应字母表
	static const char Jian26[26];
};