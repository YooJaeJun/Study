#pragma once


struct customer {
	int id;	    // �� ��ȣ
	int tArrival;	// ���� ������ �ð�
	int tService; // �� ���� ���񽺿� �ʿ��� �ð�
	
	customer(int i = 0, int tArr = 0, int tServ = 0) 
		: id(i), tArrival(tArr), tService(tServ) {
	}

};