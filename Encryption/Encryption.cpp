#include "Encryption.h"

#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))

// ��ʼ��Ħ˹������ձ�
const string Encryption::Mosi[36] = { ".-", "-...", "-.-.", "-..", ".",            // A B C D E
    "..-.", "--.", "....", "..", ".---",         // F G H I J
    "-.-", ".-..", "--", "-.", "---",            // K L M N O
    ".--.", "--.-", ".-.", "...", "-",           // P Q R S T
    "..-", "...-", ".--", "-..-", "-.--",        // U V W X Y
    "--..",                                      // Z
    ".----", "..---", "...--", "....-", ".....", // 1 2 3 4 5
    "-....", "--...", "---..", "----.", "-----", // 6 7 8 9 0 
};

// ��ʼ���ż���Ӧ��
const char Encryption::Jiujian[9][4] = {{'A', 'B', 'C', '#'}, 
                                        {'D', 'E', 'F', '#'},
                                        {'G', 'H', 'I', '#'},
                                        {'J', 'K', 'L', '#'},
                                        {'M', 'N', 'O', '#'},
                                        {'P', 'O', 'R', 'S'},
                                        {'T', 'U', 'V', '#'},
                                        {'W', 'X', 'Y', 'Z'}};

// ��ʼ��26����Ӧ��ĸ��
const char Encryption::Jian26[26] = { 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
                                      'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
                                      'Z', 'X', 'C', 'V', 'B', 'N', 'M',};

Encryption::Encryption()
{
	
}

/* 
Ħ˹������ܺ���
����: str: Ҫ���ܵ�����
result: ����
���أ�int: ������(0:�ɹ���1[ERROR]:ʧ��)
ʱ�临�Ӷ�: O(n)
*/
int Encryption::EnMosi(string* str, string* result)
{
    result->clear();
    for (string::iterator it = str->begin(); it < str->end(); ++it) {
        // ����'0'
        if (*it == '0') {
            *result += Mosi[35];
        }
        // ��ĸ����
        else if (*it > 64 && *it < 91) {
            *result += Mosi[*it - 65];
            
        }
        // 1~9���ֲ���
        else if (*it > 47 && *it < 58){
            *result += Mosi[*it - 23];
        }
        // ���������ϵ��κβ��֣�������󣬷��ش�����
        else {
            return ERROR;
        }
        // ����ָ���
        *result += ' ';
    }
    // ���򷵻�
    return 0;
}

// Ħ˹���������תascii
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
Ħ˹������ܺ���
������str: ����(�ɵ�ͻ����'.- -...')
result: ����(��д��ĸ�����֣��ÿո���)
���أ�int: ������(0:�ɹ�, 1[ERROR]:ʧ��)
ʱ�临�Ӷ�: O(n)
*/
int Encryption::DeMosi(string* str, string* result)
{
    result->clear();
    string word;
    for (string::iterator it = str->begin(); it < str->end(); ++it) {
        // �ж��Ƿ�Ϊһ������
        if (*it == 32) {
            // �������������
            int i = 0;
            while (true){
                if (Mosi[i] == word) {
                    // ����ĸ����
                    *result += IndexToAbc(i);
                    // �˳�ѭ��
                    break;
                }
                // ��������
                if (i < 36) {
                    i++;
                }
                else {
                    // �����鵽�����δ������򷵻ش���
                    return ERROR;
                }
            }
            // ��ջ����
            word.clear();
        }
        else {
            word += *it;
        }
    }
    return 0;
}

/*
�������ܳ���
������str:Ҫ���ܵ�����(������ĸ�����ּ��ո�)(֧�ִ�Сд)(�ո񽫱���)
index: ��λ����(25 > index > 0)
result: ����
���أ�int: ������(0:�ɹ�, 1[ERROR]:ʧ��)
ʱ�临�Ӷ�: O(n)
*/
int Encryption::EnKaisa(string *str, int index, string *result)
{
    if (index > 0 && index < 26) {
        result->clear();
        for (string::iterator it = str->begin(); it < str->end(); ++it) {
            // �ж��Ƿ�����ĸ������
            if (*it > 64 && *it < 91 || *it > 96 && *it < 123 || *it > 47 && *it < 58) {
                // ƫ��
                char ch = *it + index;
                // �Ƿ���
                if (ch > 90 || ch > 122) {
                    // �ص���һλ
                    ch -= 26;
                }
                else if (ch > 57 && ch < 67) {
                    ch -= 10;
                }
                *result += ch;
            }
            else {
                // ����Ƿ�Ϊ�ո�
                if (*it == 32) {
                    // ����
                    *result += *it;
                }
                else {
                    // �Ƿ��ַ�������
                    return ERROR;
                }
                
            }
        }
    }
    else {
        // ƫ�Ʋ����ϱ�׼������
        return ERROR;
    }
    return 0;
}

/*
�������ܺ���
������str:Ҫ���ܵ�����(������ĸ�����ּ��ո�)(֧�ִ�Сд)(�ո񽫱���)
index: ������λ����(25 > index > 0)
result: ����
���أ�int: ������(0:�ɹ�, 1[ERROR]:ʧ��)
ʱ�临�Ӷ�: O(n)
*/
int Encryption::DeKaisa(string* str, int index, string* result)
{
    // ������
    if (index > 0 && index < 26) {
        // ͵�����ٺ٣���ʵʵ�ַ�ʽ��һ����
        int ret = EnKaisa(str, 26, result);
        if (ret == ERROR) {
            return ret;
        }
        EnKaisa(str, index, result);
    }
    else {
        // ƫ�Ʋ����ϱ�׼������
        return ERROR;
    }
    return 0;
}

/*
դ�����ܳ���
������str:Ҫ���ܵ�����(������ĸ������)(֧�ִ�Сд)
result: ����
���أ�int: ������(0:�ɹ�, 1[ERROR]:ʧ��)
ʱ�临�Ӷ�: O(n/2)
*/
int Encryption::EnShanlan(string* str, string* result)
{
    result->clear();
    // ������
    for (string::iterator it = str->begin(); it < str->end(); ++it) {
        // �ж��Ƿ�����ĸ������
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
    // ż����
    for (string::iterator it = str->begin()+1; it < str->end(); ++it) {
        // �ж��Ƿ�����ĸ������
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
դ�����ܳ���
������str:Ҫ���ܵ�����(������ĸ������)(֧�ִ�Сд)
result: ����
���أ�int: ������(0:�ɹ�, 1[ERROR]:ʧ��)
ʱ�临�Ӷ�: O(n/2)
*/
int Encryption::DeShanlan(string* str, string* result)
{
    result->clear();

    // �����Ĵ��м�ؿ�
    int middle = str->size() / 2;
    if (str->size() % 2 != 0) {
        middle += 1;
    }
    int a_index = 0;
    int b_index = middle;

    // �������б�������ȡ������
    while (b_index < str->size()) {
        *result += str->at(a_index);
        a_index++;
        *result += str->at(b_index);
        b_index++;
    }
    // ����Ϊ����ʱ����Ҫ�����һ���������
    if (str->size() % 2 != 0) {
        *result += str->at(a_index);
    }
    return 0;
}


/*
�ż���ĸת���ּ��ܳ���
������str:Ҫ���ܵ�����(���޴�д��ĸ)
result: ����
���أ�int: ������(0:�ɹ�, 1[ERROR]:ʧ��)
ʱ�临�Ӷ�: O(n/2)
*/
int Encryption::EnJiujian(string* str, string* result)
{
    result->clear();

    bool mark = false;
    // ż����
    for (string::iterator it = str->begin(); it < str->end(); ++it) {
        // �ж��Ƿ��Ǵ�д��ĸ
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
�ż�����ת��ĸ����
������str:Ҫ���ܵ�����(���������ַ���)
result: ����
���أ�int: ������(0:�ɹ�, 1[ERROR]:ʧ��)
ʱ�临�Ӷ�: O(n/2)
*/
int Encryption::DeJiujian(string* str, string* result)
{
    result->clear();

    // ������飬Ϊ����ʱ�׳�����
    if (str->size() % 2 == 1) {
        return ERROR;
    }

    // ������
    for (string::iterator it = str->begin(); it < str->end(); it += 2) {
        // �ж��Ƿ�������
        if (*it > 47 && *it < 58) {
            // �ж������Ƿ���ȷ
            // asciiת����
            int a_index = *it - 48 - 2;
            int b_index = *(it + 1) - 48 - 1;
            if (a_index >= 0 && b_index < 4) {
                char ch = Jiujian[a_index][b_index];
                if (ch != '#') {
                    *result += ch;
                }
                else {
                    // �������ޣ�����
                    return ERROR;
                }
            }
            else {
                // ������������ȷ
                return ERROR;
            }
        }
        else {
            // �����ַ�������
            return ERROR;
        }
    }
    return 0;
}

