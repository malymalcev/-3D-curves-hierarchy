#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <math.h>

# define M_PI           3.14159265358979323846

using namespace std;


// Задание 1. Класс кривых Curve. Его наследники классы Circle, Ellipse, Helix.

struct Point {
	double x, y, z;
};

struct Vector {
	double dx, dy, dz;
};

class Curve {
public:
	~Curve() {}
	virtual Point getPoint(double t) = 0;
	virtual Vector getVector(double t) = 0;
};

class Circle : public Curve
{
protected:
	double radius;
	Point center;
public:
	Circle(double r, Point c) 
	{
		if (r < 0)
		{
			r = 0.0;
		}
		radius = r;
		center = c;
	}
	Circle()
	{
		radius = 0.0;
		center = { 0.0, 0.0, 0.0 };
	}
	~Circle(){}
	Circle(const Circle& other) {
		radius = other.radius;
		center = other.center;
	}
	// Программа работает для произвольного центра окружности/элипса/спирали. 
	Point getPoint(double t) override 
	{
		return { center.x + radius * cos(t), center.y + radius * sin(t), center.z };
	}
	Vector getVector(double t) override
	{
		return { (-radius) * sin(t), radius * cos(t), 0.0 };
	}
	double getRadius()
	{
		return radius;
	}
};

class Ellipse : public Curve
{
protected:
	double radius_a;
	double radius_b;
	Point center;
public:
	Ellipse(double a, double b, Point c)
	{
		if (a < 0)
		{
			a = 0.0;
		}
		if (b < 0)
		{
			b = 0.0;
		}
		radius_a = a;
		radius_b = b;
		center = c;
	}
	Ellipse()
	{
		radius_a = 0.0;
		radius_b = 0.0;
		center = { 0.0, 0.0, 0.0 };
	}
	~Ellipse() {}
	Ellipse(const Ellipse& other) {
		radius_a = other.radius_a;
		radius_b = other.radius_b;
		center = other.center;
	}
	Point getPoint(double t) override
	{
		return { center.x + radius_a * cos(t), center.y + radius_b * sin(t), center.z };
	}
	Vector getVector(double t) override
	{
		return { (-radius_a) * sin(t), radius_b * cos(t), 0.0 };
	}
};

class Helix : public Curve
{
protected:
	double radius;
	Point center;
	double step;
public:
	Helix(double r,Point c,double s)
	{
		if (r < 0)
		{
			r = 0.0;
		}
		radius = r;
		center = c;
		step = s;
	}
	Helix()
	{
		radius = 0.0;
		center = { 0.0,0.0,0.0 };
		step = 0.0;
	}
	~Helix() {}
	Helix(const Helix& other)
	{
		radius = other.radius;
		center = other.center;
		step = other.step;
	}
	Point getPoint(double t) override
	{
		return{ center.x + radius * cos(t), center.y + radius * sin(t), center.z + (step * t) / (2.0 * M_PI) };
	}
	Vector getVector(double t) override
	{
		return { (-radius) * sin(t), radius * cos(t), (step) / (2.0 * M_PI) };
	}
};