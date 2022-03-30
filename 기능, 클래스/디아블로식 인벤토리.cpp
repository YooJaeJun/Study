#include <cstdio>
#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

//칼라 외부 자료
void ColorSet(int backColor, int textColor) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, (backColor << 4) + textColor);
}
struct point {
	int x;
	int y;
};

enum color_kinds {
	black, blue, green, skyblue, red, pink, orange, white, gray, lightblue, breightgreen, sky, brightred, brightpink, brightyellow, brightwhite
};

//아이템
class item_data {
public:
	item_data() : id_(' '), x_(0), y_(0), color_vari_(0) {}
	explicit item_data(char id, int x, int y, int color_vari) : x_(x), y_(y), color_vari_(color_vari) {
		if (id_ != id) {
			id_ = id;
		}
	}
	char get_id() const { return id_; }
	int get_x() const { return x_; }
	int get_y() const { return y_; }
	int get_color() const { return color_vari_; }
private:
	char id_;
	int x_;
	int y_;
	int color_vari_;
};

//인벤토리
class inventory {
public:
	inventory() : x_(10), y_(4) { }
	explicit inventory(int x, int y) : x_(x), y_(y) { }
	int get_x() const { return x_; }
	int get_y() const { return y_; }
	void add(const item_data item);
	bool check_item(const int final);
	void print_inven();
	void remove(char id);
	int remove_item(char id);
private:
	int arr[4][10] = { 0, };	//[핵심] 유효 좌표 기록 및 판단
	int x_;
	int y_;
	vector<item_data> items_;
};
void inventory::add(const item_data item) {

	items_.push_back(item);
	int final = items_.size() - 1;
	//아이템 유효 좌표 기록
	bool isSpace = check_item(final);

	if (isSpace) {
		printf("Success Add Item (id = %c Size= %dx%d)\n"
			, items_[final].get_id(), items_[final].get_x(), items_[final].get_y());
	}
	else {
		printf("Fail Add Item (id = %c Size= %dx%d)\n"
			, items_[final].get_id(), items_[final].get_x(), items_[final].get_y());
	}

	//아이템 채우기
	print_inven();

	//콘솔창 출력 위한 거리
	printf("\n");
}

bool inventory::check_item(const int final) {
	bool isSpace = false;
	//아이템 들어갈 자리 있는지 검사 로직
	for (int y = 0; y != y_; y++) {
		for (int x = 0; x != x_; x++) {
			//최초로 할당된 자리 보이면 아이템 들어갈 공간 있는지 다시 검사
			if (arr[y][x] == 0) {
				for (int j = y; j != y + items_[final].get_y(); j++) {
					for (int k = x; k != x + items_[final].get_x(); k++) {
						if (arr[j][k] == 0) {
							isSpace = true;
						}
						else {
							isSpace = false;
							break;
						}
					}
					//남은 공간 없으니 다음 자리 알아보기~
					if (!isSpace) {
						break;
					}
				}
			}
			//남은 공간 찾았으니 좌표 기록하고 순회 검사 빠져나옴
			if (isSpace) {
				for (int j = y; j != y + items_[final].get_y(); j++) {
					for (int k = x; k != x + items_[final].get_x(); k++) {
						arr[j][k] = final + 1;
					}
				}
				break;
			}
		}
		if (isSpace) {
			break;
		}
	}
	return isSpace;
}

void inventory::print_inven() {
	for (int y = 0; y != y_; y++) {
		for (int x = 0; x != x_; x++) {
			//좌표에 맞는 아이템 세팅
			if (arr[y][x] != 0) {
				ColorSet(items_[arr[y][x] - 1].get_color(), black);
				printf("%c ", items_[arr[y][x] - 1].get_id());
			}
			else {
				ColorSet(black, white);
				printf("0 ");
			}
			ColorSet(black, white);
		}
		puts("");
	}
}

void inventory::remove(char id) {

	//아이템 좌표 판단 및 제거
	int item_index = remove_item(id);

	if (item_index != -1) {
		printf("Success Remove Item (id = %c Size= %dx%d)\n"
			, items_[item_index].get_id(), items_[item_index].get_x(), items_[item_index].get_y());
	}
	else {
		printf("Fail Remove Item (id = %c Size= %dx%d)\n"
			, items_[item_index].get_id(), items_[item_index].get_x(), items_[item_index].get_y());
	}

	print_inven();

	//콘솔창 출력 위한 거리
	printf("\n");
}

int inventory::remove_item(char id) {
	//아이템 순번 찾기
	int item_index = -1;
	for (int i = 0; i != items_.size(); i++) {
		if (items_[i].get_id() == id) {
			item_index = i;
			break;
		}
	}
	if (item_index != -1) {
		//인벤 순회하면서 아이템 좌표 0으로 만들기 (벡터에선 erase 안 함. 땡기지 않음)
		for (int y = 0; y != y_; y++) {
			for (int x = 0; x != x_; x++) {
				if (arr[y][x] == item_index + 1) {
					arr[y][x] = 0;
				}
			}
		}
	}
	return item_index;	//아이템 있는지
}

int main() {
	vector<item_data> items;
	inventory inven;

	inven.add(item_data('a', 3, 3, blue));
	inven.add(item_data('b', 1, 1, green));
	inven.add(item_data('c', 1, 1, skyblue));
	inven.add(item_data('d', 3, 3, red));
	inven.add(item_data('e', 1, 4, pink));
	inven.add(item_data('f', 2, 3, orange));
	inven.add(item_data('g', 2, 2, white));
	inven.add(item_data('h', 2, 2, brightpink));
	inven.remove('d');
	inven.add(item_data('i', 2, 2, lightblue));
	inven.add(item_data('j', 2, 2, breightgreen));
	inven.add(item_data('k', 2, 1, sky));
	inven.add(item_data('l', 2, 2, brightpink));
	inven.add(item_data('m', 3, 1, brightpink));

	return 0;
}