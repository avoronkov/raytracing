#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_QuadroBox.h"

CFIT_6203_Voronkov_Ray_QuadroBox::CFIT_6203_Voronkov_Ray_QuadroBox()
{
}
CFIT_6203_Voronkov_Ray_QuadroBox::CFIT_6203_Voronkov_Ray_QuadroBox
		(const Quadric & q, const Box & b)
{
	m_quadric = q;
	m_box = b;
}
CFIT_6203_Voronkov_Ray_QuadroBox::~CFIT_6203_Voronkov_Ray_QuadroBox()
{

}

WireFrame CFIT_6203_Voronkov_Ray_QuadroBox::getWireFrame() const
{
	WireFrame res = m_box.getWireFrame();

	Point vlll = m_box.getVertex(0);
	Point vllh = m_box.getVertex(1);
	Point vlhh = m_box.getVertex(2);
	Point vlhl = m_box.getVertex(3);
	Point vhll = m_box.getVertex(4);
	Point vhlh = m_box.getVertex(5);
	Point vhhh = m_box.getVertex(6);
	Point vhhl = m_box.getVertex(7);

	// adds diagonales
	res += Segment(vlll, vlhh);
	res += Segment(vlhl, vllh);
	res += Segment(vhll, vhhh);
	res += Segment(vhhl, vhlh);

	res += Segment(vlll, vhlh);
	res += Segment(vllh, vhll);
	res += Segment(vlhl, vhhh);
	res += Segment(vlhh, vhhl);

	res += Segment(vlll, vhhl);
	res += Segment(vlhl, vhll);
	res += Segment(vllh, vhhh);
	res += Segment(vlhh, vhlh);

	return res;
}
double CFIT_6203_Voronkov_Ray_QuadroBox::getMax(int coord) const
{
	switch (coord)
	{
	case 0: return m_box.getXMax();
	case 1: return m_box.getYMax();
	case 2: return m_box.getZMax();
	}
	ASSERT (false);
	return 0;
}
double CFIT_6203_Voronkov_Ray_QuadroBox::getMin(int coord) const
{
	switch (coord)
	{
	case 0: return m_box.getXMin();
	case 1: return m_box.getYMin();
	case 2: return m_box.getZMin();
	}
	ASSERT (false);
	return 0;
}
bool CFIT_6203_Voronkov_Ray_QuadroBox::isCorrect() const
{
	return m_quadric.isCorrect();
}

bool CFIT_6203_Voronkov_Ray_QuadroBox::calculateIntersection()
{
	Point i_near;
	Point i_far;
	Point n_near;
	Point n_far;
	Point refl_near;
	Point refl_far;
	double t_near;
	double t_far;
	int res = m_quadric.intersectRay(m_ray, &i_near, &n_near, &refl_near, &t_near,
			&i_far, &n_far, &refl_far, &t_far);
	if (res == 0)
	{
		has_intersection = false;
		return false;
	}
	else if (res == 1)
	{
		if (m_box.isInside(i_near)){
			has_intersection = true;
			m_intersection = i_near;
			m_normal = n_near;
			m_normal.normalizeLength();
			m_reflected = refl_near;
			m_reflected.normalizeLength();
			m_t = t_near;
			return true;
		}
		else {
			has_intersection = false;
			return false;
		}
	}
	else if (res == 2)
	{
		ASSERT (t_near <= t_far);
		if (m_box.isInside(i_near)){
			has_intersection = true;
			m_intersection = i_near;
			m_normal = n_near;
			m_normal.normalizeLength();
			m_reflected = refl_near;
			m_reflected.normalizeLength();
			m_t = t_near;
			return true;
		}
		else if (m_box.isInside(i_far)){
			has_intersection = true;
			m_intersection = i_far;
			m_normal = n_far;
			m_normal.normalizeLength();
			m_reflected = refl_far;
			m_reflected.normalizeLength();
			m_t = t_far;
			return true;
		}
		else{
			has_intersection = false;
			return false;
		}
	}
	else 
	{
		ASSERT (false);
	}
	ASSERT (false);
	return false;
}
bool CFIT_6203_Voronkov_Ray_QuadroBox::calculateNormal()
{
	return has_intersection;
}