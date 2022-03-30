
const int buffer_size = 6;
class parser {
public:
	parser() {
		clear();
	}

	int read(char c) {
		*buffer_ptr++ = c;
		int ret = to_number();
		if (ret != -1) {
			clear();
		}
		return ret;
	}

private:
	void clear() {
		for (auto& c : buffer) {
			c = 0;
		}
		buffer_ptr = buffer;
	}

	bool is_number() const {
		return buffer[0] >= '0' && buffer[0] <= '9';
	}

	int to_number() const {
		if (is_number()) {
			return buffer[0] - '0';
		}
		return to_number_by_str();
	}

	static bool compare_str(const char* str1, const char* str2) {
		for (int i = 0; str1[i] || str2[i]; ++i) {
			if (str1[i] < str2[i]) {
				return false;
			}
			else if (str2[i] < str1[i]) {
				return false;
			}
		}
		return true;
	}

	int to_number_by_str() const {
		static const int NumberSize = 10;
		static const char* const Numbers[NumberSize] = {
			"zero","one","two","three","four","five","six","seven","eight","nine"
		};

		for (int i = 0; i != NumberSize; ++i) {
			if (compare_str(buffer_ptr, Numbers[i])) {
				return i;
			}
		}

		return -1;
	}

private:
	char buffer[buffer_size] = {};
	char* buffer_ptr = nullptr;
};

int solution(const char* s) {
	int answer = 0;
	parser p;
	while (*s) {
		int value = p.read(*s);
		if (value >= 0) {
			answer *= 10;
			answer += value;
		}
	}
	return answer;
}
