#pragma once
#ifndef STRING_H_
#define STRING_H_
#include <cstdlib>
#include <cassert>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
template <typename Type> Type catStr(Type a, Type b);		//连接两个字符串
template <typename Type> void Swap(Type a, Type b);
template <typename Type> size_t S_size(Type rhs) noexcept;


class String {
private:
	char* buf;
	size_t len;

public:
	String();
	String(const String& rhs);								  //拷贝构造函数
	String(String& rhs, size_t n);							  //范围拷贝
	explicit String(char* str);								  //一个参数构造
	String(const char* str);								  // const char *构造
	void Swap(String&);										  //交换对象的数据
	String& operator+(char* str);							  //两字符串相加
	String& operator+(String& rhs);							  //附加到buf尾部
	String& operator+=(String& rhs);						  //对象相加
	String& operator=(const char* str);						  //拷贝字符串
	String& operator=(String&& rsh);						  //移动赋值，省去分配空间std::move
	String& operator=(String& rhs);							  //复制b对象
	bool operator==(String& rhs);    						  //比较
	bool operator==(char* str);   							  //与*str进行比较
	char& operator[](const int n);							  //随机访问
	char* Scopy(char* lhs, const char* rhs);				  //拷贝字符串,源指针所指的字符串内容是不能修改的，因此应该声明为 const 类型。
	int Strcmp(const char* str1, const char* str2);			  //比较两个字符串
	int BF(String& s1, String& s2);							  //成功匹配返回开始匹配位置
	size_t my_strlen() noexcept;
	void delete_char(char Tatget);							  //删除相同的字符
	size_t Length() noexcept { return len = my_strlen(); };
	char* getStr() const noexcept;							  //返回字符串
	void Myclear() const noexcept;
	bool IsEmpty() const { return buf == nullptr; };
	~String();
};

template <typename Type> Type catStr(Type str1, Type str2) {
	int i = 0, j = 0, k = 0, m = 0;
	while (str1[i] != '\0') {
		++i;
		++k;
	}
	while (str2[j] != '\0') {
		++j;
		++m;
	}
	// m == str 的长度
	for (i = 0; i <= m; ++i) {
		//注意：在把str2复制过来时连着最后一个'\0'也要复制过来
		// str1[i + k] = str2[i];
		*(str1 + i + k) = *(str2 + i);
	}
	return str1;
}
template <typename Type> void Swap(Type a, Type b) {
	Type temp;
	temp = a;
	a = b;
	b = temp;
}
template <typename Type> size_t S_size(Type rhs) noexcept {
	assert(rhs != nullptr);
	size_t len = 0;
	while (*rhs++ != '\0') {
		++len;
	}
	return len;
}
//析构
String::~String() {
	if (buf != nullptr) {
		delete[] buf;
		cout << "析构完毕\n";
	}
}
//默认构造函数
String::String() : buf(new char[1]), len(0) { buf = nullptr; }
//接受一个char * 的构造函数
String::String(char* str) {
	if (str == nullptr) {
		buf = new char[1];
		buf[0] = '\0';
		len = 0;
	}
	else {
		buf = new char[S_size(str) + 1];
		Scopy(buf, str);
	}
	len = 0; //重置为0
}
//交换对象数据
void String::Swap(String& rhs) {
	assert((buf != nullptr) && (rhs.buf != nullptr));
	char* temp;
	temp = buf;
	buf = rhs.buf;
	rhs.buf = temp;
}
String::String(const char* str) {
	if (str == nullptr) {
		buf = new char[1];
		buf = nullptr;
		len = 0;
	}
	else {
		buf = new char[S_size(str)];
		// buf = const_cast<char *>(str)去掉常量性,//指向同一块内存，释放会出问题
		Scopy(buf, str);
	}
}
//拷贝构造函数
String::String(const String& rhs) : buf(new char[S_size(rhs.buf)]) {
	// buf = new char[S_size(rhs.buf)]; //申请空间
	// buf = rhs.buf; 指向同一块内存，释放必然出错
	Scopy(buf, rhs.buf);
}
//范围拷贝构造函数
String::String(String& rhs, size_t n) {
	if ((n < 1) || (n > S_size(rhs.buf))) { //检查拷贝范围
		std::cout << "拷贝范围违法\n";
		exit(EXIT_SUCCESS);
	}
	buf = new char[S_size(rhs.buf)];
	assert(buf != nullptr);
	for (size_t x = 0; x != n; ++x)
		buf[x] = rhs.buf[x];
}
//返回字符串
char* String::getStr() const noexcept { return buf; }
//返回数组的大小
size_t String::my_strlen() noexcept {
	if (IsEmpty()) {
		return 0;
	}
	// return strlen(buf); //strlen()标准库函数
	int n = 0;
	len = 0;                   //重置为0
	while (buf[n++] != '\0') { //直到遇到空字符
		++len;
	}
	return len; //返回字符串长度
}
//两个对象相加
String& String::operator+(String& rhs) {
	if (rhs.buf == nullptr) {
		return *this;
	}
	if (buf == nullptr) {
		int n = strlen(rhs.buf);
		buf = new char[n];
		// buf = rhs.buf;
		Scopy(buf, rhs.buf);
	}
	else {
		char* p = catStr(buf, rhs.buf); //为了简洁，使用模板函数，避免重复代码
		Scopy(buf, p);
	}
	return *this;
}
//重载 char* +
String& String::operator+(char* str) {
	if (str == nullptr && buf != nullptr)
		return *this;
	if (buf == nullptr) {
		int n = strlen(str);
		buf = new char[n];
		Scopy(buf, str);
	}
	else {
		char* p = catStr(buf, str); //调用模板函数
		Scopy(buf, p);
	}
	return *this;
}
//重载+=
String& String::operator+=(String& rhs) {
	if (rhs.buf == nullptr) {
		return *this;
	}
	else {
		int i = 0, j = 0, k = 0, m = 0;
		while (buf[i]) {
			++i;
			++k;
		}
		while (rhs.buf[j] != '\0') {
			++j;
			++m;
		}
		for (i = 0; i != k + m; ++i) {
			buf[i + k] = rhs.buf[i];
		}
	}
	return *this;
}
//重载==
bool String::operator==(String& rhs) {
	if (rhs.buf == nullptr || buf == nullptr)
		return false;
	else {
		int i = 0;
		int j = 0;
		while (buf[i] != '\0' && rhs.buf[j] != '\0') {
			if (buf[i] == rhs.buf[j]) {                     //逐一对比，一旦匹配失败，则两字符串不相等
				++i;
				++j;
			}
			else
				return false;
		}
	}
	return true;
}
//比较 char *str ==
bool String::operator==(char* str) {
	if (str == nullptr)
		return false;
	else if (str == nullptr || buf == nullptr)
		return true;
	int i = 0, j = 0;
	while (buf[i] != '\0' && str[j] != '\0') {
		if (buf[i] == str[j]) {
			++i;
			++j;
		}
		else
			return false;
	}
	return true;
}
//拷贝对象
String& String::operator=(String& rhs) {
	if (rhs.buf == nullptr) {
		return *this;
	}
	else {
		delete[] buf;
		buf = new char[rhs.Length()];
		Scopy(buf, rhs.buf);
	}
	return *this;
}
//重载赋值
String& String::operator=(const char* str) {
	if (str == nullptr) { //为空
		buf = NULL;
	}
	else {
		delete[] buf; //先删除，在拷贝
		// int n = my_strlen(str);
		buf = new char[strlen(str) + 1];
		Scopy(buf, str);
	}
	return *this;
}
//移动构造函数
String& String::operator=(String&& rhs) {
	if (this != &rhs) {
		delete[] buf; //先释放内存
		Scopy(buf, rhs.buf);
		rhs.buf = nullptr;
	}
	return *this;
}
//随机访问
char& String ::operator[](const int n) {
	int bufsize = strlen(buf);
	if (n < 0 || n > static_cast<int>(bufsize)) {
		std::cout << "下标索引非法:";
		exit(EXIT_SUCCESS);
	}
	return buf[n];
}
//删除相同的字符
void String::delete_char(char Target) {
	assert((buf != nullptr));
	int j;
	for (int x = j = 0; buf[x] != '\0'; ++x) {
		if (buf[x] != Target)
			buf[j++] = buf[x]; //删除
	}
	buf[j] = '\0';
}

//清空buf
void String::Myclear() const noexcept {
	assert(buf != nullptr);
	size_t n = S_size(buf);
	for (int x = 0; buf[x] != '\0'; ++x) {
		buf[x] = '\0';
	}
}
//拷贝字符串
char* String::Scopy(char* lhs, const char* rhs) {
	assert((lhs != nullptr) && (rhs != nullptr));
	char* temp = lhs; //要用一个临时变量保存目的串的首地址，最后返回这个首地址。
	while ((*lhs++ = *rhs++) != '\0')
		;
	return temp;
}
/*比较两个字符串
若s1==s2，返回零；
若s1>s2，返回正数；
若s1<s2，返回负数。
*/
int String::Strcmp(const char* str1, const char* str2) {
	assert((str1 != nullptr) && (str2 != nullptr));
	while (*str1 == *str2) {
		if (*str1 == '\0')
			return 0;
		++str1;
		++str2;
	}
	return *str1 - *str2; //返回差值
}

//匹配成功的开始位置
int String::BF(String& s1, String& s2) {
	int index = 0;
	int x = 0, y = 0;
	while (s1[x] != '\0' && s2[y] != '\0') {
		if (s1[x] == s2[y]) {
			++x;
			++y;
		}
		else {
			++index;
			x = index;
			y = 0;
		}
	}
	if (s2[y] == '\0')
		return index;
	return -1; //匹配失败
}

#endif // STRING_H_