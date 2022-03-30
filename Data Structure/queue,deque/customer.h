#pragma once


struct customer {
	int id;	    // 고객 번호
	int tArrival;	// 고객의 도착한 시간
	int tService; // 이 고객의 서비스에 필요한 시간
	
	customer(int i = 0, int tArr = 0, int tServ = 0) 
		: id(i), tArrival(tArr), tService(tServ) {
	}

};