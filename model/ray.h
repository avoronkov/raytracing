#ifndef RAY_H
#define RAY_H

#include "model/point.h"

namespace rt { namespace model {

class Ray
{
    Point _origin;
    Point _direction;
public:
    Ray() = default;
    Ray(const Ray & r) = default;
    Ray(const Point & origin, const Point & direction);
    Ray(const double& _x, const double& _y, const double& _z,
        const double& dx, const double& dy, const double& dz);
    virtual ~Ray() = default;

    Ray& operator=(const Ray & r) = default;

    const Point & getOrigin() const { return _origin; }
    const Point & getDirection() const { return _direction; }

    void setOrigin(const Point & origin);
    void setDirection(const Point & direction);
    void setDirectionByPoint(const Point & direction);

    Ray operator-() const;

    bool isCorrect() const;
    // CString toString() const;
};

}}

#endif // RAY_H
