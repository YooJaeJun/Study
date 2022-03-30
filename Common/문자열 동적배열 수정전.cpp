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
	yjjvector(const yjjvector& other); //���� ������
	~yjjvector();

	yjjvector& operator=(const yjjvector& other);//���� ���� ������
	const int& operator[](size_t offset) const; //[] ������

	size_t size() const; //�����̳��� ũ�⸦ ��ȯ
	void push_back(int new_item); //��Ҹ� �� �ڿ� �߰�.
	void pop_back(); //�� �� ��Ҹ� ����
	int& at(size_t offset); //��ҿ� ����
	const int& at(size_t offset) const; //��ҿ� ����
	void insert(int new_item, size_t offset); //������ ��ġ�� ��Ҹ� ����

	yjjvector(yjjvector&& other); //�̵� ������
	yjjvector& operator=(yjjvector&& other);//�̵� ���� ������

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

yjjvector::yjjvector() : size_(0), capacity_(0), data_(nullptr) {} //������

yjjvector::yjjvector(const yjjvector& other) //���� ������
	: size_(other.size_), capacity_(other.capacity_)
{
	//���� �����, �����Ϳ� ���� ������ �޸� �Ҵ��� �� ��� �ϳ� �ϳ� ����
	data_ = (int*)malloc(other.capacity_ * sizeof(int));
	for (int i = 0; i < size_; i++) {
		data_[i] = other.data_[i];
	}
}

yjjvector& const yjjvector::operator=(const yjjvector& other)//���� ���� ������
{
	//1. ������ ������ �׳� ����
	if (this == &other) { return *this; }
	//2. ������ �ִ� �� ������ �� �� �Ҹ�����شٴ� �߻�
	if (data_ != nullptr) { free(data_); }
	data_ = nullptr;

	size_ = other.size_;
	capacity_ = other.capacity_;
	//3. ���뷮�� 0 �ƴϸ� �޸� �Ҵ�����ִ� �߻�
	if (capacity_ != 0) {
		data_ = (int*)malloc(capacity_ * sizeof(int));
	}
	for (int i = 0; i != size_; ++i) {
		data_[i] = other.data_[i];
	}
	return *this;
}
yjjvector::yjjvector(yjjvector&& other) //�̵� ������
	: data_(other.data_), size_(other.size_), capacity_(other.capacity_)
{
	other.data_ = nullptr;
	other.size_ = other.capacity_ = 0;
}
yjjvector& yjjvector::operator=(yjjvector&& other) //�̵� ���� ������
{
	if (this == &other) { return *this; }
	if (data_ != nullptr) { free(data_); }
	data_ = nullptr;

	//���� ����� �ּҰ��� �ޱ� ������ �޸� �Ҵ� ���� ����
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

const int& yjjvector::operator[](size_t offset) const //[] ������
{
	return data_[offset];
}

size_t yjjvector::size() const //�����̳��� ũ�⸦ ��ȯ
{
	return size_;
}

void yjjvector::push_back(int new_item) //��Ҹ� �� �ڿ� �߰�.
{
	size_++;
	memory_check();
	data_[size_ - 1] = new_item;
}
void yjjvector::pop_back() //�� �� ��Ҹ� ����
{
	size_--;
	data_[size_] = '\0';
}

int& yjjvector::at(size_t offset) //��ҿ� ����
{
	return data_[offset];
}
const int& yjjvector::at(size_t offset) const //��ҿ� ����
{
	return data_[offset];
}
void yjjvector::insert(int new_item, size_t offset) //������ ��ġ�� ��Ҹ� ����
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
	v.push_back(tc); std::cout << "1��° ��� ���� �Ϸ�.\n";
	v.push_back(tc); std::cout << "2��° ��� ���� �Ϸ�.\n";
	v.push_back(tc); std::cout << "3��° ��� ���� �Ϸ�.\n";
	v.push_back(tc); std::cout << "4��° ��� ���� �Ϸ�.\n";
	v.push_back(tc); std::cout << "5��° ��� ���� �Ϸ�.\n";
	*/

}