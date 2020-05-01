#include <iostream>
#include <string>
#include "Encryption.h"

using namespace std;

int main(void) {
	string str = "KEVIN";
	cout << "原文：" << str << endl;

	string result;
	// 调用静态方法加密为摩斯电码
	Encryption::EnMosi(&str, &result);
	cout << "摩斯电码加密：" << result << endl;
	// 调用静态方法摩斯电码解密
	string re1;
	Encryption::DeMosi(&result, &re1);
	cout << "摩斯电码解密：" << re1 << endl << endl;

	// 凯撒密码加密
	Encryption::Enkaisa(&str, 5, &result);
	cout << "凯撒密码加密(偏移5位)：" << result << endl;
	// 凯撒密码解密
	Encryption::Dekaisa(&result, 5, &re1);
	cout << "凯撒密码加密(偏移5位)：" << re1 << endl;


	return 0;
}