#ifndef QUADRIC_H
#define QUADRIC_H

namespace rt { namespace model {

class Point;
class Ray;

class Quadric
{
    double m_a;
    double m_e;
    double m_h;
    double m_b;
    double m_c;
    double m_f;
    double m_d;
    double m_g;
    double m_i;
    double m_j;
public:
    Quadric();
    Quadric(double A, double E, double H, double B,
                                    double C, double F, double D,
                                    double G, double I, double J);
    Quadric(const Quadric &) = default;
    ~Quadric() = default;

    Quadric & operator=(const Quadric &) = default;

    const double & getA() const { return m_a;}
    const double & getE() const { return m_e;}
    const double & getH() const { return m_h;}
    const double & getB() const { return m_b;}
    const double & getC() const { return m_c;}
    const double & getF() const { return m_f;}
    const double & getD() const { return m_d;}
    const double & getG() const { return m_g;}
    const double & getI() const { return m_i;}
    const double & getJ() const { return m_j;}

    bool isCorrect() const;
    // CString toString() const;

    int intersectRay(const Ray & ray, Point * i_near, Point * n_near, Point * refl_near,
        double * t_near, Point * i_far, Point * n_far, Point * refl_far, double * t_far);
    Point getReflected(const Point & ray, const Point & normal)const;

};

}}

#endif // QUADRIC_H
