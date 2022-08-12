// Vector.h -- ��� ���¿� <<�� ����ϴ�, Vector Ŭ����
#pragma once;
#include <iostream>

namespace VECTOR
{
	class Vector
	{
	public:
		enum Mode { RECT, POL };
		// ���簢���� ���ؼ��� RECT��, Polar modes�� ���ؼ��� POL�� ����Ѵ�
	private:
		double x;	// ���� ����
		double y;	// ���� ����
		double mag;	// ������ ����
		double ang;	// ����(��)�� ǥ�õǴ� ������ ����
		Mode mode;	// POL�� ���ؼ� RECT�� (RECT �Ǵ� POL)
		// ���� �����ϴ� private �޼����
		void set_mag();
		void set_ang();
		void set_x();
		void set_y();
	public:
		Vector();
		Vector(double n1, double n2, Mode form = RECT);
		void reset(double n1, double n2, Mode form = RECT);
		~Vector();
		double xval() const { return x; }
		double yval() const { return y; }
		double magval() const { return mag; }
		double angval() const { return ang; }
		void polar_mode();		// ��带 'p'�� �����Ѵ�
		void rect_mode();		// ��带 'r'�� �����Ѵ�
		// ������ �����ε�
		Vector operator+(const Vector& b) const;
		Vector operator-(const Vector& b) const;
		Vector operator-() const;
		Vector operator*(double n) const;
		// ������ �Լ�
		friend Vector operator*(double n, const Vector& a);
		friend std::ostream& operator<< (std::ostream & os, const Vector & v);
	};
}


// Vector.cpp
#include <cmath>
// #include "Vector.h"
using std::sqrt;
using std::sin;
using std::cos;
using std::atan;
using std::atan2;
using std::cout;

namespace VECTOR
{
	// 1 ���� ���� ������ ����ض� (1 ���ȿ� ���� degree �� ���)
	const double Rad_to_deg = 45.0 / atan(1.0);
	// �ݵ�� 57.2957785130823 ���� �Ǿ�� ��

	// private �޼����
	// x���� y������ ũ�⸦ ����Ѵ�.
	void Vector::set_mag()
	{
		mag = sqrt(x * x + y * y);
	}
	void Vector::set_ang()
	{
		if (x == 0.0 && y == 0.0)
			ang = 0.0;
		else
			ang = atan2(y, x);
	}

	// �� ��ǥ�� ����Ͽ� x�� �����Ѵ�.
	void Vector::set_x()
	{
		x = mag * cos(ang);
	}
	// ~ y ~
	void Vector::set_y()
	{
		y = mag * sin(ang);
	}

	// public
	Vector::Vector()
	{
		x = y = mag = ang = 0.0;
		mode = RECT;
	}

	// form�� r�̸� ���� ��ǥ�κ��� ���͸� �����Ѵ�.
	// form�� p�̸� �� ��ǥ�κ��� ���͸� �����Ѵ�.
	Vector::Vector(double n1, double n2, Mode form)
	{
		reset(n1, n2, form);
	}

	// form�� RECT�̸� ���� ��ǥ�κ��� ���͸� �����Ѵ� (����Ʈ)
	// form�� POL�̸� �� ��ǥ�κ��� ���͸� �����Ѵ�.
	void Vector::reset(double n1, double n2, Mode form)
	{
		mode = form;
		if (form == RECT)
		{
			x = n1;
			y = n2;
			set_mag();
			set_ang();
		}
		else if (form == POL)
		{
			mag = n1;
			ang = n2 / Rad_to_deg;
			set_x();
			set_y();
		}
		else
		{
			cout << "Vector()�� ���޵� �� 3�� �Ű������� �߸��Ǿ���.\n";
			cout << "�׷��� ���͸� 0���� �����ߴ�.\n";
			x = y = mag = ang = 0.0;
			mode = RECT;
		}
	}

	Vector::~Vector() {}

	void Vector::polar_mode()	// �� ��ǥ ���� �����Ѵ�.
	{
		mode = POL;
	}

	void Vector::polar_mode()	// ���� ~
	{
		mode = RECT;
	}

	// ������ �����ε�
	Vector Vector::operator+(const Vector& b) const
	{
		return Vector(x + b.x, y + b.y);
	}

	Vector Vector::operator-(const Vector& b) const
	{
		return Vector(x - b.x, y - b.y);
	}

	Vector Vector::operator-() const
	{
		return Vector(-x, -y);
	}

	Vector Vector::operator*(double n) const
	{
		return Vector(n * x, n * y);
	}

	Vector operator*(double n, const Vector& a)
	{
		return a * n;
	}

	// mode�� RECT�� ���� ��ǥ�� ���
	// ~ POL ~ �� ~
	std::ostream& operator<<(std::ostream& os, const Vector& v)
	{
		if (v.mode == Vector::RECT)
			os << "(x,y) = (" << v.x << ", " << v.y << ")";
		else if (v.mode == Vector::POL)
		{
			os << "(m,a) = (" << v.mag << ", "
				<< v.ang * Rad_to_deg << ")";
		}
		else
			os << "Vector ��ü�� ��� ������ Ʋ�Ƚ��ϴ�.\n";
		return os;
	}
}

// randwalk.cpp
#include <cstdlib>
#include <ctime>
// #include "Vector.h"

int main()
{
	using namespace std;
	using VECTOR::Vector;
	srand(time(0));
	double direction;
	Vector step;
	Vector result(0.0, 0.0);
	unsigned long steps = 0;
	double target;
	double dstep;
	cout << "��ǥ �Ÿ��� �Է�(�������� q): ";
	while (cin >> target)
	{
		cout << "������ �Է�: ";
		if (!(cin >> dstep))
			break;

		while (result.magval() < target)
		{
			direction = rand() % 360;
			step.reset(dstep, direction, Vector::POL);
			result = result + step;
			steps++;
		}
	}
}