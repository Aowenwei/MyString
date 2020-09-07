#pragma once
#ifndef STRING_H_
#define STRING_H_
#include <cstdlib>
#include <cassert>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
template <typename Type> Type catStr(Type a, Type b);		//���������ַ���
template <typename Type> void Swap(Type a, Type b);
template <typename Type> size_t S_size(Type rhs) noexcept;


class String {
private:
	char* buf;
	size_t len;

public:
	String();
	String(const String& rhs);								  //�������캯��
	String(String& rhs, size_t n);							  //��Χ����
	explicit String(char* str);								  //һ����������
	String(const char* str);								  // const char *����
	void Swap(String&);										  //�������������
	String& operator+(char* str);							  //���ַ������
	String& operator+(String& rhs);							  //���ӵ�bufβ��
	String& operator+=(String& rhs);						  //�������
	String& operator=(const char* str);						  //�����ַ���
	String& operator=(String&& rsh);						  //�ƶ���ֵ��ʡȥ����ռ�std::move
	String& operator=(String& rhs);							  //����b����
	bool operator==(String& rhs);    						  //�Ƚ�
	bool operator==(char* str);   							  //��*str���бȽ�
	char& operator[](const int n);							  //�������
	char* Scopy(char* lhs, const char* rhs);				  //�����ַ���,Դָ����ָ���ַ��������ǲ����޸ĵģ����Ӧ������Ϊ const ���͡�
	int Strcmp(const char* str1, const char* str2);			  //�Ƚ������ַ���
	int BF(String& s1, String& s2);							  //�ɹ�ƥ�䷵�ؿ�ʼƥ��λ��
	size_t my_strlen() noexcept;
	void delete_char(char Tatget);							  //ɾ����ͬ���ַ�
	size_t Length() noexcept { return len = my_strlen(); };
	char* getStr() const noexcept;							  //�����ַ���
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
	// m == str �ĳ���
	for (i = 0; i <= m; ++i) {
		//ע�⣺�ڰ�str2���ƹ���ʱ�������һ��'\0'ҲҪ���ƹ���
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
//����
String::~String() {
	if (buf != nullptr) {
		delete[] buf;
		cout << "�������\n";
	}
}
//Ĭ�Ϲ��캯��
String::String() : buf(new char[1]), len(0) { buf = nullptr; }
//����һ��char * �Ĺ��캯��
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
	len = 0; //����Ϊ0
}
//������������
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
		// buf = const_cast<char *>(str)ȥ��������,//ָ��ͬһ���ڴ棬�ͷŻ������
		Scopy(buf, str);
	}
}
//�������캯��
String::String(const String& rhs) : buf(new char[S_size(rhs.buf)]) {
	// buf = new char[S_size(rhs.buf)]; //����ռ�
	// buf = rhs.buf; ָ��ͬһ���ڴ棬�ͷű�Ȼ����
	Scopy(buf, rhs.buf);
}
//��Χ�������캯��
String::String(String& rhs, size_t n) {
	if ((n < 1) || (n > S_size(rhs.buf))) { //��鿽����Χ
		std::cout << "������ΧΥ��\n";
		exit(EXIT_SUCCESS);
	}
	buf = new char[S_size(rhs.buf)];
	assert(buf != nullptr);
	for (size_t x = 0; x != n; ++x)
		buf[x] = rhs.buf[x];
}
//�����ַ���
char* String::getStr() const noexcept { return buf; }
//��������Ĵ�С
size_t String::my_strlen() noexcept {
	if (IsEmpty()) {
		return 0;
	}
	// return strlen(buf); //strlen()��׼�⺯��
	int n = 0;
	len = 0;                   //����Ϊ0
	while (buf[n++] != '\0') { //ֱ���������ַ�
		++len;
	}
	return len; //�����ַ�������
}
//�����������
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
		char* p = catStr(buf, rhs.buf); //Ϊ�˼�࣬ʹ��ģ�庯���������ظ�����
		Scopy(buf, p);
	}
	return *this;
}
//���� char* +
String& String::operator+(char* str) {
	if (str == nullptr && buf != nullptr)
		return *this;
	if (buf == nullptr) {
		int n = strlen(str);
		buf = new char[n];
		Scopy(buf, str);
	}
	else {
		char* p = catStr(buf, str); //����ģ�庯��
		Scopy(buf, p);
	}
	return *this;
}
//����+=
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
//����==
bool String::operator==(String& rhs) {
	if (rhs.buf == nullptr || buf == nullptr)
		return false;
	else {
		int i = 0;
		int j = 0;
		while (buf[i] != '\0' && rhs.buf[j] != '\0') {
			if (buf[i] == rhs.buf[j]) {                     //��һ�Աȣ�һ��ƥ��ʧ�ܣ������ַ��������
				++i;
				++j;
			}
			else
				return false;
		}
	}
	return true;
}
//�Ƚ� char *str ==
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
//��������
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
//���ظ�ֵ
String& String::operator=(const char* str) {
	if (str == nullptr) { //Ϊ��
		buf = NULL;
	}
	else {
		delete[] buf; //��ɾ�����ڿ���
		// int n = my_strlen(str);
		buf = new char[strlen(str) + 1];
		Scopy(buf, str);
	}
	return *this;
}
//�ƶ����캯��
String& String::operator=(String&& rhs) {
	if (this != &rhs) {
		delete[] buf; //���ͷ��ڴ�
		Scopy(buf, rhs.buf);
		rhs.buf = nullptr;
	}
	return *this;
}
//�������
char& String ::operator[](const int n) {
	int bufsize = strlen(buf);
	if (n < 0 || n > static_cast<int>(bufsize)) {
		std::cout << "�±������Ƿ�:";
		exit(EXIT_SUCCESS);
	}
	return buf[n];
}
//ɾ����ͬ���ַ�
void String::delete_char(char Target) {
	assert((buf != nullptr));
	int j;
	for (int x = j = 0; buf[x] != '\0'; ++x) {
		if (buf[x] != Target)
			buf[j++] = buf[x]; //ɾ��
	}
	buf[j] = '\0';
}

//���buf
void String::Myclear() const noexcept {
	assert(buf != nullptr);
	size_t n = S_size(buf);
	for (int x = 0; buf[x] != '\0'; ++x) {
		buf[x] = '\0';
	}
}
//�����ַ���
char* String::Scopy(char* lhs, const char* rhs) {
	assert((lhs != nullptr) && (rhs != nullptr));
	char* temp = lhs; //Ҫ��һ����ʱ��������Ŀ�Ĵ����׵�ַ����󷵻�����׵�ַ��
	while ((*lhs++ = *rhs++) != '\0')
		;
	return temp;
}
/*�Ƚ������ַ���
��s1==s2�������㣻
��s1>s2������������
��s1<s2�����ظ�����
*/
int String::Strcmp(const char* str1, const char* str2) {
	assert((str1 != nullptr) && (str2 != nullptr));
	while (*str1 == *str2) {
		if (*str1 == '\0')
			return 0;
		++str1;
		++str2;
	}
	return *str1 - *str2; //���ز�ֵ
}

//ƥ��ɹ��Ŀ�ʼλ��
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
	return -1; //ƥ��ʧ��
}

#endif // STRING_H_