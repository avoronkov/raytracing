#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_Light.h"


CFIT_6203_Voronkov_Ray_Light::CFIT_6203_Voronkov_Ray_Light()
{

}
CFIT_6203_Voronkov_Ray_Light::CFIT_6203_Voronkov_Ray_Light(const Point & pos, const Color & color)
{
	m_pos = pos;
	m_color = color;
}
CFIT_6203_Voronkov_Ray_Light::CFIT_6203_Voronkov_Ray_Light(const double & px, const double & py, const double & pz, 
								const double & r, const double & g, const double & b)
{
	m_pos = Point(px, py, pz);
	m_color = Color(r, g, b);
}
CFIT_6203_Voronkov_Ray_Light::~CFIT_6203_Voronkov_Ray_Light()
{

}

CFIT_6203_Voronkov_Ray_Light & CFIT_6203_Voronkov_Ray_Light::operator=
	(const CFIT_6203_Voronkov_Ray_Light & obj)
{
	m_pos = obj.m_pos;
	m_color = obj.m_color;
	return * this;
}
