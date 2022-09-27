#include <iostream>
using namespace std;

template<typename T>
class Stack
{
public:
	T* arr;
	int size;

private:
	int capacity;

public:
	Stack()
	{
		arr = new T[2];
		size = 0;
		capacity = 2;
	}
	~Stack()
	{
		if (arr) delete[] arr;
	}

public:
	void push(T num)
	{
		if (isFull())
		{
			capacity *= 2;
			T* temp = new T[capacity];
			for (int i = 0; i < size; i++)
			{
				temp[i] = arr[i];
			}
			delete[] arr;
			arr = new T[capacity];
			copy(temp, temp + size, arr);
		}

		arr[size++] = num;
	}

	T pop()
	{
		if (isEmpty())
		{
			cout << "비어있어서 pop 불가\n";
			exit(1);
		}
		T temp = arr[size - 1];
		arr[size - 1] = -1;
		size--;
		return temp;
	}

	bool isEmpty()
	{
		return size == 0;
	}

	T top()
	{
		return arr[size - 1];
	}

	void print()
	{
		for (int i = size - 1; i >= 0; i--)
		{
			cout << arr[i] << ' ';
		}
	}

private:
	bool isFull()
	{
		return size >= capacity;
	}
};

/*
int main()
{
	Stack<char> st;
	st.push('a');
	st.push('b');
	st.push('c');
	st.push('d');
	st.print();
}
*/

class Postfix
{
public:
	bool isOperand(char ch)
	{
		return ch >= '0' && ch <= '9';
	}

	bool isOperator(char ch)
	{
		string operators = "+-*/%";
		return strchr(operators.c_str(), ch);
	}

	int prec(char ch)
	{
		switch (ch)
		{
		case '+':
		case '-':
			return 1;
		case '%':
		case '*':
		case '/':
			return 2;
		}
		return -1;
	}

	bool infixToPostfix(string& exp)
	{
		Stack<char> st;
		int iPostfix = -1;

		for (size_t i = 0; i < exp.size(); i++)
		{
			if (isOperand(exp[i]))
			{
				exp[++iPostfix] = exp[i];
			}
			else if (exp[i] == '(')
			{
				st.push(exp[i]);
			}
			else if (exp[i] == ')')
			{
				while (!st.isEmpty() && st.top() != '(')
				{
					exp[++iPostfix] = st.pop();
				}
				if (!st.isEmpty() && st.top() != '(')
				{
					return false;
				}
				else
				{
					st.pop();
				}
			}
			else if (isOperator(exp[i]))
			{
				while (!st.isEmpty() && prec(exp[i]) <= prec(st.top()))
				{
					exp[++iPostfix] = st.pop();
				}
				st.push(exp[i]);
			}
		}

		while (!st.isEmpty())
		{
			exp[++iPostfix] = st.pop();
		}
		for (int i = iPostfix + 1; i < exp.size(); i++)
		{
			exp[i] = '\0';
		}
		return true;
	}

	int evalPostfixExpression(string& exp)
	{
		Stack<int> st;
		char ch;
		int operand1, operand2;

		for (size_t i = 0; i < exp.size(); i++)
		{
			ch = exp[i];

			if (isOperand(ch))
			{
				st.push(ch - '0');
			}
			else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
			{
				operand2 = st.pop();
				operand1 = st.pop();

				switch (ch)
				{
				case '+': st.push(operand1 + operand2); break;
				case '-': st.push(operand1 - operand2); break;
				case '*': st.push(operand1 * operand2); break;
				case '/': st.push(operand1 / operand2); break;
				case '%': st.push(operand1 % operand2); break;
				}
			}
		}
		return st.pop();
	}
};

int main()
{
	int result = 0;
	
	string exp[8] = { 
		"4*5+1",
		"3+4*(5+1)",
		"3+4-5",
		"(4+5)*6",
		"3 * 4 / 5 * 6",
		"4 + 4 / (8 - 2)",
		"5%2 + 3 % 6",
		"1 + (2 + 3 * 4 / (5 - 6)) - 7"
	};

	Postfix pf;

	for (auto& elem : exp)
	{
		cout << elem << " = ";
		pf.infixToPostfix(elem);
		cout << elem << " = ";
		result = pf.evalPostfixExpression(elem);
		cout << result << '\n';
	}
}