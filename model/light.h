#ifndef LIGHT_H
#define LIGHT_H

#include "model/color.h"
#include "model/point.h"

namespace rt { namespace model {

class Light
{
    Point _pos;
    Color _color;
public:
    Light() = default;
    Light(const Point &pos,const Color &color);
    Light(const double & px, const double & py, const double & pz,
                                const double & r, const double & g, const double & b);
    Light(const Light &) = default;
    virtual ~Light() = default;

    Light & operator=(const Light & obj) = default;

    const Point & position() const {return _pos;}
    const Color & color() const {return _color;}
    void setPosition(const Point & pos){_pos = pos;}
    void setColor(const Color & color){_color = color;}
};

}}

#endif // LIGHT_H
