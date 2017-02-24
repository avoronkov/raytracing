#include "primitive.h"

#include <QtMath>

namespace rt { namespace model {

void Primitive::setOptics
        (double k_Ar, double k_Ag, double k_Ab, double k_Dr, double k_Dg, double k_Db,
        double k_Sr, double k_Sg, double k_Sb, double power, double kt, double no, double ni)
{
    _kA = Color (k_Ar, k_Ag, k_Ab);
    _kD = Color (k_Dr, k_Dg, k_Db);
    _kS = Color (k_Sr, k_Sg, k_Sb);

    _power = power;
    _kt = kt;
    _n_outside = ni;
    _n_inside = no;
}

void Primitive::intersect(const Ray & ray)
{
    _ray = ray;
    if (!this->isCorrect()) {
        Q_ASSERT(false);
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
bool Primitive::calculateReflected()
{
    if (!has_intersection) return false;
    Point incident_ray = - (_ray.getDirection());
    _reflected = _normal * 2.0 * (_normal * incident_ray) - incident_ray;

    return true;
}

bool Primitive::calculateRefracted()
{
    if (!has_intersection) return false;
    if (ray_from_outside)
    {
        // normal outside
        Point incident_ray = -_ray.getDirection();
        double n_it = _n_outside / _n_inside;
        double cos_teta = ( _normal * incident_ray);
        double D = 1.0 + n_it * n_it * (cos_teta * cos_teta - 1.0);
        if (D <= 0.0){
            has_refracted = false;
            return false;
        }
        _refracted = -incident_ray * n_it + _normal * (n_it * cos_teta - qSqrt (D));
        has_refracted = true;
    }
    else
    {
        // from the inside
        Point incident_ray = -_ray.getDirection();
        double n_it = _n_inside / _n_outside;
        Point normal = -_normal;
        double cos_teta = ( normal * incident_ray);
        double D = 1.0 + n_it * n_it * (cos_teta * cos_teta - 1.0);
        if (D <= 0.0){
            has_refracted = false;
            return false;
        }
        _refracted = -incident_ray * n_it + normal * (n_it * cos_teta - qSqrt (D));
        has_refracted = true;
    }
    return true;
}


}}
