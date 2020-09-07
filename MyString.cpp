#include "MyString.h"


int main(int argc, char* argv[]) {
	char a[]{ "Hello World" };
	char b[15]{ "accnfgcc" };
	String val(a);
	cout << val.getStr() << "\nlen: " << val.Length() << endl;
	String s(b);
	// cout << "¿ªÊ¼Æ¥ÅäÎ»ÖÃ:" << s.BF(val, s) << endl;
	cout << "\n¿½±´£º" << s.getStr() << "\nlen: " << s.Length() << "\n";
	cout << "É¾³ý£º\n";
	// s.S_erase(2, 4);
	cout << s.getStr() << endl;
	return 0;
}
