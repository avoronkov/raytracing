#ifndef BOX_H
#define BOX_H

#include "model/point.h"
#include "model/primitive.h"

namespace rt { namespace model {

class Box : public Primitive
{
    double _x_low;
    double _y_low;
    double _z_low;
    double _x_high;
    double _y_high;
    double _z_high;
public:
    Box();
    Box(const double & x_low, const double & y_low, const double & z_low,
        const double &x_high, const double &y_high, const double &z_high);
    Box(const Box &) = default;
    virtual ~Box() = default;

    Box & operator=(const Box &) = default;

    const double & getXMax() const { return _x_high; }
    const double & getXMin() const { return _x_low; }
    const double & getYMax() const { return _y_high; }
    const double & getYMin() const { return _y_low; }
    const double & getZMax() const { return _z_high; }
    const double & getZMin() const { return _z_low; }

    Point getVertex(int num) const; // from 0 to 7

    Point getMin() const;
    Point getMax() const;

    void setMax(const double & x, const double & y, const double & z);
    void setMin(const double & x, const double & y, const double & z);


    // CString toString() const;
    bool isCorrect() const;

    enum PrimitiveType getType() const{return PrimitiveType::BOX;}
    virtual WireFrame getWireFrame() const override;
    virtual double getMax(int coord) const override;
    virtual double getMin(int coord) const override;

    bool isInside(const Point & point)const;

    virtual bool calculateIntersection() override;
    virtual bool calculateNormal() override;
};

}}

#endif // BOX_H
