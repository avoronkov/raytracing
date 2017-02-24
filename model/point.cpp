#include "point.h"
#include <initializer_list>
#include <QtMath>

namespace rt { namespace model {

Point::Point()
{
    v[0] = v[1] = v[2] = v[3] = 0.0;
}

Point::~Point()
{
    //
}

Point::Point(double x, double y, double z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 0.0;
}

Point::Point(const Point & p)
{
    for(int i: {0, 1, 2, 3}) {
        v[i] = p.v[i];
    }
}

Point & Point::operator=(const Point & p) {
    if (this != &p) {
        for(int i: {0, 1, 2, 3}) {
        v[i] = p.v[i];
        }
    }
    return *this;
}

Point & Point::operator+=(const Point & p) {
    for(int i: {0, 1, 2}) { // skip w
        v[i] += p.v[i];
    }
    return *this;
}

Point Point::operator+(const Point & p) const {
    Point res;
    for (int i: {0, 1, 2}) {
        res.v[i] = v[i] + p.v[i];
    }
    res.v[3] = 1.0;
    return res;
}

Point Point::operator-(const Point & p) const {
    Point res;
    for (int i: {0, 1, 2}) {
        res.v[i] = v[i] - p.v[i];
    }
    res.v[3] = 1.0;
    return res;
}

Point Point::operator-() const {
    Point res;
    for (int i: {0, 1, 2}) {
        res.v[i] = -v[i];
    }
    res.v[3] = 1.0;
    return res;
}

Point Point::operator*(const double & value) const {
    Point res;
    for (int i: {0, 1, 2}) {
        res.v[i] = v[i] * value;
    }
    res.v[3] = 1.0;
    return res;
}

double Point::operator*(const Point & p) const {
    double res = 0.0;
    for (int i: {0, 1, 2}) {
        res += v[i] * p.v[i];
    }
    return res;
}

double Point::get(int idx) const {
    Q_ASSERT(idx >= 0 && idx < 3);
    return v[idx];
}

void Point::set(int idx, double value) {
    Q_ASSERT(idx >= 0 && idx < 3);
    v[idx] = value;
}

double Point::length() const {
    return qSqrt((*this) * (*this));
}

double Point::cos(const Point & p) const {
    Point a = *this;
    Point b = p;
    a.normalizeLength();
    b.normalizeLength();
    return a * b;
}

QPoint Point::toRaster() const {
    QPoint res;
    res.setX((int)v[0] + 0.5);
    res.setY((int)v[1] + 0.5);
    return res;
}

void Point::normalizeLength() {
    double len = length();
    if (len > 0) {
        for (int i: {0, 1, 2}) {
            v[i] /= len;
        }
    }
}

void Point::normalizeW() {
    for (int i: {0, 1, 2, 3}) {
        v[i] /= v[3];
    }
}

Point Point::vectorProduct(const Point & p) const {
    double rx = v[1] * p.v[2] - v[2] * p.v[1];
    double ry = - (v[0] * p.v[2] - v[2] * p.v[0]);
    double rz = v[0] * p.v[1] - v[1] * p.v[0];
    return Point(rx, ry, rz);
}

}} // namespace rt::model

QDebug operator<<(QDebug debug, const rt::model::Point& p) {
    QDebugStateSaver saver(debug);
    debug.nospace() << "Point(" << p.x() << ", " << p.y() << ", " << p.z() << ")";
    return debug;
}
