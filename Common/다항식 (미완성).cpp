#include <iostream>
#include <cstdio>
using namespace std;

const int maxDegree = 80;

//���׽� Ŭ����
class polynomial {
public:
	polynomial() : degree(0) {
		for (float& elem : coef) {
			elem = 0.0f;
		}
	}
	void read() {
		while (degree < 1) {
			printf("���׽� �ְ� ����(�ڿ���): ");
			scanf_s("%d", &degree);
			if (degree < 1) {
				printf("�ڿ����� �Է����ּ���.");
			}
		}
		printf("�� ���� ��� �Է�(�ְ� %d��): ", degree + 1);
		for (int i = degree; i >= 0; i--) {
			scanf_s("%f", &coef[i]);
		}
	}
	void display() {
		printf("���׽� ���: \n");
		for (int i = degree; i != 0; i--) {
			printf("%dx^%d + ", (int)coef[i], i);
		}
		printf("%d\n", (int)coef[0]);
	}
	bool isZero() {
		return degree == 0;
	}
	void negate() {
		for (float& elem : coef) {
			elem *= -1;
		}
	}
	void add(polynomial p1, polynomial p2) {
		if (p1.degree > p2.degree) {
			degree = p1.degree;
			for (int i = 0; i <= p1.degree; i++) {
				coef[i] = p1.coef[i] + p2.coef[i];
			}
		}
		else {
			degree = p2.degree;
			for (int i = 0; i <= p2.degree; i++) {
				coef[i] = p1.coef[i] + p2.coef[i];
			}
		}
	}
	void mult(polynomial p1, polynomial p2) {

	}
private:
	int degree;
	float coef[maxDegree];
};



struct term {
	int expon;	//����
	float coeff;	//���
};

const int maxTerms = 80;

//��� ���׽� Ŭ����
class sparsePoly {
public:
	sparsePoly() : nTerms(0) {
		for (term& elem : terms) {
			elem = { 0, 0.0f };
		}
	}
private:
	int nTerms;	//����� 0�� �ƴ� ���� ����
	term terms[maxTerms];	//����� 0�� �ƴ� ���� �迭
};




void main() {
	polynomial p1;
	polynomial p2;
	p1.read();
	p1.display();
	p2.read();
	p2.display();

	p1.add(p1, p2);
	p1.display();

	p1.negate();
	p1.display();
}