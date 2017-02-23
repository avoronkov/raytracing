#include "StdAfx.h"
#include "FIT_6203_Voronkov_Ray_Eye.h"

CFIT_6203_Voronkov_Ray_Eye::CFIT_6203_Voronkov_Ray_Eye(void)
{
}

CFIT_6203_Voronkov_Ray_Eye::~CFIT_6203_Voronkov_Ray_Eye(void)
{
}
CFIT_6203_Voronkov_Ray_Eye & CFIT_6203_Voronkov_Ray_Eye::operator=
		(const CFIT_6203_Voronkov_Ray_Eye & obj)
{
	m_origin = obj.m_origin;
	for (int i=0; i<4; i++){
		m_view_border[i] = obj.m_view_border[i];
	}
	m_freq =obj.m_freq;
	return * this;
}
void CFIT_6203_Voronkov_Ray_Eye::setOrigin(const Point & origin)
{
	m_origin = origin;
}
void CFIT_6203_Voronkov_Ray_Eye::setBorder(int i, const Point & point)
{
	ASSERT (i>=0 && i<4);
	m_view_border[i] = point;
}
void CFIT_6203_Voronkov_Ray_Eye::setBorder
		(const Point &a, const Point &b, const Point &c, const Point &d)
{
	m_view_border[0] = a;
	m_view_border[1] = b;
	m_view_border[2] = c;
	m_view_border[3] = d;
}
void CFIT_6203_Voronkov_Ray_Eye::setFreq(const CSize & freq)
{
	m_freq = freq;
}
void CFIT_6203_Voronkov_Ray_Eye::setFreq(int hor, int vert)
{
	setFreq(CSize(hor, vert));
}
const Point & CFIT_6203_Voronkov_Ray_Eye::origin() const
{
	return m_origin;
}
const Point & CFIT_6203_Voronkov_Ray_Eye::border(int i) const
{
	ASSERT (i>=0 && i<4);
	return m_view_border[i];
}
const CSize & CFIT_6203_Voronkov_Ray_Eye::frequency() const
{
	return m_freq;
}

Ray CFIT_6203_Voronkov_Ray_Eye::getRay(int h, int v) const
{
	ASSERT (h>=0 && h < m_freq.cx);
	ASSERT (v>=0 && v < m_freq.cy);
	
	Ray res;
	
	res.setOrigin(m_origin);
	Point second;
	// горизонтальное направление
	Point dir_h = (m_view_border[1] - m_view_border[0]) * ((double)h / (m_freq.cx - 1.0));
	Point dir_v = (m_view_border[2] - m_view_border[0]) * ((double)v / (m_freq.cy - 1.0));
	res.setDirectionByPoint(m_view_border[0] + dir_h + dir_v);

	return res;
}