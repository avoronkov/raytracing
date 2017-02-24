#include "ray.h"

namespace rt { namespace model {

Ray::Ray(const Point & origin, const Point & direction):
    _origin{origin},
    _direction{direction}
{
    _direction.normalizeLength();
}

Ray::Ray(const double& _x, const double& _y, const double& _z,
         const double& dx, const double& dy, const double& dz):
    _origin{_x, _y, _z},
    _direction{dx, dy, dz}
{
    _direction.normalizeLength();
}

void Ray::setOrigin(const Point & origin)
{
    _origin = origin;
}

void Ray::setDirection(const Point & direction)
{
    _direction = direction;
    _direction.normalizeLength();
}

void Ray::setDirectionByPoint(const Point & point)
{
    _direction = point - _origin;
    _direction.normalizeLength();
}

Ray Ray::operator-() const
{
    return Ray(_origin, -_direction);
}

bool Ray::isCorrect() const {
    return _direction.x() != 0 || _direction.y() != 0 || _direction.z() != 0;
}

}} // namespace rt::model
