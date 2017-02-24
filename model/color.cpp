#include "color.h"

namespace rt { namespace model {

Color::Color(): Color{0, 0, 0}
{

}

Color::Color(const double & r, const double & g, const double & b):
    _r{r}, _g{g}, _b{b}, _background{false}
{}

Color Color::operator*(const Color& obj)const
{
    Color res;

    res._r = _r * obj._r;
    res._g = _g * obj._g;
    res._b = _b * obj._b;
    res._background = false;
    return res;
}

Color Color::operator+(const Color& obj)const
{
    Color res;

    res._r = _r + obj._r;
    res._g = _g + obj._g;
    res._b = _b + obj._b;
    res._background = (_background & obj._background);
    return res;
}

Color Color::operator*(const double& factor)const
{
    Color res;
    res._r = _r * factor;
    res._g = _g * factor;
    res._b = _b * factor;
    res._background = false;
    return res;
}

Color Color::operator/(const double& factor)const
{
    Color res;
    res._r = _r / factor;
    res._g = _g / factor;
    res._b = _b / factor;
    res._background = false;
    return res;
}

Color& Color::operator/=(const double& value)
{
    _r /= value;
    _g /= value;
    _b /= value;
    _background = false;
    return * this;
}

Color& Color::operator+=(const Color& obj)
{
    _r += obj._r;
    _g += obj._g;
    _b += obj._b;
    _background &= obj._background;
    return * this;
}

void Color::set(const double & r, const double & g, const double & b)
{
    _r = r;
    _g = g;
    _b = b;
    _background = false;
}


}}
