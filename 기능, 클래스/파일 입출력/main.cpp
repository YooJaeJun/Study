#include <iostream>
#include <ctime>
using namespace std;

void selectionSort(int data[], int n)
{
	int smallest;

	for (int i = 0; i < n - 1; i++)
	{
		smallest = i;
		for (int j = i + 1; j < n; j++)
		{
			if (data[j] < data[smallest]) smallest = j;
		}
		swap(data[i], data[smallest]);
	}
}

int fileInput(string inputFile, int data[], int no)
{
	FILE* fp = nullptr;

	fopen_s(&fp, inputFile.c_str(), "r");

	if (fp == nullptr)
	{
		printf("파일 열기 실패");
		return 1;
	}

	for (int i = 0; i < no; i++)
	{
		fscanf_s(fp, "%d ", &data[i]);
	}
	fclose(fp);
	return 0;
}

int fileOutput(string inputFile, int data[], int no)
{
	FILE* fp = nullptr;
	fopen_s(&fp, inputFile.c_str(), "w");

	if (fp == nullptr)
	{
		printf("파일 쓰기 실패");
		return 1;
	}

	for (int i = 0; i < no; i++)
	{
		fprintf(fp, "%d ", data[i]);
	}
	fclose(fp);
	return 0;
}

int main()
{
	int data[100];
	srand(time(nullptr));

	for (int i = 0; i < 100; i++)
	{
		data[i] = rand() % 100;
	}
	fileOutput("input.txt", data, 100);

	fileInput("input.txt", data, 100);
	selectionSort(data, 100);
	fileOutput("output.txt", data, 100);
	return 0;
}