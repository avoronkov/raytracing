#include "light.h"

namespace rt { namespace model {

Light::Light(const Point &pos,const Color &color):
    _pos{pos},
    _color{color}
{
}

Light::Light(const double & px, const double & py, const double & pz,
             const double & r, const double & g, const double & b):
    Light{Point{px, py, pz}, Color{r, g, b}}
{
}

}}
