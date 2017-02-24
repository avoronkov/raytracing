#ifndef SPHERE_H
#define SPHERE_H

#include "model/point.h"
#include "model/primitive.h"

namespace rt { namespace model {

class Sphere : public Primitive
{
    Point _center;
    double _radius;

public:
    Sphere();
    Sphere(const Point& center, const double& radius);
    Sphere(const Sphere &) = default;
    ~Sphere() = default;

    const double & getRadius() const;
    const Point & getCenter() const;

    void setRadius(const double & value);
    void setCenter(const Point & center);
    void setCenter(const double& x, const double& y, const double& z);

    Sphere & operator=(const Sphere & obj);

    virtual bool isCorrect() const override;

    virtual enum PrimitiveType getType() const override {return PrimitiveType::SPH;}
    virtual WireFrame getWireFrame() const override;
    virtual double getMax(int coord) const override;
    virtual double getMin(int coord) const override;

    virtual bool calculateIntersection() override;
    virtual bool calculateNormal() override;

private:
    Point spherePoint(double s, double t)const;
};

}}

#endif // SPHERE_H
