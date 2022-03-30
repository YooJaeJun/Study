#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <mutex>
#include <iterator>
#include <algorithm>
using namespace std;

용어정리

implementaion 구현환경
표준 명세를 구현하여 만든, 프로그램의 번역을 수행하고 함수의 실행을 지원하는 개발 환경으로,
특별한 제어 옵션 아래에서 실행되는 프로그램 개발 소프트웨어(컴파일러, 링커, 표준라이브러리, 운영체제)의 집합
'표준을 구현한 개발환경', '프로그램 제작'

undefined 미정의 사항, 정의되지 않은
표준에서 undefined는 이식성이 없거나 잘못된 프로그램 구조 혹은 에러가 있는 데이터나 값이 불확실한 개체의 사용에 의존하는 동작(behavior)

implementation - defined 구현별 정의 사항, 구현별 의존사항
표준에서는 정확히 한 가지를 정하지 않고 여러 가지 가능성을 제시하며, 구현에 따라 다르게 결정되는 사항




항목 1 : C++를 언어의 연합체로 바라보자!

	C / 객체 지향 개념의 C++ / 템플릿 C++ / STL;




항목 2: #define을 쓰려거든 const, enum, inline 을 떠올리자!

포인터와 함께 쓰일 경우 const 포인터 사용;
const char * const authorName = "d";
문자열은 보통 std의 string 사용;
const std::string authorName("d");

클래스 멤버로 상수를 정의하는 경우
어떤 상수의 유효범위를 클래스로 한정하고자 할 때는 그 상수를 멤버로 만들어야 하는데,
그 상수의 사본 개수가 한 개를 넘지 못하게 하고 싶다면 정적(static) 멤버로 만들어야 함.;
class GamePlayer {
private:
	static const int NumTurns = 5;
	int scores[NumTurns];
};
클래스 상수의 정의는 구현 파일에 두고, 헤더 파일에 두지 않음.
정의에는 상수의 초기값이 있으면 안됨.클래스 상수의 초기값은 해당 상수가 선언된 시점에 바로 주어지기 때문.;


"enum hack" 기법
나열자(enumerator)의 타입의 값은 int가 놓일 곳에도 쓸 수 있다는 점을 확용한 기법
정수 타입이 정적 클래스 상수에 대한 클래스 내 초기화를 금지하는 구식 컴파일러에서 괜찮은 기법(텍스트 rpg 때 사용했음);
class GamePlayer {
private:
	enum { NumTurns = 5 };
	int scores[NumTurns];
};
const나 #define 메모리 할당하는 일을 안 함;


매크로의 단점
#define CALL_WITH_MAX(a, b) ((nodes) > (b) ? (nodes) : (b))
void main() {
	int a = 5, b = 0;
	CALL_WITH_MAX(++a, b);	//a가 두 번 증가함
	CALL_WITH_MAX(++nodes, b + 10);
}
안정성 확보!인라인 함수에 대한 템플릿;
template<typename T>
inline void callWithMax(const T& a, const T& b) {
	f(a > b ? a : b);	//본문 코드와 달리 f는 빠져야 컴파일 됨.
}
const, enum, inline을 사용하면 선행 처리자(특히 #define)을 쓰는 일 줄어듦
단순한 상수 = > const 객체 or enum
함수처럼 쓰이는 매크로 = > 인라인 함수;




항목 3: 낌새만 보이면 const를 들이대 보자!

const char * p = greeting;	//비상수 포인터, 상수 데이터
char * const p = greeting;	//상수 포인터, 비상수 데이터
단, 포인터가 가리키는 대상을 상수로 만들 때, const 사용 스타일이 조금씩 다르나,
다음 매개변수 타입은 모두 똑같음;
void f1(const Widget *pw);
void f2(Widget const *pw);

std::vector<int> vec;
//...
const std::vector<int>::iterator iter = vec.begin();	//상수 데이터인 것처럼 보임
*iter = 10;
++iter; //에러. iter는 상수
std::vector<int>::const_iterator cIter = vec.begin();	//상수 포인터인 것처럼 보임
*cIter = 10;	//에러. *cIter는 상수.
++cIter;

함수 반환 값 상수;
class Rational {};
const Rational operator*(const Rational& lhs, const Rational& rhs);
반환 값이 상수 객체일 이유 ?
다음 실수 방지
Rational a, b, c;
(nodes * b) = c;

상수 멤버 함수
const 키워드의 역할은 해당 멤버 함수가 상수 객체에 대해 호출될 함수다.
그 클래스로 만들어진 객체를 변경할 수 있는 함수는 무엇이고, 또 변경할 수 없는 함수는 무엇인가를 사용자가 알아야 함;
class TextBlock {
public:
	//...
	const char& operator[](std::size_t position) const
	{ return text[position]; }
	char& operator[](std::size_t position)
	{ return text[position]; }
private:
	std::string text;
};
void print(const TextBlock& ctb) {
	TextBlock tb("Hello");
	std::cout << tb[0];		//비상수 멤버 호출
	const TextBlock ctb("World");
	tb[0] = 'x';
	ctb[0] = 'x';	//에러. 상수 버전의 객체에 쓰기 안됨.
}
operator[]의 비상수 멤버는 char의 참조자!를 반환;


어떤 멤버 함수가 상수 멤버라는 의미
1 비트수준 상수성
	그 객체의 어떤 데이터 멤버도 건드리지 않아야 함(정적 멤버는 제외)
	다만 문제;
//...
char& operator[](std::size_t position) const {
	return pText[position];
}
//...
const CTextBlock cctb("Hello");
char *pc = &cctb[0];
*pc = 'J';	//상수를 의도했음에도 값이 변경됨

2 논리적 상수성
	객체 일부 몇 비트 정도는 바꿀 수 있되, 사용자측에서 알아채지 못하게만 하면 상수의 멤버 자격이 있다는 것
	mutable : 비정적 데이터 멤버를 비트수준 상수성의 족쇄에서 풀어주는 키워드;
	
class CTextBlock {
	public:
		//...
		std::size_t length() const;
	private:
		char *pText;

		mutable std::size_t  textlength;	//이 데이터 멤버들은 어떤 순간에도 수정 가능
		mutable bool lengthIsValid;

		std::size_t length() const {
			if (!lengthIsValid) {
				textlength = std::strlen(pText);
				lengthIsValid = true;
			}
			return textlength;
		}
};


상수, 비상수 버전 함수를 2개 만들 때 중복을 줄이는 방법 (상수 멤버 쌍둥이 사용 기법)
class TextBlock {
public:
	const char& operator[](std::size_t position) const {
		//...
		return text[position];
	}
	char& operator[](std::size_t position) {	//상수 버전 op[]를 호출하고 끝
		return
			const_cast<char&> (	//op의 반환 타입에 캐스팅을 적용, const를 떼어냅니다.
				static_cast<const TextBlock&>	//*this의 타입에 const를 붙입니다.
				(*this)[position]	//op[]의 상수 버전을 호출합니다.
				);
	}
};
위 코드에서 캐스팅 2가지
1 * this에 const 붙이는 캐스팅
2 operator[]의 반환값에서 const를 떼어내는 캐스팅

잊지 말쟈
const 를 붙여 선언하면 컴파일러가 에러 잡아줌
컴파일러는 비트수준 상수성 지키면 허용, 우리가 논리적 상수성 이용해야 함
상수 멤버, 비상수 멤버 함수가 똑같으면 비상수 버전이 상수 버전을 호출




항목 4 : 객체를 사용하기 전에 반드시 그 객체를 초기화하자!

생성자에서 그 객체의 모든 것을 초기화하자
대신 대입을 초기화와 헷갈리지 않기;
class PhoneNumber { /*...*/ };
class ABEntry {	
public:
	ABEntry(const string& name, const string& address,
		const list<PhoneNumber>& phones);
private:
	string theName;
	string theAddress;
	list<PhoneNumber> thePhones;
	int numTimesConsulted;
};
ABEntry::ABEntry(const string& name, const string& address,
	const list<PhoneNumber>& phones)
	: theName(name), theAddress(address), thePhones(phones), numTimesConsulted(0)
	{	/*여기서 대입하는 건 초기화가 아님슨*/	}

초기화 리스트에 들어가는 인자는 바로 데이터 멤버에 대한 생성자의 인자로 쓰임

	매개변수 없는 생성자가 클래스에 들어있었다면..
	ABEntry::ABEntry()
	: theName(), theAddress(), thePhones()
	, numTimesConsulted(0) //명시적으로 0으로 초기화
	{}
기본 생성자를 호출해서 쓸 필요 없다고만 생각하지 말기
어떤 멤버가 초기화되지 않을 수 있다는 사실 파악 가능

멤버 초기화 리스트에 넣는 멤버들의 순서도 클래스에 선언한 순서와 동일하게 맞춰주기;


비지역 정적 객체의 초기화 순서는 개별 번역 단위에서 정해진다 ? 의미

정적 객체(static object)는 자신이 생성된 시점부터 프로그램이 끝날 때까지 살아있는 객체.
스택 객체 및 힙 객체는 정적 객체가 아님.
정적 객체 범주
1 전역 객체
2 네임스페이스 유효범위에서 정의된 객체
3 클래스 안에서 static 으로 선언된 객체
4 함수 안에서 static 으로 선언된 객체
5 파일 유효범위에서 static 으로 정의된 객체
이들 중 함수 안에 있는 정적 객체 == > 지역 정적 객체(local static object)
나머지는 비지역 정적 객체(non - local static object)

번역 단위(translation unit)은 컴파일을 통해 하나의 목적 파일(object file)을 만드는 바탕이 되는 소스 코드
번역은 소스의 언어를 기계어로 옮긴다는 의미
#include하는 파일(들)까지 합쳐서 하나의 번역 단위.

별개의 번역 단위에서 정의된 비지역 정적 객체들의 초기화 순서는 정해져 있지 않다.;

class FileSystem {	//만들어져 있는 클래스
public:
	//...
	std::size_t numDisks() const;
};
extern FileSystem tfs;

class Directory {	//사용자가 만들었다고 가정
public:
	Directory(params);
	//...
};
Directory::Directory(params) {
	//...
	std::size_t disks = tfs.numDisks();	//tfs 객체를 여기서 사용함
};
Directory tempDir(params);

위 코드에서 tfs가 tempDir보다 먼저 초기화되지 않으면,
tempDir의 생성자는 tfs가 초기화되지도 않았는데 tfs를 사용하려고 할 것
tfs와 tempDir은 제작자도 다르고 만들어진 시기도, 소스 파일도 다르다~
== 다른 번역 단위 안에서 정의된 비지역 정적 객체

tempDir 전에 tfs가 초기화 하고 싶다 ?
지금 안됨.서로 다른 번역 단위에 정의된 비지역 정적 객체들 사이의 상대적인 초기화 순서는 정해져 있지 않다.
다른 해결책 : 비지역 정적 객체를 하나씩 맡는 함수를 준비하고 이 안에 각 객체를 넣자.
비지역 정적 객체를 직접 참고하지 않고 함수 호출로 대신함.
Singleton pattern 구현양식;

class FileSystem {/*...*/ };

FileSystem& tfs() {		//tfs 객체를 이 함수로 대신. 클래스 안에 정적 멤버로 들어가도 됨
	static FileSystem fs;	//지역 정적 객체를 정의하고 초기화.
	return fs;	//객체에 대한 참조자 반환.
}
;
class Directory {/*...*/ };

Directory::Directory(params) {
	//...
	std::size_t disks = tfs.numDisks();
}
;
Directory& tempDir() {		//tempDir 객체를 이 함수로 대신함. Directory 클래스의 정적 멤버로 들어가도 됨
	static Directory td;		//지역 정적 객체를 정의/초기화.
	return td;		//이 객체에 대한 참조자를 반환.
}
단, 참조자 반환 함수는 내부적으로 정적 객체를 쓰기 때문에,
다중스레드 시스템에서는 동작에 장애가 생길 수 있음.

비상수 정적 객체는 골칫거리.
다중 스레드 돌입 전 시동 단계에서 참조자 반환 함수를 전부 손으로 호출해줘야 함.;

잊지 말자!
1 기본 제공 타입의 객체는 직접 초기화.
2 생상자에서는, 멤버 초기화 리스트 즐겨 사용.
	초기화 리스트에 데이터 멤버 나열 시, 클래스에 각 데이터 멤버가 선언된 순서와 똑같이 나열
3 여러 번역 단위에 있는 비지역 정적 객체들의 초기화 순서 문제는 피해서 설계.
	비지역 정적 객체를 지역 정적 객체로 바꾸자.;




항목 5: C++가 은근슬쩍 만들어 호출해 버리는 함수들에 촉각을 세우자!

컴파일러 자동 기본형 선언 : 생성자, 복사 생성자, 복사 대입 연산자, 소멸자
class Empty {};
Empty e1;	//기본 생성자, 소멸자
Empty e2(e1);	//복사 생성자
e2 = e1;	//복사 대입 연산자

template<typename T>
class NamedObeject {
public:
	NamedObject(const char *name, const T& value);
	NamedObject(const std::string& name, const T& value);
private:
	std::string nameValue;
	T objectValue;
};
NamedObject<int> no1("Smallest Prime Number", 2);
NamedObject<int> no2(no1);	//복사 생성자 호출

template<class T>
class Named Object {
public:
	//이 생성자는 이제 상수 타입의 name을 취하지 않습니다. nameVlue가 비상수 string의 참조자가 되었기 때문입니다.
	//참조할 string을 가져야 하기 때문에 char*는 없애버렸습니다.
	NamedObject(std::string& name, const T& value);
	//위의 경우와 마찬가지로 operator=는 선언된 게 없다고 가정
private:
	std::string& nameValue;	//이제 이 멤버는 참조자
	const T objectValue;	//이제 이 멤버는 상수
};
std::string newDog("Persephone");
std::string oldDog("Satch");
NamedObject<int> p(newDog, 2);
NamedObject<int> s(oldDog, 36);
p = s;
컴파일 거부.클래스에 대입 연산을 지원하려면 직접 복사 대입 연산자 정의.
private으로 선언 시에는 여전히 거부

잊지 말자!
컴파일러는 경우에 따라 클래스에 대해 기본 생성자, 복사 생성자, 복사 대입 연산자, 소멸자를 암시적으로 만들어 놓을 수 있습니다.




항목 6: 컴파일러가 만들어낸 함수가 필요 없으면 확실히 이들의 사용을 금해 버리자

복사를 막고 싶은 경우, ;
class HomeForSale {/*...*/ };
HomeForSale h1;
HomeForSale h2;
HomeForSale h3(h1);	//하면 안 되는 동작
h1 = h2;	//하면 안 되는 동작
이때 private으로 선언하면 컴파일러가 기본 버전을 만들지도 않고 비공개의 접근성을 가진다.
단, 프렌드 함수 및 멤버 함수에서 호출될 허점 있음.

해결책;
class HomeForSale {
public:
private:
	HomeForSale(const HomeForSale&);
	HomeForSale& operator=(const HomeForSale&);
};
매개변수를 기재하지 않은 상태로 선언
객체 복사 시도 시 컴파일러 에러
멤버 함수 혹은 프렌드 함수에서 복사 시도 시 링커에서 에러

링크 시점 에러를 컴파일 시점 에러로 옮기기
파생 클래스 상속
class Uncopyable {
protected:	//파생된 객체에 대해 생성과 소멸은 허용
	Uncopyable() {}
	~Uncopyable() {}
private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);	//복사는 방지
};

class HomeForSale : private Uncopyable {
	/*...*/	//복사 생성자도, 복사 대입 연산자도 이제 선언되지 않음
}

(스캔본 가려진 내용 있음)

잊지 말자!
컴파일러에서 자동으로 제공하는 기능을 허용치 않으려면,
대응되는 멤버 함수를 private으로 선언한 후에 구현은 하지 않은 채로 두기.
Uncopyable과 비슷한 기본 클래스를 쓰는 것도 한 방법.;




항목 7: 다형성을 가진 기본 클래스에서는 소멸자를 반드시 가상 소멸자로 선언하자!;

class TimeKeeper {
public:
	TimeKeeper();
	~TimeKeeper();
};
class AtomicClock : public TimeKeeper {};
class WaterClock : public TimeKeeper {};
class WristWatch : public TimeKeeper {};

팩토리 함수 : 새로 생성된 파생 클래스 객체에 대한 기본 클래스 포인터를 반환하는 함수;
TimeKeeper* getTimeKeeper();	//TimeKeeper에서 파생된 클래스를 통해 동적으로 할당된 객체의 포인터를 반환합니다.
TimeKeeper *ptk = getTimeKeeper();	//TimeKeeper 클래스 계통으로 부터 동적으로 할당된 객체를 얻습니다.
/*...*/		//객체 사용
delete ptk;		//자원 누출을 막기 위해 해제(삭제)

c++규정 중 기본 클래스 포인터를 통해 파생 클래스 객체가 삭제될 때
그 기본 클래스에 비가상 소멸자가 들어 있으면, 프로그램 동작은 미정의 사항.

getTimeKeeper 함수에서 포인터를 통해 날아오는 AtomicClock 객체는 
기본 클래스 포인터를 통해 삭제될 때 AtomicClock 클래스에서 정의된 데이터 멤버들이 저 세상으로 가지 못함
AtomicCLock의 소멸자도 실행되지 않음.
그러나 기본 클래스 부분(TimeKeeper 부분)은 소멸. 반쪽짜리 부분 소멸

class TimeKeeper {
public:
	TimeKeeper();
	virtual ~TimeKeeper();
};
TimeKeeper *ptk = getTimeKeeper();
delete ptk;	//제대로 동작

가상 함수를 하나라도 가진 클래스는 가상 소멸자를 가져가야 한다.

class Point {
public:
	Point(int xCoord, int yCoord);
	~Point();
private:
	int x, y;
};
가상함수 테이블 포인터 vptr
가상 함수의 주소, 포인터들의 배열.
가상 함수 테이블 포인터의 배열 == > 가상 함수 테이블 vtbl

위 Point 클래스에 가상함수가 들어가면, Point 타입 객체의 크기가 커지는 문제 발생
하여, 소멸자는 가상 함수를 하나 이상 클래스에만 사용
class SpecialString : public std::string {};	//std::string 은 가상 소멸자 없어서 불가능

SpecialString *pss = new SpecialString("Impending Doom");
std::string *ps;
ps = pss;	//SpecialString* => std::string*
delete ps;	//미정의 동작. *ps의 SpeicalString 부분에 있는 자원이 누출됨.
			//그 이유는 SpecialString의 소멸자가 호출되지 않기 때문.
가상 소멸자가 없는 클래스 : STL 컨테이너 타입(vector, list, set, trl::unordered_map 등)

추상 클래스(abstract class) : 그 자체로는 인스턴스를 못 만드는 클래스. 그 타입의 객체를 생성할 수 없는.
순수 가상 함수는 해당 클래스를 추상 클래스로 만듦.
하지만 어떤 클래스가 추상 클래스였으면 좋겠는데 마땅히 넣을 만한 순수 가상 함수가 없을 때에는?
추상 클래스로 만들고 싶은 클래스에 순수 가상 소멸자 선언.

class AWOV {	//AWOV = "Abstrack w/o Virtuals"
public:
	virtual ~AWOV() = 0;	//순수 가상 소멸자 선언
};

모든 기본 클래스가 다형성을 갖도록 설계된 것이 아님. (string, STL 컨테이너 타입)
또한 기본 클래스로는 쓰일 수 있지만 다형성은 갖지 않도록 설계된 클래스도 있음(항목 6의 Uncopyable과 표준 input_iterator_tag)
기본 클래스의 인터페이스를 통한 파생 클래스 객체의 조작이 허용되지 않는다.
하여, 이들에게서 가상 소멸자를 볼 수 없다.

잊지 말자!
1 다형성을 가진 기본 클래스에는 반드시 가상 소멸자를 선언해야 합니다.
	즉 어떤 클래스가 가상 함수를 하나라도 갖고 있으면, 이 클래스의 소멸자도 가상 소멸자이어야 합니다.
2 기본 클래스로 설계되지 않았거나 다형성을 갖도록 설계되지 않은 클래스에는 가상 소멸자를 선언하지 말아야 합니다.



항목 8: 예외가 소멸자를 떠나지 못하도록 붙들어 놓자!
;
class Widget {
public:
	~Widget() {/**/ }	//이 함수로부터 예외가 발생된다고 가정
};
void doSomething() {
	std::vector<Widget> v;
}	//v 자동 소멸
예외 발생 때 어떻게 처리할까 ?

다른 예 : 데이터베이스 연결을 나타내는 클래스;
class DBConnection {
public:
	static DBConnection create();	//DBConnection 객체를 반환하는 함수. 매개변수는 편의상 생략.

	void close();	//연결을 닫는다. 이때 연결이 실패하면 예외를 던진다.
};
class DBConn {
public:
	~DBConn() {
		db.close();
	}
private:
	DBConnection db;
};
{
	DBConn dbc(DBConnction::create());	//DBConnection 객체를 생성하고, 이것을 DBConn 객체로 넘겨서 관리를 맡김
	/*...*/		//DBConn 인터페이스를 통해 그 DBConnection 객체를 사용
}	//블록 끝. DBConn 객체가 여기서 소멸됨. 따라서 DBConnection 객체에 대한 close 함수의 호출이 자동으로 이루어짐.
예외를 던지는 소멸자는 예외 전파

피하는 방법
1 close에서 예외가 발생하면 프로그램을 바로 끝냅니다. 대개 abort를 호출
DBConn::~DBConn() {
	try {
		db.close();
	}
	catch (/*...*/) {
		//close 호출 실패했다는 로그 가정
		std::abort();
	}
}
2 close를 호출한 곳에서 일어난 예외를 삼켜 버린다. <= 예외 무시하고도 프로그램이 신뢰성 있게 실행 지속 가능할 때
DBConn:~DBConn() {
	try {
		db.close();
	}
	catch (/*...*/) {
		//close 호출 실패했다는 로그 가정
	}
}

다른 방법은? 인터페이스를 잘 설계..
class DBConn {
public:
	void close() {
		db.close();
		closed = true;
	}
	~DBConn() {
		if (!closed) {
			try {	//사용자가 연결 안 닫았으면 여기서 닫기
				db.closse();
			}
			catch (/*...*/) {		//연결을 닫다가 실패하면, 실패를 알린 후에 실행을 끝내거나 예외를 삼키기
				//close 호출 실패 로그
				//...
			}
		}
	}
private:
	DBConnection db;
	bool closed;
}
close 호출의 책임을 DBConn의 소멸자에서 DBConn의 사용자로 떠넘기는 아이디어.
어떤 동작이 예외를 일으키면서 실패할 가능성이 있고,
또 그 예외를 처리해야 할 필요가 있다면,
그 예외는 소멸자가 아닌 다른 함수에서 비롯된 것이어야 한다.

잊지 말자!
1 소멸자에서는 예외가 빠져나가면 안 된다.
	소멸자 안에서 호출된 함수가 예외를 던질 가능성이 있다면, 
	어떤 예외이든지 소멸자에서 모두 받아낸 후에 삼켜 버리든지 프로그램을 끝내든지 해야 한다.
2 어떤 클래스의 연산이 진행되다가 던진 예외에 대해 사용자가 반응해야 할 필요가 있다면,
	해당 연산을 제공하는 함수는 반드시 보통의 함수(즉, 소멸자가 아닌 함수)이어야 한다.;




항목 9: 객체 생성 및 소멸 과정 중에는 절대로 가상 함수를 호출하지 말자!

객체 생성 및 소멸 과정 중에는 가상 함수를 호출하면 절대로 안 됩니다!
객체 생성 및 소멸 과정 중에는 가상 함수를 호출하면 절대로 안 됩니다!;


class Transaction {
public:
	Transaction();
	virtual void logTransaction() const = 0;	//타입에 따라 달라지는 로그 기록이라 가정
	//...
};
Transaction::Transaction() {	//생성자
	//...
	logTransaction();	//거래 로깅 시작
}

class BuyTransaction : public Transaction {	//Transaction의 파생 클래스
public:
	virtual void logTransaction() const;	//이 타입에 따른 거래내역 로깅
	//...
};
class SellTransaction : public Transaction {	//동일
public:
	virtual void logTransaction() const;
	//...
};
BuyTransaction b;

기본 클래스의 생성자가 호출될 동안에는, 가상 함수는 절대로 파생 클래스 쪽으로 내려가지 않는다.
대신 객체 자신이 기본 클래스 타입인 것처럼 동작한다.

기본 클래스 생성자가 돌아가고 있을 시점에 파생 클래스 데이터 멤버는 아직 초기화된 상태가 아니다.

파생 클래스 객체의 기본 클래스 부분이 생성되는 동안은, 그 객체의 타입은 바로 기본 클래스.
호출되는 가상 함수는 모두 기본 클래스의 것으로 결정됨.
이때 파생 클래스의 데이터는 아직 초기화된 상태가 아니기 때문에, 아예 없었던 것처럼 취급.
파생 클래스의 생성자의 실행이 시작되어야만 비로소 파생 클래스 객체의 면모를 가짐.;

class Transaction {
public:
	Transaction() {
		init();	//비가상 멤버 함수 호출
	}
	virtual void logTransaction() const = 0;
	//...
private:
	void init() { //...
		logTransaction();	//비가상 함수에서 가상 함수 호출중
	}
};
위 코드는 컴파일 링크도 잘되나 매우 위험.
생성 중이거나 소멸 중인 객체에 대해 생성자나 소멸자에서 가상 함수를 호출하는 코드를 솎아내기.
개선책;
class Transaction {
public:
	explicit Transaction(const std::string& logInfo);
	void logTransaction(const std::string& logInfo) const;	//이제는 비가상 함수
	//...
};
Transaction::Transaction(const std::string& logInfo) {
	//...
	logTransaction(logInfo);
}
class BuyTransaction : public Transaction {
public:
	BuyTransaction(parameters)
		: Transaction(createLogString(parameters)) {	//로그 정보를 기본 클래스 생성자로 넘긴다.
		/*...*/
	}
private:
	static std::string createLogString(parameters);
};
파생 클래스 부분에서 기본 클래스 생성자로 올려주기
이 정적 함수는 기본 클래스 생성자 쪽으로 넘길 값을 생성하는 용도로 쓰이는 도우미 함수
기본 클래스에 멤버 초기화 리스트가 많이 달려있을 때 편리.
정적 멤버라 생성이 채 끝나지 않은 BuyTransaction 객체의 미초기화된 데이터 멤버를 실수로 건드릴 위험도 없음.
= > '미초기화된 데이터 멤버는 정의되지 않은 상태에 있다.'

잊지 말자!
생성자 혹은 소멸자 안에서 가상 함수 호출 xxx.
가상 함수라고 해도, 지금 실행 중인 생성자나 소멸자에 해당되는 클래스의 파생 클래스 쪽으로는 내려가지 않는다.




항목 10: 대입 연산자는 *this 의 참조자를 반환하게 한다.

class Widget {
public: /*...*/
	Widget& operator=(const Widget& rhs) { /*...*/	//반환 타입은 현재 클래스에 대한 참조자.
		return *this;	//좌변 객체(의 참조자)를 반환. (인자가 뭐든 모든 +=, -= 등 대입에도 동일한 규약 적용)
	}
};
위 사항은 '관례'

잊지 말자!
대입 연산자는 *this의 참조자를 반환하도록 만드세요!




항목 11: operator=에서는 자기대입에 대한 처리가 빠지지 않도록 하자

자기대입(self assignment)이란, 어떤 객체가 자기 자신에 대해 대입 연산자를 적용하는 것을 의미함.
class Widget {/*...*/ };
Widget w;
//...
w = w;
nodes[i] = nodes[j];
*px = *py
등 자기대입의 가능성을 가득 품은 문장들.
여러 곳에서 하나의 객체를 참조하는 상태, '중복참조';

class Base {/*...*/ };
class Derived : public Base {/*...*/ };
void doSomething(const Base& rb, Derived* pd);	//rb 및 *pd는 원래 같은 객체였을 수도 있음.

예시: 동적 할당된 비트맵 가리키는 원시 포인터를 데이터 멤버로 갖는 클래스;
class Bitmap {/*...*/ };
class Widget {
	//...
	Widget& operator=(const Widget& rhs) {	//안전하지 않은 예시
		delete pb;	//현재의 비트맵 사용 중지
		pb = new Bitmap(*rhs.pb);	//rhs의 비트맵 사용
		return *this;
	}
private:
	Bitmap *pb;	//힙에 할당된 객체를 가리키는 포인터
};
*this와 rhs가 같은 객체일 가능성이 있음
delete 연산자가 *this 객체의 비트맵에만 적용되는 것이 아니라 rhs의 객체까지 적용되어 버림~

전통적인 방법
operator=의 첫머리에서 일치성 검사(identity test)
Widget& Widget::operator=(const Widget& rhs) {
	if (this == &rhs) return *this;	//객체가 같은지, 즉 자기대입인지. 자기대입이면 아무것도 안 함.
	delete pb;
	//...
}
그러나 예외에 안전하지 않다.
new Bitmap에서 예외가 터지면(동적 할당에 필요한 메모리 부족, Bitmap 클래스 복사 생성자에서 예외를 던지는 등)
Widget 객체는 결국 삭제된 Bitmap을 가리키는 포인터를 껴안고 홀로 남고 만다.

개선안;
Widget& Widget::operator=(const Widget& rhs) {
	Bitmap *pOrig = pb;		//원래의 pb를 어딘가에 기억해 둔다.
	pb = new Bitmap(*rhs.pb);	//다음, pb가 *pb의 사본을 가리키게 한다.
	delete pOrig;	//원래의 사본을 삭제한다.
	return *this;
}
예외와 자기대입 모두 처리됨

또 다른 방법 : 복사 후 맞바꾸기(copy and swap);
class Widget {
	void swap(Widget& rhs);	//*this의 데이터 및 rhs의 데이터를 맞바꾸기 (항목 29 확인)
};
Widget& Widget::operator=(const Widget& rhs) {
	Widget temp(rhs);	//rhs의 데이터에 대해 사본을 하나 만든다.
	swap(temp);	//*this의 데이터를 그 사본의 걼과 맞바꾼다.
	return *this;
}
조금 다르게 구현해볼까 ? ;
Widget& Widget::operator=(Widget rhs) {	//rhs는 넘어온 원래 객체의 사본. 값에 의한 전달
	swap(rhs);	//*this의 데이터를 이 사본의 데이터와 맞바꿈
	return *this;
}
우려가 조금 있으나 효율적임.

이것만은 잊지 말자!
1 operator= 을 구현할 때 어떤 객체가 그 자신에 대입되는 경우를 제대로 처리하도록.
	원본 객체와 복사대상 객체의 주소를 비교해도 되고, 문장의 순서를 적절히 조정할 수도 있으며,
	복사 후 맞바꾸기 기법을 써도 된다.
2 두 개 이상의 객체에 대해 동작하는 함수가 있다면,
	이 함수에 넘겨지는 객체들이 같은 객체인 경우에 정확하게 동작하는지 확인해 보세요.;




항목 12: 객체의 모든 부분을 빠짐없이 복사하자

복사 함수 == 복사 생성자와 복사 대입 연산자

예시 : 고객을 나타내는 함수;
void logCall(const std::string& funcName);	//로그 기록내용을 만든다.
class Customer {
public:
	Customer(const Customer& rhs);
	Customer& operator=(const Customer& rhs);
private:
	std::string name;
};
Customer::Customer(const Customaer& rhs)
	: name(rhs.name) {
	logCall("Customer copy constructor");
}
Customer& Customer::operator=(const Customer& rhs) {
	logCall("Customer copy assignment operator");
	name = rhs.name;
	return *this;
}

여기까지는 문제 없으나 다음과 같이 데이터 멤버 추가 시 문제;
class Date {/*...*/ };
class Customer {
public:
	//이전과 동일
private:
	std::string name;
	Date lastTranaction;
};
복사 함수의 동작은 부분복사가 된다.
이때 컴파일러가 경고조차 하지 않음.
그럼 생성자, 연산자, 복사 함수 모두 처리 또 해줘야 함.

다음은 클래스 상속에서 문제;
class PriorityCustomer : public Customer {	//파생 클래스
public:
	//...
	PriorityCustomer(const PriorityCustomer& rhs);
	PriorityCustomer& operator=(const PriorityCustomer& rhs);
private:
	int priority;
};

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
	: priority(rhs.priority) {
	logCall("PriorityCustomer copy constructor");
}
PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs) {
	logCall("PriorityCustomer copy assignment operator");
	priority = rhs.priority;
	return *this;
}
Customer로부터 상속한 데이터 멤버들의 사본도 PriorityCustomer 클래스에 들어 있는데,
이들은 복사가 안 되고 있어!
객체의 Customer 부분은 Customer 생성자에 의해 초기화된다.

파생 클래스에 대한 복사 함수에서 기본 클래스 부분의 복사를 빠뜨리지 않도록 한다!;
PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs) 
	: Customer(rhs) , priority(rhs.priority) {	//기본 클래스의 복사 생성자 호출!
	logCall("PriorityCustomer copy ctor");
}
PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs) {
	logCall("PriorityCustomer copy assignment operator");
	Customer::operator=(rhs);	//기본 클래스 부분 대입!!
	priority = rhs.priority;
	return *this;
}

중복 피하려고 복사 대입 연산자에서 복사 생성자를 호출할 수 없음.그 반대도 안됨.
복사 대입 연산자의 역할은 이미 초기화가 끝난 객체에 값을 주는 것.
다만 양쪽에서 겹치는 부분을 별도의 멤버 함수를 만들어 호출할 수 있음.
private init 이 그러함.

이것만은 잊지 말자!
1 객체 복사 함수는 주어진 객체의 모든 데이터 멤버 및 모든 기본 클래스 부분을 빠뜨리지 말고 복사해야 한다.
2 클래스의 복사 함수 두 개를 구현할 때, 한쪽을 이용해서 다른 쪽을 구현 x
	그 대신, 공통된 동작을 제3의 함수에다 분리해 놓고 양쪽에서 이것을 호출;




자원 관리
항목 13: 자원관리에는 객체가 그만!

예시 : 투자 모델링 클래스 라이브러리로 작업;
class Investment {/*...*/ };	//여러 형태의 투자를 모델링한 클래스 계통의 최상위 클래스로 가정

팩토리 함수 사용
팩토리 함수 : 새로 생성된 파생 클래스 객체에 대한 기본 클래스 포인터를 반환하는 함수(아래는 예시);
	TimeKeeper* getTimeKeeper();	//TimeKeeper에서 파생된 클래스를 통해 동적으로 할당된 객체의 포인터를 반환합니다.
	TimeKeeper *ptk = getTimeKeeper();	//TimeKeeper 클래스 계통으로 부터 동적으로 할당된 객체를 얻습니다.)

Investment* createInvestment();	
//Investment 클래스 계통에 속한 클래스의 객체를 동적 할당하고, 그 포인터를 반환.
//이 객체의 해제는 호출자 쪽에서 직접 해야 함. (매개변수는 예시에서는 생략함)
void f() {
	Investment *pInv = createInvestment();	//팩토리 함수 호출
	//...
	delete pInv;	//객체 해제
}
delete 앞에 도중 return문이 있을 경우, 예외를 던질 경우, 루프 빠져나올 경우 위험


auto_ptr 삭제됐는데...
암튼 자동으로 delete 불러줌;
void f() {
	std::auto_ptr<Investment>pInv(createInvestment());	//팩토리 함수 호출
}
객체를 사용하는 방법의 중요한 2가지 특징
1 자원을 획득한 후에 자원 관리는 객체에게 넘긴다.
	자원 획득 즉 초기화(Resource Acquisition Is Initialization : RAII)라는 이름.
	자원 획득과 자원 관리 객체의 초기화가 한 문장에서 이뤄지는 게 보통.
2 자원 관리 객체는 자신의 소멸자를 사용해서 자원이 확실히 해제되도록 한다.
	소멸자는 어떤 객체가 소멸될 때(유효범위를 벗어나는 경우 등) 자동으로 호출되기 때문에 자원 해제됨;

auto_ptr : 스마트 포인터
	객체를 복사하면 원본 객체는 null로 만듦.;
std::auto_ptr<Investment> pInv1(createInvestment());
std::auto_ptr<Investment> pInv2(pInv1);		//pInv1은 이제 null
pInv1 = pInv2;		//지금 1은 그 객체를 가리키고 있으며, pInv2는 null
= > auto_ptr은 객체는 두 개 이상 물고 있으면 안 되는 요구사항!불편...

참조 카운팅 방식 스마트 포인트(reference - counting smart pointer : RCSP)
	특정한 어떤 자원을 가리키는(참조하는) 외부 객체의 개수를 유지하고 있다가
	그 개수가 0이 되면 해당 자원을 자동으로 삭제하는 스마트 포인터.
"tr1::shared_ptr"이 대표적인 RCSP;

void f() {
	std::tr1::shared_ptr<Investment> pInv(createInvestment());	//팩토리 함수 호출. shared_ptr의 소멸자를 통해 pInv 자동 삭제.
}
자연스럽게 복사됨;
void f() {
	std::tr1::shared_ptr<Investment> pInv1(createInvestment());
	std::tr1::shared_ptr<Investment> pInv2(createInvestment());	//pInv1과 2가 동시에 그 객체를 가리킨다.
	pInv1 = pInv2;	//마찬가지. 변한 것은 없음.
}	//pInv1, 2 소멸되며, 이들이 가리키고 있는 객체도 자동 삭제.

자원을 관리하는 객체를 써서 자원을 관리하는 것이 중요함.
auto_ptr 및 tr1::shared_ptr은 소멸자 내부에서 delete 연산자 사용(delete[]가 아님. 16장에서 확인)
동적 할당한 배열에 대해 사용하면 난감~
std::auto_ptr<std::string>	//좋지 않은 발상
	aps(new std::string[10]);	//잘못된 deletle 발생
std::tr1::shared_ptr<int> spi(new int[1024]);	//같은 문제 발생.

또 다른 문제
createInvestment 함수의 반환타입이 포인터로 되어있음. Investment* createInvestment();
반환된 포인터에 대한 delete 호출을 호출자 쪽에서 해야 하는데, 잊어버리기 쉽다.
이건 항목 18에서 to be continued...

이것만은 잊지 말자!
1 자원 누출을 막기 위해, 생성자 안에서 자원을 획득하고 소멸자에서 그것을 해제하는 RAII객체를 사용합시다!
2 일반적으로 널리 쓰이는 RAII 클래스는 tr1::shared_ptr 그리고 auto_ptr.
	이 둘 중 쉐어드가 복사 시 동작이 직관적이기 때문에 대개 더 좋다.
	반면 auto_ptr은 복사되는 원본 객체를 null로 만듦.;




항목 14: 자원 관리 클래스의 복사 동작에 대해 진지하게 고찰하자!

힙에 생기지 않는 자원은 auto_ptr이나 tr1::shared_ptr 등의 스마트 포인터로 처리해주기엔 맞지 않다.

예시 : Mutex 타입의 뮤텍스 객체를 조작하는 C API;
void lock(Mutex *pm);
void unlock(Mutex *pm);

class Lock {
public:
	explicit Lock(Mutex *pm)
		: mutexPtr(pm) {
		lock(mutextPtr);
	}
	~Lock() {
		unLock(mutextPtr);
	}
private:
	Mutex *mutextPtr;
}
Mutex m;
{	//임계 영역 정하기 위해 블록 만듦.
	Lock ml(&m);	//뮤텍스에 잠금
}
여기까진 잘됨슨;
Lock ml1(&m);	//m에 잠금
Lock ml2(ml1);	//ml1 을 ml2로 복사.


RAII 객체 복사될 떄 어떠 동작이 이루어져야 할까...
1 복사 금지 ?
	private으로 만들기(항목 6참고);
class Lock : priavate Uncopyable { }	//복사 금지 예시.

2 관리하고 있는 자원에 대해 참조 카운팅을 수행.
해당 자원을 참조하는 객체의 개수에 대한 카운트를 증가시키는 방식.
tr1::shared_ptr이 사용하고 있음.
단, mutextPtr의 타입을 Mutex*에서 tr1::shared_ptr<Mutex>로 바꾸면,
tr1::shared_ptr은 참조 카운트가 0이 될 때 자신이 가리키고 있는 대상을 삭제해 버리므로,
삭제를 원하지 않을 경우 적절하지 않음.

다행인 점은 tr1::shared_ptr은 '삭제자(deleter)' 를 허용함.
tr1::shared_ptr의 참조 카운트가 0이 되었을 때 호출하는 함수 or 함수 객체.;

class Lock {
public:
	explicit Lock(Mutex *pm)	//shared_ptr을 초기화하는데, 가리킬 포인터로 Mutext 객체의 포인터 사용하고 삭제자로 unlock 함수 사용
		: mutextPtr(pm, unlock) {
		lock(mutextPtr.get());	//get은 항목 15 확인
	}
private:
	std::tr1::shared_ptr<Mutex> mutextPtr;	//원시 포인터 대신 shared_ptr 사용
};
객체 소멸 과정을 잊은 게 아니라 컴파일러가 생성한 소멸자를 통해 동작한다.

3 관리하고 있는 자원을 진짜로 복사한다.
	자원을 다 썼을 때 각각의 사본을 확실히 해제하는 것 <= = 자원 관리 클래스가 필요한 유일한 명분
	자원 관리 객체를 복사하면 그 객체가 둘러싸고 있는 자원까지 복사되어야 한다.
	== > 즉, 깊은 복사 수행 ex.string 타입

4 관리하고 있는 자원의 소유권을 옮긴다.
	어떤 자원을 실제로 참조하는 RAII 객체는 딱 하나만 존재하도록 만들고 싶을 때,
	객체 복사 시 소유권을 사본 쪽으로 아예 옮길 때
	auto_ptr 복사 동작 사용;

이것만은 잊지 말자!
1 RAII 객체의 복사는 그 객체가 관리하는 자원의 복사 문제를 안고 가기 때문에
	그 자원을 어떻게 복사하느냐에 따라 RAII 객체의 복사 동작이 결정됨.
2 RAII 클래스에 구현하는 일반적인 복사 동작은 복사를 긂지하거나 참조 카운팅을 해주는 선에서 마무리;

(어려웡..)




항목 15: 자원 관리 클래스에서 관리되는 자원은 외부에서 접근할 수 있도록 하자

자원 관리 객체의 보호벽을 넘어서 실제 자원을 직접 관리할 경우;
std::tr1::shared_ptr<Investment> pInv(createInvestment());
int daysHeld(const Investment *pi);	//투자금이 유입된 이후로 경과한 날수로 가정
int days = daysHeld(pInv)	//에러!
Investment* 타입이 아닌, tr1::shared_ptr<Investment> 타입의 객체를 넘겼기 때문.

형 변환 2가지
명시적 변환(explicit conversion)
암시적 변환(implicit conversion)

tr1::shared_ptr 은 명시적 변환을 수행하는 get이라는 멤버 함수 제공.
int days = daysHeld(pInv.get());

스마트 포인터는 포인터 역참조 연산자(operator-> 및 operator*)도 오버로딩하고 있음.;
class Investment {
public:
	bool isTaxFree() const;
};
Investment* createInvestment();		//팩토리 함수
std::tr1::shared_ptr<Investment> pi1(createInvestment());	//tr1::shared_ptr이 자원 관리를 맡음
bool taxable1 = !(pi1->isTexFree());	//operator->를 써서 자원에 접근

std::auto_ptr<Investment> pi2(createInvestment());	//auto_ptr로 하여금 자원 관리 맡도록 함
bool texable2 = !((*pi2).isTaxFree());	//operator*를 써서 자원에 접근


예시;
FontHandle getFont();	//C API에서 가져온 함수. 매개변수는 현재는 생략
void release(FontHandle fh);	//C API에서 가져온 함수. 

class Font {	//RAII 클래스
public:
	explicit Font(FontHandle fh)	//자원을 획득. 여기서 값에 의한 전달 수행함을 주의. 자원 해제를 C API로 하기 때문.
		: f(fh) {}
	~Font() { releaseFont(f); }
	FontHandle get() const {
		return f;
	}
private:
	FontHandle f;	//실제 폰트 자원
}
이때 하부 수분 API를 쓰고 싶을 때마다 get을 호출해야 함;
void changeFontSize(FontHandle f, int newSize);	//폰트 API의 일부
Font f(getFont());
int newFontSize;
changeFontSize(f.get(), newFontSize);		//Font에서 FontHandle로 명시적으로 바꾼 후에 넘깁니다.

다른 안: FontHandle로의 암시적 변환 함수를 Font에서 제공;
class Font {
public:
	//...
	operator FontHandle() const {		//암시적 변환 함수
		return f;
	}
};
Font f(getFont());
int newFontSize;
changeFontSize(f, newFontSize);		//Font에서 FontHandle로 암시적 변환을 수행합니다.

다만 암시적 변환을 쓰면 실수 여지 많아짐.
Font f1(getFont());
FontHandle f2 = f1;		//원래 의도는 Font 객체를 복사하는 것이었는데, f1이 FontHandle로 바뀌고 나서 복사됨.

하여, get 등의 명시적 변환 함수를 제공하는 쪽이 나을 때가 많음.

이것만은 잊지 말자!
1 실제 자원을 직접 접근해야 하는 기존 API들도 많기 때문에,
	RAII 클래스를 만들 때는 그 클래스가 관리하는 자원을 얻을 수 있는 방법을 열어 주어야 한다.
2 자원 접근은 명시적 변환 혹은 암시적 변환을 통해 가능.
	안전성만 따지만 명시적 변환이 대체적으로 더 낫지만,
	고객 편의성을 놓고 보면 암시적 변환이 괜찮음.;




항목 16: new 및 delete를 사용할 때는 형태를 반드시 맞추자!

std::string *stringArray = new std::string[100];
//...
delete stringArray;
= > stringArray가 가리키는 100개의 string 객체들 중 99개 소멸 안됨
new 동적 할당 시
1 메모리 할당(operator new 함수 호출)
2 할당된 메모리에 1개 이상의 생성자 호출
delete 사용 시
1 기존 할당된 메모리에 1개 이상의 소멸자 호출
2 그 후 메모리 해제(operator delete 함수 호출)
delete 연산자가 적용되는 객체 개수 == > '소멸자가 호출되는 횟수';

std::string *stringPtr1 = new std::string;
std::string *stringPtr2 = new std::string[100];
//...
delete stringPtr1;		//객체 1개 삭제
delete[] stringPtr2;	//객체 배열 삭제

vector<string>으로 만들면 할당, 해제 직접 할 일이 없을 것!

이것만은 잊지 말자!
new 표현식에[]을 썼으면, 대응되는 delete 표현식에도[]를 써야 한다.
new 표현식제[]을 안 썼으면, 대응되는 delete 표현식에도 []를 쓰지 말아야 한다.;




항목 17: new로 생성한 객체를 스마트 포인터에 저장하는 코드는 별도의 한 문장으로 만들자!

예시 : 처리 우선순위 알려주는 함수 + 동적 할당한 객체에 대해 우선순위 적용하는 함수;
int priority();
void processWidget(std::tr1::shared_ptr<Widget> pw, int priority);
processWidget(new Widget, priority());

컴파일 안됨.tr1::shared_ptr의 생성자는 explicit 로 선언되었기 때문에, new Widget이라는 표현식에 의한 만들어진 포인터가
tr1::shared_ptr 타입의 객체로 바꾸는 암시적인 변환이 없음.
반면 아래의 코드는 컴파일됨.;
processWidget(std::tr1::shared_ptr<Widget>(new Widget), priority());
but, 자원을 흘릴 가능성이 있다.

c++에서 보통 연산 순서는 다음과 같으나..
1 priority를 호출
2 "new Widget"을 실행
3 tr1::shared_ptr 생성자를 호출
컴파일러에 따라 1, 2번이 뒤집어질 수 있음
priority 호출 부분에서 예외 발생 시 new Widget으로 만든 포인터 유실 가능
자원 누출을 막아줄 줄 알고 준비한 tr1::shared_ptr에 저장되기도 전에 예외.

피하는 방법;
std::tr1::shared_ptr<Widget> pw(new Widget)		//new로 생성한 객체를 스마트 포인터에 담는 코드를 하나의 독립적인 문장으로.
processWidget(pw, priority());

이것만은 잊지 말자!
	new 로 생성한 객체를 스마트 포인터로 넣는 코드는 별도의 한 문장으로 만듭시다!
	이것이 안 되어 있으면, 예외가 발생될 때 디버깅하기 힘든 자원이 누출이 초래될 수 있다.;




설계 및 선언

항목 18: 인터페이스 설계는 제대로 쓰기엔 쉽게, 엉터리로 쓰기엔 어렵게 하자

;
class Date {
public:
	Date(int month, int day, int year);
}
전달될 순서가 잘못될 여지가 있다.

새로운 타입을 들여와 인터페이스 강화.
랩퍼(wrapper) 타입;
struct Day {
	explicit Day(int d) : val(d) {}
	int val;
};
struct Month {
	explicit Month(int m) : val(m) {}
	int val;
};
struct Year {
	explicit Year(int y) : val(y) {}
	int val;
};
class Date {
public:
	Date(const Month& m, const Day& d, const Year& y);
};
Date d(30, 3, 1995);	//에러. 타입 틀림슨발록
Date d(Day(30), Month(3), Year(1995));	//에러. 타입 틀림
Date d(Month(3), Day(30), Year(1995));	//타입 맞음ㅅ!

유효한 값 제약 걸 수 있음.
enum 을 넣는 방법.단, 타입 안정성 낮음.;

class Month {
public:
	static Month Jan() {	//왜 함수이며 객체는 왜 안 되는가는 아래 설명
		return Month(1);
	}
	//...
	static Month Dec() {
		return Month(12);
	}
private:
	explicit Month(int m);	//Month 값이 새로 생성되지 않도록 명시호출 생성자가 private 멤버.
};
class Date {
public:
	Date(const Month& m, const Day& d, const Year& y);
};
Date d(Month::Jan(), Day(30), Year(1995));

항목 4에 따르면, 비지역 정적 객체들의 초기화를 밀고 나가는 것은 문제가 있다.
하여, 특정한 월을 나타내는 데 객체를 쓰지 않고 함수를 씀.

operator*의 반환 타입을 const로 한정함으로써 사용자 정의 타입에 다음과 같은 실수 방지
if (a * b = c) ...

예시: 팩토리 함수 Investment 클래스 계통의 동적할당 후 객체의 포인터 반환;
Investment* createInvestment();
포인터를 나중에라도 삭제해야 함.그를 위해 스마트 포인터 사용한 것.

스마트 포인터 사용한다는 사실도 잊어버리면 ?
애초부터 팩토리 함수가 스마트 포인터를 반환하게 만드는 것.;
std::tr1::shared_ptr<Investment> createInvestment();
생성 시점에 자원 해제 함수(삭제자)를 직접 엮을 수도 있다. (auto_ptr은 이런 기능이 없다)

스마트 포인터 tr1::shared_ptr에는 두 개의 인자를 받는 생성자가 있다.
관리할 실제 포인터, 참조 카운트 0이 될 떄 호출될 삭제자.;
std::tr1::shared_ptr<Investment> pInv{ static_cast<Investment*>(0), getRidOfInvestmen };	
//0은 널 포인터, 뒤 함수는 사용자 정의 삭제자

std::tr1::shared_ptr<Investment> createInvestment() {
	std::tr1::shared_ptr<Investment> retVal(statck_cast<Investment*>(0), getRidOfInvestment);
	retVal = ...;	//retVal은 실제 객체를 가리키도록 만들기.
	return retVal;
}

std::tr1::shared_ptr의 또 하나의 특징
교차 DLL 문제(cross - DLL problem) 해결
	: 어떤 동적 링크 라이브러리(DLL)에 new 를 썼는데 그 객체를 삭제할 때는 이전의 DLL과 다른 DLL에 있는 delete 를 썼을 경우.
	: new / delete 짝이 달라서 꼬여서 런타임 에러.
기본 삭제자가 std::tr1::shared_ptr이 생성된 DLL과 동일한 DLL에서 delete 사용하도록 만들어져 있음.;

std::tr1::shared_ptr<Investment> createInvestment() {
	return std::tr1::shared_ptr<Investment>(new stock);
}
=> 다른 DLL들 사이를 넘어가도 문제 걱정 no.

std::tr1::shared_ptr 구현한 제품 중 흔히 쓰이는 부스트 라이브러리의 shared_ptr
원시 포인터보다 크고 느리며 내부 관리용 동적 메모리까지 추가로 매달리나,
사용자 실수가 눈에 띄게 줄어듦.

이것만은 잊지 말자!
1 좋은 인터페이스는 제대로 쓰이게 쉬우며 엉터리로 쓰기에 어렵습니다.
	인터페이스를 만들 때는 이 특성을 지닐 수 있도록 고민하고 또 고민합시다.
2 인터페이스의 올바른 사용을 이끄는 방법으로는 인터페이스 사이의 일관성 잡아주기,
	그리고 기본제공 타입과의 동작 호환성 유지하기가 있습니다.
3 사용자의 실수를 방지하는 방법으로는 새로운 타입 만들기, 타입에 대한 연산을 제한하기,
	객체의 값에 대해 제약 걸기, 자원 관리 작업을 사용자 책임으로 놓지 않기가 있습니다.
4 tr1::shared_ptr은 사용자 정의 삭제자를 지원합니다. 이 특징 때문에 tr1::shared_ptr은
	교차 DLL 문제를 막아 주며, 뮤텍스 등을 자동으로 잠금 해제하는 데 쓸 수 있습니다.;




항목 19: 클래스 설계는 타입 설계와 똑같이 취급하자

새로 정의한 타입의 객체 생성 및 소멸은 어떻게 이루어져야 하는가?
	어떻게 정의하는가에 따라 operator new 등 메모리 할당 함수 설계에 영향.

객체 초기화는 객체 대입과 어떻게 달라야 하는가?
	초기화와 대입을 헷갈리지 않는 것.

새로운 타입으로 만든 객체가 값에 의해 전달되는 경우에 어떤 의미를 줄 것인가?
	어떤 타입에 대해 '값에 의한 전달'을 구현하는 쪽은 복사 생성자이다?

새로운 타입이 가질 수 있는 적법한 값에 대한 제약은 무엇으로 잡을 것인가?
	클래스의 데이터 멤버의 몇 가지 조합 값만은 반드시 유효 ==> 클래스의 '불변속성(invariant)'
	생성자, 대입 연산자, 각종 쓰기(setter) 함수는 불변속성에 의해 많이 좌우된다.

기존의 클래스 상속 계통망(inheritance graph)에 맞출 것인가?
	멤버 함수가 가상인가, 비가상인가 여부가 가장 큰 요인. 특히 소멸자

어떤 종류의 타입 변환을 허용할 것인가?
	T1 타입의 객체를 T2 타입의 객체로 암시적으로 변환되도록 하고 싶다면, T1 클래스에 타입 변환 함수(operator T2)
	or 인자 1개로 호출될 수 있는 비명시호출(non-explicit) 생성자를 T2 클래스에 넣어두기
	명시적 타입 변환만 허용하고 싶다면, 타입 변환 연산자or비명시호출 생성자 만들지 않기.

어떤 연산자와 함수를 두어야 의미가 있을까?

표준 함수들 중 어떤 것을 허용하지 말 것인가?
	private 로 선언해야 하는 함수 해당

새로운 타입의 멤버에 대한 접근권한을 어느 쪽에 줄 것인가?
	public protected private, 프렌드, 중첩 등 고민

'선언되지 않은 인터페이스'로 무엇을 둘 것인가?
	내가 만든 타입이 제공할 보장이 어떤 종류? 수행 성능 및 예외 안정성, 자원 사용(잠금 및 동적 메모리 등)

새로 만드는 타입이 얼마나 일반적인가?
	새로운 클래스 템플릿을 정의해야 할 것.

정말로 필요한 타입인가?
	기존 클래스 기능 몇 개 아쉬워서 파생 클래스를 새로 뽑느니,
	간단하게 비멤버 함수라든지 템플릿을 몇 개 더 정의하는 편이 낫다.

이것만은 잊지 말자!
	클래스 설계 == 타입 설계. 위 질문 모두 고려;




항목 20: '값에 의한 전달'보다는 '상수객체 참조자에 의한 전달' 방식을 택하는 편이 대개 낫다!

함수 매개변수는 실제 인자의 '사본'을 통해 초기화.
값에 의한 전달이 고비용의 연산.;
class Person {
public:
	Person();
	virtual ~Person();
private:
	std::string name;
	std::string address;
};

class Student : public Person {
public:
	Student();
	~Student();
private:
	std::string schoolName;
	std::string schoolAddress;
};

bool validateStudent(Student s);
Student plato;
bool platoIsOK = validateStudent(plato);

위 코드 생성자 여섯 번에 소멸자 여섯 번 호출...
상수 객체에 대한 참조자(reference - to - const)로 전달하자!;
bool validateStudent(const Student& s);

= > 새로 만들어지는 객체가 없어 생성자, 소멸자 전혀 호출되지 않음
복사손실 문제(slicing problem)이 없어짐.

예시: 윈도우 클래스 라이브러리;
class Window {
public:
	std::string name() const;	//윈도우 이름 반환
	virtual void display() const;	//윈도우 테두리 및 내부 그림
};
class WindowWithScrollBars : public Window {
public:
	virtual void display() const;
};

잘못된 예시;
void printNameAndDisplay(Window w) {
	std::cout << w.name();
	w.display();
}
WindowWithScrollBars wwsb;
printNameAndDisplay(wwsb);

어떤 타입의 객체로 넘어가든 기본 Window 클래스 객체의 면모만을 갖게 됨.파생 클래스의 함수는 호출안됨!!;

void printNameAndDisplay(const Window& w) {	/*...*/ }	//이제 매개변수는 잘리지 않는다.

이것만은 잊지 말자!
1 '값에 의한 전달'보다는 '상수 객체 참조자에 의한 전달'을 선호합시다!
대체적으로 효율적일 뿐만 아니라 복사손식 문제까지 막아 줍니다.
2 이 항목에서 다룬 법칙은 기본제공 타입, STL 반복자, 그리고 함수 객체 타입 이 3가지에는 맞지 않는다.
이들은 '값에 의한 전달'이 더 적절합니다.




항목 21: 함수에서 객체를 반환해야 할 경우에 참조자를 반환하려고 들지 말자!;

class Rational {
public:
	Rational(int numerator = 0,	int denominator = 1);	//생성자가 explicit로 선언되지 않은 이유는 항목 24에서 확인
private:
	int n, d;	//분자 및 분모
	friend const Rational operator*(const Rational& lhs, const Rational& rhs);	//반환 타입이 const인 이유는 항목 3에서 확인
};

참조자는 그냥 이름이야!
이 함수가 참조자를 반환하도록 만들어졌다면, 이 함수가 반환하는 참조자는 반드시 이미 존재하는 Rational 객체의 참조자.

함수 수준에서 새로운 객체를 만드는 방법 (모두 문제가 있음)
1 스택에 만드는 것;
const Rational& operator*(const Rational& lhs, const Rational& rhs) {
	Rational result(lhs.n * rhs.n, lhs.d * rhs.d);
	return result;
}
= > 생성자 불러야 하는 문제 + 온전한 참조자 반환하지 않음
지역 객체에 대한 참조자를 반환하는 함수는 미정의 행동을 이어짐.

2 힙에 만드는 것;
const Rational& operator*(const Rational& lhs, const Rational& rhs) {
	Rational *result = new Rational(lhs.n * rhs.n, lhs.d * rhs.d);
	return *result;
}
= > 여전히 생성자 호출 + 누가 delete ?
Rational w, x, y, z;
w = x * y * z;		//operator*(operator*(x,y),z)
이때 delete 2번 해줘야 함.;

const Rational& operator*(const Rational& lhs, const Rational& rhs) {
	statck Rational result;	//반환할 참조자가 가리킬 정적 객체
	result = ...;	//lhs*rhs
	return result;
}
= > 스레드 안정성 문제;

inline const Rational operator*(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.n * rhs.n, lhs.d * rhs.d);
}
=> 올바른 동작

이것만은 잊지 말자!
	지역 스택 객체에 대한 포인터나 참조자를 반환하는 일, 혹은 힙에 할당된 객체에 대한 참조자를 반환하는 일,
	또는 지역 정적 객체에 대한 포인터나 참조자를 반환하는 일은 그런 객체가 두 개 이상 필요해질 가능성이 있다면 절대 xxx;




항목 22: 데이터 멤버가 선언될 곳은 private 영역임을 명심하자

데이터 멤버는 반드시 private 멤버이어야 한다...

public이 안 되는 이유
1 문법적 일관성
	ex. get_x()? get_x? 모두 함수라 () 쓰면 되겠지~
2 쓸 건 읽기 쓰기 함수 사용
3 캡슐화(encapsulation)

class SpeedDataCollection {
public:
	void addValue(int spped);
	double averageSoFar() const;	//평균 속도 반환
};
캡슐화 이점:
데이터 멤버를 함수 인터페이스 뒤에 감추면 이득: 
데이터 멤버를 읽거나 쓸 때 다른 객체에 알림 메시지를 보낸다든지, 
클래스의 불변속성 및 사전조건, 사후조건을 검증한다든지,
스레딩 환경에서 동기화를 건다든지 하는 일.

캡슐화되지 않았다 == 바꿀 수 없다 로 이해하셈.

protected 도 public 과 다를 바 없다...

이것만은 잊지 말자!
1 데이터 멤버는 private 멤버로 선언합시다!
	문법적으로 일관성 있는 데이터 접근 통로를 제공
	필요에 따라 세밀한 접근 제어도 가능
	클래스의 불변속성을 강화
	내부 구현의 융통성도 발휘
2 protected 는 public 보다 더 많이 보호받고 있는 것이 절대 아니다.




항목 23: 멤버 함수보다는 비멤버 비프렌드 함수와 더 가까워지자!

예시: 웹브라우저 클래스;
class WebBrowser {
public:
	void clearCache();
	void clearHistory();
	void removeCookies();
};
class WebBrowser {
public:
	void clearEverything();		//위 세 함수 모아서 불러주는 함수 가정
};
위 코드에서 비멤버 함수로 제공;
void clearBrowser(WebBrowser& wb) {
	void clearCache();
	void clearHistory();
	void removeCookies();
}

비멤버 함수를 사용하면 패키징 유연성이 높아진다!
컴파일 의존도도 낮춘다!
WebBrowser의 확장성도 높인다.

어떤 데이터를 접근하는 함수가 많으면 그 데이터의 캡슐화 정도는 낮다.
비멤버 비프렌드 함수는 어떤 클래스의 private 멤버 부분을 접근할 수 있는 함수의 개수를 늘리지 않으므로,
캡슐화 정도가 더 높다!

단, friend 함수는 private 멤버에 대한 접근권한이 해당 클래스의 멤버 함수가 가진 접근권한과 똑같기 때문에,
캡슐화에 대한 영향 역시 같다.

비멤버 함수로 두되, 네임스페이스 사용이 더 자연스러움;
namespace WebBrowserStuff {
	class WebBrowser {/*...*/ };
	void clearBrowser(WebBrowser& wb);
}
예시
//"webbrower.h" 헤더 - WebBrowser 클래스 자체에 대한 헤더
//관련 핵심 기능들이 선언되어 있음
namespace WebBrowserStuff {
	class WebBrowser { ... };	//핵심 관련 기능. 거의 모든 사용자가 써야 하는 비멤버 함수들
}
//"webbrowserbookmarks.h" 헤더
namespace WebBrowserStuff {
	...		//즐겨찾기 관련 편의 함수들
}
//"webbrowserbookmarks.h" 헤더
namespace WebBrowserStuff {
	...		//쿠키 관련 편의 함수들
}
편의 함수 전체를 여러 개의 헤더 파일에(그러나 하나의 네임스페이스에) 나누어 놓으면
편의 함수 집합의 확장(extend)도 손쉬워진다.

이것만은 잊지 말자!
	멤버 함수보다는 비멤버 비프렌드 함수를 자주 쓰도록 합시다.
	캡슐화 정도가 높아지고, 패키징 유연성도 커지며, 기능적인 확장성도 늘어납니다.




항목 24: 타입 변환이 모든 매개변수에 대해 적용되어야 한다면 비멤버 함수를 선언하자!

클래스에서 암시적 타입 변환을 지원하는 것은 일반적으로 못된 생각이다...
물론 이 규칙에도 예외가 있다.
유리수 나타내는 클래스에서 정수에서 유리수로의 암시적 변환은 허용해도 ㄱㅊ;

class Rational {
public:
	Rational(int numerator = 0, int denominator = 1);	//생성자에 일부러 explicit를 붙이지 않음.
												//int에서 Rational로의 암시적 변환을 허용하기 위함.
	int numerator() const;		//분자 및 분모에 대한 접근용 함수.
	int denominator() const;
private:
};
곱셈 만들기;
class Rational {
public:
	const Rational operator*(const Rational& rhs) const;
};
상수를 값으로 반환하고, 상수에 대한 참조자를 인자로 받아들이도록. (항목 3, 20, 21);
Rational oneEighth(1, 8);
Rational oneHalf(1, 2);
Rational result = oneHalf * oneEighth;
result = result * oneEight;

ㅇㅇ
혼합형 수치 연산 - Rational을 int 와 같은 같과도 곱;
result = oneHalf * 2;
result = 2 * oneHalf;	//에러
교환법칙 미성립

두 함수를 함수 형태로 바꿔보자.;
result = oneHalf.operator*(2);
result = 2.operator*(oneHalf);		//에러

result = operator*(2, oneHalf);		//에러

const Rational sorted(2);		//2로부터 임시 Rational 객체 생성
result = oneHalf * sorted;	//oneHalf.operator*(temp); 와 같다.
명시호출(explicit)로 선언되지 않은 생성자가 있기 때문에 동작
비명시호출 생성자와 해도
result = 2 * oneHalf;	//에러
암시 타입 변환에 대해 매개변수가 먹혀들려면 매개변수 리스트에 들어 있어야만 한다.

혼합형 수치 연산 지원하고 싶다?
이제 operator*를 비멤버 함수로 만들어서, 컴파일러 쪽에서 모든 인자에 대해 암시적 타입 변환을 수행하도록 함
class Rational {/*...*/ };	//operator*가 없음.

const Rational operator*(const Rational& lhs, const Rational& rhs) {	//비멤버 함수
	return Rational(lhs.numerator() * rhs.numerator(),
		lhs.denominator() * rhs.denominator());
}
Rational oneFourth(1, 4);
Rational result;
result = oneFourth * 2;
result = 2 * oneFourth;
=> 성공

operator* 함수는 Rational 클래스의 프렌드 함수로? 아니오.
Rational의 public 인터페이스만을 써서 구현할 수 있기 때문.

"멤버 함수의 반대는 프렌드 함수가 아니라 비멤버 함수다."
어떤 클래스와 연관 관계를 맺어 놓고는 싶은데 멤버 함수면 안 되는 함수에 대해
(모든 인자에 대해 타입 변환이 필요하다든가 하는 이유로)
프렌드xxx. 비멤버~

Rational을 클래스가 아닌 클래스 템플릿으로 만들다 보면 설계 사항 완전 다름 (항목 46에서 만나자~)

이것만은 잊지 말자!
	어떤 함수에 들어가는 모든 매개변수(this 포인터가 가리키는 객체도 포함해서)에 대해
	타입 변환을 해줄 필요가 있다면, 그 함수는 비멤버이어야 한다!!




항목 25: 예외를 던지지 않는 swap에 대한 지원도 생각해 보자!

swap : 자기대입 현상 대처
전형적인 구현;
namespace std {
	template<typename T>
	void swap(T& a, T& b) {
		T temp(a);
		a = b;
		b = temp;
	}
}

'pimpl 관용구(pointer to implementation)';
만들어진 객체를 직접 맞바꾼다면, pImpl 포인터만 살짝 바꾸는 것
사용 예제
class WidgetImpl {
public:
private:
	int a, b, c;
	std::vector<double> v;
};
class Widget {		//pimpl 관용구 사용할
public:
	Widget(const Widget& rhs);
	Widget& operator=(const Widget& rhs) {		//WIdget을 복사하기 위해, 자신의 WidgetImpl 객체를 복사
		*pImpl = *(rhs.pImpl);
	}
private:
	WidgetImpl *pImpl;
};
namespace std {
	template<>
	void swap<Widget>(Widget& a, Widget& b) {
		swap(a.pImpl, b.pImpl);	//Widget을 스왑하기 위해 각자의 pImpl 포인터만 맞바꿈
	}
}
template<>는 std::swap의 완전 템플릿 특수화(total template speicalization)
<Widget> 은 T가 Widget일 경우 특수화인 것을 알림.

다만 아직 컴파일 안됨.포인터가 private;

class Widget {
public:
	void swap(Widget& other) {
		using std::swap;	//선언문 필요한 이유 이따가
		swap(pImpl, other.pImpl);	//Widget을 맞바꾸기 위해, 각 Widget의 pImpl 포인터를 맞바꾸기
	}
};
namespace std {
	template<>
	void swap<Widget>(Widget& a, Widget& b) {
		a.swap(b);
	}
}
컴파일됨.STL 컨테이너와 일관성 유지됨

Widget과 WidgetImpl이 클래스가 아닌 클래스 템플릿으로 하면 외않되 ? ;
template<typename T>
void swap<Widget<T>>(Widget<T>& a, Widget<T>& b) { a.swap(b); }
= > C++은 클래스 템플릿에 대해 부분 특수화를 허용하지만, 함수 템플릿에 대해서는 미허용

함수 템플릿을 부분적으로 특수화 하고 싶을 땐 오버로드 버전을 하나 추가;
namespace std {
	template<typename T>
	void swap(Widget<T>& a, Widget<T>& b) { a.swap(b); }
}
= > 다만 std에 새로운 템플릿 추가하면 안됨.미정의사항.

대안
멤버 swap을 호출하는 비멤버 swap 선언.
비멤버 함수를 std::swap의 특수화 버전이나 오버로딩 버전으로 선언하지만 않으면 된다.;

템플릿 전용 버전을 써보자~
namespace WidgetStuff {		//namespace가 std가 아니라 위젯 관련 기능이 전부 WidgetStuff에 들어있다고 가정
	template<typename T>
	class Widget {/*...*/ };
	
	template<typename T>
	void swap(Widget<T>& a, Widget<T>& b) {		//비멤버 swap 함수
		nodes.swap(b);
	}
}

c++의 이름 탐색 규칙 == '인자 기반 탐색(argument-dependent lookup)' or '쾨니그 탐색(Koenig lookup)'
어떤 함수에 어떤 타입의 인자가 있으면, 
그 함수의 이름을 찾기 위해 해당 타입의 인자가 위치한 네임스페이스 내부의 이름을 탐색해 들어간다는 규칙
어떤 코드가 두 Widget 객체에 대해 swap을 호출해도, 네임스페이스 안에서 Widget 특수화 버전을 찾아낸다.

클래스 타입 전용의 swap이 되도록 많은 곳에서 호출되도록 하고 싶으면
그 클래스와 동일한 네임스페이스 안에 비멤버 버전의 swap을 만들어 넣고,
std::swap의 특수화 버전도 준비.;

template<typename T>
void doSomething(T& obj1, T& obj2) {
	swap(obj1, obj2);
}
= > 어떤 swap 호출할까 ?
1 std의 일반형 버전 2 std의 일반형을 특수화한 버전 3 T 타입 전용의 버전

타입 T 전용 버전이 있으면 그거 호출하고, ㅇ벗으면 std의 일반형 버전이 호출하고 싶다.;
template<typename T>
void doSomething(T& obj1, T& obj2) {
	using std::swap;	//std::swap을 이 함수 안으로 끌어올 수 있도록 만드는 문장
	swap(obj1, obj2);	//T 타입 전용의 swap을 호출. 앞에 std:: 쓰지 말기~ 그건 std 것만 쓰라는 뜻.
}

1 표준 swap이 우리 클래스 및 클래스 템플릿에 납득할 만한 효율이면, 놔두기

2 표준 swap 효율이 충분하지 않으면(클래스 및 클래스 템플릿이 'pimpl 관용구'와 비슷할 경우)
2.1 swap을 public으로. 예외를 던져선 안됨.
2.2 클래스or클래스 템플릿이 들어있는 네임스페이스에 비멤버 swap을 만들어 넣기. 
	위에서 만든 swap 멤버 함수를 이 비멤버 함수가 호출.
2.3 새로운 클래스를 만든다면, 그 클래스에 대한 std::swap의 특수화 버전을 준비. 
	특수화 버전에서도 swap 멤버 함수를 호출.

3 swap 호출 시, swap을 호출하는 함수가 std::swap을 볼 수 있도록 using 선언을 반드시 포함. 
	그 다음 swap을 호출하되, 네임스페이스 한정자 붙이지 않기.

멤버 버전의 swap이 예외 던지지 않아야 하는 이유: 
	항목 29 to be continued..
	비멤버 버전에서 표준 swap은 복사 생성과 복사 대입에 기반하는데, 복사 생성 및 복사 대입 함수는 예외 발생 허용.

이것만은 잊지 말자!
1 std::swap이 여러분의 타입에 대해 느리게 동작할 여지가 있다면, swap 멤버 함수를 제공
2 멤버 swap을 제공했으면, 이 멤버를 호출하는 비멤버 swap도 제공.
	클래스(템플릿이 아닌)에 대해서는 std::swap도 특수화.
3 사용자 입장에서 swap을 호출할 때는, std::swap에 대한 using 선언을 넣어 준 후에 네임스페이스 한정 없이 swap을 호출
4 사용자 정의 타입에 대한 std 템플릿을 완전 특수화하는 것은 가능.
	그러나 std에 어떤 것이라도 새로 추가하려고 들지 말기.;




구현

항목 26: 변수 정의는 늦출 수 있는 데까지 늦추는 근성을 발휘하자

예시: 비밀번호 길 경우 암호화하여 반환하는 함수;
//이 함수는 "encrypted 변수를 너무 일찍 정의해 버립니다.
std::string encryptPassword(const std::string& password) {
	using namespace std;
	string encrypted;	//이거이거
	if (password.length() < MinimumPasswordLength) {
		throw logic_error("Password is too short");
	}
	//...		//주어진 비밀번호를 암호화하여 enctypted 변수에 넣는 데 필요한 일들 했다고 가정
	return encrypted;
}
암호화 부분 가정;
//이 함수는 encrypted 변수가 필요할 때까지 이 변수의 정의를 늦추긴 했지만, 여전히 비효율적
void encrypt(std::string& s);
std::string encryptPassword(const std::string& password) {
	std::string encrypted;	//기본 생성자에 의해 만들어지는 encrypted
	encrypted = password;
	encrypt(encrypted);
	return encrypted;
}
=> 의미도 없고 비용도 만만치 않은 기본 생성자 호출 건너뛰자!;
std::string encryptPassword(const std::string& password) {
	std::string encrypted(password);	//변수를 정의함과 동시에 초기화. 이때 복사 생성자 쓰임.
	encrypt(encrypted);
	return encrypted;
}

루프는 ?
방법 A
Widget w;
for (int i = 0; i < n; ++i) {
	w = i/*i에 따라 달라지는 값*/;
}
방법 B
for (int i = 0; i < n; ++i) {
	Widget w(i/*i에 따라 달라지는 값)*/);
}
=> A방법이 생성자 소멸자 훨씬 더 불릴 것.
다만 프로그램의 이해도와 유지보수성이 안 좋아질 수 있다.
대입이 생성자-소멸자 쌍보다 비용이 덜 들고, 전체 코드에서 수행 성능에 민감한 부분을 건드리지 않다고 생각하면 B 방법.

이것만은 잊지 말자!
	변수 정의는 늦출 수 있을 때까지 늦추기!




항목 27: 캐스팅은 절약, 또 절약! 잊지 말쟈

c++ 동작 규칙: 어떤 일이 있어도 타입 에러가 생기지 않도록 보장한다.

c 스타일 캐스트
1 (T) 표현식
2 T(표현식)	: 함수 방식
=> 1,2 구형 스타일의 캐스트

c++ 스타일 캐스트
=> 신형 스타일의 캐스트
const_cast<T>(표현식) 
	: 객체의 상수성(constness)을 없애는 용도. (혹은 휘발성(volatileness)을 없애는 용도)
dynamic_cast<T>(표현식) 
	: 안전한 다운캐스팅할 떄 사용.
	: 주어진 객체가 어떤 클래스 상속 계통에 속한 특정 타입인지 아닌지를 결정.
	: 런타임 비용이 높음
reinterpret_cast<T>(표현식)
	: 포인터를 int로 바꾸는 등 하부 수준 캐스팅
	: 이식성이 없음. 책에서 딱 한 번 사용. ex. 원시 메모리용 디버깅 할당자 작성하는 방법
static_cast<T>(표현식)
	: 암시적 변환[비상수 객체를 상수 객체로 바꾸거나, int 를 double 로 바꾸는 등의 변환]을 강제로 진행할 때 사용. (그 반대는 안됨)
	: 타입 변환을 거꾸로 수행하는 용도(void*를 일반 타입의 포인터로 바꾸거나, 기본 클래스의 포인터를 파생 클래스의 포인터로 바꾸는 등)

명시하는 것이 컴파일 자체가 안 되어 에러 진단 가능

class Widget {
public:
	explicit Widget(int size);
};
void doSomeWork(const Widget& w);
doSomeWork(Widget(15));		//함수 방식 캐스트 문법으로 int로부터 Widget을 생성.
doSomeWork(static_cast<Widget>(15));		//c++방식 캐스트를 써서 int로부터 Widget을 생성.
= > 언제든지 신형 스타일 캐스트 권장.;

class Base {};
class Derived : public Base {};
Derived d;
Base *pb = &d;		//Derived* => Base*의 암시적 변환
=> 파생 클래스 객체에 대한 기본 클래스 포인터를 초기화하는 코드.
포인터의 변위(offset)를 Derived* 포인터에 적용하여 실제의 Base* 포인터 값을 구하는 동작이 런타임에 이루어짐.

ex. 객체의 주소를 char* 포인터로 바꿔서 산술 연산을 적용하는 코드는 거의 항상 미정의 동작

예시 안 좋은 코드
가상 함수를 파생 클래스에서 재정의해서 구현할 때 기본 클래스의 버전을 호출하는 문장을 가장 먼저 넣어달라-;
class Window {
public:
	virtual void onResize() {}
};
class SpecialWindow : public Window {
public:
	virtual void onResize() {
		static_cast<Window>(*this).onResize();		//*this를 Window로 캐스팅하고 그것에 대해 onResize를 호출하나 동작 안됨
	}
};
= > 캐스팅이 일어나며 *this의 기본 클래스 부분에 대한 사본이 임시적으로 만들어짐.
onResize는 기본 클래스 부분의 '사본'에 대고 호출된 것.
결국 Window::onResize를 호출하지 않고 지나감.

수정;
class SpecailWindow : public Window {
public:
	virtual void onResize() {
		Window::onResize();		//*this에서 Window::onResize를 호출.
	}
};


dynamic_cast
느리다..

파생 클래스의 함수를 호출하고 싶은데, 그 객체를 조작할 수단으로 기본 클래스의 포인터(or참조자)밖에 없을 경우...
1 파생 클래스 객체에 대한 포인터를 컨테이너에 담아둠.;
class Window {/*...*/ };
class SpecialWindow : public Window {
public:
	void blink();
};
typedef std::vector<std::tr1::shared_ptr<SpecialWindow> > VPSW;
VPSW winPtrs;
for (VPSW::iterator iter = vinPtrs.begin(); iter != winPtrs.end(); ++iter) {
	(*iter)->blink();		//if(SpecialWindow *psw = dynamic_cast<SpecailWindow*>(iter->get()))  psw->blink() 보다 더 나음
}

2 기본 클래스 인터페이스를 통해 조작할 수 있는 다른 방법
	: 아무 것도 안 하는 기본 blink를 구현해서 가상 함수로 제공;
class Window {
public:
	virtual void blink() { }
};
class SpecialWindow : public Window {
public:
	virtual void blink() {/*...*/ }
};
typedef std::vector<std::tr1::shared_ptr<Window> > VPW;
VPW winPtrs;
for (VPW::iterator iter = winPtrs.begin(); iter != winPtrs.end(); ++iter) {
	(*iter)->blink();
}

폭포식(cascading) dynamic_cast 설계 피하기!
if (SpecialWindow *psw1 = dynamic_cast<SpecailWindow1*>(iter->get())) { psw->blink(); }
if (SpecialWindow *psw2 = dynamic_cast<SpecailWindow2*>(iter->get())) { psw->blink(); }
if (SpecialWindow *psw3 = dynamic_cast<SpecailWindow3*>(iter->get())) { psw->blink(); }
...

잘 작성된 c++코드는 캐스팅을 거의 쓰지 않는다.

이것만은 잊지 말자!
1 다른 방법이 가능하다면 캐스팅은 피하십시오.
	특히 수행 성능에 민감한 코드는 dynamic_cast 는 다시 생각
2 캐스팅이 어쩔 수 없이 필요하다면, 함수 안에 숨기기.
	최소한 사용자는 자신의 코드에 캐스팅을 넣지 않고 이 함수를 호출할 수 있게 됨.
3 구형 스타일보다 c++ 스타일 캐스트 선호.
	발견하기도 쉽고, 설계자가 어떤 역할을 의도했는지 더 자세하게 드러남.




항목 28: 내부에서 사용하는 객체에 대한 핸들을 반환하는 코드는 되도록 피하자

예시: 사각형 사용;
class Point {
public:
	Point(int x, int y);
	void setX(int newVal);
	void setY(int newVal);
};
struct RectData {	//Rectangle에 쓰기 위한 점 데이터
	Point ulhc;		//좌측상단, 우측하단 (upper left-hand corner) (lower right-hand corner)
	Point lrhc;
};
class Rectangle {
private:
	std::tr1::shared_ptr<RectData> pData;
};

참조에 의한 방식으로 써볼까 ? ;
class Rectangle {
public:
	Point& upperLeft() const { return pData->ulhc; }
	Point& lowerRight() const { return pData->lrhc; }
};
Point coord1(0, 0);
Point coord2(100, 100);
const Rectangle rec(coord1, coord2);
rec.upperLeft().setX(50);
=> 상수 객체인 rec의 은밀한 곳의 Point 데이터 멤버를 참조자로 끌어와 바꿀 수 있다.

1. 클래스 데이터 멤버는 아무리 숨겨봤자 
	그 멤버의 참조자를 반환하는 함수들의 최대 접근도에 따라 캡슐화 정도가 정해진다.
	ulhc와 lrhc는 private 으로 선언되어도 실질적으로는 public 멤버.
	이들의 참조자를 반환하는 upperLeft, lowerRight 함수가 실질적으로 public 멤버 함수.
2 어떤 객체에서 호출한 상수 멤버 함수의 참조자 반환 값이 실제 데이터가 그 객체의 바깥에 저장되어 있다면,
	이 함수의 호출부에서 데이터의 수정이 가능하다.
	(비트수준 상숭성의 한계)


참조자, 포인터 및 반복자는 어쨌든 모두 핸들(handle, 다른 객체에 손을 댈 수 있게 하는 매개자).
어떤 객체의 내부요소에 대한 핸들을 반환하게 만들면,
언제든지 그 객체의 캡슐화를 무너뜨리는 위험을 무릅쓸 수밖에.

외부 공개가 차단된 멤버 함수에 대해, 포인터를 반환하는 멤버 함수를 만드는 일은 없어야 한다!;

class Rectangle {
public:
	const Point& upperLeft() const { return pData->ulhc; }
	const Point& lowerRight() const { return pData->lrhc; }
};
반환 타입에 const 떄문에 읽을 순 있지만, 쓸 수는 없게 됨.

읽기 가능한 이유는
Rectangle을 구성하는 Point를 들여다보도록 하자는 것은 처음부터 알고 시작한 설계이기 때문에,
의도적인 캡슐화 완화.

'무효참조 핸들(dangling handle)'
	: 핸들이 있기는 하지만 그 핸들을 따라갔을 떄 실제 객체의 데이터가 없는 것.

예시;
class GUIObject {/*...*/ };
const Rectangle boundingBox(const GUIObject& obj);	//값으로 반환

GUIObject *pgo;
const Point *pUpperLeft = &(boundingBox(*pgo).upperLeft());	//pgo가 가리키는 GUIObect의 사각 테두리 영역으로부터 좌측 상단 꼭짓점 포인터 얻음
=> 문장이 끝나면, 함수의 반환 값인 임시 객체가 소멸되며 그 안에 있는 Point 객체들도 없어짐.
=> pUpperLeft 포인터가 가리키는 객체는 없어짐

이것만은 잊지 말자!
	어떤 객체의 내부요소에 대한 핸들(참조자, 포인터 ,반복자)을 반환하는 것은 되도록 피하자.
	캡슐화 정도를 높이고, 상수 멤버 함수가 객체의 상수성을 유지한 채로 동작할 수 있도록 한다.
	무효참조 핸들이 생기는 경우를 최소화할 수 있다.

(어려웡..)




항목 29: 예외 안정성이 확보되는 그날 위해!

예외 안정성(exception safety)

예시: GUI 메뉴;		//..mutex는 여러 스레드의 공유자원에 대한 동시 접근을 막아 주는 역할
class PrettyMenu {
public:
	void changeBackground(std::istream& imgSrc);
private:
	Mutex mutex;	//이 객체 하나를 위한 뮤텍스
	Image *bgImage;		//현재의 배경그림	
	int imageChanges;		//배경그림이 바뀐 횟수
};
void PrettyMenu::changeBackground(std::istream& imgSrc) {
	lock(&mutex);	//뮤텍스 획득 (항목 14와 같음)
	delete bgImage;
	++imageChanges;
	bhImage = new Image(imgSrc);
	unlock(&mutex);	//뮤텍스 해제
}
=> 예외 안정성 고려 안됨 위험.

예외가 발생할 때..
1. 자원이 새도록 만들지 않는다.
	new Image 표현식에서 예외를 던지면 unlock 함수가 실행되지 않아 뮤텍스가 계속 잡힌 상태.
2. 자료구조가 더럽혀지는 것을 허용하지 않는다.
	new Image 가 예외를 던지면 bgImage가 가리키는 객체는 이미 삭제된 후.
	새 그림 깔리지도 않았는데 imageChanges 증가했고..;

1. 자원 누출 문제
void PrettyMenu::changeBackground(std::istream& imgSrc) {
	Lock ml(&mutex);		//항목 14에서 가져옴. 뮤텍스를 대신 획득하고 이것이 필요 없어질 시점에 바로 해제해주는 객체.
	delete bgImage;
	++imageChanges;
	bgImage = new Image(imgSrc);
}
Lock 등의 자원관리 전담 클래스 : 함수의 코드 길이가 짧아진다.
자원 누출 문제 해결.

2. 자료구조 오염 문제
예외 안정성을 갖춘 함수의 세 가지 보장(guarantee)

2.1.기본적인 보장(basic guarantee)
	함수 동작 중 예외 발생 시, 실행 중 모든 것들 유효한 상태로 유지.
	클래스 불변속성 만족.
	단, 사용자가 예측 어려움

2.2.강력한 보장(strong guarantee)
	예외 발생 시 프로그램의 상태를 절대로 변경하지 않겠다.
	이런 함수를 호출하는 것 : 원자적인(atomic) 동작.
	쓰기 쉬운 정도 : 강력한 보장 > 기본 보장.

2.3.예외불가 보장(nothrow guarantee)
	예외를 절대로 던지지 않겠다.약속한 동작은 언제나 끝까지 완수하라.
	int doSomething() throw();
	예외 발생 시 실행되는 처리자인 unexpected 함수 호출 필요.

위 3가지 보장 중 하나를 반드시 보장해야 함.
현실적으로 기본적인 보장 or 강력한 보장 중 하나.;

class PrettyMenu {
	std::tr1::shared_ptr<Image> bgImage;
};
void PrettyMenu::changeBackground(stdd::istream& imgSrc) {
	Lock ml(&mutex);
	bgImage.reset(new Image(imgSrc));		//bgImage의 내부 포인터를 new Image 표현식의 실행 결과로 바꿔치기
	++imageChanges;
}
배경그림이 스마트 포인터의 손에서 관리되고 있다.

'복사-후-맞바꾸기(copy-and-swap)' 전략
	객체를 수정하고 싶으면 그 객체의 사본을 하나 만들고 사본을 수정.
	수정 동작 중 어떤 예외가 던져지더라도 원본 객체는 바뀌지 않는 것.
	수정 완료 후 수정된 객체를 원본 객체와 맞바꾸는데, 이 작업을 '예외를 던지지 않는' 연산 내부에서 수행.

진짜 객체의 모든 데이터를 별도의 구현(implementation) 객체에 넣어두고,
그 구현 객체를 가리키는 포인터를 진짜 객체가 물고 있게 하는 식으로 구현.;

struct PMImple {
	std::tr1::shared_ptr<Image> bgImage;
	int imageChanges;
};	//PMImple이 struct로 선언된 이유 밑에서 확인
class PrettyMenu {
private:
	Mutex mutex;
	std::tr1::shared_ptr<PMImpl> pImpl;
};
void PrettyMenu::changeBackground(std::istream& imgSrc) {
	using std::swap;	//항목 25 참고
	Lock ml(&mutex);	//뮤텍스 잡고 드가자
	std::tr1::shared_ptr<PMImpl>pNew(new PMImpl(*pImpl));	//객체의 데이터 부분을 복사
	pNew->bgImage.reset(new Image(imgSrc));		//사본 수정
	++pNew->imageChanges;
	swap(pImpl, pNew);		//새 데이터로 바꿔 넣어 진짜로 배경그림 바꿈
}	//뮤텍스 놓기


함수의 부수효과(side effect).
비지역 데이터에 대해 부수효과를 주는 함수는 강력한 보장을 주기 까다롭다.

강력한 보장은 실용성이 확보될 때 바로 사용.

자원 관리가 필요할 때 자원 관리용 객체를 사용하는 것부터 시작 (항목 13 참고)

이것만은 잊지 말자!
1. 예외 안전성을 갖춘 함수는 실행 중 예외가 발생되더라도 자원을 누출시키지 않으며
	자료구조를 더럽힌 채로 내버려 두지 않습니다.
	이런 함수들이 제공할 수 있는 예외 안정성 보장은 기본적인 보장, 강력한 보장, 예외 금지 보장이 있습니다.

2. 강력한 예외 안정성 보장은 '복사-후-맞바꾸기' 방법을 써서 구현할 수 있지만,
	모든 함수에 대해 강력한 보장이 실용적인 것은 아닙니다.

3. 어떤 함수가 제공하는 예외 안정성 보장의 강도는, 그 함수가 내부적으로 호출하는 함수들이
	제공하는 가장 약한 보장을 넘지 않습니다.




항목 30: 인라인 함수는 미주알고주알 따져서 이해해 두자

인라인 함수 장점
	: 매크로보다 안전하고 쓰기 쉬움, 오버헤드 걱정할 필요 없음.
	: 컴파일러가 함수 본문에 대해 문맥별(context-specific) 최적화를 걸기 용이해짐
단점
	목적 코드의 크기가 커질 수 있다. 성능의 걸림돌이 될 수 있다. 페이징 횟수 증가, 명령어 캐시 적중률 떨어짐...

단, 본문 길이가 짧은 인라인 함수 사용 시 목적 코드의 크기도 작아질 수 있다.

inline은 컴파일러에 요청하는 것.
암시적 요청;
class Person {
public:
	int age() const { return theAge; }		//암시적인 인라인 요청: age는 클래스 정의 내부에서 정의되었다.
private:
	int theAge;
};

명시적 요청
예시 : 표준 라이브러리의 max 템플릿(<algorithm>에 있음);
template<typename T>
inline const T& std::max(const T& a, const T& b) { return a < b ? b : a; }

인라인 함수는 대체적으로 헤더 파일에 들어 있어야.
대부분의 빌드 환경에서 인라인을 컴파일 도중에 수행하기 때문.
그 함수의 본문으로 바꿔치기하려면, 컴파일러는 그 함수가 어떤 형태인지 알고 있어야.
대부분의 c++ 프로그램에서 함수 인라인은 컴파일 타임에 진행.

템플릿 역시, 대체적으로 헤더 파일에.
템플릿이 사용되는 부분에서 해당 템플릿을 인스턴스로 만들려면 어떻게 생겼는지 컴파일러가 알아야 하기 때문.
(모든 빌드 환경이 그런 건 아니지만..)

inline 이 '요청'인 이유
복잡한 함수는 절대 인라인 확장 대상에 넣지 않는다.
ex. 루프, 재귀 함수, 가상 함수
	virtual : 어떤 함수를 호출할지 결정하는 작업을 실행 중에 한다.
	<-> inline : 함수 호출 위치에 호출된 함수를 끼워 넣는 작업을 프로그램 실행 전에 한다.
ex. 인라인 함수를 함수 포인터를 통해 호출 등;
inline void f() { ... }
void(*pf)() = f;
f();		//호출은 인라인됨~
pf();		//인라인 안됨. 함수 포인터를 통해 호출중.


생성자와 소멸자는 인라인 좋지 않음
class Base {
public:
private:
	std::string bm1, bm2;		//Base 클래스의 멤버(bm)1, 멤버2
};
class Derived : public Base {
public:
	Derived() {}		//Derived의 생성자가 비어있다??
private:
	std::string dm1, dm2, dm2;		//Derived의 멤버
};

어떤 구현환경에서는 위 코드의 생성자는 다음과 같이 동작할 수 있따.
Derived::Derived() {
	Base::Base();
	try { dm1.std::string::string(); }
	catch (...) {
		Base::~Base();
		throw;
	}
	try { dm2.std::string::string(); }
	catch (...) {
		dm1.std::string::~string();	//이전 것 소멸
		Base::~Base();	//기본 클래스 소멸
		throw;
	}
	try { dm1.std::string::string(); }
	catch (...) {
		dm2.std::string::~string();
		dm1.std::string::~string();
		Base::~Base();
		throw;
	}
}
인라인이 난감해짐.

일단 아무것도 인라인하지 말고, 단순한 함수만 인라인 사용.

이것만은 잊지 말자!
1. 함수 인라인은 작고, 자주 호출되는 함수에 대해서만 하는 것으로.
	디버깅 및 라이브러리의 바이너리 업그레이드가 용이해지고, 
	자칫 생길 수 있는 코드 부풀림 현상이 최소화되며,
	프로그램의 속력이 더 빨리질 수 있는 여지가 최고로 많아짐
2. 함수 템플릿이 대개 헤더 파일에 들어간다는 일반적인 부분만 생각해서 이들을 inline으로 선언하면 안 됨슨




항목 31: 파일 사이의 컴파일 의존성을 최대로 줄이자!

;
class Person {
public:
	Person(const std::string& name, const Date& birthday, const Address& addr);
	std::string name() const;
	std::string birthDate() const;
	std::string address() const;
private:
	std::string theName;	//이하 구현 세부사항들
	Date theBirthDate;
	Address theAddress;
};

클래스 정의하는 파일을 보면 대개 아래와 비슷한 코드 발견;
#include <string>
#include "date.h"
#include <address.h>
이 녀석들이 골칫덩이
컴파일 의존성이 엮임.

구현 세부사항 바로 떼어볼까 ? ;
namespace std {
	class string;	//전방 선언 (틀린 것!)
}
class Date;		//전방 선언
class Address;	//전방 선언
class Person {
public:
	Person(const std::string& name, const Date& birthdayt, const Address& addr);
	std::string name() const;
	std::string birthDate() const;
	std::string address() const;
	//...
};
= > 문제 2가지
string은 사실 클래스가 아니라 typedef으로 정의한 타입동의어!
basic_string<char>를 typedef 한 것.
그러니 string에 대한 전방 선언이 맞을 리가...;

int main() {
	int x;
	Person p(params);	//클래스 정의된 정보를 봐야 컴파일러가 객체 하나의 크기가 얼마인지 알 수 있음.
}

인터페이스만 제공하는 클래스 / 인터페이스의 구현을 맡은 클래스를 만들어 보쟈!;
#include <string>	//표준 라이브러리 구성요소는 전방 선언을 하면 안 된다.
#include <memory>	//tr1::shared_ptr을 위한 헤더
class PersonImpl;	//Person의 구현 클래스에 대한 전방 선언
class Date;			//Person 클래스 안에서 사용하는 것들에 대한 전방 선언
class Address;
class Person {
public:
	Person(const std::string& name, const Date& birthday, const Address& addr);
	std::string name() const;
	std::string birthDate() const;
	std::string address() const;
private:
	std::tr1::shared_ptr<PersonImpl>pImpl;
};
구현 클래스(tr1::shared_ptr)에 대한 포인터
pimpl 관용구(pointer to implementation)
pImpl == 포인터 이름

인터페이스와 구현을 둘로 나누는 열쇠는 '정의부에 대한 의존성(dependencies on definitions)'을
'선언부에 대한 의존성(dependencies on declarations')로 바꾸어 놓는 데 있다.
컴파일 의존성을 최소화하는 핵심 원리.
헤더 파일을 만들 때는 실용적으로 의미를 갖는 한 자체조달(self-sufficient) 형태로.
정 안 되면 다른 파일에 의존성을 갖되, 정의부가 아닌 선언부에 대해 의존성을 갖도록 하는 것.

정리
1. 객체 참조자 및 포인터로 충분한 경우에는 객체를 직접 쓰지 않는다.
	어떤 타입에 대한 참조자 및 포인터를 정의할 때는 그 타입의 선언부만 필요.
	반면 어떤 타입의 객체를 정의할 때는 그 타입의 정의가 준비되어 있어야 한다.

2. 할 수 있으면 클래스 정의 대신 클래스 선언에 최대한 의존하도록 한다.
	어떤 클래스를 사용하는 함수를 선언할 때는 그 클래스의 정의를 가져오지 않아도 됨.
	심지어 그 클래스 객체를 값으로 전달하거나 반환하더라도 클래스 정의가 필요 없음.;
class Date;
Date today();
void clearAppointments(Date d);

Date를 정의하지 않고도 today와 함수를 선언할 수 있음.
함수 선언이 되어 있는 헤더 파일 쪽에 그 부담을 주지 않고,
실제 함수 호출이 일어나는 사용자의 소스 파일 쪽에 전가.

3. 선언부와 정의부에 대해 별도의 헤더 파일을 제공.;
#include "datefwd.h"	//Date 클래스를 선언하고 있는(그러나 정의하진 않는) 헤더 파일
Date today();
void clearAppointments(Date d);


템플릿 선언과 템플릿 정의를 분리할 수 있도록 하는 기능을 'export' 라는 키워드로 제공.
아직 잘 안 쓰는 키워드.

pimpl 관용구를 사용하는 Person 같은 클래스를 가리켜 '핸들 클래스' 라고 한다.;
#include "Person.h"		//Person 클래스의 정의를 포함
#include "PersonImpl.h"		//PersonImpl 클래스 정의도 포함. 이렇게 해야 멤버 함수 호출 가능
							//이 둘의 멤버 함수는 일대일로 대응됨. 인터페이스가 같음.
Person::Person(const std::string& name, const Date& birthday, const Address& addr) 
	: pImpl(new PersonImpl(name, birthday, addr) {}
std::string Person::name() const {
	return pImpl->name();
}
생성자에 new 사용.


핸들 클래스 방법 대신 다른 방법은 Person을 특수 형태의 추상 기본 클래스,
이른 바 '인터페이스 클래스' 로 만드는 방법.

어떤 기능을 나타내는 인터페이스를 추상 기본 클래스를 통해 마련해 놓고,
이 클래스로부터 파생 클래스를 만들 수 있게 하는 것.
파생이 목적.데이터 멤버도, 생성자나 가상 소멸자도 없으며, 인터페이스를 구성하는 순수 가상 함수만 들어있다.;

class Person {
public:
	virtual ~Person();
	virtual std::string name() const = 0;
	virtual std::string birthDate() const = 0;
	virtual std::string address() const = 0;
};
Person에 대한 포인터or참조자로 프로그래밍
인터페이스 클래스를 사용하기 위해서는 객체 생성 수단이 최소한 하나는 필요.
파생 클래스의 생성자 역할을 대신하는 어떤 함수를 만들어 놓고 이것을 호출.

이런 함수를 가리켜 '팩토리 함수'(항목 13), or 가상 생성자(virtual constructor).
주어진 인터페이스 클래스의 인터페이스를 지원하는 객체를 동적으로 할당한 후, 그 객체의 스마트 포인터를 반환.
함수는 인터페이스 클래스 내부에 정적 멤버로 선언되는 경우가 많다.;

class Person {
public:
	static std::tr1::shared_ptr<Person>create(const std::string& name, const Date& birthday, const Address& addr);
	//주어진 매개변수로 초기화되는 Person 객체를 새로 생성하고,
	//그것에 대한 쉐어드 포인터 반환.
};
사용자 입장 코드;
std::string name;
Date dateOfBirth;
Address address;
//Person 인터페이스를 지원하는 객체 한 개를 생성.
std::tr1::shared_ptr<Person>pp(Person::create(name, dateOfBirth, address));
std::cout << pp->name() << " was born on "
	<< pp->birthDate() << " and now lives at " << pp->address();
//위에서 생성한 객체는 pp가 유효범위를 벗어날 때 자동으로 삭제됨(항목 13 참고).


인터페이스 클래스의 인터페이스를 지원하는 구체 클래스(concrete class) 정의
정말로 실행되는 생성자(구체 클래스의 생성자)가 호출되어야 한다.
가상 생성자의 구현부를 갖고 있는 파일 안에서 이루어진다.

Person 클래스로부터 파생된 RealPerson 이란 구체 클래스가 있다면,
이 클래스는 자신이 상속받은 순수 가상 함수에 대한 구현부를 제공하는 식으로 만들어졌을 것.;

class RealPerson : public Person {
public:
	RealPerson(const std::string& name, const Date& birthday, const Address& addr)
		: theName(name), theBirthDate(birthday), theAddress(addr) {}
	virtual ~RealPerson() {}
	std::string name() const;		//멤버 함수에 대한 구현은 생략
	std::string birthDate() const;
	std::string address() const;
private:
	std::string theName;
	Date theBirthDate;
	Address theAddress;
};
std::tr1::shared_ptr<Person> Person::create(const std::string& name, const Date& birthday, const Address& adr) {
	return std::tr1::shared_ptr<Person>(new RealPerson(name, birthday, addr));
}
인터페이스 클래스(Person)로부터 인터페이스 명세를 물려받게 만든 후에, 그 인터페이스에 들어 있는 가상 함수 구현.

(어려웡..)


핸들 클래스 약점
	한 번 접근할 때마다 요구되는 간접화 연산이 한 단계 더 증가
	객체 하나씩을 저장하는 데 필요한 메모리 크기에 구현부 포인터의 크기가 더해짐
	구현부 포인터가 동적 할당된 구현부 객체를 가리키도록 어디선가 그 구현부 포인터의 초기화가 일어나야 하며, 
		연산 오버헤드 및 메모리 고갈 예외 가능성

인터페이스 클래스 약점
	호출되는 함수가 전부 가상 함수 - 함수 호출 시 가상 테이블 점프에 따르는 비용 소모.
	인터페이스 클래스에서 파생된 객체는 죄다 가상 테이블 포인터를 지녀야 함.
	-> 객체 하나 저장하는 데 필요한 메모리 크기를 늘림

공통 약점
	인라인 함수의 도움을 제대로 끌어내기 어려움.
	인라인 되게 하려면 함수 본문을 대개 헤더 파일에 두어야 하는데,
	핸들 클래스와 인터페이스 클래스는 함수 본문과 같은 구현부를 사용자의 눈으로부터 차단하는 데 중점

이것만은 잊지 말자!
1. 컴파일 의존성을 최소화하는 작업의 배경이 되는 가장 기본적인 아이디어는 '정의' 대신에 '선언'에 의존하게 하자.
	이 아이디어에 기반한 두 가지 접근 방법은 핸들 클래스와 인터페이스 클래스.
2. 라이브러리 헤더는 그 자체로 모든 것을 갖추어야 하며 선언부만 갖고 있는 형태여야 한다.
	이 규칙은 템플릿이 쓰이거나 쓰이지 않거나 동일하게 적용.;




상속, 그리고 객체 지향 설계
OOP 관련 기능 하나하나를 코드에 적용할 떄 무엇을 표현해야 정확하게 쓰는 것인가?
	ex. public 상속은 반드시 'is-a' 관계를 의미
	ex. 가상 함수의 의미는 "인터페이스가 상속되어야 한다."인 반면, 비가상 함수의 의미는 "인터페이스와 구현이 둘 다 상속되어야 한다."

항목 32: public 상속 모형은 반드시 "is-a (...는 ...의 일종이다)" 를 따르도록 만들자!

Derived 타입으로 만들어진 모든 객체는 또한 Base 타입의 객체이지만, '그 반대는 되지 않는다.'

B는 D보다 더 일반적인 개념을 나타내며,
D는 B보다 더 특수한 개념을 나타낸다.
B 타입의 객체가 쓰일 수 있는 곳에는 D 타입의 객체도 마찬가지로 쓰일 수 있다고 단정(assert)하는 것.
D is a B;

class Person {};
class Student : public Person {};
void eat(const Person& p);
void study(const Student& s);
Person p;
Student s;
eat(p);
eat(s);
study(s);
study(p);	//에러! p는 Student가 아님

class Bird {
public:
	virtual void fly();
};
class FlyingBird : public Bird {
public:
	virtual void fly();
};
class Penguin : public Bird {};
= > 모든 새가 날지 않음.
단, 소프트웨어에선 새의 부리와 날개에만 관심이 있고 비행 관련 할 일이 없을 경우,
Bird와 Penguin만 있어도 될 것.

런타임 에러 내기;
void error(const std::string& msg);
class Penguin : public Bird {
public:
	virtual void fly() { error("Attempt to make a penguin fly!"); }
};
= > 펭귄은 날 수 없다가 아닌, '펭귄은 날 수 있다. but 펭귄이 실제로 날려고 하면 에러가 난다.'
런타임 에러로 판별
fly 함수가 애초에 선언되지 않으면 컴파일 에러.
유효하지 않은 코드를 컴파일 단계에서 막아주는 인터페이스가 좋은 인터페이스!


예시: 상속 : 정사각형은 직사각형에 포함되니 상속?;
class Rectangle {
public:
	virtual void setHeight(int newHeight);
	virtual void setWidth(int newWidth);
	virtual int height() const;	//현재 값 반환 함수
	virtual int width() const;
};
void makeBigger(Rectangle& r) {	//r의 넓이를 늘리는 함수
	int oldHeight = r.height();
	r.setWidth(r.width() + 10);	//r의 가로 길이에 10 더하기
	assert(r.height() == oldHeight);	//r의 세로길이가 변하지 않는다는 조건에 단정문(assert) 걸기
}
class Square: public Rectangle {};
Square s;
assert(s.width() == s.height());	//이 단정문은 모든 직사각형에 대해 참이어야
makeBigger(s);	//상속된 것이므로, s는 Rectangle의 일종. 즉, s의 넓이를 늘릴 수 있따.
assert(s.width() == s.height());	//이 단정문이 모든 정사각형에 대해 참이어야.

makeBigger 함수가 변경하는 것은 s 그 자체이지, s의 사본이 아님.

public 상속: 기본 클래스 객체가 가진 '모든 것들'이 파생 클래스 객체에도 그대로 적용된다고 단정하는 상속.
정사각형: 가로, 세로 길이가 같아야 한다.
직사각형: 가로 길이가 세로 길이에 상관없이 바뀔 수 있다.
불일치.

클래스 사이 관계 "has-a(...는...를 가짐)"과 "is-implemented-in-terms-of(...는...를 써서 구현됨)"은
항목 38, 39 참고.

이것만은 잊지 말자!
	public 상속의 의미는 "is-a(...는...의 일종)". 
	기본 클래스에 적용되는 모든 것들이 파생 클래에 그대로 적용되어야 함.
	왜냐하면 모든 파생 클래스 객체는 기본 클래스 객체의 일종이기 때문이다.


항목 33: 상속된 이름을 숨기는 일은 피하자!

이름의 유효범위;
int x;
void someFunc() {
	double x;
	std::cin >> x;
}
지역 유효범위부터.
x라는 이름의 double이 x라는 이름의 int를 가리는 것.;

class Base {
private:
	int x;
public:
	virtual void mf1() = 0;
	virtual void mf2();
	void mf3();
};
class Derived : public Base {
	virtual void mf1();
	void mf4();
};

Base의 유효범위: x(데이터 멤버), 함수 3개, Derived의 유효범위
Derived의 유효범위: 함수 2개

컴파일러가 탐색
지역 유효범위 -> 클래스 내 유효범위 -> Base 클래스의 유효범위 -> 전역 요휴범위 순

오버로드 써보기 (비가상 함수가 상속된 함수를 오버로드하는 것은 별로 좋지 않지만 예시로);
class Base {
private:
	int x;
public:
	virtual void mf1() = 0;
	virtual void mf1(int);
	virtual void mf2();
	void mf3();
	void mf3(double);
};
class Derived : public Base {
public:
	virtual void mf1();
	void mf3();
	void mf4();
};
Base의 유효범위 : x(데이터 멤버), mf1() 2개, mf2 1개, mf3(2개), Derived의 유효범위
Derived의 유효범위 : 함수 3개

= > 이름 탐색 시점에서 Base::mf1과 Base::mf3은 Derived가 상속한 것이 아니게 된다.;
가상함수든 아니든... 타입이 다르든 아니든...

Derived d;
int x;
d.mf1();
d.mf1(x);	//에러. Derived::mf1이 Base::mf1을 가린다.
d.mf2();
d.mf3();
d.mf3(x);	//에러. Derived::mf3이 Base::mf3을 가린다.

class Base {
private:
	int x;
public:
	virtual void mf1() = 0;
	virtual void mf1(int);
	virtual void mf2();
	void mf3();
	void mf3(double);
};
class Derived : public Base {
public:
	using Base::mf1;	//Base에 있는 것들 중 mf1과 mf3을 이름으로 가진 것들을 Derived의 유효범위에서 볼 수 있도록 만듦.
	using Base::mf3;

	virtual void mf1();
	void mf3();
	void mf4();
};
Base의 유효범위 : x(데이터 멤버), mf1() 2개, mf2 1개, mf3(2개), Derived의 유효범위
Derived의 유효범위 : mf1() 1개, mf3() 2개, mf4() 1개

상속됨;
Derived d;
int x;
d.mf1();
d.mf1(x);	//성공. Base::mf1 호출
d.mf2();
d.mf3();
d.mf3(x);	//성공. Base::mf3 호출

기본 클래스에 오버로드된 함수가 그 클래스에 들어있고, 이 함수들 중 몇 개만 재정의(오버라이드) 하고 싶다면,
각 이름에 대해 using 선언.


Derived가 Base로부터 private 상속일 때, 상속하려는 mf1함수가 매개변수 없는 버전 하나밖에 없을 때,
	using 선언하면 이름에 해당되는 것들이 모두 파생 클래스로 내려가 버림.
	이때 다른 기법 필요.

전달 함수(forwarding function) 기법;
class Base {
public:
	virtual void mf1() = 0;
	virtual void mf1(int);	//이하 전과 동일
};
class Derived : private Base {	//private 상속일 때
public:
	virtual void mf1() {	//전달 함수. 암시적으로 인라인 함수
		Base::mf1();
	}
};
Derived d;
int x;
d.mf1();	//성공. Derived::mf1(매개변수없는버전)을 호출.
d.mf1(x);	//에러. Base::mf1은 가려져 있음.

항목 43에서 to be continued...

이것만은 잊지 말자!
1. 파생 클래스의 이름은 기본 클래스의 이름을 가립니다.
	public 상속에서는 이런 이름 가림 현상은 바람직하지 않습니다.
2. 가려진 이름을 다시 볼 수 있게 하는 방법으로, using 선언 혹은 전달 함수를 쓸 수 있다.




항목 34: 인터페이스 상속과 구현 상속의 차이를 제대로 파악하고 구별하자

(public) 상속 개념: 함수 인터페이스의 상속 / 구현의 상속
차이는 "독자 여러분 반갑습니다"에서 이야기한 
함수 선언(function declaration) 및 함수 정의(function definition)의 차이와 맥을 같이 한다.;

class Shape {
public:
	virtual void draw() const = 0;
	virtual void error(const std::string& msg);
	int objectID() const;
};
class Rectangle: public Shape {...};
class Ellipse: public Shape {...};

Shape는 추상 클래스.
순수 가상 함수인 draw
Shape 클래스의 인스턴스를 만들면 안됨.
파생 클래스만 인스턴스화 가능.

멤버 함수 인터페이스는 항상 상속되게 되어 있기 때문에,
기본 클래스에 해당하는 것들은 모두 파생 클래스에도 해당되어야 함.

class Shape {
public:
	virtual void draw() const = 0;
};

순수 가상 함수 특징
1. 어떤 순수 가상 함수를 물려받은 구체 클래스가 해당 순수 가상 함수를 다시 선언해야 한다.
2. 순수 가상 함수는 전형적으로 추상 클래스 안에서 정의를 갖지 않는다.

순수 가상 함수를 선언하는 목적은 파생 클래스에게 함수의 인터페이스만을 물려주는 것.
'draw 함수는 여러분이 직접 제공하도록 하슈. 난 어떻게 구현될지 생각 없소.'

순수 가상 함수에도 정의를 제공할 수 있음.
단, 클래스 이름을 한정자로 붙여 주어야 한다.;
Shape *ps = new Shape;	//에러!! Shape는 추상 클래스.

Shape *ps1 = new Rectangle;
ps1->draw();	//Rectangle::draw 호출

Shape *ps2 = new Ellipse;
ps2->draw();	//Ellipse::draw 호출

ps1->Shape::draw();	//Shape::draw 호출
ps2->Shape::draw();	//Shape::draw 호출


단순(비순수) 가상 함수.
단순 가상 함수를 선언하는 목적: 파생 클래스로 하여금 함수의 인터페이스뿐만 아니라
	그 함수의 기본 구현도 물려받게 하자.;
class Shape {
public:
	virtual void error(const std::string& msg);
};
'에러 함수는 여러분이 지원하슈. 새로 만들 생각 없으면 기본 버전 쓰슈'

다만 단순 가상 함수에서 함수 인터페이스, 기본 구현을 한꺼번에 지정하는 건 위험할 수 있음.
예시;
class Airport {/*...*/};
class Airplane {
public:
	virtual void fly(const Airport& destination);
};
void Airplane::fly(const Airport& destination) {
	//주어진 목적지로 비행기를 날려 보내는 기본 동작 원리를 가진 코드
}
class ModelA: public Airplane {...};
class ModelB: public Airplane {...};

Airplane::fly는 가상함수.
이 상태에서 새로운 모델 추가;
class ModelC : public Airplane {
	//모르고 fly 함수가 선언되지 않음을 가정
};
Airport PDX(/*...*/);
Airplane *pa = new ModelC;
pa->fly(PDX);	//Airplane::fly 함수가 호출됨!
기본 동작을 원한다고 명시적으로 밝히지 않았는데도 이 동작을 물려받는 데 아무런 걸림돌이 없는 위험.

개선안
가상 함수의 인터페이스와 그 가상 함수의 기본 구현을 잇는 연결 관계를 끊어 버리는 것.;
class Airplane {
public:
	virtual void fly(const Airport& destination) = 0;
protected:
	void defaultFly(const Airport& destination);
};
void Airplane::defaultFly(const Airport& destination) {
	//주어진 목적지로 비행기를 날려 보내는 기본 동작 원리를 가진 코드
}
Ariplane::fly 함수가 순수 가상 함수로 바뀜.
이전 구현은 defaultFly라는 이름의 별도의 함수로 거듭남.
defaultFly 함수를 인라인 호출.;
class ModelA : public Airplane {
public:
	virtual void fly(const Airport& destination) {
		defaultFly(destination);
	}
};
class ModelB : public Airplane {
public:
	virtual void fly(const Airport& destination) {
		defaultFly(destination);
	}
};
= > 기본 구현을 우연찮게 물려받을 가능성이 없어짐;
class ModelC : public Airplane {
public:
	virtual void fly(const Airport& destination);
};
void ModelC::fly(const Airport& destination) {
	//주어진 목적지로 ModelC 비행기를 날려 보내는 코드
}

Airplane::defaultFly 함수는 protected 멤버.
Airplane 및 그 클래스의 파생 클래스만 내부적으로 사용하는 구현 세부사항이다.
비행기를 사용하는 사용자는 '비행기가 날 수 있다'라는 점만 알면 될 뿐,
'비행 동작이 어떻게 구현되는가'는 신경 쓰지 말아야 합니다.

Airplane::defaultFly 함수는 또한 비가상 함수.
파생 클래스 쪽에서 이 함수를 재정의해선 안됨. (항목 36에서도 알려쥼);


class Shape {
public:
	int objectID() const;
};
멤버 함수가 비가상 함수로 되어 있다는 것: 파생 클래스에서 다른 행동이 일어나지 않을 것 가정.
비가상 멤버 함수는 '클래스 파생에 상관없이 변하지 않는 동작'을 지정하는 데 쓰임.

비가상 함수를 선언하는 목적은 파생 클래스가 함수 '인터페이스와 더불어 그 함수의 필수적인 구현(mandatory implementation)'
을 물려받게 하는 것.

Shape::objectID의 선언은
"Shape 및 이것에서 파생된 모든 객체는 객체의 식별자를 내어 주는 함수를 갖게 되겠지"
"객체 식별자를 계산하는 방법은 항상 똑같겠군. 실제 계산 방법은 Shape::objectID의 정의에서 결정되고,"
"파생 클래스는 이것을 바꿀 수 없겠는걸."
비가상 함수는 클래스 파생에 상관없는 불변동작(invariant).
하여, 파생 클래스에서 재정의 할 수 없음.


클래스 실수 2가지
실수 1. 모든 멤버 함수를 비가상 함수로 선언하는 것.
파생 클래스를 만들더라도 기본 클래스의 동작을 특별하게 만들 만한 여지가 없어진다.
특히 비가상 소멸자가 문젯거리 (항목 7 참고)
기본 클래스로 쓰이는 클래스는 십중팔구 가상 함수

cf) 가상 함수의 비용 문제? 80-20 법칙. (항목 30..)
전체 실행 시간의 80%가 소모되는 부분이 전체 코드의 20%밖에 되지 않는다는 법칙.
함수 호출 중 80%를 가상 함수로 두더라도 프로그램의 전체 수행 성능에는 손실 별로 없음

실수 2. 모든 멤버 함수를 가상 함수로 선언.
물론 항목 31의 인터페이스 클래스 같이 불변동작을 갖고 있어야 한다면, 있을 수 있음.

이것만은 잊지 말자!
1. 인터페이스 상속은 구현 상속과 다르다.
	public 상속에서, 파생 클래스는 항상 기본 클래스의 인터페이스를 모두 물려받는다.
2. 순수 가상 함수는 인터페이스 상속만을 허용한다.
3. 단순(비순수) 가상 함수는 인터페이스 상속과 더불어 기본 구현의 상속도 가능하도록 지정한다.
4. 비가상 함수는 인터페이스 상속과 더불어 필수 구현의 상속도 가하도록 지정한다.


'구현 상속: 멤버 함수를 호출할 수는 있지만, 스스로 멤버 함수를 가지지 않는 상속'
'인터펭이스 상속: 상속받은 객체에서 함수를 외부호출할 수 있음.'




항목 35: 가상 함수 대신 쓸 것들도 생각해 두는 자세를 시시때때로 길러 두자

예시
게임에서 체력을 멤버 함수로 제공하기로 결정
체력을 어떻게 계산하는지는 캐릭터마다 다를 것이 뻔하므로, 가상 함수로 선언해보자.;
class GameCharacter {
public:
	virtual int healthValue() const;
};
순수 가상 함수가 아닌 것으로 보아, 체력치를 계산하는 기본 알고리즘이 제공된다는 것을 앎 (항목 34 참고)
'에러 함수는 여러분이 지원하슈. 새로 만들 생각 없으면 기본 버전 쓰슈'

가상 함수 은폐론: "가상 함수는 반드시 private 멤버로 두어야 한다."

class GameCharacter {
public:
	int healthValue() const {	//파생 클래스는 이제 이 함수를 재정의 할 수 없습니다.
		//...	//사전 동작
		int retVal = doHealthValue();	//실제 동작 수행
		//...	//사후 동작
		return retVal;
	}
private:
	virtual int doHealthValue() const {	//파생 클래스는 이 함수를 재정의할 수 있습니다.
		//...
	}
};
public 비가상 멤버 함수를 통해 private 가상 함수를 간접적으로 호출하게 만드는 방법
'비가상 함수 인터페이스(non-virtual interface: NVI) 관용구'
템플릿 메서드라 불리는 디자인 패턴을 구현
이 관용구에 쓰이는 비가상 함수(ex. healthValue)를 가상 함수의 랩퍼(wrapper)라고 부른다.

NVI 관용구에서는 파생 클래스의 가상 함수 재정의를 허용.
상속받은 private 가상 함수를 파생 클래스가 재정의할 수 있다는 규칙


'함수 포인터로 구현한 전략 패턴'
예시: 각 캐릭터의 생성자에 체력치 계산용 함수의 포인터를 넘기고, 이 함수를 호출해서 실제 계산 수행;
class GameCharacter;	//전방 선언
int defaultHealthCalc(const GameCharacter& gc);		//체력치 계산에 대한 기본 알고리즘 구현
class GameCharacter {
public:
	typedef int(*HealthCalcFunc)(const GameCharacter&);
	explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc) : healthFunc(hcf) {}
	int healthValue() const { 
		return healthFunc(*this); 
	}
private:
	HealthCalcFunc healthFunc;
};
전략(Strategy) 패턴의 단순한 응용 예
함수 포인터 이점
1. 같은 캐릭터 타입으로부터 만들어진 객체(인스턴스)들도 체력치 함수를 각각 다르게 가질 수 있음.;
class EvilBadGuy : public GameCharacter {
public:
	explicit EvilBadGuy(HealthCalcFunc hcf = defaultHealthCalc)
		: GameCharacter(hcf) {}
};
int loseHealthQuickly(const GameCharacter&);	//다른 동작 원리로 구현된 체력치 계산 함수들
int loseHealthSlowly(const GameCharacter&);
EvilBadGuy ebg1(loseHealthQuickly);		//같은 타입인데도 체력치 변화가 다르게 나오는 캐릭터들
EvilBadGuy ebg2(loseHealthSlowly);

2. 게임이 실행되는 도중에 특정 캐릭터에 대한 체력치 계산 함수를 바꿀 수 있음.



'tr1::function으로 구현한 전략 패턴'

tr1::function 계열의 객체는 함수호출성 개체(callable entity)(함수 포인터, 함수 객체 or 멤버 함수 포인터)를 가질 수 있음.

class GameCharacter;	//전방 선언
int defaultHealthCalc(const GameCharacter& gc);		//체력치 계산에 대한 기본 알고리즘 구현
class GameCharacter {
public:
	//HealthCalcFunc는 함수호출성 객체로서, GameCharacter와 호환되는 어떤 것이든 넘겨받아서 호출될 수 있으며,
	//int와 호환되는 모든 타입의 객체를 반환합니다.
	typedef std::tr1::function<int(const GameCharacter&)>HealthCalcFunc;
	explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc) : healthFunc(hcf) {}
	int healthValue() const {
		return healthFunc(*this);
	}
private:
	HealthCalcFunc healthFunc;
};
=> HealthCalcFunc는 tr1::function 템플릿을 인스턴스화 한 것에 대한 typedef 타입.;

std::tr1::function<int(const GameCharacter&)>
const GameCharacter에 대한 참조자를 받고 int를 반환하는 함수.


tr1::function 객체, 좀더 일반화된 함수 포인터를 물게 될 것.
다음 코드에서 정리.;

short calcHealth(const GameCharacter&);	//체력치 계산 함수. 반환 타입이 int가 아닌 부분에 주목

struct HealthCalculator {	//체력치 계산용 함수 객체를 만들기 위한 클래스
	int operator()(const GameCharacter&) const {/*...*/};
};
class GameLevel {
public:
	float health(const GameCharacter) const;	//체력치 계산에 쓰일 멤버 함수. 반환 타입이 int가 아닌 부분에 주목
};
class EvilBadGuy : public GameCharacter { };	//예전의 그것과 같음.
class EyeCandyCharacter : public GameCharacter { };	//생성자는 위의 것과 똑같다고 가정

//main
EvilBadGuy ebg1(calcHealth);	//체력치 계산을 위한 함수를 사용하는 캐릭터
EyeCandyCharacter eccl(HealthCalcCulator());
GameLevel currentLevel;
EvilBadGuy ebg2(std::tr1::bind(&GameLevel::health, currentLevel, _1));	//체력치 계산을 위한 멤버 함수를 사용하는 캐릭터.

위 정의문에서는 ebg2의 체력치를 계산하기 위해 GameLevel 클래스의 health 멤버 함수를 써야 한다고 함.
그 담 설명..
(어려웡..)

_[숫자] 형태의 토큰은 tr1::bind로 묶인 함수를 호출할 때 대체할 자유 매개변수(free parameter) 리스트에 대한 자리채움자.


"고전적인" 전략 패턴

체력치 계산 함수를 나타내는 클래스 계통을 따로 만들고,
체력치 계산 함수는 이 클래스 계통의 가상 멤버 함수로.;

class GameCharacter;
class HealthCalcFunc {
public:
	virtual int calc(const GameCharacter& gc) const { }
};
HealthCalcFunc defaultHealthCalc;
class GameCharacter {
public:
	explicit GameCharacter(HealthCalcFunc *phcf = &defaultHealthCalc)
		: pHealthCalc(phcf) {}
	int healthValue() const {
		return pHealthCalc->calc(*this);
	}
private:
	HealthCalcFunc *pHealthCalc;
};
표준적인 전략 패턴 구현 방법에 친숙한 경우 빨리 이해.
기존의 체력치 계산 알고리즘을 조정/개조 가능


요약
1. 비가상 인터페이스 관용구(NVI 관용구) 사용
	공개되지 않은 가상 함수를 비가상 public 멤버 함수로 감싸서 호출하는, 템플릿 메서드 패턴의 한 형태.

2. 가상 함수를 함수 포인터 데이터 멤버로 대체
	전략 패턴의 핵심만 보여줌

3. 가상 함수를 tr1::function 데이터 멤버로 대체하여,
	호환되는 시그니처를 가진 함수호출성 개체를 사용할 수 있도록: 역시 전략 패턴의 한 형태.

4. 한쪽 클래스 계통에 속해 있는 가상 함수를 다른 쪽 계통에 속해 있는 가상 함수로 대체
	: 전략 패턴의 전통적인 구현 형태.


이것만은 잊지 말자!
1. 가상 함수 대신에 쓸 수 있는 방법으로 NVI 관용구 및 전략 패턴을 들 수 있다.
	이 중 NVI 관용구는 그 자체가 템플릿 메시드 패턴의 한 예.

2. 객체에 필요한 기능을 멤버 함수로부터 클래스 외부의 비멤버 함수로 옮기면,
	그 비멤버 함수는 그 클래스의 public 멤버가 아닌 것들을 접근할 수 없다는 단점

3. tr1::function 객체는 일반화된 함수 포인터처럼 동작.
	이 객체는 주어진 대상 시그니처와 호환되는 모든 함수호출성 개체를 지원한다.




항목 36: 상속받은 비가상 함수를 파생 클래스에서 재정의하는 것은 절대 금물!

예시;
class B {
public:
	void mf();
};
class D: public B {/*...*/ };

D x;
B *pB = &x;
pB->mf();	//이 코드가
D *pD = &x;
pD->mf();	//이 코드처럼 동작하지 않는다.
=> 다를 수도 있다!

mf가 비가상 함수, D클래스가 자체적으로 mf 함수를 또 정의할 때.;
class D : public B {
public:
	void mf();	//B::mf를 가려버림
};
pB->mf();	//B::mf를 호출
pD->mf();	//D::mf를 호출


cf)바인딩: 프로그램 소스에 쓰인 각종 내부 요소, 이름, 식별자들에 대해 값 혹은 속성을 확정하는 과정.
이 과정이 빌드 중에 이루어지면 정적 바인딩
실행 중에 이루어지면 동적 바인딩.
c++ 가상 함수의 바인딩은 문서상으론 동적 바인딩으로 되어 있으나,
구현상으로는 런타임 성능을 높이기 위해 정적 바인딩을 쓰고 있다.
즉, 컴파일 중에 아예 가상 함수 테이블을 파생 클래스에 맞게 바꿈으로써, 겉보기에 파생 클래스 타입에서 오버라이드한 가상 함수를 호출하는 것처럼 보임.


B::mf 및 D::mf 등의 비가상 함수는 정적 바인딩(static binding)으로 묶임.

반면 가상 함수는 동적 바인딩.진짜로 가리키는 대상 타입의 함수를 호출.

B 객체에 해당되는 모든 것들이 D 객체에 그대로 적용.
B에서 파생된 클래스는 mf 함수의 인터페이스와 구현을 모두 물려받는다.
mf는 B클래스에서 비가상 멤버 함수이기 때문.

위 상황에서 B의 mf 구현을 사용해야 한다면, '모든 D는 B의 일종'이란 명제는 거짓이 된다!
'mf는 클래스 파생에 상관없이 B에 대한 불변동작을 나타낸다.'도 참이 되지 않음.
이땐 가상 함수로 만드는 것.

항목 7에서 다형성을 부여한 기본 클래스의 소멸자를 반ㄴ드시 가상 함수로 만들어야 하는 이유이기도 하다!

이것만은 잊지 말자!

상속받은 비가상 함수를 재정의하는 일은 절대로 하지 맙시다!




항목 37: 어떤 함수에 대해서도 상속받은 기본 매개변수 값은 절대로 재정의하지 말자!

가상 함수는 동적으로 바인딩, 기본 매개변수 값은 정적으로 바인딩.
정적 바인딩 == 선행 바인딩(early binding)
동적 바인딩 == 지연 바인딩(late binding)

객체의 정적 타입(static type)은 소스 안에 선언문을 통해 그 객체가 갖는 타입.;

//기하학 도형을 나타내는 클래스
class Shape {
public:
	enum ShapeColor { Red, Green, Blue };

	//모든 도형은 자기 자신을 그리는 함수를 제공해야.
	virtual void draw(ShapeColor color = Red) const = 0;
};
class Rectangel : public Shape {
public:
	//기본 매개변수 값이 달라진 부분을 놓치지 마세요. 큰일났어!
	virtual void draw(ShapeColor color = Green) const;
};
class Circle : public Shape {
public:
	virtual void draw(ShapeColor color) const;
};

포인터 나타내볼까;
Shape *ps;
Shape *pc = new Circle;
Shape *pr = new Rectangle;

모두 정적 타입(static type) == Shape *

객체가 어떻게 동작할 것이냐를 가리키는 타입
동적 타입(dynamic type)
pc => Circle*
pr => Rectangle*

프로그램 실행중 대입문을 바뀔 수 있음
ps = pc;	//ps=>Circle*
ps = pr;	//ps=>Rectangle*

가상함수;
pc->draw(Shape::Red);	//Circle::draw(Shape::Red)를 호출
pr->draw(Shape::Red);	//Rectangle::draw(Shape::Red)를 호출

기본 매개변수 값이 설정된 가상 함수는? ;
pr->draw()	//Rectangle::draw(Shape::Red)를 호출해버림슨!!!!!
정적 타입이 Shape*이기 때문.;

class Shape {
public:
	enum ShapeColor { Red, Green, Blue };
	virtual void draw(ShapeColor color = Red) const = 0;
};
class Rectangle : public Shape {
public:
	virtual void draw(ShapeColor color = Red) const;
};
=> 코드 중복 + 의존성.

비가상 인터페이스(non-virtual interface) 관용구(NVI 관용구) 사용해보자!!
	파생 클래스에서 재정의할 수 있는 가상 함수를 private 멤버로 두고,
	이 가상 함수를 호출하는 public 비가상 함수를 기본 클래스에 만들어 두기;

class Shape {
public:
	enum ShapeColor { Red, Green, Blue };
	void draw(ShapeColor color = Red) const {	//비가상 함수
		doDraw(color);	//가상 함수 호출
	}
private:
	virtual void doDraw(ShapeColor color) const = 0;	//진짜 작업은 이 함수에서.
};
class Rectangle : public Shape {
public:
private:
	virtual void draw(ShapeColor color) const;	//기본 매개변수 값이 없음.
};

비가상 함수는 파생 클래스에서 오버라이드되면 안 되기 때문에,
draw 함수의 color 매개변수에 대한 기본값을 깔끔하게 Red로 고정.


이것만은 잊지 말자!
	상속받은 기본 매개변수 값은 절대로 재정의해선 안 된다.
	왜냐하면 기본 매개변수 값은 정적으로 바인딩되는 반면, 
	가상함수(오버라이드 할 수 있는 유일한 함수)는 동적으로 바인딩되기 때문입니다.




항목 38: "has-a(...는...를 가짐)" 혹은 "is-implemented-in-terms-of(...는...를 써서 구현됨)"를 모형화할 때는 객체 합성을 사용하자!

합성(composition)이란, 어떤 타입의 객체들이 그와 다른 타입의 객체들을 포함하고 있을 경우에 성립하는 그 타입들 사이의 관계.
;
class Address { /*...*/ };
class PhoneNumber {};
class Person {
public:
private:
	std::string name;
	Address address;
	PhoneNumber voiceNumber;
	PhoneNumber faxNumber;
};
합성 == 레이어링(layering) == 포함(containment) == 통합(aggregation) == 내장(embedding) 등

객체 합성의 의미 2가지
"has-a(...는...를 가짐)"
"is-implemented-in-terms-of(...는...를 써서 구현됨)"

왜 2가지?
소프트웨이 영역 2가지
응용 영역(application domain)
	사람, 이동수단, 비디오 프레임 등 일상생활 사물 본 뜬 것
구현 영역(implementation domain)
	버퍼, 뮤텍스, 탐색 트리 등 순수하게 시스템 구현만을 위한 인공물

객체 합성이 응용 영역에서 일어나면 has-a / 구현 영역에서 일어나면 is-implemented-in-terms-of 관계


Set<T>는 list<T>로부터 상속받게 하자??;
template<typename T>
class Set : public std::list<T> {};
list 객체는 중복 원소를 가질 수 있는 컨테이너.
Set 객체는 원소가 중복되면 안 된다.
하여, Set이 list의 일종(is-a)이라는 명제는 참이 아니다.
list 객체에 해당하는 사실들이 Set 객체에서도 통하는 게 아니다.

이때 is implemented in terms of 형태 설계!;
template<class T>
class Set {
public:
	bool member(const T& item) const;

	void insert(const T& item);
	void remove(const T& item);

	std::size_t size() const;
private:
	std::list<T> rep;	//Set 데이터의 내부 표현부
};

template<typename T>
bool Set<T>::member(const T& item) const {
	return std::find(rep.begin(), rep.end(), item) != rep.end();
}

template<typename T>
void Set<T>::insert(const T& item) {
	if (!member(item)) rep.push_back(item);
}
template<typename T>
void Set<T>::remove(const T& item) {
	typename std::list<T>::iterator it =
		std::find(rep.begin(), rep.end(), item);
	if (it != rep.end()) rep.erase(it);
}
template<typename T>
std::size_t Set<T>::size() const {
	return rep.size();
}
=> is-a가 아니라 is-implemented-in-terms-of 다!

이것만은 잊지 말자!
1. 객체 합성(composition)의 의미는 public 상속이 가진 의미와 완전히 다르다.
2. 응용 영역에서 객체 합성의 의미는 has-a(...는...를 가짐)다.
	구현 영역에서는 is-implemented-in-terms-of(...는...를 써서 구현됨) 의미다.




항목 39: private 상속은 심사숙고해서 구사하자

public 상속 is-a.
private 상속 써보기;

class Person {};
class Student : private Person {};
void eat(const Person& p);
void study(const Student& s);
Person p;
Student s;
eat(p);
eat(s);		//에러! Student는 Person의 일종이 아니다.

기본 클래스로부터 물려받은 멤버는 파생 클래스에서 모조리 private 멤버가 됨.
private 상속의 의미는 is-implemeted-in-terms-of.
'구현만 물려받을 수 있다. 인터페이스는 국물도 없다'
D 객체가 B 객체를 써서 구현됨.
소프트웨어 설계(design) 도중 의미 없음. 단지 소프트웨어 구현(implementation) 중에만 의미를 가짐.

할 수 있으면 객체 합성, 꼭 해야 하면 private 상속.
비공개 멤버를 접근할 때 혹은 가상 함수를 재정의할 경우.

cf) 프로파일: 프로그램이 실행되면서 호출되는 함수들의 순차적 리스트 및 
각 함수의 실행 시간과 전체 시간에 대한 실행 시간 비율을 분석하는 작업 혹은 그 결과.;

class Timer {
public:
	explicit Timer(int tickFrequency);
	virtual void onTick() const;		//일정 시간이 경과할 떄마다 자동으로 이것이 호출됨.
};

Widget 클래스로 Timer 클래스를 상속받고자 함.;
class Widget : private Timer {
private:
	virtual void onTick() const;	//Widget 사용 자료 등을 수집함.
};
상속 방식을 private으로 한 덕택에, Timer의 public 멤버인 onTick 함수는 Widget에서 private 멤버가 됨.
public 으로 선언하면 안됨. (함수 호출할 수 있을 것으로 오해함);


class Widget {
private:
	class WidgetTimer : public Timer {
	public:
		virtual void onTick() const;
	};
	WidgetTimer timer;
};
객체 합성
private 중첩 클래스 선언.

private 상속과 비교하면 복잡하나, public 상속에 객체 합성 조합이 쓰이는 이유

1. Widget 클래스를 설계하는 데 있어서 파생은 가능하게 하되,
파생 클래스에서 onTick 을 재정의할 수 없도록 설계 차원에서 막고 싶을 때 유용.
Widget의 파생 클래스는 아무리 용을 써도 WidgetTimer에 접근조차 불가능.
파생 클래스에서 가상 함수를 재정의할 수 없게 막는 기능

2. Widget의 컴파일 의존성을 최소화하고 싶을 때 좋음.
Widget이 Timer에서 파생된 상태라면, Widget이 컴파일될 때 Timer의 정의도 끌어올 수 있어야 함.
Widget의 정의부 파일에서 Timer.h 같은 헤더를 #include 해야 한다.

반면, 지금의 설계에서는 WidgetTimer의 정의를 Widget으로부터 빼내고,
Widget이 WidgetTimer 객체에 대한 포인터만 갖도록 만들어 두면,
WidgetTimer 클래스를 간단히 선언하는 것만으로도 컴파일 의존성을 슬쩍 피할 수 있음.
(컴파일 의존성 최소화: 항목 31 참고)


private 상속을 사용해야 하는 경우? 
비공개 멤버를 접근할 때 혹은 가상 함수를 재정의할 경우.
이 경우 거의 없음.

공백 클래스(empty class)는 개념적으로 차지하는 메모리 공간이 없다.
C++에는 "독립 구조(freestanding)의 객체는 반드시 크기가 0을 넘어야 한다"는 사항이 있음

class Empty {};
class HoldsAnInt {
private:
	int x;
	Empty e;	//메모리 요구가 없어야 하는데..
};
=> sizeof(HoldsAnInt) > sizeof(int) 됨.
sizeof(Empty)의 값은 1.
컴파일러는 공백 객체에 char 한 개를 슬그머니 끼워넣음.
바이트 정렬(alignment)(항목 50 참고)이 필요하다면 클래스에 바이트 패딩 과정을 추가할 수 있음
	HoldsAnInt 객체의 크기는 char 하나의 크기를 넘게 됨.
단, 이 제약은 파생 클래스 객체의 기본 클래스 부분에는 적용되지 않음.
	이때의 기본 클래스 부분은 독립구조 객체, 홀로서기를 한 객체가 아니기 때문.

Empty 타입의 객체를 데이터 멤버로 두지 말고 Empty로부터 상속 시켜보자;
class HoldsAnInt: private Empty {
private:
	int x;
};
sizeof(HoldsAnInt) == sizeof(int)
이 공간절약 기법은 "공백 기본 클래스 최적화(empty base optimization: EBO)"
EBO는 단일 상속 하에서만 적용.

이것만은 잊지 말자!
1. private 상속의 의미는 is-implemented-in-terms-of(...는...를 써서 구현됨)이다.
	대개 객체 합성과 비교해서 쓰이는 분야가 많지는 않지만, 
	파생 클래스 쪽에서 기본 클래스의 protected 멤버에 접근해야 할 경우,
	or 상속받은 가상 함수를 재정의해야 할 경우 private 상속이 의미가 있다.

2. 객체 합성과 달리, private 상속은 공백 기본 클래스 최적화(EBO)를 활성화시킬 수 있다.




항목 40: 다중 상속은 심사숙고해서 사용하자

다중 상속(multiple inheritance: MI).
단일 상속(single ingheritance: SI).;

class BorrowableItem {	//라이브러리로부터 가져올 수 있는 어떤 것
public:
	void checkOut();
};
class ElectronicGadget {
private:
	bool checkOut() const;	//자체 테스트를 실시하고, 성공 여부를 반환.
};
class MP3Player:		//여기서 MI가 된다.(몇몇 라이브러리로부터 기능을 가져온다.)
	public BorrowableItem, public ElectronicGadget 
	{ /*...*/ };
MP3Player mp;
mp.checkOut();	//모호성 발생! 어느 checkOut?
개선? => mp.BorrowableItem::checkOut();
=> private 멤버 함수 호출이라 안됨.

"죽음의 MI 마름모꼴(deadly MI diamond)" 모양이 나올 수 있음.;
class File {};
class InputFile : public File {};
class OutputFile : public File {};
class IOFile : public InputFile, public OutputFile {};

c++은 데이터 멤버를 중복 생성 해버림.
가상 기본 클래스(virtual base class)로 만듦.
기본 클래스로 삼을 클래스에 직접 연결된 파생 클래스에서 가상 상속(virtual inheritance)를 사용하게 만듦.;

class File {};
class InputFile : virtual public File {};
class OutputFile : virtual public File {};
class IOFile : public InputFile, public OutputFile {};

c++ 표준 라이브러리 중 basic_ios 계열이 이러함.

파생 클래스들로 인해 가상 기본 클래스 부분을 초기화 할 때 규칙
1. 초기화가 필요한 가상 기본 클래스로부터 클래스가 파생된 경우, 이 파생 클래스는 가상 기본 클래스와의 거리에 상관없이
	가상 기본 클래스의 존재를 염두에 두고 있어야 한다.
2. 기존의 클래스 계통에 파생 클래스를 새로 추가할 때도 그 파생 클래스는 가상 기본 클래스의 초기화를 떠맡아야 한다.

가상 기본 클래스에 대한 조언
1. 쓸 필요 없으면 사용하지 마라. 비가상 상속이 기본.
2. 그래도 써야 한다면, 가상 기본 클래스에는 데이터를 넣지 않도록.;

class IPerson {
public:
	virtual ~Iperson();
	virtual std::string name() const = 0;
	virtual std::string birthDate() const = 0;
};
추상 클래스를 인스턴스로 만들 수 없으니 포인터 및 참조자를 통해 프로그래밍 해야 할 것.
IPerson의 사용자는 팩토리 함수(항목 31 참고)를 사용해서 구체 파생 클래스를 인스턴스로.;

//유일한 데이터베이스 ID로부터 IPerson 객체를 만들어내는 팩토리 함수다.
//반환 타입이 원시 포인터가 아닌 이유가 궁금하면 항목 18 필독!
std::tr1::shared_ptr<IPerson> makePerson(DatabaseID, personIdentifier);
//사용자로부터 데이터베이스 ID를 얻어내는 함수
DatabaseID askUserForDatabaseID();
DatabaseID id(askUserForDatabaseID());
std::tr1::shared_ptr<IPerson> pp(makePerson(id));	//IPerson 인터페이스를 지원하는 객체를 하나 만들고 pp로 가리키게 함.
													//이후에는 *pp의 조작을 위해 IPerson의 멤버 함수를 사용.

makePerson 함수가 인스턴스로 만들 수 있는 구체 클래스가 IPerson으로부터 파생되어 있어야.
CPerson이라고 가정.
CPerson은 IPerson으로부터 물려받은 순수 가상 함수에 대한 구현을 제공.
데이터베이스 전담 클래스인 PersonInfo를 보니 CPerson에 필요한 핵심 기능을 가지고 있더라고 가정.;
class PersonInfo {
public:
	explicit PersonInfo(DatabaseId pid);
	virtual ~PersonInfo();
	virtual const char * theName() const;
	virtual const char * theBirthDate() const;
private:
	virtual const char * valueDelimOpen() const;
	virtual const char * valueDelimClose() const;
};

다양한 서식으로 문자열 출력을 구분할 수 있다고 가정
valueDelim~는 시작 구분자, 끝 구분자를 지정할 수 있도록 함.;

const char * PersonInfo::valueDelimOpen() const {
	return "[";
}
const char * PersonInfo::valueDelimClose() const {
	return "]";
}
const char * PersonInfo::theName() const {
	//변환 값을 위한 버퍼를 예약. 이 버퍼는 정적 메모리이기 때문에, 자동으로 모두 0으로 초기화됨.
	static char value[Max_Formatted_Field_Value_Length];
	std::strcpy(value, valueDelimOpen());
	//value에 들어있는 문자열에 이 객체의 name 필드를 덧붙인다. (버퍼 오버런, 스레딩 문제 일으킬 수 있음. 항목 21 참고)
	//끝 구분자를 value에 추가.
	std::strcat(value, valueDelimClose());
	return value;
}

theName은 valueDelimOpen을 호출 = > 시작 구분자를 만들고 = >
name값 자체를 만든 다음 = > valueDelimClose를 호출하도록 구현됨.

valueDelimOpen, Close는 가상 함수이기 때문에,
theName이 반환하는 결과는 PersonInfo에만 좌우되는 것이 아니라
Person - Info로부터 파생된 클래스에도 좌우된다.

CPerson 상속 IPerson;
class IPerson {		//이 클래스가 나타내는 것은 용도에 따라 구현될 인터페이스.
public:
	virtual ~Iperson();
	virtual std::string name() const = 0;
	virtual std::string birthDate() const = 0;
};
class DatabaseID { /*...*/ };

class PersonInfo {		//이 클래스에는 IPerson 인터페이스를 구현하는 데 유용한 함수가 들어있다.
public:
	explicit PersonInfo(DatabaseID pid);
	virtual ~PersonInfo();
	virtual const char * theName() const;
	virtual const char * theBirthDate() const;
	virtual const char * valueDelimOpen() const;
	virtual const char * valueDelimClose() const;
};

class CPerson : public IPerson, private PersonInfo {		//MI가 쓰임~
public:
	explicit CPerson(DatabaseID pid) : PersonInfo(pid) {}
	virtual std::string name() const {		//IPerson 클래스의 순수 가상 함수에 대해 파생 클래스의 구현을 제공.
		return PersonInfo::theName();
	}
	virtual std::string birthDate() const {
		return PersonInfo::theBirthDate();
	}
private:
	const char * valueDelimOpen() const { return ""; }	//가상 함수들도 상속되므로 이 함수들에 대한 재정의 버전을 만들기.
	const char * valueDelimClose() const { return ""; }
};
=>다중 상속의 예시.
다만 진짜진짜 필요할 거 같을 때만 쓰기.

이것만은 잊지 말자!
1. 다중 상속은 단일 상속보다 확실히 복잡하다. 
	새로운 모호성 문제를 일으킬 뿐만 아니라 가상 상속이 필요해질 수도 있다.

2. 가상 상속을 쓰면 크기 비용, 속도 비용이 늘어나며, 초기화 및 대입 연산의 복잡도가 커진다.
	따라서 가상 기본 클래스에는 데이터를 두지 않는 것이 현실적으로 가장 실용적.

3. 가상 상속을 적법하게 쓸 수 있는 경우가 있다. 여러 시나리오 중 하나는,
	인터페이스 클래스로부터 public 상속을 시킴과 동시에 구현을 돕는 클래스로부터 private 상속을 시키는 것.;





템플릿과 일반화 프로그래밍

템플릿.
템플릿의 응용 분야로 파생된 일반화 프로그래밍(generic programming, 조작할 객체의 타입과 상관없이 코드를 작성하도록 하는 개념) 가능
튜링 완전(Turing-complete)성을 갖고 있다.
cf) 튜링 완전: 범용 튜링 기계와 동등한 계산 능력을 갖고 있는 어떤 추상 기계 혹은 프로그래밍 언어.

다시 말해, 계산 가능한(computable) 어떤 값도 계산할 수 있다.
템플릿 메타프로그래밍(metaprogramming)이라는 새로운 영역 탄생.


항목 41: 템플릿 프로그래밍의 천릿길도 암시적 인터페이스와 컴파일 타임 다형성부터.

원래 프로그래밍 세계는
'명시적 인터페이스(explicit interface)'와 '런타임 다형성(runtime polymorphism)'
예시;
class Widget {
public:
	Widget();
	virtual ~Widget();
	virtual std::size_t size() const;
	virtual void normalize();
	void swap(Widget& other);	//항목 25 참고.
};
void doProcessing(Widget& w) {
	if (w.size() > 10 && w != someNastyWidget) {
		Widget temp(w);
		temp.normalize();
		temp.swap(w);
	}
}
w는 Widget 타입으로 선언되었기 때문에, w는 Widget 인터페이스르 지원해야 한다.
	Widget이 선언된 h 파일 등 소스 코드에서 찾으면 어떤 형태인지 확인할 수 있으므로,
	이런 인터페이스를 가리켜 '명시적 인터페이스'.
	소스 코드에 명시적으로 드러나는 인터페이스

Widget의 멤버 함수 중 몇 개는 가상 함수이므로, 이 가상 함수에 대한 호출은 '런 타임 다형성'에 의해 이루어진.
	즉, 특정한 함수에 대한 실제 호출은 w의 동적 타입(항목 37 참고)를 기반으로 런타임에 결정됨.

템플릿
'암시적 인터페이스(implicit interface)'와 '컴파일 타임 다형성(compile-time polymorphism)';
template<typename T>
void doProcessing(T& w) {
	if (w.size() > 10 && w != smoeNastyWidget) {
		T temp(w);
		temp.normalize();
		temp.swap(w);
	}
}

w가 지원해야 하는 인터페이스는 이 템플릿 안에서 w에 대해 실행되는 연산이 결정함.
size, normalize 등..
이 템플릿이 컴파일되려면 몇 개의 표현식이 '유효(valid)'해야 하는데, 
이 표현식들은 바로 T가 지원해야 하는 암시적 인터페이스.

w가 수반되는 함수 호출 operator>, operator!= 함수 호출 시 해당 호출 성공 위한 템플릿의 인스턴스화가 일어남.
컴파일 도중에 일어남.
인스턴스화를 진행하는 함수 템플릿에 어떤 템플릿 매개변수가 들어가느냐에 따라 호출되는 함수가 달라지기 때문에,
이것을 가리켜 '컴파일 타임 다형성' 이라고 한다.


런타임, 컴파일 타임 다형성 헷갈리지 않기
오버로드된 함수 중 지금 호출할 것을 골라내는 과정(컴파일 중에 일어남)과
가상 함수 호출의 동적 바인딩(프로그램 실행 중)의 차이점과 흡사.

명시적, 암시적 인터페이스 설명
명시~ 는 대개 함수 시그니처로 이루어짐
cf) 시그니처: 함수의 이름, 매개변수 타입, 반환 타입 등을 통틀어 이름.;
class Widget {
public:
	Widget();
	virtual ~Widget();
	virtual std::size_t size() const;
	virtual void normalize();
	void swap(Widget& other);
};
생성자, 소멸자, size 등 함수, 매개변수 타입, 반환 타입, 각 함수의 상수성 여부로 이루어짐.
	컴파일러가 자동으로 만든 복사 생성자, 복사 대입 연산자도 포함됨(항목 5 참고).
	typedef 타입이 있을 경우 이것도 포함.)
	다만, 데이터 멤버는 public에 있어도 시그니처에 들어가지 않음.

반면 암시적 인터페이스는 함수 시그니처에 기반하고 있지 않음.
	암시~ 를 이루는 요소는 유효 '표현식(expression)'.;
template<typename T>
void doProcessing(T& w) {
	if (w.size() > 10 && w != someNastyWidget) {}
}
T에서 제공될 암시적 인터페이스에는 다음의 제약
1. 정수 계열의 값을 반환하고 이름이 size인 함수를 지원해야 함.
2. T 타입의 객체 둘을 비교하는 operator!= 함수를 지원해야 함.

=> 다만 둘 다 연산자 오버로딩 가능성이 있어서 만족시킬 필요 없음.

암시적 인터페이슨느 그저 유효 표현식의 집합.
if (w.size() > 10 && w != someNastyWidget) {}
에서 함수에 대한 제약은?
if 괄호 안 bool과 호환 / 복사 생성자, normalize, swap 함수에 대한 호출이 T 타입의 객체에 대해 '유효'해야 함.


이것만은 잊지 말자!
1. 클래스 및 템플릿은 모두 인터페이스와 다형성을 지원함.
2. 클래스의 경우, 인터페이스는 명시적이며 함수의 시그니처를 중심으로 구성됨.
	다형성은 프로그램 실행 중에 가상 함수를 통해 나타남.
3. 템플릿 매개변수의 경우, 인터페이스는 암시적이며 유효 표현식에 기반을 두어 구성됨.
	다형성은 컴파일 중에 템플릿 인스턴스와 함수 오버로딩 모호성 해결을 통해 나타남.;




항목 42: typename 의 두 가지 의미를 제대로 파악하자!

둘 차이점 ? ;
template<class T> class Widget;
template<typename T> class Widget;
차이 없음. 스타일 따라 다름.


예시: 컨테이너에 담길 원소들 중 두 번째 것의 값을 출력하는 이상한 코드;
template<typename C>
void print2nd(const C& container) {
	if (container.size() >= 2) {
		C::const_iterator iter(container.begin());	//첫째 원소에 대한 반복자 얻기
		++iter;	//iter를 두 번째 원소로 옮기기.
		int value = *iter;	//이 원소를 다른 int로 복사.
		std::cout << value;
	}
}

iter의 타입은 C::const_iterator
템플릿 매개변수인 C에 따라 달라지는 타입.
템플릿 내의 이름 중에 이렇게 템플릿 매개변수에 종속된 것을 가리켜 '의존 이름(dependent name)'이라 함.

의존 이름이 어떤 클래스 안에 중첩된 경우는 '중첩 의존 이름(nested dependent name)'이라 함.
'중첩 의존 타입 이름(nested dependent type name)'
타입을 참조하는 중첩 의존 이름.

위 value같은 int 는 템플릿 매개변수가 어떻든 상관없는 타입 이름.
'비의존 이름(non-dependent name)'.


template<typename C>
void print2nd(const C& container) {
	C::const_iterator * x;
}
= > C::~~와 x를 곱한 형태일 수도 있는 멍청한 코드.

중첩 의존 이름은 기본적으로 타입이 아닌 것으로 해석됨.;
template<typename C>
void print2nd(const C& container) {
	if (container.size() >= 2) {
		typename C::const_iterator iter(container.begin());
	}
}
=> 제대로 된 코드. C::const_iterator가 반드시 타입이라 알려줘야 함.
템플릿 안에서 중첩 의존 이름을 참조할 경우에는, 이름 앞 typename 키워드
(예외 좀 이따 나옴);


template<typename C>
void f(const C& container,			//typename 쓰면 안됨
	typename C::iterator iter);		//typename 꼭 써야 함
=> C는 중첩 의존 타입 이름이 아님.
즉, 템플릿 매개변수에 의존적인 어떤 것도 C를 품고 있지 않음.


(예외) 중첩 의존 타입 이름이 기본 클래스의 리스트에 있거나 
멤버 초기화 리스트 내의 기본 클래스 식별자로 있을 경우는 안됨.;

template<typename T>
class Derived : public Base<T>::Nested {		//상속되는 기본 클래스 리스트
	explicit Derived(int x) : Base<T>::Nested(x) {		//멤버 초기화 리스트에 있는 기본 클래스 식별자
		typename Base<T>::Nested temp;		//중첩 의존 타입 이름이며, 기본 클래스 리스트에도 없고,
											//멤버 초기화 리스트의 기본 클래스 식별자도 아님.
	}
};

template<typename IterT>
void workWithIterator(IterT iter) {
	typename std::iterator_traits<IterT>::value_type temp(*iter);
}
C++ 표준의 특성정보(traits) 클래스(항목 47 참고)를 사용한 것뿐.
IterT 타입의 객체로 가리키는 대상의 타입.
IterT 객체가 가리키는 것과 똑같은 타입의 지역 변수(temp)를 선언한 후,
iter가 가리키는 객체로 그 temp를 초기화하는 문장.

IterT가 vector<int>::iterator라면 temp의 타입은 int.
std::iterator_traits<IterT>::value_type은 중첩 의존 타입 이름.
value_type이 iterator_traits<IterT> 안에 중첩되어 있고, IterT는 템플릿 매개변수이므로.
이 앞에는 typename !

std::iterator_traits<IterT>::value_type
이거 치기 너무 숨막힌다.
typedef으로 이름 만들기.;
template<typename IterT>
void workWithIterator(IterT iter) {
	typedef typename std::iterator_traits<IterT>::value_type value_type;
	value_type temp(*iter);
}
"typedef typename T" 형태.


잊지 말자!
1. 템플릿 매개변수를 선언할 때, class 및 typename 은 서로 바꾸어 써도 무방함.
2. 중첩 의존 타입 이름을 식별하는 용도에서 반드시 typename 을 사용.
	중첩 의존 이름이 기본 클래스 리스트에 있거나
	멤버 초기화 리스트 내의 기본 클래스 식별자로 있는 경우에는 예외.;




항목 43: 템플릿으로 만들어진 기본 클래스 안의 이름에 접근하는 방법을 알아 두자!

예시: 몇 개 회사에 메시지 전송할 수 있는 응용 프로그램
전송용 메시지는 암호화될 수도, 가공텍스트(비암호화) 형태가 될 수도.;
class CompanyA {
public:
	void sendCleartext(const std::string& msg);
	void sendEncrypted(const std::string& msg);
};
class CompanyB {
public:
	void sendCleartext(const std::string& msg);
	void sendEncrypted(const std::string& msg);
};
//...
class MsgInfo {/*...*/};	//메시지 생성에 사용되는 정보르 담기 위한 클래스

template<typename Company>
class MsgSender {
public:
	//...생성자 소멸자 등등
	void sendClear(const MsagInfo& info) {
		std::string msg;	
		//info로부터 msg를 만든다.;
		Company c;
		c.sendCleartext(msg);
	}
	void sendSecret(const MsgInfo& info) {/*...*/}	//sendClear 함수와 비슷. 단, c.sendEncrypted 함수를 호출하는 차이
};
//로그 추가
template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	void sendClearMsg(const MsgeInfo& info) {
		//"메시지 전송 전" 정보를 로그에 기록;
		sendClear(info);					//기본 클래스의 함수를 호출하는데, 이 코드는 컴파일되지 않습니다!
		//"메시지 전송 후" 정보를 로그에 기록;
	}
};

LoggingMsgSender::sendClearMsg와
MsgSender::sendClear 이름 다름.
기본 클래스로부터 물려받은 이름을 파생 클래스에서 가리는 문제(항목 33) 해결.
상속받은 비가상 함수를 재정의하는 문제(항목 36) 해결.

다만 컴파일되지 않음.
LoggingMsgSender 클래스 템플릿의 정의와 마주칠 때, 컴파일러는 이 클래스가 어디서 파생된 것인지 모름.
Company가 무엇이 될지 알 수 없음.

문제를 구체적으로 알아보자
예시: 암호화된 통신만을 사용.;
class CompanyZ {		//이 함수는 sendCleartext 함수를 제공 안 함.
public:
	void sendEncrypted(const std::string& msg);
};

MsgSender 템플릿은 CompanyZ 에 쓰긴엔 좀 그럼.
이 템플릿은 sendClear 함수를 제공하기 때문.
CompanyZ를 위한 MsgSender의 특수화 버전 만듦. sendCleartext 함수가 빠진 것만 제외하면 일반형 템플릿과 똑같음.;
template<>
class MsgSender<CompanyZ> {
public:
	void sendSecret(const MsgInfo& info) { }
};

template<> 의 뜻: 이건 템플릿도 아니고 클래스도 아니다.
다시 말하면, 위의 코드는 MsgSender 템플릿을 템플릿 매개변수가 CompanyZ일 때 쓸 수 있도록 특수화한 버전이다.
'완전 템플릿 특수화(total template specialization)'이라고 한다.
템플릿의 매개변수들이 빠짐없이 구체적인 타입으로 정해진 상태.

다시 아까 코드로;
template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	void sendClearMsg(const MsgeInfo& info) {
		//...
		sendClear(info);					//만약 Company == CompanyZ라면 이 함수는 있을 수 조차 없다!
		//...
	}
};
기본 클래스가 MsgSender<CompanyZ>은 말이 안 됨. sendClear 함수 없으니..

C++의 템플릿화된 기본 클래스는 멋대로 안 뒤지는 동작이 발현되지 않도록! 하는 방법 3가지

1. this->;
template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	void sendClearMsg(const MsgInfo& info) {
		this->sendClear(info)	//sendClear가 상속되는 것으로 가정
	}
};

2. using 선언;
template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	using MsgSender<Company>::sendClear		//컴파일러에게 sendClear함수가 기본 클래스에 있다고 가정하라고 알려줌.
	void sendClearMsg(const MsgInfo& info) {
		sendClear(info)	//sendClear가 상속되는 것으로 가정
	}
};

3. 호출할 함수가 기본 클래스의 함수라는 점을 명시적으로 지정;
template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	void sendClearMsg(const MsgInfo& info) {
		MsgSender<Company>::sendClear(info)	//sendClear함수가 상속되는 것으로 가정함.
	}
};
다만 세 번째 방법은 가상 함수 바인딩이 무시되어 단점이 있음.


세 가지 방법 모두 동작 원리는 같음.
기본 클래스 템플릿이 이후에 어떻게 특수화되더라도
원래의 일반형 템플릿에서 제공하는 인터페이스를 그대로 제공할 것이라 컴파일러에게 약속.
약속은 LoggingMsgSender 등의 파생 클래스 템플릿을 컴파일러가 구문분석하는 데 반드시 필요하지만,
그 약속이 다음과 같으면;
LoggingMsgSender<CompanyZ>zMsgSender;
MsgInfo msgData;
zMsgSender.sendClearMsg(msgData);	//에러!

컴파일되지 않음.
sendClearMsg는 MsgSender<CompanyZ> 클래스에 안 들어 있다는 사실도 컴파일러가 알아챈 후.

기본 클래스의 멤버에 대한 참조가 무효한지를 컴파일러가 진단하는 과정이 미리(파생 클래스 템플릿의 정의가 구문분석될 때) 들어가느냐,
아니면 나중에(파생 클래스 템플릿이 특정한 매개변수를 받아 인스턴스화될 때) 들어가느냐가 바로 핵심.
C++은 '이른 진단(early diagnose)'을 선호하는 정책으로 결정.
파생 클래스가 템플릿으로부터 인스턴스화될 때 컴파일러가 기본 클래스의 내용에 대해 아무것도 모르는 것으로 가정하는 것.

잊지 말자!
1. 파생 클래스 템플릿에서 기본 클래스 템플릿의 이름을 참조할 때는, "this->"를 접두사로 붙이거나
	기본 클래스 한정문을 명시적으로 써 주는 것으로 해결.;




항목 44: 매개변수에 독립적인 코드는 템플릿으로부터 분리시키자!

템플릿 장점 짱짱
템플릿 잘못 사용하면 '코드 비대화(code bloat)'

코드 중복 방지책
공통성 및 가변성 분석(commonality and variability analysis)
공통 부분을 별도의 새로운 클래스에 옮긴 후, 클래스 상속 or 객체 합성(항목 32, 38, 39) 사용해서
원래의 클래스들이 공통 부분을 공유하도록 하기.
고유 부분(varying part)은 원래의 위치에 남아있음.

템플릿이 여러 번 인스턴스화될 때 발생할 수 있는 코드 중복을 알아채야 한다.

예시: 역행렬 연산;
template<typename T, std::size_t n>		//T 타입의 객체를 원소로 하는 n행 n열의 행렬을 나타내는 템플릿.
class SquareMatrix {
public:
	void insert();		//주어진 행렬을 그 저장공간에서 역행렬로 만듦.
};
=> 이 템플릿은 T 타입 매개변수도 받지만, size_t 타입의 '비타입 매개변수(non-type parameter)'인 n도 받도록 되어있음.;

SquareMatrix<double, 5> sm1;
sm1.invert();		//SquareMatrix<double, 5>::invert를 호출
SquareMatrix<double, 10> sm2;
sm2.invert();		//SquareMatrix<double, 10>::invert를 호출

invert의 사본이 인스턴스화.
5x5 행렬에 대해 동작하는 함수, 10x10 ~
=> 전형적인 코드 비대화 형태.;

template<typename T>
class SquareMatrixBase {	//정방행렬에 대해 쓸 수 있는 크기에 독립적인 기본 클래스
protected:
	void invert(std::size_t matrixsize);	//주어진 크기의 행렬을 역행렬로 만드는 역할
};
template<typename T>
class SquareMatrix: private SquareMatrixBase<T> {
private:
	using SquareMatrixBase<T>::invert;		//기본 클래스의 invert가 가려지는 것을 막기 위한 문장. 항목 33.
public:
	void invert() {
		this->invert(n);	//invert의 기본 클래스 버전에 대해 인라인 호출을 수행.
	}
};
=> 값을 매개변수로 받는 별도의 함수를 만들고, 5와 10을 매개변수로 넘겨서 함수 호출.
모든 정방행렬은 오직 한 가지의 SquareMatrixBase 클래스를 공유.
같은 원소 타입의 정방행렬이 사용하는 기본 클래스 버전의 invert 함수도 오직 한 개의 사본.

SquareMatrixBase::invert 함수는 파생 클래스에서 코드 복제를 피할 목적으로만 마련한 장치.
그래서 protected 멤버.
파생클래스의 invert함수가 암시적 인라인 함수(항목 30)

this-> 표기는 항목 43에서 이야기한 템플릿화된 기본 클래스의 멤버 함수 이름이 파생 클래스에서 가려지는 문제를 피하기 위한 것.
using 선언도 마찬가지. 이땐 using 선언 불필요할 수 있음.

상속 관계도  private.
기본 클래스는 순전히 파생 클래스의 구현을 돕기 위한 것 외엔 아무 이유도 없다는 사실을 드러냄. (항목 39)

문제
기본 클래스 함수는 진짜 행렬을 저장한 데이터가 어디에 있는지 모름.
행렬 값들을 메모리에 담는 포인터를 SquareMatrixBase가 저장하게 하자.;

template<typename T>
class SquareMatrixBase {
protected:
	SquareMatrixBase(std::size_t n, T *pMem)	//행렬 크기를 저장하고, 행렬 값에 대한 포인터를 저장.
		: size(n), pData(pMem) {}
	void setDataPtr(T *ptr) { pData = ptr; }	//pData에 다시 대입.
private:
	std::size_t size;	//행렬의 크기
	T *pData;	//행렬 값에 대한 포인터
};

template<typename T, std::size_t n>
class SquareMatrix : private SquareMatrixBase<T> {
public:
	SquareMatrix()
		: SquareMatrixBase<T>(n, data) {}	//행렬 크기(n) 및 데이터 포인터를 기본 클래스로 올려 보냄슨
private:
	T data[n*n];
};
=> 동적 메모리 할당 필요 없는 객체. 다만 객체 자체의 크기가 좀 커질 수 있다.

각 행렬의 데이터를 힙에 둘 수도 있다.;
template<typename T, std::size_t n>
class SquareMatrix : private SquareMatrixBase<T> {
public:
	SquareMatrix() : SquareMatrixBase<T>(n, 0), pData(new T[n*n]) {		//기본 클래스의 포인터를 널로 설정하고, 행렬 값의 메모리를 할당하고,
		this->setDataPtr(pData.get());			//파생 클래스의 포인터에 그 메모리를 물려 놓은 후, 이 포인터의 사본을 기본 클래소 올려보냄슨
	}
private:
	T data[n*n];
};

성과
SquareMatrix에 속한 멤버 함수 중 상단수가 기본 클래스 버전을 호출하는 단순 인라인 함수가 됨
똑같은 타입의 데이터를 원소로 갖는 모든 정방행렬들이 행렬 크기에 상관없이 이 기본 클래스 버전의 사본 하나를 공유함.
행렬 크기가 다른 SquareMatrix 객체는 저마다 고유의 타입을 가지고 있음.
	SquareMatrix<double, 5>와 SquareMatrix<double, 10>은 타입이 다름.


공짜는 아님
크기별 고정 버전의 경우, 행렬 크기가 컴파일 시점에 투입되는 상수이기 때문에 
상수 전파(constant propagation) 등의 최적화가 먹혀 들기 좋음
생성되는 기계 명령어에 대해 이 크기 값이 즉치 피연산자(immediate operand)로 박히는 것도 이런 종류의 최적화.
크기별 독립 버전은 이 혜택 없음.

(어려웡..)

다른 혜택
실행 코드가 작아진다.
프로그램의 작업 세트 크기가 줄어들면서 명령어 캐시 내의 참조 지역성도 향상
cf) 작업 세트: 한 프로세스에서 자주 참조하는 페이지의 집합
cf) 참조 지역성: 프로세스의 메모리 참조가 실행 중에 균일하게 흩어져 있지 않으며 특정 시점 및 특정 부분에 집중된다는 경험적/실험적 특성.
	시간적 지역성: 지금 참조된 메모리는 멀지 않은 나중에 또 참조될 가능성이 높다는 성질
	공간적 지역성: 지금 참조된 메모리와 가까운 곳에 있는 메모리가 참조될 가능성이 높다는 성질
	캐시: 바로 이러한 참조 지역성을 이용해서 수행 성능을 높이는 고속 메모리다.

이번 항목에서는 비타입 템플릿 매개변수로 인한 코드 비대화를 다룸.

잊지 말자!
1. 템플릿을 사용하면 비슷비슷한 클래스와 함수가 여러 벌 만들어짊.
	따라서 템플릿 매개변수에 좋속되지 않은 템플릿 코드는 비대화의 원인이 됨.
2. 비타입 템플릿 매개변수로 생기는 코드 비대화의 경우, 템플릿 매개변수를 함수 매개변수 혹은
	클래스 데이터 멤버로 대체함으로써 비대화를 종종 없앨 수 있음.
3. 타입 매개변수로 생기는 코드 비대화의 경우, 동일한 이진 표현구조를 가지고 인스턴스화되는 타입들이
	한 가지 함수 구현을 공유하게 만듦으로써 비대화를 감소시킬 수 있다.




항목 45: "호환되는 모든 타입"을 받아들이는 데는 멤버 함수 템플릿이 직방!

스마트 포인터.
힙 기반 자원의 삭제를 제때 삭제해줌.
STL 컨테이너의 반복자.
포인터에 ++ 연산 적용해서 연결 리스트의 한 노드에서 다른 노드로 이동하게 함.

포인터에도 스마트 포인터로 대신할 수 없는 특징이 있다.
암시적 변환(implicit conversion)을 지원한다.
	파생 클래스 포인터는 암시적으로 기본 클래스 포인터로 변환되고,
	비상수 객체에 대한 포인터는 상수 객체에 대한 포인터로의 암시적 변환이 가능.;

class Top {/*...*/ };
class Middle: public Top {/*...*/ };
class Bottom: public Middle {/*...*/ };
Top *pt1 = new Middle;		//Middle* ==> Top*의 변환
Top *pt2 = new Bottom;		//Bottom* ==> Top*의 변환
const Top *pct2 = pt1;		//Top* ==> const Top*의 변환

=> 이런 식의 타입 변환을 사용자 정의 스마트 포인터를 써서 흉내 내려면 까다로움;

template<typename T>
class SmartPtr {
public:
	explicit SmartPtr(T *realPtr);		//스마트 포인터는 대개 기본제공 포인터로 초기화됨.
};
SmartPtr<Top> pt1 = SmartPtr<Middle>(new Middle);	//SmartPtr<Middle> ==> SmartPtr<Top>의 변환
SmartPtr<Top> pt2 = SmartPtr<Bottom>(new Bottom);
SmartPtr<const Top> pct2 = pt1;


템플릿을 인스턴스화 하면 무제한 개수의 함수를 만들어 낼 수 있따.
생성자를 만들어내는 템플릿을 쓰자!
'멤버 함수 템플릿(member function templat, 멤버 템플릿)': 어떤 클래스의 멤버 함수를 찍어내는 템플릿.;

template<typename T>
class SmartPtr {
public:
	template<typename U>		//"일반화된 복사 생성자"를 만들기 위해 마련한 멤버 템플릿.
	SmartPtr(const SmartPtr<U>& other);
};
=> SmartPtr<T> 객체가 SmartPtr<U>로부터 생성될 수 있다는 코드.
그 이유는 SmartPtr<U>의 참조자를 매개변수로 받아들이는 생성자가 SmartPtr<T> 안에 들어있다.

같은 템플릿을 써서 인스턴스화되지만 타입이 다른 타입의 객체로부터 원하는 객체를 만들어 주는 생성자를 가리켜 
'일반화 복사 생성자(generalized copy constructor)'라고 부른다.

explicit로 선언하지 않음.
포인터는 포인터 타입 사이 타입 변환이 암시적으로 이루어지며 캐스팅이 필요하지 않기 때문에,
스마트 포인터도 이런 형태로 동작하도록 흉내낸 것.


다만, 원하지 않는 SmartPtr<Top>으로부터 SmartPtr<Bottom>을 만들거나, SmartPtr<double>로부터 SmartPtr<int>를 만들 수 있음.
public 상속의 의미(항목 32)에 역행함!
포인터는 int*에서 double*로 진행되는 암시적인 변환이 불가능.

get 멤버 함수를 통해 스마트 포인터 객체에 자체적으로 담긴 기본제공 포인터의 사본을 반환(항목 15);
template<typename T>
class SmartPtr {
public:
	template<typename U>
	SmartPtr(const SmartPtr<U>& other)		//이 SmartPtr에 담긴 포인터를
		: heldPtr(other.get()) {/*...*/}	//다른 SmartPtr에 담긴 포인터로 초기화.
	T* get() const { return heldPtr; }
private:
	T *heldPtr;		//SmartPtr에 담긴 기본제공 포인터
};

=> 효과;
SmartPtr<T>의 '일반화 복사 생성자'는 호환되는(compatible) 타입의 매개변수를 넘겨받을 때만 컴파일 됨.

멤버 함수 템플릿의 활용은 생성자에만 그치지 않는다.
대입 연산.;
template<class T> class shared_ptr {
public:
	template<class Y>
	explicit shared_ptr(Y * p);		//호환되는 모든 기본제공 포인터.
	template<class Y>
	explicit shared_ptr(shared_ptr<Y> const& r);
	template<class Y>
	explicit shared_ptr(weak_ptr<Y> const& r);
	template<class Y>
	explicit shared_ptr(auto_ptr<Y>& r);	//스마트 포인터 객체로부터 생성자 호출
	template<class Y>
	explicit operator=(shared_ptr<Y> const& r);
	template<class Y>
	explicit operator=(auto_ptr<Y>& r);		//weak_ptr을 제외한 대입 연산에 사용 (weak_ptr은 항목 54)
};

explicit 의 의미: shared_ptr로 만든 어떤 타입으로부터 진행되는 암시적 변환은 허용되지만,
	기본제공 포인터 or 다른 스마트 포인터 타입으로부터 변환되는 것은 막겠다.
		명시적 변환(캐스팅 등)은 ok.

auto_ptr이 const 선언 안 한 이유: 복사 연산으로 인해 객체가 수정될 때 오직 복사된 쪽 하나만 유효하게 남음(항목 13)

일반화 복사 생성자는 보통의 복사 생성자가 아니다.
복사 생성을 전부 컨트롤 하고 싶으면, 복사 생성자까지 직접 선언 필요.;

template<class T> class shared_ptr {
public:
	shared_ptr(shared_ptr const& r);	//복사 생성자
	template<class Y> shared_ptr(shared_ptr<Y> const& r);	//일반화 복사 생성자

	shared_ptr& operator=(shared_ptr const& r);	//복사 대입 연산자
	template<class Y> shared_ptr& operator=(shared_ptr<Y> const& r);		//일반화 복사 대입 연산자
};

잊지 말자!
1. 호환되는 모든 타입을 받아들이는 멤버 함수를 만들려면 멤버 함수 템플릿을 사용합시다.
2. 일반화된 복사 생성 연산과 일반화된 대입 연산을 위해 멤버 템플릿을 선언했다 하더라도,
	보통의 복사 생성자와 복사 대입 연산자는 직접 선언해야 한다.




항목 46: 타입 변환이 바람직할 경우에는 비멤버 함수를 클래스 템플릿 안에 정의해 두자!

모든 매개변수에 대해 암시적 타입 변환이 되도록 하기 위해서는 비멤버 함수밖에 방법이 없다.
(항목 24) Rational 클래스의 operator*;

template<typename T>
class Rational {
public:
	Rational(const T& numerator = 0,	//매개변수가 참조자로 전달되는 이유는 항목 20 참고
		const T& denominator = 1);
	const T numerator() const;		//반환 값 전달이 여전히 값에 의한 전달인 이유는 항목 28. const인 이유는 항목 3
	const T denominator() const;
};

template<typename T>
const Rational<T> operator*(const Rational<T>& lhs,	const Rational<T>& rhs) { /*...*/ }

항목 24에서 그랬듯, 혼합형(mixed - mode) 수치 연산은 여전히 필요.;
Rational<int> oneHalf(1, 2);		//Rational이 이제 템플릿이란 것만 빼면 항목 24의 것과 똑같음
Rational<int> result = oneHalf * 2;	//그런데 에러!!

항목 24에서는 우리가 호출하려고 하는 함수가 무엇인지 컴파일러가 알고 있지만(Rational 객체 두 개를 받는 operator* 함수)
operator*라는 이름의 템플릿으로부터 만들 함수를 결정하기 위해 온갖 계산을 동원할 뿐.
컴파일러가 아는 건 Rational<T> 타입의 매개변수 2가지를 받아들이는 operator* 함수를 어떻게 인스턴스로 만들어야 하는데...
'T가 무엇인고?'

컴파일러는 우선 operator* 호출 시 넘겨진 인자의 모든 타입을 살핀다.
Rational<int>(oneHalf의 타입) 및 int(2의 타입)
매개변수1 T는 int 일 수밖에...
매개변수2 T는 ?
템플릿 인자 추론(template argument deduction) 과정에서는 암시적 타입 변환이 고려되지 않음.

방법 프렌드 함수.;
template<typename T>
class Rational {
public:
	friend const Rational operator*(const Rational& lhs, const Rational& rhs);
};
template<typename T>
const Rational<T> operator*(const Rational<T>& lhs, const Rational<T>& rhs) { /*...*/ }		//operator* 함수를 재정의.

지금은 함수 템플릿이 아니라 함수가 선언된 것.
컴파일러는 이 호출문에 대해 암시적 변환 함수(Rational의 비명시 호출 생성자 등)을 적용할 수 있게 됨.
단, 링크가 안 된다...!

클래스 템플릿 내부에 템플릿의 이름(<> 뗀 것)을 템플릿 및 매개변수의 줄임말로 쓸 수 있다.
Rational<T> 안에서는 Rational이라고만 써도 Rational<T>로 먹힌다.
위 코드는 다음과 같은 의미;
template<typename T>
class Rational {
public:
	const Rational<T> operator*(const Rational& lhs, const Rational& rhs);
};

Rational 선언만 되어 있지, 정의까진 안 되어 있음.
operator* 함수의 본문을 선언부와 붙이기.;

class Rational {
public:
	//...
	friend const Rational operator*(const Rational& lhs, const Rational& rhs) {
		return Rational(lhs.numerator() * rhs.nemerator(), lhs.denominator() * rhs.denominator());
			//항목 24의 그 코드 동일한 구현
	}
};
=> 컴파일, 링크 잘됨.

모든 인자에 대해 타입 변환이 가능하도록 하기 위해 비멤버 함수가 필요(항목 24)
호출 시의 상황에 맞는 함수를 자동으로 인스턴스화하기 위해 그 비멤버 함수를 클래스 안에 선언해야.
공교롭게도, 클래스 안에 비멤버 함수를 선언하는 유일한 방법이 '프렌드'였을 뿐.
"프렌드 함수는 도우미만 호출하게 만들기"

헤더 파일 예시;
template<typename T>
const Rational<T>  doMultiply(const Rational<T>& lhs, const Rational<T>& rhs);	//도우미 함수 템플릿을 선언.

template<typename T>
class Rational {
public:
	friend const Rational<T> operator*(const Rational<T>& lhs, const Rational<T>& rhs) {
		return doMultiply(lhs, rhs);		//프렌드 함수가 도우미 함수를 호출하게 만듦.
	}
};

대다수 컴파일러가 템플릿 정의를 헤더 파일에 전부 넣을 것을 사실상 강제.
doMultiply도 헤더 파일 안에 정의해 넣어야 할 것. 이런 템플릿은 인라인일 필요 없음(항목 30)

적용 예시;
template<typename T>
const Rational<T> doMultiply(const Rational<T>& lhs, const Rational<T>& rhs) {
	return Rational<T>(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}

잊지 말자!
1. 모든 매개변수에 대해 암시적 타입 변환을 지원하는 템플릿과 관계가 있는 함수를 제공하는 클래스 템플릿을 만들려고 한다면,
	이런 함수는 클래스 템플릿 안에 프렌드 함수로서 정의한다.




항목 47: 타입에 대한 정보가 필요하다면 특성정보 클래스를 사용하자!

STL은 컨테이너, 반복자, 알고리즘의 템플릿으로 구성.
이 외에 유틸리티 템플릿도 몇 개.
이 중 하나 advance 라는 템플릿: 지정된 반복자를 지정된 거리만큼 이동.;

template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d);		//iter를 d 단위만큼 전진시킨다. d < 0이면 iter를 후진시킨다.

임의 접근 반복자 밖에 += 할 수 없다.
다른 반복자는 ++나 --를 d번 하는 수밖에...


STL 반복자
1. 입력 반복자(input iterator)
	: 전진만 가능 / 한 번에 한 칸씩 이동 / 자신이 가리키는 위치에서 읽기만 가능 / 읽을 수 있는 횟수 1번
	istream_iterator
2. 출력 반복자(output iterator)
	: 전진만 가능 / 한 번에 한 칸씩 이동 / 자신이 가리키는 위치에서 쓰기만 가능 / 쓸 수 있는 횟수 1번
	ostream_iterator

=> 단일 패스 알고리즘에만 제대로 사용 가능

3. 순방향 반복자(forward itator)
	: 입력, 출력 반복자 하는 일 모두 + 자신이 가리키고 있는 위치에서 읽기와 쓰기를 동시에, 여러 번 가능
	다중 패스(multi-pass) 알고리즘에 문제없이 쓸 수 있음.
	해시 컨테이너(항목 54) 가리키는 반복자. 단일 연결 리스트를 사용하는 라이브러리에서 컨테이너의 반복자.

4. 양방향 반복자(bidirectional iterator)
	: 순방향 반복자 + 뒤로 갈 수 있는 기능
	STL의 list에 쓰는 반복자
	set, multiset, map, multimap 등의 컨테이너

5. 임의 접근 반복자(random access iterator)
	: 양방향 반복자 + "반복자 산술 연산(iterator arithmetic)" 수행 기능
	반복자를 임의의 거리만큼 앞뒤로 이동시키는 일을 상수 시간 안에 할 수 있다.
	기본 제공 포인터를 본떠서 임의 접근 반복자를 만듦.
	C++ 표준 라이브러리의 vector, deque, string에 사용.

각 "태그 구조체";
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag: public input_iterator_tag {};
struct bidirectional_iterator_tag: public forward_iterator_tag {};
struct random_access_iterator_tag: public bidirectional_iterator_tag {};


advance
최소 공통 분모(lowest-common-denominator) 전략
반복자를 주어진 횟수만큼 (한 칸씩) 반복적으로 증가, 감소하는 루프;

template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d) {
	if (/*iter가 임의 접근 반복자이다*/) {
		iter += d;	//임의 접근 반복자에 대해서는 반복자 산술 연산을 씁니다.
	}
	else {
		if (d >= 0) { while (d--) ++iter; }		//다른 종류의 반복자에 대해서는 ++혹은 --연산의 반복 호출을 사용합니다.
		else { while (d++) --iter; }
	}
}

iter 부분이 임의 접근 반복자인지 우째 판단해쓰까?
'특성정보(traits)': 컴파일 도중에 어떤 주어진 타입의 정보를 얻을 수 있게 하는 객체.
구현 기법이며, 관례.
특성정보 기법을 포인터 등의 기본제공 타입에 적용할 수 있어야 한다.

어떤 타입 내에 중첩된 정보 등으로는 구현이 안 된다.
어떤 타입의 특성정보는 그 타입의 외부에 존재한다.
템플릿 및 템플릿의 1개 이상의 특수화 버전에 넣기.

반복자의 경우, 표준 라이브러리의 특성정보용 템플릿이 iterator_traits 라는 이름으로 준비됨.;

template<typename IterT>
struct iterator_traits;		//반복자 타입에 대한 정보를 나타내는 템플릿
=> '특성정보 클래스'

임의 접근 반복자 deque 클래스(템플릿) 예시;
template</*템플릿 매개변수는 편의상 생략*/>
class deque {
public:
	class iterator {
	public:
		typedef random_access_iterator_tag iterator_category;
	};
};

양방향 반복자 list;
template</*...*/>
class list {
public:
	class iterator {
	public:
		typedef bidirectional_iterator_tag iterator_category;
	};
};

iterator_traits;
//IterT 타입에 대한 iterator_category는 IterT가 온몸으로 말하고 있는 바 그대로.
//"typedef typename"이 사용된 부분에 대해 설명은 항목 42.
template<typename IterT>
struct iterator_traits {
	typedef typename IterT::iterator_category iterator_category;
};
=> 위 코드는 사용자 정의 타입은 잘 돌아가나, 반복자의 실제 타입이 포인터인 경우에는 전혀 안 돌아감.
typedef 타입이 중첩된 게 말이 안되서.
iterator_traits 구현의 두 번째 부분은 반복자가 포인터인 경우의 처리.

iterator_traits는 포인터 타입에 대한 '부분 템플릿 특수화(partial template specialization)' 버전을 제공함.
사실 포인터의 동작 원리가 임의 접근 반복자와 똑같으므로, 
iterator_traits가 이런 식으로 지원하는 반복자 범주가 임의 접근 반복자.;

template<typename IterT>		//기본제공 포인터 타입에 대한 부분 템플릿 특수화
struct iterator_traits<IterT*> {
	typedef random_access_iterator_tag iterator_category;
};

특성정보 설계 및 구현 방법.
1. 다른 사람이 사용하도록 열어 주고 싶은 타입 관련 정보 확인 (ex. 반복자라면 반복자 범주 등)
2. 그 정보를 식별할 이름 선택(ex. iterator_category).
3. 지원하고자 하는 타입 관련 정보를 담은 템플릿 및 그 템플릿의 특수화 버전(ex. iterator_traits) 제공.

std::iterator_traits가 주어졌으므로 advance 의사코드 다듬기.;

template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d) {
	if(typeid(typename std::iterator_traits<IterT>::iterator_category)
		== typeid(std::random_access_iterator_tag))
	//...
}
=> typeid 사용. 문제 있음. ㅜㅡㅜ
컴파일 문제는 항목 48.

IterT의 타입은 컴파일 도중에 파악되기 때문에, 'iterator_traits<IterT>::iterator_category'를 파악할 수 있을 때도 컴파일 도중임.
하지만 if문은 런타임에 평가됨.
실행 코드 크기 크고 시간 낭비.

컴파일 도중에 수행하는 조건처리 구문요소. '오버로딩'
오버로딩: 매개변수 리스트가 다르지만 f라는 이름은 같은 오버로드 버전을 여러 개 만든다.
컴파일러 "당신이 넘긴 인자 타입에 가장 잘 맞는 오버로드 버전이 이 거면, 이 f를 부를 거야."
"두 번째가 가장 잘 맞으면 두 번째, 세 번째가 가장 잘 맞으면 세 번째"

advance의 "동작 원리 알맹이"는 똑같게 하고, 받아들이는 iterator_category 객체의 타입을 다르게 해서 오버로드 함수를 만든다.
이 오버로드 함수의 이름을 doAdvance라고 하자.;

template<typename IterT, typename DistT>	//임의 접근 반복자에 대해서는 이 구현.
void doAdvance(IterT& iter, DistT d, std::random_access_iterator_tag) {	
	iter += d;
}

template<typename IterT, typename DistT>	//양방향 반복자~
void doAdvance(IterT& iter, DistT d, std::bidirectional_iterator_tag) {
	if (d >= 0) { while (d--) ++iter; }
	else { while (d++) --iter; }
}

template<typename IterT, typename DistT>	//입력 반복자~
void doAdvance(IterT& iter, DistT d, std::input_iterator_tag) {
	if (d < 0) {
		throw std::out_of_range("Negative distance");
	}
	while (d--) ++iter;
}

forward_iterator_tag 는 input_iterator_tag로부터 상속을 받는 것.
input_iterator_tag를 매개변수로 받는 doAdvance는 순방향 반복자도 받을 수 있다.

advance는 임의 접근 반복자 및 양방향 반복자에 대해 양수 및 음수 거리를 받을 수 있게 되어 있지만,
순방향, 입력 반복자를 음수 거리만큼 이동하려고 하면 미정의 동작 발생.

오버로딩 된 doAdvance 호출하는 advance();
template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d) {		//iter의 반복자 범주에 적합한 doAdvance의 오버로드 버전을 호출.
	doAdvance(iter, d, typename std::iterator_traits<IterT>::iterator_category());
}

특성정보 클래스 How Use
1. '작업자(worker)' 역할을 맡을 함수or함수 템플릿(ex. doAdvance)을 특성정보 매개변수를 다르게 하여 오버로딩.
	전달되는 해당 특성정보에 맞추어 각 오버로드 버전을 구현.
2. 작업자를 호출하는 '주작업자(master' 역할을 맡을 함수or함수 템플릿(ex. advance)를 만듦.
	이때 특성정보 클래스에서 제공되는 정보를 넘겨서 작업자를 호출하도록 구현.

iterator_traits는 
iterator_category 말고도 제공하는 반복자 관련 정보가 4가지
1. value_type은 항목 42
2. char_traits: 문자 타입 정보
3. numeric_limits: 숫자 타입에 대한 정보(표현 가능한 최소값, 최대값 등)

TR1(항목 54)이 도입되면서 타입 관련 정보를 제공하는 특성정보 클래스가 상당수 추가됨.
is_fundamental<T> 
	T가 기본제공 타입인지 알려줌)
is_array<T>
	T가 배열 타입인지 알려줌
is_base_of<T1, T2>
	T1이 T2와 같거나 T2의 기본 클래스인지 알려줌.
등등.. 추가된 것만 합 50개.

잊지 말자!
1. 특성정보 클래스는 컴파일 도중 사용할 수 있는 타입 관련 정보를 만들어낸다.
	또한 템플릿 및 템플릿 특수 버전을 사용하여 구현한다.
2. 함수 오버로딩 기법과 결합하여 특성정보 클래스를 사용하면, 
	컴파일 타임에 결정되는 타입별 if...else 점검문을 구사할 수 있다.;




항목 48: 템플릿 메타프로그래밍, 하지 않겠는가?

'템플릿 메타프로그래밍(template metaprogramming: TMP)'
	: 컴파일 도중에 실행되는 템플릿 기반의 프로그램을 작성하는 일.

TMP 프로그램이 실행 마친 후 => 그 결과로 나온 출력물(템플릿으로부터 인스턴스화된 C++ 소스 코드)이 다시 보통의 컴파일 과정.

강점
1. 다른 방법보다 까다롭거나 불가능한 일 할 수있음
2. 기존 작업을 런타임 영역에서 컴파일 타임 영역으로 전환하며,
	실행 도중 몇몇 에러를 컴파일 도중에 찾을 수 있음.
	효율적일 여지가 많음(실행 코드 작음, 실행 시간 작음, 메모리 적게 먹음)

STL advance(항목 47);
template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d) {
	if (/*iter가 임의 접근 반복자이다*/) {
		iter += d;
	}
	else {
		if (d >= 0) { while (d--) ++iter; }
		else { while (d++) --iter; }
	}
}

타입 정보를 꺼내는 작업을 런타임에 해보자;
template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d) {
	if (typeid(typename std::iterator_traits<IterT>::iterator_category) ==
		typeid(std::random_access_iterator_tag)) {
		iter += d;
	}
	else {
		if (d >= 0) { while (d--) ++iter; }
		else { while (d++) --iter; }
	}
}

typeid 연산자를 쓰는 방법은 특성정보(traits)를 쓰는 방법보다 효율 떨어짐.
1. 타입 점검 동작이 컴파일 도중이 아니라 런타임에 일어나기 때문.
2. 런타임 타입 점검을 수행하는 코드는 어쩔 수 없이 실행 파일에 들어가야 함.

항목 47에서 말한 typeid 방법의 컴파일 문제;
std::list<int>::iterator iter;
advance(iter, 10);		//iter를 10개 원소만큼 앞으로 옮길까 했으나, 위 구현된 advance로는 컴파일 안됨.

void advance(std::list<int>::iterator& iter, int d) {
	if (typeid(std::iterator_traits<std::list<int>::iterator>::iterator_category) ==		//typeid 점검 실패
		typeid(std::random_access_iterator_tag)) {
		iter += d;	//에러!
	}
	else {
		if (d >= 0) { while (d--) ++iter; }
		else { while (d++) --iter; }
	}
}

list<int>::iterator는 양방향 반복자여서 += 안됨.

TMP 튜링 완전성.
어떤 것이든 계산할 수 있음. 변수 선언, 루프, 함수 작성, 호출
TMP용 라이브러리(부스트의 MPL 등. 항목 55)

TMP에 반복(iteration) 의미의 진정한 루프는 없기 때문에, 재귀(recursion)를 사용해서 루프의 효과를 냄.

단, TMP의 루프는 재귀 함수 호출을 만들지 않고 '재귀식 템플릿 인스턴스화(recursive template instantiation)'을 한다.

template<unsigned n>	
struct Factorial {		//일반적인 경우: Factorial<n>의 값은 Factorial<n-1>의 값에 n을 곱해서 구한다.
	enum { value = n * Factorial<n-1>::value };
};
template<>		//특수한 경우: Factorial<0>의 값은 1이다.
struct Factorial<0> {
	enum { value = 1 };
};

Factorial<n>::value를 참조함으로써 n의 계승을 바로 얻을 수 있음.
재귀를 끝내는 특수 조건은 Factorial<0>.

Factorial 템플릿은 구조체 타입이 인스턴스화되도록 만들어져 있다.
구조체 안에 value라는 이름의 TMP 변수가 선언되어 있다.
나열자 둔갑술(enum hack)(항목 2)

int main() {
	std::cout << Factorial<5>::value;		//120을 런타임 계산 없이 출력
	std::cout << Factorial<10>::value;		//3628800을 런타임 계산 없이 출력
}


TMP 사용처
1. 치수 단위(dimensional unit)의 정확성 확인
과학 기술 분야... 치수 단위(질량, 거리, 시간 등)가 똑바로 조합되어야 할 때
컴파일 동안에 맞춰볼 수 있다.선행 에러 탐지(early error detection)
분수식 지수 표현이 지원.컴파일 도중에 분수의 약분이 되어야 함.time ^ 1 / 2 는 time ^ 4 / 8 과 똑같이 받아들여짐

2. 행렬 연산의 최적화
operator* 등의 연산자 함수는 연산 결과를 새로운 객체에 담아 반환해야 한다.(항목 21);

typedef SquareMatrix<double, 10000> BigMatrix;
BigMatrix m1, m2, m3, m4, m5;		//행렬들을 생성하고 각 행렬에 값을 준다.
BigMatrix result = m1 * m2 * m3 * m4 * m5;		//행렬들의 곱을 계산함.

네 개의 임시 행렬이 생겨야... operator*를 한 번씩 호출 후 반환... 네 개의 루프...
이런 비싼 연산에 TMP 사용.
TMP를 응용한 고급 프로그래밍 기술인 '표현식 템플릿(expression template)'을 사용하면 
	덩치 큰 임시 객체를 없애는 것은 물론, 루프까지 합쳐 버릴 수 있다.

3. 맞춤식 디자인 패턴 구현의 생성
전략(Strategy) 패턴, 감시자(Observer) 패턴, 방문자(Visitor) 패턴 등의 디자인 패턴
TMP를 사용한 프로그래밍 기술인 정책 기반 설계(policy-based design) 사용하면, 
따로따로 마련된 설계상의 선택(정책)을 나타내는 템플릿을 만들어낼 수 있게 됨.

ex. 스마트 포인터 동작 정책을 하나씩 구현한 각각의 템플릿을 만들고,
이들을 사용자가 마음대로 조합하여 수백 가지의 스마트 포인터 타입을 생성할 수 있게(컴파일 도중에) 하는 것.
'생성식 프로그래밍(generative programming)'의 기초

잊지 말자!
1. 템플릿 메타프로그래밍은 기존 작업을 런타임에서 컴파일 타임으로 전환하는 효과.
	TMP를 쓰면 선행 에러 탐지와 높은 런타임 효율.

2. TMP는 정책 선택의 조합에 기반하여 사용자 정의 코드를 생성하는 데 쓸 수 있으며,
	또한 특정 타입에 대해 부적절한 코드가 만들어지는 것을 막는 데도 쓸 수 있음.




new 와 delete 를 내 맘대로

가비지 컬렉션 지원 프로그래밍 환경에서,
C++은 여전히 수동을 고집.
메모리 할당 및 해제 루틴(operator new 및 operator delete)
new 처리자(new-handler)가 도움

다중스레드 환경에서 메모리 관리는 여러 문젯거리.
힙은 수정이 가능한 전역 자원으로 분류.
다중스레드 시스템에서는 스레드들이 이런 전역 자원에 미친 듯이 접근.

operator new 및 delete 는 객체 한 개를 할당할 때만 적용
배열을 담을 메모리 할당 operator new[] 해제 operator delete[]

STL 컨테이너에 대한 힙 메모리 관리




항목 49: new 처리자의 동작 원리를 제대로 이해하자

사용자가 보낸 메모리 할당 요청을 operator new 함수가 맞추어 주지 못할 경우 == 할당할 메모리 없을 때
	operator new 함수는 예외를 던지게 되어있음.
에러 처리 함수 new 처리자(new-handler, 할당에러 처리자) (자세한 건 항목 51)

메모리 고갈 상황을 처리할 함수를 사용자 쪽에서 지정.
표준 라이브러리 set_new_handler 함수;

namespace std {
	typedef void(*new_handler)();
	new_handler set_new_handler(new_handler p) throw();
}
=> new_handler : 받는 것도 없고 반환하는 것도 없는 함수의 포인터에 대해 typedef 를 걸어 놓은 타입동의어.
throw() 예외 지정(exception specification): 이 함수는 어떤 예외도 던지지 않을 것 (항목 29)

//충분한 메모리를 operator new 가 할당하지 못했을 때 호출할 함수
void outOfMem() {
	std::cerr << "Unable to satisfy request for memory\n";
	std::abort();
}
int main() {
	std::set_new_handler(outOfMem);
	int *pBigDataArray = new int[100000000L];
}
=> operator new 가 1억 개의 정수 할당에 실패하면 outOfMem 함수 호출.
호출 시 메시지 출력 후 프로그램 강제 종료.

new 처리자 함수 잘 작동 위해 할 수 있는 동작들
1. 사용할 수 있는 메모리 더 많이 확보.
	operator new 가 시도하는 이후의 메모리 확보가 성공할 수 있도록 하자.
	프로그램이 시작할 때 메모리 블록을 크게 하나 할당해 놓았다가 new 처리자가 가장 처음 호출될 때 그 메모리를 쓸 수 있도록 허용.

2. 다른 new 처리자를 설치.
	현재의 new 처리자는 제자리에서 다른 new 처리자를 설치할 수 있음(현재의 new 처리자 안에서 set_new_handler 호출)
	operator new 함수가 다시 new 처리자를 호출할 때가 되면, 새로 설치된 new 처리자가 호출.

3. new 처리자의 설치를 제거.
	set_new_handler 에 널 포인터를 넘기기. 
	new 처리자가 설치된 것이 없으면, operator new 는 메모리 할당이 실패했을 때 예외를 던짐.

4. 복귀하지 않음
	대개 abort 혹은 exit 호출


할당된 객체의 클래스 타입에 따라서 메모리 할당 실패에 대한 처리를 다르게 가져가고 싶을 때.;
class X {
public:
	static void outOfMemory();
};
class Y {
public:
	static void outOfMemory();
};
X* p1 = new X;		//메모리 할당 실패했을 경우 X::outOfMemory 호출.
Y* p2 = new Y;

set_new_handler 함수의 역할은 사용자로부터 그 클래스에 쓰기 위한 new 처리자를 받아내는 것.
operator new 함수는, 그 클래스 객체를 담을 메모리가 할당되려고 할 때(그리고 실패했을 때)
	전역 new 처리자 대신 클래스 버전의 new 처리자가 호출되도록 만드는 역할

예시: Widget 클래스에 대한 메모리 할당 실패를 직접 처리하고 싶을 경우.;
class Widget {
public:
	static std::new_handler set_new_handler(std::new_handler p) throw();
	static void * operator new(std::size_t size) throw(std::bad_alloc);
private:
	static std::new_handler currentHandler;
};
new 처리자를 가리키는 new_handler 타입의 정적 데이터 멤버.
정적 클래스 멤버의 정의는 정수 타입 상수 멤버가 아니면 클래스의 바깥쪽. (항목 2);

std::new_handler Widget::currentHandler;	//널로 초기화. 클래스 구현 파일에 두어야 함.

set_new_handler 함수는 넘어온 포인터를 아무 점검 없이 저장, 전에 저장했던 포인터를 점검 없이 반환.;

std::new_handler Widget::set_new_handler(std::new_handler p) throw() {
	std::new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}

Widget의 operator new;

1. 표준 set_new_handler 함수에 Widget의 new 처리자를 넘겨서 호출.
	즉, 전역 new 처리자로서 Widget의 new 처리자를 설치.

2. 전역 operator new 호출하여 실제 메모리 할당을 수행.
	전역 operator new 할당이 실패하면, 이 함수는 Widget의 new 처리자를 호출.
	앞 단계에서 전역 new 처리자로 설치된 함수가 바로 이 함수.
	마지막까지 전역 operator new의 메모리 할당 시도가 실패하면, '좌절' 의미로 bad_alloc 예외 던짐.
	Widgt의 operator new 는 전역 new 처리자를 원래의 것으로 되돌려 놓고, 이 예외를 전파.
	Widget은 전역 new 처리자를 자원으로 간주하고 처리.
	(항목 13) 자원 관리 객체 사용해서 전역 new 처리자를 관리하여 메모리 누수 막기

3. 전역 operator new 가 Widget 객체 하나만큼의 메모리를 할당할 수 있으면, Widget의 operator new는 할당된 메모리 반환.
	전역 new 처리자를 관리하는 객체의 소멸자 호출.
	Widget의 operator new 가 호출되기 전에 쓰이던 전역 new 처리자가 자동으로 복원.

(어려웡..)

class NewHandlerHolder {
public:
	explicit NewHandlerHolder(std::new_handler nh)	//현재의 new 처리자를 획득
		: handler(nh) {}
	~NewHandlerHolder() {	//이것을 해제
		std::set_new_handler(handler);
	}
private:
	std::new_handler handler;	//이것을 기억해두기
	NewHandlerHolder(const NewHandlerHolder&);	//복사를 막기 위한 부분(항목 14)
	NewHandlerHolder& operator=(const NewHandlerHolder&);
};

void * Widget::operator new(std::size_t size) throw(std::bad_alloc) {
	NewHandlerHolder h(std::set_new_handler(currentHandler));	//Widget의 new 처리자를 설치
	return ::operator new(size);	//메모리를 할당하거나, 할당이 실패하면 예외를 던진다.
									//이전의 전역 new 처리자가 자동으로 복원됨.
}

void outOfMem();	//Widget 객체에 대한 메모리 할당이 실패했을 때 호출될 함수의 선언.
Widget::set_new_handler(outOfMem);	//Widget의 new 처리자 함수로서 outOfMem을 설치.
Widget *pw1 = new Widget;	//메모리 할당이 실패하면 outOfMem이 호출됨.
std::string *ps = new std::string;	//메모리 할당이 실패하면 전역 new 처리자 함수가 있으면 호출됨.
Widget::set_new_handler(0);	//Widget 클래스만을 위한 new 처리자 함수가 아무것도 없도록 함(즉, null로 설정).
Widget *pw2 = new Widget;		//메모리 할당이 실패하면 이제는 예외를 바로 던짐(Widget 클래스를 위한 new 처리자 함수가 없음).


다른 클래스에도 재사용하고 픔
'믹스인(mixin) 양식'의 기본 클래스.
	다른 파생 클래스들이 한 가지의 특정 기능만을 물려받아 갈 수 있도록 설계된 기본 클래스 만들기.
	'특정 기능'은 클래스별 new 처리자를 설정하는 기능. 그 담 기본 클래스를 템플릿으로 탈바꿈.
	파생 클래스마다 클래스 데이터(원래의 new 처리자를 기억해 두는 정적 멤버 데이터)의 사본이 따로따로 존재하게 됨.

위와 같은 클래스 템플릿 이점
1. 기본 클래스 부분은 파생 클래스들이 가져야 하는 set_new_handler 함수와 operator new 함수를 물려줌.
	템플릿 부분은 각 파생 클래스가(인스턴스화된 클래스가 되면서) currentHandler 데이터 멤버를 따로따로 가질 수 있게 함.;

template<typename T>
class NewHandlerSupport {	//클래스별 set_new_handler를 지원하는 "믹스인 양식"의 기본 클래스.
public:
	static std::new_handler set_new_handler(std::new_handler p) throw();
	static void * operator new(std::size_t size) throw(std::bad_alloc);
	//...	//operaotr new의 다른 버전들 (항목 52)
private:
	static std::new_handler currentHandler;
};

template<typename T>
std::new_handler
NewHandlerSupport<T>::set_new_handler(std::new_handler p) throw() {
	std::new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}
template<typename T>
void * NewHandlerSupport<T>::operator new(std::size_t size) throw(std::bad_alloc) {
	NewHandlerHolder h(std::set_new_handler(currentHandler));
	return ::operator new(size);
}
//클래스별로 만들어지는 currentHandler 멤버를 널로 초기화함.
template<typename T>
std::new_handler NewHandlerSupport<T>::currentHandler = 0;

class Widget :public NewHandlerSupport<Widget> {
	//...	//이전과 같지만, 이제는 set_new_handler 혹은 operator new에 대한 선언문이 빠져 있습니다.
};

(어려웡..) (모르겠엉..)

Widget ...<Widget> ..?
'신기하게 반복되는 템플릿 패턴(curiously recurring template pattern: CRTP)'
'넌 나만의 템플릿이야..'


예외불가(nothrow) 형태;
class Widget {/*...*/};
Widget *pw1 = new Widget;	//할당이 실패하면 bad_alloc 예외 던짐
if (pw1 == 0) {/*...*/ };	//이 점검 코드는 꼭 실패한다
Widget *pw2 = new(std::nothrow) Widget;	//Widget을 할당하다 실패하면 0(널)을 반환함.
if(pw2 == 0) {/*...*/ };	//이 코드는 성공할 수 있ㅇ.ㅁ


잊지 말자!
1. set_new_handler 함수를 쓰면 메모리 할당 요청이 만족되지 못했을 때 호출되는 함수를 지정할 수 있다.
2. 예외불가(nothrow) new 는 영향력이 제한되어 있다.
	메모리 할당 자체에만 적용되기 때문.
	이후에 호출되는 생성자에서는 얼마든지 에외를 던질 수 있다.




항목 50: new 및 delete 를 언제 바꿔야 좋은 소리를 들을지를 파악해 두자!

컴파일러의 operator new, operator delete 를 바꾸고 싶은 이유 3가지
1. 잘못된 힙 사용을 탐지하기 위해.
	할당된 메모리 주소의 목록을 operator new 가 유지해 두고, 
	operator delete 가 그 목록으로부터 주소를 하나씩 제거해 주게 하면, 실수 덜.

	문제: 데이터 오버런(overrun, 할당된 메모리 블록의 끝을 넘어 기록하는 것)
		언더런(underrun, 할당된 메모리 블록의 시작을 넘어 앞에 기록하는 것)

	오버런/언더런 탐지용 바이트 패턴[일명 "경계표지(signature)"]를 적어두도록 만들 수 있음.

2. 효율을 향상시키기 위해
	기존 함수는 일반적인 쓰임새를 위한 것
		: 실행시간 긴 프로그램, 짧은 프로그램, 힙 단편화(fragmentation)에 대한 대처방안 등
	기본제공 버전보다 맞춰 썼을 때 우수한 성능을 낼 확률이 높음.

3. 동적 할당 메모리의 실제 사용에 관한 통계 정보를 수집하기 위해
	: 패턴 차이, 한 번에 쓰이는 동적 할당 메모리의 최대량[다른 말로 "최고수 위선(high water mark)"] 등등 파악

버퍼 오버런, 언더런 탐지하기 쉬운 전역 opertor new 만들기
예시;
static const int signature = 0xDEADBEEF;
typedef unsigned char Byte;
//이 코드는 고쳐야 할 부분 몇 개 있음.
void* operator new(std::size_t size) throw(std::bad_alloc) {
	using namespace std;
	size_t realSize = size + 2 * sizeof(int);	//경계표지 2개를 앞뒤에 붙일 수 있을 만큼만 메모리 크기를 늘린다.

	void *pMem = malloc(realSize);	//malloc을 호출하여 실제 메모리를 얻어냄.
	if (!pMem) throw bad_alloc();

	//메모리 블록의 시작 및 끝부분에 경계표지를 기록한다.
	*(static_cast<int*>(pMem)) = signature;
	*(reinterpret_cast<int*>(static_cast<Byte*>(pMem) + realSize - sizeof(int))) = signature;
	//앞쪽 경계표지 바로 다음의 메모리를 가리키는 포인터를 반환.
	return static_cast<Byte*>(pMem) + sizeof(int);
}
=> new 처리자를 호출하는 루프 없음. 이건 항목 51.
또 하나의 문제, 바이트 정렬(alignment)

컴퓨터 주소 아키텍쳐 요구사항들
포인터는 4바이트 단위로 정렬, double 값 8바이트 단위로 정렬 등등


부스트의 풀(Pool) 라이브러리 (항목 55)
이 라이브러리의 메모리 할당자는 크기가 작은 소형 객체를 많이 할당할 경우에 초점.
(바이트 정렬 문제라면 TR1(항목 54)을 참고)

언제 new 및 delete 의 기본제공 버전을 다른 것으로 대체?
1. 잘못된 힙 사용 탐지.
2. 동적 할당 메모리의 실제 사용에 관한 통계 정보를 수집.
3. 할당 및 해제 속력을 높이기 위해.
	고정된 크기의 객체만 만들어 주는 할당자의 전형적인 응용 예가 바로 클래스 전용(class-specific) 할당자.
	
4. 기본 메모리 관리자의 공간 오버헤드를 줄이기 위해

5. 적당히 타협한 기본 할당자의 바이트 정렬 동작을 보정하기 위해.
	x86 아키텍처는 double 8바이트 정렬이 가장 빠른데, 몇몇 컴파일러는 operator new 가 정렬 보장 안 함.

6. 임의의 관계를 맺고 있는 객체들을 한 군데 나란히 모아 놓기 위해
	여러 자료구조 사용 중일 때..
	페이지 부재(page fault) 발생 횟수 최소화하고 싶을 때, 자료구조를 담을 별도의 힙을 생성.
	메모리 군집화는 위치 지정(placement) new 및 위치지정 delete 를 통해 쉽게 구현

7. 그때그때 원하는 동작을 수행하도록 하기 위해
	공유 메모리 조작. C API로밖에 할 수 없을 때
	데이터의 보안 강화를 위해 해제한 메모리 블록에 0을 덮어쓰는 경우 등


잊지 말자!
1. 개발자가 스스로 사용자 정의 new 및 delete 를 작성하는 데는 여러 가지 나름대로 타당한 이유가 있다.
	수행성능 향상 / 힙 사용 시 에러 디버깅 / 힙 사용 정보 수집 목적 등;




항목 51: new 및 delete 를 작성할 때 따라야 할 기존의 관례를 잘 알아 두자

사용자 정의 버전 operator new, operator delete 관례
	반환 값이 제대로 / 가용 메모리 부족 시 new 처리자 함수 호출(항목 49) / 크기가 없는(0바이트) 메모리 요청에 대한 대비책
	실수로 '기본(normal' 형태의 new 가 가려지지 않도록. (항목 52)

반환 값
요청된 메모리를 마련해 줄 수 있으면 그 메모리에 대한 포인터를 반환.
마련 못하면 bad_alloc 예외 (항목 49)

but, 실패 시 new 처리자 함수 호출하는 식으로 메모리 할당을 2회 이상 시도하기 때문에 어려움.
new 처리자 함수에 대한 포인터가 널일 때;

void * operator new(std::size_t size) throw(std::bad_alloc) {	//operator new 함수는 다른 매개변수를 추가로 가질 수 있음
	using namespace std;
	if (size == 0) {	//0바이트 요청이 들어오면, 이것을 1바이트 요구로 간주하고 처리.
		size = 1;
	}
	while (true) {
		//size 바이트를 할당해 봄.
		if (/*할당이 성공했음*/) {
			return /*할당된 메모리에 대한 포인터*/;
		}
		//할당이 실패했을 경우, 현재의 new 처리자 함수가 어느 것으로 설정되어 있는지 찾아내기.
		new_handler globalHandler = set_new_handler(0);
		set_new_handler(globalHandler);
		
		if (globalHandler) (*globalHandler)();
		else throw std::bad_alloc();
	}
}


파생 클래스 객체를 담을 메모리를 할당하는 데 기본 클래스의 operator new 함수가 호출됨.;
class Base {
public:
	static void * operator new(std::size_t size) throw(std::bad_alloc);
};
class Derived:public Base {/*...*/ };	//Derived에는 operator new가 선언되지 않음

Derived *p = new Derived;	//Base::operator new 가 호출됨.


틀린 메모리 크기가 들어왔을 때 시작 부분에서 확인한 표준 operator new 를 호출하는 쪽;

void * Base::operator new(std::size_t size) throw(std::bad_alloc) {
	if (size != sizeof(Base)) {		//틀린 크기가 들어오면, 표준 operator new쪽에서 메모리 할당 요구를 처리하도록 넘김. (0바이트 점검도 됨)
		return ::operator new(size);
		//... //맞는 크기가 들어오면, 메모리 할당 요구를 여기서 처리
	}
}

C++에는 모든 독립 구조(freestanding)의 객체는 반드시 크기가 0이 넘어야 한다는 규칙(항목 39)
sizeof(Base)는 0초과.


배열은 '배열 new(array new) operator new[]' 라고 불러.
파생 클래스 객체는 기본 클래스 객체보다 더 크기 때문에,
요구된 바이트 수 / sizeof(Base)로 객체의 개수 계산 불가능

operator new 관례 끝.
operator delete 관례 시작.

널 포인터에 대한 delete 적용이 안전하다는 사실 보장.;
void operator delete(void *rawMemory) throw() {
	if (rawMemory == 0) return;		//널 포인터가 delete되려고 할 경우에는 아무것도 하지 않게 함.
	//rawMemory가 가리키는 메모리를 해제.
}

operaotr delete 역시 '틀린 크기로 할당된' 메모리의 요청을 ::operator delete 쪽으로 전달;
class Base {	//이전과 같으나, operator delete가 선언된 상태.
public:
	static void * operator new(std::size_t size_ throw(std::bad_alloc));
	static void operator delete(void *rawMemory, std::size_t size) throw();
};
void Base::operator delete(void *rawMemory, std::size_t size) throw() {
	if (rawMemory == 0) return;		//널 포인터에 대한 점검
	if (size != sizeof(Base)) {		//크기가 '틀린' 경우, 표준 operator delete가 메모리 삭제 요청을 맡도록 함.
		::operator delete(rawMemory);
		return;
	}
	//rawMemory가 가리키는 메모리를 해제.
	return;
}

가상 소멸자가 없는 기본 클래스로부터 파생된 클래스의 객체를 삭제하려고 할 경우, 
	operator delete 로 C++가 넘기는 size_t 값이 잘못될 수 있다.
	=> 가상 소멸자를 꼭 넣어야 한 경우 (항목 7)


잊지 말자!
1. 관례적으로, operator new 함수는 메모리 할당을 반복해서 시도하는 무한 루프를 가져야 하고,
	메모리 할당 요구를 만족시킬 수 없을 때 new 처리자를 호출해야 하며,
	0바이트에 대한 대책도 있어야 함.
	클래스 전용 버전은 자신이 할당하기로 예정된 크기보다 더 큰(틀린) 메모리 블록에 대한 요구도 처리해야 한다.

2. operator delete 함수는 널 포인터가 들어왔을 때 아무 일도 하지 않아야 함.
	클래스 전용 버전의 경우에는 예정 크기보다 더 큰 블록을 처리해야 한다.




항목 52: 위치지정 new 를 작성한다면 위치지정 delete 도 같이 준비하자.;

Widget *pw = new Widget;
위 함수 2개가 호출.
1. operator new
2. Widget의 기본 생성자.

2번 중 예외 발생 시 메모리 누출!
C++ 런타임 시스템이 제대로 알고 있으면 delete 호출 가능.

기본형;
void* operator new(std::size_t) throw(std::bad_alloc);

void* operator delete(void *rawMemory) throw();	///전역 유효범위에서의 기본형 시그니처
void operator delete(void *rawMemory, std::size_t size) throw();	//전형적인 기본형 시그니처

어떻게 new 와 delete 짝 지음 ?
예시 : operator new 사용자 정의 / operator delete 기본형
	메모리 할당 정보를 로그로 기록;
class Widget {
public:
	static void* operator new(std::size_t size, std::ostream& logStream)
		throw(std::bad_alloc);	//비표준 형태의 operator new
	static void operator delete(void *pMemory, size_t size) throw();		//클래스 전용 operator delete의 표준 형태
};

'위치지정(placement) new'
	매개변수를 추가로 받는 operator new.

유용한 예시: 어떤 객체를 생성시킬 메모리 위치를 나타내는 포인터를 매개변수로 받는 것;
void* operator new(std::size_t, void *pMemory) throw();		//위치지정 new
C++ 표준 라이브러리. <new> 헤더에 있음
사용처: vector의 미사용 공간에 원소 객체를 생성할 때


Widget *pw = new(std::cerr) Widget;		//operator new를 호출하는 데 cerr을 ostream 인자로 넘기는데,
										//이때 Widget 생성자에서 예외가 발생하면 메모리가 누출됨.

런타임 시스템은 호출된 operator new 가 받아들이는 '매개변수의 개수 및 타입이 똑같은' 버전의
operator delete 를 찾아내고 호출
위 코드는 ostream& 타입의 매개변수를 추가로 받아들이므로 똑같은 시그니처의 operator delete 필요.
위치 지정 버전 없는데 (Widget 생성자가 예외를 던지면) 어떤 operator delete 도 호출되지 않음.

void operaotr delete(void *, std::ostream&) throw();
'위치지정 delete';

class Widget {
public:
	static void* operator new(std::size_t size, std::ostream& logStream)
		throw(std::bad_alloc);	//비표준 형태의 operator new
	static void operator delete(void *pMemory) throw();
	
	static void operator delete(void *pMemory, std::ostream& logStream) throw();
};

Widget *pw = new (std::cerr) Widget;	//이전과 같은 사용자 코드. 하지만 메모리 누출 없음.

delete pw;		//기본형의 operator delete 가 호출됨.
위치지정 버전을 호출하지 않는다.
호출되는 생성자에서 예외가 발생했을 때만.
위치지정 new 함수 - 표준 operator delete - 위치지정 delete 모두 작성.


이름 가리기 문제 조심(항목 33);

class Base {
public:
	static void* operator new(std::size_t size, std::ostream& logStream)	//이 new가 표준 형태의 전역 new를 가립니다.
		throw(std::bad_alloc);
	//...
};
Base *pb = new Base;	//에러! 표준 형태의 전역 new가 가려졌죠
Base *pb = new (std::cerr) Base;	//문제 없음. 위치지정 new 호출

파생 클래스;
class Derived : public Base {
public:
	static void* operator new(std::size_t size)	//기본형 new를 클래스 전용으로 다시 선언.
		throw(std::bad_alloc);
	//...
};
Derived *pd = new (std::clog) Derived;	//에러! Base의 위치지정 new가 가려져 있기 때문.
Derived *pd = new Derived;	//문제 없음. Derived의 operator new를 호출.


전역 유효 범위에서 제공하는 operator new의 형태 3가지
void* operator new(std::size_t) throw(std::bad_alloc);			//기본형
void* operator new(std::size_t, void*) throw();					//위치지정
void* operator new(std::size_t, const std::nothrow_t*) throw();	//예외불가(항목 49)


기본 클래스에 new 및 delete 형태 전부 넣기 방법;
class StandardNewDeleteForms {
public:
	//기본형 new/delete
	static void* operator new(std::size_t size) throw(std::bad_alloc) {
		return ::operator new(size);
	}
	static void operator delete(void *pMemory) throw() {
		::operator delete(pMemory);
	}
	//위치지정 new/delete
	static void* operator new(std::size_t size, void *ptr) throw() {
		return ::operator new(size, ptr);
	}
	static void operator delete(void *pMemory, void *ptr) throw() {
		::operator delete(pMemory, ptr);
	}
	//예외불가 new/delete
	static void* operator new(std::size_t size, const std::nothrow_t& nt) throw() {
		return ::operator new(size, nt);
	}
	static void operator delete(void *pMemory, const std::nothrow_t&) throw() {
		::operator delete(pMemory);
	}
};

사용자 정의 형태 추가: 상속과 using 선언
표준 형태를 파생 클래스 쪽으로 끌어와 외부에서 사용할 수 있게 만들기;

class Widget : public StandardNewDeleteForms {	//표준 형태 물려받기
public:
	using StandardNewDeleteForms::operator new;	//표준 형태가 Widget 내부에 보이도록 만들기
	using StandardNewDeleteForms::operator delete;
	static void* operator new(std::size_t size, std::ostream& logStream) throw(std::bad_alloc);	//사용자 정의 위치지정 new 추가
	static void operator delete(void *pMemory, std::ostream& logStream) throw();	//앞의 것과 짝이 되는 위치지정 delete 추가.
};

잊지 말자!
1. operator new 함수의 위치지정(placement) 버전을 만들 때는, 위치지정 operator delete 도 만들기.
	생겼다 안 생겼다 하는 메모리 누출 현상
2. new, delete 위치지정 버전 선언 시, 표준 버전이 가려지지 않도록 하기.




잊지 말자!
컴파일러 경고 지나치지 않기.
컴파일러 경고에 너무 기대지 않기

최초 C++ 표준 라이브러리: STL, iostream, 로케일 등
TR1 라입브러리: 스마트 포인터, 일반화 함수 포인터, 해시 기반 컨테이너, 정규 표현식 외 10개
부스트: 라이브러리 사이트
이야기 등등


끗