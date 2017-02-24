#include "eye.h"

namespace rt { namespace model {

void Eye::setBorder(int i, const Point & point)
{
    Q_ASSERT (i>=0 && i<4);
    _view_border[i] = point;
}

void Eye::setBorder
        (const Point &a, const Point &b, const Point &c, const Point &d)
{
    _view_border[0] = a;
    _view_border[1] = b;
    _view_border[2] = c;
    _view_border[3] = d;
}

void Eye::setFreq(int hor, int vert)
{
    setFreq(QSize(hor, vert));
}

const Point & Eye::border(int i) const
{
    Q_ASSERT (i>=0 && i<4);
    return _view_border[i];
}

Ray Eye::getRay(int h, int v) const
{
    Q_ASSERT (h>=0 && h < _freq.width());
    Q_ASSERT (v>=0 && v < _freq.height());

    Ray res;

    res.setOrigin(_origin);
    // ãîðèçîíòàëüíîå íàïðàâëåíèå
    Point dir_h = (_view_border[1] - _view_border[0]) * ((double)h / (_freq.height() - 1.0));
    Point dir_v = (_view_border[2] - _view_border[0]) * ((double)v / (_freq.width() - 1.0));
    res.setDirectionByPoint(_view_border[0] + dir_h + dir_v);

    return res;
}

}}
