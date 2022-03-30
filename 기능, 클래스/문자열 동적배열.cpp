#include <Turboc.h>
#include <iostream>
using namespace std;
//�翬�� ���� Ÿ�Կ� ���� �̵�, ���� ������ �� ���Կ����ڴ� ¥����.
//���ڿ� Ŭ����.
class yjjstring {
private:
	char * str_;
	size_t size_;
	size_t cap_;
	size_t find_common(const char * str, size_t count) const;
	void append_common(const char * str, size_t new_elem_count);	//�����
	void yjjstrcpy(char * str1, const char * str2, size_t str2_len);
public:
	constexpr static size_t npos = -1; //non-position, ��Ȯ���� ���� ������.
	yjjstring();
	yjjstring(const char* new_str);//raw ���ڿ��� ���� �ʱ�ȭ�ؾ���.
	~yjjstring();
	yjjstring(const yjjstring& other);//���� ������
	yjjstring(yjjstring&& other);//�̵� ������
	yjjstring& operator =(const yjjstring& other);//���� ���Կ�����
	yjjstring& operator=(const char* null_terminated_str);//��-���� ���ڿ��� ���� ���� ����.
	yjjstring& operator =(yjjstring&& other);//�̵� ���Կ�����
	void moveFrom(yjjstring&& other);
	void clear();//��� ���ڸ� ���.
	void reserve(size_t new_capacity); //(�޸� ����)ĳ�н�Ƽ�� ����.
	size_t check_up_count(size_t new_elem_count) const;
	void push_back(char c); //�� �ڿ� ���ڸ� �߰�.
	void pop_back();//�� �� ���ڸ� ����.
	char& at(size_t offset);//÷�ڿ����� ���� �ش� ��ġ�� ���ڸ� ����.
	const char& at(size_t offset) const;//÷�ڿ����� ���� �ش� ��ġ�� ���ڸ� ����.
	char& operator[](size_t offset);//÷�ڿ����� ���� �ش� ��ġ�� ���ڸ� ����.
	const char& operator[](size_t offset) const; //÷�ڿ����� ���� �ش� ��ġ�� ���ڸ� ����.
	const char* c_str() const;//�����Ṯ�ڿ��� ��ȯ.
	yjjstring substr(size_t offset, size_t len) const;// offset ��ġ�κ��� len��ŭ�� ���ڿ��� ��ȯ.
	size_t find(char c) const; //������ġ�κ��� �ش� ���ڸ� ã���� ���� ��ġ�� ��ȯ. ���� ã�� ���ߴٸ� npos�� ��ȯ.
	size_t find(const char* null_terminated_str) const; //������ġ�κ��� �ش� ���ڿ��� ã���� ���� ��ġ�� ��ȯ. ���� ã�� ���ߴٸ� npos�� ��ȯ.
	size_t find(const yjjstring& str) const;//������ġ�κ��� �ش� ���ڿ��� ã���� ���� ��ġ�� ��ȯ. ���� ã�� ���ߴٸ� npos�� ��ȯ.
	size_t capacity() const; //(����� ũ��)ĳ�ǽ�Ƽ ũ�⸦ ��ȯ.
	size_t size() const; //���ڿ��� ���̸� ��ȯ.
	size_t length() const; //���ڿ��� ���̸� ��ȯ.
	void append(char c); //���� �ϳ��� �߰���.
	void append(const char* null_terminated_str); //��-���� ���ڿ��� �߰���.
	void append(const yjjstring& str); //���ڿ��� �߰���.
	yjjstring& operator +=(char c); //���� �ϳ��� �߰���.
	yjjstring& operator +=(const char* null_terminated_str); //��-���� ���ڿ��� �߰���.
	yjjstring& operator +=(const yjjstring& str); //���ڿ��� �߰���.
};
void main()
{
	yjjstring s;
	s.append('a');
	printf("apped ���� 1ȸ : %s\n", s.c_str());
	s.append("bc");	s.append("def");
	printf("apped ���ڿ� 2ȸ : %s\n", s.c_str());
	s.pop_back();	s.pop_back();
	printf("pop 2ȸ : %s\n", s.c_str());
	printf("s at(2) : %c\n", s.at(2));
	printf("s[1] : %c\n", s[1]);
	printf("s.substr(1,4) : %s\n", s.substr(1, 4));
	yjjstring s2 = s;
	printf("s ������ s2 : %s\n", s2.c_str());
	yjjstring s3("gg");
	printf("s3 string: %s, size: %d, cap: %d\n", s3.c_str(), s3.size(), s3.capacity());
	puts("");
	s += 'g';
	printf("+= ���� : %s\n", s.c_str());
	s += "hij";
	printf("+= ���ڿ� : %s\n", s.c_str());
	puts("");
	printf("capacity() 1ȸ = %d\n", s.capacity());
	printf("size() = %d\n", s.size());
	printf("length() = %d\n", s.length());
	puts("");
	s.append(s2);
	printf("s1 apped s2 : %s\n", s.c_str());
	printf("%s���� %s(s2.str_)�� %d��° find\n", s.c_str(), s2.c_str(), s.find(s2));
	printf("%s���� %s�� %d��° find\n", s.c_str(), s2.c_str(), s.find(s2.c_str()));
	printf("%s���� %c�� %d��° find\n", s.c_str(), 'g', s.find('g'));
	printf("%s���� %s�� %d��° find\n", s.c_str(), nullptr, s.find(nullptr));
}
yjjstring::yjjstring() : str_(nullptr), size_(0), cap_(1) {}
yjjstring::yjjstring(const char* new_str)//raw ���ڿ��� ���� �ʱ�ȭ�ؾ���.
{
	if (new_str != nullptr) {
		clear();
		append(new_str);
	}
}
yjjstring::~yjjstring()
{
	clear();
}
yjjstring::yjjstring(const yjjstring& other)//���� ������
{
	yjjstring();
	append(other);
}
yjjstring::yjjstring(yjjstring&& other)//�̵� ������
{
	moveFrom(std::move(other));
}
yjjstring& yjjstring::operator =(const yjjstring& other)//���� ���Կ�����
{
	if (this != &other) {
		clear();
		append(other);
	}
	return *this;
}
yjjstring& yjjstring::operator=(const char* null_terminated_str)//��-���� ���ڿ��� ���� ���� ����.
{
	clear();
	append(null_terminated_str);
	return *this;
}
yjjstring& yjjstring::operator =(yjjstring&& other)//�̵� ���Կ�����
{
	moveFrom(std::move(other));
	return *this;
}
void yjjstring::moveFrom(yjjstring&& other)	//�̵� ���� �� ���� �� ���� ����
{
	if (this != &other) {
		str_ = other.str_;
		size_ = other.size_;
		cap_ = other.cap_;
		other.str_ = nullptr;
		other.size_ = other.cap_ = 0;
	}
}
void yjjstring::clear()//��� ���ڸ� ���.
{
	if (str_)
		free(str_);
	str_ = nullptr;
	cap_ = size_ = 0;
}
void yjjstring::append_common(const char * str, size_t new_elem_count)
{
	const size_t up_count = check_up_count(new_elem_count);
	size_t new_cap = 0;
	if (up_count != 0) {
		if (capacity() == 0) {
			new_cap = up_count + 1;
		}
		else {
			new_cap = up_count + capacity();
		}
		reserve(new_cap);
	}
	yjjstrcpy(str_ + size(), str, new_elem_count);
	size_ += new_elem_count;
}
size_t yjjstring::find_common(const char * str, size_t count) const
{
	if (str_ == nullptr || str == nullptr) {
		return npos;
	}
	char * findstrstr = strstr(str_, str);
	if (findstrstr == nullptr) {
		return npos;
	}
	else {
		return (findstrstr - str_);
	}
}
size_t yjjstring::check_up_count(size_t new_elem_count) const
{
	if (capacity() == 0) {
		return new_elem_count;
	}
	size_t extra_count = capacity() - size() - 1;
	if (extra_count > new_elem_count) {
		return 0;
	}
	return new_elem_count - extra_count;
}
void yjjstring::reserve(size_t new_capacity) //(�޸� ����)ĳ�н�Ƽ�� ����.
{
	if (cap_ >= new_capacity) {
		return;
	}
	//temp �޸� �Ҵ�
	char* new_buffer = (char*)malloc(new_capacity);
	if (new_buffer == nullptr) {
		return;
	}
	//�޸� ����
	cap_ = new_capacity;
	//temp ����
	for (size_t i = 0; i != size(); i++) {
		new_buffer[i] = str_[i];
	}
	//������ ��ҿ� 0
	if (size() > 0) {
		new_buffer[size()] = 0;
	}
	//�̹� str_�� �޸� ������ ����
	if (str_) {
		free(str_);
	}
	//temp �ٽ� ����
	str_ = new_buffer;
}
void yjjstring::push_back(char c) //�� �ڿ� ���ڸ� �߰�.
{
	append(c);
}
void yjjstring::pop_back()//�� �� ���ڸ� ����.
{
	if (size() > 0) {
		str_[size() - 1] = 0;
		size_--;
	}
}
char& yjjstring::at(size_t offset)//÷�ڿ����� ���� �ش� ��ġ�� ���ڸ� ����.
{
	return str_[offset];
}
const char& yjjstring::at(size_t offset) const//÷�ڿ����� ���� �ش� ��ġ�� ���ڸ� ����.
{
	return str_[offset];
}
char& yjjstring::operator[](size_t offset)//÷�ڿ����� ���� �ش� ��ġ�� ���ڸ� ����.
{
	return *(str_ + offset);
}
const char& yjjstring::operator[](size_t offset) const //÷�ڿ����� ���� �ش� ��ġ�� ���ڸ� ����.
{
	return *(str_ + offset);
}
const char* yjjstring::c_str() const//�����Ṯ�ڿ��� ��ȯ.
{
	return str_;
}
yjjstring yjjstring::substr(size_t offset, size_t len) const// offset ��ġ�κ��� len��ŭ�� ���ڿ��� ��ȯ.
{
	yjjstring tmp;
	tmp.reserve(len + 1);
	for (size_t i = 0; i <= len; i++) {
		tmp.push_back(at(offset + i));
	}
	return tmp;
}
size_t yjjstring::find(char c) const //������ġ�κ��� �ش� ���ڸ� ã���� ���� ��ġ�� ��ȯ. ���� ã�� ���ߴٸ� npos�� ��ȯ.
{
	return find_common(&c, 1);
}
size_t yjjstring::find(const char* null_terminated_str) const //������ġ�κ��� �ش� ���ڿ��� ã���� ���� ��ġ�� ��ȯ. ���� ã�� ���ߴٸ� npos�� ��ȯ.
{
	if (null_terminated_str == nullptr) {
		return npos;
	}
	return find_common(null_terminated_str, strlen(null_terminated_str));
}
size_t yjjstring::find(const yjjstring& str) const//������ġ�κ��� �ش� ���ڿ��� ã���� ���� ��ġ�� ��ȯ. ���� ã�� ���ߴٸ� npos�� ��ȯ.
{
	if (str.size() == 0) {
		return npos;
	}
	return find_common(str.c_str(), strlen(str.c_str()));
}
size_t yjjstring::capacity() const //(����� ũ��)ĳ�ǽ�Ƽ ũ�⸦ ��ȯ.
{
	return cap_;
}
size_t yjjstring::size() const //���ڿ��� ���̸� ��ȯ.
{
	return size_;
}
size_t yjjstring::length() const //���ڿ��� ���̸� ��ȯ.
{
	return size_;
}
void yjjstring::append(char c) //���� �ϳ��� �߰���.
{
	append_common(&c, 1);
}
void yjjstring::append(const char* null_terminated_str) //��-���� ���ڿ��� �߰���.
{
	if (null_terminated_str == nullptr) {
		return;
	}
	append_common(null_terminated_str, strlen(null_terminated_str));
}
void yjjstring::append(const yjjstring& str) //���ڿ��� �߰���.
{
	if (str.c_str() == nullptr) {
		return;
	}
	append_common(str.c_str(), str.size());
}
yjjstring& yjjstring::operator +=(char c) //���� �ϳ��� �߰���.
{
	append(c);
	return *this;
}
yjjstring& yjjstring::operator +=(const char* null_terminated_str) //��-���� ���ڿ��� �߰���.
{
	append(null_terminated_str);
	return *this;
}
yjjstring& yjjstring::operator +=(const yjjstring& str) //���ڿ��� �߰���.
{
	append(str.str_);
	return *this;
}
void yjjstring::yjjstrcpy(char * str1, const char * str2, size_t str2_len)
{
	for (size_t i = 0; i != str2_len; i++) {
		str1[i] = str2[i];
	}
	str1[str2_len] = 0;
}