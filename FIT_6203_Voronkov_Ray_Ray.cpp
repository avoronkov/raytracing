#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_Ray.h"

CFIT_6203_Voronkov_Ray_Ray::CFIT_6203_Voronkov_Ray_Ray()
{
	m_origin = Point();
	m_direction = Point();
}
CFIT_6203_Voronkov_Ray_Ray::CFIT_6203_Voronkov_Ray_Ray
		(const Point & origin, const Point & direction)
{
	m_origin = origin;
	m_direction = direction;
	m_direction.normalizeLength();
}
CFIT_6203_Voronkov_Ray_Ray::CFIT_6203_Voronkov_Ray_Ray
		(const double& _x, const double& _y, const double& _z,
		 const double& dx, const double& dy, const double& dz)
{
	m_origin = Point(_x, _y, _z);
	m_direction = Point(dx, dy, dz);
	m_direction.normalizeLength();
}
CFIT_6203_Voronkov_Ray_Ray::CFIT_6203_Voronkov_Ray_Ray
		(const CFIT_6203_Voronkov_Ray_Ray & obj)
{
	m_origin = obj.m_origin;
	m_direction = obj.m_direction;
	m_direction.normalizeLength();
}
CFIT_6203_Voronkov_Ray_Ray::~CFIT_6203_Voronkov_Ray_Ray()
{
}

const Point & CFIT_6203_Voronkov_Ray_Ray::getOrigin() const
{
	return m_origin;
}
const Point & CFIT_6203_Voronkov_Ray_Ray::getDirection() const
{
	return m_direction;
}

void CFIT_6203_Voronkov_Ray_Ray::setOrigin(const Point & origin)
{
	m_origin = origin;
}
void CFIT_6203_Voronkov_Ray_Ray::setDirection(const Point & direction)
{
	m_direction = direction;
	m_direction.normalizeLength();
}
void CFIT_6203_Voronkov_Ray_Ray::setDirectionByPoint(const Point & point)
{
	m_direction = point - m_origin;
	m_direction.normalizeLength();
}

CFIT_6203_Voronkov_Ray_Ray & CFIT_6203_Voronkov_Ray_Ray::operator=
		(const CFIT_6203_Voronkov_Ray_Ray & obj)
{
	m_origin = obj.m_origin;
	m_direction = obj.m_direction;
	return * this;
}
CFIT_6203_Voronkov_Ray_Ray CFIT_6203_Voronkov_Ray_Ray::operator-() const
{
	Ray res(m_origin, -m_direction);
	return res;
}
CString CFIT_6203_Voronkov_Ray_Ray::toString() const
{
	CString res;
	res.Format("[Ray:(%.5lf, %.5lf, %.5lf), (%.5lf, %.5lf, %.5lf)]\n",
		m_origin.x(), m_origin.y(), m_origin.z(),
		m_direction.x(), m_direction.y(), m_direction.z());
	return res;
}
bool CFIT_6203_Voronkov_Ray_Ray::isCorrect() const
{
	if (m_direction.x() == 0 && m_direction.y() == 0 &&m_direction.z() == 0){
		return false;
	}
	return true;
}