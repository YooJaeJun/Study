#include <Turboc.h>
#include <iostream>
using namespace std;
//당연히 같은 타입에 대한 이동, 복사 생성자 및 대입연산자는 짜야함.
//문자열 클래스.
class yjjstring {
private:
	char * str_;
	size_t size_;
	size_t cap_;
	size_t find_common(const char * str, size_t count) const;
	void append_common(const char * str, size_t new_elem_count);	//어펜드
	void yjjstrcpy(char * str1, const char * str2, size_t str2_len);
public:
	constexpr static size_t npos = -1; //non-position, 정확하지 않은 포지션.
	yjjstring();
	yjjstring(const char* new_str);//raw 문자열을 통해 초기화해야함.
	~yjjstring();
	yjjstring(const yjjstring& other);//복사 생성자
	yjjstring(yjjstring&& other);//이동 생성자
	yjjstring& operator =(const yjjstring& other);//복사 대입연산자
	yjjstring& operator=(const char* null_terminated_str);//널-종료 문자열을 통해 대입 연산.
	yjjstring& operator =(yjjstring&& other);//이동 대입연산자
	void moveFrom(yjjstring&& other);
	void clear();//모든 문자를 비움.
	void reserve(size_t new_capacity); //(메모리 예약)캐패시티를 예약.
	size_t check_up_count(size_t new_elem_count) const;
	void push_back(char c); //맨 뒤에 문자를 추가.
	void pop_back();//맨 끝 문자를 제거.
	char& at(size_t offset);//첨자연산을 통해 해당 위치의 문자를 접근.
	const char& at(size_t offset) const;//첨자연산을 통해 해당 위치의 문자를 접근.
	char& operator[](size_t offset);//첨자연산을 통해 해당 위치의 문자를 접근.
	const char& operator[](size_t offset) const; //첨자연산을 통해 해당 위치의 문자를 접근.
	const char* c_str() const;//널종료문자열을 반환.
	yjjstring substr(size_t offset, size_t len) const;// offset 위치로부터 len만큼의 문자열을 반환.
	size_t find(char c) const; //시작위치로부터 해당 문자를 찾았을 때의 위치를 반환. 만약 찾지 못했다면 npos를 반환.
	size_t find(const char* null_terminated_str) const; //시작위치로부터 해당 문자열을 찾았을 때의 위치를 반환. 만약 찾지 못했다면 npos를 반환.
	size_t find(const yjjstring& str) const;//시작위치로부터 해당 문자열을 찾았을 때의 위치를 반환. 만약 찾지 못했다면 npos를 반환.
	size_t capacity() const; //(예약된 크기)캐피시티 크기를 반환.
	size_t size() const; //문자열의 길이를 반환.
	size_t length() const; //문자열의 길이를 반환.
	void append(char c); //문자 하나를 추가함.
	void append(const char* null_terminated_str); //널-종료 문자열을 추가함.
	void append(const yjjstring& str); //문자열을 추가함.
	yjjstring& operator +=(char c); //문자 하나를 추가함.
	yjjstring& operator +=(const char* null_terminated_str); //널-종료 문자열을 추가함.
	yjjstring& operator +=(const yjjstring& str); //문자열을 추가함.
};
void main()
{
	yjjstring s;
	s.append('a');
	printf("apped 문자 1회 : %s\n", s.c_str());
	s.append("bc");	s.append("def");
	printf("apped 문자열 2회 : %s\n", s.c_str());
	s.pop_back();	s.pop_back();
	printf("pop 2회 : %s\n", s.c_str());
	printf("s at(2) : %c\n", s.at(2));
	printf("s[1] : %c\n", s[1]);
	printf("s.substr(1,4) : %s\n", s.substr(1, 4));
	yjjstring s2 = s;
	printf("s 대입한 s2 : %s\n", s2.c_str());
	yjjstring s3("gg");
	printf("s3 string: %s, size: %d, cap: %d\n", s3.c_str(), s3.size(), s3.capacity());
	puts("");
	s += 'g';
	printf("+= 문자 : %s\n", s.c_str());
	s += "hij";
	printf("+= 문자열 : %s\n", s.c_str());
	puts("");
	printf("capacity() 1회 = %d\n", s.capacity());
	printf("size() = %d\n", s.size());
	printf("length() = %d\n", s.length());
	puts("");
	s.append(s2);
	printf("s1 apped s2 : %s\n", s.c_str());
	printf("%s에서 %s(s2.str_)는 %d번째 find\n", s.c_str(), s2.c_str(), s.find(s2));
	printf("%s에서 %s는 %d번째 find\n", s.c_str(), s2.c_str(), s.find(s2.c_str()));
	printf("%s에서 %c는 %d번째 find\n", s.c_str(), 'g', s.find('g'));
	printf("%s에서 %s는 %d번째 find\n", s.c_str(), nullptr, s.find(nullptr));
}
yjjstring::yjjstring() : str_(nullptr), size_(0), cap_(1) {}
yjjstring::yjjstring(const char* new_str)//raw 문자열을 통해 초기화해야함.
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
yjjstring::yjjstring(const yjjstring& other)//복사 생성자
{
	yjjstring();
	append(other);
}
yjjstring::yjjstring(yjjstring&& other)//이동 생성자
{
	moveFrom(std::move(other));
}
yjjstring& yjjstring::operator =(const yjjstring& other)//복사 대입연산자
{
	if (this != &other) {
		clear();
		append(other);
	}
	return *this;
}
yjjstring& yjjstring::operator=(const char* null_terminated_str)//널-종료 문자열을 통해 대입 연산.
{
	clear();
	append(null_terminated_str);
	return *this;
}
yjjstring& yjjstring::operator =(yjjstring&& other)//이동 대입연산자
{
	moveFrom(std::move(other));
	return *this;
}
void yjjstring::moveFrom(yjjstring&& other)	//이동 생성 및 대입 시 얕은 복사
{
	if (this != &other) {
		str_ = other.str_;
		size_ = other.size_;
		cap_ = other.cap_;
		other.str_ = nullptr;
		other.size_ = other.cap_ = 0;
	}
}
void yjjstring::clear()//모든 문자를 비움.
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
void yjjstring::reserve(size_t new_capacity) //(메모리 예약)캐패시티를 예약.
{
	if (cap_ >= new_capacity) {
		return;
	}
	//temp 메모리 할당
	char* new_buffer = (char*)malloc(new_capacity);
	if (new_buffer == nullptr) {
		return;
	}
	//메모리 예약
	cap_ = new_capacity;
	//temp 복사
	for (size_t i = 0; i != size(); i++) {
		new_buffer[i] = str_[i];
	}
	//마지막 요소에 0
	if (size() > 0) {
		new_buffer[size()] = 0;
	}
	//이미 str_에 메모리 있으면 해제
	if (str_) {
		free(str_);
	}
	//temp 다시 복사
	str_ = new_buffer;
}
void yjjstring::push_back(char c) //맨 뒤에 문자를 추가.
{
	append(c);
}
void yjjstring::pop_back()//맨 끝 문자를 제거.
{
	if (size() > 0) {
		str_[size() - 1] = 0;
		size_--;
	}
}
char& yjjstring::at(size_t offset)//첨자연산을 통해 해당 위치의 문자를 접근.
{
	return str_[offset];
}
const char& yjjstring::at(size_t offset) const//첨자연산을 통해 해당 위치의 문자를 접근.
{
	return str_[offset];
}
char& yjjstring::operator[](size_t offset)//첨자연산을 통해 해당 위치의 문자를 접근.
{
	return *(str_ + offset);
}
const char& yjjstring::operator[](size_t offset) const //첨자연산을 통해 해당 위치의 문자를 접근.
{
	return *(str_ + offset);
}
const char* yjjstring::c_str() const//널종료문자열을 반환.
{
	return str_;
}
yjjstring yjjstring::substr(size_t offset, size_t len) const// offset 위치로부터 len만큼의 문자열을 반환.
{
	yjjstring tmp;
	tmp.reserve(len + 1);
	for (size_t i = 0; i <= len; i++) {
		tmp.push_back(at(offset + i));
	}
	return tmp;
}
size_t yjjstring::find(char c) const //시작위치로부터 해당 문자를 찾았을 때의 위치를 반환. 만약 찾지 못했다면 npos를 반환.
{
	return find_common(&c, 1);
}
size_t yjjstring::find(const char* null_terminated_str) const //시작위치로부터 해당 문자열을 찾았을 때의 위치를 반환. 만약 찾지 못했다면 npos를 반환.
{
	if (null_terminated_str == nullptr) {
		return npos;
	}
	return find_common(null_terminated_str, strlen(null_terminated_str));
}
size_t yjjstring::find(const yjjstring& str) const//시작위치로부터 해당 문자열을 찾았을 때의 위치를 반환. 만약 찾지 못했다면 npos를 반환.
{
	if (str.size() == 0) {
		return npos;
	}
	return find_common(str.c_str(), strlen(str.c_str()));
}
size_t yjjstring::capacity() const //(예약된 크기)캐피시티 크기를 반환.
{
	return cap_;
}
size_t yjjstring::size() const //문자열의 길이를 반환.
{
	return size_;
}
size_t yjjstring::length() const //문자열의 길이를 반환.
{
	return size_;
}
void yjjstring::append(char c) //문자 하나를 추가함.
{
	append_common(&c, 1);
}
void yjjstring::append(const char* null_terminated_str) //널-종료 문자열을 추가함.
{
	if (null_terminated_str == nullptr) {
		return;
	}
	append_common(null_terminated_str, strlen(null_terminated_str));
}
void yjjstring::append(const yjjstring& str) //문자열을 추가함.
{
	if (str.c_str() == nullptr) {
		return;
	}
	append_common(str.c_str(), str.size());
}
yjjstring& yjjstring::operator +=(char c) //문자 하나를 추가함.
{
	append(c);
	return *this;
}
yjjstring& yjjstring::operator +=(const char* null_terminated_str) //널-종료 문자열을 추가함.
{
	append(null_terminated_str);
	return *this;
}
yjjstring& yjjstring::operator +=(const yjjstring& str) //문자열을 추가함.
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