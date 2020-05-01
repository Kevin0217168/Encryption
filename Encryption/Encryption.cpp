#include "Encryption.h"

#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))

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

// 初始化九键对应表
const char Encryption::Jiujian[9][4] = {{'A', 'B', 'C', '#'}, 
                                        {'D', 'E', 'F', '#'},
                                        {'G', 'H', 'I', '#'},
                                        {'J', 'K', 'L', '#'},
                                        {'M', 'N', 'O', '#'},
                                        {'P', 'O', 'R', 'S'},
                                        {'T', 'U', 'V', '#'},
                                        {'W', 'X', 'Y', 'Z'}};

// 初始化26键对应字母表
const char Encryption::Jian26[26] = { 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
                                      'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
                                      'Z', 'X', 'C', 'V', 'B', 'N', 'M',};

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
            *result += Mosi[*it - 23];
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
int Encryption::EnKaisa(string *str, int index, string *result)
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
int Encryption::DeKaisa(string* str, int index, string* result)
{
    // 输入检查
    if (index > 0 && index < 26) {
        // 偷懒，嘿嘿，其实实现方式是一样的
        int ret = EnKaisa(str, 26, result);
        if (ret == ERROR) {
            return ret;
        }
        EnKaisa(str, index, result);
    }
    else {
        // 偏移不符合标准，错误
        return ERROR;
    }
    return 0;
}

/*
栅栏加密程序
参数：str:要加密的明文(仅限字母、数字)(支持大小写)
result: 密文
返回：int: 错误码(0:成功, 1[ERROR]:失败)
时间复杂度: O(n/2)
*/
int Encryption::EnShanlan(string* str, string* result)
{
    result->clear();
    // 奇数加
    for (string::iterator it = str->begin(); it < str->end(); ++it) {
        // 判断是否是字母或数字
        if (*it > 64 && *it < 91 || *it > 96 && *it < 123 || *it > 47 && *it < 58) {
            *result += *it;
        }
        else {
            return ERROR;
        }
        if (it + 1 >= str->end()) {
            break;
        }
        else {
            it += 1;
        }
    }
    // 偶数加
    for (string::iterator it = str->begin()+1; it < str->end(); ++it) {
        // 判断是否是字母或数字
        if (*it > 64 && *it < 91 || *it > 96 && *it < 123 || *it > 47 && *it < 58) {
            *result += *it;
        }
        else {
            return ERROR;
        }
        if (it + 1 >= str->end()) {
            break;
        }
        else {
            it += 1;
        }
    }
    return 0;
}

/*
栅栏解密程序
参数：str:要解密的密文(仅限字母、数字)(支持大小写)
result: 明文
返回：int: 错误码(0:成功, 1[ERROR]:失败)
时间复杂度: O(n/2)
*/
int Encryption::DeShanlan(string* str, string* result)
{
    result->clear();

    // 将密文从中间截开
    int middle = str->size() / 2;
    if (str->size() % 2 != 0) {
        middle += 1;
    }
    int a_index = 0;
    int b_index = middle;

    // 从两个列表中依次取出数据
    while (b_index < str->size()) {
        *result += str->at(a_index);
        a_index++;
        *result += str->at(b_index);
        b_index++;
    }
    // 数据为奇数时，需要将最后一个数据输出
    if (str->size() % 2 != 0) {
        *result += str->at(a_index);
    }
    return 0;
}


/*
九键字母转数字加密程序
参数：str:要加密的明文(仅限大写字母)
result: 密文
返回：int: 错误码(0:成功, 1[ERROR]:失败)
时间复杂度: O(n/2)
*/
int Encryption::EnJiujian(string* str, string* result)
{
    result->clear();

    bool mark = false;
    // 偶数加
    for (string::iterator it = str->begin(); it < str->end(); ++it) {
        // 判断是否是大写字母
        if (*it > 64 && *it < 91) {
            mark = false;
            for (int y = 0; y < 9; y++) {
                for (int x = 0; x < LEN(Jiujian[y]); x++) {
                    if (Jiujian[y][x] == *it) {
                        char str[2];
                        _itoa_s(y+2, str, 10);
                        *result += str;
                        _itoa_s(x+1, str, 10);
                        *result += str;
                        mark = true;
                    }
                }
            }
            if (!mark) {
                return ERROR;
            }
        }
        else {
            return ERROR;
        }
    }
    return 0;
}


/*
九键数字转字母程序
参数：str:要解密的密文(仅限数字字符串)
result: 密文
返回：int: 错误码(0:成功, 1[ERROR]:失败)
时间复杂度: O(n/2)
*/
int Encryption::DeJiujian(string* str, string* result)
{
    result->clear();

    // 奇数检查，为奇数时抛出错误
    if (str->size() % 2 == 1) {
        return ERROR;
    }

    // 奇数走
    for (string::iterator it = str->begin(); it < str->end(); it += 2) {
        // 判断是否是数字
        if (*it > 47 && *it < 58) {
            // 判断索引是否正确
            // ascii转数字
            int a_index = *it - 48 - 2;
            int b_index = *(it + 1) - 48 - 1;
            if (a_index >= 0 && b_index < 4) {
                char ch = Jiujian[a_index][b_index];
                if (ch != '#') {
                    *result += ch;
                }
                else {
                    // 索引超限，错误
                    return ERROR;
                }
            }
            else {
                // 数字索引不正确
                return ERROR;
            }
        }
        else {
            // 其他字符，错误
            return ERROR;
        }
    }
    return 0;
}

