#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "model/color.h"
#include "model/ray.h"

namespace rt { namespace model {

enum class PrimitiveType {SPH, BOX, PLG, QDR};

class WireFrame;

class Primitive
{
    Color _kA; // ambient factor
    Color _kD; // diffuse factor
    Color _kS; // specular factor

    double m_power;

    double m_kt;

    double m_n_outside;
    double m_n_inside;

    Ray m_ray;

    bool has_intersection;
    Point m_intersection;
    Point m_normal;
    Point m_reflected;
    bool has_refracted;
    Point m_refracted;

    double m_t;

    bool ray_from_outside;

public:
    virtual PrimitiveType getType() const = 0;
    virtual WireFrame getWireFrame() const = 0;
    virtual double getMax(int coord) const = 0;
    virtual double getMin(int coord) const = 0;
    void setOptics(double k_Ar, double k_Ag, double k_Ab, double k_Dr, double k_Dg, double k_Db,
                double k_Sr, double k_Sg, double k_Sb, double power, double kt, double no, double ni);

    const Color & getAmbientFactor()const { return _kA; }
    const Color & getDiffuseFactor() const { return _kD; }
    const Color & getSpecularFactor() const { return _kS; }

    const double & getPower() const{return m_power;}

    virtual void intersect(const Ray & ray);

    virtual bool calculateIntersection() = 0;
    virtual bool calculateNormal() = 0;
    bool calculateReflected();
    bool calculateRefracted();

    virtual bool hasIntersection()const {return has_intersection;}
    virtual const Point & getIntersection()const {return m_intersection;}
    virtual const double & getT()const {return m_t;}
    virtual const Point & getNormal()const {return m_normal;}
    virtual const Point & getReflected()const {return m_reflected;}
    virtual bool hasRefracted()const {return has_refracted;}
    virtual const Point & getRefracted()const {return m_refracted;}

    virtual bool isCorrect()const = 0;

};

}}

#endif // PRIMITIVE_H
