// 영역 채색 프로그램
#include <iostream>

const int width = 20;
const int height = 9;

void labelComponent(unsigned char img[height][width], int x, int y, int label) {
	if (x < 0 || y < 0 || x >= width || y >= height) {
		return;
	}
	if (img[y][x] == 9) {	
		img[y][x] = label;
		labelComponent(img, x - 1, y, label);
		labelComponent(img, x, y - 1, label);
		labelComponent(img, x + 1, y, label);
		labelComponent(img, x, y + 1, label);
	}
}

// 이진 영상의 영역 채색(blob coloring) 함수
void blobColoring(unsigned char img[height][width]) {
	int label = 1;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (img[y][x] == 9) {
				labelComponent(img, x, y, label++);
			}
		}
	}
}

// 영상의 화소 값을 화면에 출력하는 함수
void printImage(unsigned char img[height][width], const char* msg) {
	printf("%s\n", msg);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (img[y][x] == 0) {
				printf(".");
			}
			else {
				printf("%-1d", img[y][x]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

void main() {
	// 입력 영상 : 자료
	unsigned char image[height][width] = {
		0,0,0,0,0,0,9,0,0,0,0,9,9,9,9,9,0,0,9,9,
		0,9,9,9,0,0,0,0,0,0,0,9,9,9,9,9,0,0,0,0,
		0,0,0,0,0,0,0,9,9,9,9,9,9,9,9,9,0,0,0,0,
	};
	printImage(image, "<Original image>");
	blobColoring(image);
	printImage(image, "<Labelled image>");
}