#include <iostream>
using namespace std;

//#include "Test.h"
//#include "Test2.h"

import math;
// import math.time;

// 전체 사용해야 함 (서브 모듈 사용 안 됨)
import MathPartition;

int main()
{
	// 전처리
	// - #include #define
	// 컴파일
	// - 오브젝트 파일 .obj
	// 링크
	
	// 기존에 사용하던 방법의 문제점
	// 1) 빌드 속도 (반복된 substitution)
	// 너무 너무 느리다
	// 2) 매크로 (#define)
	// 3) 심볼 중복 정의
	// const int test = NUM;

	// Module
	// - 모듈은 딱 한 번만 import 된다
	// - import 순서에 상관 없음
	// - 심볼 중복 정의
	// - 모듈의 이름도 지정 가능
	// - 인터페이스/구현부 분리 관리할 필요 없음


	//int sum = Add(1, 2);
	//TestExport();
	//math::TestExport2();

	MathTimeFunc();

	MyFunc1();
	MyFunc2();
}