#include <iostream>

using namespace std;

class A
{
	virtual void Print() {}
};

class B : public A
{
	virtual void Print() override {}
	void Hi() {}
};


int main()
{
	A* a = new A();
	B b2;

	B* b = static_cast<B*>(a);

	//a = &b2;
	if (B* b = (B*)a)
		cout << "null พฦดิ\n";
	else
		cout << "null\n";

	//a = &b2;
	if (B* b = static_cast<B*>(a))
		cout << "null พฦดิ\n";
	else
		cout << "null\n";

	//a = &b2;
	if (B* b = dynamic_cast<B*>(a))
		cout << "null พฦดิ\n";
	else
		cout << "null\n";

	return 0;
}