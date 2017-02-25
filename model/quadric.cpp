#include "quadric.h"

#include "model/point.h"
#include "model/ray.h"

#include <QtMath>

namespace rt { namespace model {
Quadric::Quadric(): Quadric{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
{

}

Quadric::Quadric(double A, double E, double H, double B,
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

bool Quadric::isCorrect() const
{
    // TODO checking for correction
    return true;
}

int Quadric::intersectRay
        (const Ray & ray, Point * i_near, Point * n_near, Point * refl_near, double * t_near,
        Point * i_far, Point * n_far, Point * refl_far, double * t_far)
{
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
        double to = (- c_b - qSqrt (D)) / (2 * c_a);
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

            Q_ASSERT (n_far->get(0) != 0 && n_far->get(1) != 0 && n_far->get(2) != 0);

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

Point Quadric::getReflected
        (const Point & ray, const Point & normal)const
{
    Point incident_ray = - (ray);
    return normal * 2.0 * (normal * incident_ray) - incident_ray;
}

}}
