#pragma once
#include "customer.h"
#include <random>

const int randMax = 5;
class bankSimulator {
	int nSimulation;	// 입력: 전체 시뮬레이션 횟수
	double probArrival;	// 입력: 단위시간에 도착하는 평균 고객 수
	int tMaxService;	// 입력: 한 고객에 대한 최대 서비스 시간
	int totalWaitTime;	// 결과: 고객들이 기다린 전체시간
	int nCustomers;		// 결과: 전체 고객 수
	int nServedCustomers;// 결과: 서비스 받은 고객 수
	customer que;		// 고객 대기 큐

	// 랜덤 숫자를 생성하여 고객 도착 여부와 서비스 시간 자동 생성
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