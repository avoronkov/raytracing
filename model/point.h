#ifndef POINT_H
#define POINT_H

#include <QPoint>
#include <QDebug>

namespace rt { namespace model {

class Point
{
private:
    double v[4]; // x, y, z, w
public:
    Point();
    Point(double x, double y, double z);
    Point(const Point &);
    ~Point();

    Point & operator=(const Point &);
    Point & operator+=(const Point &);
    Point   operator+(const Point &) const;
    Point   operator-(const Point &) const;

    Point operator*(const double &) const;
    double operator*(const Point &) const;
    Point operator-() const;

    double x() const { return v[0]; }
    double y() const { return v[1]; }
    double z() const { return v[2]; }

    void setX(double value) { v[0] = value; }
    void setY(double value) { v[1] = value; }
    void setZ(double value) { v[2] = value; }

    double get(int idx) const;
    void set(int idx, double value);

    double length() const;
    double cos(const Point &)const;

    QPoint toRaster() const;
    void normalizeW();
    void normalizeLength();

    Point vectorProduct(const Point &)const;
};


}}

QDebug operator<<(QDebug, const rt::model::Point&);

#endif // POINT_H
