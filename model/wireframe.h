#ifndef WIREFRAME_H
#define WIREFRAME_H

#include "model/segment.h"

#include <QList>

namespace rt { namespace model {

class WireFrame
{
    QList<Segment> _segms;
    double _max_coord[3];
    double _min_coord[3];

public:
    WireFrame();
    WireFrame(const WireFrame & obj) = default;
    virtual ~WireFrame() = default;
    WireFrame& operator=(const WireFrame& obj) = default;

    WireFrame& operator+=(const Segment& seg);
    WireFrame& operator+=(const WireFrame& obj);
    WireFrame operator+(const WireFrame& obj) const;

    // void restartIterator();
    // bool hasNextSegment();
    // Segment nextSegment();

    const QList<Segment> & content() const { return _segms; }

    // outer box
    void setOuterBoxMax(int coord, const double & value);
    void setOuterBoxMin(int coord, const double & value);
    const double & getOuterBoxMax(int coord) const;
    const double & getOuterBoxMin(int coord) const;

    void clear();
    // CString show() const;

    static WireFrame cube(const double &xs, const double &ys, const double &zs,
                          const double &xf, const double &yf, const double &zf);

    static WireFrame orts(const Point & center, double size);
    static WireFrame orts(const Point & center, double xsize, double ysize, double zsize);
    static WireFrame orts(const Point & center, const Point & sizes);

};

}}

#endif // WIREFRAME_H
