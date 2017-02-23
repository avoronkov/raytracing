#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_Color.h"

CFIT_6203_Voronkov_Ray_Color::CFIT_6203_Voronkov_Ray_Color()
{
	m_r = 0.0;
	m_g = 0.0;
	m_b = 0.0;
}
CFIT_6203_Voronkov_Ray_Color::CFIT_6203_Voronkov_Ray_Color
		(const double & _r, const double & _g, const double & _b)
{
	m_r = _r;
	m_g = _g;
	m_b = _b;
}
CFIT_6203_Voronkov_Ray_Color::~CFIT_6203_Voronkov_Ray_Color()
{

}

CFIT_6203_Voronkov_Ray_Color & CFIT_6203_Voronkov_Ray_Color::operator=
		(const CFIT_6203_Voronkov_Ray_Color & obj)
{
	m_r = obj.m_r;
	m_g = obj.m_g;
	m_b = obj.m_b;

	is_background = obj.is_background;

	return * this;
}
CFIT_6203_Voronkov_Ray_Color CFIT_6203_Voronkov_Ray_Color::operator*
		(const CFIT_6203_Voronkov_Ray_Color& obj)const
{
	Color res;

	res.m_r = m_r * obj.m_r;
	res.m_g = m_g * obj.m_g;
	res.m_b = m_b * obj.m_b;
	res.is_background = false;
	return res;
}
CFIT_6203_Voronkov_Ray_Color CFIT_6203_Voronkov_Ray_Color::operator+
		(const CFIT_6203_Voronkov_Ray_Color& obj)const
{
	Color res;

	res.m_r = m_r + obj.m_r;
	res.m_g = m_g + obj.m_g;
	res.m_b = m_b + obj.m_b;
	res.is_background = is_background & obj.is_background;
	return res;
}
CFIT_6203_Voronkov_Ray_Color CFIT_6203_Voronkov_Ray_Color::operator*
		(const double& factor)const
{
	Color res;
	res.m_r = m_r * factor;
	res.m_g = m_g * factor;
	res.m_b = m_b * factor;
	res.is_background = false;
	return res;
}
CFIT_6203_Voronkov_Ray_Color CFIT_6203_Voronkov_Ray_Color::operator/
		(const double& factor)const
{
	Color res;
	res.m_r = m_r / factor;
	res.m_g = m_g / factor;
	res.m_b = m_b / factor;
	res.is_background = false;
	return res;
}
CFIT_6203_Voronkov_Ray_Color& CFIT_6203_Voronkov_Ray_Color::operator/=
		(const double& value)
{
	m_r /= value;
	m_g /= value;
	m_b /= value;
	is_background = false;
	return * this;
}
CFIT_6203_Voronkov_Ray_Color& CFIT_6203_Voronkov_Ray_Color::operator+=
		(const CFIT_6203_Voronkov_Ray_Color& obj)
{
	m_r += obj.m_r;
	m_g += obj.m_g;
	m_b += obj.m_b;
	is_background &= obj.is_background;
	return * this;
}
void CFIT_6203_Voronkov_Ray_Color::set
		(const double & _r, const double & _g, const double & _b)
{
	m_r = _r;
	m_g = _g;
	m_b = _b;
	is_background = false;
}