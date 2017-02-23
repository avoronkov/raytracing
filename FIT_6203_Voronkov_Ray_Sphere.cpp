#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_Sphere.h"

#define N 10
#define M 10
#define KZ 1

CFIT_6203_Voronkov_Ray_Sphere::CFIT_6203_Voronkov_Ray_Sphere()
{
	m_center = Point();
	m_radius = 0.0;
}
CFIT_6203_Voronkov_Ray_Sphere::CFIT_6203_Voronkov_Ray_Sphere
		(const Point & center, const double & radius)
{
	m_center = center;
	m_radius = radius;
}
CFIT_6203_Voronkov_Ray_Sphere::~CFIT_6203_Voronkov_Ray_Sphere()
{
}

const double & CFIT_6203_Voronkov_Ray_Sphere::getRadius() const
{
	return m_radius;
}
const Point & CFIT_6203_Voronkov_Ray_Sphere::getCenter() const
{
	return m_center;
}

void CFIT_6203_Voronkov_Ray_Sphere::setRadius(const double & value)
{
	m_radius = value;
}
void CFIT_6203_Voronkov_Ray_Sphere::setCenter(const Point & center)
{
	m_center = center;
}
void CFIT_6203_Voronkov_Ray_Sphere::setCenter(const double& x, const double& y, const double& z)
{
	m_center = Point(x, y, z);
}
CFIT_6203_Voronkov_Ray_Sphere & CFIT_6203_Voronkov_Ray_Sphere::
		operator=(const CFIT_6203_Voronkov_Ray_Sphere & obj)
{
	m_center = obj.m_center;
	m_radius = obj.m_radius;
	return *this;
}
CString CFIT_6203_Voronkov_Ray_Sphere::toString() const
{
	CString res;
	res.Format("[Sphere:(%.5lf, %.5lf, %.5lf), %.5lf]\n",
		m_center.x(), m_center.y(), m_center.z(), m_radius);
	return res;
}
bool CFIT_6203_Voronkov_Ray_Sphere::isCorrect() const
{
	if (m_radius <= 0) {
		return false;
	}
	return true;
}
WireFrame CFIT_6203_Voronkov_Ray_Sphere::getWireFrame() const
{
	WireFrame res;
	int n = N;
	int m = M;
	int kz = KZ;
	int n_kz = n * kz;
	int m_kz = m * kz;
	double d_t = M_PI / m_kz; // отрезок по широте
	double d_t_big = M_PI / m;

	double d_s = 2.0 * M_PI / n_kz; // отрезок по долготе
	double d_s_big = 2.0 * M_PI / n;

	int i, j;
	double current_s, next_s;
	double current_t, next_t;
	Segment segm;
	Point pprev;
	Point pnext;
	for (i=0; i< n; i++) // цикл по всем меридианам
	{
		current_s = d_s_big * i;
		current_t = - M_PI_2;
		pprev = spherePoint(current_s, current_t);
		for (j = 0; j < m_kz; j ++) // цикл по всем отрезкам меридиана
		{
//			current_t = j * d_t - M_PI_2;
			next_t = (j + 1) * d_t - M_PI_2;
			pnext = spherePoint(current_s, next_t);
			segm.setStart(pprev);
			segm.setFinish(pnext);
			res +=segm;
//			current_t = next_t;
			pprev = pnext;
		}
	}
	for (j=0; j<m; j++) // цикл по всем параллелям
	{
		current_t = j * d_t_big - M_PI_2;
		current_s = 0.0;
		pprev = spherePoint(current_s, current_t);
		for (i=0; i < n_kz; i++)
		{
//			current_s = d_s * i;
			next_s = d_s * ((i + 1) % n_kz);
			pnext = spherePoint(next_s, current_t);
			segm.setStart(pprev);
			segm.setFinish(pnext);
			res += segm;
//			current_s = next_s;
			pprev = pnext;
		}
	}
	return res;
}
Point CFIT_6203_Voronkov_Ray_Sphere::spherePoint(double s, double t)const
{
	ASSERT(t >= - M_PI_2 && t <= M_PI_2);
	ASSERT(s >= 0 && s <= 2.0 * M_PI);
	Point res;
	double cos_t = cos(t);
	double sin_t = sin(t);
	double cos_s = cos(s);
	double sin_s = sin(s);
	double lx = cos_t * cos_s * m_radius;
	double ly = cos_t * sin_s * m_radius;
	double lz = sin_t * m_radius;
	res.setX(lx);
	res.setY(ly);
	res.setZ(lz);
	return res + m_center;
}
double CFIT_6203_Voronkov_Ray_Sphere::getMax(int coord) const
{
	ASSERT (coord == 0 || coord == 1 || coord == 2);
	return m_center.get(coord) + m_radius;
}
double CFIT_6203_Voronkov_Ray_Sphere::getMin(int coord) const
{
	ASSERT (coord == 0 || coord == 1 || coord == 2);
	return m_center.get(coord) - m_radius;
}

bool CFIT_6203_Voronkov_Ray_Sphere::calculateIntersection()
{
	const Point & ray_origin = m_ray.getOrigin();
	double x0 = ray_origin.x();
	double y0 = ray_origin.y();
	double z0 = ray_origin.z();

	const Point & ray_direction = m_ray.getDirection();
	double xd = ray_direction.x();
	double yd = ray_direction.y();
	double zd = ray_direction.z();

	double xs = m_center.x();
	double ys = m_center.y();
	double zs = m_center.z();

	double rs = m_radius;

	double B = 2*(xd * (x0 - xs) +  yd * (y0 - ys) +  zd * (z0 - zs));
	double C = (x0 - xs) * (x0 - xs) 
			 + (y0 - ys) * (y0 - ys)
			 + (z0 - zs) * (z0 - zs);
	double E = C - rs * rs;
	double D = B * B - 4.0 * E; // discriminant

	if (D < 0) {
		has_intersection = false;
		return false;
	}
	//double normal_outside = 1.0; // 1.0 if outside and -1.0 if inside
	double t = (- B - sqrt (D)) / 2.0;
	ray_from_outside = true;
	if (t < 0){
		if ((t = (-B + sqrt (D)) / 2.0) < 0){
			has_intersection = false;
			return false;
		}
		ray_from_outside = false;
	}
	m_intersection = ray_origin + ray_direction * t;

	m_t = t;
	has_intersection = true;
	return true;
}
bool CFIT_6203_Voronkov_Ray_Sphere::calculateNormal()
{
	if (!this->has_intersection) return false;

	m_normal.setX((m_intersection.x() - m_center.x()) / m_radius);
	m_normal.setY((m_intersection.y() - m_center.y()) / m_radius);
	m_normal.setZ((m_intersection.z() - m_center.z()) / m_radius);

	return true;
}