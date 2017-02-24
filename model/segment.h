#ifndef SEGMENT_H
#define SEGMENT_H

#include "model/point.h"

#include <QColor>

namespace rt { namespace model {

class Segment
{
    Point _start;
    Point _finish;
    int _width;
    QColor _color;
public:
    Segment();
      Segment
        (const Segment & another);
    Segment(const Point & s, const Point & f);
    Segment(double sx, double sy, double sz, double fx, double fy, double fz);
    Segment(double sx, double sy, double sz, double fx, double fy, double fz, const QColor &color);
    ~Segment();

    Segment& operator=(const Segment & obj);
    Segment& operator+=(const Segment & obj);
    Segment operator+(const Point & point);
    const Point & start() const { return _start; }
    const Point & finish() const { return _finish; }

    void setStart(const Point & s) { _start = s; }
    void setFinish(const Point & f) { _finish = f; }

    const QColor& color() const { return _color; }
    void setColor(const QColor & color) { _color = color; }
    void setColor(int r, int g, int b) { _color = QColor(r, g, b); }

    int width() const { return _width; }
    void setWidth(int w) { _width = w; }

    // CString show() const;
    void normalizeW();

};

}}

#endif // SEGMENT_H
