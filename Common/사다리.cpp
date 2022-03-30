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
		bool isHyphen = false;	//가로줄은 해당 y에서 유일하게 하기 위함

		//사다리 그리기
		for (size_t i = 0; i != height; i++) {
			for (size_t j = 0; j != player_num_; j++) {
				printf("|");
				r = rand() % player_num_;
				if (j < player_num_ - 1 && isHyphen == false && r == 1) {	//임의값 확률은 1/플레이어수
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
		//플레이어 n명
		for (size_t i = 0; i != player_num_; i++) {
			player.push_back(i);
		}
		//플레이어와 가로줄 만남 비교 규칙 (핵심)
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
		//player[order] == i번째 자리일 때 player 배열의 순서인 order를 출력
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
	std::vector<int> vertical_line;	//가로줄의 좌측 번호를 계속 넣어서 플레이어 n번째 벡터와 비교
	std::vector<int> player;	//플레이어 n번째
};


void main()
{
	srand((unsigned)time(NULL));
	//입력
	size_t player_num = 6;

	printf("참가자 수 입력(2명 이상) : ");
	scanf_s("%d", &player_num);
	while (player_num < 2) {
		printf("참가자 수는 2명 이상이어야 합니다.");
		scanf_s("%d", &player_num);
	}

	//사다리
	ladder lad(player_num);
	lad.player_num_print();
	lad.ladder_print();
	lad.ladder_player();
}