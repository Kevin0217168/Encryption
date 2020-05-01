#include "Encryption.h"

// 初始化摩斯电码对照表
const string Encryption::Mosi[36] = { ".-", "-...", "-.-.", "-..", ".",            // A B C D E
    "..-.", "--.", "....", "..", ".---",         // F G H I J
    "-.-", ".-..", "--", "-.", "---",            // K L M N O
    ".--.", "--.-", ".-.", "...", "-",           // P Q R S T
    "..-", "...-", ".--", "-..-", "-.--",        // U V W X Y
    "--..",                                      // Z
    ".----", "..---", "...--", "....-", ".....", // 1 2 3 4 5
    "-....", "--...", "---..", "----.", "-----", // 6 7 8 9 0 
};

Encryption::Encryption()
{
	
}

/* 
摩斯电码加密函数
参数: str: 要加密的明文
result: 密文
返回：int: 错误码(0:成功，1[ERROR]:失败)
时间复杂度: O(n)
*/
int Encryption::EnMosi(string* str, string* result)
{
    result->clear();
    for (string::iterator it = str->begin(); it < str->end(); ++it) {
        // 数字'0'
        if (*it == '0') {
            *result += Mosi[35];
        }
        // 字母部分
        else if (*it > 64 && *it < 91) {
            *result += Mosi[*it - 65];
            
        }
        // 1~9数字部分
        else if (*it > 47 && *it < 58){
            *result += Mosi[*it + 36 - 49];
        }
        // 不属于以上的任何部分，输入错误，返回错误码
        else {
            return ERROR;
        }
        // 加入分隔符
        *result += ' ';
    }
    // 程序返回
    return 0;
}

// 摩斯电码表索引转ascii
char Encryption::IndexToAbc(int i) {
    if (i < 26) {
        return (char)(i + 65);
    }
    else if (i == 35) {
        return '0';
    }
    else {
        return (char)(i + 49 - 26);
    }
}

/*
摩斯电码解密函数
参数：str: 密文(由点和划组成'.- -...')
result: 明文(大写字母及数字，用空格间隔)
返回：int: 错误码(0:成功, 1[ERROR]:失败)
时间复杂度: O(n)
*/
int Encryption::DeMosi(string* str, string* result)
{
    result->clear();
    string word;
    for (string::iterator it = str->begin(); it < str->end(); ++it) {
        // 判断是否为一个单词
        if (*it == 32) {
            // 暴力搜索密码表
            int i = 0;
            while (true){
                if (Mosi[i] == word) {
                    // 将字母存入
                    *result += IndexToAbc(i);
                    // 退出循环
                    break;
                }
                // 索引后移
                if (i < 36) {
                    i++;
                }
                else {
                    // 如果检查到最后仍未结果，则返回错误
                    return ERROR;
                }
            }
            // 清空缓冲词
            word.clear();
        }
        else {
            word += *it;
        }
    }
    return 0;
}

/*
凯撒加密程序
参数：str:要加密的明文(仅限字母、数字及空格)(支持大小写)(空格将保留)
index: 移位个数(25 > index > 0)
result: 密文
返回：int: 错误码(0:成功, 1[ERROR]:失败)
时间复杂度: O(n)
*/
int Encryption::Enkaisa(string *str, int index, string *result)
{
    if (index > 0 && index < 26) {
        result->clear();
        for (string::iterator it = str->begin(); it < str->end(); ++it) {
            // 判断是否是字母或数字
            if (*it > 64 && *it < 91 || *it > 96 && *it < 123 || *it > 47 && *it < 58) {
                // 偏移
                char ch = *it + index;
                // 是否超限
                if (ch > 90 || ch > 122) {
                    // 回到第一位
                    ch -= 26;
                }
                else if (ch > 57 && ch < 67) {
                    ch -= 10;
                }
                *result += ch;
            }
            else {
                // 检查是否为空格
                if (*it == 32) {
                    // 忽略
                    *result += *it;
                }
                else {
                    // 非法字符，错误
                    return ERROR;
                }
                
            }
        }
    }
    else {
        // 偏移不符合标准，错误
        return ERROR;
    }
    return 0;
}

/*
凯撒解密函数
参数：str:要解密的密文(仅限字母、数字及空格)(支持大小写)(空格将保留)
index: 反向移位个数(25 > index > 0)
result: 明文
返回：int: 错误码(0:成功, 1[ERROR]:失败)
时间复杂度: O(n)
*/
int Encryption::Dekaisa(string* str, int index, string* result)
{
    // 输入检查
    if (index > 0 && index < 26) {
        // 偷懒，嘿嘿，其实实现方式是一样的
        int ret = Enkaisa(str, 26, result);
        if (ret == ERROR) {
            return ret;
        }
        Enkaisa(str, index, result);
    }
    else {
        // 偏移不符合标准，错误
        return ERROR;
    }
    return 0;
}