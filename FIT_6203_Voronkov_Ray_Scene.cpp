#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_Scene.h"

CFIT_6203_Voronkov_Ray_Scene::CFIT_6203_Voronkov_Ray_Scene()
{
	m_min_coords[0] = 1;
	m_min_coords[1] = 1;
	m_min_coords[2] = 1;
	m_max_coords[0] = -1;
	m_max_coords[1] = -1;
	m_max_coords[2] = -1;
}
CFIT_6203_Voronkov_Ray_Scene::~CFIT_6203_Voronkov_Ray_Scene()
{

}

void CFIT_6203_Voronkov_Ray_Scene::addPrimitive(Primitive * p)
{
	m_prims.Add(p);

	// evaluating new limits
	double current_max, current_min;
	for (int i=0; i<3; i++){
		current_max = p->getMax(i);
		current_min = p->getMin(i);
		if (m_min_coords[i] > m_max_coords[i] || current_min < m_min_coords[i]){
			m_min_coords[i] = current_min;
		}
		if (m_min_coords[i] > m_max_coords[i] || current_max > m_max_coords[i]){
			m_max_coords[i] = current_max;
		}
	}
}
WireFrame CFIT_6203_Voronkov_Ray_Scene::getWireFrame() const
{
	WireFrame wire_frame;

	for (int i=0; i<m_prims.GetSize(); i++){
		wire_frame += m_prims[i]->getWireFrame();
	}
	for (int i=0; i<3; i++)
	{
		wire_frame.setOuterBoxMax(i, m_max_coords[i]);
		wire_frame.setOuterBoxMin(i, m_min_coords[i]);
	}
	return wire_frame;
}
double CFIT_6203_Voronkov_Ray_Scene::getMax(int coord) const
{
	ASSERT (coord == 0 || coord == 1 || coord == 2);
	return m_max_coords[coord];
}
double CFIT_6203_Voronkov_Ray_Scene::getMin(int coord) const
{
	ASSERT (coord == 0 || coord == 1 || coord == 2);
	return m_min_coords[coord];
}
void CFIT_6203_Voronkov_Ray_Scene::setAmbientColor(const Color & color)
{
	m_ambient = color;
}
void CFIT_6203_Voronkov_Ray_Scene::addLight(const Light & light)
{
	m_lights.Add(light);
}

int CFIT_6203_Voronkov_Ray_Scene::countPrimitives() const // количество примитивов
{
	return m_prims.GetSize();
}
int CFIT_6203_Voronkov_Ray_Scene::countLights() const // количество источников света
{
	return m_lights.GetSize();
}

const Color & CFIT_6203_Voronkov_Ray_Scene::ambientColor() const
{
	return m_ambient;
}
const Light & CFIT_6203_Voronkov_Ray_Scene::light(int i) const
{
	ASSERT(i>=0 && i<m_lights.GetSize());
	return m_lights.GetAt(i);
}
Primitive * CFIT_6203_Voronkov_Ray_Scene::primitive(int i)
{
	ASSERT(i>=0 && i<m_prims.GetSize());
	return m_prims.GetAt(i);
}
bool CFIT_6203_Voronkov_Ray_Scene::intersect
		(const Ray & ray, Ray * reflecred,  Ray * normal, Primitive ** pprim)
{
	int count = m_prims.GetSize();
	bool has_i = false;
	double min_t = 0;
	int min_prim = 0;
	for (int i=0; i<count; i++)
	{
		m_prims[i]->intersect(ray);
		if (m_prims[i]->hasIntersection())
		{
			double current_t = m_prims[i]->getT();
			ASSERT(current_t >= 0);
			if (!has_i || current_t < min_t)
			{
				min_t = current_t;
				has_i = true;
				min_prim = i;
			}
		}
	}
	if (!has_i) return false;
	*reflecred = Ray(m_prims[min_prim]->getIntersection(), m_prims[min_prim]->getReflected());
	*normal = Ray(m_prims[min_prim]->getIntersection(), m_prims[min_prim]->getNormal());
	*pprim = m_prims[min_prim];
	return true;
}
//Color CFIT_6203_Voronkov_Ray_Scene::countTotalDiffuseLight
//		(const Ray & normal, const Color & factor)const
//{
//	int light_count = m_lights.GetSize();
//	Color res(0, 0, 0);
//	const Point & point = normal.getOrigin();
//	for (int i=0; i<light_count; i++)
//	{
//		if (lightIsVisible(point, m_lights[i].position())
//		{
//			// 
//		}
//	}
//}
Color CFIT_6203_Voronkov_Ray_Scene::countDiffuseLight
		(const Ray & normal, const Color & factor, int light_idx)const
{
	ASSERT (light_idx >=0 && light_idx < m_lights.GetSize());
	const Point & light = m_lights[light_idx].position();
	double cos_fi = normal.getDirection().cos(light - normal.getOrigin());
	if (cos_fi < 0) cos_fi = 0;
	return factor * cos_fi;
}
int CFIT_6203_Voronkov_Ray_Scene::lightIsVisible
		(const Point & point, const Point & light)const
{
	int size = this->m_prims.GetSize();
	double length = (light - point).length();
	Ray ray;
	ray.setOrigin(point);
	ray.setDirectionByPoint(light);
	for (int i=0; i<size; i++)
	{
		m_prims[i]->intersect(ray);
		if (m_prims[i]->hasIntersection()){
			if (m_prims[i]->getT() < length){
				return 0;
			}
		}
	}
	return 1;
}
Color CFIT_6203_Voronkov_Ray_Scene::countSpecularLight
		(const Ray & normal, Point to_eye, const Color & factor, int light_idx, double power)const
{
	ASSERT (light_idx >=0 && light_idx < m_lights.GetSize());
	const Point & light = m_lights[light_idx].position();
	Point intersection = normal.getOrigin();
	Point to_light = light - intersection;
//	Point to_eye = eye.getDirection();
	to_light.normalizeLength();
	to_eye.normalizeLength();
	Point bisectr = to_light + to_eye;
	double cos_f = bisectr.cos(normal.getDirection());
//	ASSERT (cos_f >= 0 && cos_f <=1);
	double pow_cos_f;
	if (cos_f < 0) pow_cos_f = 0;
	else pow_cos_f = pow(cos_f, power);
	return  factor * pow_cos_f;
}
int CFIT_6203_Voronkov_Ray_Scene::lightIsVisible
		(const Point & point, int light_idx)const
{	
	int size = this->m_prims.GetSize();
	const Point & light = m_lights[light_idx].position();
	double length = (light - point).length();
	Ray ray;
	ray.setOrigin(point);
	ray.setDirectionByPoint(light);
	for (int i=0; i<size; i++)
	{
		m_prims[i]->intersect(ray);
		if (m_prims[i]->hasIntersection()){
			if (m_prims[i]->getT() < length){
				return 0;
			}
		}
	}
	return 1;
}