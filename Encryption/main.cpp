#include <iostream>
#include <string>
#include "Encryption.h"

using namespace std;

int main(void) {
	string str = "KEVIN";
	cout << "Ô­ÎÄ£º" << str << endl;

	string result;
	// µ÷ÓÃ¾²Ì¬·½·¨¼ÓÃÜÎªÄ¦Ë¹µçÂë
	Encryption::EnMosi(&str, &result);
	cout << "Ä¦Ë¹µçÂë¼ÓÃÜ£º" << result << endl;
	// µ÷ÓÃ¾²Ì¬·½·¨Ä¦Ë¹µçÂë½âÃÜ
	string re1;
	Encryption::DeMosi(&result, &re1);
	cout << "Ä¦Ë¹µçÂë½âÃÜ£º" << re1 << endl << endl;

	// ¿­ÈöÃÜÂë¼ÓÃÜ
	Encryption::EnKaisa(&str, 5, &result);
	cout << "¿­ÈöÃÜÂë¼ÓÃÜ(Æ«ÒÆ5Î»)£º" << result << endl;
	// ¿­ÈöÃÜÂë½âÃÜ
	Encryption::DeKaisa(&result, 5, &re1);
	cout << "¿­ÈöÃÜÂë¼ÓÃÜ(Æ«ÒÆ5Î»)£º" << re1 << endl << endl;

	// Õ¤À¸ÃÜÂë¼ÓÃÜ
	Encryption::EnShanlan(&str, &result);
	cout << "Õ¤À¸ÃÜÂë¼ÓÃÜ(Æ«ÒÆ5Î»)£º" << result << endl;
	// Õ¤À¸ÃÜÂë½âÃÜ
	Encryption::DeShanlan(&result, &re1);
	cout << "Õ¤À¸ÃÜÂë¼ÓÃÜ(Æ«ÒÆ5Î»)£º" << re1 << endl;

	return 0;
}