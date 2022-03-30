#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int is_num(char c) {
	return c >= '0' && c <= '9';
}

int is_equal(const char* str1, const char* str2) {
	for (int i = 0; str1[i] || str2[i]; ++i) {
		if (str1[i] < str2[i]) {
			return -1;
		}
		else if (str2[i] < str1[i]) {
			return 1;
		}
	}
	return 0;
}

#define NUMS 10
int get_num_by_str(const char* buffer) {
	static const char* const Numbers[NUMS] = {
		"zero","one","two","three","four","five","six","seven","eight","nine"
	};

	for (int i = 0; i != NUMS; ++i) {
		if (is_equal(Numbers[i], buffer) == 0) {
			return i;
		}
	}
	return -1;
}

int get_num(const char* buffer) {
	if (is_num(buffer[0])) {
		return buffer[0] - '0';
	}
	return get_num_by_str(buffer);
}

#define BUFFER_SIZE 6
void clear_buffer(char* buffer) {
	for (int i = 0; i != BUFFER_SIZE; ++i) {
		buffer[i] = 0;
	}
}

int solution(const char* s) {
	int answer = 0;
	char buffer[BUFFER_SIZE];
	clear_buffer(buffer);
	char* buffer_ptr = buffer;
	while (*s) {
		*buffer_ptr++ = *s++;
		int value = get_num(buffer);
		if (value >= 0) {
			answer *= 10;
			answer += value;
			buffer_ptr = buffer;
			clear_buffer(buffer);
		}
	}
	return answer;
}

int main()
{
	const char *s = "one2two";
	solution(s);

	return 0;
}