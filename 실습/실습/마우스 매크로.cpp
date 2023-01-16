#include <Windows.h>
#include <cstdio>


#define RECORD VK_F2	// 녹화
#define STOP VK_F3		// 정지
#define START VK_F4		// 시작
#define EXIT VK_F5		// 종료

POINT pt;
const int limit = 40000;
int x[limit];
int y[limit];
int sub_x[limit], sub_y[limit];
int sub_x2[limit], sub_y2[limit];
int check_mouse;
int check_mouse2;
int frame;
bool is_end;

void home();
void quit();
void recording();
void play();

int main() {
	check_mouse = 2;
	check_mouse2 = 2;
	frame = 0;
	system("mode con: cols=35 lines=13");
	home();
	while (1) {
		if (GetKeyState(EXIT) < 0) {
			quit();
			return 0;
		}
		else if (GetKeyState(RECORD) < 0) {
			recording();
		}
		else if (GetKeyState(START) < 0) {
			play();
		}

		if (is_end) {
			return 0;
		}

		Sleep(10); // 0.01초
	}
	return 0;
}

void home() {
	puts("");
	puts("");
	puts("");
	puts("	-----------------");
	puts("	|   F2 : 녹화   |");
	puts("	|   F3 : 정지   |");
	puts("	|   F4 : 시작   |");
	puts("	|   F5 : 종료   |");
	puts("	-----------------");
}

void quit() {
	printf("프로그램을 종료합니다.\n");
	is_end = true;
}

void recording() {
	printf("마우스 입력중입니다.\n");

	for (frame = 0; frame != limit; frame++) {
		x[frame] = 0;
		y[frame] = 0;
		sub_x[frame] = 0;
		sub_y[frame] = 0;
		sub_x2[frame] = 0;
		sub_y2[frame] = 0;
	}
	frame = 0;

	while (true) {
		GetCursorPos(&pt);
		x[frame] = pt.x;
		y[frame] = pt.y;
		sub_x[frame] = 0;	// 왼쪽버튼 누르고 떼는 모습 저장하는 곳
		sub_y[frame] = 0;
		frame++;	// 프레임을 의미
		Sleep(10);
		if (GetKeyState(VK_LBUTTON) < 0
			&& check_mouse >= 1
			|| GetKeyState(VK_RBUTTON) < 0
			&& check_mouse2 >= 1) {	// 왼쪽버튼, 오른쪽 버튼 눌렀을 때

			if (GetKeyState(VK_LBUTTON) < 0
				&& check_mouse >= 1) {
				//왼쪽만 
				sub_x[frame] = x[frame - 1];
				sub_y[frame] = y[frame - 1];
				x[frame] = 5000;
				y[frame] = 5000;
				check_mouse = 0;
			}
			else if (GetKeyState(VK_RBUTTON) < 0
				&& check_mouse2 >= 1) {
				//오른쪽만 
				sub_x2[frame] = x[frame - 1];
				sub_y2[frame] = y[frame - 1];
				x[frame] = 7000;
				y[frame] = 7000;
				check_mouse2 = 0;
			}
			frame++;
		}
		else if (GetKeyState(VK_LBUTTON) >= 0
			&& check_mouse == 0
			|| GetKeyState(VK_RBUTTON) >= 0
			&& check_mouse2 == 0) {

			// 왼쪽버튼 뗄 때
			if (GetKeyState(VK_LBUTTON) >= 0
				&& check_mouse == 0) {

				sub_x[frame] = x[frame - 1];
				sub_y[frame] = y[frame - 1];
				x[frame] = 6000;
				y[frame] = 6000;
				check_mouse = 1;
			}
			else if (GetKeyState(VK_RBUTTON) >= 0
				&& check_mouse2 == 0) {

				sub_x2[frame] = x[frame - 1];
				sub_y2[frame] = y[frame - 1];
				x[frame] = 8000;
				y[frame] = 8000;
				check_mouse2 = 1;
			}
			frame++;
		}
		if (GetKeyState(STOP) < 0) {
			printf("녹화를 정지합니다.\n");
			break;
		}

		if (GetKeyState(EXIT) < 0) {
			quit();
			break;
		}
	}
}

void play() {
	printf("재생중입니다. \n");
	frame = 0; // 프레임 처음으로 돌아가서 재생하기 위한 n

	while (true) {
		switch (x[frame]) {
		case 7000:	// 왼쪽버튼 눌러지는 것을 5000이라고 가정
			mouse_event(MOUSEEVENTF_RIGHTDOWN, sub_x2[frame], sub_y2[frame], 0, 0); // 좌표에 맞게 왼쪽버튼 누르기
			Sleep(1);
			break;
		case 8000:	// 왼쪽버튼 떼지는 것을 6000이라고 가정
			mouse_event(MOUSEEVENTF_RIGHTUP, sub_x2[frame], sub_y2[frame], 0, 0);  // 좌표에 맞게 왼쪽버튼 떼기
			Sleep(1);
			break;
		case 5000:	// 왼쪽버튼 눌러지는 것을 5000이라고 가정
			mouse_event(MOUSEEVENTF_LEFTDOWN, sub_x[frame], sub_y[frame], 0, 0); // 좌표에 맞게 왼쪽버튼 누르기
			Sleep(1);
			break;
		case 6000:	// 왼쪽버튼 떼지는 것을 6000이라고 가정
			mouse_event(MOUSEEVENTF_LEFTUP, sub_x[frame], sub_y[frame], 0, 0);  // 좌표에 맞게 왼쪽버튼 떼기
			Sleep(1);
			break;
		}

		if (x[frame] == 0) { //NULL을 만나면 작동
			frame = 0; // 즉, 매크로의 끝부분으로 가면 다시 n = 0 으로 하여 다시 처음부터 시작
		}

		SetCursorPos(x[frame], y[frame]); // 0.01초마다 지정한 곳의 좌표로 마우스 이동
		Sleep(10); // 0.01초 

		frame++;

		//0.01초마다 조건문 확인 
		if (GetKeyState(STOP) < 0) {
			printf("재생을 멈춥니다.\n");
			break;
		}
		if (GetKeyState(EXIT) < 0) {
			quit();
			break;
		}
	}
}