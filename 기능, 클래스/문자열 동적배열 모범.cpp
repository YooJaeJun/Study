#include <Turboc.h>
#include <iostream>
using namespace std;
class zeestring {
public:
	static constexpr size_t npos = -1;
	zeestring() noexcept
		: buffer_(nullptr), size_(0), capacity_(0)
	{
	}
	zeestring(const zeestring& other)
		: zeestring()
	{
		append(other);
	}
	zeestring(zeestring&& other) noexcept
		: zeestring()
	{
		move_from(std::move(other));
	}
	~zeestring() {
		clear();
	}
	zeestring& operator=(const char* str) {
		clear();
		append(str);
		return *this;
	}
	zeestring& operator=(const zeestring& other) {
		if (this != &other) {
			clear();
			append(other);
		}
		return *this;
	}
	zeestring& operator=(zeestring&& other) noexcept {
		if (this != &other) {
			move_from(std::move(other));
		}
		return *this;
	}
	void clear() {
		if (buffer_) {
			free(buffer_);
		}
		buffer_ = nullptr;
		capacity_ = size_ = 0;
	}
	size_t capacity() const { return capacity_; }
	size_t size() const { return size_; }
	const char* c_str() const { return buffer_; }
	char& at(size_t offset) { return buffer_[offset]; }
	const char& at(size_t offset) const { return buffer_[offset]; }
	void reserve(size_t new_capacity) {
		if (capacity_ >= new_capacity) {
			return;
		}
		char* new_buffer = (char*)malloc(new_capacity);
		if (new_buffer == nullptr) {
			return;
		}
		capacity_ = new_capacity;
		for (size_t i = 0; i != size(); ++i) {
			new_buffer[i] = buffer_[i];
		}
		if (size() > 0) {
			new_buffer[size()] = 0;
		}
		if (buffer_) {
			free(buffer_);
		}
		buffer_ = new_buffer;
	}
	void append(char c) {
		append_impl(&c, 1);
	}
	void append(const char* str) {
		if (str == nullptr) {
			return;
		}
		append_impl(str, strlen(str));
	}
	void append(const zeestring& other) {
		append_impl(other.c_str(), other.size());
	}
	void push_back(char c) {
		append(c);
	}
	void pop_back() {
		if (size() > 0) {
			buffer_[size() - 1] = 0;
			size_--;
		}
	}
	zeestring substr(size_t offset, size_t len) const {
		zeestring ret;
		ret.reserve(len + 1);
		for (size_t i = 0; i != len; ++i) {
			ret.push_back(at(offset + i));
		}
		return ret;
	}
	size_t find(char c) const {
		return find_impl(&c, 1);
	}
	size_t find(const char* str) const {
		if (str == nullptr) {
			return npos;
		}
		return find_impl(str, strlen(str));
	}
	size_t find(const zeestring& other) const {
		if (other.size() == 0) {
			return npos;
		}
		return find_impl(other.c_str(), other.size());
	}
	zeestring& operator+=(char c) {
		append(c);
		return *this;
	}
	zeestring& operator+=(const char* str) {
		append(str);
		return *this;
	}
	zeestring& operator+=(const zeestring& other) {
		append(other);
		return *this;
	}
	char& operator[](size_t offset) { return at(offset); }
	const char& operator[](size_t offset) const { return at(offset); }
private:
	size_t find_impl(const char* str, size_t count) const {
		size_t ret = npos;
		if (size() > 0) {
			bool bFound = true;
			for (size_t i = 0; i != size(); ++i) {
				bFound = true;
				for (size_t j = 0; j != count; ++j) {
					if (at(i + j) != str[j]) {
						bFound = false;
						break;
					}
				}
				if (bFound) {
					ret = i;
					break;
				}
			}
		}
		return ret;
	}
	void append_impl(const char* str, size_t new_elem_count) {
		const size_t growth_up_count = check_growth_up_count(new_elem_count);
		if (growth_up_count != 0) {
			const size_t new_capacity = capacity() == 0 ? growth_up_count + 1 : growth_up_count + capacity();
			reserve(new_capacity);
		}
		zee_strcpy(buffer_ + size(), str, new_elem_count);
		size_ += new_elem_count;
	}
	size_t check_growth_up_count(size_t new_elem_count) const {
		if (capacity() == 0) {
			return new_elem_count;
		}
		size_t extra_count = capacity() - size() - 1;
		if (extra_count > new_elem_count) {
			return 0;
		}
		return new_elem_count - extra_count;
	}
	static void zee_strcpy(char* dest, const char* src, size_t src_count) {
		for (size_t i = 0; i != src_count; ++i) {
			dest[i] = src[i];
		}
		dest[src_count] = 0;
	}
	void move_from(zeestring&& other) {
		if (this != &other) {
			clear();
			buffer_ = other.buffer_;
			size_ = other.size_;
			capacity_ = other.capacity_;
			other.buffer_ = nullptr;
			other.capacity_ = other.size_ = 0;
		}
	}
private:
	char* buffer_;
	size_t size_;
	size_t capacity_;
};