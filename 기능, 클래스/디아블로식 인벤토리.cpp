#include <cstdio>
#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

//Į�� �ܺ� �ڷ�
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

//������
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

//�κ��丮
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
	int arr[4][10] = { 0, };	//[�ٽ�] ��ȿ ��ǥ ��� �� �Ǵ�
	int x_;
	int y_;
	vector<item_data> items_;
};
void inventory::add(const item_data item) {

	items_.push_back(item);
	int final = items_.size() - 1;
	//������ ��ȿ ��ǥ ���
	bool isSpace = check_item(final);

	if (isSpace) {
		printf("Success Add Item (id = %c Size= %dx%d)\n"
			, items_[final].get_id(), items_[final].get_x(), items_[final].get_y());
	}
	else {
		printf("Fail Add Item (id = %c Size= %dx%d)\n"
			, items_[final].get_id(), items_[final].get_x(), items_[final].get_y());
	}

	//������ ä���
	print_inven();

	//�ܼ�â ��� ���� �Ÿ�
	printf("\n");
}

bool inventory::check_item(const int final) {
	bool isSpace = false;
	//������ �� �ڸ� �ִ��� �˻� ����
	for (int y = 0; y != y_; y++) {
		for (int x = 0; x != x_; x++) {
			//���ʷ� �Ҵ�� �ڸ� ���̸� ������ �� ���� �ִ��� �ٽ� �˻�
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
					//���� ���� ������ ���� �ڸ� �˾ƺ���~
					if (!isSpace) {
						break;
					}
				}
			}
			//���� ���� ã������ ��ǥ ����ϰ� ��ȸ �˻� ��������
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
			//��ǥ�� �´� ������ ����
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

	//������ ��ǥ �Ǵ� �� ����
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

	//�ܼ�â ��� ���� �Ÿ�
	printf("\n");
}

int inventory::remove_item(char id) {
	//������ ���� ã��
	int item_index = -1;
	for (int i = 0; i != items_.size(); i++) {
		if (items_[i].get_id() == id) {
			item_index = i;
			break;
		}
	}
	if (item_index != -1) {
		//�κ� ��ȸ�ϸ鼭 ������ ��ǥ 0���� ����� (���Ϳ��� erase �� ��. ������ ����)
		for (int y = 0; y != y_; y++) {
			for (int x = 0; x != x_; x++) {
				if (arr[y][x] == item_index + 1) {
					arr[y][x] = 0;
				}
			}
		}
	}
	return item_index;	//������ �ִ���
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