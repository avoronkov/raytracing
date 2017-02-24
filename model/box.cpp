#include "box.h"

#include "model/wireframe.h"

namespace rt { namespace model {

Box::Box(): Box{0, 0, 0, 0, 0, 0}
{

}

Box::Box(const double & x_low, const double & y_low, const double & z_low,
        const double &x_high, const double &y_high, const double &z_high):
    _x_low{x_low}, _y_low{y_low}, _z_low{z_low},
    _x_high{x_high}, _y_high{y_high}, _z_high{z_high}
{
}

Point Box::getMin() const
{
    return Point(_x_low, _y_low, _z_low);
}
Point Box::getMax() const
{
    return Point(_x_high, _y_high, _z_high);
}

void Box::setMax(const double & x, const double & y, const double & z)
{
    _x_high = x;
    _y_high = y;
    _z_high = z;
}
void Box::setMin(const double & x, const double & y, const double & z)
{
    _x_low = x;
    _y_low = y;
    _z_low = z;
}

bool Box::isCorrect() const {
    return _x_low <= _x_high && _y_low <= _y_high && _z_low <= _z_high;
}

WireFrame Box::getWireFrame() const
{
    WireFrame res;

    res += Segment(_x_high, _y_high, _z_high, _x_low, _y_high, _z_high);
    res += Segment(_x_high, _y_high, _z_low, _x_low, _y_high, _z_low);
    res += Segment(_x_high, _y_low, _z_high, _x_low, _y_low, _z_high);
    res += Segment(_x_high, _y_low, _z_low, _x_low, _y_low, _z_low);

    res += Segment(_x_high, _y_high, _z_high, _x_high, _y_low, _z_high);
    res += Segment(_x_high, _y_high, _z_low, _x_high, _y_low, _z_low);
    res += Segment(_x_low, _y_high, _z_high, _x_low, _y_low, _z_high);
    res += Segment(_x_low, _y_high, _z_low, _x_low, _y_low, _z_low);

    res += Segment(_x_high, _y_high, _z_high, _x_high, _y_high, _z_low);
    res += Segment(_x_high, _y_low, _z_high, _x_high, _y_low, _z_low);
    res += Segment(_x_low, _y_high, _z_high, _x_low, _y_high, _z_low);
    res += Segment(_x_low, _y_low, _z_high, _x_low, _y_low, _z_low);

    return res;
}

Point Box::getVertex(int num) const
{
    switch(num)
    {
    case 0: return Point(_x_low, _y_low, _z_low);
    case 1: return Point(_x_low, _y_high, _z_low);
    case 2: return Point(_x_high, _y_high, _z_low);
    case 3: return Point(_x_high, _y_low, _z_low);
    case 4: return Point(_x_low, _y_low, _z_high);
    case 5: return Point(_x_low, _y_high, _z_high);
    case 6: return Point(_x_high, _y_high, _z_high);
    case 7: return Point(_x_high, _y_low, _z_high);
    default: Q_ASSERT (false);
    }
    return Point();
}

double Box::getMax(int coord) const
{
    switch (coord)
    {
    case 0: return _x_high;
    case 1: return _y_high;
    case 2: return _z_high;
    }
    Q_ASSERT (false);
    return 0;
}

double Box::getMin(int coord) const
{
    switch (coord)
    {
    case 0: return _x_low;
    case 1: return _y_low;
    case 2: return _z_low;
    }
    Q_ASSERT (false);
    return 0;
}

bool Box::calculateIntersection()
{
    const Point & ray_origin = _ray.getOrigin();

    const Point & ray_direction = _ray.getDirection();
    double xd = ray_direction.x();
    double yd = ray_direction.y();
    double zd = ray_direction.z();

    Point box_min = getMin();
    Point box_max = getMax();

    double t_near = 0.0;
    double t_far = 0.0;
    bool t_near_inf = true; // t_near == -inf
    bool t_far_inf = true; // t_far == +inf
    int t_near_plane = 0; // index of plane for t near
    int t_far_plane = 0; // index of plane for t far

    for (int i=0; i<3; i++) // for all planes
    {
        // For planes
        double orig_c = ray_origin.get(i); // component of ray's origin
        double box_min_c = box_min.get(i); // minimal component of box
        double box_max_c = box_max.get(i); // minimal component of box
        double d_c = ray_direction.get(i); // ray direction's component
        if (d_c == 0)
        {
            if (orig_c < box_min_c || orig_c > box_max_c) return false; // no intersections
        }
        else
        {
            double t1 = (box_min_c - orig_c) / d_c;
            double t2 = (box_max_c - orig_c) / d_c;

            if (t2 < t1){
                double tmp = t1;
                t1 = t2;
                t2 = tmp;
            }

            if (t_near_inf || t1 > t_near){
                t_near = t1;
                t_near_inf = false;
                t_near_plane = i;
            }
            if (t_far_inf || t2 < t_far){
                t_far = t2;
                t_far_inf = false;
                t_far_plane = i;
            }
            if (t_near > t_far) {
                has_intersection = false;
                return false;
            }
            if (t_far < 0) {
                has_intersection = false;
                return false;
            }
        }
    }
    if (t_near > 0)
    {
        // use t_near
        ray_from_outside = true;
        _intersection = _ray.getOrigin() + _ray.getDirection() * t_near;
        _t = t_near;
        has_intersection = true;
        if (t_near_plane == 0){
            // x plane
            if (xd > 0){
                _normal = Point(-1, 0, 0);
            } else{
                _normal = Point(1, 0, 0);
            }
        }
        else if (t_near_plane == 1){
            // y plane
            if (yd >0){
                _normal = Point(0, -1, 0);
            }
            else{
                _normal = Point(0, 1, 0);
            }
        }
        else if (t_near_plane == 2){
            // z plane
            if (zd > 0){
                _normal = Point(0, 0, -1);
            }
            else{
                _normal = Point(0, 0, 1);
            }
        }
    }
    else
    {
        // use t_far
        ray_from_outside = false;
        _intersection = _ray.getOrigin() + _ray.getDirection() * t_far;
        _t = t_far;
        switch (t_far_plane)
        {
        case 0:{ // x plane
            if (xd > 0) _normal = Point(1, 0, 0);
            else _normal = Point(-1, 0, 0);
            break;
               }
        case 1:{ // y plane
            if (yd > 0) _normal = Point(0, 1, 0);
            else _normal = Point(0, -1, 0);
            break;
               }
        case 2:{ // z plane
            if (zd > 0) _normal = Point(0, 0, 1);
            else _normal = Point(0, 0, -1);
            break;
               }
        default:{}
        }
    }
    return true;
}
bool Box::calculateNormal()
{
    if (!this->has_intersection) return false;

    // all calculations have been already made in calculateIntersection() method

    return true;
}
bool Box::isInside(const Point & point)const
{
    if (point.x() < _x_low || point.x() > _x_high) return false;
    if (point.y() < _y_low || point.y() > _y_high) return false;
    if (point.z() < _z_low || point.z() > _z_high) return false;
    return true;
}

}}
