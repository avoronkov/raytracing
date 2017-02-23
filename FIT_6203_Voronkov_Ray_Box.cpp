#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_Box.h"

CFIT_6203_Voronkov_Ray_Box::CFIT_6203_Voronkov_Ray_Box()
{
	m_x_high = 0.0;
	m_y_high = 0.0;
	m_z_high = 0.0;
	m_x_low = 0.0;
	m_y_low = 0.0;
	m_z_low = 0.0;
}
CFIT_6203_Voronkov_Ray_Box::CFIT_6203_Voronkov_Ray_Box(const double & x_low, const double & y_low, const double & z_low,
							const double &x_high, const double &y_high, const double &z_high)
{
	m_x_low = x_low;
	m_y_low = y_low;
	m_z_low = z_low;
	m_x_high = x_high;
	m_y_high = y_high;
	m_z_high = z_high;
}
CFIT_6203_Voronkov_Ray_Box::CFIT_6203_Voronkov_Ray_Box
		(const CFIT_6203_Voronkov_Ray_Box & obj)
{
	m_x_low = obj.m_x_low;
	m_y_low = obj.m_y_low;
	m_z_low = obj.m_z_low;
	m_x_high = obj.m_x_high;
	m_y_high = obj.m_y_high;
	m_z_high = obj.m_z_high;
}
CFIT_6203_Voronkov_Ray_Box::~CFIT_6203_Voronkov_Ray_Box()
{}

const double & CFIT_6203_Voronkov_Ray_Box::getXMax() const
{
	return m_x_high;
}
const double & CFIT_6203_Voronkov_Ray_Box::getXMin() const
{
	return m_x_low;
}
const double & CFIT_6203_Voronkov_Ray_Box::getYMax() const
{
	return m_y_high;
}
const double & CFIT_6203_Voronkov_Ray_Box::getYMin() const
{
	return m_y_low;
}
const double & CFIT_6203_Voronkov_Ray_Box::getZMax() const
{
	return m_z_high;
}
const double & CFIT_6203_Voronkov_Ray_Box::getZMin() const
{
	return m_z_low;
}
Point CFIT_6203_Voronkov_Ray_Box::getMin() const
{
	return Point(m_x_low, m_y_low, m_z_low);
}
Point CFIT_6203_Voronkov_Ray_Box::getMax() const
{
	return Point(m_x_high, m_y_high, m_z_high);
}
CFIT_6203_Voronkov_Ray_Box & CFIT_6203_Voronkov_Ray_Box::operator=
		(const CFIT_6203_Voronkov_Ray_Box & obj)
{
	m_x_low = obj.m_x_low;
	m_x_high = obj.m_x_high;
	m_y_low = obj.m_y_low;
	m_y_high = obj.m_y_high;
	m_z_low = obj.m_z_low;
	m_z_high = obj.m_z_high;
	return * this;
}
void CFIT_6203_Voronkov_Ray_Box::setMax(const double & x, const double & y, const double & z)
{
	m_x_high = x;
	m_y_high = y;
	m_z_high = z;
}
void CFIT_6203_Voronkov_Ray_Box::setMin(const double & x, const double & y, const double & z)
{
	m_x_low = x;
	m_y_low = y;
	m_z_low = z;
}
CString CFIT_6203_Voronkov_Ray_Box::toString() const
{
	CString res;
	res.Format("[Box:(%.5lf, %.5lf, %.5lf),(%.5lf, %.5lf, %.5lf)]\n", 
			m_x_low, m_y_low, m_z_low, m_x_high, m_y_high, m_z_high);
	return res;
}

bool CFIT_6203_Voronkov_Ray_Box::isCorrect() const
{
	if (m_x_low > m_x_high || m_y_low > m_y_high || m_z_low > m_z_high){
		return false;
	}
	return true;
}
WireFrame CFIT_6203_Voronkov_Ray_Box::getWireFrame() const
{
	WireFrame res;

	res += Segment(m_x_high, m_y_high, m_z_high, m_x_low, m_y_high, m_z_high);
	res += Segment(m_x_high, m_y_high, m_z_low, m_x_low, m_y_high, m_z_low);
	res += Segment(m_x_high, m_y_low, m_z_high, m_x_low, m_y_low, m_z_high);
	res += Segment(m_x_high, m_y_low, m_z_low, m_x_low, m_y_low, m_z_low);

	res += Segment(m_x_high, m_y_high, m_z_high, m_x_high, m_y_low, m_z_high);
	res += Segment(m_x_high, m_y_high, m_z_low, m_x_high, m_y_low, m_z_low);
	res += Segment(m_x_low, m_y_high, m_z_high, m_x_low, m_y_low, m_z_high);
	res += Segment(m_x_low, m_y_high, m_z_low, m_x_low, m_y_low, m_z_low);

	res += Segment(m_x_high, m_y_high, m_z_high, m_x_high, m_y_high, m_z_low);
	res += Segment(m_x_high, m_y_low, m_z_high, m_x_high, m_y_low, m_z_low);
	res += Segment(m_x_low, m_y_high, m_z_high, m_x_low, m_y_high, m_z_low);
	res += Segment(m_x_low, m_y_low, m_z_high, m_x_low, m_y_low, m_z_low);

	return res;
}

Point CFIT_6203_Voronkov_Ray_Box::getVertex(int num) const
{
	switch(num)
	{
	case 0: return Point(m_x_low, m_y_low, m_z_low);
	case 1: return Point(m_x_low, m_y_high, m_z_low);
	case 2: return Point(m_x_high, m_y_high, m_z_low);
	case 3: return Point(m_x_high, m_y_low, m_z_low);
	case 4: return Point(m_x_low, m_y_low, m_z_high);
	case 5: return Point(m_x_low, m_y_high, m_z_high);
	case 6: return Point(m_x_high, m_y_high, m_z_high);
	case 7: return Point(m_x_high, m_y_low, m_z_high);
	default: ASSERT (false);
	}
	return Point();
}
double CFIT_6203_Voronkov_Ray_Box::getMax(int coord) const
{
	switch (coord)
	{
	case 0: return m_x_high;
	case 1: return m_y_high;
	case 2: return m_z_high;
	}
	ASSERT (false);
	return 0;
}
double CFIT_6203_Voronkov_Ray_Box::getMin(int coord) const
{
	switch (coord)
	{
	case 0: return m_x_low;
	case 1: return m_y_low;
	case 2: return m_z_low;
	}
	ASSERT (false);
	return 0;
}
bool CFIT_6203_Voronkov_Ray_Box::calculateIntersection()
{
	const Point & ray_origin = m_ray.getOrigin();

	const Point & ray_direction = m_ray.getDirection();
	double xd = ray_direction.x();
	double yd = ray_direction.y();
	double zd = ray_direction.z();

	Point box_min = getMin();
	Point box_max = getMax();

	double t_near = 0.0;
	double t_far = 0.0;
	bool t_near_inf = true; // t_near == -inf
	bool t_far_inf = true; // t_far == +inf
	int t_near_plane = 0; // index of plane for t near
	int t_far_plane = 0; // index of plane for t far
	
	for (int i=0; i<3; i++) // for all planes
	{
		// For planes
		double orig_c = ray_origin.get(i); // component of ray's origin
		double box_min_c = box_min.get(i); // minimal component of box
		double box_max_c = box_max.get(i); // minimal component of box
		double d_c = ray_direction.get(i); // ray direction's component
		if (d_c == 0)
		{
			if (orig_c < box_min_c || orig_c > box_max_c) return false; // no intersections
		}
		else
		{
			double t1 = (box_min_c - orig_c) / d_c;
			double t2 = (box_max_c - orig_c) / d_c;
			
			if (t2 < t1){
				double tmp = t1;
				t1 = t2;
				t2 = tmp;
			}
			
			if (t_near_inf || t1 > t_near){
				t_near = t1;
				t_near_inf = false;
				t_near_plane = i;
			}
			if (t_far_inf || t2 < t_far){
				t_far = t2;
				t_far_inf = false;
				t_far_plane = i;
			}
			if (t_near > t_far) {
				has_intersection = false;
				return false;
			}
			if (t_far < 0) {
				has_intersection = false;
				return false;
			}
		}
	}
	if (t_near > 0)
	{
		// use t_near
		ray_from_outside = true;
		m_intersection = m_ray.getOrigin() + m_ray.getDirection() * t_near;
		m_t = t_near;
		has_intersection = true;
		if (t_near_plane == 0){
			// x plane
			if (xd > 0){
				m_normal = Point(-1, 0, 0);
			} else{
				m_normal = Point(1, 0, 0);
			}
		}
		else if (t_near_plane == 1){
			// y plane
			if (yd >0){
				m_normal = Point(0, -1, 0);
			}
			else{
				m_normal = Point(0, 1, 0);
			}
		}
		else if (t_near_plane == 2){
			// z plane
			if (zd > 0){
				m_normal = Point(0, 0, -1);
			}
			else{
				m_normal = Point(0, 0, 1);
			}
		}
	}
	else
	{
		// use t_far
		ray_from_outside = false;
		m_intersection = m_ray.getOrigin() + m_ray.getDirection() * t_far;
		m_t = t_far;
		switch (t_far_plane)
		{
		case 0:{ // x plane
			if (xd > 0) m_normal = Point(1, 0, 0);
			else m_normal = Point(-1, 0, 0);
			break;
			   }
		case 1:{ // y plane
			if (yd > 0) m_normal = Point(0, 1, 0);
			else m_normal = Point(0, -1, 0);
			break;
			   }
		case 2:{ // z plane
			if (zd > 0) m_normal = Point(0, 0, 1);
			else m_normal = Point(0, 0, -1);
			break;
			   }
		default:{}
		}
	}
	return true;
}
bool CFIT_6203_Voronkov_Ray_Box::calculateNormal()
{
	if (!this->has_intersection) return false;

	// all calculations have been already made in calculateIntersection() method

	return true;
}
bool CFIT_6203_Voronkov_Ray_Box::isInside(const Point & point)const
{
	if (point.x() < m_x_low || point.x() > m_x_high) return false;
	if (point.y() < m_y_low || point.y() > m_y_high) return false;
	if (point.z() < m_z_low || point.z() > m_z_high) return false;
	return true;
}