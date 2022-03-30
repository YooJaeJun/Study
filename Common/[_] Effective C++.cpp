#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <mutex>
#include <iterator>
#include <algorithm>
using namespace std;

�������

implementaion ����ȯ��
ǥ�� ���� �����Ͽ� ����, ���α׷��� ������ �����ϰ� �Լ��� ������ �����ϴ� ���� ȯ������,
Ư���� ���� �ɼ� �Ʒ����� ����Ǵ� ���α׷� ���� ����Ʈ����(�����Ϸ�, ��Ŀ, ǥ�ض��̺귯��, �ü��)�� ����
'ǥ���� ������ ����ȯ��', '���α׷� ����'

undefined ������ ����, ���ǵ��� ����
ǥ�ؿ��� undefined�� �̽ļ��� ���ų� �߸��� ���α׷� ���� Ȥ�� ������ �ִ� �����ͳ� ���� ��Ȯ���� ��ü�� ��뿡 �����ϴ� ����(behavior)

implementation - defined ������ ���� ����, ������ ��������
ǥ�ؿ����� ��Ȯ�� �� ������ ������ �ʰ� ���� ���� ���ɼ��� �����ϸ�, ������ ���� �ٸ��� �����Ǵ� ����




�׸� 1 : C++�� ����� ����ü�� �ٶ���!

	C / ��ü ���� ������ C++ / ���ø� C++ / STL;




�׸� 2: #define�� �����ŵ� const, enum, inline �� ���ø���!

�����Ϳ� �Բ� ���� ��� const ������ ���;
const char * const authorName = "d";
���ڿ��� ���� std�� string ���;
const std::string authorName("d");

Ŭ���� ����� ����� �����ϴ� ���
� ����� ��ȿ������ Ŭ������ �����ϰ��� �� ���� �� ����� ����� ������ �ϴµ�,
�� ����� �纻 ������ �� ���� ���� ���ϰ� �ϰ� �ʹٸ� ����(static) ����� ������ ��.;
class GamePlayer {
private:
	static const int NumTurns = 5;
	int scores[NumTurns];
};
Ŭ���� ����� ���Ǵ� ���� ���Ͽ� �ΰ�, ��� ���Ͽ� ���� ����.
���ǿ��� ����� �ʱⰪ�� ������ �ȵ�.Ŭ���� ����� �ʱⰪ�� �ش� ����� ����� ������ �ٷ� �־����� ����.;


"enum hack" ���
������(enumerator)�� Ÿ���� ���� int�� ���� ������ �� �� �ִٴ� ���� Ȯ���� ���
���� Ÿ���� ���� Ŭ���� ����� ���� Ŭ���� �� �ʱ�ȭ�� �����ϴ� ���� �����Ϸ����� ������ ���(�ؽ�Ʈ rpg �� �������);
class GamePlayer {
private:
	enum { NumTurns = 5 };
	int scores[NumTurns];
};
const�� #define �޸� �Ҵ��ϴ� ���� �� ��;


��ũ���� ����
#define CALL_WITH_MAX(a, b) ((nodes) > (b) ? (nodes) : (b))
void main() {
	int a = 5, b = 0;
	CALL_WITH_MAX(++a, b);	//a�� �� �� ������
	CALL_WITH_MAX(++nodes, b + 10);
}
������ Ȯ��!�ζ��� �Լ��� ���� ���ø�;
template<typename T>
inline void callWithMax(const T& a, const T& b) {
	f(a > b ? a : b);	//���� �ڵ�� �޸� f�� ������ ������ ��.
}
const, enum, inline�� ����ϸ� ���� ó����(Ư�� #define)�� ���� �� �پ��
�ܼ��� ��� = > const ��ü or enum
�Լ�ó�� ���̴� ��ũ�� = > �ζ��� �Լ�;




�׸� 3: ������ ���̸� const�� ���̴� ����!

const char * p = greeting;	//���� ������, ��� ������
char * const p = greeting;	//��� ������, ���� ������
��, �����Ͱ� ����Ű�� ����� ����� ���� ��, const ��� ��Ÿ���� ���ݾ� �ٸ���,
���� �Ű����� Ÿ���� ��� �Ȱ���;
void f1(const Widget *pw);
void f2(Widget const *pw);

std::vector<int> vec;
//...
const std::vector<int>::iterator iter = vec.begin();	//��� �������� ��ó�� ����
*iter = 10;
++iter; //����. iter�� ���
std::vector<int>::const_iterator cIter = vec.begin();	//��� �������� ��ó�� ����
*cIter = 10;	//����. *cIter�� ���.
++cIter;

�Լ� ��ȯ �� ���;
class Rational {};
const Rational operator*(const Rational& lhs, const Rational& rhs);
��ȯ ���� ��� ��ü�� ���� ?
���� �Ǽ� ����
Rational a, b, c;
(nodes * b) = c;

��� ��� �Լ�
const Ű������ ������ �ش� ��� �Լ��� ��� ��ü�� ���� ȣ��� �Լ���.
�� Ŭ������ ������� ��ü�� ������ �� �ִ� �Լ��� �����̰�, �� ������ �� ���� �Լ��� �����ΰ��� ����ڰ� �˾ƾ� ��;
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
	std::cout << tb[0];		//���� ��� ȣ��
	const TextBlock ctb("World");
	tb[0] = 'x';
	ctb[0] = 'x';	//����. ��� ������ ��ü�� ���� �ȵ�.
}
operator[]�� ���� ����� char�� ������!�� ��ȯ;


� ��� �Լ��� ��� ������ �ǹ�
1 ��Ʈ���� �����
	�� ��ü�� � ������ ����� �ǵ帮�� �ʾƾ� ��(���� ����� ����)
	�ٸ� ����;
//...
char& operator[](std::size_t position) const {
	return pText[position];
}
//...
const CTextBlock cctb("Hello");
char *pc = &cctb[0];
*pc = 'J';	//����� �ǵ��������� ���� �����

2 ���� �����
	��ü �Ϻ� �� ��Ʈ ������ �ٲ� �� �ֵ�, ����������� �˾�ä�� ���ϰԸ� �ϸ� ����� ��� �ڰ��� �ִٴ� ��
	mutable : ������ ������ ����� ��Ʈ���� ������� ���⿡�� Ǯ���ִ� Ű����;
	
class CTextBlock {
	public:
		//...
		std::size_t length() const;
	private:
		char *pText;

		mutable std::size_t  textlength;	//�� ������ ������� � �������� ���� ����
		mutable bool lengthIsValid;

		std::size_t length() const {
			if (!lengthIsValid) {
				textlength = std::strlen(pText);
				lengthIsValid = true;
			}
			return textlength;
		}
};


���, ���� ���� �Լ��� 2�� ���� �� �ߺ��� ���̴� ��� (��� ��� �ֵ��� ��� ���)
class TextBlock {
public:
	const char& operator[](std::size_t position) const {
		//...
		return text[position];
	}
	char& operator[](std::size_t position) {	//��� ���� op[]�� ȣ���ϰ� ��
		return
			const_cast<char&> (	//op�� ��ȯ Ÿ�Կ� ĳ������ ����, const�� ������ϴ�.
				static_cast<const TextBlock&>	//*this�� Ÿ�Կ� const�� ���Դϴ�.
				(*this)[position]	//op[]�� ��� ������ ȣ���մϴ�.
				);
	}
};
�� �ڵ忡�� ĳ���� 2����
1 * this�� const ���̴� ĳ����
2 operator[]�� ��ȯ������ const�� ����� ĳ����

���� ����
const �� �ٿ� �����ϸ� �����Ϸ��� ���� �����
�����Ϸ��� ��Ʈ���� ����� ��Ű�� ���, �츮�� ���� ����� �̿��ؾ� ��
��� ���, ���� ��� �Լ��� �Ȱ����� ���� ������ ��� ������ ȣ��




�׸� 4 : ��ü�� ����ϱ� ���� �ݵ�� �� ��ü�� �ʱ�ȭ����!

�����ڿ��� �� ��ü�� ��� ���� �ʱ�ȭ����
��� ������ �ʱ�ȭ�� �򰥸��� �ʱ�;
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
	{	/*���⼭ �����ϴ� �� �ʱ�ȭ�� �ƴԽ�*/	}

�ʱ�ȭ ����Ʈ�� ���� ���ڴ� �ٷ� ������ ����� ���� �������� ���ڷ� ����

	�Ű����� ���� �����ڰ� Ŭ������ ����־��ٸ�..
	ABEntry::ABEntry()
	: theName(), theAddress(), thePhones()
	, numTimesConsulted(0) //��������� 0���� �ʱ�ȭ
	{}
�⺻ �����ڸ� ȣ���ؼ� �� �ʿ� ���ٰ� �������� ����
� ����� �ʱ�ȭ���� ���� �� �ִٴ� ��� �ľ� ����

��� �ʱ�ȭ ����Ʈ�� �ִ� ������� ������ Ŭ������ ������ ������ �����ϰ� �����ֱ�;


������ ���� ��ü�� �ʱ�ȭ ������ ���� ���� �������� �������� ? �ǹ�

���� ��ü(static object)�� �ڽ��� ������ �������� ���α׷��� ���� ������ ����ִ� ��ü.
���� ��ü �� �� ��ü�� ���� ��ü�� �ƴ�.
���� ��ü ����
1 ���� ��ü
2 ���ӽ����̽� ��ȿ�������� ���ǵ� ��ü
3 Ŭ���� �ȿ��� static ���� ����� ��ü
4 �Լ� �ȿ��� static ���� ����� ��ü
5 ���� ��ȿ�������� static ���� ���ǵ� ��ü
�̵� �� �Լ� �ȿ� �ִ� ���� ��ü == > ���� ���� ��ü(local static object)
�������� ������ ���� ��ü(non - local static object)

���� ����(translation unit)�� �������� ���� �ϳ��� ���� ����(object file)�� ����� ������ �Ǵ� �ҽ� �ڵ�
������ �ҽ��� �� ����� �ű�ٴ� �ǹ�
#include�ϴ� ����(��)���� ���ļ� �ϳ��� ���� ����.

������ ���� �������� ���ǵ� ������ ���� ��ü���� �ʱ�ȭ ������ ������ ���� �ʴ�.;

class FileSystem {	//������� �ִ� Ŭ����
public:
	//...
	std::size_t numDisks() const;
};
extern FileSystem tfs;

class Directory {	//����ڰ� ������ٰ� ����
public:
	Directory(params);
	//...
};
Directory::Directory(params) {
	//...
	std::size_t disks = tfs.numDisks();	//tfs ��ü�� ���⼭ �����
};
Directory tempDir(params);

�� �ڵ忡�� tfs�� tempDir���� ���� �ʱ�ȭ���� ������,
tempDir�� �����ڴ� tfs�� �ʱ�ȭ������ �ʾҴµ� tfs�� ����Ϸ��� �� ��
tfs�� tempDir�� �����ڵ� �ٸ��� ������� �ñ⵵, �ҽ� ���ϵ� �ٸ���~
== �ٸ� ���� ���� �ȿ��� ���ǵ� ������ ���� ��ü

tempDir ���� tfs�� �ʱ�ȭ �ϰ� �ʹ� ?
���� �ȵ�.���� �ٸ� ���� ������ ���ǵ� ������ ���� ��ü�� ������ ������� �ʱ�ȭ ������ ������ ���� �ʴ�.
�ٸ� �ذ�å : ������ ���� ��ü�� �ϳ��� �ô� �Լ��� �غ��ϰ� �� �ȿ� �� ��ü�� ����.
������ ���� ��ü�� ���� �������� �ʰ� �Լ� ȣ��� �����.
Singleton pattern �������;

class FileSystem {/*...*/ };

FileSystem& tfs() {		//tfs ��ü�� �� �Լ��� ���. Ŭ���� �ȿ� ���� ����� ���� ��
	static FileSystem fs;	//���� ���� ��ü�� �����ϰ� �ʱ�ȭ.
	return fs;	//��ü�� ���� ������ ��ȯ.
}
;
class Directory {/*...*/ };

Directory::Directory(params) {
	//...
	std::size_t disks = tfs.numDisks();
}
;
Directory& tempDir() {		//tempDir ��ü�� �� �Լ��� �����. Directory Ŭ������ ���� ����� ���� ��
	static Directory td;		//���� ���� ��ü�� ����/�ʱ�ȭ.
	return td;		//�� ��ü�� ���� �����ڸ� ��ȯ.
}
��, ������ ��ȯ �Լ��� ���������� ���� ��ü�� ���� ������,
���߽����� �ý��ۿ����� ���ۿ� ��ְ� ���� �� ����.

���� ���� ��ü�� ��ĩ�Ÿ�.
���� ������ ���� �� �õ� �ܰ迡�� ������ ��ȯ �Լ��� ���� ������ ȣ������� ��.;

���� ����!
1 �⺻ ���� Ÿ���� ��ü�� ���� �ʱ�ȭ.
2 �����ڿ�����, ��� �ʱ�ȭ ����Ʈ ��� ���.
	�ʱ�ȭ ����Ʈ�� ������ ��� ���� ��, Ŭ������ �� ������ ����� ����� ������ �Ȱ��� ����
3 ���� ���� ������ �ִ� ������ ���� ��ü���� �ʱ�ȭ ���� ������ ���ؼ� ����.
	������ ���� ��ü�� ���� ���� ��ü�� �ٲ���.;




�׸� 5: C++�� ���ٽ�½ ����� ȣ���� ������ �Լ��鿡 �˰��� ������!

�����Ϸ� �ڵ� �⺻�� ���� : ������, ���� ������, ���� ���� ������, �Ҹ���
class Empty {};
Empty e1;	//�⺻ ������, �Ҹ���
Empty e2(e1);	//���� ������
e2 = e1;	//���� ���� ������

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
NamedObject<int> no2(no1);	//���� ������ ȣ��

template<class T>
class Named Object {
public:
	//�� �����ڴ� ���� ��� Ÿ���� name�� ������ �ʽ��ϴ�. nameVlue�� ���� string�� �����ڰ� �Ǿ��� �����Դϴ�.
	//������ string�� ������ �ϱ� ������ char*�� ���ֹ��Ƚ��ϴ�.
	NamedObject(std::string& name, const T& value);
	//���� ���� ���������� operator=�� ����� �� ���ٰ� ����
private:
	std::string& nameValue;	//���� �� ����� ������
	const T objectValue;	//���� �� ����� ���
};
std::string newDog("Persephone");
std::string oldDog("Satch");
NamedObject<int> p(newDog, 2);
NamedObject<int> s(oldDog, 36);
p = s;
������ �ź�.Ŭ������ ���� ������ �����Ϸ��� ���� ���� ���� ������ ����.
private���� ���� �ÿ��� ������ �ź�

���� ����!
�����Ϸ��� ��쿡 ���� Ŭ������ ���� �⺻ ������, ���� ������, ���� ���� ������, �Ҹ��ڸ� �Ͻ������� ����� ���� �� �ֽ��ϴ�.




�׸� 6: �����Ϸ��� ���� �Լ��� �ʿ� ������ Ȯ���� �̵��� ����� ���� ������

���縦 ���� ���� ���, ;
class HomeForSale {/*...*/ };
HomeForSale h1;
HomeForSale h2;
HomeForSale h3(h1);	//�ϸ� �� �Ǵ� ����
h1 = h2;	//�ϸ� �� �Ǵ� ����
�̶� private���� �����ϸ� �����Ϸ��� �⺻ ������ �������� �ʰ� ������� ���ټ��� ������.
��, ������ �Լ� �� ��� �Լ����� ȣ��� ���� ����.

�ذ�å;
class HomeForSale {
public:
private:
	HomeForSale(const HomeForSale&);
	HomeForSale& operator=(const HomeForSale&);
};
�Ű������� �������� ���� ���·� ����
��ü ���� �õ� �� �����Ϸ� ����
��� �Լ� Ȥ�� ������ �Լ����� ���� �õ� �� ��Ŀ���� ����

��ũ ���� ������ ������ ���� ������ �ű��
�Ļ� Ŭ���� ���
class Uncopyable {
protected:	//�Ļ��� ��ü�� ���� ������ �Ҹ��� ���
	Uncopyable() {}
	~Uncopyable() {}
private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);	//����� ����
};

class HomeForSale : private Uncopyable {
	/*...*/	//���� �����ڵ�, ���� ���� �����ڵ� ���� ������� ����
}

(��ĵ�� ������ ���� ����)

���� ����!
�����Ϸ����� �ڵ����� �����ϴ� ����� ���ġ ��������,
�����Ǵ� ��� �Լ��� private���� ������ �Ŀ� ������ ���� ���� ä�� �α�.
Uncopyable�� ����� �⺻ Ŭ������ ���� �͵� �� ���.;




�׸� 7: �������� ���� �⺻ Ŭ���������� �Ҹ��ڸ� �ݵ�� ���� �Ҹ��ڷ� ��������!;

class TimeKeeper {
public:
	TimeKeeper();
	~TimeKeeper();
};
class AtomicClock : public TimeKeeper {};
class WaterClock : public TimeKeeper {};
class WristWatch : public TimeKeeper {};

���丮 �Լ� : ���� ������ �Ļ� Ŭ���� ��ü�� ���� �⺻ Ŭ���� �����͸� ��ȯ�ϴ� �Լ�;
TimeKeeper* getTimeKeeper();	//TimeKeeper���� �Ļ��� Ŭ������ ���� �������� �Ҵ�� ��ü�� �����͸� ��ȯ�մϴ�.
TimeKeeper *ptk = getTimeKeeper();	//TimeKeeper Ŭ���� �������� ���� �������� �Ҵ�� ��ü�� ����ϴ�.
/*...*/		//��ü ���
delete ptk;		//�ڿ� ������ ���� ���� ����(����)

c++���� �� �⺻ Ŭ���� �����͸� ���� �Ļ� Ŭ���� ��ü�� ������ ��
�� �⺻ Ŭ������ �񰡻� �Ҹ��ڰ� ��� ������, ���α׷� ������ ������ ����.

getTimeKeeper �Լ����� �����͸� ���� ���ƿ��� AtomicClock ��ü�� 
�⺻ Ŭ���� �����͸� ���� ������ �� AtomicClock Ŭ�������� ���ǵ� ������ ������� �� �������� ���� ����
AtomicCLock�� �Ҹ��ڵ� ������� ����.
�׷��� �⺻ Ŭ���� �κ�(TimeKeeper �κ�)�� �Ҹ�. ����¥�� �κ� �Ҹ�

class TimeKeeper {
public:
	TimeKeeper();
	virtual ~TimeKeeper();
};
TimeKeeper *ptk = getTimeKeeper();
delete ptk;	//����� ����

���� �Լ��� �ϳ��� ���� Ŭ������ ���� �Ҹ��ڸ� �������� �Ѵ�.

class Point {
public:
	Point(int xCoord, int yCoord);
	~Point();
private:
	int x, y;
};
�����Լ� ���̺� ������ vptr
���� �Լ��� �ּ�, �����͵��� �迭.
���� �Լ� ���̺� �������� �迭 == > ���� �Լ� ���̺� vtbl

�� Point Ŭ������ �����Լ��� ����, Point Ÿ�� ��ü�� ũ�Ⱑ Ŀ���� ���� �߻�
�Ͽ�, �Ҹ��ڴ� ���� �Լ��� �ϳ� �̻� Ŭ�������� ���
class SpecialString : public std::string {};	//std::string �� ���� �Ҹ��� ��� �Ұ���

SpecialString *pss = new SpecialString("Impending Doom");
std::string *ps;
ps = pss;	//SpecialString* => std::string*
delete ps;	//������ ����. *ps�� SpeicalString �κп� �ִ� �ڿ��� �����.
			//�� ������ SpecialString�� �Ҹ��ڰ� ȣ����� �ʱ� ����.
���� �Ҹ��ڰ� ���� Ŭ���� : STL �����̳� Ÿ��(vector, list, set, trl::unordered_map ��)

�߻� Ŭ����(abstract class) : �� ��ü�δ� �ν��Ͻ��� �� ����� Ŭ����. �� Ÿ���� ��ü�� ������ �� ����.
���� ���� �Լ��� �ش� Ŭ������ �߻� Ŭ������ ����.
������ � Ŭ������ �߻� Ŭ���������� ���ڴµ� ������ ���� ���� ���� ���� �Լ��� ���� ������?
�߻� Ŭ������ ����� ���� Ŭ������ ���� ���� �Ҹ��� ����.

class AWOV {	//AWOV = "Abstrack w/o Virtuals"
public:
	virtual ~AWOV() = 0;	//���� ���� �Ҹ��� ����
};

��� �⺻ Ŭ������ �������� ������ ����� ���� �ƴ�. (string, STL �����̳� Ÿ��)
���� �⺻ Ŭ�����δ� ���� �� ������ �������� ���� �ʵ��� ����� Ŭ������ ����(�׸� 6�� Uncopyable�� ǥ�� input_iterator_tag)
�⺻ Ŭ������ �������̽��� ���� �Ļ� Ŭ���� ��ü�� ������ ������ �ʴ´�.
�Ͽ�, �̵鿡�Լ� ���� �Ҹ��ڸ� �� �� ����.

���� ����!
1 �������� ���� �⺻ Ŭ�������� �ݵ�� ���� �Ҹ��ڸ� �����ؾ� �մϴ�.
	�� � Ŭ������ ���� �Լ��� �ϳ��� ���� ������, �� Ŭ������ �Ҹ��ڵ� ���� �Ҹ����̾�� �մϴ�.
2 �⺻ Ŭ������ ������� �ʾҰų� �������� ������ ������� ���� Ŭ�������� ���� �Ҹ��ڸ� �������� ���ƾ� �մϴ�.



�׸� 8: ���ܰ� �Ҹ��ڸ� ������ ���ϵ��� �ٵ�� ����!
;
class Widget {
public:
	~Widget() {/**/ }	//�� �Լ��κ��� ���ܰ� �߻��ȴٰ� ����
};
void doSomething() {
	std::vector<Widget> v;
}	//v �ڵ� �Ҹ�
���� �߻� �� ��� ó���ұ� ?

�ٸ� �� : �����ͺ��̽� ������ ��Ÿ���� Ŭ����;
class DBConnection {
public:
	static DBConnection create();	//DBConnection ��ü�� ��ȯ�ϴ� �Լ�. �Ű������� ���ǻ� ����.

	void close();	//������ �ݴ´�. �̶� ������ �����ϸ� ���ܸ� ������.
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
	DBConn dbc(DBConnction::create());	//DBConnection ��ü�� �����ϰ�, �̰��� DBConn ��ü�� �Ѱܼ� ������ �ñ�
	/*...*/		//DBConn �������̽��� ���� �� DBConnection ��ü�� ���
}	//��� ��. DBConn ��ü�� ���⼭ �Ҹ��. ���� DBConnection ��ü�� ���� close �Լ��� ȣ���� �ڵ����� �̷����.
���ܸ� ������ �Ҹ��ڴ� ���� ����

���ϴ� ���
1 close���� ���ܰ� �߻��ϸ� ���α׷��� �ٷ� �����ϴ�. �밳 abort�� ȣ��
DBConn::~DBConn() {
	try {
		db.close();
	}
	catch (/*...*/) {
		//close ȣ�� �����ߴٴ� �α� ����
		std::abort();
	}
}
2 close�� ȣ���� ������ �Ͼ ���ܸ� ���� ������. <= ���� �����ϰ� ���α׷��� �ŷڼ� �ְ� ���� ���� ������ ��
DBConn:~DBConn() {
	try {
		db.close();
	}
	catch (/*...*/) {
		//close ȣ�� �����ߴٴ� �α� ����
	}
}

�ٸ� �����? �������̽��� �� ����..
class DBConn {
public:
	void close() {
		db.close();
		closed = true;
	}
	~DBConn() {
		if (!closed) {
			try {	//����ڰ� ���� �� �ݾ����� ���⼭ �ݱ�
				db.closse();
			}
			catch (/*...*/) {		//������ �ݴٰ� �����ϸ�, ���и� �˸� �Ŀ� ������ �����ų� ���ܸ� ��Ű��
				//close ȣ�� ���� �α�
				//...
			}
		}
	}
private:
	DBConnection db;
	bool closed;
}
close ȣ���� å���� DBConn�� �Ҹ��ڿ��� DBConn�� ����ڷ� ���ѱ�� ���̵��.
� ������ ���ܸ� ����Ű�鼭 ������ ���ɼ��� �ְ�,
�� �� ���ܸ� ó���ؾ� �� �ʿ䰡 �ִٸ�,
�� ���ܴ� �Ҹ��ڰ� �ƴ� �ٸ� �Լ����� ��Ե� ���̾�� �Ѵ�.

���� ����!
1 �Ҹ��ڿ����� ���ܰ� ���������� �� �ȴ�.
	�Ҹ��� �ȿ��� ȣ��� �Լ��� ���ܸ� ���� ���ɼ��� �ִٸ�, 
	� �����̵��� �Ҹ��ڿ��� ��� �޾Ƴ� �Ŀ� ���� �������� ���α׷��� �������� �ؾ� �Ѵ�.
2 � Ŭ������ ������ ����Ǵٰ� ���� ���ܿ� ���� ����ڰ� �����ؾ� �� �ʿ䰡 �ִٸ�,
	�ش� ������ �����ϴ� �Լ��� �ݵ�� ������ �Լ�(��, �Ҹ��ڰ� �ƴ� �Լ�)�̾�� �Ѵ�.;




�׸� 9: ��ü ���� �� �Ҹ� ���� �߿��� ����� ���� �Լ��� ȣ������ ����!

��ü ���� �� �Ҹ� ���� �߿��� ���� �Լ��� ȣ���ϸ� ����� �� �˴ϴ�!
��ü ���� �� �Ҹ� ���� �߿��� ���� �Լ��� ȣ���ϸ� ����� �� �˴ϴ�!;


class Transaction {
public:
	Transaction();
	virtual void logTransaction() const = 0;	//Ÿ�Կ� ���� �޶����� �α� ����̶� ����
	//...
};
Transaction::Transaction() {	//������
	//...
	logTransaction();	//�ŷ� �α� ����
}

class BuyTransaction : public Transaction {	//Transaction�� �Ļ� Ŭ����
public:
	virtual void logTransaction() const;	//�� Ÿ�Կ� ���� �ŷ����� �α�
	//...
};
class SellTransaction : public Transaction {	//����
public:
	virtual void logTransaction() const;
	//...
};
BuyTransaction b;

�⺻ Ŭ������ �����ڰ� ȣ��� ���ȿ���, ���� �Լ��� ����� �Ļ� Ŭ���� ������ �������� �ʴ´�.
��� ��ü �ڽ��� �⺻ Ŭ���� Ÿ���� ��ó�� �����Ѵ�.

�⺻ Ŭ���� �����ڰ� ���ư��� ���� ������ �Ļ� Ŭ���� ������ ����� ���� �ʱ�ȭ�� ���°� �ƴϴ�.

�Ļ� Ŭ���� ��ü�� �⺻ Ŭ���� �κ��� �����Ǵ� ������, �� ��ü�� Ÿ���� �ٷ� �⺻ Ŭ����.
ȣ��Ǵ� ���� �Լ��� ��� �⺻ Ŭ������ ������ ������.
�̶� �Ļ� Ŭ������ �����ʹ� ���� �ʱ�ȭ�� ���°� �ƴϱ� ������, �ƿ� ������ ��ó�� ���.
�Ļ� Ŭ������ �������� ������ ���۵Ǿ�߸� ��μ� �Ļ� Ŭ���� ��ü�� ��� ����.;

class Transaction {
public:
	Transaction() {
		init();	//�񰡻� ��� �Լ� ȣ��
	}
	virtual void logTransaction() const = 0;
	//...
private:
	void init() { //...
		logTransaction();	//�񰡻� �Լ����� ���� �Լ� ȣ����
	}
};
�� �ڵ�� ������ ��ũ�� �ߵǳ� �ſ� ����.
���� ���̰ų� �Ҹ� ���� ��ü�� ���� �����ڳ� �Ҹ��ڿ��� ���� �Լ��� ȣ���ϴ� �ڵ带 �ԾƳ���.
����å;
class Transaction {
public:
	explicit Transaction(const std::string& logInfo);
	void logTransaction(const std::string& logInfo) const;	//������ �񰡻� �Լ�
	//...
};
Transaction::Transaction(const std::string& logInfo) {
	//...
	logTransaction(logInfo);
}
class BuyTransaction : public Transaction {
public:
	BuyTransaction(parameters)
		: Transaction(createLogString(parameters)) {	//�α� ������ �⺻ Ŭ���� �����ڷ� �ѱ��.
		/*...*/
	}
private:
	static std::string createLogString(parameters);
};
�Ļ� Ŭ���� �κп��� �⺻ Ŭ���� �����ڷ� �÷��ֱ�
�� ���� �Լ��� �⺻ Ŭ���� ������ ������ �ѱ� ���� �����ϴ� �뵵�� ���̴� ����� �Լ�
�⺻ Ŭ������ ��� �ʱ�ȭ ����Ʈ�� ���� �޷����� �� ��.
���� ����� ������ ä ������ ���� BuyTransaction ��ü�� ���ʱ�ȭ�� ������ ����� �Ǽ��� �ǵ帱 ���赵 ����.
= > '���ʱ�ȭ�� ������ ����� ���ǵ��� ���� ���¿� �ִ�.'

���� ����!
������ Ȥ�� �Ҹ��� �ȿ��� ���� �Լ� ȣ�� xxx.
���� �Լ���� �ص�, ���� ���� ���� �����ڳ� �Ҹ��ڿ� �ش�Ǵ� Ŭ������ �Ļ� Ŭ���� �����δ� �������� �ʴ´�.




�׸� 10: ���� �����ڴ� *this �� �����ڸ� ��ȯ�ϰ� �Ѵ�.

class Widget {
public: /*...*/
	Widget& operator=(const Widget& rhs) { /*...*/	//��ȯ Ÿ���� ���� Ŭ������ ���� ������.
		return *this;	//�º� ��ü(�� ������)�� ��ȯ. (���ڰ� ���� ��� +=, -= �� ���Կ��� ������ �Ծ� ����)
	}
};
�� ������ '����'

���� ����!
���� �����ڴ� *this�� �����ڸ� ��ȯ�ϵ��� ���弼��!




�׸� 11: operator=������ �ڱ���Կ� ���� ó���� ������ �ʵ��� ����

�ڱ����(self assignment)�̶�, � ��ü�� �ڱ� �ڽſ� ���� ���� �����ڸ� �����ϴ� ���� �ǹ���.
class Widget {/*...*/ };
Widget w;
//...
w = w;
nodes[i] = nodes[j];
*px = *py
�� �ڱ������ ���ɼ��� ���� ǰ�� �����.
���� ������ �ϳ��� ��ü�� �����ϴ� ����, '�ߺ�����';

class Base {/*...*/ };
class Derived : public Base {/*...*/ };
void doSomething(const Base& rb, Derived* pd);	//rb �� *pd�� ���� ���� ��ü���� ���� ����.

����: ���� �Ҵ�� ��Ʈ�� ����Ű�� ���� �����͸� ������ ����� ���� Ŭ����;
class Bitmap {/*...*/ };
class Widget {
	//...
	Widget& operator=(const Widget& rhs) {	//�������� ���� ����
		delete pb;	//������ ��Ʈ�� ��� ����
		pb = new Bitmap(*rhs.pb);	//rhs�� ��Ʈ�� ���
		return *this;
	}
private:
	Bitmap *pb;	//���� �Ҵ�� ��ü�� ����Ű�� ������
};
*this�� rhs�� ���� ��ü�� ���ɼ��� ����
delete �����ڰ� *this ��ü�� ��Ʈ�ʿ��� ����Ǵ� ���� �ƴ϶� rhs�� ��ü���� ����Ǿ� ����~

�������� ���
operator=�� ù�Ӹ����� ��ġ�� �˻�(identity test)
Widget& Widget::operator=(const Widget& rhs) {
	if (this == &rhs) return *this;	//��ü�� ������, �� �ڱ��������. �ڱ�����̸� �ƹ��͵� �� ��.
	delete pb;
	//...
}
�׷��� ���ܿ� �������� �ʴ�.
new Bitmap���� ���ܰ� ������(���� �Ҵ翡 �ʿ��� �޸� ����, Bitmap Ŭ���� ���� �����ڿ��� ���ܸ� ������ ��)
Widget ��ü�� �ᱹ ������ Bitmap�� ����Ű�� �����͸� ���Ȱ� Ȧ�� ���� ����.

������;
Widget& Widget::operator=(const Widget& rhs) {
	Bitmap *pOrig = pb;		//������ pb�� ��򰡿� ����� �д�.
	pb = new Bitmap(*rhs.pb);	//����, pb�� *pb�� �纻�� ����Ű�� �Ѵ�.
	delete pOrig;	//������ �纻�� �����Ѵ�.
	return *this;
}
���ܿ� �ڱ���� ��� ó����

�� �ٸ� ��� : ���� �� �¹ٲٱ�(copy and swap);
class Widget {
	void swap(Widget& rhs);	//*this�� ������ �� rhs�� �����͸� �¹ٲٱ� (�׸� 29 Ȯ��)
};
Widget& Widget::operator=(const Widget& rhs) {
	Widget temp(rhs);	//rhs�� �����Ϳ� ���� �纻�� �ϳ� �����.
	swap(temp);	//*this�� �����͸� �� �纻�� ���� �¹ٲ۴�.
	return *this;
}
���� �ٸ��� �����غ��� ? ;
Widget& Widget::operator=(Widget rhs) {	//rhs�� �Ѿ�� ���� ��ü�� �纻. ���� ���� ����
	swap(rhs);	//*this�� �����͸� �� �纻�� �����Ϳ� �¹ٲ�
	return *this;
}
����� ���� ������ ȿ������.

�̰͸��� ���� ����!
1 operator= �� ������ �� � ��ü�� �� �ڽſ� ���ԵǴ� ��츦 ����� ó���ϵ���.
	���� ��ü�� ������ ��ü�� �ּҸ� ���ص� �ǰ�, ������ ������ ������ ������ ���� ������,
	���� �� �¹ٲٱ� ����� �ᵵ �ȴ�.
2 �� �� �̻��� ��ü�� ���� �����ϴ� �Լ��� �ִٸ�,
	�� �Լ��� �Ѱ����� ��ü���� ���� ��ü�� ��쿡 ��Ȯ�ϰ� �����ϴ��� Ȯ���� ������.;




�׸� 12: ��ü�� ��� �κ��� �������� ��������

���� �Լ� == ���� �����ڿ� ���� ���� ������

���� : ���� ��Ÿ���� �Լ�;
void logCall(const std::string& funcName);	//�α� ��ϳ����� �����.
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

��������� ���� ������ ������ ���� ������ ��� �߰� �� ����;
class Date {/*...*/ };
class Customer {
public:
	//������ ����
private:
	std::string name;
	Date lastTranaction;
};
���� �Լ��� ������ �κк��簡 �ȴ�.
�̶� �����Ϸ��� ������� ���� ����.
�׷� ������, ������, ���� �Լ� ��� ó�� �� ����� ��.

������ Ŭ���� ��ӿ��� ����;
class PriorityCustomer : public Customer {	//�Ļ� Ŭ����
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
Customer�κ��� ����� ������ ������� �纻�� PriorityCustomer Ŭ������ ��� �ִµ�,
�̵��� ���簡 �� �ǰ� �־�!
��ü�� Customer �κ��� Customer �����ڿ� ���� �ʱ�ȭ�ȴ�.

�Ļ� Ŭ������ ���� ���� �Լ����� �⺻ Ŭ���� �κ��� ���縦 ���߸��� �ʵ��� �Ѵ�!;
PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs) 
	: Customer(rhs) , priority(rhs.priority) {	//�⺻ Ŭ������ ���� ������ ȣ��!
	logCall("PriorityCustomer copy ctor");
}
PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs) {
	logCall("PriorityCustomer copy assignment operator");
	Customer::operator=(rhs);	//�⺻ Ŭ���� �κ� ����!!
	priority = rhs.priority;
	return *this;
}

�ߺ� ���Ϸ��� ���� ���� �����ڿ��� ���� �����ڸ� ȣ���� �� ����.�� �ݴ뵵 �ȵ�.
���� ���� �������� ������ �̹� �ʱ�ȭ�� ���� ��ü�� ���� �ִ� ��.
�ٸ� ���ʿ��� ��ġ�� �κ��� ������ ��� �Լ��� ����� ȣ���� �� ����.
private init �� �׷���.

�̰͸��� ���� ����!
1 ��ü ���� �Լ��� �־��� ��ü�� ��� ������ ��� �� ��� �⺻ Ŭ���� �κ��� ���߸��� ���� �����ؾ� �Ѵ�.
2 Ŭ������ ���� �Լ� �� ���� ������ ��, ������ �̿��ؼ� �ٸ� ���� ���� x
	�� ���, ����� ������ ��3�� �Լ����� �и��� ���� ���ʿ��� �̰��� ȣ��;




�ڿ� ����
�׸� 13: �ڿ��������� ��ü�� �׸�!

���� : ���� �𵨸� Ŭ���� ���̺귯���� �۾�;
class Investment {/*...*/ };	//���� ������ ���ڸ� �𵨸��� Ŭ���� ������ �ֻ��� Ŭ������ ����

���丮 �Լ� ���
���丮 �Լ� : ���� ������ �Ļ� Ŭ���� ��ü�� ���� �⺻ Ŭ���� �����͸� ��ȯ�ϴ� �Լ�(�Ʒ��� ����);
	TimeKeeper* getTimeKeeper();	//TimeKeeper���� �Ļ��� Ŭ������ ���� �������� �Ҵ�� ��ü�� �����͸� ��ȯ�մϴ�.
	TimeKeeper *ptk = getTimeKeeper();	//TimeKeeper Ŭ���� �������� ���� �������� �Ҵ�� ��ü�� ����ϴ�.)

Investment* createInvestment();	
//Investment Ŭ���� ���뿡 ���� Ŭ������ ��ü�� ���� �Ҵ��ϰ�, �� �����͸� ��ȯ.
//�� ��ü�� ������ ȣ���� �ʿ��� ���� �ؾ� ��. (�Ű������� ���ÿ����� ������)
void f() {
	Investment *pInv = createInvestment();	//���丮 �Լ� ȣ��
	//...
	delete pInv;	//��ü ����
}
delete �տ� ���� return���� ���� ���, ���ܸ� ���� ���, ���� �������� ��� ����


auto_ptr �����ƴµ�...
��ư �ڵ����� delete �ҷ���;
void f() {
	std::auto_ptr<Investment>pInv(createInvestment());	//���丮 �Լ� ȣ��
}
��ü�� ����ϴ� ����� �߿��� 2���� Ư¡
1 �ڿ��� ȹ���� �Ŀ� �ڿ� ������ ��ü���� �ѱ��.
	�ڿ� ȹ�� �� �ʱ�ȭ(Resource Acquisition Is Initialization : RAII)��� �̸�.
	�ڿ� ȹ��� �ڿ� ���� ��ü�� �ʱ�ȭ�� �� ���忡�� �̷����� �� ����.
2 �ڿ� ���� ��ü�� �ڽ��� �Ҹ��ڸ� ����ؼ� �ڿ��� Ȯ���� �����ǵ��� �Ѵ�.
	�Ҹ��ڴ� � ��ü�� �Ҹ�� ��(��ȿ������ ����� ��� ��) �ڵ����� ȣ��Ǳ� ������ �ڿ� ������;

auto_ptr : ����Ʈ ������
	��ü�� �����ϸ� ���� ��ü�� null�� ����.;
std::auto_ptr<Investment> pInv1(createInvestment());
std::auto_ptr<Investment> pInv2(pInv1);		//pInv1�� ���� null
pInv1 = pInv2;		//���� 1�� �� ��ü�� ����Ű�� ������, pInv2�� null
= > auto_ptr�� ��ü�� �� �� �̻� ���� ������ �� �Ǵ� �䱸����!����...

���� ī���� ��� ����Ʈ ����Ʈ(reference - counting smart pointer : RCSP)
	Ư���� � �ڿ��� ����Ű��(�����ϴ�) �ܺ� ��ü�� ������ �����ϰ� �ִٰ�
	�� ������ 0�� �Ǹ� �ش� �ڿ��� �ڵ����� �����ϴ� ����Ʈ ������.
"tr1::shared_ptr"�� ��ǥ���� RCSP;

void f() {
	std::tr1::shared_ptr<Investment> pInv(createInvestment());	//���丮 �Լ� ȣ��. shared_ptr�� �Ҹ��ڸ� ���� pInv �ڵ� ����.
}
�ڿ������� �����;
void f() {
	std::tr1::shared_ptr<Investment> pInv1(createInvestment());
	std::tr1::shared_ptr<Investment> pInv2(createInvestment());	//pInv1�� 2�� ���ÿ� �� ��ü�� ����Ų��.
	pInv1 = pInv2;	//��������. ���� ���� ����.
}	//pInv1, 2 �Ҹ�Ǹ�, �̵��� ����Ű�� �ִ� ��ü�� �ڵ� ����.

�ڿ��� �����ϴ� ��ü�� �Ἥ �ڿ��� �����ϴ� ���� �߿���.
auto_ptr �� tr1::shared_ptr�� �Ҹ��� ���ο��� delete ������ ���(delete[]�� �ƴ�. 16�忡�� Ȯ��)
���� �Ҵ��� �迭�� ���� ����ϸ� ����~
std::auto_ptr<std::string>	//���� ���� �߻�
	aps(new std::string[10]);	//�߸��� deletle �߻�
std::tr1::shared_ptr<int> spi(new int[1024]);	//���� ���� �߻�.

�� �ٸ� ����
createInvestment �Լ��� ��ȯŸ���� �����ͷ� �Ǿ�����. Investment* createInvestment();
��ȯ�� �����Ϳ� ���� delete ȣ���� ȣ���� �ʿ��� �ؾ� �ϴµ�, �ؾ������ ����.
�̰� �׸� 18���� to be continued...

�̰͸��� ���� ����!
1 �ڿ� ������ ���� ����, ������ �ȿ��� �ڿ��� ȹ���ϰ� �Ҹ��ڿ��� �װ��� �����ϴ� RAII��ü�� ����սô�!
2 �Ϲ������� �θ� ���̴� RAII Ŭ������ tr1::shared_ptr �׸��� auto_ptr.
	�� �� �� ����尡 ���� �� ������ �������̱� ������ �밳 �� ����.
	�ݸ� auto_ptr�� ����Ǵ� ���� ��ü�� null�� ����.;




�׸� 14: �ڿ� ���� Ŭ������ ���� ���ۿ� ���� �����ϰ� ��������!

���� ������ �ʴ� �ڿ��� auto_ptr�̳� tr1::shared_ptr ���� ����Ʈ �����ͷ� ó�����ֱ⿣ ���� �ʴ�.

���� : Mutex Ÿ���� ���ؽ� ��ü�� �����ϴ� C API;
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
{	//�Ӱ� ���� ���ϱ� ���� ��� ����.
	Lock ml(&m);	//���ؽ��� ���
}
������� �ߵʽ�;
Lock ml1(&m);	//m�� ���
Lock ml2(ml1);	//ml1 �� ml2�� ����.


RAII ��ü ����� �� � ������ �̷������ �ұ�...
1 ���� ���� ?
	private���� �����(�׸� 6����);
class Lock : priavate Uncopyable { }	//���� ���� ����.

2 �����ϰ� �ִ� �ڿ��� ���� ���� ī������ ����.
�ش� �ڿ��� �����ϴ� ��ü�� ������ ���� ī��Ʈ�� ������Ű�� ���.
tr1::shared_ptr�� ����ϰ� ����.
��, mutextPtr�� Ÿ���� Mutex*���� tr1::shared_ptr<Mutex>�� �ٲٸ�,
tr1::shared_ptr�� ���� ī��Ʈ�� 0�� �� �� �ڽ��� ����Ű�� �ִ� ����� ������ �����Ƿ�,
������ ������ ���� ��� �������� ����.

������ ���� tr1::shared_ptr�� '������(deleter)' �� �����.
tr1::shared_ptr�� ���� ī��Ʈ�� 0�� �Ǿ��� �� ȣ���ϴ� �Լ� or �Լ� ��ü.;

class Lock {
public:
	explicit Lock(Mutex *pm)	//shared_ptr�� �ʱ�ȭ�ϴµ�, ����ų �����ͷ� Mutext ��ü�� ������ ����ϰ� �����ڷ� unlock �Լ� ���
		: mutextPtr(pm, unlock) {
		lock(mutextPtr.get());	//get�� �׸� 15 Ȯ��
	}
private:
	std::tr1::shared_ptr<Mutex> mutextPtr;	//���� ������ ��� shared_ptr ���
};
��ü �Ҹ� ������ ���� �� �ƴ϶� �����Ϸ��� ������ �Ҹ��ڸ� ���� �����Ѵ�.

3 �����ϰ� �ִ� �ڿ��� ��¥�� �����Ѵ�.
	�ڿ��� �� ���� �� ������ �纻�� Ȯ���� �����ϴ� �� <= = �ڿ� ���� Ŭ������ �ʿ��� ������ ���
	�ڿ� ���� ��ü�� �����ϸ� �� ��ü�� �ѷ��ΰ� �ִ� �ڿ����� ����Ǿ�� �Ѵ�.
	== > ��, ���� ���� ���� ex.string Ÿ��

4 �����ϰ� �ִ� �ڿ��� �������� �ű��.
	� �ڿ��� ������ �����ϴ� RAII ��ü�� �� �ϳ��� �����ϵ��� ����� ���� ��,
	��ü ���� �� �������� �纻 ������ �ƿ� �ű� ��
	auto_ptr ���� ���� ���;

�̰͸��� ���� ����!
1 RAII ��ü�� ����� �� ��ü�� �����ϴ� �ڿ��� ���� ������ �Ȱ� ���� ������
	�� �ڿ��� ��� �����ϴ��Ŀ� ���� RAII ��ü�� ���� ������ ������.
2 RAII Ŭ������ �����ϴ� �Ϲ����� ���� ������ ���縦 �E���ϰų� ���� ī������ ���ִ� ������ ������;

(�����..)




�׸� 15: �ڿ� ���� Ŭ�������� �����Ǵ� �ڿ��� �ܺο��� ������ �� �ֵ��� ����

�ڿ� ���� ��ü�� ��ȣ���� �Ѿ ���� �ڿ��� ���� ������ ���;
std::tr1::shared_ptr<Investment> pInv(createInvestment());
int daysHeld(const Investment *pi);	//���ڱ��� ���Ե� ���ķ� ����� ������ ����
int days = daysHeld(pInv)	//����!
Investment* Ÿ���� �ƴ�, tr1::shared_ptr<Investment> Ÿ���� ��ü�� �Ѱ�� ����.

�� ��ȯ 2����
����� ��ȯ(explicit conversion)
�Ͻ��� ��ȯ(implicit conversion)

tr1::shared_ptr �� ����� ��ȯ�� �����ϴ� get�̶�� ��� �Լ� ����.
int days = daysHeld(pInv.get());

����Ʈ �����ʹ� ������ ������ ������(operator-> �� operator*)�� �����ε��ϰ� ����.;
class Investment {
public:
	bool isTaxFree() const;
};
Investment* createInvestment();		//���丮 �Լ�
std::tr1::shared_ptr<Investment> pi1(createInvestment());	//tr1::shared_ptr�� �ڿ� ������ ����
bool taxable1 = !(pi1->isTexFree());	//operator->�� �Ἥ �ڿ��� ����

std::auto_ptr<Investment> pi2(createInvestment());	//auto_ptr�� �Ͽ��� �ڿ� ���� �õ��� ��
bool texable2 = !((*pi2).isTaxFree());	//operator*�� �Ἥ �ڿ��� ����


����;
FontHandle getFont();	//C API���� ������ �Լ�. �Ű������� ����� ����
void release(FontHandle fh);	//C API���� ������ �Լ�. 

class Font {	//RAII Ŭ����
public:
	explicit Font(FontHandle fh)	//�ڿ��� ȹ��. ���⼭ ���� ���� ���� �������� ����. �ڿ� ������ C API�� �ϱ� ����.
		: f(fh) {}
	~Font() { releaseFont(f); }
	FontHandle get() const {
		return f;
	}
private:
	FontHandle f;	//���� ��Ʈ �ڿ�
}
�̶� �Ϻ� ���� API�� ���� ���� ������ get�� ȣ���ؾ� ��;
void changeFontSize(FontHandle f, int newSize);	//��Ʈ API�� �Ϻ�
Font f(getFont());
int newFontSize;
changeFontSize(f.get(), newFontSize);		//Font���� FontHandle�� ��������� �ٲ� �Ŀ� �ѱ�ϴ�.

�ٸ� ��: FontHandle���� �Ͻ��� ��ȯ �Լ��� Font���� ����;
class Font {
public:
	//...
	operator FontHandle() const {		//�Ͻ��� ��ȯ �Լ�
		return f;
	}
};
Font f(getFont());
int newFontSize;
changeFontSize(f, newFontSize);		//Font���� FontHandle�� �Ͻ��� ��ȯ�� �����մϴ�.

�ٸ� �Ͻ��� ��ȯ�� ���� �Ǽ� ���� ������.
Font f1(getFont());
FontHandle f2 = f1;		//���� �ǵ��� Font ��ü�� �����ϴ� ���̾��µ�, f1�� FontHandle�� �ٲ�� ���� �����.

�Ͽ�, get ���� ����� ��ȯ �Լ��� �����ϴ� ���� ���� ���� ����.

�̰͸��� ���� ����!
1 ���� �ڿ��� ���� �����ؾ� �ϴ� ���� API�鵵 ���� ������,
	RAII Ŭ������ ���� ���� �� Ŭ������ �����ϴ� �ڿ��� ���� �� �ִ� ����� ���� �־�� �Ѵ�.
2 �ڿ� ������ ����� ��ȯ Ȥ�� �Ͻ��� ��ȯ�� ���� ����.
	�������� ������ ����� ��ȯ�� ��ü������ �� ������,
	�� ���Ǽ��� ���� ���� �Ͻ��� ��ȯ�� ������.;




�׸� 16: new �� delete�� ����� ���� ���¸� �ݵ�� ������!

std::string *stringArray = new std::string[100];
//...
delete stringArray;
= > stringArray�� ����Ű�� 100���� string ��ü�� �� 99�� �Ҹ� �ȵ�
new ���� �Ҵ� ��
1 �޸� �Ҵ�(operator new �Լ� ȣ��)
2 �Ҵ�� �޸𸮿� 1�� �̻��� ������ ȣ��
delete ��� ��
1 ���� �Ҵ�� �޸𸮿� 1�� �̻��� �Ҹ��� ȣ��
2 �� �� �޸� ����(operator delete �Լ� ȣ��)
delete �����ڰ� ����Ǵ� ��ü ���� == > '�Ҹ��ڰ� ȣ��Ǵ� Ƚ��';

std::string *stringPtr1 = new std::string;
std::string *stringPtr2 = new std::string[100];
//...
delete stringPtr1;		//��ü 1�� ����
delete[] stringPtr2;	//��ü �迭 ����

vector<string>���� ����� �Ҵ�, ���� ���� �� ���� ���� ��!

�̰͸��� ���� ����!
new ǥ���Ŀ�[]�� ������, �����Ǵ� delete ǥ���Ŀ���[]�� ��� �Ѵ�.
new ǥ������[]�� �� ������, �����Ǵ� delete ǥ���Ŀ��� []�� ���� ���ƾ� �Ѵ�.;




�׸� 17: new�� ������ ��ü�� ����Ʈ �����Ϳ� �����ϴ� �ڵ�� ������ �� �������� ������!

���� : ó�� �켱���� �˷��ִ� �Լ� + ���� �Ҵ��� ��ü�� ���� �켱���� �����ϴ� �Լ�;
int priority();
void processWidget(std::tr1::shared_ptr<Widget> pw, int priority);
processWidget(new Widget, priority());

������ �ȵ�.tr1::shared_ptr�� �����ڴ� explicit �� ����Ǿ��� ������, new Widget�̶�� ǥ���Ŀ� ���� ������� �����Ͱ�
tr1::shared_ptr Ÿ���� ��ü�� �ٲٴ� �Ͻ����� ��ȯ�� ����.
�ݸ� �Ʒ��� �ڵ�� �����ϵ�.;
processWidget(std::tr1::shared_ptr<Widget>(new Widget), priority());
but, �ڿ��� �긱 ���ɼ��� �ִ�.

c++���� ���� ���� ������ ������ ������..
1 priority�� ȣ��
2 "new Widget"�� ����
3 tr1::shared_ptr �����ڸ� ȣ��
�����Ϸ��� ���� 1, 2���� �������� �� ����
priority ȣ�� �κп��� ���� �߻� �� new Widget���� ���� ������ ���� ����
�ڿ� ������ ������ �� �˰� �غ��� tr1::shared_ptr�� ����Ǳ⵵ ���� ����.

���ϴ� ���;
std::tr1::shared_ptr<Widget> pw(new Widget)		//new�� ������ ��ü�� ����Ʈ �����Ϳ� ��� �ڵ带 �ϳ��� �������� ��������.
processWidget(pw, priority());

�̰͸��� ���� ����!
	new �� ������ ��ü�� ����Ʈ �����ͷ� �ִ� �ڵ�� ������ �� �������� ����ô�!
	�̰��� �� �Ǿ� ������, ���ܰ� �߻��� �� ������ϱ� ���� �ڿ��� ������ �ʷ��� �� �ִ�.;




���� �� ����

�׸� 18: �������̽� ����� ����� ���⿣ ����, ���͸��� ���⿣ ��ư� ����

;
class Date {
public:
	Date(int month, int day, int year);
}
���޵� ������ �߸��� ������ �ִ�.

���ο� Ÿ���� �鿩�� �������̽� ��ȭ.
����(wrapper) Ÿ��;
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
Date d(30, 3, 1995);	//����. Ÿ�� Ʋ�����߷�
Date d(Day(30), Month(3), Year(1995));	//����. Ÿ�� Ʋ��
Date d(Month(3), Day(30), Year(1995));	//Ÿ�� ������!

��ȿ�� �� ���� �� �� ����.
enum �� �ִ� ���.��, Ÿ�� ������ ����.;

class Month {
public:
	static Month Jan() {	//�� �Լ��̸� ��ü�� �� �� �Ǵ°��� �Ʒ� ����
		return Month(1);
	}
	//...
	static Month Dec() {
		return Month(12);
	}
private:
	explicit Month(int m);	//Month ���� ���� �������� �ʵ��� ���ȣ�� �����ڰ� private ���.
};
class Date {
public:
	Date(const Month& m, const Day& d, const Year& y);
};
Date d(Month::Jan(), Day(30), Year(1995));

�׸� 4�� ������, ������ ���� ��ü���� �ʱ�ȭ�� �а� ������ ���� ������ �ִ�.
�Ͽ�, Ư���� ���� ��Ÿ���� �� ��ü�� ���� �ʰ� �Լ��� ��.

operator*�� ��ȯ Ÿ���� const�� ���������ν� ����� ���� Ÿ�Կ� ������ ���� �Ǽ� ����
if (a * b = c) ...

����: ���丮 �Լ� Investment Ŭ���� ������ �����Ҵ� �� ��ü�� ������ ��ȯ;
Investment* createInvestment();
�����͸� ���߿��� �����ؾ� ��.�׸� ���� ����Ʈ ������ ����� ��.

����Ʈ ������ ����Ѵٴ� ��ǵ� �ؾ������ ?
���ʺ��� ���丮 �Լ��� ����Ʈ �����͸� ��ȯ�ϰ� ����� ��.;
std::tr1::shared_ptr<Investment> createInvestment();
���� ������ �ڿ� ���� �Լ�(������)�� ���� ���� ���� �ִ�. (auto_ptr�� �̷� ����� ����)

����Ʈ ������ tr1::shared_ptr���� �� ���� ���ڸ� �޴� �����ڰ� �ִ�.
������ ���� ������, ���� ī��Ʈ 0�� �� �� ȣ��� ������.;
std::tr1::shared_ptr<Investment> pInv{ static_cast<Investment*>(0), getRidOfInvestmen };	
//0�� �� ������, �� �Լ��� ����� ���� ������

std::tr1::shared_ptr<Investment> createInvestment() {
	std::tr1::shared_ptr<Investment> retVal(statck_cast<Investment*>(0), getRidOfInvestment);
	retVal = ...;	//retVal�� ���� ��ü�� ����Ű���� �����.
	return retVal;
}

std::tr1::shared_ptr�� �� �ϳ��� Ư¡
���� DLL ����(cross - DLL problem) �ذ�
	: � ���� ��ũ ���̺귯��(DLL)�� new �� ��µ� �� ��ü�� ������ ���� ������ DLL�� �ٸ� DLL�� �ִ� delete �� ���� ���.
	: new / delete ¦�� �޶� ������ ��Ÿ�� ����.
�⺻ �����ڰ� std::tr1::shared_ptr�� ������ DLL�� ������ DLL���� delete ����ϵ��� ������� ����.;

std::tr1::shared_ptr<Investment> createInvestment() {
	return std::tr1::shared_ptr<Investment>(new stock);
}
=> �ٸ� DLL�� ���̸� �Ѿ�� ���� ���� no.

std::tr1::shared_ptr ������ ��ǰ �� ���� ���̴� �ν�Ʈ ���̺귯���� shared_ptr
���� �����ͺ��� ũ�� ������ ���� ������ ���� �޸𸮱��� �߰��� �Ŵ޸���,
����� �Ǽ��� ���� ��� �پ��.

�̰͸��� ���� ����!
1 ���� �������̽��� ����� ���̰� ����� ���͸��� ���⿡ ��ƽ��ϴ�.
	�������̽��� ���� ���� �� Ư���� ���� �� �ֵ��� ����ϰ� �� ����սô�.
2 �������̽��� �ùٸ� ����� �̲��� ������δ� �������̽� ������ �ϰ��� ����ֱ�,
	�׸��� �⺻���� Ÿ�԰��� ���� ȣȯ�� �����ϱⰡ �ֽ��ϴ�.
3 ������� �Ǽ��� �����ϴ� ������δ� ���ο� Ÿ�� �����, Ÿ�Կ� ���� ������ �����ϱ�,
	��ü�� ���� ���� ���� �ɱ�, �ڿ� ���� �۾��� ����� å������ ���� �ʱⰡ �ֽ��ϴ�.
4 tr1::shared_ptr�� ����� ���� �����ڸ� �����մϴ�. �� Ư¡ ������ tr1::shared_ptr��
	���� DLL ������ ���� �ָ�, ���ؽ� ���� �ڵ����� ��� �����ϴ� �� �� �� �ֽ��ϴ�.;




�׸� 19: Ŭ���� ����� Ÿ�� ����� �Ȱ��� �������

���� ������ Ÿ���� ��ü ���� �� �Ҹ��� ��� �̷������ �ϴ°�?
	��� �����ϴ°��� ���� operator new �� �޸� �Ҵ� �Լ� ���迡 ����.

��ü �ʱ�ȭ�� ��ü ���԰� ��� �޶�� �ϴ°�?
	�ʱ�ȭ�� ������ �򰥸��� �ʴ� ��.

���ο� Ÿ������ ���� ��ü�� ���� ���� ���޵Ǵ� ��쿡 � �ǹ̸� �� ���ΰ�?
	� Ÿ�Կ� ���� '���� ���� ����'�� �����ϴ� ���� ���� �������̴�?

���ο� Ÿ���� ���� �� �ִ� ������ ���� ���� ������ �������� ���� ���ΰ�?
	Ŭ������ ������ ����� �� ���� ���� ������ �ݵ�� ��ȿ ==> Ŭ������ '�Һ��Ӽ�(invariant)'
	������, ���� ������, ���� ����(setter) �Լ��� �Һ��Ӽ��� ���� ���� �¿�ȴ�.

������ Ŭ���� ��� �����(inheritance graph)�� ���� ���ΰ�?
	��� �Լ��� �����ΰ�, �񰡻��ΰ� ���ΰ� ���� ū ����. Ư�� �Ҹ���

� ������ Ÿ�� ��ȯ�� ����� ���ΰ�?
	T1 Ÿ���� ��ü�� T2 Ÿ���� ��ü�� �Ͻ������� ��ȯ�ǵ��� �ϰ� �ʹٸ�, T1 Ŭ������ Ÿ�� ��ȯ �Լ�(operator T2)
	or ���� 1���� ȣ��� �� �ִ� ����ȣ��(non-explicit) �����ڸ� T2 Ŭ������ �־�α�
	����� Ÿ�� ��ȯ�� ����ϰ� �ʹٸ�, Ÿ�� ��ȯ ������or����ȣ�� ������ ������ �ʱ�.

� �����ڿ� �Լ��� �ξ�� �ǹ̰� ������?

ǥ�� �Լ��� �� � ���� ������� �� ���ΰ�?
	private �� �����ؾ� �ϴ� �Լ� �ش�

���ο� Ÿ���� ����� ���� ���ٱ����� ��� �ʿ� �� ���ΰ�?
	public protected private, ������, ��ø �� ���

'������� ���� �������̽�'�� ������ �� ���ΰ�?
	���� ���� Ÿ���� ������ ������ � ����? ���� ���� �� ���� ������, �ڿ� ���(��� �� ���� �޸� ��)

���� ����� Ÿ���� �󸶳� �Ϲ����ΰ�?
	���ο� Ŭ���� ���ø��� �����ؾ� �� ��.

������ �ʿ��� Ÿ���ΰ�?
	���� Ŭ���� ��� �� �� �ƽ����� �Ļ� Ŭ������ ���� �̴���,
	�����ϰ� ���� �Լ������ ���ø��� �� �� �� �����ϴ� ���� ����.

�̰͸��� ���� ����!
	Ŭ���� ���� == Ÿ�� ����. �� ���� ��� ���;




�׸� 20: '���� ���� ����'���ٴ� '�����ü �����ڿ� ���� ����' ����� ���ϴ� ���� �밳 ����!

�Լ� �Ű������� ���� ������ '�纻'�� ���� �ʱ�ȭ.
���� ���� ������ ������ ����.;
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

�� �ڵ� ������ ���� ���� �Ҹ��� ���� �� ȣ��...
��� ��ü�� ���� ������(reference - to - const)�� ��������!;
bool validateStudent(const Student& s);

= > ���� ��������� ��ü�� ���� ������, �Ҹ��� ���� ȣ����� ����
����ս� ����(slicing problem)�� ������.

����: ������ Ŭ���� ���̺귯��;
class Window {
public:
	std::string name() const;	//������ �̸� ��ȯ
	virtual void display() const;	//������ �׵θ� �� ���� �׸�
};
class WindowWithScrollBars : public Window {
public:
	virtual void display() const;
};

�߸��� ����;
void printNameAndDisplay(Window w) {
	std::cout << w.name();
	w.display();
}
WindowWithScrollBars wwsb;
printNameAndDisplay(wwsb);

� Ÿ���� ��ü�� �Ѿ�� �⺻ Window Ŭ���� ��ü�� ����� ���� ��.�Ļ� Ŭ������ �Լ��� ȣ��ȵ�!!;

void printNameAndDisplay(const Window& w) {	/*...*/ }	//���� �Ű������� �߸��� �ʴ´�.

�̰͸��� ���� ����!
1 '���� ���� ����'���ٴ� '��� ��ü �����ڿ� ���� ����'�� ��ȣ�սô�!
��ü������ ȿ������ �Ӹ� �ƴ϶� ����ս� �������� ���� �ݴϴ�.
2 �� �׸񿡼� �ٷ� ��Ģ�� �⺻���� Ÿ��, STL �ݺ���, �׸��� �Լ� ��ü Ÿ�� �� 3�������� ���� �ʴ´�.
�̵��� '���� ���� ����'�� �� �����մϴ�.




�׸� 21: �Լ����� ��ü�� ��ȯ�ؾ� �� ��쿡 �����ڸ� ��ȯ�Ϸ��� ���� ����!;

class Rational {
public:
	Rational(int numerator = 0,	int denominator = 1);	//�����ڰ� explicit�� ������� ���� ������ �׸� 24���� Ȯ��
private:
	int n, d;	//���� �� �и�
	friend const Rational operator*(const Rational& lhs, const Rational& rhs);	//��ȯ Ÿ���� const�� ������ �׸� 3���� Ȯ��
};

�����ڴ� �׳� �̸��̾�!
�� �Լ��� �����ڸ� ��ȯ�ϵ��� ��������ٸ�, �� �Լ��� ��ȯ�ϴ� �����ڴ� �ݵ�� �̹� �����ϴ� Rational ��ü�� ������.

�Լ� ���ؿ��� ���ο� ��ü�� ����� ��� (��� ������ ����)
1 ���ÿ� ����� ��;
const Rational& operator*(const Rational& lhs, const Rational& rhs) {
	Rational result(lhs.n * rhs.n, lhs.d * rhs.d);
	return result;
}
= > ������ �ҷ��� �ϴ� ���� + ������ ������ ��ȯ���� ����
���� ��ü�� ���� �����ڸ� ��ȯ�ϴ� �Լ��� ������ �ൿ�� �̾���.

2 ���� ����� ��;
const Rational& operator*(const Rational& lhs, const Rational& rhs) {
	Rational *result = new Rational(lhs.n * rhs.n, lhs.d * rhs.d);
	return *result;
}
= > ������ ������ ȣ�� + ���� delete ?
Rational w, x, y, z;
w = x * y * z;		//operator*(operator*(x,y),z)
�̶� delete 2�� ����� ��.;

const Rational& operator*(const Rational& lhs, const Rational& rhs) {
	statck Rational result;	//��ȯ�� �����ڰ� ����ų ���� ��ü
	result = ...;	//lhs*rhs
	return result;
}
= > ������ ������ ����;

inline const Rational operator*(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.n * rhs.n, lhs.d * rhs.d);
}
=> �ùٸ� ����

�̰͸��� ���� ����!
	���� ���� ��ü�� ���� �����ͳ� �����ڸ� ��ȯ�ϴ� ��, Ȥ�� ���� �Ҵ�� ��ü�� ���� �����ڸ� ��ȯ�ϴ� ��,
	�Ǵ� ���� ���� ��ü�� ���� �����ͳ� �����ڸ� ��ȯ�ϴ� ���� �׷� ��ü�� �� �� �̻� �ʿ����� ���ɼ��� �ִٸ� ���� xxx;




�׸� 22: ������ ����� ����� ���� private �������� �������

������ ����� �ݵ�� private ����̾�� �Ѵ�...

public�� �� �Ǵ� ����
1 ������ �ϰ���
	ex. get_x()? get_x? ��� �Լ��� () ���� �ǰ���~
2 �� �� �б� ���� �Լ� ���
3 ĸ��ȭ(encapsulation)

class SpeedDataCollection {
public:
	void addValue(int spped);
	double averageSoFar() const;	//��� �ӵ� ��ȯ
};
ĸ��ȭ ����:
������ ����� �Լ� �������̽� �ڿ� ���߸� �̵�: 
������ ����� �аų� �� �� �ٸ� ��ü�� �˸� �޽����� �����ٵ���, 
Ŭ������ �Һ��Ӽ� �� ��������, ���������� �����Ѵٵ���,
������ ȯ�濡�� ����ȭ�� �Ǵٵ��� �ϴ� ��.

ĸ��ȭ���� �ʾҴ� == �ٲ� �� ���� �� �����ϼ�.

protected �� public �� �ٸ� �� ����...

�̰͸��� ���� ����!
1 ������ ����� private ����� �����սô�!
	���������� �ϰ��� �ִ� ������ ���� ��θ� ����
	�ʿ信 ���� ������ ���� ��� ����
	Ŭ������ �Һ��Ӽ��� ��ȭ
	���� ������ ���뼺�� ����
2 protected �� public ���� �� ���� ��ȣ�ް� �ִ� ���� ���� �ƴϴ�.




�׸� 23: ��� �Լ����ٴ� ���� �������� �Լ��� �� ���������!

����: �������� Ŭ����;
class WebBrowser {
public:
	void clearCache();
	void clearHistory();
	void removeCookies();
};
class WebBrowser {
public:
	void clearEverything();		//�� �� �Լ� ��Ƽ� �ҷ��ִ� �Լ� ����
};
�� �ڵ忡�� ���� �Լ��� ����;
void clearBrowser(WebBrowser& wb) {
	void clearCache();
	void clearHistory();
	void removeCookies();
}

���� �Լ��� ����ϸ� ��Ű¡ �������� ��������!
������ �������� �����!
WebBrowser�� Ȯ�强�� ���δ�.

� �����͸� �����ϴ� �Լ��� ������ �� �������� ĸ��ȭ ������ ����.
���� �������� �Լ��� � Ŭ������ private ��� �κ��� ������ �� �ִ� �Լ��� ������ �ø��� �����Ƿ�,
ĸ��ȭ ������ �� ����!

��, friend �Լ��� private ����� ���� ���ٱ����� �ش� Ŭ������ ��� �Լ��� ���� ���ٱ��Ѱ� �Ȱ��� ������,
ĸ��ȭ�� ���� ���� ���� ����.

���� �Լ��� �ε�, ���ӽ����̽� ����� �� �ڿ�������;
namespace WebBrowserStuff {
	class WebBrowser {/*...*/ };
	void clearBrowser(WebBrowser& wb);
}
����
//"webbrower.h" ��� - WebBrowser Ŭ���� ��ü�� ���� ���
//���� �ٽ� ��ɵ��� ����Ǿ� ����
namespace WebBrowserStuff {
	class WebBrowser { ... };	//�ٽ� ���� ���. ���� ��� ����ڰ� ��� �ϴ� ���� �Լ���
}
//"webbrowserbookmarks.h" ���
namespace WebBrowserStuff {
	...		//���ã�� ���� ���� �Լ���
}
//"webbrowserbookmarks.h" ���
namespace WebBrowserStuff {
	...		//��Ű ���� ���� �Լ���
}
���� �Լ� ��ü�� ���� ���� ��� ���Ͽ�(�׷��� �ϳ��� ���ӽ����̽���) ������ ������
���� �Լ� ������ Ȯ��(extend)�� �ս�������.

�̰͸��� ���� ����!
	��� �Լ����ٴ� ���� �������� �Լ��� ���� ������ �սô�.
	ĸ��ȭ ������ ��������, ��Ű¡ �������� Ŀ����, ������� Ȯ�强�� �þ�ϴ�.




�׸� 24: Ÿ�� ��ȯ�� ��� �Ű������� ���� ����Ǿ�� �Ѵٸ� ���� �Լ��� ��������!

Ŭ�������� �Ͻ��� Ÿ�� ��ȯ�� �����ϴ� ���� �Ϲ������� ���� �����̴�...
���� �� ��Ģ���� ���ܰ� �ִ�.
������ ��Ÿ���� Ŭ�������� �������� ���������� �Ͻ��� ��ȯ�� ����ص� ����;

class Rational {
public:
	Rational(int numerator = 0, int denominator = 1);	//�����ڿ� �Ϻη� explicit�� ������ ����.
												//int���� Rational���� �Ͻ��� ��ȯ�� ����ϱ� ����.
	int numerator() const;		//���� �� �и� ���� ���ٿ� �Լ�.
	int denominator() const;
private:
};
���� �����;
class Rational {
public:
	const Rational operator*(const Rational& rhs) const;
};
����� ������ ��ȯ�ϰ�, ����� ���� �����ڸ� ���ڷ� �޾Ƶ��̵���. (�׸� 3, 20, 21);
Rational oneEighth(1, 8);
Rational oneHalf(1, 2);
Rational result = oneHalf * oneEighth;
result = result * oneEight;

����
ȥ���� ��ġ ���� - Rational�� int �� ���� ������ ��;
result = oneHalf * 2;
result = 2 * oneHalf;	//����
��ȯ��Ģ �̼���

�� �Լ��� �Լ� ���·� �ٲ㺸��.;
result = oneHalf.operator*(2);
result = 2.operator*(oneHalf);		//����

result = operator*(2, oneHalf);		//����

const Rational sorted(2);		//2�κ��� �ӽ� Rational ��ü ����
result = oneHalf * sorted;	//oneHalf.operator*(temp); �� ����.
���ȣ��(explicit)�� ������� ���� �����ڰ� �ֱ� ������ ����
����ȣ�� �����ڿ� �ص�
result = 2 * oneHalf;	//����
�Ͻ� Ÿ�� ��ȯ�� ���� �Ű������� ��������� �Ű����� ����Ʈ�� ��� �־�߸� �Ѵ�.

ȥ���� ��ġ ���� �����ϰ� �ʹ�?
���� operator*�� ���� �Լ��� ����, �����Ϸ� �ʿ��� ��� ���ڿ� ���� �Ͻ��� Ÿ�� ��ȯ�� �����ϵ��� ��
class Rational {/*...*/ };	//operator*�� ����.

const Rational operator*(const Rational& lhs, const Rational& rhs) {	//���� �Լ�
	return Rational(lhs.numerator() * rhs.numerator(),
		lhs.denominator() * rhs.denominator());
}
Rational oneFourth(1, 4);
Rational result;
result = oneFourth * 2;
result = 2 * oneFourth;
=> ����

operator* �Լ��� Rational Ŭ������ ������ �Լ���? �ƴϿ�.
Rational�� public �������̽����� �Ἥ ������ �� �ֱ� ����.

"��� �Լ��� �ݴ�� ������ �Լ��� �ƴ϶� ���� �Լ���."
� Ŭ������ ���� ���踦 �ξ� ����� ������ ��� �Լ��� �� �Ǵ� �Լ��� ����
(��� ���ڿ� ���� Ÿ�� ��ȯ�� �ʿ��ϴٵ簡 �ϴ� ������)
������xxx. ����~

Rational�� Ŭ������ �ƴ� Ŭ���� ���ø����� ����� ���� ���� ���� ���� �ٸ� (�׸� 46���� ������~)

�̰͸��� ���� ����!
	� �Լ��� ���� ��� �Ű�����(this �����Ͱ� ����Ű�� ��ü�� �����ؼ�)�� ����
	Ÿ�� ��ȯ�� ���� �ʿ䰡 �ִٸ�, �� �Լ��� �����̾�� �Ѵ�!!




�׸� 25: ���ܸ� ������ �ʴ� swap�� ���� ������ ������ ����!

swap : �ڱ���� ���� ��ó
�������� ����;
namespace std {
	template<typename T>
	void swap(T& a, T& b) {
		T temp(a);
		a = b;
		b = temp;
	}
}

'pimpl ���뱸(pointer to implementation)';
������� ��ü�� ���� �¹ٲ۴ٸ�, pImpl �����͸� ��¦ �ٲٴ� ��
��� ����
class WidgetImpl {
public:
private:
	int a, b, c;
	std::vector<double> v;
};
class Widget {		//pimpl ���뱸 �����
public:
	Widget(const Widget& rhs);
	Widget& operator=(const Widget& rhs) {		//WIdget�� �����ϱ� ����, �ڽ��� WidgetImpl ��ü�� ����
		*pImpl = *(rhs.pImpl);
	}
private:
	WidgetImpl *pImpl;
};
namespace std {
	template<>
	void swap<Widget>(Widget& a, Widget& b) {
		swap(a.pImpl, b.pImpl);	//Widget�� �����ϱ� ���� ������ pImpl �����͸� �¹ٲ�
	}
}
template<>�� std::swap�� ���� ���ø� Ư��ȭ(total template speicalization)
<Widget> �� T�� Widget�� ��� Ư��ȭ�� ���� �˸�.

�ٸ� ���� ������ �ȵ�.�����Ͱ� private;

class Widget {
public:
	void swap(Widget& other) {
		using std::swap;	//���� �ʿ��� ���� �̵���
		swap(pImpl, other.pImpl);	//Widget�� �¹ٲٱ� ����, �� Widget�� pImpl �����͸� �¹ٲٱ�
	}
};
namespace std {
	template<>
	void swap<Widget>(Widget& a, Widget& b) {
		a.swap(b);
	}
}
�����ϵ�.STL �����̳ʿ� �ϰ��� ������

Widget�� WidgetImpl�� Ŭ������ �ƴ� Ŭ���� ���ø����� �ϸ� �ܾʵ� ? ;
template<typename T>
void swap<Widget<T>>(Widget<T>& a, Widget<T>& b) { a.swap(b); }
= > C++�� Ŭ���� ���ø��� ���� �κ� Ư��ȭ�� ���������, �Լ� ���ø��� ���ؼ��� �����

�Լ� ���ø��� �κ������� Ư��ȭ �ϰ� ���� �� �����ε� ������ �ϳ� �߰�;
namespace std {
	template<typename T>
	void swap(Widget<T>& a, Widget<T>& b) { a.swap(b); }
}
= > �ٸ� std�� ���ο� ���ø� �߰��ϸ� �ȵ�.�����ǻ���.

���
��� swap�� ȣ���ϴ� ���� swap ����.
���� �Լ��� std::swap�� Ư��ȭ �����̳� �����ε� �������� ���������� ������ �ȴ�.;

���ø� ���� ������ �Ẹ��~
namespace WidgetStuff {		//namespace�� std�� �ƴ϶� ���� ���� ����� ���� WidgetStuff�� ����ִٰ� ����
	template<typename T>
	class Widget {/*...*/ };
	
	template<typename T>
	void swap(Widget<T>& a, Widget<T>& b) {		//���� swap �Լ�
		nodes.swap(b);
	}
}

c++�� �̸� Ž�� ��Ģ == '���� ��� Ž��(argument-dependent lookup)' or '��ϱ� Ž��(Koenig lookup)'
� �Լ��� � Ÿ���� ���ڰ� ������, 
�� �Լ��� �̸��� ã�� ���� �ش� Ÿ���� ���ڰ� ��ġ�� ���ӽ����̽� ������ �̸��� Ž���� ���ٴ� ��Ģ
� �ڵ尡 �� Widget ��ü�� ���� swap�� ȣ���ص�, ���ӽ����̽� �ȿ��� Widget Ư��ȭ ������ ã�Ƴ���.

Ŭ���� Ÿ�� ������ swap�� �ǵ��� ���� ������ ȣ��ǵ��� �ϰ� ������
�� Ŭ������ ������ ���ӽ����̽� �ȿ� ���� ������ swap�� ����� �ְ�,
std::swap�� Ư��ȭ ������ �غ�.;

template<typename T>
void doSomething(T& obj1, T& obj2) {
	swap(obj1, obj2);
}
= > � swap ȣ���ұ� ?
1 std�� �Ϲ��� ���� 2 std�� �Ϲ����� Ư��ȭ�� ���� 3 T Ÿ�� ������ ����

Ÿ�� T ���� ������ ������ �װ� ȣ���ϰ�, �������� std�� �Ϲ��� ������ ȣ���ϰ� �ʹ�.;
template<typename T>
void doSomething(T& obj1, T& obj2) {
	using std::swap;	//std::swap�� �� �Լ� ������ ����� �� �ֵ��� ����� ����
	swap(obj1, obj2);	//T Ÿ�� ������ swap�� ȣ��. �տ� std:: ���� ����~ �װ� std �͸� ����� ��.
}

1 ǥ�� swap�� �츮 Ŭ���� �� Ŭ���� ���ø��� ������ ���� ȿ���̸�, ���α�

2 ǥ�� swap ȿ���� ������� ������(Ŭ���� �� Ŭ���� ���ø��� 'pimpl ���뱸'�� ����� ���)
2.1 swap�� public����. ���ܸ� ������ �ȵ�.
2.2 Ŭ����orŬ���� ���ø��� ����ִ� ���ӽ����̽��� ���� swap�� ����� �ֱ�. 
	������ ���� swap ��� �Լ��� �� ���� �Լ��� ȣ��.
2.3 ���ο� Ŭ������ ����ٸ�, �� Ŭ������ ���� std::swap�� Ư��ȭ ������ �غ�. 
	Ư��ȭ ���������� swap ��� �Լ��� ȣ��.

3 swap ȣ�� ��, swap�� ȣ���ϴ� �Լ��� std::swap�� �� �� �ֵ��� using ������ �ݵ�� ����. 
	�� ���� swap�� ȣ���ϵ�, ���ӽ����̽� ������ ������ �ʱ�.

��� ������ swap�� ���� ������ �ʾƾ� �ϴ� ����: 
	�׸� 29 to be continued..
	���� �������� ǥ�� swap�� ���� ������ ���� ���Կ� ����ϴµ�, ���� ���� �� ���� ���� �Լ��� ���� �߻� ���.

�̰͸��� ���� ����!
1 std::swap�� �������� Ÿ�Կ� ���� ������ ������ ������ �ִٸ�, swap ��� �Լ��� ����
2 ��� swap�� ����������, �� ����� ȣ���ϴ� ���� swap�� ����.
	Ŭ����(���ø��� �ƴ�)�� ���ؼ��� std::swap�� Ư��ȭ.
3 ����� ���忡�� swap�� ȣ���� ����, std::swap�� ���� using ������ �־� �� �Ŀ� ���ӽ����̽� ���� ���� swap�� ȣ��
4 ����� ���� Ÿ�Կ� ���� std ���ø��� ���� Ư��ȭ�ϴ� ���� ����.
	�׷��� std�� � ���̶� ���� �߰��Ϸ��� ���� ����.;




����

�׸� 26: ���� ���Ǵ� ���� �� �ִ� ������ ���ߴ� �ټ��� ��������

����: ��й�ȣ �� ��� ��ȣȭ�Ͽ� ��ȯ�ϴ� �Լ�;
//�� �Լ��� "encrypted ������ �ʹ� ���� ������ �����ϴ�.
std::string encryptPassword(const std::string& password) {
	using namespace std;
	string encrypted;	//�̰��̰�
	if (password.length() < MinimumPasswordLength) {
		throw logic_error("Password is too short");
	}
	//...		//�־��� ��й�ȣ�� ��ȣȭ�Ͽ� enctypted ������ �ִ� �� �ʿ��� �ϵ� �ߴٰ� ����
	return encrypted;
}
��ȣȭ �κ� ����;
//�� �Լ��� encrypted ������ �ʿ��� ������ �� ������ ���Ǹ� ���߱� ������, ������ ��ȿ����
void encrypt(std::string& s);
std::string encryptPassword(const std::string& password) {
	std::string encrypted;	//�⺻ �����ڿ� ���� ��������� encrypted
	encrypted = password;
	encrypt(encrypted);
	return encrypted;
}
=> �ǹ̵� ���� ��뵵 ����ġ ���� �⺻ ������ ȣ�� �ǳʶ���!;
std::string encryptPassword(const std::string& password) {
	std::string encrypted(password);	//������ �����԰� ���ÿ� �ʱ�ȭ. �̶� ���� ������ ����.
	encrypt(encrypted);
	return encrypted;
}

������ ?
��� A
Widget w;
for (int i = 0; i < n; ++i) {
	w = i/*i�� ���� �޶����� ��*/;
}
��� B
for (int i = 0; i < n; ++i) {
	Widget w(i/*i�� ���� �޶����� ��)*/);
}
=> A����� ������ �Ҹ��� �ξ� �� �Ҹ� ��.
�ٸ� ���α׷��� ���ص��� ������������ �� ������ �� �ִ�.
������ ������-�Ҹ��� �ֺ��� ����� �� ���, ��ü �ڵ忡�� ���� ���ɿ� �ΰ��� �κ��� �ǵ帮�� �ʴٰ� �����ϸ� B ���.

�̰͸��� ���� ����!
	���� ���Ǵ� ���� �� ���� ������ ���߱�!




�׸� 27: ĳ������ ����, �� ����! ���� ����

c++ ���� ��Ģ: � ���� �־ Ÿ�� ������ ������ �ʵ��� �����Ѵ�.

c ��Ÿ�� ĳ��Ʈ
1 (T) ǥ����
2 T(ǥ����)	: �Լ� ���
=> 1,2 ���� ��Ÿ���� ĳ��Ʈ

c++ ��Ÿ�� ĳ��Ʈ
=> ���� ��Ÿ���� ĳ��Ʈ
const_cast<T>(ǥ����) 
	: ��ü�� �����(constness)�� ���ִ� �뵵. (Ȥ�� �ֹ߼�(volatileness)�� ���ִ� �뵵)
dynamic_cast<T>(ǥ����) 
	: ������ �ٿ�ĳ������ �� ���.
	: �־��� ��ü�� � Ŭ���� ��� ���뿡 ���� Ư�� Ÿ������ �ƴ����� ����.
	: ��Ÿ�� ����� ����
reinterpret_cast<T>(ǥ����)
	: �����͸� int�� �ٲٴ� �� �Ϻ� ���� ĳ����
	: �̽ļ��� ����. å���� �� �� �� ���. ex. ���� �޸𸮿� ����� �Ҵ��� �ۼ��ϴ� ���
static_cast<T>(ǥ����)
	: �Ͻ��� ��ȯ[���� ��ü�� ��� ��ü�� �ٲٰų�, int �� double �� �ٲٴ� ���� ��ȯ]�� ������ ������ �� ���. (�� �ݴ�� �ȵ�)
	: Ÿ�� ��ȯ�� �Ųٷ� �����ϴ� �뵵(void*�� �Ϲ� Ÿ���� �����ͷ� �ٲٰų�, �⺻ Ŭ������ �����͸� �Ļ� Ŭ������ �����ͷ� �ٲٴ� ��)

����ϴ� ���� ������ ��ü�� �� �Ǿ� ���� ���� ����

class Widget {
public:
	explicit Widget(int size);
};
void doSomeWork(const Widget& w);
doSomeWork(Widget(15));		//�Լ� ��� ĳ��Ʈ �������� int�κ��� Widget�� ����.
doSomeWork(static_cast<Widget>(15));		//c++��� ĳ��Ʈ�� �Ἥ int�κ��� Widget�� ����.
= > �������� ���� ��Ÿ�� ĳ��Ʈ ����.;

class Base {};
class Derived : public Base {};
Derived d;
Base *pb = &d;		//Derived* => Base*�� �Ͻ��� ��ȯ
=> �Ļ� Ŭ���� ��ü�� ���� �⺻ Ŭ���� �����͸� �ʱ�ȭ�ϴ� �ڵ�.
�������� ����(offset)�� Derived* �����Ϳ� �����Ͽ� ������ Base* ������ ���� ���ϴ� ������ ��Ÿ�ӿ� �̷����.

ex. ��ü�� �ּҸ� char* �����ͷ� �ٲ㼭 ��� ������ �����ϴ� �ڵ�� ���� �׻� ������ ����

���� �� ���� �ڵ�
���� �Լ��� �Ļ� Ŭ�������� �������ؼ� ������ �� �⺻ Ŭ������ ������ ȣ���ϴ� ������ ���� ���� �־�޶�-;
class Window {
public:
	virtual void onResize() {}
};
class SpecialWindow : public Window {
public:
	virtual void onResize() {
		static_cast<Window>(*this).onResize();		//*this�� Window�� ĳ�����ϰ� �װͿ� ���� onResize�� ȣ���ϳ� ���� �ȵ�
	}
};
= > ĳ������ �Ͼ�� *this�� �⺻ Ŭ���� �κп� ���� �纻�� �ӽ������� �������.
onResize�� �⺻ Ŭ���� �κ��� '�纻'�� ��� ȣ��� ��.
�ᱹ Window::onResize�� ȣ������ �ʰ� ������.

����;
class SpecailWindow : public Window {
public:
	virtual void onResize() {
		Window::onResize();		//*this���� Window::onResize�� ȣ��.
	}
};


dynamic_cast
������..

�Ļ� Ŭ������ �Լ��� ȣ���ϰ� ������, �� ��ü�� ������ �������� �⺻ Ŭ������ ������(or������)�ۿ� ���� ���...
1 �Ļ� Ŭ���� ��ü�� ���� �����͸� �����̳ʿ� ��Ƶ�.;
class Window {/*...*/ };
class SpecialWindow : public Window {
public:
	void blink();
};
typedef std::vector<std::tr1::shared_ptr<SpecialWindow> > VPSW;
VPSW winPtrs;
for (VPSW::iterator iter = vinPtrs.begin(); iter != winPtrs.end(); ++iter) {
	(*iter)->blink();		//if(SpecialWindow *psw = dynamic_cast<SpecailWindow*>(iter->get()))  psw->blink() ���� �� ����
}

2 �⺻ Ŭ���� �������̽��� ���� ������ �� �ִ� �ٸ� ���
	: �ƹ� �͵� �� �ϴ� �⺻ blink�� �����ؼ� ���� �Լ��� ����;
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

������(cascading) dynamic_cast ���� ���ϱ�!
if (SpecialWindow *psw1 = dynamic_cast<SpecailWindow1*>(iter->get())) { psw->blink(); }
if (SpecialWindow *psw2 = dynamic_cast<SpecailWindow2*>(iter->get())) { psw->blink(); }
if (SpecialWindow *psw3 = dynamic_cast<SpecailWindow3*>(iter->get())) { psw->blink(); }
...

�� �ۼ��� c++�ڵ�� ĳ������ ���� ���� �ʴ´�.

�̰͸��� ���� ����!
1 �ٸ� ����� �����ϴٸ� ĳ������ ���Ͻʽÿ�.
	Ư�� ���� ���ɿ� �ΰ��� �ڵ�� dynamic_cast �� �ٽ� ����
2 ĳ������ ��¿ �� ���� �ʿ��ϴٸ�, �Լ� �ȿ� �����.
	�ּ��� ����ڴ� �ڽ��� �ڵ忡 ĳ������ ���� �ʰ� �� �Լ��� ȣ���� �� �ְ� ��.
3 ���� ��Ÿ�Ϻ��� c++ ��Ÿ�� ĳ��Ʈ ��ȣ.
	�߰��ϱ⵵ ����, �����ڰ� � ������ �ǵ��ߴ��� �� �ڼ��ϰ� �巯��.




�׸� 28: ���ο��� ����ϴ� ��ü�� ���� �ڵ��� ��ȯ�ϴ� �ڵ�� �ǵ��� ������

����: �簢�� ���;
class Point {
public:
	Point(int x, int y);
	void setX(int newVal);
	void setY(int newVal);
};
struct RectData {	//Rectangle�� ���� ���� �� ������
	Point ulhc;		//�������, �����ϴ� (upper left-hand corner) (lower right-hand corner)
	Point lrhc;
};
class Rectangle {
private:
	std::tr1::shared_ptr<RectData> pData;
};

������ ���� ������� �Ẽ�� ? ;
class Rectangle {
public:
	Point& upperLeft() const { return pData->ulhc; }
	Point& lowerRight() const { return pData->lrhc; }
};
Point coord1(0, 0);
Point coord2(100, 100);
const Rectangle rec(coord1, coord2);
rec.upperLeft().setX(50);
=> ��� ��ü�� rec�� ������ ���� Point ������ ����� �����ڷ� ����� �ٲ� �� �ִ�.

1. Ŭ���� ������ ����� �ƹ��� ���ܺ��� 
	�� ����� �����ڸ� ��ȯ�ϴ� �Լ����� �ִ� ���ٵ��� ���� ĸ��ȭ ������ ��������.
	ulhc�� lrhc�� private ���� ����Ǿ ���������δ� public ���.
	�̵��� �����ڸ� ��ȯ�ϴ� upperLeft, lowerRight �Լ��� ���������� public ��� �Լ�.
2 � ��ü���� ȣ���� ��� ��� �Լ��� ������ ��ȯ ���� ���� �����Ͱ� �� ��ü�� �ٱ��� ����Ǿ� �ִٸ�,
	�� �Լ��� ȣ��ο��� �������� ������ �����ϴ�.
	(��Ʈ���� ������� �Ѱ�)


������, ������ �� �ݺ��ڴ� ��·�� ��� �ڵ�(handle, �ٸ� ��ü�� ���� �� �� �ְ� �ϴ� �Ű���).
� ��ü�� ���ο�ҿ� ���� �ڵ��� ��ȯ�ϰ� �����,
�������� �� ��ü�� ĸ��ȭ�� ���ʶ߸��� ������ ������ ���ۿ�.

�ܺ� ������ ���ܵ� ��� �Լ��� ����, �����͸� ��ȯ�ϴ� ��� �Լ��� ����� ���� ����� �Ѵ�!;

class Rectangle {
public:
	const Point& upperLeft() const { return pData->ulhc; }
	const Point& lowerRight() const { return pData->lrhc; }
};
��ȯ Ÿ�Կ� const ������ ���� �� ������, �� ���� ���� ��.

�б� ������ ������
Rectangle�� �����ϴ� Point�� �鿩�ٺ����� ���ڴ� ���� ó������ �˰� ������ �����̱� ������,
�ǵ����� ĸ��ȭ ��ȭ.

'��ȿ���� �ڵ�(dangling handle)'
	: �ڵ��� �ֱ�� ������ �� �ڵ��� ������ �� ���� ��ü�� �����Ͱ� ���� ��.

����;
class GUIObject {/*...*/ };
const Rectangle boundingBox(const GUIObject& obj);	//������ ��ȯ

GUIObject *pgo;
const Point *pUpperLeft = &(boundingBox(*pgo).upperLeft());	//pgo�� ����Ű�� GUIObect�� �簢 �׵θ� �������κ��� ���� ��� ������ ������ ����
=> ������ ������, �Լ��� ��ȯ ���� �ӽ� ��ü�� �Ҹ�Ǹ� �� �ȿ� �ִ� Point ��ü�鵵 ������.
=> pUpperLeft �����Ͱ� ����Ű�� ��ü�� ������

�̰͸��� ���� ����!
	� ��ü�� ���ο�ҿ� ���� �ڵ�(������, ������ ,�ݺ���)�� ��ȯ�ϴ� ���� �ǵ��� ������.
	ĸ��ȭ ������ ���̰�, ��� ��� �Լ��� ��ü�� ������� ������ ä�� ������ �� �ֵ��� �Ѵ�.
	��ȿ���� �ڵ��� ����� ��츦 �ּ�ȭ�� �� �ִ�.

(�����..)




�׸� 29: ���� �������� Ȯ���Ǵ� �׳� ����!

���� ������(exception safety)

����: GUI �޴�;		//..mutex�� ���� �������� �����ڿ��� ���� ���� ������ ���� �ִ� ����
class PrettyMenu {
public:
	void changeBackground(std::istream& imgSrc);
private:
	Mutex mutex;	//�� ��ü �ϳ��� ���� ���ؽ�
	Image *bgImage;		//������ ���׸�	
	int imageChanges;		//���׸��� �ٲ� Ƚ��
};
void PrettyMenu::changeBackground(std::istream& imgSrc) {
	lock(&mutex);	//���ؽ� ȹ�� (�׸� 14�� ����)
	delete bgImage;
	++imageChanges;
	bhImage = new Image(imgSrc);
	unlock(&mutex);	//���ؽ� ����
}
=> ���� ������ ��� �ȵ� ����.

���ܰ� �߻��� ��..
1. �ڿ��� ������ ������ �ʴ´�.
	new Image ǥ���Ŀ��� ���ܸ� ������ unlock �Լ��� ������� �ʾ� ���ؽ��� ��� ���� ����.
2. �ڷᱸ���� ���������� ���� ������� �ʴ´�.
	new Image �� ���ܸ� ������ bgImage�� ����Ű�� ��ü�� �̹� ������ ��.
	�� �׸� ������ �ʾҴµ� imageChanges �����߰�..;

1. �ڿ� ���� ����
void PrettyMenu::changeBackground(std::istream& imgSrc) {
	Lock ml(&mutex);		//�׸� 14���� ������. ���ؽ��� ��� ȹ���ϰ� �̰��� �ʿ� ������ ������ �ٷ� �������ִ� ��ü.
	delete bgImage;
	++imageChanges;
	bgImage = new Image(imgSrc);
}
Lock ���� �ڿ����� ���� Ŭ���� : �Լ��� �ڵ� ���̰� ª������.
�ڿ� ���� ���� �ذ�.

2. �ڷᱸ�� ���� ����
���� �������� ���� �Լ��� �� ���� ����(guarantee)

2.1.�⺻���� ����(basic guarantee)
	�Լ� ���� �� ���� �߻� ��, ���� �� ��� �͵� ��ȿ�� ���·� ����.
	Ŭ���� �Һ��Ӽ� ����.
	��, ����ڰ� ���� �����

2.2.������ ����(strong guarantee)
	���� �߻� �� ���α׷��� ���¸� ����� �������� �ʰڴ�.
	�̷� �Լ��� ȣ���ϴ� �� : ��������(atomic) ����.
	���� ���� ���� : ������ ���� > �⺻ ����.

2.3.���ܺҰ� ����(nothrow guarantee)
	���ܸ� ����� ������ �ʰڴ�.����� ������ ������ ������ �ϼ��϶�.
	int doSomething() throw();
	���� �߻� �� ����Ǵ� ó������ unexpected �Լ� ȣ�� �ʿ�.

�� 3���� ���� �� �ϳ��� �ݵ�� �����ؾ� ��.
���������� �⺻���� ���� or ������ ���� �� �ϳ�.;

class PrettyMenu {
	std::tr1::shared_ptr<Image> bgImage;
};
void PrettyMenu::changeBackground(stdd::istream& imgSrc) {
	Lock ml(&mutex);
	bgImage.reset(new Image(imgSrc));		//bgImage�� ���� �����͸� new Image ǥ������ ���� ����� �ٲ�ġ��
	++imageChanges;
}
���׸��� ����Ʈ �������� �տ��� �����ǰ� �ִ�.

'����-��-�¹ٲٱ�(copy-and-swap)' ����
	��ü�� �����ϰ� ������ �� ��ü�� �纻�� �ϳ� ����� �纻�� ����.
	���� ���� �� � ���ܰ� ���������� ���� ��ü�� �ٲ��� �ʴ� ��.
	���� �Ϸ� �� ������ ��ü�� ���� ��ü�� �¹ٲٴµ�, �� �۾��� '���ܸ� ������ �ʴ�' ���� ���ο��� ����.

��¥ ��ü�� ��� �����͸� ������ ����(implementation) ��ü�� �־�ΰ�,
�� ���� ��ü�� ����Ű�� �����͸� ��¥ ��ü�� ���� �ְ� �ϴ� ������ ����.;

struct PMImple {
	std::tr1::shared_ptr<Image> bgImage;
	int imageChanges;
};	//PMImple�� struct�� ����� ���� �ؿ��� Ȯ��
class PrettyMenu {
private:
	Mutex mutex;
	std::tr1::shared_ptr<PMImpl> pImpl;
};
void PrettyMenu::changeBackground(std::istream& imgSrc) {
	using std::swap;	//�׸� 25 ����
	Lock ml(&mutex);	//���ؽ� ��� �尡��
	std::tr1::shared_ptr<PMImpl>pNew(new PMImpl(*pImpl));	//��ü�� ������ �κ��� ����
	pNew->bgImage.reset(new Image(imgSrc));		//�纻 ����
	++pNew->imageChanges;
	swap(pImpl, pNew);		//�� �����ͷ� �ٲ� �־� ��¥�� ���׸� �ٲ�
}	//���ؽ� ����


�Լ��� �μ�ȿ��(side effect).
������ �����Ϳ� ���� �μ�ȿ���� �ִ� �Լ��� ������ ������ �ֱ� ��ٷӴ�.

������ ������ �ǿ뼺�� Ȯ���� �� �ٷ� ���.

�ڿ� ������ �ʿ��� �� �ڿ� ������ ��ü�� ����ϴ� �ͺ��� ���� (�׸� 13 ����)

�̰͸��� ���� ����!
1. ���� �������� ���� �Լ��� ���� �� ���ܰ� �߻��Ǵ��� �ڿ��� �����Ű�� ������
	�ڷᱸ���� ������ ä�� ������ ���� �ʽ��ϴ�.
	�̷� �Լ����� ������ �� �ִ� ���� ������ ������ �⺻���� ����, ������ ����, ���� ���� ������ �ֽ��ϴ�.

2. ������ ���� ������ ������ '����-��-�¹ٲٱ�' ����� �Ἥ ������ �� ������,
	��� �Լ��� ���� ������ ������ �ǿ����� ���� �ƴմϴ�.

3. � �Լ��� �����ϴ� ���� ������ ������ ������, �� �Լ��� ���������� ȣ���ϴ� �Լ�����
	�����ϴ� ���� ���� ������ ���� �ʽ��ϴ�.




�׸� 30: �ζ��� �Լ��� ���־˰��־� ������ ������ ����

�ζ��� �Լ� ����
	: ��ũ�κ��� �����ϰ� ���� ����, ������� ������ �ʿ� ����.
	: �����Ϸ��� �Լ� ������ ���� ���ƺ�(context-specific) ����ȭ�� �ɱ� ��������
����
	���� �ڵ��� ũ�Ⱑ Ŀ�� �� �ִ�. ������ �ɸ����� �� �� �ִ�. ����¡ Ƚ�� ����, ��ɾ� ĳ�� ���߷� ������...

��, ���� ���̰� ª�� �ζ��� �Լ� ��� �� ���� �ڵ��� ũ�⵵ �۾��� �� �ִ�.

inline�� �����Ϸ��� ��û�ϴ� ��.
�Ͻ��� ��û;
class Person {
public:
	int age() const { return theAge; }		//�Ͻ����� �ζ��� ��û: age�� Ŭ���� ���� ���ο��� ���ǵǾ���.
private:
	int theAge;
};

����� ��û
���� : ǥ�� ���̺귯���� max ���ø�(<algorithm>�� ����);
template<typename T>
inline const T& std::max(const T& a, const T& b) { return a < b ? b : a; }

�ζ��� �Լ��� ��ü������ ��� ���Ͽ� ��� �־��.
��κ��� ���� ȯ�濡�� �ζ����� ������ ���߿� �����ϱ� ����.
�� �Լ��� �������� �ٲ�ġ���Ϸ���, �����Ϸ��� �� �Լ��� � �������� �˰� �־��.
��κ��� c++ ���α׷����� �Լ� �ζ����� ������ Ÿ�ӿ� ����.

���ø� ����, ��ü������ ��� ���Ͽ�.
���ø��� ���Ǵ� �κп��� �ش� ���ø��� �ν��Ͻ��� ������� ��� ������� �����Ϸ��� �˾ƾ� �ϱ� ����.
(��� ���� ȯ���� �׷� �� �ƴ�����..)

inline �� '��û'�� ����
������ �Լ��� ���� �ζ��� Ȯ�� ��� ���� �ʴ´�.
ex. ����, ��� �Լ�, ���� �Լ�
	virtual : � �Լ��� ȣ������ �����ϴ� �۾��� ���� �߿� �Ѵ�.
	<-> inline : �Լ� ȣ�� ��ġ�� ȣ��� �Լ��� ���� �ִ� �۾��� ���α׷� ���� ���� �Ѵ�.
ex. �ζ��� �Լ��� �Լ� �����͸� ���� ȣ�� ��;
inline void f() { ... }
void(*pf)() = f;
f();		//ȣ���� �ζ��ε�~
pf();		//�ζ��� �ȵ�. �Լ� �����͸� ���� ȣ����.


�����ڿ� �Ҹ��ڴ� �ζ��� ���� ����
class Base {
public:
private:
	std::string bm1, bm2;		//Base Ŭ������ ���(bm)1, ���2
};
class Derived : public Base {
public:
	Derived() {}		//Derived�� �����ڰ� ����ִ�??
private:
	std::string dm1, dm2, dm2;		//Derived�� ���
};

� ����ȯ�濡���� �� �ڵ��� �����ڴ� ������ ���� ������ �� �ֵ�.
Derived::Derived() {
	Base::Base();
	try { dm1.std::string::string(); }
	catch (...) {
		Base::~Base();
		throw;
	}
	try { dm2.std::string::string(); }
	catch (...) {
		dm1.std::string::~string();	//���� �� �Ҹ�
		Base::~Base();	//�⺻ Ŭ���� �Ҹ�
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
�ζ����� ��������.

�ϴ� �ƹ��͵� �ζ������� ����, �ܼ��� �Լ��� �ζ��� ���.

�̰͸��� ���� ����!
1. �Լ� �ζ����� �۰�, ���� ȣ��Ǵ� �Լ��� ���ؼ��� �ϴ� ������.
	����� �� ���̺귯���� ���̳ʸ� ���׷��̵尡 ����������, 
	��ĩ ���� �� �ִ� �ڵ� ��Ǯ�� ������ �ּ�ȭ�Ǹ�,
	���α׷��� �ӷ��� �� ������ �� �ִ� ������ �ְ�� ������
2. �Լ� ���ø��� �밳 ��� ���Ͽ� ���ٴ� �Ϲ����� �κи� �����ؼ� �̵��� inline���� �����ϸ� �� �ʽ�




�׸� 31: ���� ������ ������ �������� �ִ�� ������!

;
class Person {
public:
	Person(const std::string& name, const Date& birthday, const Address& addr);
	std::string name() const;
	std::string birthDate() const;
	std::string address() const;
private:
	std::string theName;	//���� ���� ���λ��׵�
	Date theBirthDate;
	Address theAddress;
};

Ŭ���� �����ϴ� ������ ���� �밳 �Ʒ��� ����� �ڵ� �߰�;
#include <string>
#include "date.h"
#include <address.h>
�� �༮���� ��ĩ����
������ �������� ����.

���� ���λ��� �ٷ� ����� ? ;
namespace std {
	class string;	//���� ���� (Ʋ�� ��!)
}
class Date;		//���� ����
class Address;	//���� ����
class Person {
public:
	Person(const std::string& name, const Date& birthdayt, const Address& addr);
	std::string name() const;
	std::string birthDate() const;
	std::string address() const;
	//...
};
= > ���� 2����
string�� ��� Ŭ������ �ƴ϶� typedef���� ������ Ÿ�Ե��Ǿ�!
basic_string<char>�� typedef �� ��.
�׷��� string�� ���� ���� ������ ���� ����...;

int main() {
	int x;
	Person p(params);	//Ŭ���� ���ǵ� ������ ���� �����Ϸ��� ��ü �ϳ��� ũ�Ⱑ ������ �� �� ����.
}

�������̽��� �����ϴ� Ŭ���� / �������̽��� ������ ���� Ŭ������ ����� ����!;
#include <string>	//ǥ�� ���̺귯�� ������Ҵ� ���� ������ �ϸ� �� �ȴ�.
#include <memory>	//tr1::shared_ptr�� ���� ���
class PersonImpl;	//Person�� ���� Ŭ������ ���� ���� ����
class Date;			//Person Ŭ���� �ȿ��� ����ϴ� �͵鿡 ���� ���� ����
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
���� Ŭ����(tr1::shared_ptr)�� ���� ������
pimpl ���뱸(pointer to implementation)
pImpl == ������ �̸�

�������̽��� ������ �ѷ� ������ ����� '���Ǻο� ���� ������(dependencies on definitions)'��
'����ο� ���� ������(dependencies on declarations')�� �ٲپ� ���� �� �ִ�.
������ �������� �ּ�ȭ�ϴ� �ٽ� ����.
��� ������ ���� ���� �ǿ������� �ǹ̸� ���� �� ��ü����(self-sufficient) ���·�.
�� �� �Ǹ� �ٸ� ���Ͽ� �������� ����, ���Ǻΰ� �ƴ� ����ο� ���� �������� ������ �ϴ� ��.

����
1. ��ü ������ �� �����ͷ� ����� ��쿡�� ��ü�� ���� ���� �ʴ´�.
	� Ÿ�Կ� ���� ������ �� �����͸� ������ ���� �� Ÿ���� ����θ� �ʿ�.
	�ݸ� � Ÿ���� ��ü�� ������ ���� �� Ÿ���� ���ǰ� �غ�Ǿ� �־�� �Ѵ�.

2. �� �� ������ Ŭ���� ���� ��� Ŭ���� ���� �ִ��� �����ϵ��� �Ѵ�.
	� Ŭ������ ����ϴ� �Լ��� ������ ���� �� Ŭ������ ���Ǹ� �������� �ʾƵ� ��.
	������ �� Ŭ���� ��ü�� ������ �����ϰų� ��ȯ�ϴ��� Ŭ���� ���ǰ� �ʿ� ����.;
class Date;
Date today();
void clearAppointments(Date d);

Date�� �������� �ʰ� today�� �Լ��� ������ �� ����.
�Լ� ������ �Ǿ� �ִ� ��� ���� �ʿ� �� �δ��� ���� �ʰ�,
���� �Լ� ȣ���� �Ͼ�� ������� �ҽ� ���� �ʿ� ����.

3. ����ο� ���Ǻο� ���� ������ ��� ������ ����.;
#include "datefwd.h"	//Date Ŭ������ �����ϰ� �ִ�(�׷��� �������� �ʴ�) ��� ����
Date today();
void clearAppointments(Date d);


���ø� ����� ���ø� ���Ǹ� �и��� �� �ֵ��� �ϴ� ����� 'export' ��� Ű����� ����.
���� �� �� ���� Ű����.

pimpl ���뱸�� ����ϴ� Person ���� Ŭ������ ������ '�ڵ� Ŭ����' ��� �Ѵ�.;
#include "Person.h"		//Person Ŭ������ ���Ǹ� ����
#include "PersonImpl.h"		//PersonImpl Ŭ���� ���ǵ� ����. �̷��� �ؾ� ��� �Լ� ȣ�� ����
							//�� ���� ��� �Լ��� �ϴ��Ϸ� ������. �������̽��� ����.
Person::Person(const std::string& name, const Date& birthday, const Address& addr) 
	: pImpl(new PersonImpl(name, birthday, addr) {}
std::string Person::name() const {
	return pImpl->name();
}
�����ڿ� new ���.


�ڵ� Ŭ���� ��� ��� �ٸ� ����� Person�� Ư�� ������ �߻� �⺻ Ŭ����,
�̸� �� '�������̽� Ŭ����' �� ����� ���.

� ����� ��Ÿ���� �������̽��� �߻� �⺻ Ŭ������ ���� ������ ����,
�� Ŭ�����κ��� �Ļ� Ŭ������ ���� �� �ְ� �ϴ� ��.
�Ļ��� ����.������ �����, �����ڳ� ���� �Ҹ��ڵ� ������, �������̽��� �����ϴ� ���� ���� �Լ��� ����ִ�.;

class Person {
public:
	virtual ~Person();
	virtual std::string name() const = 0;
	virtual std::string birthDate() const = 0;
	virtual std::string address() const = 0;
};
Person�� ���� ������or�����ڷ� ���α׷���
�������̽� Ŭ������ ����ϱ� ���ؼ��� ��ü ���� ������ �ּ��� �ϳ��� �ʿ�.
�Ļ� Ŭ������ ������ ������ ����ϴ� � �Լ��� ����� ���� �̰��� ȣ��.

�̷� �Լ��� ������ '���丮 �Լ�'(�׸� 13), or ���� ������(virtual constructor).
�־��� �������̽� Ŭ������ �������̽��� �����ϴ� ��ü�� �������� �Ҵ��� ��, �� ��ü�� ����Ʈ �����͸� ��ȯ.
�Լ��� �������̽� Ŭ���� ���ο� ���� ����� ����Ǵ� ��찡 ����.;

class Person {
public:
	static std::tr1::shared_ptr<Person>create(const std::string& name, const Date& birthday, const Address& addr);
	//�־��� �Ű������� �ʱ�ȭ�Ǵ� Person ��ü�� ���� �����ϰ�,
	//�װͿ� ���� ����� ������ ��ȯ.
};
����� ���� �ڵ�;
std::string name;
Date dateOfBirth;
Address address;
//Person �������̽��� �����ϴ� ��ü �� ���� ����.
std::tr1::shared_ptr<Person>pp(Person::create(name, dateOfBirth, address));
std::cout << pp->name() << " was born on "
	<< pp->birthDate() << " and now lives at " << pp->address();
//������ ������ ��ü�� pp�� ��ȿ������ ��� �� �ڵ����� ������(�׸� 13 ����).


�������̽� Ŭ������ �������̽��� �����ϴ� ��ü Ŭ����(concrete class) ����
������ ����Ǵ� ������(��ü Ŭ������ ������)�� ȣ��Ǿ�� �Ѵ�.
���� �������� �����θ� ���� �ִ� ���� �ȿ��� �̷������.

Person Ŭ�����κ��� �Ļ��� RealPerson �̶� ��ü Ŭ������ �ִٸ�,
�� Ŭ������ �ڽ��� ��ӹ��� ���� ���� �Լ��� ���� �����θ� �����ϴ� ������ ��������� ��.;

class RealPerson : public Person {
public:
	RealPerson(const std::string& name, const Date& birthday, const Address& addr)
		: theName(name), theBirthDate(birthday), theAddress(addr) {}
	virtual ~RealPerson() {}
	std::string name() const;		//��� �Լ��� ���� ������ ����
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
�������̽� Ŭ����(Person)�κ��� �������̽� ���� �����ް� ���� �Ŀ�, �� �������̽��� ��� �ִ� ���� �Լ� ����.

(�����..)


�ڵ� Ŭ���� ����
	�� �� ������ ������ �䱸�Ǵ� ����ȭ ������ �� �ܰ� �� ����
	��ü �ϳ����� �����ϴ� �� �ʿ��� �޸� ũ�⿡ ������ �������� ũ�Ⱑ ������
	������ �����Ͱ� ���� �Ҵ�� ������ ��ü�� ����Ű���� ��𼱰� �� ������ �������� �ʱ�ȭ�� �Ͼ�� �ϸ�, 
		���� ������� �� �޸� �� ���� ���ɼ�

�������̽� Ŭ���� ����
	ȣ��Ǵ� �Լ��� ���� ���� �Լ� - �Լ� ȣ�� �� ���� ���̺� ������ ������ ��� �Ҹ�.
	�������̽� Ŭ�������� �Ļ��� ��ü�� �˴� ���� ���̺� �����͸� ����� ��.
	-> ��ü �ϳ� �����ϴ� �� �ʿ��� �޸� ũ�⸦ �ø�

���� ����
	�ζ��� �Լ��� ������ ����� ����� �����.
	�ζ��� �ǰ� �Ϸ��� �Լ� ������ �밳 ��� ���Ͽ� �ξ�� �ϴµ�,
	�ڵ� Ŭ������ �������̽� Ŭ������ �Լ� ������ ���� �����θ� ������� �����κ��� �����ϴ� �� ����

�̰͸��� ���� ����!
1. ������ �������� �ּ�ȭ�ϴ� �۾��� ����� �Ǵ� ���� �⺻���� ���̵��� '����' ��ſ� '����'�� �����ϰ� ����.
	�� ���̵� ����� �� ���� ���� ����� �ڵ� Ŭ������ �������̽� Ŭ����.
2. ���̺귯�� ����� �� ��ü�� ��� ���� ���߾�� �ϸ� ����θ� ���� �ִ� ���¿��� �Ѵ�.
	�� ��Ģ�� ���ø��� ���̰ų� ������ �ʰų� �����ϰ� ����.;




���, �׸��� ��ü ���� ����
OOP ���� ��� �ϳ��ϳ��� �ڵ忡 ������ �� ������ ǥ���ؾ� ��Ȯ�ϰ� ���� ���ΰ�?
	ex. public ����� �ݵ�� 'is-a' ���踦 �ǹ�
	ex. ���� �Լ��� �ǹ̴� "�������̽��� ��ӵǾ�� �Ѵ�."�� �ݸ�, �񰡻� �Լ��� �ǹ̴� "�������̽��� ������ �� �� ��ӵǾ�� �Ѵ�."

�׸� 32: public ��� ������ �ݵ�� "is-a (...�� ...�� �����̴�)" �� �������� ������!

Derived Ÿ������ ������� ��� ��ü�� ���� Base Ÿ���� ��ü������, '�� �ݴ�� ���� �ʴ´�.'

B�� D���� �� �Ϲ����� ������ ��Ÿ����,
D�� B���� �� Ư���� ������ ��Ÿ����.
B Ÿ���� ��ü�� ���� �� �ִ� ������ D Ÿ���� ��ü�� ���������� ���� �� �ִٰ� ����(assert)�ϴ� ��.
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
study(p);	//����! p�� Student�� �ƴ�

class Bird {
public:
	virtual void fly();
};
class FlyingBird : public Bird {
public:
	virtual void fly();
};
class Penguin : public Bird {};
= > ��� ���� ���� ����.
��, ����Ʈ����� ���� �θ��� �������� ������ �ְ� ���� ���� �� ���� ���� ���,
Bird�� Penguin�� �־ �� ��.

��Ÿ�� ���� ����;
void error(const std::string& msg);
class Penguin : public Bird {
public:
	virtual void fly() { error("Attempt to make a penguin fly!"); }
};
= > ����� �� �� ���ٰ� �ƴ�, '����� �� �� �ִ�. but ����� ������ ������ �ϸ� ������ ����.'
��Ÿ�� ������ �Ǻ�
fly �Լ��� ���ʿ� ������� ������ ������ ����.
��ȿ���� ���� �ڵ带 ������ �ܰ迡�� �����ִ� �������̽��� ���� �������̽�!


����: ��� : ���簢���� ���簢���� ���ԵǴ� ���?;
class Rectangle {
public:
	virtual void setHeight(int newHeight);
	virtual void setWidth(int newWidth);
	virtual int height() const;	//���� �� ��ȯ �Լ�
	virtual int width() const;
};
void makeBigger(Rectangle& r) {	//r�� ���̸� �ø��� �Լ�
	int oldHeight = r.height();
	r.setWidth(r.width() + 10);	//r�� ���� ���̿� 10 ���ϱ�
	assert(r.height() == oldHeight);	//r�� ���α��̰� ������ �ʴ´ٴ� ���ǿ� ������(assert) �ɱ�
}
class Square: public Rectangle {};
Square s;
assert(s.width() == s.height());	//�� �������� ��� ���簢���� ���� ���̾��
makeBigger(s);	//��ӵ� ���̹Ƿ�, s�� Rectangle�� ����. ��, s�� ���̸� �ø� �� �ֵ�.
assert(s.width() == s.height());	//�� �������� ��� ���簢���� ���� ���̾��.

makeBigger �Լ��� �����ϴ� ���� s �� ��ü����, s�� �纻�� �ƴ�.

public ���: �⺻ Ŭ���� ��ü�� ���� '��� �͵�'�� �Ļ� Ŭ���� ��ü���� �״�� ����ȴٰ� �����ϴ� ���.
���簢��: ����, ���� ���̰� ���ƾ� �Ѵ�.
���簢��: ���� ���̰� ���� ���̿� ������� �ٲ� �� �ִ�.
����ġ.

Ŭ���� ���� ���� "has-a(...��...�� ����)"�� "is-implemented-in-terms-of(...��...�� �Ἥ ������)"��
�׸� 38, 39 ����.

�̰͸��� ���� ����!
	public ����� �ǹ̴� "is-a(...��...�� ����)". 
	�⺻ Ŭ������ ����Ǵ� ��� �͵��� �Ļ� Ŭ���� �״�� ����Ǿ�� ��.
	�ֳ��ϸ� ��� �Ļ� Ŭ���� ��ü�� �⺻ Ŭ���� ��ü�� �����̱� �����̴�.


�׸� 33: ��ӵ� �̸��� ����� ���� ������!

�̸��� ��ȿ����;
int x;
void someFunc() {
	double x;
	std::cin >> x;
}
���� ��ȿ��������.
x��� �̸��� double�� x��� �̸��� int�� ������ ��.;

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

Base�� ��ȿ����: x(������ ���), �Լ� 3��, Derived�� ��ȿ����
Derived�� ��ȿ����: �Լ� 2��

�����Ϸ��� Ž��
���� ��ȿ���� -> Ŭ���� �� ��ȿ���� -> Base Ŭ������ ��ȿ���� -> ���� ���޹��� ��

�����ε� �Ẹ�� (�񰡻� �Լ��� ��ӵ� �Լ��� �����ε��ϴ� ���� ���� ���� ������ ���÷�);
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
Base�� ��ȿ���� : x(������ ���), mf1() 2��, mf2 1��, mf3(2��), Derived�� ��ȿ����
Derived�� ��ȿ���� : �Լ� 3��

= > �̸� Ž�� �������� Base::mf1�� Base::mf3�� Derived�� ����� ���� �ƴϰ� �ȴ�.;
�����Լ��� �ƴϵ�... Ÿ���� �ٸ��� �ƴϵ�...

Derived d;
int x;
d.mf1();
d.mf1(x);	//����. Derived::mf1�� Base::mf1�� ������.
d.mf2();
d.mf3();
d.mf3(x);	//����. Derived::mf3�� Base::mf3�� ������.

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
	using Base::mf1;	//Base�� �ִ� �͵� �� mf1�� mf3�� �̸����� ���� �͵��� Derived�� ��ȿ�������� �� �� �ֵ��� ����.
	using Base::mf3;

	virtual void mf1();
	void mf3();
	void mf4();
};
Base�� ��ȿ���� : x(������ ���), mf1() 2��, mf2 1��, mf3(2��), Derived�� ��ȿ����
Derived�� ��ȿ���� : mf1() 1��, mf3() 2��, mf4() 1��

��ӵ�;
Derived d;
int x;
d.mf1();
d.mf1(x);	//����. Base::mf1 ȣ��
d.mf2();
d.mf3();
d.mf3(x);	//����. Base::mf3 ȣ��

�⺻ Ŭ������ �����ε�� �Լ��� �� Ŭ������ ����ְ�, �� �Լ��� �� �� ���� ������(�������̵�) �ϰ� �ʹٸ�,
�� �̸��� ���� using ����.


Derived�� Base�κ��� private ����� ��, ����Ϸ��� mf1�Լ��� �Ű����� ���� ���� �ϳ��ۿ� ���� ��,
	using �����ϸ� �̸��� �ش�Ǵ� �͵��� ��� �Ļ� Ŭ������ ������ ����.
	�̶� �ٸ� ��� �ʿ�.

���� �Լ�(forwarding function) ���;
class Base {
public:
	virtual void mf1() = 0;
	virtual void mf1(int);	//���� ���� ����
};
class Derived : private Base {	//private ����� ��
public:
	virtual void mf1() {	//���� �Լ�. �Ͻ������� �ζ��� �Լ�
		Base::mf1();
	}
};
Derived d;
int x;
d.mf1();	//����. Derived::mf1(�Ű��������¹���)�� ȣ��.
d.mf1(x);	//����. Base::mf1�� ������ ����.

�׸� 43���� to be continued...

�̰͸��� ���� ����!
1. �Ļ� Ŭ������ �̸��� �⺻ Ŭ������ �̸��� �����ϴ�.
	public ��ӿ����� �̷� �̸� ���� ������ �ٶ������� �ʽ��ϴ�.
2. ������ �̸��� �ٽ� �� �� �ְ� �ϴ� �������, using ���� Ȥ�� ���� �Լ��� �� �� �ִ�.




�׸� 34: �������̽� ��Ӱ� ���� ����� ���̸� ����� �ľ��ϰ� ��������

(public) ��� ����: �Լ� �������̽��� ��� / ������ ���
���̴� "���� ������ �ݰ����ϴ�"���� �̾߱��� 
�Լ� ����(function declaration) �� �Լ� ����(function definition)�� ���̿� ���� ���� �Ѵ�.;

class Shape {
public:
	virtual void draw() const = 0;
	virtual void error(const std::string& msg);
	int objectID() const;
};
class Rectangle: public Shape {...};
class Ellipse: public Shape {...};

Shape�� �߻� Ŭ����.
���� ���� �Լ��� draw
Shape Ŭ������ �ν��Ͻ��� ����� �ȵ�.
�Ļ� Ŭ������ �ν��Ͻ�ȭ ����.

��� �Լ� �������̽��� �׻� ��ӵǰ� �Ǿ� �ֱ� ������,
�⺻ Ŭ������ �ش��ϴ� �͵��� ��� �Ļ� Ŭ�������� �ش�Ǿ�� ��.

class Shape {
public:
	virtual void draw() const = 0;
};

���� ���� �Լ� Ư¡
1. � ���� ���� �Լ��� �������� ��ü Ŭ������ �ش� ���� ���� �Լ��� �ٽ� �����ؾ� �Ѵ�.
2. ���� ���� �Լ��� ���������� �߻� Ŭ���� �ȿ��� ���Ǹ� ���� �ʴ´�.

���� ���� �Լ��� �����ϴ� ������ �Ļ� Ŭ�������� �Լ��� �������̽����� �����ִ� ��.
'draw �Լ��� �������� ���� �����ϵ��� �Ͻ�. �� ��� �������� ���� ����.'

���� ���� �Լ����� ���Ǹ� ������ �� ����.
��, Ŭ���� �̸��� �����ڷ� �ٿ� �־�� �Ѵ�.;
Shape *ps = new Shape;	//����!! Shape�� �߻� Ŭ����.

Shape *ps1 = new Rectangle;
ps1->draw();	//Rectangle::draw ȣ��

Shape *ps2 = new Ellipse;
ps2->draw();	//Ellipse::draw ȣ��

ps1->Shape::draw();	//Shape::draw ȣ��
ps2->Shape::draw();	//Shape::draw ȣ��


�ܼ�(�����) ���� �Լ�.
�ܼ� ���� �Լ��� �����ϴ� ����: �Ļ� Ŭ������ �Ͽ��� �Լ��� �������̽��Ӹ� �ƴ϶�
	�� �Լ��� �⺻ ������ �����ް� ����.;
class Shape {
public:
	virtual void error(const std::string& msg);
};
'���� �Լ��� �������� �����Ͻ�. ���� ���� ���� ������ �⺻ ���� ����'

�ٸ� �ܼ� ���� �Լ����� �Լ� �������̽�, �⺻ ������ �Ѳ����� �����ϴ� �� ������ �� ����.
����;
class Airport {/*...*/};
class Airplane {
public:
	virtual void fly(const Airport& destination);
};
void Airplane::fly(const Airport& destination) {
	//�־��� �������� ����⸦ ���� ������ �⺻ ���� ������ ���� �ڵ�
}
class ModelA: public Airplane {...};
class ModelB: public Airplane {...};

Airplane::fly�� �����Լ�.
�� ���¿��� ���ο� �� �߰�;
class ModelC : public Airplane {
	//�𸣰� fly �Լ��� ������� ������ ����
};
Airport PDX(/*...*/);
Airplane *pa = new ModelC;
pa->fly(PDX);	//Airplane::fly �Լ��� ȣ���!
�⺻ ������ ���Ѵٰ� ��������� ������ �ʾҴµ��� �� ������ �����޴� �� �ƹ��� �ɸ����� ���� ����.

������
���� �Լ��� �������̽��� �� ���� �Լ��� �⺻ ������ �մ� ���� ���踦 ���� ������ ��.;
class Airplane {
public:
	virtual void fly(const Airport& destination) = 0;
protected:
	void defaultFly(const Airport& destination);
};
void Airplane::defaultFly(const Airport& destination) {
	//�־��� �������� ����⸦ ���� ������ �⺻ ���� ������ ���� �ڵ�
}
Ariplane::fly �Լ��� ���� ���� �Լ��� �ٲ�.
���� ������ defaultFly��� �̸��� ������ �Լ��� �ŵ쳲.
defaultFly �Լ��� �ζ��� ȣ��.;
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
= > �⺻ ������ �쿬���� �������� ���ɼ��� ������;
class ModelC : public Airplane {
public:
	virtual void fly(const Airport& destination);
};
void ModelC::fly(const Airport& destination) {
	//�־��� �������� ModelC ����⸦ ���� ������ �ڵ�
}

Airplane::defaultFly �Լ��� protected ���.
Airplane �� �� Ŭ������ �Ļ� Ŭ������ ���������� ����ϴ� ���� ���λ����̴�.
����⸦ ����ϴ� ����ڴ� '����Ⱑ �� �� �ִ�'��� ���� �˸� �� ��,
'���� ������ ��� �����Ǵ°�'�� �Ű� ���� ���ƾ� �մϴ�.

Airplane::defaultFly �Լ��� ���� �񰡻� �Լ�.
�Ļ� Ŭ���� �ʿ��� �� �Լ��� �������ؼ� �ȵ�. (�׸� 36������ �˷���);


class Shape {
public:
	int objectID() const;
};
��� �Լ��� �񰡻� �Լ��� �Ǿ� �ִٴ� ��: �Ļ� Ŭ�������� �ٸ� �ൿ�� �Ͼ�� ���� �� ����.
�񰡻� ��� �Լ��� 'Ŭ���� �Ļ��� ������� ������ �ʴ� ����'�� �����ϴ� �� ����.

�񰡻� �Լ��� �����ϴ� ������ �Ļ� Ŭ������ �Լ� '�������̽��� ���Ҿ� �� �Լ��� �ʼ����� ����(mandatory implementation)'
�� �����ް� �ϴ� ��.

Shape::objectID�� ������
"Shape �� �̰Ϳ��� �Ļ��� ��� ��ü�� ��ü�� �ĺ��ڸ� ���� �ִ� �Լ��� ���� �ǰ���"
"��ü �ĺ��ڸ� ����ϴ� ����� �׻� �Ȱ��ڱ�. ���� ��� ����� Shape::objectID�� ���ǿ��� �����ǰ�,"
"�Ļ� Ŭ������ �̰��� �ٲ� �� ���ڴ°�."
�񰡻� �Լ��� Ŭ���� �Ļ��� ������� �Һ�����(invariant).
�Ͽ�, �Ļ� Ŭ�������� ������ �� �� ����.


Ŭ���� �Ǽ� 2����
�Ǽ� 1. ��� ��� �Լ��� �񰡻� �Լ��� �����ϴ� ��.
�Ļ� Ŭ������ ������� �⺻ Ŭ������ ������ Ư���ϰ� ���� ���� ������ ��������.
Ư�� �񰡻� �Ҹ��ڰ� �����Ÿ� (�׸� 7 ����)
�⺻ Ŭ������ ���̴� Ŭ������ �����ȱ� ���� �Լ�

cf) ���� �Լ��� ��� ����? 80-20 ��Ģ. (�׸� 30..)
��ü ���� �ð��� 80%�� �Ҹ�Ǵ� �κ��� ��ü �ڵ��� 20%�ۿ� ���� �ʴ´ٴ� ��Ģ.
�Լ� ȣ�� �� 80%�� ���� �Լ��� �δ��� ���α׷��� ��ü ���� ���ɿ��� �ս� ���� ����

�Ǽ� 2. ��� ��� �Լ��� ���� �Լ��� ����.
���� �׸� 31�� �������̽� Ŭ���� ���� �Һ������� ���� �־�� �Ѵٸ�, ���� �� ����.

�̰͸��� ���� ����!
1. �������̽� ����� ���� ��Ӱ� �ٸ���.
	public ��ӿ���, �Ļ� Ŭ������ �׻� �⺻ Ŭ������ �������̽��� ��� �����޴´�.
2. ���� ���� �Լ��� �������̽� ��Ӹ��� ����Ѵ�.
3. �ܼ�(�����) ���� �Լ��� �������̽� ��Ӱ� ���Ҿ� �⺻ ������ ��ӵ� �����ϵ��� �����Ѵ�.
4. �񰡻� �Լ��� �������̽� ��Ӱ� ���Ҿ� �ʼ� ������ ��ӵ� ���ϵ��� �����Ѵ�.


'���� ���: ��� �Լ��� ȣ���� ���� ������, ������ ��� �Լ��� ������ �ʴ� ���'
'�������̽� ���: ��ӹ��� ��ü���� �Լ��� �ܺ�ȣ���� �� ����.'




�׸� 35: ���� �Լ� ��� �� �͵鵵 ������ �δ� �ڼ��� �ýö����� �淯 ����

����
���ӿ��� ü���� ��� �Լ��� �����ϱ�� ����
ü���� ��� ����ϴ����� ĳ���͸��� �ٸ� ���� ���ϹǷ�, ���� �Լ��� �����غ���.;
class GameCharacter {
public:
	virtual int healthValue() const;
};
���� ���� �Լ��� �ƴ� ������ ����, ü��ġ�� ����ϴ� �⺻ �˰����� �����ȴٴ� ���� �� (�׸� 34 ����)
'���� �Լ��� �������� �����Ͻ�. ���� ���� ���� ������ �⺻ ���� ����'

���� �Լ� �����: "���� �Լ��� �ݵ�� private ����� �ξ�� �Ѵ�."

class GameCharacter {
public:
	int healthValue() const {	//�Ļ� Ŭ������ ���� �� �Լ��� ������ �� �� �����ϴ�.
		//...	//���� ����
		int retVal = doHealthValue();	//���� ���� ����
		//...	//���� ����
		return retVal;
	}
private:
	virtual int doHealthValue() const {	//�Ļ� Ŭ������ �� �Լ��� �������� �� �ֽ��ϴ�.
		//...
	}
};
public �񰡻� ��� �Լ��� ���� private ���� �Լ��� ���������� ȣ���ϰ� ����� ���
'�񰡻� �Լ� �������̽�(non-virtual interface: NVI) ���뱸'
���ø� �޼���� �Ҹ��� ������ ������ ����
�� ���뱸�� ���̴� �񰡻� �Լ�(ex. healthValue)�� ���� �Լ��� ����(wrapper)��� �θ���.

NVI ���뱸������ �Ļ� Ŭ������ ���� �Լ� �����Ǹ� ���.
��ӹ��� private ���� �Լ��� �Ļ� Ŭ������ �������� �� �ִٴ� ��Ģ


'�Լ� �����ͷ� ������ ���� ����'
����: �� ĳ������ �����ڿ� ü��ġ ���� �Լ��� �����͸� �ѱ��, �� �Լ��� ȣ���ؼ� ���� ��� ����;
class GameCharacter;	//���� ����
int defaultHealthCalc(const GameCharacter& gc);		//ü��ġ ��꿡 ���� �⺻ �˰��� ����
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
����(Strategy) ������ �ܼ��� ���� ��
�Լ� ������ ����
1. ���� ĳ���� Ÿ�����κ��� ������� ��ü(�ν��Ͻ�)�鵵 ü��ġ �Լ��� ���� �ٸ��� ���� �� ����.;
class EvilBadGuy : public GameCharacter {
public:
	explicit EvilBadGuy(HealthCalcFunc hcf = defaultHealthCalc)
		: GameCharacter(hcf) {}
};
int loseHealthQuickly(const GameCharacter&);	//�ٸ� ���� ������ ������ ü��ġ ��� �Լ���
int loseHealthSlowly(const GameCharacter&);
EvilBadGuy ebg1(loseHealthQuickly);		//���� Ÿ���ε��� ü��ġ ��ȭ�� �ٸ��� ������ ĳ���͵�
EvilBadGuy ebg2(loseHealthSlowly);

2. ������ ����Ǵ� ���߿� Ư�� ĳ���Ϳ� ���� ü��ġ ��� �Լ��� �ٲ� �� ����.



'tr1::function���� ������ ���� ����'

tr1::function �迭�� ��ü�� �Լ�ȣ�⼺ ��ü(callable entity)(�Լ� ������, �Լ� ��ü or ��� �Լ� ������)�� ���� �� ����.

class GameCharacter;	//���� ����
int defaultHealthCalc(const GameCharacter& gc);		//ü��ġ ��꿡 ���� �⺻ �˰��� ����
class GameCharacter {
public:
	//HealthCalcFunc�� �Լ�ȣ�⼺ ��ü�μ�, GameCharacter�� ȣȯ�Ǵ� � ���̵� �Ѱܹ޾Ƽ� ȣ��� �� ������,
	//int�� ȣȯ�Ǵ� ��� Ÿ���� ��ü�� ��ȯ�մϴ�.
	typedef std::tr1::function<int(const GameCharacter&)>HealthCalcFunc;
	explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc) : healthFunc(hcf) {}
	int healthValue() const {
		return healthFunc(*this);
	}
private:
	HealthCalcFunc healthFunc;
};
=> HealthCalcFunc�� tr1::function ���ø��� �ν��Ͻ�ȭ �� �Ϳ� ���� typedef Ÿ��.;

std::tr1::function<int(const GameCharacter&)>
const GameCharacter�� ���� �����ڸ� �ް� int�� ��ȯ�ϴ� �Լ�.


tr1::function ��ü, ���� �Ϲ�ȭ�� �Լ� �����͸� ���� �� ��.
���� �ڵ忡�� ����.;

short calcHealth(const GameCharacter&);	//ü��ġ ��� �Լ�. ��ȯ Ÿ���� int�� �ƴ� �κп� �ָ�

struct HealthCalculator {	//ü��ġ ���� �Լ� ��ü�� ����� ���� Ŭ����
	int operator()(const GameCharacter&) const {/*...*/};
};
class GameLevel {
public:
	float health(const GameCharacter) const;	//ü��ġ ��꿡 ���� ��� �Լ�. ��ȯ Ÿ���� int�� �ƴ� �κп� �ָ�
};
class EvilBadGuy : public GameCharacter { };	//������ �װͰ� ����.
class EyeCandyCharacter : public GameCharacter { };	//�����ڴ� ���� �Ͱ� �Ȱ��ٰ� ����

//main
EvilBadGuy ebg1(calcHealth);	//ü��ġ ����� ���� �Լ��� ����ϴ� ĳ����
EyeCandyCharacter eccl(HealthCalcCulator());
GameLevel currentLevel;
EvilBadGuy ebg2(std::tr1::bind(&GameLevel::health, currentLevel, _1));	//ü��ġ ����� ���� ��� �Լ��� ����ϴ� ĳ����.

�� ���ǹ������� ebg2�� ü��ġ�� ����ϱ� ���� GameLevel Ŭ������ health ��� �Լ��� ��� �Ѵٰ� ��.
�� �� ����..
(�����..)

_[����] ������ ��ū�� tr1::bind�� ���� �Լ��� ȣ���� �� ��ü�� ���� �Ű�����(free parameter) ����Ʈ�� ���� �ڸ�ä����.


"��������" ���� ����

ü��ġ ��� �Լ��� ��Ÿ���� Ŭ���� ������ ���� �����,
ü��ġ ��� �Լ��� �� Ŭ���� ������ ���� ��� �Լ���.;

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
ǥ������ ���� ���� ���� ����� ģ���� ��� ���� ����.
������ ü��ġ ��� �˰����� ����/���� ����


���
1. �񰡻� �������̽� ���뱸(NVI ���뱸) ���
	�������� ���� ���� �Լ��� �񰡻� public ��� �Լ��� ���μ� ȣ���ϴ�, ���ø� �޼��� ������ �� ����.

2. ���� �Լ��� �Լ� ������ ������ ����� ��ü
	���� ������ �ٽɸ� ������

3. ���� �Լ��� tr1::function ������ ����� ��ü�Ͽ�,
	ȣȯ�Ǵ� �ñ״�ó�� ���� �Լ�ȣ�⼺ ��ü�� ����� �� �ֵ���: ���� ���� ������ �� ����.

4. ���� Ŭ���� ���뿡 ���� �ִ� ���� �Լ��� �ٸ� �� ���뿡 ���� �ִ� ���� �Լ��� ��ü
	: ���� ������ �������� ���� ����.


�̰͸��� ���� ����!
1. ���� �Լ� ��ſ� �� �� �ִ� ������� NVI ���뱸 �� ���� ������ �� �� �ִ�.
	�� �� NVI ���뱸�� �� ��ü�� ���ø� �޽õ� ������ �� ��.

2. ��ü�� �ʿ��� ����� ��� �Լ��κ��� Ŭ���� �ܺ��� ���� �Լ��� �ű��,
	�� ���� �Լ��� �� Ŭ������ public ����� �ƴ� �͵��� ������ �� ���ٴ� ����

3. tr1::function ��ü�� �Ϲ�ȭ�� �Լ� ������ó�� ����.
	�� ��ü�� �־��� ��� �ñ״�ó�� ȣȯ�Ǵ� ��� �Լ�ȣ�⼺ ��ü�� �����Ѵ�.




�׸� 36: ��ӹ��� �񰡻� �Լ��� �Ļ� Ŭ�������� �������ϴ� ���� ���� �ݹ�!

����;
class B {
public:
	void mf();
};
class D: public B {/*...*/ };

D x;
B *pB = &x;
pB->mf();	//�� �ڵ尡
D *pD = &x;
pD->mf();	//�� �ڵ�ó�� �������� �ʴ´�.
=> �ٸ� ���� �ִ�!

mf�� �񰡻� �Լ�, DŬ������ ��ü������ mf �Լ��� �� ������ ��.;
class D : public B {
public:
	void mf();	//B::mf�� ��������
};
pB->mf();	//B::mf�� ȣ��
pD->mf();	//D::mf�� ȣ��


cf)���ε�: ���α׷� �ҽ��� ���� ���� ���� ���, �̸�, �ĺ��ڵ鿡 ���� �� Ȥ�� �Ӽ��� Ȯ���ϴ� ����.
�� ������ ���� �߿� �̷������ ���� ���ε�
���� �߿� �̷������ ���� ���ε�.
c++ ���� �Լ��� ���ε��� ���������� ���� ���ε����� �Ǿ� ������,
���������δ� ��Ÿ�� ������ ���̱� ���� ���� ���ε��� ���� �ִ�.
��, ������ �߿� �ƿ� ���� �Լ� ���̺��� �Ļ� Ŭ������ �°� �ٲ����ν�, �Ѻ��⿡ �Ļ� Ŭ���� Ÿ�Կ��� �������̵��� ���� �Լ��� ȣ���ϴ� ��ó�� ����.


B::mf �� D::mf ���� �񰡻� �Լ��� ���� ���ε�(static binding)���� ����.

�ݸ� ���� �Լ��� ���� ���ε�.��¥�� ����Ű�� ��� Ÿ���� �Լ��� ȣ��.

B ��ü�� �ش�Ǵ� ��� �͵��� D ��ü�� �״�� ����.
B���� �Ļ��� Ŭ������ mf �Լ��� �������̽��� ������ ��� �����޴´�.
mf�� BŬ�������� �񰡻� ��� �Լ��̱� ����.

�� ��Ȳ���� B�� mf ������ ����ؾ� �Ѵٸ�, '��� D�� B�� ����'�̶� ������ ������ �ȴ�!
'mf�� Ŭ���� �Ļ��� ������� B�� ���� �Һ������� ��Ÿ����.'�� ���� ���� ����.
�̶� ���� �Լ��� ����� ��.

�׸� 7���� �������� �ο��� �⺻ Ŭ������ �Ҹ��ڸ� �ݤ���� ���� �Լ��� ������ �ϴ� �����̱⵵ �ϴ�!

�̰͸��� ���� ����!

��ӹ��� �񰡻� �Լ��� �������ϴ� ���� ����� ���� ���ô�!




�׸� 37: � �Լ��� ���ؼ��� ��ӹ��� �⺻ �Ű����� ���� ����� ���������� ����!

���� �Լ��� �������� ���ε�, �⺻ �Ű����� ���� �������� ���ε�.
���� ���ε� == ���� ���ε�(early binding)
���� ���ε� == ���� ���ε�(late binding)

��ü�� ���� Ÿ��(static type)�� �ҽ� �ȿ� ������ ���� �� ��ü�� ���� Ÿ��.;

//������ ������ ��Ÿ���� Ŭ����
class Shape {
public:
	enum ShapeColor { Red, Green, Blue };

	//��� ������ �ڱ� �ڽ��� �׸��� �Լ��� �����ؾ�.
	virtual void draw(ShapeColor color = Red) const = 0;
};
class Rectangel : public Shape {
public:
	//�⺻ �Ű����� ���� �޶��� �κ��� ��ġ�� ������. ū�ϳ���!
	virtual void draw(ShapeColor color = Green) const;
};
class Circle : public Shape {
public:
	virtual void draw(ShapeColor color) const;
};

������ ��Ÿ������;
Shape *ps;
Shape *pc = new Circle;
Shape *pr = new Rectangle;

��� ���� Ÿ��(static type) == Shape *

��ü�� ��� ������ ���̳ĸ� ����Ű�� Ÿ��
���� Ÿ��(dynamic type)
pc => Circle*
pr => Rectangle*

���α׷� ������ ���Թ��� �ٲ� �� ����
ps = pc;	//ps=>Circle*
ps = pr;	//ps=>Rectangle*

�����Լ�;
pc->draw(Shape::Red);	//Circle::draw(Shape::Red)�� ȣ��
pr->draw(Shape::Red);	//Rectangle::draw(Shape::Red)�� ȣ��

�⺻ �Ű����� ���� ������ ���� �Լ���? ;
pr->draw()	//Rectangle::draw(Shape::Red)�� ȣ���ع�����!!!!!
���� Ÿ���� Shape*�̱� ����.;

class Shape {
public:
	enum ShapeColor { Red, Green, Blue };
	virtual void draw(ShapeColor color = Red) const = 0;
};
class Rectangle : public Shape {
public:
	virtual void draw(ShapeColor color = Red) const;
};
=> �ڵ� �ߺ� + ������.

�񰡻� �������̽�(non-virtual interface) ���뱸(NVI ���뱸) ����غ���!!
	�Ļ� Ŭ�������� �������� �� �ִ� ���� �Լ��� private ����� �ΰ�,
	�� ���� �Լ��� ȣ���ϴ� public �񰡻� �Լ��� �⺻ Ŭ������ ����� �α�;

class Shape {
public:
	enum ShapeColor { Red, Green, Blue };
	void draw(ShapeColor color = Red) const {	//�񰡻� �Լ�
		doDraw(color);	//���� �Լ� ȣ��
	}
private:
	virtual void doDraw(ShapeColor color) const = 0;	//��¥ �۾��� �� �Լ�����.
};
class Rectangle : public Shape {
public:
private:
	virtual void draw(ShapeColor color) const;	//�⺻ �Ű����� ���� ����.
};

�񰡻� �Լ��� �Ļ� Ŭ�������� �������̵�Ǹ� �� �Ǳ� ������,
draw �Լ��� color �Ű������� ���� �⺻���� ����ϰ� Red�� ����.


�̰͸��� ���� ����!
	��ӹ��� �⺻ �Ű����� ���� ����� �������ؼ� �� �ȴ�.
	�ֳ��ϸ� �⺻ �Ű����� ���� �������� ���ε��Ǵ� �ݸ�, 
	�����Լ�(�������̵� �� �� �ִ� ������ �Լ�)�� �������� ���ε��Ǳ� �����Դϴ�.




�׸� 38: "has-a(...��...�� ����)" Ȥ�� "is-implemented-in-terms-of(...��...�� �Ἥ ������)"�� ����ȭ�� ���� ��ü �ռ��� �������!

�ռ�(composition)�̶�, � Ÿ���� ��ü���� �׿� �ٸ� Ÿ���� ��ü���� �����ϰ� ���� ��쿡 �����ϴ� �� Ÿ�Ե� ������ ����.
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
�ռ� == ���̾(layering) == ����(containment) == ����(aggregation) == ����(embedding) ��

��ü �ռ��� �ǹ� 2����
"has-a(...��...�� ����)"
"is-implemented-in-terms-of(...��...�� �Ἥ ������)"

�� 2����?
����Ʈ���� ���� 2����
���� ����(application domain)
	���, �̵�����, ���� ������ �� �ϻ��Ȱ �繰 �� �� ��
���� ����(implementation domain)
	����, ���ؽ�, Ž�� Ʈ�� �� �����ϰ� �ý��� �������� ���� �ΰ���

��ü �ռ��� ���� �������� �Ͼ�� has-a / ���� �������� �Ͼ�� is-implemented-in-terms-of ����


Set<T>�� list<T>�κ��� ��ӹް� ����??;
template<typename T>
class Set : public std::list<T> {};
list ��ü�� �ߺ� ���Ҹ� ���� �� �ִ� �����̳�.
Set ��ü�� ���Ұ� �ߺ��Ǹ� �� �ȴ�.
�Ͽ�, Set�� list�� ����(is-a)�̶�� ������ ���� �ƴϴ�.
list ��ü�� �ش��ϴ� ��ǵ��� Set ��ü������ ���ϴ� �� �ƴϴ�.

�̶� is implemented in terms of ���� ����!;
template<class T>
class Set {
public:
	bool member(const T& item) const;

	void insert(const T& item);
	void remove(const T& item);

	std::size_t size() const;
private:
	std::list<T> rep;	//Set �������� ���� ǥ����
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
=> is-a�� �ƴ϶� is-implemented-in-terms-of ��!

�̰͸��� ���� ����!
1. ��ü �ռ�(composition)�� �ǹ̴� public ����� ���� �ǹ̿� ������ �ٸ���.
2. ���� �������� ��ü �ռ��� �ǹ̴� has-a(...��...�� ����)��.
	���� ���������� is-implemented-in-terms-of(...��...�� �Ἥ ������) �ǹ̴�.




�׸� 39: private ����� �ɻ�����ؼ� ��������

public ��� is-a.
private ��� �Ẹ��;

class Person {};
class Student : private Person {};
void eat(const Person& p);
void study(const Student& s);
Person p;
Student s;
eat(p);
eat(s);		//����! Student�� Person�� ������ �ƴϴ�.

�⺻ Ŭ�����κ��� �������� ����� �Ļ� Ŭ�������� ������ private ����� ��.
private ����� �ǹ̴� is-implemeted-in-terms-of.
'������ �������� �� �ִ�. �������̽��� ������ ����'
D ��ü�� B ��ü�� �Ἥ ������.
����Ʈ���� ����(design) ���� �ǹ� ����. ���� ����Ʈ���� ����(implementation) �߿��� �ǹ̸� ����.

�� �� ������ ��ü �ռ�, �� �ؾ� �ϸ� private ���.
����� ����� ������ �� Ȥ�� ���� �Լ��� �������� ���.

cf) ��������: ���α׷��� ����Ǹ鼭 ȣ��Ǵ� �Լ����� ������ ����Ʈ �� 
�� �Լ��� ���� �ð��� ��ü �ð��� ���� ���� �ð� ������ �м��ϴ� �۾� Ȥ�� �� ���.;

class Timer {
public:
	explicit Timer(int tickFrequency);
	virtual void onTick() const;		//���� �ð��� ����� ������ �ڵ����� �̰��� ȣ���.
};

Widget Ŭ������ Timer Ŭ������ ��ӹް��� ��.;
class Widget : private Timer {
private:
	virtual void onTick() const;	//Widget ��� �ڷ� ���� ������.
};
��� ����� private���� �� ���ÿ�, Timer�� public ����� onTick �Լ��� Widget���� private ����� ��.
public ���� �����ϸ� �ȵ�. (�Լ� ȣ���� �� ���� ������ ������);


class Widget {
private:
	class WidgetTimer : public Timer {
	public:
		virtual void onTick() const;
	};
	WidgetTimer timer;
};
��ü �ռ�
private ��ø Ŭ���� ����.

private ��Ӱ� ���ϸ� �����ϳ�, public ��ӿ� ��ü �ռ� ������ ���̴� ����

1. Widget Ŭ������ �����ϴ� �� �־ �Ļ��� �����ϰ� �ϵ�,
�Ļ� Ŭ�������� onTick �� �������� �� ������ ���� �������� ���� ���� �� ����.
Widget�� �Ļ� Ŭ������ �ƹ��� ���� �ᵵ WidgetTimer�� �������� �Ұ���.
�Ļ� Ŭ�������� ���� �Լ��� �������� �� ���� ���� ���

2. Widget�� ������ �������� �ּ�ȭ�ϰ� ���� �� ����.
Widget�� Timer���� �Ļ��� ���¶��, Widget�� �����ϵ� �� Timer�� ���ǵ� ����� �� �־�� ��.
Widget�� ���Ǻ� ���Ͽ��� Timer.h ���� ����� #include �ؾ� �Ѵ�.

�ݸ�, ������ ���迡���� WidgetTimer�� ���Ǹ� Widget���κ��� ������,
Widget�� WidgetTimer ��ü�� ���� �����͸� ������ ����� �θ�,
WidgetTimer Ŭ������ ������ �����ϴ� �͸����ε� ������ �������� ��½ ���� �� ����.
(������ ������ �ּ�ȭ: �׸� 31 ����)


private ����� ����ؾ� �ϴ� ���? 
����� ����� ������ �� Ȥ�� ���� �Լ��� �������� ���.
�� ��� ���� ����.

���� Ŭ����(empty class)�� ���������� �����ϴ� �޸� ������ ����.
C++���� "���� ����(freestanding)�� ��ü�� �ݵ�� ũ�Ⱑ 0�� �Ѿ�� �Ѵ�"�� ������ ����

class Empty {};
class HoldsAnInt {
private:
	int x;
	Empty e;	//�޸� �䱸�� ����� �ϴµ�..
};
=> sizeof(HoldsAnInt) > sizeof(int) ��.
sizeof(Empty)�� ���� 1.
�����Ϸ��� ���� ��ü�� char �� ���� ���׸Ӵ� ��������.
����Ʈ ����(alignment)(�׸� 50 ����)�� �ʿ��ϴٸ� Ŭ������ ����Ʈ �е� ������ �߰��� �� ����
	HoldsAnInt ��ü�� ũ��� char �ϳ��� ũ�⸦ �Ѱ� ��.
��, �� ������ �Ļ� Ŭ���� ��ü�� �⺻ Ŭ���� �κп��� ������� ����.
	�̶��� �⺻ Ŭ���� �κ��� �������� ��ü, Ȧ�μ��⸦ �� ��ü�� �ƴϱ� ����.

Empty Ÿ���� ��ü�� ������ ����� ���� ���� Empty�κ��� ��� ���Ѻ���;
class HoldsAnInt: private Empty {
private:
	int x;
};
sizeof(HoldsAnInt) == sizeof(int)
�� �������� ����� "���� �⺻ Ŭ���� ����ȭ(empty base optimization: EBO)"
EBO�� ���� ��� �Ͽ����� ����.

�̰͸��� ���� ����!
1. private ����� �ǹ̴� is-implemented-in-terms-of(...��...�� �Ἥ ������)�̴�.
	�밳 ��ü �ռ��� ���ؼ� ���̴� �о߰� ������ ������, 
	�Ļ� Ŭ���� �ʿ��� �⺻ Ŭ������ protected ����� �����ؾ� �� ���,
	or ��ӹ��� ���� �Լ��� �������ؾ� �� ��� private ����� �ǹ̰� �ִ�.

2. ��ü �ռ��� �޸�, private ����� ���� �⺻ Ŭ���� ����ȭ(EBO)�� Ȱ��ȭ��ų �� �ִ�.




�׸� 40: ���� ����� �ɻ�����ؼ� �������

���� ���(multiple inheritance: MI).
���� ���(single ingheritance: SI).;

class BorrowableItem {	//���̺귯���κ��� ������ �� �ִ� � ��
public:
	void checkOut();
};
class ElectronicGadget {
private:
	bool checkOut() const;	//��ü �׽�Ʈ�� �ǽ��ϰ�, ���� ���θ� ��ȯ.
};
class MP3Player:		//���⼭ MI�� �ȴ�.(��� ���̺귯���κ��� ����� �����´�.)
	public BorrowableItem, public ElectronicGadget 
	{ /*...*/ };
MP3Player mp;
mp.checkOut();	//��ȣ�� �߻�! ��� checkOut?
����? => mp.BorrowableItem::checkOut();
=> private ��� �Լ� ȣ���̶� �ȵ�.

"������ MI �������(deadly MI diamond)" ����� ���� �� ����.;
class File {};
class InputFile : public File {};
class OutputFile : public File {};
class IOFile : public InputFile, public OutputFile {};

c++�� ������ ����� �ߺ� ���� �ع���.
���� �⺻ Ŭ����(virtual base class)�� ����.
�⺻ Ŭ������ ���� Ŭ������ ���� ����� �Ļ� Ŭ�������� ���� ���(virtual inheritance)�� ����ϰ� ����.;

class File {};
class InputFile : virtual public File {};
class OutputFile : virtual public File {};
class IOFile : public InputFile, public OutputFile {};

c++ ǥ�� ���̺귯�� �� basic_ios �迭�� �̷���.

�Ļ� Ŭ������� ���� ���� �⺻ Ŭ���� �κ��� �ʱ�ȭ �� �� ��Ģ
1. �ʱ�ȭ�� �ʿ��� ���� �⺻ Ŭ�����κ��� Ŭ������ �Ļ��� ���, �� �Ļ� Ŭ������ ���� �⺻ Ŭ�������� �Ÿ��� �������
	���� �⺻ Ŭ������ ���縦 ���ο� �ΰ� �־�� �Ѵ�.
2. ������ Ŭ���� ���뿡 �Ļ� Ŭ������ ���� �߰��� ���� �� �Ļ� Ŭ������ ���� �⺻ Ŭ������ �ʱ�ȭ�� ���þƾ� �Ѵ�.

���� �⺻ Ŭ������ ���� ����
1. �� �ʿ� ������ ������� ����. �񰡻� ����� �⺻.
2. �׷��� ��� �Ѵٸ�, ���� �⺻ Ŭ�������� �����͸� ���� �ʵ���.;

class IPerson {
public:
	virtual ~Iperson();
	virtual std::string name() const = 0;
	virtual std::string birthDate() const = 0;
};
�߻� Ŭ������ �ν��Ͻ��� ���� �� ������ ������ �� �����ڸ� ���� ���α׷��� �ؾ� �� ��.
IPerson�� ����ڴ� ���丮 �Լ�(�׸� 31 ����)�� ����ؼ� ��ü �Ļ� Ŭ������ �ν��Ͻ���.;

//������ �����ͺ��̽� ID�κ��� IPerson ��ü�� ������ ���丮 �Լ���.
//��ȯ Ÿ���� ���� �����Ͱ� �ƴ� ������ �ñ��ϸ� �׸� 18 �ʵ�!
std::tr1::shared_ptr<IPerson> makePerson(DatabaseID, personIdentifier);
//����ڷκ��� �����ͺ��̽� ID�� ���� �Լ�
DatabaseID askUserForDatabaseID();
DatabaseID id(askUserForDatabaseID());
std::tr1::shared_ptr<IPerson> pp(makePerson(id));	//IPerson �������̽��� �����ϴ� ��ü�� �ϳ� ����� pp�� ����Ű�� ��.
													//���Ŀ��� *pp�� ������ ���� IPerson�� ��� �Լ��� ���.

makePerson �Լ��� �ν��Ͻ��� ���� �� �ִ� ��ü Ŭ������ IPerson���κ��� �Ļ��Ǿ� �־��.
CPerson�̶�� ����.
CPerson�� IPerson���κ��� �������� ���� ���� �Լ��� ���� ������ ����.
�����ͺ��̽� ���� Ŭ������ PersonInfo�� ���� CPerson�� �ʿ��� �ٽ� ����� ������ �ִ���� ����.;
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

�پ��� �������� ���ڿ� ����� ������ �� �ִٰ� ����
valueDelim~�� ���� ������, �� �����ڸ� ������ �� �ֵ��� ��.;

const char * PersonInfo::valueDelimOpen() const {
	return "[";
}
const char * PersonInfo::valueDelimClose() const {
	return "]";
}
const char * PersonInfo::theName() const {
	//��ȯ ���� ���� ���۸� ����. �� ���۴� ���� �޸��̱� ������, �ڵ����� ��� 0���� �ʱ�ȭ��.
	static char value[Max_Formatted_Field_Value_Length];
	std::strcpy(value, valueDelimOpen());
	//value�� ����ִ� ���ڿ��� �� ��ü�� name �ʵ带 �����δ�. (���� ������, ������ ���� ����ų �� ����. �׸� 21 ����)
	//�� �����ڸ� value�� �߰�.
	std::strcat(value, valueDelimClose());
	return value;
}

theName�� valueDelimOpen�� ȣ�� = > ���� �����ڸ� ����� = >
name�� ��ü�� ���� ���� = > valueDelimClose�� ȣ���ϵ��� ������.

valueDelimOpen, Close�� ���� �Լ��̱� ������,
theName�� ��ȯ�ϴ� ����� PersonInfo���� �¿�Ǵ� ���� �ƴ϶�
Person - Info�κ��� �Ļ��� Ŭ�������� �¿�ȴ�.

CPerson ��� IPerson;
class IPerson {		//�� Ŭ������ ��Ÿ���� ���� �뵵�� ���� ������ �������̽�.
public:
	virtual ~Iperson();
	virtual std::string name() const = 0;
	virtual std::string birthDate() const = 0;
};
class DatabaseID { /*...*/ };

class PersonInfo {		//�� Ŭ�������� IPerson �������̽��� �����ϴ� �� ������ �Լ��� ����ִ�.
public:
	explicit PersonInfo(DatabaseID pid);
	virtual ~PersonInfo();
	virtual const char * theName() const;
	virtual const char * theBirthDate() const;
	virtual const char * valueDelimOpen() const;
	virtual const char * valueDelimClose() const;
};

class CPerson : public IPerson, private PersonInfo {		//MI�� ����~
public:
	explicit CPerson(DatabaseID pid) : PersonInfo(pid) {}
	virtual std::string name() const {		//IPerson Ŭ������ ���� ���� �Լ��� ���� �Ļ� Ŭ������ ������ ����.
		return PersonInfo::theName();
	}
	virtual std::string birthDate() const {
		return PersonInfo::theBirthDate();
	}
private:
	const char * valueDelimOpen() const { return ""; }	//���� �Լ��鵵 ��ӵǹǷ� �� �Լ��鿡 ���� ������ ������ �����.
	const char * valueDelimClose() const { return ""; }
};
=>���� ����� ����.
�ٸ� ��¥��¥ �ʿ��� �� ���� ���� ����.

�̰͸��� ���� ����!
1. ���� ����� ���� ��Ӻ��� Ȯ���� �����ϴ�. 
	���ο� ��ȣ�� ������ ����ų �Ӹ� �ƴ϶� ���� ����� �ʿ����� ���� �ִ�.

2. ���� ����� ���� ũ�� ���, �ӵ� ����� �þ��, �ʱ�ȭ �� ���� ������ ���⵵�� Ŀ����.
	���� ���� �⺻ Ŭ�������� �����͸� ���� �ʴ� ���� ���������� ���� �ǿ���.

3. ���� ����� �����ϰ� �� �� �ִ� ��찡 �ִ�. ���� �ó����� �� �ϳ���,
	�������̽� Ŭ�����κ��� public ����� ��Ŵ�� ���ÿ� ������ ���� Ŭ�����κ��� private ����� ��Ű�� ��.;





���ø��� �Ϲ�ȭ ���α׷���

���ø�.
���ø��� ���� �о߷� �Ļ��� �Ϲ�ȭ ���α׷���(generic programming, ������ ��ü�� Ÿ�԰� ������� �ڵ带 �ۼ��ϵ��� �ϴ� ����) ����
Ʃ�� ����(Turing-complete)���� ���� �ִ�.
cf) Ʃ�� ����: ���� Ʃ�� ���� ������ ��� �ɷ��� ���� �ִ� � �߻� ��� Ȥ�� ���α׷��� ���.

�ٽ� ����, ��� ������(computable) � ���� ����� �� �ִ�.
���ø� ��Ÿ���α׷���(metaprogramming)�̶�� ���ο� ���� ź��.


�׸� 41: ���ø� ���α׷����� õ���浵 �Ͻ��� �������̽��� ������ Ÿ�� ����������.

���� ���α׷��� �����
'����� �������̽�(explicit interface)'�� '��Ÿ�� ������(runtime polymorphism)'
����;
class Widget {
public:
	Widget();
	virtual ~Widget();
	virtual std::size_t size() const;
	virtual void normalize();
	void swap(Widget& other);	//�׸� 25 ����.
};
void doProcessing(Widget& w) {
	if (w.size() > 10 && w != someNastyWidget) {
		Widget temp(w);
		temp.normalize();
		temp.swap(w);
	}
}
w�� Widget Ÿ������ ����Ǿ��� ������, w�� Widget �������̽��� �����ؾ� �Ѵ�.
	Widget�� ����� h ���� �� �ҽ� �ڵ忡�� ã���� � �������� Ȯ���� �� �����Ƿ�,
	�̷� �������̽��� ������ '����� �������̽�'.
	�ҽ� �ڵ忡 ��������� �巯���� �������̽�

Widget�� ��� �Լ� �� �� ���� ���� �Լ��̹Ƿ�, �� ���� �Լ��� ���� ȣ���� '�� Ÿ�� ������'�� ���� �̷����.
	��, Ư���� �Լ��� ���� ���� ȣ���� w�� ���� Ÿ��(�׸� 37 ����)�� ������� ��Ÿ�ӿ� ������.

���ø�
'�Ͻ��� �������̽�(implicit interface)'�� '������ Ÿ�� ������(compile-time polymorphism)';
template<typename T>
void doProcessing(T& w) {
	if (w.size() > 10 && w != smoeNastyWidget) {
		T temp(w);
		temp.normalize();
		temp.swap(w);
	}
}

w�� �����ؾ� �ϴ� �������̽��� �� ���ø� �ȿ��� w�� ���� ����Ǵ� ������ ������.
size, normalize ��..
�� ���ø��� �����ϵǷ��� �� ���� ǥ������ '��ȿ(valid)'�ؾ� �ϴµ�, 
�� ǥ���ĵ��� �ٷ� T�� �����ؾ� �ϴ� �Ͻ��� �������̽�.

w�� ���ݵǴ� �Լ� ȣ�� operator>, operator!= �Լ� ȣ�� �� �ش� ȣ�� ���� ���� ���ø��� �ν��Ͻ�ȭ�� �Ͼ.
������ ���߿� �Ͼ.
�ν��Ͻ�ȭ�� �����ϴ� �Լ� ���ø��� � ���ø� �Ű������� �����Ŀ� ���� ȣ��Ǵ� �Լ��� �޶����� ������,
�̰��� ������ '������ Ÿ�� ������' �̶�� �Ѵ�.


��Ÿ��, ������ Ÿ�� ������ �򰥸��� �ʱ�
�����ε�� �Լ� �� ���� ȣ���� ���� ��󳻴� ����(������ �߿� �Ͼ)��
���� �Լ� ȣ���� ���� ���ε�(���α׷� ���� ��)�� �������� ���.

�����, �Ͻ��� �������̽� ����
���~ �� �밳 �Լ� �ñ״�ó�� �̷����
cf) �ñ״�ó: �Լ��� �̸�, �Ű����� Ÿ��, ��ȯ Ÿ�� ���� ��Ʋ�� �̸�.;
class Widget {
public:
	Widget();
	virtual ~Widget();
	virtual std::size_t size() const;
	virtual void normalize();
	void swap(Widget& other);
};
������, �Ҹ���, size �� �Լ�, �Ű����� Ÿ��, ��ȯ Ÿ��, �� �Լ��� ����� ���η� �̷����.
	�����Ϸ��� �ڵ����� ���� ���� ������, ���� ���� �����ڵ� ���Ե�(�׸� 5 ����).
	typedef Ÿ���� ���� ��� �̰͵� ����.)
	�ٸ�, ������ ����� public�� �־ �ñ״�ó�� ���� ����.

�ݸ� �Ͻ��� �������̽��� �Լ� �ñ״�ó�� ����ϰ� ���� ����.
	�Ͻ�~ �� �̷�� ��Ҵ� ��ȿ 'ǥ����(expression)'.;
template<typename T>
void doProcessing(T& w) {
	if (w.size() > 10 && w != someNastyWidget) {}
}
T���� ������ �Ͻ��� �������̽����� ������ ����
1. ���� �迭�� ���� ��ȯ�ϰ� �̸��� size�� �Լ��� �����ؾ� ��.
2. T Ÿ���� ��ü ���� ���ϴ� operator!= �Լ��� �����ؾ� ��.

=> �ٸ� �� �� ������ �����ε� ���ɼ��� �־ ������ų �ʿ� ����.

�Ͻ��� �������̽��� ���� ��ȿ ǥ������ ����.
if (w.size() > 10 && w != someNastyWidget) {}
���� �Լ��� ���� ������?
if ��ȣ �� bool�� ȣȯ / ���� ������, normalize, swap �Լ��� ���� ȣ���� T Ÿ���� ��ü�� ���� '��ȿ'�ؾ� ��.


�̰͸��� ���� ����!
1. Ŭ���� �� ���ø��� ��� �������̽��� �������� ������.
2. Ŭ������ ���, �������̽��� ������̸� �Լ��� �ñ״�ó�� �߽����� ������.
	�������� ���α׷� ���� �߿� ���� �Լ��� ���� ��Ÿ��.
3. ���ø� �Ű������� ���, �������̽��� �Ͻ����̸� ��ȿ ǥ���Ŀ� ����� �ξ� ������.
	�������� ������ �߿� ���ø� �ν��Ͻ��� �Լ� �����ε� ��ȣ�� �ذ��� ���� ��Ÿ��.;




�׸� 42: typename �� �� ���� �ǹ̸� ����� �ľ�����!

�� ������ ? ;
template<class T> class Widget;
template<typename T> class Widget;
���� ����. ��Ÿ�� ���� �ٸ�.


����: �����̳ʿ� ��� ���ҵ� �� �� ��° ���� ���� ����ϴ� �̻��� �ڵ�;
template<typename C>
void print2nd(const C& container) {
	if (container.size() >= 2) {
		C::const_iterator iter(container.begin());	//ù° ���ҿ� ���� �ݺ��� ���
		++iter;	//iter�� �� ��° ���ҷ� �ű��.
		int value = *iter;	//�� ���Ҹ� �ٸ� int�� ����.
		std::cout << value;
	}
}

iter�� Ÿ���� C::const_iterator
���ø� �Ű������� C�� ���� �޶����� Ÿ��.
���ø� ���� �̸� �߿� �̷��� ���ø� �Ű������� ���ӵ� ���� ������ '���� �̸�(dependent name)'�̶� ��.

���� �̸��� � Ŭ���� �ȿ� ��ø�� ���� '��ø ���� �̸�(nested dependent name)'�̶� ��.
'��ø ���� Ÿ�� �̸�(nested dependent type name)'
Ÿ���� �����ϴ� ��ø ���� �̸�.

�� value���� int �� ���ø� �Ű������� ��� ������� Ÿ�� �̸�.
'������ �̸�(non-dependent name)'.


template<typename C>
void print2nd(const C& container) {
	C::const_iterator * x;
}
= > C::~~�� x�� ���� ������ ���� �ִ� ��û�� �ڵ�.

��ø ���� �̸��� �⺻������ Ÿ���� �ƴ� ������ �ؼ���.;
template<typename C>
void print2nd(const C& container) {
	if (container.size() >= 2) {
		typename C::const_iterator iter(container.begin());
	}
}
=> ����� �� �ڵ�. C::const_iterator�� �ݵ�� Ÿ���̶� �˷���� ��.
���ø� �ȿ��� ��ø ���� �̸��� ������ ��쿡��, �̸� �� typename Ű����
(���� �� �̵� ����);


template<typename C>
void f(const C& container,			//typename ���� �ȵ�
	typename C::iterator iter);		//typename �� ��� ��
=> C�� ��ø ���� Ÿ�� �̸��� �ƴ�.
��, ���ø� �Ű������� �������� � �͵� C�� ǰ�� ���� ����.


(����) ��ø ���� Ÿ�� �̸��� �⺻ Ŭ������ ����Ʈ�� �ְų� 
��� �ʱ�ȭ ����Ʈ ���� �⺻ Ŭ���� �ĺ��ڷ� ���� ���� �ȵ�.;

template<typename T>
class Derived : public Base<T>::Nested {		//��ӵǴ� �⺻ Ŭ���� ����Ʈ
	explicit Derived(int x) : Base<T>::Nested(x) {		//��� �ʱ�ȭ ����Ʈ�� �ִ� �⺻ Ŭ���� �ĺ���
		typename Base<T>::Nested temp;		//��ø ���� Ÿ�� �̸��̸�, �⺻ Ŭ���� ����Ʈ���� ����,
											//��� �ʱ�ȭ ����Ʈ�� �⺻ Ŭ���� �ĺ��ڵ� �ƴ�.
	}
};

template<typename IterT>
void workWithIterator(IterT iter) {
	typename std::iterator_traits<IterT>::value_type temp(*iter);
}
C++ ǥ���� Ư������(traits) Ŭ����(�׸� 47 ����)�� ����� �ͻ�.
IterT Ÿ���� ��ü�� ����Ű�� ����� Ÿ��.
IterT ��ü�� ����Ű�� �Ͱ� �Ȱ��� Ÿ���� ���� ����(temp)�� ������ ��,
iter�� ����Ű�� ��ü�� �� temp�� �ʱ�ȭ�ϴ� ����.

IterT�� vector<int>::iterator��� temp�� Ÿ���� int.
std::iterator_traits<IterT>::value_type�� ��ø ���� Ÿ�� �̸�.
value_type�� iterator_traits<IterT> �ȿ� ��ø�Ǿ� �ְ�, IterT�� ���ø� �Ű������̹Ƿ�.
�� �տ��� typename !

std::iterator_traits<IterT>::value_type
�̰� ġ�� �ʹ� ��������.
typedef���� �̸� �����.;
template<typename IterT>
void workWithIterator(IterT iter) {
	typedef typename std::iterator_traits<IterT>::value_type value_type;
	value_type temp(*iter);
}
"typedef typename T" ����.


���� ����!
1. ���ø� �Ű������� ������ ��, class �� typename �� ���� �ٲپ� �ᵵ ������.
2. ��ø ���� Ÿ�� �̸��� �ĺ��ϴ� �뵵���� �ݵ�� typename �� ���.
	��ø ���� �̸��� �⺻ Ŭ���� ����Ʈ�� �ְų�
	��� �ʱ�ȭ ����Ʈ ���� �⺻ Ŭ���� �ĺ��ڷ� �ִ� ��쿡�� ����.;




�׸� 43: ���ø����� ������� �⺻ Ŭ���� ���� �̸��� �����ϴ� ����� �˾� ����!

����: �� �� ȸ�翡 �޽��� ������ �� �ִ� ���� ���α׷�
���ۿ� �޽����� ��ȣȭ�� ����, �����ؽ�Ʈ(���ȣȭ) ���°� �� ����.;
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
class MsgInfo {/*...*/};	//�޽��� ������ ���Ǵ� ������ ��� ���� Ŭ����

template<typename Company>
class MsgSender {
public:
	//...������ �Ҹ��� ���
	void sendClear(const MsagInfo& info) {
		std::string msg;	
		//info�κ��� msg�� �����.;
		Company c;
		c.sendCleartext(msg);
	}
	void sendSecret(const MsgInfo& info) {/*...*/}	//sendClear �Լ��� ���. ��, c.sendEncrypted �Լ��� ȣ���ϴ� ����
};
//�α� �߰�
template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	void sendClearMsg(const MsgeInfo& info) {
		//"�޽��� ���� ��" ������ �α׿� ���;
		sendClear(info);					//�⺻ Ŭ������ �Լ��� ȣ���ϴµ�, �� �ڵ�� �����ϵ��� �ʽ��ϴ�!
		//"�޽��� ���� ��" ������ �α׿� ���;
	}
};

LoggingMsgSender::sendClearMsg��
MsgSender::sendClear �̸� �ٸ�.
�⺻ Ŭ�����κ��� �������� �̸��� �Ļ� Ŭ�������� ������ ����(�׸� 33) �ذ�.
��ӹ��� �񰡻� �Լ��� �������ϴ� ����(�׸� 36) �ذ�.

�ٸ� �����ϵ��� ����.
LoggingMsgSender Ŭ���� ���ø��� ���ǿ� ����ĥ ��, �����Ϸ��� �� Ŭ������ ��� �Ļ��� ������ ��.
Company�� ������ ���� �� �� ����.

������ ��ü������ �˾ƺ���
����: ��ȣȭ�� ��Ÿ��� ���.;
class CompanyZ {		//�� �Լ��� sendCleartext �Լ��� ���� �� ��.
public:
	void sendEncrypted(const std::string& msg);
};

MsgSender ���ø��� CompanyZ �� ���俣 �� �׷�.
�� ���ø��� sendClear �Լ��� �����ϱ� ����.
CompanyZ�� ���� MsgSender�� Ư��ȭ ���� ����. sendCleartext �Լ��� ���� �͸� �����ϸ� �Ϲ��� ���ø��� �Ȱ���.;
template<>
class MsgSender<CompanyZ> {
public:
	void sendSecret(const MsgInfo& info) { }
};

template<> �� ��: �̰� ���ø��� �ƴϰ� Ŭ������ �ƴϴ�.
�ٽ� ���ϸ�, ���� �ڵ�� MsgSender ���ø��� ���ø� �Ű������� CompanyZ�� �� �� �� �ֵ��� Ư��ȭ�� �����̴�.
'���� ���ø� Ư��ȭ(total template specialization)'�̶�� �Ѵ�.
���ø��� �Ű��������� �������� ��ü���� Ÿ������ ������ ����.

�ٽ� �Ʊ� �ڵ��;
template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	void sendClearMsg(const MsgeInfo& info) {
		//...
		sendClear(info);					//���� Company == CompanyZ��� �� �Լ��� ���� �� ���� ����!
		//...
	}
};
�⺻ Ŭ������ MsgSender<CompanyZ>�� ���� �� ��. sendClear �Լ� ������..

C++�� ���ø�ȭ�� �⺻ Ŭ������ �ڴ�� �� ������ ������ �������� �ʵ���! �ϴ� ��� 3����

1. this->;
template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	void sendClearMsg(const MsgInfo& info) {
		this->sendClear(info)	//sendClear�� ��ӵǴ� ������ ����
	}
};

2. using ����;
template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	using MsgSender<Company>::sendClear		//�����Ϸ����� sendClear�Լ��� �⺻ Ŭ������ �ִٰ� �����϶�� �˷���.
	void sendClearMsg(const MsgInfo& info) {
		sendClear(info)	//sendClear�� ��ӵǴ� ������ ����
	}
};

3. ȣ���� �Լ��� �⺻ Ŭ������ �Լ���� ���� ��������� ����;
template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
	void sendClearMsg(const MsgInfo& info) {
		MsgSender<Company>::sendClear(info)	//sendClear�Լ��� ��ӵǴ� ������ ������.
	}
};
�ٸ� �� ��° ����� ���� �Լ� ���ε��� ���õǾ� ������ ����.


�� ���� ��� ��� ���� ������ ����.
�⺻ Ŭ���� ���ø��� ���Ŀ� ��� Ư��ȭ�Ǵ���
������ �Ϲ��� ���ø����� �����ϴ� �������̽��� �״�� ������ ���̶� �����Ϸ����� ���.
����� LoggingMsgSender ���� �Ļ� Ŭ���� ���ø��� �����Ϸ��� �����м��ϴ� �� �ݵ�� �ʿ�������,
�� ����� ������ ������;
LoggingMsgSender<CompanyZ>zMsgSender;
MsgInfo msgData;
zMsgSender.sendClearMsg(msgData);	//����!

�����ϵ��� ����.
sendClearMsg�� MsgSender<CompanyZ> Ŭ������ �� ��� �ִٴ� ��ǵ� �����Ϸ��� �˾�æ ��.

�⺻ Ŭ������ ����� ���� ������ ��ȿ������ �����Ϸ��� �����ϴ� ������ �̸�(�Ļ� Ŭ���� ���ø��� ���ǰ� �����м��� ��) ������,
�ƴϸ� ���߿�(�Ļ� Ŭ���� ���ø��� Ư���� �Ű������� �޾� �ν��Ͻ�ȭ�� ��) �����İ� �ٷ� �ٽ�.
C++�� '�̸� ����(early diagnose)'�� ��ȣ�ϴ� ��å���� ����.
�Ļ� Ŭ������ ���ø����κ��� �ν��Ͻ�ȭ�� �� �����Ϸ��� �⺻ Ŭ������ ���뿡 ���� �ƹ��͵� �𸣴� ������ �����ϴ� ��.

���� ����!
1. �Ļ� Ŭ���� ���ø����� �⺻ Ŭ���� ���ø��� �̸��� ������ ����, "this->"�� ���λ�� ���̰ų�
	�⺻ Ŭ���� �������� ��������� �� �ִ� ������ �ذ�.;




�׸� 44: �Ű������� �������� �ڵ�� ���ø����κ��� �и���Ű��!

���ø� ���� ¯¯
���ø� �߸� ����ϸ� '�ڵ� ���ȭ(code bloat)'

�ڵ� �ߺ� ����å
���뼺 �� ������ �м�(commonality and variability analysis)
���� �κ��� ������ ���ο� Ŭ������ �ű� ��, Ŭ���� ��� or ��ü �ռ�(�׸� 32, 38, 39) ����ؼ�
������ Ŭ�������� ���� �κ��� �����ϵ��� �ϱ�.
���� �κ�(varying part)�� ������ ��ġ�� ��������.

���ø��� ���� �� �ν��Ͻ�ȭ�� �� �߻��� �� �ִ� �ڵ� �ߺ��� �˾�ä�� �Ѵ�.

����: ����� ����;
template<typename T, std::size_t n>		//T Ÿ���� ��ü�� ���ҷ� �ϴ� n�� n���� ����� ��Ÿ���� ���ø�.
class SquareMatrix {
public:
	void insert();		//�־��� ����� �� ����������� ����ķ� ����.
};
=> �� ���ø��� T Ÿ�� �Ű������� ������, size_t Ÿ���� '��Ÿ�� �Ű�����(non-type parameter)'�� n�� �޵��� �Ǿ�����.;

SquareMatrix<double, 5> sm1;
sm1.invert();		//SquareMatrix<double, 5>::invert�� ȣ��
SquareMatrix<double, 10> sm2;
sm2.invert();		//SquareMatrix<double, 10>::invert�� ȣ��

invert�� �纻�� �ν��Ͻ�ȭ.
5x5 ��Ŀ� ���� �����ϴ� �Լ�, 10x10 ~
=> �������� �ڵ� ���ȭ ����.;

template<typename T>
class SquareMatrixBase {	//������Ŀ� ���� �� �� �ִ� ũ�⿡ �������� �⺻ Ŭ����
protected:
	void invert(std::size_t matrixsize);	//�־��� ũ���� ����� ����ķ� ����� ����
};
template<typename T>
class SquareMatrix: private SquareMatrixBase<T> {
private:
	using SquareMatrixBase<T>::invert;		//�⺻ Ŭ������ invert�� �������� ���� ���� ���� ����. �׸� 33.
public:
	void invert() {
		this->invert(n);	//invert�� �⺻ Ŭ���� ������ ���� �ζ��� ȣ���� ����.
	}
};
=> ���� �Ű������� �޴� ������ �Լ��� �����, 5�� 10�� �Ű������� �Ѱܼ� �Լ� ȣ��.
��� ��������� ���� �� ������ SquareMatrixBase Ŭ������ ����.
���� ���� Ÿ���� ��������� ����ϴ� �⺻ Ŭ���� ������ invert �Լ��� ���� �� ���� �纻.

SquareMatrixBase::invert �Լ��� �Ļ� Ŭ�������� �ڵ� ������ ���� �������θ� ������ ��ġ.
�׷��� protected ���.
�Ļ�Ŭ������ invert�Լ��� �Ͻ��� �ζ��� �Լ�(�׸� 30)

this-> ǥ��� �׸� 43���� �̾߱��� ���ø�ȭ�� �⺻ Ŭ������ ��� �Լ� �̸��� �Ļ� Ŭ�������� �������� ������ ���ϱ� ���� ��.
using ���� ��������. �̶� using ���� ���ʿ��� �� ����.

��� ���赵  private.
�⺻ Ŭ������ ������ �Ļ� Ŭ������ ������ ���� ���� �� �ܿ� �ƹ� ������ ���ٴ� ����� �巯��. (�׸� 39)

����
�⺻ Ŭ���� �Լ��� ��¥ ����� ������ �����Ͱ� ��� �ִ��� ��.
��� ������ �޸𸮿� ��� �����͸� SquareMatrixBase�� �����ϰ� ����.;

template<typename T>
class SquareMatrixBase {
protected:
	SquareMatrixBase(std::size_t n, T *pMem)	//��� ũ�⸦ �����ϰ�, ��� ���� ���� �����͸� ����.
		: size(n), pData(pMem) {}
	void setDataPtr(T *ptr) { pData = ptr; }	//pData�� �ٽ� ����.
private:
	std::size_t size;	//����� ũ��
	T *pData;	//��� ���� ���� ������
};

template<typename T, std::size_t n>
class SquareMatrix : private SquareMatrixBase<T> {
public:
	SquareMatrix()
		: SquareMatrixBase<T>(n, data) {}	//��� ũ��(n) �� ������ �����͸� �⺻ Ŭ������ �÷� ������
private:
	T data[n*n];
};
=> ���� �޸� �Ҵ� �ʿ� ���� ��ü. �ٸ� ��ü ��ü�� ũ�Ⱑ �� Ŀ�� �� �ִ�.

�� ����� �����͸� ���� �� ���� �ִ�.;
template<typename T, std::size_t n>
class SquareMatrix : private SquareMatrixBase<T> {
public:
	SquareMatrix() : SquareMatrixBase<T>(n, 0), pData(new T[n*n]) {		//�⺻ Ŭ������ �����͸� �η� �����ϰ�, ��� ���� �޸𸮸� �Ҵ��ϰ�,
		this->setDataPtr(pData.get());			//�Ļ� Ŭ������ �����Ϳ� �� �޸𸮸� ���� ���� ��, �� �������� �纻�� �⺻ Ŭ���� �÷�������
	}
private:
	T data[n*n];
};

����
SquareMatrix�� ���� ��� �Լ� �� ��ܼ��� �⺻ Ŭ���� ������ ȣ���ϴ� �ܼ� �ζ��� �Լ��� ��
�Ȱ��� Ÿ���� �����͸� ���ҷ� ���� ��� ������ĵ��� ��� ũ�⿡ ������� �� �⺻ Ŭ���� ������ �纻 �ϳ��� ������.
��� ũ�Ⱑ �ٸ� SquareMatrix ��ü�� ������ ������ Ÿ���� ������ ����.
	SquareMatrix<double, 5>�� SquareMatrix<double, 10>�� Ÿ���� �ٸ�.


��¥�� �ƴ�
ũ�⺰ ���� ������ ���, ��� ũ�Ⱑ ������ ������ ���ԵǴ� ����̱� ������ 
��� ����(constant propagation) ���� ����ȭ�� ���� ��� ����
�����Ǵ� ��� ��ɾ ���� �� ũ�� ���� ��ġ �ǿ�����(immediate operand)�� ������ �͵� �̷� ������ ����ȭ.
ũ�⺰ ���� ������ �� ���� ����.

(�����..)

�ٸ� ����
���� �ڵ尡 �۾�����.
���α׷��� �۾� ��Ʈ ũ�Ⱑ �پ��鼭 ��ɾ� ĳ�� ���� ���� �������� ���
cf) �۾� ��Ʈ: �� ���μ������� ���� �����ϴ� �������� ����
cf) ���� ������: ���μ����� �޸� ������ ���� �߿� �����ϰ� ����� ���� ������ Ư�� ���� �� Ư�� �κп� ���ߵȴٴ� ������/������ Ư��.
	�ð��� ������: ���� ������ �޸𸮴� ���� ���� ���߿� �� ������ ���ɼ��� ���ٴ� ����
	������ ������: ���� ������ �޸𸮿� ����� ���� �ִ� �޸𸮰� ������ ���ɼ��� ���ٴ� ����
	ĳ��: �ٷ� �̷��� ���� �������� �̿��ؼ� ���� ������ ���̴� ��� �޸𸮴�.

�̹� �׸񿡼��� ��Ÿ�� ���ø� �Ű������� ���� �ڵ� ���ȭ�� �ٷ�.

���� ����!
1. ���ø��� ����ϸ� �������� Ŭ������ �Լ��� ���� �� �������.
	���� ���ø� �Ű������� ���ӵ��� ���� ���ø� �ڵ�� ���ȭ�� ������ ��.
2. ��Ÿ�� ���ø� �Ű������� ����� �ڵ� ���ȭ�� ���, ���ø� �Ű������� �Լ� �Ű����� Ȥ��
	Ŭ���� ������ ����� ��ü�����ν� ���ȭ�� ���� ���� �� ����.
3. Ÿ�� �Ű������� ����� �ڵ� ���ȭ�� ���, ������ ���� ǥ�������� ������ �ν��Ͻ�ȭ�Ǵ� Ÿ�Ե���
	�� ���� �Լ� ������ �����ϰ� �������ν� ���ȭ�� ���ҽ�ų �� �ִ�.




�׸� 45: "ȣȯ�Ǵ� ��� Ÿ��"�� �޾Ƶ��̴� ���� ��� �Լ� ���ø��� ����!

����Ʈ ������.
�� ��� �ڿ��� ������ ���� ��������.
STL �����̳��� �ݺ���.
�����Ϳ� ++ ���� �����ؼ� ���� ����Ʈ�� �� ��忡�� �ٸ� ���� �̵��ϰ� ��.

�����Ϳ��� ����Ʈ �����ͷ� ����� �� ���� Ư¡�� �ִ�.
�Ͻ��� ��ȯ(implicit conversion)�� �����Ѵ�.
	�Ļ� Ŭ���� �����ʹ� �Ͻ������� �⺻ Ŭ���� �����ͷ� ��ȯ�ǰ�,
	���� ��ü�� ���� �����ʹ� ��� ��ü�� ���� �����ͷ��� �Ͻ��� ��ȯ�� ����.;

class Top {/*...*/ };
class Middle: public Top {/*...*/ };
class Bottom: public Middle {/*...*/ };
Top *pt1 = new Middle;		//Middle* ==> Top*�� ��ȯ
Top *pt2 = new Bottom;		//Bottom* ==> Top*�� ��ȯ
const Top *pct2 = pt1;		//Top* ==> const Top*�� ��ȯ

=> �̷� ���� Ÿ�� ��ȯ�� ����� ���� ����Ʈ �����͸� �Ἥ �䳻 ������ ��ٷο�;

template<typename T>
class SmartPtr {
public:
	explicit SmartPtr(T *realPtr);		//����Ʈ �����ʹ� �밳 �⺻���� �����ͷ� �ʱ�ȭ��.
};
SmartPtr<Top> pt1 = SmartPtr<Middle>(new Middle);	//SmartPtr<Middle> ==> SmartPtr<Top>�� ��ȯ
SmartPtr<Top> pt2 = SmartPtr<Bottom>(new Bottom);
SmartPtr<const Top> pct2 = pt1;


���ø��� �ν��Ͻ�ȭ �ϸ� ������ ������ �Լ��� ����� �� �� �ֵ�.
�����ڸ� ������ ���ø��� ����!
'��� �Լ� ���ø�(member function templat, ��� ���ø�)': � Ŭ������ ��� �Լ��� ���� ���ø�.;

template<typename T>
class SmartPtr {
public:
	template<typename U>		//"�Ϲ�ȭ�� ���� ������"�� ����� ���� ������ ��� ���ø�.
	SmartPtr(const SmartPtr<U>& other);
};
=> SmartPtr<T> ��ü�� SmartPtr<U>�κ��� ������ �� �ִٴ� �ڵ�.
�� ������ SmartPtr<U>�� �����ڸ� �Ű������� �޾Ƶ��̴� �����ڰ� SmartPtr<T> �ȿ� ����ִ�.

���� ���ø��� �Ἥ �ν��Ͻ�ȭ������ Ÿ���� �ٸ� Ÿ���� ��ü�κ��� ���ϴ� ��ü�� ����� �ִ� �����ڸ� ������ 
'�Ϲ�ȭ ���� ������(generalized copy constructor)'��� �θ���.

explicit�� �������� ����.
�����ʹ� ������ Ÿ�� ���� Ÿ�� ��ȯ�� �Ͻ������� �̷������ ĳ������ �ʿ����� �ʱ� ������,
����Ʈ �����͵� �̷� ���·� �����ϵ��� �䳻�� ��.


�ٸ�, ������ �ʴ� SmartPtr<Top>���κ��� SmartPtr<Bottom>�� ����ų�, SmartPtr<double>�κ��� SmartPtr<int>�� ���� �� ����.
public ����� �ǹ�(�׸� 32)�� ������!
�����ʹ� int*���� double*�� ����Ǵ� �Ͻ����� ��ȯ�� �Ұ���.

get ��� �Լ��� ���� ����Ʈ ������ ��ü�� ��ü������ ��� �⺻���� �������� �纻�� ��ȯ(�׸� 15);
template<typename T>
class SmartPtr {
public:
	template<typename U>
	SmartPtr(const SmartPtr<U>& other)		//�� SmartPtr�� ��� �����͸�
		: heldPtr(other.get()) {/*...*/}	//�ٸ� SmartPtr�� ��� �����ͷ� �ʱ�ȭ.
	T* get() const { return heldPtr; }
private:
	T *heldPtr;		//SmartPtr�� ��� �⺻���� ������
};

=> ȿ��;
SmartPtr<T>�� '�Ϲ�ȭ ���� ������'�� ȣȯ�Ǵ�(compatible) Ÿ���� �Ű������� �Ѱܹ��� ���� ������ ��.

��� �Լ� ���ø��� Ȱ���� �����ڿ��� ��ġ�� �ʴ´�.
���� ����.;
template<class T> class shared_ptr {
public:
	template<class Y>
	explicit shared_ptr(Y * p);		//ȣȯ�Ǵ� ��� �⺻���� ������.
	template<class Y>
	explicit shared_ptr(shared_ptr<Y> const& r);
	template<class Y>
	explicit shared_ptr(weak_ptr<Y> const& r);
	template<class Y>
	explicit shared_ptr(auto_ptr<Y>& r);	//����Ʈ ������ ��ü�κ��� ������ ȣ��
	template<class Y>
	explicit operator=(shared_ptr<Y> const& r);
	template<class Y>
	explicit operator=(auto_ptr<Y>& r);		//weak_ptr�� ������ ���� ���꿡 ��� (weak_ptr�� �׸� 54)
};

explicit �� �ǹ�: shared_ptr�� ���� � Ÿ�����κ��� ����Ǵ� �Ͻ��� ��ȯ�� ��������,
	�⺻���� ������ or �ٸ� ����Ʈ ������ Ÿ�����κ��� ��ȯ�Ǵ� ���� ���ڴ�.
		����� ��ȯ(ĳ���� ��)�� ok.

auto_ptr�� const ���� �� �� ����: ���� �������� ���� ��ü�� ������ �� ���� ����� �� �ϳ��� ��ȿ�ϰ� ����(�׸� 13)

�Ϲ�ȭ ���� �����ڴ� ������ ���� �����ڰ� �ƴϴ�.
���� ������ ���� ��Ʈ�� �ϰ� ������, ���� �����ڱ��� ���� ���� �ʿ�.;

template<class T> class shared_ptr {
public:
	shared_ptr(shared_ptr const& r);	//���� ������
	template<class Y> shared_ptr(shared_ptr<Y> const& r);	//�Ϲ�ȭ ���� ������

	shared_ptr& operator=(shared_ptr const& r);	//���� ���� ������
	template<class Y> shared_ptr& operator=(shared_ptr<Y> const& r);		//�Ϲ�ȭ ���� ���� ������
};

���� ����!
1. ȣȯ�Ǵ� ��� Ÿ���� �޾Ƶ��̴� ��� �Լ��� ������� ��� �Լ� ���ø��� ����սô�.
2. �Ϲ�ȭ�� ���� ���� ����� �Ϲ�ȭ�� ���� ������ ���� ��� ���ø��� �����ߴ� �ϴ���,
	������ ���� �����ڿ� ���� ���� �����ڴ� ���� �����ؾ� �Ѵ�.




�׸� 46: Ÿ�� ��ȯ�� �ٶ����� ��쿡�� ���� �Լ��� Ŭ���� ���ø� �ȿ� ������ ����!

��� �Ű������� ���� �Ͻ��� Ÿ�� ��ȯ�� �ǵ��� �ϱ� ���ؼ��� ���� �Լ��ۿ� ����� ����.
(�׸� 24) Rational Ŭ������ operator*;

template<typename T>
class Rational {
public:
	Rational(const T& numerator = 0,	//�Ű������� �����ڷ� ���޵Ǵ� ������ �׸� 20 ����
		const T& denominator = 1);
	const T numerator() const;		//��ȯ �� ������ ������ ���� ���� ������ ������ �׸� 28. const�� ������ �׸� 3
	const T denominator() const;
};

template<typename T>
const Rational<T> operator*(const Rational<T>& lhs,	const Rational<T>& rhs) { /*...*/ }

�׸� 24���� �׷���, ȥ����(mixed - mode) ��ġ ������ ������ �ʿ�.;
Rational<int> oneHalf(1, 2);		//Rational�� ���� ���ø��̶� �͸� ���� �׸� 24�� �Ͱ� �Ȱ���
Rational<int> result = oneHalf * 2;	//�׷��� ����!!

�׸� 24������ �츮�� ȣ���Ϸ��� �ϴ� �Լ��� �������� �����Ϸ��� �˰� ������(Rational ��ü �� ���� �޴� operator* �Լ�)
operator*��� �̸��� ���ø����κ��� ���� �Լ��� �����ϱ� ���� �°� ����� ������ ��.
�����Ϸ��� �ƴ� �� Rational<T> Ÿ���� �Ű����� 2������ �޾Ƶ��̴� operator* �Լ��� ��� �ν��Ͻ��� ������ �ϴµ�...
'T�� �����ΰ�?'

�����Ϸ��� �켱 operator* ȣ�� �� �Ѱ��� ������ ��� Ÿ���� ���ɴ�.
Rational<int>(oneHalf�� Ÿ��) �� int(2�� Ÿ��)
�Ű�����1 T�� int �� ���ۿ�...
�Ű�����2 T�� ?
���ø� ���� �߷�(template argument deduction) ���������� �Ͻ��� Ÿ�� ��ȯ�� ������� ����.

��� ������ �Լ�.;
template<typename T>
class Rational {
public:
	friend const Rational operator*(const Rational& lhs, const Rational& rhs);
};
template<typename T>
const Rational<T> operator*(const Rational<T>& lhs, const Rational<T>& rhs) { /*...*/ }		//operator* �Լ��� ������.

������ �Լ� ���ø��� �ƴ϶� �Լ��� ����� ��.
�����Ϸ��� �� ȣ�⹮�� ���� �Ͻ��� ��ȯ �Լ�(Rational�� ���� ȣ�� ������ ��)�� ������ �� �ְ� ��.
��, ��ũ�� �� �ȴ�...!

Ŭ���� ���ø� ���ο� ���ø��� �̸�(<> �� ��)�� ���ø� �� �Ű������� ���Ӹ��� �� �� �ִ�.
Rational<T> �ȿ����� Rational�̶�� �ᵵ Rational<T>�� ������.
�� �ڵ�� ������ ���� �ǹ�;
template<typename T>
class Rational {
public:
	const Rational<T> operator*(const Rational& lhs, const Rational& rhs);
};

Rational ���� �Ǿ� ����, ���Ǳ��� �� �Ǿ� ����.
operator* �Լ��� ������ ����ο� ���̱�.;

class Rational {
public:
	//...
	friend const Rational operator*(const Rational& lhs, const Rational& rhs) {
		return Rational(lhs.numerator() * rhs.nemerator(), lhs.denominator() * rhs.denominator());
			//�׸� 24�� �� �ڵ� ������ ����
	}
};
=> ������, ��ũ �ߵ�.

��� ���ڿ� ���� Ÿ�� ��ȯ�� �����ϵ��� �ϱ� ���� ���� �Լ��� �ʿ�(�׸� 24)
ȣ�� ���� ��Ȳ�� �´� �Լ��� �ڵ����� �ν��Ͻ�ȭ�ϱ� ���� �� ���� �Լ��� Ŭ���� �ȿ� �����ؾ�.
�����ӰԵ�, Ŭ���� �ȿ� ���� �Լ��� �����ϴ� ������ ����� '������'���� ��.
"������ �Լ��� ����̸� ȣ���ϰ� �����"

��� ���� ����;
template<typename T>
const Rational<T>  doMultiply(const Rational<T>& lhs, const Rational<T>& rhs);	//����� �Լ� ���ø��� ����.

template<typename T>
class Rational {
public:
	friend const Rational<T> operator*(const Rational<T>& lhs, const Rational<T>& rhs) {
		return doMultiply(lhs, rhs);		//������ �Լ��� ����� �Լ��� ȣ���ϰ� ����.
	}
};

��ټ� �����Ϸ��� ���ø� ���Ǹ� ��� ���Ͽ� ���� ���� ���� ��ǻ� ����.
doMultiply�� ��� ���� �ȿ� ������ �־�� �� ��. �̷� ���ø��� �ζ����� �ʿ� ����(�׸� 30)

���� ����;
template<typename T>
const Rational<T> doMultiply(const Rational<T>& lhs, const Rational<T>& rhs) {
	return Rational<T>(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}

���� ����!
1. ��� �Ű������� ���� �Ͻ��� Ÿ�� ��ȯ�� �����ϴ� ���ø��� ���谡 �ִ� �Լ��� �����ϴ� Ŭ���� ���ø��� ������� �Ѵٸ�,
	�̷� �Լ��� Ŭ���� ���ø� �ȿ� ������ �Լ��μ� �����Ѵ�.




�׸� 47: Ÿ�Կ� ���� ������ �ʿ��ϴٸ� Ư������ Ŭ������ �������!

STL�� �����̳�, �ݺ���, �˰����� ���ø����� ����.
�� �ܿ� ��ƿ��Ƽ ���ø��� �� ��.
�� �� �ϳ� advance ��� ���ø�: ������ �ݺ��ڸ� ������ �Ÿ���ŭ �̵�.;

template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d);		//iter�� d ������ŭ ������Ų��. d < 0�̸� iter�� ������Ų��.

���� ���� �ݺ��� �ۿ� += �� �� ����.
�ٸ� �ݺ��ڴ� ++�� --�� d�� �ϴ� ���ۿ�...


STL �ݺ���
1. �Է� �ݺ���(input iterator)
	: ������ ���� / �� ���� �� ĭ�� �̵� / �ڽ��� ����Ű�� ��ġ���� �б⸸ ���� / ���� �� �ִ� Ƚ�� 1��
	istream_iterator
2. ��� �ݺ���(output iterator)
	: ������ ���� / �� ���� �� ĭ�� �̵� / �ڽ��� ����Ű�� ��ġ���� ���⸸ ���� / �� �� �ִ� Ƚ�� 1��
	ostream_iterator

=> ���� �н� �˰��򿡸� ����� ��� ����

3. ������ �ݺ���(forward itator)
	: �Է�, ��� �ݺ��� �ϴ� �� ��� + �ڽ��� ����Ű�� �ִ� ��ġ���� �б�� ���⸦ ���ÿ�, ���� �� ����
	���� �н�(multi-pass) �˰��� �������� �� �� ����.
	�ؽ� �����̳�(�׸� 54) ����Ű�� �ݺ���. ���� ���� ����Ʈ�� ����ϴ� ���̺귯������ �����̳��� �ݺ���.

4. ����� �ݺ���(bidirectional iterator)
	: ������ �ݺ��� + �ڷ� �� �� �ִ� ���
	STL�� list�� ���� �ݺ���
	set, multiset, map, multimap ���� �����̳�

5. ���� ���� �ݺ���(random access iterator)
	: ����� �ݺ��� + "�ݺ��� ��� ����(iterator arithmetic)" ���� ���
	�ݺ��ڸ� ������ �Ÿ���ŭ �յڷ� �̵���Ű�� ���� ��� �ð� �ȿ� �� �� �ִ�.
	�⺻ ���� �����͸� ������ ���� ���� �ݺ��ڸ� ����.
	C++ ǥ�� ���̺귯���� vector, deque, string�� ���.

�� "�±� ����ü";
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag: public input_iterator_tag {};
struct bidirectional_iterator_tag: public forward_iterator_tag {};
struct random_access_iterator_tag: public bidirectional_iterator_tag {};


advance
�ּ� ���� �и�(lowest-common-denominator) ����
�ݺ��ڸ� �־��� Ƚ����ŭ (�� ĭ��) �ݺ������� ����, �����ϴ� ����;

template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d) {
	if (/*iter�� ���� ���� �ݺ����̴�*/) {
		iter += d;	//���� ���� �ݺ��ڿ� ���ؼ��� �ݺ��� ��� ������ ���ϴ�.
	}
	else {
		if (d >= 0) { while (d--) ++iter; }		//�ٸ� ������ �ݺ��ڿ� ���ؼ��� ++Ȥ�� --������ �ݺ� ȣ���� ����մϴ�.
		else { while (d++) --iter; }
	}
}

iter �κ��� ���� ���� �ݺ������� ��° �Ǵ��ؾ���?
'Ư������(traits)': ������ ���߿� � �־��� Ÿ���� ������ ���� �� �ְ� �ϴ� ��ü.
���� ����̸�, ����.
Ư������ ����� ������ ���� �⺻���� Ÿ�Կ� ������ �� �־�� �Ѵ�.

� Ÿ�� ���� ��ø�� ���� �����δ� ������ �� �ȴ�.
� Ÿ���� Ư�������� �� Ÿ���� �ܺο� �����Ѵ�.
���ø� �� ���ø��� 1�� �̻��� Ư��ȭ ������ �ֱ�.

�ݺ����� ���, ǥ�� ���̺귯���� Ư�������� ���ø��� iterator_traits ��� �̸����� �غ��.;

template<typename IterT>
struct iterator_traits;		//�ݺ��� Ÿ�Կ� ���� ������ ��Ÿ���� ���ø�
=> 'Ư������ Ŭ����'

���� ���� �ݺ��� deque Ŭ����(���ø�) ����;
template</*���ø� �Ű������� ���ǻ� ����*/>
class deque {
public:
	class iterator {
	public:
		typedef random_access_iterator_tag iterator_category;
	};
};

����� �ݺ��� list;
template</*...*/>
class list {
public:
	class iterator {
	public:
		typedef bidirectional_iterator_tag iterator_category;
	};
};

iterator_traits;
//IterT Ÿ�Կ� ���� iterator_category�� IterT�� �¸����� ���ϰ� �ִ� �� �״��.
//"typedef typename"�� ���� �κп� ���� ������ �׸� 42.
template<typename IterT>
struct iterator_traits {
	typedef typename IterT::iterator_category iterator_category;
};
=> �� �ڵ�� ����� ���� Ÿ���� �� ���ư���, �ݺ����� ���� Ÿ���� �������� ��쿡�� ���� �� ���ư�.
typedef Ÿ���� ��ø�� �� ���� �ȵǼ�.
iterator_traits ������ �� ��° �κ��� �ݺ��ڰ� �������� ����� ó��.

iterator_traits�� ������ Ÿ�Կ� ���� '�κ� ���ø� Ư��ȭ(partial template specialization)' ������ ������.
��� �������� ���� ������ ���� ���� �ݺ��ڿ� �Ȱ����Ƿ�, 
iterator_traits�� �̷� ������ �����ϴ� �ݺ��� ���ְ� ���� ���� �ݺ���.;

template<typename IterT>		//�⺻���� ������ Ÿ�Կ� ���� �κ� ���ø� Ư��ȭ
struct iterator_traits<IterT*> {
	typedef random_access_iterator_tag iterator_category;
};

Ư������ ���� �� ���� ���.
1. �ٸ� ����� ����ϵ��� ���� �ְ� ���� Ÿ�� ���� ���� Ȯ�� (ex. �ݺ��ڶ�� �ݺ��� ���� ��)
2. �� ������ �ĺ��� �̸� ����(ex. iterator_category).
3. �����ϰ��� �ϴ� Ÿ�� ���� ������ ���� ���ø� �� �� ���ø��� Ư��ȭ ����(ex. iterator_traits) ����.

std::iterator_traits�� �־������Ƿ� advance �ǻ��ڵ� �ٵ��.;

template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d) {
	if(typeid(typename std::iterator_traits<IterT>::iterator_category)
		== typeid(std::random_access_iterator_tag))
	//...
}
=> typeid ���. ���� ����. �̤Ѥ�
������ ������ �׸� 48.

IterT�� Ÿ���� ������ ���߿� �ľǵǱ� ������, 'iterator_traits<IterT>::iterator_category'�� �ľ��� �� ���� ���� ������ ������.
������ if���� ��Ÿ�ӿ� �򰡵�.
���� �ڵ� ũ�� ũ�� �ð� ����.

������ ���߿� �����ϴ� ����ó�� �������. '�����ε�'
�����ε�: �Ű����� ����Ʈ�� �ٸ����� f��� �̸��� ���� �����ε� ������ ���� �� �����.
�����Ϸ� "����� �ѱ� ���� Ÿ�Կ� ���� �� �´� �����ε� ������ �� �Ÿ�, �� f�� �θ� �ž�."
"�� ��°�� ���� �� ������ �� ��°, �� ��°�� ���� �� ������ �� ��°"

advance�� "���� ���� �˸���"�� �Ȱ��� �ϰ�, �޾Ƶ��̴� iterator_category ��ü�� Ÿ���� �ٸ��� �ؼ� �����ε� �Լ��� �����.
�� �����ε� �Լ��� �̸��� doAdvance��� ����.;

template<typename IterT, typename DistT>	//���� ���� �ݺ��ڿ� ���ؼ��� �� ����.
void doAdvance(IterT& iter, DistT d, std::random_access_iterator_tag) {	
	iter += d;
}

template<typename IterT, typename DistT>	//����� �ݺ���~
void doAdvance(IterT& iter, DistT d, std::bidirectional_iterator_tag) {
	if (d >= 0) { while (d--) ++iter; }
	else { while (d++) --iter; }
}

template<typename IterT, typename DistT>	//�Է� �ݺ���~
void doAdvance(IterT& iter, DistT d, std::input_iterator_tag) {
	if (d < 0) {
		throw std::out_of_range("Negative distance");
	}
	while (d--) ++iter;
}

forward_iterator_tag �� input_iterator_tag�κ��� ����� �޴� ��.
input_iterator_tag�� �Ű������� �޴� doAdvance�� ������ �ݺ��ڵ� ���� �� �ִ�.

advance�� ���� ���� �ݺ��� �� ����� �ݺ��ڿ� ���� ��� �� ���� �Ÿ��� ���� �� �ְ� �Ǿ� ������,
������, �Է� �ݺ��ڸ� ���� �Ÿ���ŭ �̵��Ϸ��� �ϸ� ������ ���� �߻�.

�����ε� �� doAdvance ȣ���ϴ� advance();
template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d) {		//iter�� �ݺ��� ���ֿ� ������ doAdvance�� �����ε� ������ ȣ��.
	doAdvance(iter, d, typename std::iterator_traits<IterT>::iterator_category());
}

Ư������ Ŭ���� How Use
1. '�۾���(worker)' ������ ���� �Լ�or�Լ� ���ø�(ex. doAdvance)�� Ư������ �Ű������� �ٸ��� �Ͽ� �����ε�.
	���޵Ǵ� �ش� Ư�������� ���߾� �� �����ε� ������ ����.
2. �۾��ڸ� ȣ���ϴ� '���۾���(master' ������ ���� �Լ�or�Լ� ���ø�(ex. advance)�� ����.
	�̶� Ư������ Ŭ�������� �����Ǵ� ������ �Ѱܼ� �۾��ڸ� ȣ���ϵ��� ����.

iterator_traits�� 
iterator_category ���� �����ϴ� �ݺ��� ���� ������ 4����
1. value_type�� �׸� 42
2. char_traits: ���� Ÿ�� ����
3. numeric_limits: ���� Ÿ�Կ� ���� ����(ǥ�� ������ �ּҰ�, �ִ밪 ��)

TR1(�׸� 54)�� ���ԵǸ鼭 Ÿ�� ���� ������ �����ϴ� Ư������ Ŭ������ ���� �߰���.
is_fundamental<T> 
	T�� �⺻���� Ÿ������ �˷���)
is_array<T>
	T�� �迭 Ÿ������ �˷���
is_base_of<T1, T2>
	T1�� T2�� ���ų� T2�� �⺻ Ŭ�������� �˷���.
���.. �߰��� �͸� �� 50��.

���� ����!
1. Ư������ Ŭ������ ������ ���� ����� �� �ִ� Ÿ�� ���� ������ ������.
	���� ���ø� �� ���ø� Ư�� ������ ����Ͽ� �����Ѵ�.
2. �Լ� �����ε� ����� �����Ͽ� Ư������ Ŭ������ ����ϸ�, 
	������ Ÿ�ӿ� �����Ǵ� Ÿ�Ժ� if...else ���˹��� ������ �� �ִ�.;




�׸� 48: ���ø� ��Ÿ���α׷���, ���� �ʰڴ°�?

'���ø� ��Ÿ���α׷���(template metaprogramming: TMP)'
	: ������ ���߿� ����Ǵ� ���ø� ����� ���α׷��� �ۼ��ϴ� ��.

TMP ���α׷��� ���� ��ģ �� => �� ����� ���� ��¹�(���ø����κ��� �ν��Ͻ�ȭ�� C++ �ҽ� �ڵ�)�� �ٽ� ������ ������ ����.

����
1. �ٸ� ������� ��ٷӰų� �Ұ����� �� �� ������
2. ���� �۾��� ��Ÿ�� �������� ������ Ÿ�� �������� ��ȯ�ϸ�,
	���� ���� ��� ������ ������ ���߿� ã�� �� ����.
	ȿ������ ������ ����(���� �ڵ� ����, ���� �ð� ����, �޸� ���� ����)

STL advance(�׸� 47);
template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d) {
	if (/*iter�� ���� ���� �ݺ����̴�*/) {
		iter += d;
	}
	else {
		if (d >= 0) { while (d--) ++iter; }
		else { while (d++) --iter; }
	}
}

Ÿ�� ������ ������ �۾��� ��Ÿ�ӿ� �غ���;
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

typeid �����ڸ� ���� ����� Ư������(traits)�� ���� ������� ȿ�� ������.
1. Ÿ�� ���� ������ ������ ������ �ƴ϶� ��Ÿ�ӿ� �Ͼ�� ����.
2. ��Ÿ�� Ÿ�� ������ �����ϴ� �ڵ�� ��¿ �� ���� ���� ���Ͽ� ���� ��.

�׸� 47���� ���� typeid ����� ������ ����;
std::list<int>::iterator iter;
advance(iter, 10);		//iter�� 10�� ���Ҹ�ŭ ������ �ű�� ������, �� ������ advance�δ� ������ �ȵ�.

void advance(std::list<int>::iterator& iter, int d) {
	if (typeid(std::iterator_traits<std::list<int>::iterator>::iterator_category) ==		//typeid ���� ����
		typeid(std::random_access_iterator_tag)) {
		iter += d;	//����!
	}
	else {
		if (d >= 0) { while (d--) ++iter; }
		else { while (d++) --iter; }
	}
}

list<int>::iterator�� ����� �ݺ��ڿ��� += �ȵ�.

TMP Ʃ�� ������.
� ���̵� ����� �� ����. ���� ����, ����, �Լ� �ۼ�, ȣ��
TMP�� ���̺귯��(�ν�Ʈ�� MPL ��. �׸� 55)

TMP�� �ݺ�(iteration) �ǹ��� ������ ������ ���� ������, ���(recursion)�� ����ؼ� ������ ȿ���� ��.

��, TMP�� ������ ��� �Լ� ȣ���� ������ �ʰ� '��ͽ� ���ø� �ν��Ͻ�ȭ(recursive template instantiation)'�� �Ѵ�.

template<unsigned n>	
struct Factorial {		//�Ϲ����� ���: Factorial<n>�� ���� Factorial<n-1>�� ���� n�� ���ؼ� ���Ѵ�.
	enum { value = n * Factorial<n-1>::value };
};
template<>		//Ư���� ���: Factorial<0>�� ���� 1�̴�.
struct Factorial<0> {
	enum { value = 1 };
};

Factorial<n>::value�� ���������ν� n�� ����� �ٷ� ���� �� ����.
��͸� ������ Ư�� ������ Factorial<0>.

Factorial ���ø��� ����ü Ÿ���� �ν��Ͻ�ȭ�ǵ��� ������� �ִ�.
����ü �ȿ� value��� �̸��� TMP ������ ����Ǿ� �ִ�.
������ �а���(enum hack)(�׸� 2)

int main() {
	std::cout << Factorial<5>::value;		//120�� ��Ÿ�� ��� ���� ���
	std::cout << Factorial<10>::value;		//3628800�� ��Ÿ�� ��� ���� ���
}


TMP ���ó
1. ġ�� ����(dimensional unit)�� ��Ȯ�� Ȯ��
���� ��� �о�... ġ�� ����(����, �Ÿ�, �ð� ��)�� �ȹٷ� ���յǾ�� �� ��
������ ���ȿ� ���纼 �� �ִ�.���� ���� Ž��(early error detection)
�м��� ���� ǥ���� ����.������ ���߿� �м��� ����� �Ǿ�� ��.time ^ 1 / 2 �� time ^ 4 / 8 �� �Ȱ��� �޾Ƶ鿩��

2. ��� ������ ����ȭ
operator* ���� ������ �Լ��� ���� ����� ���ο� ��ü�� ��� ��ȯ�ؾ� �Ѵ�.(�׸� 21);

typedef SquareMatrix<double, 10000> BigMatrix;
BigMatrix m1, m2, m3, m4, m5;		//��ĵ��� �����ϰ� �� ��Ŀ� ���� �ش�.
BigMatrix result = m1 * m2 * m3 * m4 * m5;		//��ĵ��� ���� �����.

�� ���� �ӽ� ����� ���ܾ�... operator*�� �� ���� ȣ�� �� ��ȯ... �� ���� ����...
�̷� ��� ���꿡 TMP ���.
TMP�� ������ ��� ���α׷��� ����� 'ǥ���� ���ø�(expression template)'�� ����ϸ� 
	��ġ ū �ӽ� ��ü�� ���ִ� ���� ����, �������� ���� ���� �� �ִ�.

3. ����� ������ ���� ������ ����
����(Strategy) ����, ������(Observer) ����, �湮��(Visitor) ���� ���� ������ ����
TMP�� ����� ���α׷��� ����� ��å ��� ����(policy-based design) ����ϸ�, 
���ε��� ���õ� ������� ����(��å)�� ��Ÿ���� ���ø��� ���� �� �ְ� ��.

ex. ����Ʈ ������ ���� ��å�� �ϳ��� ������ ������ ���ø��� �����,
�̵��� ����ڰ� ������� �����Ͽ� ���� ������ ����Ʈ ������ Ÿ���� ������ �� �ְ�(������ ���߿�) �ϴ� ��.
'������ ���α׷���(generative programming)'�� ����

���� ����!
1. ���ø� ��Ÿ���α׷����� ���� �۾��� ��Ÿ�ӿ��� ������ Ÿ������ ��ȯ�ϴ� ȿ��.
	TMP�� ���� ���� ���� Ž���� ���� ��Ÿ�� ȿ��.

2. TMP�� ��å ������ ���տ� ����Ͽ� ����� ���� �ڵ带 �����ϴ� �� �� �� ������,
	���� Ư�� Ÿ�Կ� ���� �������� �ڵ尡 ��������� ���� ���� ���� �� �� ����.




new �� delete �� �� �����

������ �÷��� ���� ���α׷��� ȯ�濡��,
C++�� ������ ������ ����.
�޸� �Ҵ� �� ���� ��ƾ(operator new �� operator delete)
new ó����(new-handler)�� ����

���߽����� ȯ�濡�� �޸� ������ ���� �����Ÿ�.
���� ������ ������ ���� �ڿ����� �з�.
���߽����� �ý��ۿ����� ��������� �̷� ���� �ڿ��� ��ģ ���� ����.

operator new �� delete �� ��ü �� ���� �Ҵ��� ���� ����
�迭�� ���� �޸� �Ҵ� operator new[] ���� operator delete[]

STL �����̳ʿ� ���� �� �޸� ����




�׸� 49: new ó������ ���� ������ ����� ��������

����ڰ� ���� �޸� �Ҵ� ��û�� operator new �Լ��� ���߾� ���� ���� ��� == �Ҵ��� �޸� ���� ��
	operator new �Լ��� ���ܸ� ������ �Ǿ�����.
���� ó�� �Լ� new ó����(new-handler, �Ҵ翡�� ó����) (�ڼ��� �� �׸� 51)

�޸� �� ��Ȳ�� ó���� �Լ��� ����� �ʿ��� ����.
ǥ�� ���̺귯�� set_new_handler �Լ�;

namespace std {
	typedef void(*new_handler)();
	new_handler set_new_handler(new_handler p) throw();
}
=> new_handler : �޴� �͵� ���� ��ȯ�ϴ� �͵� ���� �Լ��� �����Ϳ� ���� typedef �� �ɾ� ���� Ÿ�Ե��Ǿ�.
throw() ���� ����(exception specification): �� �Լ��� � ���ܵ� ������ ���� �� (�׸� 29)

//����� �޸𸮸� operator new �� �Ҵ����� ������ �� ȣ���� �Լ�
void outOfMem() {
	std::cerr << "Unable to satisfy request for memory\n";
	std::abort();
}
int main() {
	std::set_new_handler(outOfMem);
	int *pBigDataArray = new int[100000000L];
}
=> operator new �� 1�� ���� ���� �Ҵ翡 �����ϸ� outOfMem �Լ� ȣ��.
ȣ�� �� �޽��� ��� �� ���α׷� ���� ����.

new ó���� �Լ� �� �۵� ���� �� �� �ִ� ���۵�
1. ����� �� �ִ� �޸� �� ���� Ȯ��.
	operator new �� �õ��ϴ� ������ �޸� Ȯ���� ������ �� �ֵ��� ����.
	���α׷��� ������ �� �޸� ����� ũ�� �ϳ� �Ҵ��� ���Ҵٰ� new ó���ڰ� ���� ó�� ȣ��� �� �� �޸𸮸� �� �� �ֵ��� ���.

2. �ٸ� new ó���ڸ� ��ġ.
	������ new ó���ڴ� ���ڸ����� �ٸ� new ó���ڸ� ��ġ�� �� ����(������ new ó���� �ȿ��� set_new_handler ȣ��)
	operator new �Լ��� �ٽ� new ó���ڸ� ȣ���� ���� �Ǹ�, ���� ��ġ�� new ó���ڰ� ȣ��.

3. new ó������ ��ġ�� ����.
	set_new_handler �� �� �����͸� �ѱ��. 
	new ó���ڰ� ��ġ�� ���� ������, operator new �� �޸� �Ҵ��� �������� �� ���ܸ� ����.

4. �������� ����
	�밳 abort Ȥ�� exit ȣ��


�Ҵ�� ��ü�� Ŭ���� Ÿ�Կ� ���� �޸� �Ҵ� ���п� ���� ó���� �ٸ��� �������� ���� ��.;
class X {
public:
	static void outOfMemory();
};
class Y {
public:
	static void outOfMemory();
};
X* p1 = new X;		//�޸� �Ҵ� �������� ��� X::outOfMemory ȣ��.
Y* p2 = new Y;

set_new_handler �Լ��� ������ ����ڷκ��� �� Ŭ������ ���� ���� new ó���ڸ� �޾Ƴ��� ��.
operator new �Լ���, �� Ŭ���� ��ü�� ���� �޸𸮰� �Ҵ�Ƿ��� �� ��(�׸��� �������� ��)
	���� new ó���� ��� Ŭ���� ������ new ó���ڰ� ȣ��ǵ��� ����� ����

����: Widget Ŭ������ ���� �޸� �Ҵ� ���и� ���� ó���ϰ� ���� ���.;
class Widget {
public:
	static std::new_handler set_new_handler(std::new_handler p) throw();
	static void * operator new(std::size_t size) throw(std::bad_alloc);
private:
	static std::new_handler currentHandler;
};
new ó���ڸ� ����Ű�� new_handler Ÿ���� ���� ������ ���.
���� Ŭ���� ����� ���Ǵ� ���� Ÿ�� ��� ����� �ƴϸ� Ŭ������ �ٱ���. (�׸� 2);

std::new_handler Widget::currentHandler;	//�η� �ʱ�ȭ. Ŭ���� ���� ���Ͽ� �ξ�� ��.

set_new_handler �Լ��� �Ѿ�� �����͸� �ƹ� ���� ���� ����, ���� �����ߴ� �����͸� ���� ���� ��ȯ.;

std::new_handler Widget::set_new_handler(std::new_handler p) throw() {
	std::new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}

Widget�� operator new;

1. ǥ�� set_new_handler �Լ��� Widget�� new ó���ڸ� �Ѱܼ� ȣ��.
	��, ���� new ó���ڷμ� Widget�� new ó���ڸ� ��ġ.

2. ���� operator new ȣ���Ͽ� ���� �޸� �Ҵ��� ����.
	���� operator new �Ҵ��� �����ϸ�, �� �Լ��� Widget�� new ó���ڸ� ȣ��.
	�� �ܰ迡�� ���� new ó���ڷ� ��ġ�� �Լ��� �ٷ� �� �Լ�.
	���������� ���� operator new�� �޸� �Ҵ� �õ��� �����ϸ�, '����' �ǹ̷� bad_alloc ���� ����.
	Widgt�� operator new �� ���� new ó���ڸ� ������ ������ �ǵ��� ����, �� ���ܸ� ����.
	Widget�� ���� new ó���ڸ� �ڿ����� �����ϰ� ó��.
	(�׸� 13) �ڿ� ���� ��ü ����ؼ� ���� new ó���ڸ� �����Ͽ� �޸� ���� ����

3. ���� operator new �� Widget ��ü �ϳ���ŭ�� �޸𸮸� �Ҵ��� �� ������, Widget�� operator new�� �Ҵ�� �޸� ��ȯ.
	���� new ó���ڸ� �����ϴ� ��ü�� �Ҹ��� ȣ��.
	Widget�� operator new �� ȣ��Ǳ� ���� ���̴� ���� new ó���ڰ� �ڵ����� ����.

(�����..)

class NewHandlerHolder {
public:
	explicit NewHandlerHolder(std::new_handler nh)	//������ new ó���ڸ� ȹ��
		: handler(nh) {}
	~NewHandlerHolder() {	//�̰��� ����
		std::set_new_handler(handler);
	}
private:
	std::new_handler handler;	//�̰��� ����صα�
	NewHandlerHolder(const NewHandlerHolder&);	//���縦 ���� ���� �κ�(�׸� 14)
	NewHandlerHolder& operator=(const NewHandlerHolder&);
};

void * Widget::operator new(std::size_t size) throw(std::bad_alloc) {
	NewHandlerHolder h(std::set_new_handler(currentHandler));	//Widget�� new ó���ڸ� ��ġ
	return ::operator new(size);	//�޸𸮸� �Ҵ��ϰų�, �Ҵ��� �����ϸ� ���ܸ� ������.
									//������ ���� new ó���ڰ� �ڵ����� ������.
}

void outOfMem();	//Widget ��ü�� ���� �޸� �Ҵ��� �������� �� ȣ��� �Լ��� ����.
Widget::set_new_handler(outOfMem);	//Widget�� new ó���� �Լ��μ� outOfMem�� ��ġ.
Widget *pw1 = new Widget;	//�޸� �Ҵ��� �����ϸ� outOfMem�� ȣ���.
std::string *ps = new std::string;	//�޸� �Ҵ��� �����ϸ� ���� new ó���� �Լ��� ������ ȣ���.
Widget::set_new_handler(0);	//Widget Ŭ�������� ���� new ó���� �Լ��� �ƹ��͵� ������ ��(��, null�� ����).
Widget *pw2 = new Widget;		//�޸� �Ҵ��� �����ϸ� ������ ���ܸ� �ٷ� ����(Widget Ŭ������ ���� new ó���� �Լ��� ����).


�ٸ� Ŭ�������� �����ϰ� ��
'�ͽ���(mixin) ���'�� �⺻ Ŭ����.
	�ٸ� �Ļ� Ŭ�������� �� ������ Ư�� ��ɸ��� �����޾� �� �� �ֵ��� ����� �⺻ Ŭ���� �����.
	'Ư�� ���'�� Ŭ������ new ó���ڸ� �����ϴ� ���. �� �� �⺻ Ŭ������ ���ø����� Ż�ٲ�.
	�Ļ� Ŭ�������� Ŭ���� ������(������ new ó���ڸ� ����� �δ� ���� ��� ������)�� �纻�� ���ε��� �����ϰ� ��.

���� ���� Ŭ���� ���ø� ����
1. �⺻ Ŭ���� �κ��� �Ļ� Ŭ�������� ������ �ϴ� set_new_handler �Լ��� operator new �Լ��� ������.
	���ø� �κ��� �� �Ļ� Ŭ������(�ν��Ͻ�ȭ�� Ŭ������ �Ǹ鼭) currentHandler ������ ����� ���ε��� ���� �� �ְ� ��.;

template<typename T>
class NewHandlerSupport {	//Ŭ������ set_new_handler�� �����ϴ� "�ͽ��� ���"�� �⺻ Ŭ����.
public:
	static std::new_handler set_new_handler(std::new_handler p) throw();
	static void * operator new(std::size_t size) throw(std::bad_alloc);
	//...	//operaotr new�� �ٸ� ������ (�׸� 52)
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
//Ŭ�������� ��������� currentHandler ����� �η� �ʱ�ȭ��.
template<typename T>
std::new_handler NewHandlerSupport<T>::currentHandler = 0;

class Widget :public NewHandlerSupport<Widget> {
	//...	//������ ������, ������ set_new_handler Ȥ�� operator new�� ���� ������ ���� �ֽ��ϴ�.
};

(�����..) (�𸣰ھ�..)

Widget ...<Widget> ..?
'�ű��ϰ� �ݺ��Ǵ� ���ø� ����(curiously recurring template pattern: CRTP)'
'�� ������ ���ø��̾�..'


���ܺҰ�(nothrow) ����;
class Widget {/*...*/};
Widget *pw1 = new Widget;	//�Ҵ��� �����ϸ� bad_alloc ���� ����
if (pw1 == 0) {/*...*/ };	//�� ���� �ڵ�� �� �����Ѵ�
Widget *pw2 = new(std::nothrow) Widget;	//Widget�� �Ҵ��ϴ� �����ϸ� 0(��)�� ��ȯ��.
if(pw2 == 0) {/*...*/ };	//�� �ڵ�� ������ �� �֤�.��


���� ����!
1. set_new_handler �Լ��� ���� �޸� �Ҵ� ��û�� �������� ������ �� ȣ��Ǵ� �Լ��� ������ �� �ִ�.
2. ���ܺҰ�(nothrow) new �� ������� ���ѵǾ� �ִ�.
	�޸� �Ҵ� ��ü���� ����Ǳ� ����.
	���Ŀ� ȣ��Ǵ� �����ڿ����� �󸶵��� ���ܸ� ���� �� �ִ�.




�׸� 50: new �� delete �� ���� �ٲ�� ���� �Ҹ��� �������� �ľ��� ����!

�����Ϸ��� operator new, operator delete �� �ٲٰ� ���� ���� 3����
1. �߸��� �� ����� Ž���ϱ� ����.
	�Ҵ�� �޸� �ּ��� ����� operator new �� ������ �ΰ�, 
	operator delete �� �� ������κ��� �ּҸ� �ϳ��� ������ �ְ� �ϸ�, �Ǽ� ��.

	����: ������ ������(overrun, �Ҵ�� �޸� ����� ���� �Ѿ� ����ϴ� ��)
		�����(underrun, �Ҵ�� �޸� ����� ������ �Ѿ� �տ� ����ϴ� ��)

	������/����� Ž���� ����Ʈ ����[�ϸ� "���ǥ��(signature)"]�� ����ε��� ���� �� ����.

2. ȿ���� ����Ű�� ����
	���� �Լ��� �Ϲ����� ���ӻ��� ���� ��
		: ����ð� �� ���α׷�, ª�� ���α׷�, �� ����ȭ(fragmentation)�� ���� ��ó��� ��
	�⺻���� �������� ���� ���� �� ����� ������ �� Ȯ���� ����.

3. ���� �Ҵ� �޸��� ���� ��뿡 ���� ��� ������ �����ϱ� ����
	: ���� ����, �� ���� ���̴� ���� �Ҵ� �޸��� �ִ뷮[�ٸ� ���� "�ְ�� ����(high water mark)"] ��� �ľ�

���� ������, ����� Ž���ϱ� ���� ���� opertor new �����
����;
static const int signature = 0xDEADBEEF;
typedef unsigned char Byte;
//�� �ڵ�� ���ľ� �� �κ� �� �� ����.
void* operator new(std::size_t size) throw(std::bad_alloc) {
	using namespace std;
	size_t realSize = size + 2 * sizeof(int);	//���ǥ�� 2���� �յڿ� ���� �� ���� ��ŭ�� �޸� ũ�⸦ �ø���.

	void *pMem = malloc(realSize);	//malloc�� ȣ���Ͽ� ���� �޸𸮸� ��.
	if (!pMem) throw bad_alloc();

	//�޸� ����� ���� �� ���κп� ���ǥ���� ����Ѵ�.
	*(static_cast<int*>(pMem)) = signature;
	*(reinterpret_cast<int*>(static_cast<Byte*>(pMem) + realSize - sizeof(int))) = signature;
	//���� ���ǥ�� �ٷ� ������ �޸𸮸� ����Ű�� �����͸� ��ȯ.
	return static_cast<Byte*>(pMem) + sizeof(int);
}
=> new ó���ڸ� ȣ���ϴ� ���� ����. �̰� �׸� 51.
�� �ϳ��� ����, ����Ʈ ����(alignment)

��ǻ�� �ּ� ��Ű���� �䱸���׵�
�����ʹ� 4����Ʈ ������ ����, double �� 8����Ʈ ������ ���� ���


�ν�Ʈ�� Ǯ(Pool) ���̺귯�� (�׸� 55)
�� ���̺귯���� �޸� �Ҵ��ڴ� ũ�Ⱑ ���� ���� ��ü�� ���� �Ҵ��� ��쿡 ����.
(����Ʈ ���� ������� TR1(�׸� 54)�� ����)

���� new �� delete �� �⺻���� ������ �ٸ� ������ ��ü?
1. �߸��� �� ��� Ž��.
2. ���� �Ҵ� �޸��� ���� ��뿡 ���� ��� ������ ����.
3. �Ҵ� �� ���� �ӷ��� ���̱� ����.
	������ ũ���� ��ü�� ����� �ִ� �Ҵ����� �������� ���� ���� �ٷ� Ŭ���� ����(class-specific) �Ҵ���.
	
4. �⺻ �޸� �������� ���� ������带 ���̱� ����

5. ������ Ÿ���� �⺻ �Ҵ����� ����Ʈ ���� ������ �����ϱ� ����.
	x86 ��Ű��ó�� double 8����Ʈ ������ ���� ������, ��� �����Ϸ��� operator new �� ���� ���� �� ��.

6. ������ ���踦 �ΰ� �ִ� ��ü���� �� ���� ������ ��� ���� ����
	���� �ڷᱸ�� ��� ���� ��..
	������ ����(page fault) �߻� Ƚ�� �ּ�ȭ�ϰ� ���� ��, �ڷᱸ���� ���� ������ ���� ����.
	�޸� ����ȭ�� ��ġ ����(placement) new �� ��ġ���� delete �� ���� ���� ����

7. �׶��׶� ���ϴ� ������ �����ϵ��� �ϱ� ����
	���� �޸� ����. C API�ιۿ� �� �� ���� ��
	�������� ���� ��ȭ�� ���� ������ �޸� ��Ͽ� 0�� ����� ��� ��


���� ����!
1. �����ڰ� ������ ����� ���� new �� delete �� �ۼ��ϴ� ���� ���� ���� ������� Ÿ���� ������ �ִ�.
	���༺�� ��� / �� ��� �� ���� ����� / �� ��� ���� ���� ���� ��;




�׸� 51: new �� delete �� �ۼ��� �� ����� �� ������ ���ʸ� �� �˾� ����

����� ���� ���� operator new, operator delete ����
	��ȯ ���� ����� / ���� �޸� ���� �� new ó���� �Լ� ȣ��(�׸� 49) / ũ�Ⱑ ����(0����Ʈ) �޸� ��û�� ���� ���å
	�Ǽ��� '�⺻(normal' ������ new �� �������� �ʵ���. (�׸� 52)

��ȯ ��
��û�� �޸𸮸� ������ �� �� ������ �� �޸𸮿� ���� �����͸� ��ȯ.
���� ���ϸ� bad_alloc ���� (�׸� 49)

but, ���� �� new ó���� �Լ� ȣ���ϴ� ������ �޸� �Ҵ��� 2ȸ �̻� �õ��ϱ� ������ �����.
new ó���� �Լ��� ���� �����Ͱ� ���� ��;

void * operator new(std::size_t size) throw(std::bad_alloc) {	//operator new �Լ��� �ٸ� �Ű������� �߰��� ���� �� ����
	using namespace std;
	if (size == 0) {	//0����Ʈ ��û�� ������, �̰��� 1����Ʈ �䱸�� �����ϰ� ó��.
		size = 1;
	}
	while (true) {
		//size ����Ʈ�� �Ҵ��� ��.
		if (/*�Ҵ��� ��������*/) {
			return /*�Ҵ�� �޸𸮿� ���� ������*/;
		}
		//�Ҵ��� �������� ���, ������ new ó���� �Լ��� ��� ������ �����Ǿ� �ִ��� ã�Ƴ���.
		new_handler globalHandler = set_new_handler(0);
		set_new_handler(globalHandler);
		
		if (globalHandler) (*globalHandler)();
		else throw std::bad_alloc();
	}
}


�Ļ� Ŭ���� ��ü�� ���� �޸𸮸� �Ҵ��ϴ� �� �⺻ Ŭ������ operator new �Լ��� ȣ���.;
class Base {
public:
	static void * operator new(std::size_t size) throw(std::bad_alloc);
};
class Derived:public Base {/*...*/ };	//Derived���� operator new�� ������� ����

Derived *p = new Derived;	//Base::operator new �� ȣ���.


Ʋ�� �޸� ũ�Ⱑ ������ �� ���� �κп��� Ȯ���� ǥ�� operator new �� ȣ���ϴ� ��;

void * Base::operator new(std::size_t size) throw(std::bad_alloc) {
	if (size != sizeof(Base)) {		//Ʋ�� ũ�Ⱑ ������, ǥ�� operator new�ʿ��� �޸� �Ҵ� �䱸�� ó���ϵ��� �ѱ�. (0����Ʈ ���˵� ��)
		return ::operator new(size);
		//... //�´� ũ�Ⱑ ������, �޸� �Ҵ� �䱸�� ���⼭ ó��
	}
}

C++���� ��� ���� ����(freestanding)�� ��ü�� �ݵ�� ũ�Ⱑ 0�� �Ѿ�� �Ѵٴ� ��Ģ(�׸� 39)
sizeof(Base)�� 0�ʰ�.


�迭�� '�迭 new(array new) operator new[]' ��� �ҷ�.
�Ļ� Ŭ���� ��ü�� �⺻ Ŭ���� ��ü���� �� ũ�� ������,
�䱸�� ����Ʈ �� / sizeof(Base)�� ��ü�� ���� ��� �Ұ���

operator new ���� ��.
operator delete ���� ����.

�� �����Ϳ� ���� delete ������ �����ϴٴ� ��� ����.;
void operator delete(void *rawMemory) throw() {
	if (rawMemory == 0) return;		//�� �����Ͱ� delete�Ƿ��� �� ��쿡�� �ƹ��͵� ���� �ʰ� ��.
	//rawMemory�� ����Ű�� �޸𸮸� ����.
}

operaotr delete ���� 'Ʋ�� ũ��� �Ҵ��' �޸��� ��û�� ::operator delete ������ ����;
class Base {	//������ ������, operator delete�� ����� ����.
public:
	static void * operator new(std::size_t size_ throw(std::bad_alloc));
	static void operator delete(void *rawMemory, std::size_t size) throw();
};
void Base::operator delete(void *rawMemory, std::size_t size) throw() {
	if (rawMemory == 0) return;		//�� �����Ϳ� ���� ����
	if (size != sizeof(Base)) {		//ũ�Ⱑ 'Ʋ��' ���, ǥ�� operator delete�� �޸� ���� ��û�� �õ��� ��.
		::operator delete(rawMemory);
		return;
	}
	//rawMemory�� ����Ű�� �޸𸮸� ����.
	return;
}

���� �Ҹ��ڰ� ���� �⺻ Ŭ�����κ��� �Ļ��� Ŭ������ ��ü�� �����Ϸ��� �� ���, 
	operator delete �� C++�� �ѱ�� size_t ���� �߸��� �� �ִ�.
	=> ���� �Ҹ��ڸ� �� �־�� �� ��� (�׸� 7)


���� ����!
1. ����������, operator new �Լ��� �޸� �Ҵ��� �ݺ��ؼ� �õ��ϴ� ���� ������ ������ �ϰ�,
	�޸� �Ҵ� �䱸�� ������ų �� ���� �� new ó���ڸ� ȣ���ؾ� �ϸ�,
	0����Ʈ�� ���� ��å�� �־�� ��.
	Ŭ���� ���� ������ �ڽ��� �Ҵ��ϱ�� ������ ũ�⺸�� �� ū(Ʋ��) �޸� ��Ͽ� ���� �䱸�� ó���ؾ� �Ѵ�.

2. operator delete �Լ��� �� �����Ͱ� ������ �� �ƹ� �ϵ� ���� �ʾƾ� ��.
	Ŭ���� ���� ������ ��쿡�� ���� ũ�⺸�� �� ū ����� ó���ؾ� �Ѵ�.




�׸� 52: ��ġ���� new �� �ۼ��Ѵٸ� ��ġ���� delete �� ���� �غ�����.;

Widget *pw = new Widget;
�� �Լ� 2���� ȣ��.
1. operator new
2. Widget�� �⺻ ������.

2�� �� ���� �߻� �� �޸� ����!
C++ ��Ÿ�� �ý����� ����� �˰� ������ delete ȣ�� ����.

�⺻��;
void* operator new(std::size_t) throw(std::bad_alloc);

void* operator delete(void *rawMemory) throw();	///���� ��ȿ���������� �⺻�� �ñ״�ó
void operator delete(void *rawMemory, std::size_t size) throw();	//�������� �⺻�� �ñ״�ó

��� new �� delete ¦ ���� ?
���� : operator new ����� ���� / operator delete �⺻��
	�޸� �Ҵ� ������ �α׷� ���;
class Widget {
public:
	static void* operator new(std::size_t size, std::ostream& logStream)
		throw(std::bad_alloc);	//��ǥ�� ������ operator new
	static void operator delete(void *pMemory, size_t size) throw();		//Ŭ���� ���� operator delete�� ǥ�� ����
};

'��ġ����(placement) new'
	�Ű������� �߰��� �޴� operator new.

������ ����: � ��ü�� ������ų �޸� ��ġ�� ��Ÿ���� �����͸� �Ű������� �޴� ��;
void* operator new(std::size_t, void *pMemory) throw();		//��ġ���� new
C++ ǥ�� ���̺귯��. <new> ����� ����
���ó: vector�� �̻�� ������ ���� ��ü�� ������ ��


Widget *pw = new(std::cerr) Widget;		//operator new�� ȣ���ϴ� �� cerr�� ostream ���ڷ� �ѱ�µ�,
										//�̶� Widget �����ڿ��� ���ܰ� �߻��ϸ� �޸𸮰� �����.

��Ÿ�� �ý����� ȣ��� operator new �� �޾Ƶ��̴� '�Ű������� ���� �� Ÿ���� �Ȱ���' ������
operator delete �� ã�Ƴ��� ȣ��
�� �ڵ�� ostream& Ÿ���� �Ű������� �߰��� �޾Ƶ��̹Ƿ� �Ȱ��� �ñ״�ó�� operator delete �ʿ�.
��ġ ���� ���� ���µ� (Widget �����ڰ� ���ܸ� ������) � operator delete �� ȣ����� ����.

void operaotr delete(void *, std::ostream&) throw();
'��ġ���� delete';

class Widget {
public:
	static void* operator new(std::size_t size, std::ostream& logStream)
		throw(std::bad_alloc);	//��ǥ�� ������ operator new
	static void operator delete(void *pMemory) throw();
	
	static void operator delete(void *pMemory, std::ostream& logStream) throw();
};

Widget *pw = new (std::cerr) Widget;	//������ ���� ����� �ڵ�. ������ �޸� ���� ����.

delete pw;		//�⺻���� operator delete �� ȣ���.
��ġ���� ������ ȣ������ �ʴ´�.
ȣ��Ǵ� �����ڿ��� ���ܰ� �߻����� ����.
��ġ���� new �Լ� - ǥ�� operator delete - ��ġ���� delete ��� �ۼ�.


�̸� ������ ���� ����(�׸� 33);

class Base {
public:
	static void* operator new(std::size_t size, std::ostream& logStream)	//�� new�� ǥ�� ������ ���� new�� �����ϴ�.
		throw(std::bad_alloc);
	//...
};
Base *pb = new Base;	//����! ǥ�� ������ ���� new�� ��������
Base *pb = new (std::cerr) Base;	//���� ����. ��ġ���� new ȣ��

�Ļ� Ŭ����;
class Derived : public Base {
public:
	static void* operator new(std::size_t size)	//�⺻�� new�� Ŭ���� �������� �ٽ� ����.
		throw(std::bad_alloc);
	//...
};
Derived *pd = new (std::clog) Derived;	//����! Base�� ��ġ���� new�� ������ �ֱ� ����.
Derived *pd = new Derived;	//���� ����. Derived�� operator new�� ȣ��.


���� ��ȿ �������� �����ϴ� operator new�� ���� 3����
void* operator new(std::size_t) throw(std::bad_alloc);			//�⺻��
void* operator new(std::size_t, void*) throw();					//��ġ����
void* operator new(std::size_t, const std::nothrow_t*) throw();	//���ܺҰ�(�׸� 49)


�⺻ Ŭ������ new �� delete ���� ���� �ֱ� ���;
class StandardNewDeleteForms {
public:
	//�⺻�� new/delete
	static void* operator new(std::size_t size) throw(std::bad_alloc) {
		return ::operator new(size);
	}
	static void operator delete(void *pMemory) throw() {
		::operator delete(pMemory);
	}
	//��ġ���� new/delete
	static void* operator new(std::size_t size, void *ptr) throw() {
		return ::operator new(size, ptr);
	}
	static void operator delete(void *pMemory, void *ptr) throw() {
		::operator delete(pMemory, ptr);
	}
	//���ܺҰ� new/delete
	static void* operator new(std::size_t size, const std::nothrow_t& nt) throw() {
		return ::operator new(size, nt);
	}
	static void operator delete(void *pMemory, const std::nothrow_t&) throw() {
		::operator delete(pMemory);
	}
};

����� ���� ���� �߰�: ��Ӱ� using ����
ǥ�� ���¸� �Ļ� Ŭ���� ������ ����� �ܺο��� ����� �� �ְ� �����;

class Widget : public StandardNewDeleteForms {	//ǥ�� ���� �����ޱ�
public:
	using StandardNewDeleteForms::operator new;	//ǥ�� ���°� Widget ���ο� ���̵��� �����
	using StandardNewDeleteForms::operator delete;
	static void* operator new(std::size_t size, std::ostream& logStream) throw(std::bad_alloc);	//����� ���� ��ġ���� new �߰�
	static void operator delete(void *pMemory, std::ostream& logStream) throw();	//���� �Ͱ� ¦�� �Ǵ� ��ġ���� delete �߰�.
};

���� ����!
1. operator new �Լ��� ��ġ����(placement) ������ ���� ����, ��ġ���� operator delete �� �����.
	����� �� ����� �ϴ� �޸� ���� ����
2. new, delete ��ġ���� ���� ���� ��, ǥ�� ������ �������� �ʵ��� �ϱ�.




���� ����!
�����Ϸ� ��� ����ġ�� �ʱ�.
�����Ϸ� ��� �ʹ� ����� �ʱ�

���� C++ ǥ�� ���̺귯��: STL, iostream, ������ ��
TR1 ���Ժ귯��: ����Ʈ ������, �Ϲ�ȭ �Լ� ������, �ؽ� ��� �����̳�, ���� ǥ���� �� 10��
�ν�Ʈ: ���̺귯�� ����Ʈ
�̾߱� ���


��