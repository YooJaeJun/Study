#include <Turboc.h>
#include <vector>
#include <iostream>
using namespace std;

/*
class temp_class {
public:
	temp_class() { std::cout << "default ctor\n"; }
	temp_class(const temp_class&) { std::cout << "copy ctor\n"; }
	temp_class(temp_class&&) noexcept { std::cout << "move ctor\n"; }
	temp_class& operator=(const temp_class&) { std::cout << "copy assign\n"; return *this; }
	temp_class& operator=(temp_class&&) noexcept { std::cout << "move assign\n"; return *this; }
	~temp_class() { std::cout << "dtor\n"; }
};
*/

class yjjvector {
public:
	yjjvector();
	yjjvector(const yjjvector& other); //복사 생성자
	~yjjvector();

	yjjvector& operator=(const yjjvector& other);//복사 대입 연산자
	const int& operator[](size_t offset) const; //[] 연산자

	size_t size() const; //컨테이너의 크기를 반환
	void push_back(int new_item); //요소를 맨 뒤에 추가.
	void pop_back(); //맨 끝 요소를 제거
	int& at(size_t offset); //요소에 접근
	const int& at(size_t offset) const; //요소에 접근
	void insert(int new_item, size_t offset); //정해진 위치에 요소를 삽입

	yjjvector(yjjvector&& other); //이동 생성자
	yjjvector& operator=(yjjvector&& other);//이동 대입 연산자

private:
	int* data_;
	size_t size_;
	size_t capacity_;
	void memory_check()
	{
		if (size_ >= capacity_) {
			if (capacity_ == 0) {
				capacity_ = 1;
			}
			else {
				capacity_ += capacity_ / 2 + 1;
			}
			if (data_ == nullptr) {
				data_ = (int *)malloc(capacity_ * sizeof(int));
			}
			else {
				int* temp = (int *)malloc(capacity_ * sizeof(int));
				for (int i = 0; i != size_; i++) {
					temp[i] = data_[i];
				}
				data_ = (int *)malloc(capacity_ * sizeof(int));
				for (int i = 0; i != size_; i++) {
					data_[i] = temp[i];
				}
			}
		}
	}
};

yjjvector::yjjvector() : size_(0), capacity_(0), data_(nullptr) {} //생성자

yjjvector::yjjvector(const yjjvector& other) //복사 생성자
	: size_(other.size_), capacity_(other.capacity_)
{
	//깊은 복사라, 포인터에 대해 별도의 메모리 할당한 후 요소 하나 하나 복사
	data_ = (int*)malloc(other.capacity_ * sizeof(int));
	for (int i = 0; i < size_; i++) {
		data_[i] = other.data_[i];
	}
}

yjjvector& const yjjvector::operator=(const yjjvector& other)//복사 대입 연산자
{
	//1. 기존에 같으면 그냥 리턴
	if (this == &other) { return *this; }
	//2. 기존에 있던 게 있으면 한 번 소멸시켜준다는 발상
	if (data_ != nullptr) { free(data_); }
	data_ = nullptr;

	size_ = other.size_;
	capacity_ = other.capacity_;
	//3. 수용량이 0 아니면 메모리 할당시켜주는 발상
	if (capacity_ != 0) {
		data_ = (int*)malloc(capacity_ * sizeof(int));
	}
	for (int i = 0; i != size_; ++i) {
		data_[i] = other.data_[i];
	}
	return *this;
}
yjjvector::yjjvector(yjjvector&& other) //이동 생성자
	: data_(other.data_), size_(other.size_), capacity_(other.capacity_)
{
	other.data_ = nullptr;
	other.size_ = other.capacity_ = 0;
}
yjjvector& yjjvector::operator=(yjjvector&& other) //이동 대입 연산자
{
	if (this == &other) { return *this; }
	if (data_ != nullptr) { free(data_); }
	data_ = nullptr;

	//얕은 복사라 주소값을 받기 때문에 메모리 할당 없이 대입
	size_ = other.size_;
	capacity_ = other.capacity_;
	data_ = other.data_;

	other.data_ = nullptr;
	other.size_ = other.capacity_ = 0;

	return *this;
}

yjjvector::~yjjvector()
{
	free(data_);
}

const int& yjjvector::operator[](size_t offset) const //[] 연산자
{
	return data_[offset];
}

size_t yjjvector::size() const //컨테이너의 크기를 반환
{
	return size_;
}

void yjjvector::push_back(int new_item) //요소를 맨 뒤에 추가.
{
	size_++;
	memory_check();
	data_[size_ - 1] = new_item;
}
void yjjvector::pop_back() //맨 끝 요소를 제거
{
	size_--;
	data_[size_] = '\0';
}

int& yjjvector::at(size_t offset) //요소에 접근
{
	return data_[offset];
}
const int& yjjvector::at(size_t offset) const //요소에 접근
{
	return data_[offset];
}
void yjjvector::insert(int new_item, size_t offset) //정해진 위치에 요소를 삽입
{
	size_++;
	memory_check();
	for (int i = size_ - 1; i != offset; i--) {
		data_[i] = data_[i - 1];
	}
	data_[offset] = new_item;
}

int main()
{
	yjjvector v1;
	v1.push_back(4);
	v1.push_back(8);
	v1.insert(5, 1);
	yjjvector v2(v1);
	v1.insert(6, 2);
	v1.insert(7, 1);
	v1.insert(7, 3);
	printf("v1[0] = %d\n", v1[0]);
	printf("v1[1] = %d\n", v1[1]);
	printf("v1[2] = %d\n", v1[2]);
	printf("v1[3] = %d\n", v1[3]);
	printf("v1[4] = %d\n", v1[4]);

	/*
	std::vector<temp_class> v;
	temp_class tc;
	v.push_back(tc); std::cout << "1번째 요소 삽입 완료.\n";
	v.push_back(tc); std::cout << "2번째 요소 삽입 완료.\n";
	v.push_back(tc); std::cout << "3번째 요소 삽입 완료.\n";
	v.push_back(tc); std::cout << "4번째 요소 삽입 완료.\n";
	v.push_back(tc); std::cout << "5번째 요소 삽입 완료.\n";
	*/

}