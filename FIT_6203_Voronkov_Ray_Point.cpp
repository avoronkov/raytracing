#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_Point.h"

CFIT_6203_Voronkov_Ray_Point::CFIT_6203_Voronkov_Ray_Point()
{
	this->v[0] = 0.0; // x
	this->v[1] = 0.0; // y
	this->v[2] = 0.0; // z
	this->v[3] = 1.0; // w
}
CFIT_6203_Voronkov_Ray_Point::CFIT_6203_Voronkov_Ray_Point(double x, double y, double z)
{
	this->v[0] = x; // x
	this->v[1] = y; // y
	this->v[2] = z; // z
	this->v[3] = 1.0; // w
}
CFIT_6203_Voronkov_Ray_Point::~CFIT_6203_Voronkov_Ray_Point()
{
}
CFIT_6203_Voronkov_Ray_Point & CFIT_6203_Voronkov_Ray_Point::operator=
	(const CFIT_6203_Voronkov_Ray_Point & another)
{
	this->v[0] = another.v[0];
	this->v[1] = another.v[1];
	this->v[2] = another.v[2];
	this->v[3] = another.v[3];
	return *this;
}
CFIT_6203_Voronkov_Ray_Point & CFIT_6203_Voronkov_Ray_Point::operator+=
		(const CFIT_6203_Voronkov_Ray_Point & another)
{
	this->v[0] += another.v[0];
	this->v[1] += another.v[1];
	this->v[2] += another.v[2];
//	this->v[3] += another.v[3];
	return *this;
}
CFIT_6203_Voronkov_Ray_Point   CFIT_6203_Voronkov_Ray_Point::operator+
		(const CFIT_6203_Voronkov_Ray_Point & point) const
{
	Point res;
	res.v[0] = this->v[0] + point.v[0];
	res.v[1] = this->v[1] + point.v[1];
	res.v[2] = this->v[2] + point.v[2];
	res.v[3] = 1.0;
	return res;
}
CFIT_6203_Voronkov_Ray_Point   CFIT_6203_Voronkov_Ray_Point::operator-
		(const CFIT_6203_Voronkov_Ray_Point & point) const
{
	Point res;
	res.v[0] = this->v[0] - point.v[0];
	res.v[1] = this->v[1] - point.v[1];
	res.v[2] = this->v[2] - point.v[2];
	res.v[3] = 1.0;
	return res;
}
CFIT_6203_Voronkov_Ray_Point CFIT_6203_Voronkov_Ray_Point::operator-() const
{
	Point res;
	res.v[0] = -this->v[0];
	res.v[1] = -this->v[1];
	res.v[2] = -this->v[2];
	res.v[3] = 1.0;
	return res;	
}
CFIT_6203_Voronkov_Ray_Point CFIT_6203_Voronkov_Ray_Point::operator*
		(const double & value) const
{
	CFIT_6203_Voronkov_Ray_Point res;
	res.v[0] = this->v[0] * value;
	res.v[1] = this->v[1] * value;
	res.v[2] = this->v[2] * value;
	res.v[3] = 1.0;
	return res;
}
double CFIT_6203_Voronkov_Ray_Point::operator*
		(const CFIT_6203_Voronkov_Ray_Point & obj) const
{
	return v[0] * obj.v[0] + v[1] * obj.v[1] + v[2] * obj.v[2];
}
double CFIT_6203_Voronkov_Ray_Point::x() const
{
	return v[0];
}
double CFIT_6203_Voronkov_Ray_Point::y() const
{
	return v[1];
}
double CFIT_6203_Voronkov_Ray_Point::z() const
{
	return v[2];
}

void CFIT_6203_Voronkov_Ray_Point::setX(double value)
{
	v[0] = value;
}
void CFIT_6203_Voronkov_Ray_Point::setY(double value)
{
	v[1] = value;
}
void CFIT_6203_Voronkov_Ray_Point::setZ(double value)
{
	v[2] = value;
}	

double CFIT_6203_Voronkov_Ray_Point::get(int idx) const
{
	ASSERT(idx >=0 && idx < 4);
	return v[idx];
}
void CFIT_6203_Voronkov_Ray_Point::set(int idx, double value)
{
	ASSERT(idx >=0 && idx < 4);
	v[idx] = value;
}
double CFIT_6203_Voronkov_Ray_Point::length() const
{
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}
double CFIT_6203_Voronkov_Ray_Point::cos(CFIT_6203_Voronkov_Ray_Point another)const
{
	Point cp = (*this);
	cp.normalizeLength();
	another.normalizeLength();
	return cp * another;

}
CPoint CFIT_6203_Voronkov_Ray_Point::toRaster() const
{
	CPoint res;
	res.x = (LONG)(this->v[0] + 0.5);
	res.y = (LONG)(this->v[1] + 0.5);
	return res;
}
void CFIT_6203_Voronkov_Ray_Point::normalizeW()
{
	for (int i=0; i<4; i++){
		this->v[i] = this->v[i] / this->v[3];
	}
}
void CFIT_6203_Voronkov_Ray_Point::normalizeLength()
{
	if (v[0] != 0.0 || v[1] != 0.0 || v[2] != 0.0)
	{
		double co = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
		v[0] /= co;
		v[1] /= co;
		v[2] /= co;
	}
}
CFIT_6203_Voronkov_Ray_Point CFIT_6203_Voronkov_Ray_Point::vectorProduct
		(const CFIT_6203_Voronkov_Ray_Point &obj)const
{
	//double rx = my * obj.mz - mz * obj.my;
	//double ry = - (mx * obj.mz - mz * obj.mx);
	//double rz = mx * obj.my - my * obj.mx;
	double rx = v[1] * obj.v[2] - v[2] * obj.v[1];
	double ry = - (v[0] * obj.v[2] - v[2] * obj.v[0]);
	double rz = v[0] * obj.v[1] - v[1] * obj.v[0];
	return CFIT_6203_Voronkov_Ray_Point(rx, ry, rz);
}