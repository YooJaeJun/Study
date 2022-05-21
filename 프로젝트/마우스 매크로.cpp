#include <Windows.h>
#include <cstdio>


#define RECORD VK_F2	// ��ȭ
#define STOP VK_F3		// ����
#define START VK_F4		// ����
#define EXIT VK_F5		// ����

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

		Sleep(10); // 0.01��
	}
	return 0;
}

void home() {
	puts("");
	puts("");
	puts("");
	puts("	-----------------");
	puts("	|   F2 : ��ȭ   |");
	puts("	|   F3 : ����   |");
	puts("	|   F4 : ����   |");
	puts("	|   F5 : ����   |");
	puts("	-----------------");
}

void quit() {
	printf("���α׷��� �����մϴ�.\n");
	is_end = true;
}

void recording() {
	printf("���콺 �Է����Դϴ�.\n");

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
		sub_x[frame] = 0;	// ���ʹ�ư ������ ���� ��� �����ϴ� ��
		sub_y[frame] = 0;
		frame++;	// �������� �ǹ�
		Sleep(10);
		if (GetKeyState(VK_LBUTTON) < 0
			&& check_mouse >= 1
			|| GetKeyState(VK_RBUTTON) < 0
			&& check_mouse2 >= 1) {	// ���ʹ�ư, ������ ��ư ������ ��

			if (GetKeyState(VK_LBUTTON) < 0
				&& check_mouse >= 1) {
				//���ʸ� 
				sub_x[frame] = x[frame - 1];
				sub_y[frame] = y[frame - 1];
				x[frame] = 5000;
				y[frame] = 5000;
				check_mouse = 0;
			}
			else if (GetKeyState(VK_RBUTTON) < 0
				&& check_mouse2 >= 1) {
				//�����ʸ� 
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

			// ���ʹ�ư �� ��
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
			printf("��ȭ�� �����մϴ�.\n");
			break;
		}

		if (GetKeyState(EXIT) < 0) {
			quit();
			break;
		}
	}
}

void play() {
	printf("������Դϴ�. \n");
	frame = 0; // ������ ó������ ���ư��� ����ϱ� ���� n

	while (true) {
		switch (x[frame]) {
		case 7000:	// ���ʹ�ư �������� ���� 5000�̶�� ����
			mouse_event(MOUSEEVENTF_RIGHTDOWN, sub_x2[frame], sub_y2[frame], 0, 0); // ��ǥ�� �°� ���ʹ�ư ������
			Sleep(1);
			break;
		case 8000:	// ���ʹ�ư ������ ���� 6000�̶�� ����
			mouse_event(MOUSEEVENTF_RIGHTUP, sub_x2[frame], sub_y2[frame], 0, 0);  // ��ǥ�� �°� ���ʹ�ư ����
			Sleep(1);
			break;
		case 5000:	// ���ʹ�ư �������� ���� 5000�̶�� ����
			mouse_event(MOUSEEVENTF_LEFTDOWN, sub_x[frame], sub_y[frame], 0, 0); // ��ǥ�� �°� ���ʹ�ư ������
			Sleep(1);
			break;
		case 6000:	// ���ʹ�ư ������ ���� 6000�̶�� ����
			mouse_event(MOUSEEVENTF_LEFTUP, sub_x[frame], sub_y[frame], 0, 0);  // ��ǥ�� �°� ���ʹ�ư ����
			Sleep(1);
			break;
		}

		if (x[frame] == 0) { //NULL�� ������ �۵�
			frame = 0; // ��, ��ũ���� ���κ����� ���� �ٽ� n = 0 ���� �Ͽ� �ٽ� ó������ ����
		}

		SetCursorPos(x[frame], y[frame]); // 0.01�ʸ��� ������ ���� ��ǥ�� ���콺 �̵�
		Sleep(10); // 0.01�� 

		frame++;

		//0.01�ʸ��� ���ǹ� Ȯ�� 
		if (GetKeyState(STOP) < 0) {
			printf("����� ����ϴ�.\n");
			break;
		}
		if (GetKeyState(EXIT) < 0) {
			quit();
			break;
		}
	}
}