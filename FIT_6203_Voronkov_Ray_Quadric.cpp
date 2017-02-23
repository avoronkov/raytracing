#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_Quadric.h"

CFIT_6203_Voronkov_Ray_Quadric::CFIT_6203_Voronkov_Ray_Quadric()
{
}
CFIT_6203_Voronkov_Ray_Quadric::CFIT_6203_Voronkov_Ray_Quadric
								(double A, double E, double H, double B, 
								double C, double F, double D,
								double G, double I, double J)
{
	m_a = A;
	m_e = E;
	m_h = H;
	m_b = B;
	m_c = C;
	m_f = F;
	m_d = D;
	m_g = G;
	m_i = I;
	m_j = J;
}
CFIT_6203_Voronkov_Ray_Quadric::~CFIT_6203_Voronkov_Ray_Quadric()
{
	
}
CFIT_6203_Voronkov_Ray_Quadric & CFIT_6203_Voronkov_Ray_Quadric::operator=
		(const CFIT_6203_Voronkov_Ray_Quadric & obj)
{
	m_a = obj.m_a;
	m_e = obj.m_e;
	m_h = obj.m_h;
	m_b = obj.m_b;
	m_c = obj.m_c;
	m_f = obj.m_f;
	m_d = obj.m_d;
	m_g = obj.m_g;
	m_i = obj.m_i;
	m_j = obj.m_j;
	return * this;
}
CString CFIT_6203_Voronkov_Ray_Quadric::toString() const
{
	CString res;
	res.Format("[Quadric:\n");
	res.AppendFormat("\tA=%.5lf\n", m_a);
	res.AppendFormat("\tE=%.5lf\n", m_e);
	res.AppendFormat("\tH=%.5lf\n", m_h);
	res.AppendFormat("\tB=%.5lf\n", m_b);
	res.AppendFormat("\tC=%.5lf\n", m_c);
	res.AppendFormat("\tF=%.5lf\n", m_f);
	res.AppendFormat("\tD=%.5lf\n", m_d);
	res.AppendFormat("\tG=%.5lf\n", m_g);
	res.AppendFormat("\tI=%.5lf\n", m_i);
	res.AppendFormat("\tJ=%.5lf\n", m_j);
	res.AppendFormat("]\n");
	return res;
}
bool CFIT_6203_Voronkov_Ray_Quadric::isCorrect() const
{
	// TODO checking for correction
	return true;
}
int CFIT_6203_Voronkov_Ray_Quadric::intersectRay
		(const Ray & ray, Point * i_near, Point * n_near, Point * refl_near, double * t_near,
		Point * i_far, Point * n_far, Point * refl_far, double * t_far)
{
	//double l_a = m_quadric.getA();
	//double l_b = m_quadric.getB();
	//double l_c = m_quadric.getC();
	//double l_d = m_quadric.getD();
	//double l_e = m_quadric.getE();
	//double l_f = m_quadric.getF();
	//double l_g = m_quadric.getG();
	//double l_h = m_quadric.getH();
	//double l_i = m_quadric.getI();
	//double l_j = m_quadric.getJ();

	const Point & ray_dir = ray.getDirection();
	double xd = ray_dir.x();
	double yd = ray_dir.y();
	double zd = ray_dir.z();

	const Point & ray_ori = ray.getOrigin();
	double xo = ray_ori.x();
	double yo = ray_ori.y();
	double zo = ray_ori.z();

	double c_a = m_a * xd * xd + m_e * yd * yd + m_h *zd * zd 
				+ 2.0 * m_b * xd * yd + 2.0 * m_c * xd * zd + 2.0 * m_f * yd * zd;
	double c_b = 2 * (m_a * xo * xd + m_e * yo * yd + m_h * zo * zd 
				+ m_b*(xo*yd + xd*yo) + m_c*(xo*zd + xd*zo) + m_f*(yo*zd + yd*zo)
				+ m_d * xd + m_g * yd + m_i * zd);
	double c_c = m_a * xo * xo + m_e * yo * yo + m_h * zo * zo 
				+ 2 * m_b * xo * yo + 2 * m_c * xo * zo + 2 * m_f * yo * zo 
				+ 2 * m_d * xo + 2 * m_g * yo + 2 * m_i * zo + m_j;
	double t;
	if (c_a == 0)
	{
		if (c_b == 0){
//			has_intersection = false;
			return 0;
		}
		t = - c_c / c_b;
		*t_near = t;
		*i_near = ray.getOrigin() + ray.getDirection() * t;
		double ix = i_near->x();
		double iy = i_near->y();
		double iz = i_near->z();
		n_near->setX(2 * (m_a * ix + m_b * iy + m_c * iz + m_d));
		n_near->setY(2 * (m_b * ix + m_e * iy + m_f * iz + m_g));
		n_near->setZ(2 * (m_c * ix + m_f * iy + m_h * iz + m_i));
		n_near->normalizeLength();
		*refl_near = getReflected(ray.getDirection(), *n_near);
		return 1;
	}
	else
	{
		if (c_a < 0){
			c_a = - c_a;
			c_b = - c_b;
			c_c = - c_c;
		}
		double D = c_b * c_b - 4 * c_a * c_c;
		if (D < 0) {
			return 0;
		}
		double to = (- c_b - sqrt (D)) / (2 * c_a);
		if (to > 0){
			t = to;
			*i_near = ray.getOrigin() + ray.getDirection() * t;
			*t_near = t;
			double ix = i_near->x();
			double iy = i_near->y();
			double iz = i_near->z();
			n_near->setX(2 * (m_a * ix + m_b * iy + m_c * iz + m_d));
			n_near->setY(2 * (m_b * ix + m_e * iy + m_f * iz + m_g));
			n_near->setZ(2 * (m_c * ix + m_f * iy + m_h * iz + m_i));
			n_near->normalizeLength();
			*refl_near = getReflected(ray.getDirection(), *n_near);
//			m_intersection = m_ray.getOrigin() + m_ray.getDirection() * t;
//			has_intersection = true;
			// second intersection
			t = (- c_b + sqrt (D)) / (2 * c_a);
			*i_far = ray.getOrigin() + ray.getDirection() * t;
			*t_far = t;
			ix = i_far->x();
			iy = i_far->y();
			iz = i_far->z();
			n_far->setX(2 * (m_a * ix + m_b * iy + m_c * iz + m_d));
			n_far->setY(2 * (m_b * ix + m_e * iy + m_f * iz + m_g));
			n_far->setZ(2 * (m_c * ix + m_f * iy + m_h * iz + m_i));

			ASSERT (n_far->get(0) != 0 && n_far->get(1) != 0 && n_far->get(2) != 0);

			n_far->normalizeLength();
			*refl_far = getReflected(ray.getDirection(), *n_far);
			return 2;
		}
		to = (- c_b + sqrt (D)) /( 2 * c_a);
		if (to > 0){
			t = to;
			*i_near = ray.getOrigin() + ray.getDirection() * t;
			*t_near = t;
			double ix = i_near->x();
			double iy = i_near->y();
			double iz = i_near->z();
			n_near->setX(2 * (m_a * ix + m_b * iy + m_c * iz + m_d));
			n_near->setY(2 * (m_b * ix + m_e * iy + m_f * iz + m_g));
			n_near->setZ(2 * (m_c * ix + m_f * iy + m_h * iz + m_i));
			n_near->normalizeLength();
			*refl_near = getReflected(ray.getDirection(), *n_near);
//			m_intersection = 
//			has_intersection = true;
			return 1;
		}
	}
	return 0;
}
Point CFIT_6203_Voronkov_Ray_Quadric::getReflected
		(const Point & ray, const Point & normal)const
{
	Point incident_ray = - (ray);
	return normal * 2.0 * (normal * incident_ray) - incident_ray;
}