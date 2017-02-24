#ifndef EYE_H
#define EYE_H

#include "model/ray.h"

#include <QSize>

namespace rt { namespace model {

class Eye
{
    Point _origin;
    Point _view_border[4];
    /*
    0 - 1
    |   |
    2 - 3
    */
    QSize _freq;

public:
    Eye() = default;
    Eye(const Eye&) = default;
    ~Eye() = default;
    Eye & operator=(const Eye &) = default;

    void setOrigin(const Point & origin) { _origin = origin; }
    void setBorder(int i, const Point & point);
    void setBorder(const Point &, const Point &, const Point &, const Point &);
    void setFreq(const QSize & freq) { _freq = freq; }
    void setFreq(int hor, int vert);

    const Point & border(int i) const;
    const Point & origin() const { return _origin; }
    const QSize & frequency() const { return _freq; }

    Ray getRay(int x, int y) const;

};

}}

#endif // EYE_H
