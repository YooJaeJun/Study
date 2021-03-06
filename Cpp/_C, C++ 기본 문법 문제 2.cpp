
>
int i = 어떤값;
float f = i;
여기서 발생하는 문제에 대해 설명.

ans.
float는 수의 표현범위는 크지만 정밀도가 낮다.
정수형->부동소수점형은 정밀도 문제가 엮임
i = 1231231424125; f = i; i = f; 했을 때 동일한 값이 된다는 보장이 없음

cf) 부동소수점 비트 표현 방식 : 실수를 지수부와 가수부로 나누어 기억하는 방식.
가수부는 값의 모양을 표현하며, 지수부는 10의 거듭승으로 값의 크기를 표현.
123.456 == 1.23456 * 10 ^ 2 == 1.23456e2



>
float f = 어떤값;
int i = f;
여기서 발생하는 문제에 대해 설명.

ans.
소수점 값을 잃어버림(손실)
부동소수점형->정수형은 오버플로우 문제가 엮임
cf) 가수, 지수값이 최대값을 초과할 경우 오버플로우



>
재귀 함수와 반복 문으로 구성된 함수 차이는 ?

ans.
재귀함수 : 함수가 여러 번 호출됨에 따라 메모리 할당이 부수적으로 계속 일어나는 부작용 발생.
	또한 재귀 함수의 제한을 두지 않으면 쉽게 스택오버플로우 마주



>
%d, %s, %f 같은 printf 출력함수의 문자열에 사용되는 문자들의 명칭은 ?

ans.
서식 문자


>
\n, \r, \t 같은 문자열에 사용되는 문자들의 명칭은 ?

ans.
이스케이프 문자


>
다음 연산의 결과 값은 ?
int a = 1, b = 2, c = 3;
int ans;
(1) !a - b + c;
(2) a > !b && c - 3
(3) !!!b == a || a <= c
(4) a && !b || !!c * 5
(5) a *= b || !2 == c

ans.
(1) 1
(2) 0
(3) 1
(4) 1
(5) 1

cf) 연산 우선순위
a *= b || !2 == c
결합괄호 a *= (b || !2 == c)
*= 복합대입연산이 우선순위 낮음
1 *= (1) == > 1


>
다음 연산의 결과 값은 ?
int m[2][3] = { {3,2,1} {4,5,6} };
(1) *m[1] + 2
(2) (*m + 1)[2]
(3) (*m)[1]
(4) (*(m + 2))[0]
(5) *(*m + 2)

ans.
(1) 6
(2) 6
(3) 4
(4) 알 수 없는 값(6 다음 주소에 있는 값)
(5) 1



>
#define NUM1 4
const int NUM2 = 4;

NUM1과 NUM2의 차이는 ?

ans.
const : 스코프 영향을 받기 때문에 이름의 충돌이 나지 않는다.
#매크로 : 전처리기의 동작이 기계적인 치환으로, 스코프의 영향을 받아 충돌
ex. {
#define a 1
	{
		const int a = 2;
		{
			const int a = 3;
			std::cout << a << std::endl;
		}}}



>
class A {
public:
	A() {}
	~A() {}
	virtual void func() = 0;
};

class B : public A {
public:
	B() { }
	void func() {
		printf("hello world");
	}
};

class C : public A {
public:
	C() { }
	void func2() {
		printf("fucking");
		func();
	}
	void func() {

	}
};

int main() {
	A* a = new B;
	a->func();
	C* c = a;
	c->func();
	delete a;
}

발생할 수 있는 모든 문제에 대해 설명하고, 수정.

ans.
1 C* c에서 다운 캐스팅.자식 타입 포인터가 부모 타입 포인터를 받음(부모 클래스가 자식 클래스의 멤버를 모를 경우 에러)
cf) 업 캐스팅은 항상 안전한 이유 : 부모 타입 객체가 가리키는 멤버는 항상 자식 타입에 포함되어 있기 때문
2 B의 소멸자를 재정의하지 않았기 때문에 B의 소멸자에 어떤 리소스를 처리하는 객체가 있었다면 문제

cf) 순수 가상 함수 : 파생 클래스에서 반드시 재정의해야 하는 함수.
하나 이상의 순수 가상 함수를 가지는 클래스를 추상 클래스라고 함.
추상 클래스는 너무 일반적인 대상을 표현하기 때문에 어떠한 정보도, 동작도 정의할 수 없으며 이런 타입의 객체를 생성하는 것은 의미 없음.
추상 클래스를 정의하는 이유는 클래스의 공동 조상이 되어 객체들의 집합을 관리하기 위해 필요.

추상 클래스의 역할 : 다형적인 함수의 집합을 정의함.
예시로 도형이 되기 위해 꼭 필요한 함수의 집합을 추상 클래스에 순수 가상 함수로 선언해 두면, 이 클래스로부터 파생되는 도형 클래스는
이 가상 함수를 반드시 재정의해야 한다는 의무가 생긴다. (위 예제의 소멸자)
파생 클래스가 추상 클래스의 순수 가상 함수를 재정의하지 않는다면 이 클래스도 여전히 추상 클래스이므로 인스턴스를 생성할 수 없음.



>
C - style 캐스팅과 C++캐스팅과 차이점.

ans.
논리적으로 변환 가능한 타입을 받는 캐스팅 유형들이 있다.
포인터끼리 상속 관계에서 다운 캐스팅을 받을 수 있다.
다운 캐스팅 시 에러를 뱉는 유형의 캐스팅이 있다.


>
왜 C++캐스팅을 써야 하는가 ?

ans.
C++에서는 C스타일 캐스팅이 각자에 맞는 캐스팅으로 해줌
ex.dynamic_cast가 필요한 상황이면 자동으로 해줌.
다만 미기입 시 의도가 명확하게 보이지 않다는 게 문제.



>
static_cast와 dynamic_cast의 차이점

ans.
둘 다 논리적으로 변환 가능한 관계 및 포인터끼리는 상속 관계를 캐스팅 할 수 있지만,
staic_cast : 자식 타입 포인터가 부모 타입 포인터를 받는 다운 캐스팅 시 모두 허용(위험 내포)
	dynamic_cast : 안전한 것만 허용(부모 클래스가 자식 클래스 멤버를 모두 아는 상황)

	(수정)
	static_cast는 컴파일타임 체크 밖에 안 함. (예시로 상속관계가 맞으면 캐스팅 해줌)
	dynamic_cast는 실제로 생성된 객체가 런타임 중 어떤 타입인지 판단해서 캐스팅 해줌.vtable을 참조해서..



>
벡터 vs 리스트 차이
벡터는 요소 간 메모리 연속성이 있지만, 리스트는 요소 간 메모리 연속성이 없다.
벡터는 반복자 앞의 요소가 삽입, 삭제될 경우 순번이 변경되기 때문에 반복자가 무효화 된다.
반면 리스트는 요소 간 삽입, 삭제되도 무결성을 해치지 않아 반복자가 무효화되지 않는다.
삽입, 삭제 시 시간 복잡도 면에서 리스트가 빠르다.


