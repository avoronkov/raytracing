#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_Primitive.h"

void CFIT_6203_Voronkov_Ray_Primitive::setOptics
		(double k_Ar, double k_Ag, double k_Ab, double k_Dr, double k_Dg, double k_Db,
		double k_Sr, double k_Sg, double k_Sb, double power, double kt, double n1, double n2)
{
	//m_k_Ar = k_Ar;
	//m_k_Ag = k_Ag;
	//m_k_Ab = k_Ab;
	m_k_A = Color (k_Ar, k_Ag, k_Ab);

	//m_k_Dr = k_Dr;
	//m_k_Dg = k_Dg;
	//m_k_Db = k_Db;
	m_k_D = Color (k_Dr, k_Dg, k_Db);

	//m_k_Sr = k_Sr;
	//m_k_Sg = k_Sg;
	//m_k_Sb = k_Sb;
	m_k_S = Color (k_Sr, k_Sg, k_Sb);

	m_power = power;
	m_kt = kt;
	m_n_outside = n1;
	m_n_inside = n2;
}
const Color & CFIT_6203_Voronkov_Ray_Primitive::getAmbientFactor()const
{
	return m_k_A;
}
const Color & CFIT_6203_Voronkov_Ray_Primitive::getDiffuseFactor() const
{
	return m_k_D;
}
const Color & CFIT_6203_Voronkov_Ray_Primitive::getSpecularFactor() const
{
	return m_k_S;
}
void CFIT_6203_Voronkov_Ray_Primitive::intersect(const Ray & ray)
{
	m_ray = ray;
	if (!this->isCorrect()) {
		ASSERT (false);
		return;
	}
	this->calculateIntersection();
	if (this->has_intersection)
	{
		this->calculateNormal();
		this->calculateReflected();
		this->calculateRefracted();
	}
}
bool CFIT_6203_Voronkov_Ray_Primitive::calculateReflected()
{
	if (!has_intersection) return false;
	Point incident_ray = - (m_ray.getDirection());
	m_reflected = m_normal * 2.0 * (m_normal * incident_ray) - incident_ray;

	return true;
}
bool CFIT_6203_Voronkov_Ray_Primitive::calculateRefracted()
{
	if (!has_intersection) return false;
	if (ray_from_outside)
	{
		// normal outside
		Point incident_ray = -m_ray.getDirection();
		double n_it = m_n_outside / m_n_inside;
		double cos_teta = ( m_normal * incident_ray);
		double D = 1.0 + n_it * n_it * (cos_teta * cos_teta - 1.0);
		if (D <= 0.0){
			has_refracted = false;
			return false;
		}
		m_refracted = -incident_ray * n_it + m_normal * (n_it * cos_teta - sqrt (D));
		has_refracted = true;
	}
	else
	{
		// from the inside
		Point incident_ray = -m_ray.getDirection();
		double n_it = m_n_inside / m_n_outside;
		Point normal = -m_normal;
		double cos_teta = ( normal * incident_ray);
		double D = 1.0 + n_it * n_it * (cos_teta * cos_teta - 1.0);
		if (D <= 0.0){
			has_refracted = false;
			return false;
		}
		m_refracted = -incident_ray * n_it + normal * (n_it * cos_teta - sqrt (D));
		has_refracted = true;
	}	
	return true;
}