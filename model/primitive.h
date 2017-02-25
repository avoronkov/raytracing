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

    double _power;

    double _kt;

    double _n_outside;
    double _n_inside;

protected:
    Ray _ray;
    bool has_intersection;
    Point _intersection;
    Point _normal;
    Point _reflected;

private:
    bool has_refracted;
    Point _refracted;

protected:
    double _t; // ??
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

    const double & getPower() const{return _power;}

    virtual void intersect(const Ray & ray);

    virtual bool calculateIntersection() = 0;
    virtual bool calculateNormal() = 0;
    bool calculateReflected();
    bool calculateRefracted();

    virtual bool hasIntersection()const {return has_intersection;}
    virtual const Point & getIntersection()const {return _intersection;}
    virtual const double & getT()const {return _t;}
    virtual const Point & getNormal()const {return _normal;}
    virtual const Point & getReflected()const {return _reflected;}
    virtual bool hasRefracted()const {return has_refracted;}
    virtual const Point & getRefracted()const {return _refracted;}

    virtual bool isCorrect()const = 0;

};

}}

#endif // PRIMITIVE_H
