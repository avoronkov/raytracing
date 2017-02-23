#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_Camera.h"

CFIT_6203_Voronkov_Ray_Camera::CFIT_6203_Voronkov_Ray_Camera(void)
{
}
CFIT_6203_Voronkov_Ray_Camera::CFIT_6203_Voronkov_Ray_Camera
		(const CFIT_6203_Voronkov_Ray_Camera & obj)
{
	m_center_z = obj.m_center_z;
	m_rotate = obj.m_rotate;
}
CFIT_6203_Voronkov_Ray_Camera::CFIT_6203_Voronkov_Ray_Camera
		(const double & z, const Matrix & rotate):m_center_z(z), m_rotate(rotate)
{
}
CFIT_6203_Voronkov_Ray_Camera::~CFIT_6203_Voronkov_Ray_Camera(void)
{
}


CFIT_6203_Voronkov_Ray_Camera & CFIT_6203_Voronkov_Ray_Camera::operator=
		(const CFIT_6203_Voronkov_Ray_Camera & obj)
{
	m_center_z = obj.m_center_z;
	m_rotate = obj.m_rotate;
	return * this;
}

void CFIT_6203_Voronkov_Ray_Camera::setCenterZ(const double & value)
{
	m_center_z = value;
}
void CFIT_6203_Voronkov_Ray_Camera::setMatrixRotate(const Matrix & rotate)
{
	m_rotate = rotate;
}

const double & CFIT_6203_Voronkov_Ray_Camera::centerZ()const
{
	return m_center_z;
}
const Matrix & CFIT_6203_Voronkov_Ray_Camera::matrixRotate() const
{
	return m_rotate;
}