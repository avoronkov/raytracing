#include "scene.h"
#include "model/wireframe.h"

#include <QtMath>

namespace rt { namespace model {

Scene::Scene()
{
    m_min_coords[0] = 1;
    m_min_coords[1] = 1;
    m_min_coords[2] = 1;
    m_max_coords[0] = -1;
    m_max_coords[1] = -1;
    m_max_coords[2] = -1;
}

void Scene::addPrimitive(QSharedPointer<Primitive> p)
{
    m_prims.append(p);

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

void Scene::addPrimitive(Primitive * p)
{
    addPrimitive(QSharedPointer<Primitive>(p));
}

WireFrame Scene::getWireFrame() const
{
    WireFrame wire_frame;

    for (int i=0; i<m_prims.size(); i++){
        wire_frame += m_prims[i]->getWireFrame();
    }
    for (int i=0; i<3; i++)
    {
        wire_frame.setOuterBoxMax(i, m_max_coords[i]);
        wire_frame.setOuterBoxMin(i, m_min_coords[i]);
    }
    return wire_frame;
}

double Scene::getMax(int coord) const
{
    Q_ASSERT (coord == 0 || coord == 1 || coord == 2);
    return m_max_coords[coord];
}
double Scene::getMin(int coord) const
{
    Q_ASSERT (coord == 0 || coord == 1 || coord == 2);
    return m_min_coords[coord];
}
void Scene::setAmbientColor(const Color & color)
{
    m_ambient = color;
}
void Scene::addLight(const Light & light)
{
    m_lights.append(light);
}

int Scene::countPrimitives() const // êîëè÷åñòâî ïðèìèòèâîâ
{
    return m_prims.size();
}
int Scene::countLights() const // êîëè÷åñòâî èñòî÷íèêîâ ñâåòà
{
    return m_lights.size();
}

const Color & Scene::ambientColor() const
{
    return m_ambient;
}

const Light & Scene::light(int i) const
{
    Q_ASSERT(i>=0 && i<m_lights.size());
    return m_lights[i];
}

QSharedPointer<Primitive> Scene::primitive(int i) const
{
    Q_ASSERT(i>=0 && i<m_prims.size());
    return m_prims[i];
}

bool Scene::intersect
        (const Ray & ray, Ray * reflecred,  Ray * normal, Primitive ** pprim)
{
    int count = m_prims.size();
    bool has_i = false;
    double min_t = 0;
    int min_prim = 0;
    for (int i=0; i<count; i++)
    {
        m_prims[i]->intersect(ray);
        if (m_prims[i]->hasIntersection())
        {
            double current_t = m_prims[i]->getT();
            Q_ASSERT(current_t >= 0);
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
    *pprim = m_prims[min_prim].data();
    return true;
}

Color Scene::countDiffuseLight
        (const Ray & normal, const Color & factor, int light_idx)const
{
    Q_ASSERT (light_idx >=0 && light_idx < m_lights.size());
    const Point & light = m_lights[light_idx].position();
    double cos_fi = normal.getDirection().cos(light - normal.getOrigin());
    if (cos_fi < 0) cos_fi = 0;
    return factor * cos_fi;
}

bool Scene::pointIsVisible(const Point & point, const Point & light)const
{
    int size = this->m_prims.size();
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

Color Scene::countSpecularLight
        (const Ray & normal, Point to_eye, const Color & factor, int light_idx, double power)const
{
    Q_ASSERT (light_idx >=0 && light_idx < m_lights.size());
    const Point & light = m_lights[light_idx].position();
    Point intersection = normal.getOrigin();
    Point to_light = light - intersection;
//  Point to_eye = eye.getDirection();
    to_light.normalizeLength();
    to_eye.normalizeLength();
    Point bisectr = to_light + to_eye;
    double cos_f = bisectr.cos(normal.getDirection());
//  Q_ASSERT (cos_f >= 0 && cos_f <=1);
    double pow_cos_f;
    if (cos_f < 0) pow_cos_f = 0;
    else pow_cos_f = qPow(cos_f, power);
    return  factor * pow_cos_f;
}

bool Scene::lightIsVisible
        (const Point & point, int light_idx)const
{
    int size = this->m_prims.size();
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

}}
