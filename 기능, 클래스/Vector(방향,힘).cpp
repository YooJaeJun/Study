// Vector.h -- 모드 상태와 <<를 사용하는, Vector 클래스
#pragma once;
#include <iostream>

namespace VECTOR
{
	class Vector
	{
	public:
		enum Mode { RECT, POL };
		// 직사각형을 위해서는 RECT를, Polar modes를 위해서는 POL을 사용한다
	private:
		double x;	// 수평 성분
		double y;	// 수직 성분
		double mag;	// 벡터의 길이
		double ang;	// 방위(도)로 표시되는 벡터의 방향
		Mode mode;	// POL을 위해서 RECT를 (RECT 또는 POL)
		// 값을 설정하는 private 메서드들
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
		void polar_mode();		// 모드를 'p'로 설정한다
		void rect_mode();		// 모드를 'r'로 설정한다
		// 연산자 오버로딩
		Vector operator+(const Vector& b) const;
		Vector operator-(const Vector& b) const;
		Vector operator-() const;
		Vector operator*(double n) const;
		// 프렌드 함수
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
	// 1 라디안 내의 각도를 계산해라 (1 라디안에 대한 degree 값 계산)
	const double Rad_to_deg = 45.0 / atan(1.0);
	// 반드시 57.2957785130823 값이 되어야 함

	// private 메서드들
	// x값과 y값으로 크기를 계산한다.
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

	// 극 좌표를 사용하여 x를 설정한다.
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

	// form이 r이면 직각 좌표로부터 벡터를 구성한다.
	// form이 p이면 극 좌표로부터 벡터를 구성한다.
	Vector::Vector(double n1, double n2, Mode form)
	{
		reset(n1, n2, form);
	}

	// form이 RECT이면 직각 좌표로부터 벡터를 구성한다 (디폴트)
	// form이 POL이면 극 좌표로부터 벡터를 구성한다.
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
			cout << "Vector()에 전달된 제 3의 매개변수가 잘못되었다.\n";
			cout << "그래서 벡터를 0으로 설정했다.\n";
			x = y = mag = ang = 0.0;
			mode = RECT;
		}
	}

	Vector::~Vector() {}

	void Vector::polar_mode()	// 극 좌표 모드로 설정한다.
	{
		mode = POL;
	}

	void Vector::polar_mode()	// 직각 ~
	{
		mode = RECT;
	}

	// 연산자 오버로딩
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

	// mode가 RECT면 직각 좌표를 출력
	// ~ POL ~ 극 ~
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
			os << "Vector 객체의 모드 지정이 틀렸습니다.\n";
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
	cout << "목표 거리를 입력(끝내려면 q): ";
	while (cin >> target)
	{
		cout << "보폭을 입력: ";
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