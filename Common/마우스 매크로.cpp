#include <Windows.h>
#include <cstdio>


POINT pt;
const int limit = 40000;
int x[limit];
int y[limit];
int sub_x[limit], sub_y[limit];
int sub_x2[limit], sub_y2[limit];
int check_mouse;
int check_mouse2;
int i;
bool is_end;

void home();
void quit();
void recording();
void play();

int main() {
	check_mouse = 2;
	check_mouse2 = 2;
	i = 0;
	system("mode con: cols=30 lines=13");
	home();
	while (true) {
		if (GetKeyState(VK_F10) < 0) {
			quit();
			return 0;
		}
		else if (GetKeyState(VK_F3) < 0) {
			recording();
		}
		else if (GetKeyState(VK_F8) < 0) {
			play();
		}

		if (is_end) {
			return 0;
		}

		Sleep(10); //Sleep(1000)�� 1����. ��, 0.01�ʸ� ��ٸ��� ���� �ö� �ݺ����� �ٽ� ���� 
	}
	return 0;
}

void home() {
	puts("");
	puts("");
	puts("");
	puts("	-----------------");
	puts("	|   F3 : ��ȭ   |");
	puts("	|   F7 : ����   |");
	puts("	|   F8 : ����   |");
	puts("	|   F10 : ����  |");
	puts("	-----------------");
}

void quit() {
	printf("���α׷��� �����մϴ�.\n");
	is_end = true;
}

void recording() {
	printf("���콺 �Է����Դϴ�.\n");

	for (i = 0; i != limit; i++) {
		x[i] = 0;
		y[i] = 0;
		sub_x[i] = 0;
		sub_y[i] = 0;
		sub_x2[i] = 0;
		sub_y2[i] = 0;
	}
	i = 0;

	while (true) {
		GetCursorPos(&pt);
		x[i] = pt.x;
		y[i] = pt.y;
		sub_x[i] = 0;	// ���ʹ�ư ������ ���� ��� �����ϴ� ��
		sub_y[i] = 0;
		i++;	//i�� �������� �ǹ�
		Sleep(10);
		if (GetKeyState(VK_LBUTTON) < 0
			&& check_mouse >= 1
			|| GetKeyState(VK_RBUTTON) < 0
			&& check_mouse2 >= 1) {	// ���ʹ�ư, ������ ��ư  ������ ��

			if (GetKeyState(VK_LBUTTON) < 0
				&& check_mouse >= 1) {
				//���ʸ� 
				sub_x[i] = x[i - 1];
				sub_y[i] = y[i - 1];
				x[i] = 5000;
				y[i] = 5000;
				check_mouse = 0;
			}
			else if (GetKeyState(VK_RBUTTON) < 0
				&& check_mouse2 >= 1) {
				//�����ʸ� 
				sub_x2[i] = x[i - 1];
				sub_y2[i] = y[i - 1];
				x[i] = 7000;
				y[i] = 7000;
				check_mouse2 = 0;
			}
			i++;
		}
		else if (GetKeyState(VK_LBUTTON) >= 0
			&& check_mouse == 0
			|| GetKeyState(VK_RBUTTON) >= 0
			&& check_mouse2 == 0) {

			// ���ʹ�ư �� ��
			if (GetKeyState(VK_LBUTTON) >= 0
				&& check_mouse == 0) {

				sub_x[i] = x[i - 1];
				sub_y[i] = y[i - 1];
				x[i] = 6000;
				y[i] = 6000;
				check_mouse = 1;
			}
			else if (GetKeyState(VK_RBUTTON) >= 0
				&& check_mouse2 == 0) {

				sub_x2[i] = x[i - 1];
				sub_y2[i] = y[i - 1];
				x[i] = 8000;
				y[i] = 8000;
				check_mouse2 = 1;
			}
			i++;
		}
		if (GetKeyState(VK_F7) < 0) {
			printf("��ȭ�� ����ϴ�.\n");
			break;
		}

		if (GetKeyState(VK_F10) < 0) {
			quit();
			break;
		}
	}
}

void play() {
	printf("������Դϴ�. \n");
	i = 0; // ������ ó������ ���ư��� ����ϱ� ���� n

	while (true) {
		switch (x[i]) {
		case 7000:	// ���ʹ�ư �������� ���� 5000�̶�� ����
			mouse_event(MOUSEEVENTF_RIGHTDOWN, sub_x2[i], sub_y2[i], 0, 0); // ��ǥ�� �°� ���ʹ�ư ������
			Sleep(1);
			break;
		case 8000:	// ���ʹ�ư ������ ���� 6000�̶�� ����
			mouse_event(MOUSEEVENTF_RIGHTUP, sub_x2[i], sub_y2[i], 0, 0);  // ��ǥ�� �°� ���ʹ�ư ����
			Sleep(1);
			break;
		case 5000:	// ���ʹ�ư �������� ���� 5000�̶�� ����
			mouse_event(MOUSEEVENTF_LEFTDOWN, sub_x[i], sub_y[i], 0, 0); // ��ǥ�� �°� ���ʹ�ư ������
			Sleep(1);
			break;
		case 6000:	// ���ʹ�ư ������ ���� 6000�̶�� ����
			mouse_event(MOUSEEVENTF_LEFTUP, sub_x[i], sub_y[i], 0, 0);  // ��ǥ�� �°� ���ʹ�ư ����
			Sleep(1);
			break;
		}

		if (x[i] == 0) { //NULL�� ������ �۵�
			i = 0; // ��, ��ũ���� ���κ����� ���� �ٽ� n = 0 ���� �Ͽ� �ٽ� ó������ ����
		}

		SetCursorPos(x[i], y[i]); // 0.01�ʸ��� ������ ���� ��ǥ�� ���콺 �̵�
		Sleep(10);//0.01�ʸ��� �ѹ��� ���� 

		i++;

		//0.01�ʸ��� ���ǹ� Ȯ�� 
		if (GetKeyState(VK_F7) < 0) {
			printf("����� ����ϴ�.\n");
			break;
		}
		if (GetKeyState(VK_F10) < 0) {
			quit();
			break;
		}
	}
}