#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_Segment.h"

CFIT_6203_Voronkov_Ray_Segment::CFIT_6203_Voronkov_Ray_Segment()
{
	this->m_width = 1;
	this->m_color = RGB(0, 0, 0);
}
CFIT_6203_Voronkov_Ray_Segment::CFIT_6203_Voronkov_Ray_Segment
	(const CFIT_6203_Voronkov_Ray_Segment & another)
{
	this->m_width = another.m_width;
	this->begin = another.begin;
	this->end = another.end;
	this->m_color = another.m_color;
//	this->m_color = RGB(0, 0, 0);
}
CFIT_6203_Voronkov_Ray_Segment::CFIT_6203_Voronkov_Ray_Segment
	(const Point & s, const Point & f)
{
	this->m_width = 1;
	this->m_color = RGB(0, 0, 0);
	this->begin = s;
	this->end = f;
}
CFIT_6203_Voronkov_Ray_Segment::CFIT_6203_Voronkov_Ray_Segment
	(double sx, double sy, double sz, double fx, double fy, double fz)
{
	this->m_width = 1;
	this->m_color = RGB(0, 0, 0);
	this->begin = Point(sx, sy, sz);
	this->end   = Point(fx, fy, fz);
}
CFIT_6203_Voronkov_Ray_Segment::CFIT_6203_Voronkov_Ray_Segment
	(double sx, double sy, double sz, double fx, double fy, double fz, COLORREF color)
{
	this->m_width = 1;
	this->m_color = color;
	this->begin = Point(sx, sy, sz);
	this->end   = Point(fx, fy, fz);	
}
CFIT_6203_Voronkov_Ray_Segment::~CFIT_6203_Voronkov_Ray_Segment()
{

}

CFIT_6203_Voronkov_Ray_Segment& CFIT_6203_Voronkov_Ray_Segment::operator=
	(const CFIT_6203_Voronkov_Ray_Segment & obj)
{
	this->m_width = obj.m_width;
	this->begin = obj.begin;
	this->end = obj.end;
	this->m_color = obj.m_color;
	return *this;
}
CFIT_6203_Voronkov_Ray_Segment& CFIT_6203_Voronkov_Ray_Segment::operator+=
	(const CFIT_6203_Voronkov_Ray_Segment & obj)
{
	this->begin += obj.begin;
	this->end += obj.end;
	return *this;
}
CFIT_6203_Voronkov_Ray_Segment CFIT_6203_Voronkov_Ray_Segment::operator+
		(const Point & point)
{
	Segment res;
	res.begin = this->begin + point;
	res.end = this->end + point;
	return res;
}
const Point & CFIT_6203_Voronkov_Ray_Segment::start() const
{
	return this->begin;
}
const Point & CFIT_6203_Voronkov_Ray_Segment::finish() const
{
	return this->end;
}

void CFIT_6203_Voronkov_Ray_Segment::setStart(const Point & s)
{
	this->begin = s;
}
void CFIT_6203_Voronkov_Ray_Segment::setFinish(const Point & f)
{
	this->end = f;
}

COLORREF CFIT_6203_Voronkov_Ray_Segment::color() const
{
	return m_color;
}
void CFIT_6203_Voronkov_Ray_Segment::setColor(COLORREF c)
{
	m_color = c;
}
void CFIT_6203_Voronkov_Ray_Segment::setColor(int r, int g, int b)
{
	m_color = RGB(r, g, b);
}
int CFIT_6203_Voronkov_Ray_Segment::width() const
{
	return m_width;
}
void CFIT_6203_Voronkov_Ray_Segment::setWidth(int w)
{
	m_width = w;
}
CString CFIT_6203_Voronkov_Ray_Segment::show() const
{
	CString str;
	str.AppendFormat("(%.2lf, %.2lf, %.2lf  :", begin.x(), begin.y(), begin.z());
	str.AppendFormat("  %.2lf, %.2lf, %.2lf)", end.x(), end.y(), end.z());
	return str;
}

void CFIT_6203_Voronkov_Ray_Segment::normalizeW()
{
	this->begin.normalizeW();
	this->end.normalizeW();
}