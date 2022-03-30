#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void memcpy(void* dst, const void* src, size_t size) {
	char* desc_ptr = (char*)dst;
	const char* source_ptr = (const char*)src;
	for (size_t i = 0; i != size; ++i) {
		desc_ptr[i] = source_ptr[i];
	}
}

void* move_ptr(void* ptr, ptrdiff_t offset, size_t size) {
	return (char*)ptr + offset * size;
}

void jaejoon_sort(void* ptr, size_t count, size_t size, int(*comp)(const void*, const void*))
{
	char* cursor = (char*)ptr;
	void* temp_buffer = malloc(count);
	for (size_t i = 0; i != count; i++)
	{
		for (size_t j = 0; j != count - 1 - i; j++)
		{
			void* left = move_ptr(ptr, j, size);
			void* right = move_ptr(ptr, j + 1, size);
			if (comp(left, right) > 0)
			{
				memcpy(temp_buffer, left, size);
				memcpy(left, right, size);
				memcpy(right, temp_buffer, size);
			}
		}
	}
	free(temp_buffer);
}

int cmp(const void* arg1, const void* arg2) {
	const int arg1_ = *(const int*)arg1;
	const int arg2_ = *(const int*)arg2;
	if (arg1_ < arg2_) return -1;
	if (arg1_ > arg2_) return 1;
	return 0;
}

int main() {
#define ARR_SIZE 9
	int arr[ARR_SIZE]{
		121,35,3,22,7,9,123,124,1
	};
	jaejoon_sort(arr, ARR_SIZE, sizeof(int), &cmp);
	int d = 0;

	return 0;
}