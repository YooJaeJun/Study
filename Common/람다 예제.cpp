
//[capture list ](parameters .. ) { function body };
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

/*
int main()
{
	[]	//lambda capture
	()	//�Լ��� �μ�����
	{}	//�Լ��� ��ü
	()	//�Լ� ȣ��
}
*/


int main() {

	/// <summary>
	/// ���� ����: ����
	/// </summary>
	/// <returns></returns>
	/// 
	std::vector<int> v = { 1,2,3,41,4,1,56,1,2,3 };

	sort(begin(v), end(v), [](int l, int r) {
		auto is_odd = [](int value) {
			return value % 2 == 0;
		};

		if (is_odd(l) && !is_odd(r)) {
			return true;
		}

		if (!is_odd(l) && is_odd(r)) {
			return false;
		}
		return false;
	});

	for (int i : v) {
		std::cout << i << std::endl;
	}
	return 0;


	/////
	// ���� ����
	/////
	auto func1 = [] {return 3.14; };
	auto func2 = [](float f) {return f; };
	auto func3 = []()->float {return 3.14; };

}

//���� ��
/*
#include <vector>
#include <algorithm>
int main() {
   std::vector<int> v = { 1,2,3,41,4,1,56,1,2,3 };

   auto odd = [](int l, int r) {
	  auto is_odd = [](int value){
		 return value % 2 == 0;
	  };

	  if (is_odd(l) && !is_odd(r)) {
		 return true;
	  }

	  if (!is_odd(l) && is_odd(r)) {
		 return false;
	  }

	  return false;
   };

   sort(begin(v), end(v), odd);
   for (int i : v) {
	  std::cout << i << std::endl;
   }
   return 0;
}
*/

int main() {
	const char* str = "yjj\n";
	auto my_func = [str]() {
		std::cout << str;
	};
	return 0;
}



int main() {
	int a;
	auto my_func = [&a]() {
		a++;
		std::cout << a;
	};
	return 0;
}




///
/// lambda�� ��ȯ�ϴ� �Լ�
/// 

std::function<void()>f() {
	std::string str("lambda");
	return[=] {std::cout << "Hello. " << str << std::endl; };
}

int main() {
	auto func = f();
	func();
	f()();
}




///
/// capture ����
/// 
int main() {
	int x = 100;
	[&]() { std::cout << x << std::endl;
		x = 200;
		}();
	
	std::cout << x << std::endl;
	getchar();
	return 0;
}