#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

class ladder {
public:
	ladder(size_t player_num) : player_num_(player_num) {}

	void player_num_print() {
		for (size_t i = 0; i != player_num_; i++) {
			printf("%d\t", i);
		}
		puts("");
	}
	void ladder_print() {
		size_t r;
		bool isHyphen = false;	//�������� �ش� y���� �����ϰ� �ϱ� ����

		//��ٸ� �׸���
		for (size_t i = 0; i != height; i++) {
			for (size_t j = 0; j != player_num_; j++) {
				printf("|");
				r = rand() % player_num_;
				if (j < player_num_ - 1 && isHyphen == false && r == 1) {	//���ǰ� Ȯ���� 1/�÷��̾��
					printf("-------");
					isHyphen = true;
					vertical_line.push_back(j);
				}
				else {
					printf("\t");
				}
			}
			isHyphen = false;
			puts("");
		}
	}
	void ladder_player() {
		//�÷��̾� n��
		for (size_t i = 0; i != player_num_; i++) {
			player.push_back(i);
		}
		//�÷��̾�� ������ ���� �� ��Ģ (�ٽ�)
		for (size_t i = 0; i != player_num_; i++) {
			for (size_t j = 0; j != vertical_line.size(); j++) {
				if (player[i] == vertical_line[j]) {
					player[i]++;
				}
				else if (player[i] == vertical_line[j] + 1) {
					player[i]--;
				}
			}
		}
		//player[order] == i��° �ڸ��� �� player �迭�� ������ order�� ���
		for (size_t i = 0; i != player_num_; i++) {
			for (size_t order = 0; order != player_num_; order++) {
				if (player[order] == i) {
					printf("%d\t", order);
				}
			}
		}
	}

private:
	size_t player_num_;
	size_t height = 25;
	std::vector<int> vertical_line;	//�������� ���� ��ȣ�� ��� �־ �÷��̾� n��° ���Ϳ� ��
	std::vector<int> player;	//�÷��̾� n��°
};


void main()
{
	srand((unsigned)time(NULL));
	//�Է�
	size_t player_num = 6;

	printf("������ �� �Է�(2�� �̻�) : ");
	scanf_s("%d", &player_num);
	while (player_num < 2) {
		printf("������ ���� 2�� �̻��̾�� �մϴ�.");
		scanf_s("%d", &player_num);
	}

	//��ٸ�
	ladder lad(player_num);
	lad.player_num_print();
	lad.ladder_print();
	lad.ladder_player();
}