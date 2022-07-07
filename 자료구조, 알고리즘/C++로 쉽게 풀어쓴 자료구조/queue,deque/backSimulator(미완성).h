#pragma once
#include "customer.h"
#include <random>

const int randMax = 5;
class bankSimulator {
	int nSimulation;	// �Է�: ��ü �ùķ��̼� Ƚ��
	double probArrival;	// �Է�: �����ð��� �����ϴ� ��� �� ��
	int tMaxService;	// �Է�: �� ���� ���� �ִ� ���� �ð�
	int totalWaitTime;	// ���: ������ ��ٸ� ��ü�ð�
	int nCustomers;		// ���: ��ü �� ��
	int nServedCustomers;// ���: ���� ���� �� ��
	customer que;		// �� ��� ť

	// ���� ���ڸ� �����Ͽ� �� ���� ���ο� ���� �ð� �ڵ� ����
	double random() {
		return rand() / (double)randMax;
	}
	bool isNewCustomer() {
		return random() < probArrival;
	}
	int randServiceTime() {
		return (int)(tMaxService * random()) + 1;
	}
};