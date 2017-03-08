#include "segment.h"

namespace rt { namespace model {

Segment::Segment():
    _width{1},
    _color{0, 0, 0}
{

}
Segment::Segment
    (const Segment & another)
{
    this->_width = another._width;
    this->_start = another._start;
    this->_finish = another._finish;
    this->_color = another._color;
//	this->_color = QColor(0, 0, 0);
}
Segment::Segment
    (const Point & s, const Point & f)
{
    this->_width = 1;
    this->_color = QColor(0, 0, 0);
    this->_start = s;
    this->_finish = f;
}
Segment::Segment
    (double sx, double sy, double sz, double fx, double fy, double fz)
{
    this->_width = 1;
    this->_color = QColor(0, 0, 0);
    this->_start = Point(sx, sy, sz);
    this->_finish   = Point(fx, fy, fz);
}
Segment::Segment
    (double sx, double sy, double sz, double fx, double fy, double fz, const QColor &color)
{
    this->_width = 1;
    this->_color = color;
    this->_start = Point(sx, sy, sz);
    this->_finish   = Point(fx, fy, fz);
}
Segment::~Segment()
{

}

Segment& Segment::operator=(const Segment & obj)
{
    this->_width = obj._width;
    this->_start = obj._start;
    this->_finish = obj._finish;
    this->_color = obj._color;
    return *this;
}
Segment& Segment::operator+=(const Segment & obj)
{
    this->_start += obj._start;
    this->_finish += obj._finish;
    return *this;
}
Segment Segment::operator+(const Point & point)
{
    Segment res;
    res._start = this->_start + point;
    res._finish = this->_finish + point;
    return res;
}
/*
CString Segment::show() const
{
    CString str;
    str.AppendFormat("(%.2lf, %.2lf, %.2lf  :", _start.x(), _start.y(), _start.z());
    str.AppendFormat("  %.2lf, %.2lf, %.2lf)", _finish.x(), _finish.y(), _finish.z());
    return str;
}
*/

void Segment::normalizeW()
{
    this->_start.normalizeW();
    this->_finish.normalizeW();
}

}} // namespace rt::model

QDebug operator<<(QDebug debug, const rt::model::Segment& seg) {
    QDebugStateSaver saver(debug);
    const rt::model::Point & s = seg.start();
    const rt::model::Point & f = seg.finish();
    debug.nospace() << "Segment((" << s.x() << ", " << s.y() << ", " << s.z() << "), ("
                    << f.x() << ", " << f.y() << ", " << f.z() << "))";
    return debug;
}
