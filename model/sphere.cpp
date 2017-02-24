#include "sphere.h"
#include "model/wireframe.h"

#include <QtMath>

namespace rt { namespace model {

#define N 10
#define M 10
#define KZ 1

Sphere::Sphere(): Sphere{Point{}, 0.0}
{
}

Sphere::Sphere(const Point & center, const double & radius):
    _center{center}, _radius{radius}
{
}

const double & Sphere::getRadius() const
{
    return _radius;
}
const Point & Sphere::getCenter() const
{
    return _center;
}

void Sphere::setRadius(const double & value)
{
    _radius = value;
}
void Sphere::setCenter(const Point & center)
{
    _center = center;
}
void Sphere::setCenter(const double& x, const double& y, const double& z)
{
    _center = Point(x, y, z);
}

bool Sphere::isCorrect() const {
    return _radius > 0.0;
}

WireFrame Sphere::getWireFrame() const
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
Point Sphere::spherePoint(double s, double t)const
{
    Q_ASSERT(t >= - M_PI_2 && t <= M_PI_2);
    Q_ASSERT(s >= 0 && s <= 2.0 * M_PI);
    Point res;
    double cos_t = qCos(t);
    double sin_t = qSin(t);
    double cos_s = qCos(s);
    double sin_s = qSin(s);
    double lx = cos_t * cos_s * _radius;
    double ly = cos_t * sin_s * _radius;
    double lz = sin_t * _radius;
    res.setX(lx);
    res.setY(ly);
    res.setZ(lz);
    return res + _center;
}
double Sphere::getMax(int coord) const
{
    Q_ASSERT (coord == 0 || coord == 1 || coord == 2);
    return _center.get(coord) + _radius;
}
double Sphere::getMin(int coord) const
{
    Q_ASSERT (coord == 0 || coord == 1 || coord == 2);
    return _center.get(coord) - _radius;
}

bool Sphere::calculateIntersection()
{
    const Point & ray_origin = _ray.getOrigin();
    double x0 = ray_origin.x();
    double y0 = ray_origin.y();
    double z0 = ray_origin.z();

    const Point & ray_direction = _ray.getDirection();
    double xd = ray_direction.x();
    double yd = ray_direction.y();
    double zd = ray_direction.z();

    double xs = _center.x();
    double ys = _center.y();
    double zs = _center.z();

    double rs = _radius;

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
    double t = (- B - qSqrt (D)) / 2.0;
    ray_from_outside = true;
    if (t < 0){
        if ((t = (-B + qSqrt (D)) / 2.0) < 0){
            has_intersection = false;
            return false;
        }
        ray_from_outside = false;
    }
    _intersection = ray_origin + ray_direction * t;

    _t = t;
    has_intersection = true;
    return true;
}
bool Sphere::calculateNormal()
{
    if (!this->has_intersection) return false;

    _normal.setX((_intersection.x() - _center.x()) / _radius);
    _normal.setY((_intersection.y() - _center.y()) / _radius);
    _normal.setZ((_intersection.z() - _center.z()) / _radius);

    return true;
}

}}
