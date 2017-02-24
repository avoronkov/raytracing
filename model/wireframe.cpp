#include "wireframe.h"

namespace rt { namespace model {

WireFrame::WireFrame()
{
    for(int i: {0, 1, 2}) {
        _min_coord[i] = -1;
        _max_coord[i] = 1;
    }
}

WireFrame& WireFrame::operator+=(const Segment & s) {
    _segms.append(s);
    return *this;
}

WireFrame& WireFrame::operator+=(const WireFrame & w) {
    _segms.append(w._segms);
    return *this;
}

WireFrame WireFrame::operator+(const WireFrame & w) const {
    WireFrame res{*this};
    res += w;
    return res;
}

void WireFrame::setOuterBoxMax(int coord, const double & value)
{
    Q_ASSERT (coord == 0 || coord == 1 || coord == 2);
    _max_coord[coord] = value;
}
void WireFrame::setOuterBoxMin(int coord, const double & value)
{
    Q_ASSERT (coord == 0 || coord == 1 || coord == 2);
    _min_coord[coord] = value;
}
const double & WireFrame::getOuterBoxMax(int coord) const
{
    Q_ASSERT (_max_coord[0] >= _min_coord[0]);
    Q_ASSERT (_max_coord[1] >= _min_coord[1]);
    Q_ASSERT (_max_coord[2] >= _min_coord[2]);
    Q_ASSERT (coord == 0 || coord == 1 || coord == 2);
    return _max_coord[coord];
}
const double & WireFrame::getOuterBoxMin(int coord) const
{
    Q_ASSERT (_max_coord[0] >= _min_coord[0]);
    Q_ASSERT (_max_coord[1] >= _min_coord[1]);
    Q_ASSERT (_max_coord[2] >= _min_coord[2]);
    Q_ASSERT (coord == 0 || coord == 1 || coord == 2);
    return _min_coord[coord];
}

void WireFrame::clear() {
    _segms.clear();
}

WireFrame WireFrame::cube
    (const double &xss, const double &yss, const double &zss,
     const double &xff, const double &yff, const double &zff)
{
    WireFrame res;
    // Segment seg;
    QColor color{8, 8, 128};
    double xs, ys, zs;
    double xf, yf, zf;
    xs = xss;
    xf = xff;

    ys = yss;
    yf = yss;
    zs = zss;
    zf = zss;
    res += Segment(xs, ys, zs, xf, yf, zf, color);
    ys = yff;
    yf = yff;
    res += Segment(xs, ys, zs, xf, yf, zf, color);
    zs = zff;
    zf = zff;
    res += Segment(xs, ys, zs, xf, yf, zf, color);
    ys = yss;
    yf = yss;
    res += Segment(xs, ys, zs, xf, yf, zf, color);

    ys = yss;
    yf = yff;

    xs = xss;
    xf = xss;
    zs = zss;
    zf = zss;
    res += Segment(xs, ys, zs, xf, yf, zf, color);
    xs = xff;
    xf = xff;
    res += Segment(xs, ys, zs, xf, yf, zf, color);
    zs = zff;
    zf = zff;
    res += Segment(xs, ys, zs, xf, yf, zf, color);
    xs = xss;
    xf = xss;
    res += Segment(xs, ys, zs, xf, yf, zf, color);

    zs = zss;
    zf = zff;

    xs = xss;
    xf = xss;
    ys = yss;
    yf = yss;
    res += Segment(xs, ys, zs, xf, yf, zf, color);
    xs = xff;
    xf = xff;
    res += Segment(xs, ys, zs, xf, yf, zf, color);
    ys = yff;
    yf = yff;
    res += Segment(xs, ys, zs, xf, yf, zf, color);
    xs = xss;
    xf = xss;
    res += Segment(xs, ys, zs, xf, yf, zf, color);
    return res;

}

WireFrame WireFrame::
        orts(const Point & center, double size)
{
    WireFrame res;
    Segment seg;
    seg.setColor(255, 0, 0);
    seg.setStart(center);
    seg.setFinish(center + Point(size, 0, 0));
    res += seg;

    seg.setColor(0, 255, 0);
    seg.setStart(center);
    seg.setFinish(center + Point(0, size, 0));
    res += seg;

    seg.setColor(0, 0, 255);
    seg.setStart(center);
    seg.setFinish(center + Point(0, 0, size));
    res += seg;
    return res;
}

WireFrame WireFrame::orts
    (const Point & center, const Point & sizes)
{
    return orts(center, sizes.x(), sizes.y(), sizes.z());
}

WireFrame WireFrame::orts
    (const Point & center, double xsize, double ysize, double zsize)
{
    WireFrame res;
    Segment seg;
    seg.setWidth(3);
    seg.setColor(255, 0, 0);

    seg.setStart(center);
    seg.setFinish(center + Point(xsize, 0, 0));
    res += seg;

    seg.setColor(0, 255, 0);
    seg.setStart(center);
    seg.setFinish(center + Point(0, ysize, 0));
    res += seg;

    seg.setColor(0, 0, 255);
    seg.setStart(center);
    seg.setFinish(center + Point(0, 0, zsize));
    res += seg;
    return res;
}

}}
