다음 식에서 결과 값을 작성하시오. (10진수로 작성)
1.
int result = (1 << 2) & 2;

ans: result의 값은 ?
	ans : result == 0

	solve :
	1 * 2 ^ 2 = 4
	//쉬프트 연산 이진수 왼쪽으로 요소 두 칸씩 이동
	4 & 2
	이진수로 100 & (비트곱)010 == 000


	2.
	int a = 0x7FF;
	 int b = 0x7;
	 int result = a & (b << 2);

 ans: result의 값은 ?
	 ans : result == (2진수) 11100 (10진수) 30

	 solve :
	 0x7FF == 이진수로 0111 1111 1111
	 0x7 == 이진수로 0111
	 0x7 << (쉬프트)2 == 0001 1100
	 0111 1111 1111 & (비트곱)0001 1100
	 == 11100


	 3.
	 int a = 0;
	  int b = 1;
	  int c = 2;
	  int result = a++ && --b || c++;

  ans: result, a, b, c 의 값은 ?
	  ans :
	  result == 1
	  a == 1
	  b == 1
	  c == 3

	  solve :
	  A && B || C의 구조다.
	  &&는 앞이 false면 뒤 수행 안 한다. (숏 서킷)
	  ((A&&B) || C)로 묶어준다.
	  || 는 앞이 true면 뒤 수행 안 한다. (숏 서킷)
	  result가 0이니 false로 판단되어 --b 무시함.
	  뒤 c++실행.

	  (비트 연산이었을 경우)
	  result == 2
	  a == 1
	  b == 0
	  c == 3

	  solve:
	   result = 0(후위) && 0(전위) || 2(후위)
		   result = 0 || 2
		   result = (이진수)00 || 10
		   이진수 10


		   4.
		   void* a = (int*)2;
	   char* b = (char*)a;
	   b += 3;
	   int* c = (int*)b;
	   c++;
	   int result = (int)c;

   ans: result의 값은 ?
	   ans : 9

	   solve :
	   a == 0x00000002
	   c == b == 0x00000005 (주소값도 정수 형태의 변수)
	   c++ == 0x00000009
	   //0x00000005에서 32bit에서 포인터 변수의 타입 크기인 4칸(4바이트) 이동 (크기는 항상 동일)
	   result = 9


	   5.
#pragma pack(4)
	   struct temp {
	   int a;
	   char b;
	   int c;
   };

		int result = sizeof(temp);
	ans: result의 값은 ?
		ans : result == 12

		solve :
#pragma 지시자: 플랫폼 별로 고유한 기능에 대한 지시 사항을 컴파일러에 전달하는 방법
#pragma pack(n): 이후부터 선언되는 구조체의 정렬 방식을 지정 
		구조체의 크기는 변수 중 크기가 가장 큰 타입을 기준으로 배수만큼 커져 메모리 낭비를 초래하기 때문에 사용.

		위 문제 : int 4바이트 / int 4바이트 / char 1바이트
		지시자 없을 경우 제일 큰 int 변수 크기만큼 4 * 3 = 12
		pack(n)은 변수 별 멤버 내 최대 타입 크기(int 4바이트)를 넘지 않는 선에서만 n바이트를 추가 할당.
		Ex.
		pack()은 디폴트 12
		pack(1)은 9
		pack(3), pack(4)... 은 12


		6.
		struct temp {
		int a = 1;
		int b = 2;
		int c = 3;
	};

		 temp t;
		 int* p = (int*)&t;
		 *++p = 3;

	 ans: t의 각 멤버들의 값은 ?
		 ans : { 1, 3, 3 }

	  solve:
		  *++p = 3;
		  타입의 크기만큼 더한 주소를 가리킴, 즉 다음 번째 변수를 가리킴.
			  전위 증감 연산이니 1번째 요소에 + 1



			  문장을 보고 왜 틀렸는지 서술하시오.
			  1.
			  int func(const int value, int a) {
			  int arr[value]{};
			  int size_ = sizeof(arr) / sizeof(int);
			  for (int i = 0; i != size_; ++i) {
				  arr[i] = i;
			  }
			  return *arr + a;
		  }

	  ans:
		  배열의 크기는 컴파일타임 상수에서 가능
			  함수 파라미터로 전달되는 값은 런타임(컴파일 끝내고 프로그램 실행중)에 결정됨.
			  하여, 컴파일타임에 스택에 배열의 크기만큼 메모리를 할당할 때 얼마나 할당할지 값을 알 수 없어 컴파일 에러.

			  추가로, C에서 const는 항상 런타임 상수. const 변수 선언 후 변수를 배열 첨자 내에 넣는 것이 불가능.
			  (C 이후 다른 컴파일러 버전에서는 파라미터를 통해 전달된 값을 통해서 배열 크기를 할당받을 수 있게 됨.다만 MSVC에선 C++ 친화적이라 여전히 안됨)
			  C++에서 const는 맥락에 따라 컴파일 상수가 될 수도(const 변수 선언), 런타임 상수(const 변수가 다른 변수를 대입)가 될 수도 있다.
			  C++에서 constexpr은 항상 컴파일타임 상수.


			  2.
			  int* func(unsigned char c) {
			  int arr[255]{ 1,2,3,4,5,6 };
			  return arr + c;
		  }

	  ans:
		  함수의 몸체를 빠져나가며 arr의 값들이 소멸하여 arr은 댕글링 포인터
			  댕글링 포인터란, 어떤 포인터가 할당된 객체의 주소를 가리키고 있었는데, 그 객체의 메모리가 해제되었음에도 여전히 가리키고 있는 포인터


			  3.
			  class A {
			  private:
				  int a;
			  protected:
				  int b;
			  public:
				  int c;
		  };

		  class B : protected A {
		  public:
			  int b;
			  int d;
		  };

		  B b;
		  b.b = 20; b.c = 10;

	  ans:
		  protected 상속은 파생 클래스에서만 액세스가 허용됨.
			  main에서 protected 멤버에 접근할 수 없음.



			  1.
			  해당 연산자가 가지고 있는 명칭을 작성.
			  1.[]
			  2. ==
			  3. *
			  4. ^
			  5. &
			  6. !

			  ans:
		  1[] 배열 첨자
			  2 == 논리 연산자 중 상등 연산자
			  3 * 산술 연산자 중 곱 / 역참조 연산자
			  4 ^ 비트 XOR 연산자
			  5 & 비트 AND 연산자 / 주소 연산자(address of)
			  6 !논리 부정(Not)

			  (추가)
			  && 논리곱(And)
			  || 논리합(Or)
			  ~비트 부정(Not)


			  2.
			  명시적 변환에 대해서 설명.
			  자동으로 변환되는 묵시적 변환과 달리 캐스팅 등으로 형변환시키는 데 사용

			  3.
			  클래스에 제공되는 기본 함수를 설명.
			  생성자, 소멸자, 복사 생성자, 복사 대입 연산자, 이동 생성자, 이동 대입 연산자

			  4.
			  얕은 복사에 대해서 설명.
			  대입 연산자로 단순 대입하여 구조체(클래스)의 사본을 만드는 것
			  정수나 실수 따위의 단순 타입은 얕은 복사로도 완전한 사본을 만들 수 있지만,
			  포인터 변수를 그대로 복사할 경우 대입에 의해 똑같은 주소를 가지게 된다.
			  즉, 포인터 변수가 가리키는 변수의 값이 변할 경우 얕은 복사된 사본이 가리키는 값이 변경되는 것.

			  5.
			  숏서킷에 대해서 설명.
			  불필요한 연산을 하지 않도록 앞의 식으로 이미 결정난 값일 경우 나머지 식은 생략하는 컴파일러의 기능
			  ex. if (a > 3 || a == 9) 일 때 앞의 식 true면 a == 9 무시하고 즉시 다음 식으로 넘어감



			  ------------------ -
			  ------------------ -
			  1. vector와 list의 차이점
			  한 번에 2칸 이상 인접 요소에 접근 불가능(advance가 불가능)

			  2. auto 동작 방식 : 우측에 오는 값의 타입이 추론되서 컴파일타임에 정해진다.
			  decay / decltype


