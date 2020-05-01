#include "Encryption.h"

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
            *result += Mosi[*it + 36 - 49];
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
int Encryption::Enkaisa(string *str, int index, string *result)
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
int Encryption::Dekaisa(string* str, int index, string* result)
{
    // ������
    if (index > 0 && index < 26) {
        // ͵�����ٺ٣���ʵʵ�ַ�ʽ��һ����
        int ret = Enkaisa(str, 26, result);
        if (ret == ERROR) {
            return ret;
        }
        Enkaisa(str, index, result);
    }
    else {
        // ƫ�Ʋ����ϱ�׼������
        return ERROR;
    }
    return 0;
}