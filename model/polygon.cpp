#include "polygon.h"

#include "model/common.h"
#include "model/wireframe.h"

namespace rt { namespace model {

Polygon::Polygon(): m_A{0}, m_B{0}, m_C{0}, m_D{0}, is_correct{false}
{

}

void Polygon::addPoint(const Point & point)
{
    m_vertexes.append(point);
}

int Polygon::count() const {
    return m_vertexes.count();
}

bool Polygon::checkPolygon()
{
    // TODO checking polygon
    int count = m_vertexes.count();
    if (count <= 2) {
        return is_correct = false;
    }
    is_correct = true;
    Point first_side = m_vertexes[1] - m_vertexes[0];
    Point second_side = m_vertexes[2] - m_vertexes[1];
    Point normal = first_side.vectorProduct(second_side);
    normal.normalizeLength();
    m_A = normal.x();
    m_B = normal.y();
    m_C = normal.z();

    m_D = - (m_A * m_vertexes[0].x() + m_B * m_vertexes[0].y() + m_C * m_vertexes[0].z());
    for (int i=0; i<m_vertexes.count(); i++){
        Point p = m_vertexes[i];
        double res = m_A * p.x() + m_B * p.y() + m_C * p.z() + m_D;
        if (res > EPS || res < -EPS){
            is_correct = false;
            return false;
        }
    }
    return true;
}

bool Polygon::isInside(const Point & point) const
{
    // get maximum component
    int c_one;
    int c_two;
    double mod_a = (m_A >= 0)? m_A : -m_A;
    double mod_b = (m_B >= 0)? m_B : -m_B;
    double mod_c = (m_C >= 0)? m_C : -m_C;
    if (mod_a > mod_b){
        if (mod_a > mod_c){	// A is the greatest
            c_one = 1;
            c_two = 2;
        }
        else{// C is the greatest
            c_one = 0;
            c_two = 1;
        }
    }
    else{
        if (mod_b > mod_c){ // B is the greatest
            c_one = 0;
            c_two = 2;
        }
        else{ // C is the greatest
            c_one = 0;
            c_two = 1;
        }
    }
    double first_sign = 0;
    double sign;
    Point current;
    Point next;
    Point side;
    Point star;
    bool sign_set = false;
    for (int i=0; i< m_vertexes.count(); i++)
    {
        current = m_vertexes[i];
        next = m_vertexes[(i+1)%m_vertexes.count()];
        side = next - current;
        star = point - current;
        sign = side.get(c_one) * star.get(c_two) - side.get(c_two) * star.get(c_one);
        if (!sign_set){
            if (sign != 0){
                first_sign = sign;
                sign_set = true;
            }
        }
        else{
            if (sign * first_sign < 0) return false;
        }
    }
    return true;
}
/*
CString Polygon::toString() const
{
    CString res;
    res.Format("[Polygon(%d):\n", m_vertexes.GetCount());
    for (int i=0; i<m_vertexes.GetCount(); i++)
    {
        Point cur_point = m_vertexes.GetAt(i);
        res.AppendFormat("\t(%.5lf, %.5lf, %.5lf),\n",
            cur_point.x(), cur_point.y(), cur_point.z());

    }
    res.AppendFormat("]\n");
    return res;
}
*/
bool Polygon::isCorrect() const
{
    return is_correct;
}
WireFrame Polygon::getWireFrame() const
{
    WireFrame res;
    int size = m_vertexes.count();
    for (int i=0; i<size; i++){
        res += Segment(m_vertexes[i], m_vertexes[(i+1)%size]);
    }
    return res;
}
double Polygon::getMax(int coord) const
{
    Q_ASSERT (m_vertexes.count() > 0);
    if (coord == 0 || coord == 1 || coord == 2){
        double val = m_vertexes[0].get(coord);
        double current;
        for (int i=1; i<m_vertexes.count(); i++){
            if ((current = m_vertexes[i].get(coord)) > val){
                val = current;
            }
        }
        return val;
    }
    Q_ASSERT (0);
    return 0;
}
double Polygon::getMin(int coord) const
{
    Q_ASSERT (m_vertexes.count() > 0);
    if (coord == 0 || coord == 1 || coord == 2){
        double val = m_vertexes[0].get(coord);
        double current;
        for (int i=1; i<m_vertexes.count(); i++){
            if ((current = m_vertexes[i].get(coord)) < val){
                val = current;
            }
        }
        return val;
    }
    Q_ASSERT (0);
    return 0;
}
bool Polygon::calculateIntersection()
{
    checkPolygon();
    Point normal = Point(m_A, m_B, m_C);
    double D = m_D;
    Point ray_dir = _ray.getDirection();
    Point ray_ori = _ray.getOrigin();

    double vd = normal * ray_dir;
    if (vd == 0) {
        has_intersection = false;
        return false;
    }
    double vo = - (normal * ray_ori) - D;
    double t = vo / vd;
    if (t <= 0) {
        has_intersection = false;
        return false;
    }
    Point i = ray_ori + ray_dir * t;

    bool inside = isInside(i);
    if (!inside){
        has_intersection = false;
        return false;
    }
    ray_from_outside = true;
    if (vd > 0){
        ray_from_outside = false;
    }
    _t = t;
    has_intersection = true;
    _intersection = i;
    return true;
}
bool Polygon::calculateNormal()
{
    if (!this->has_intersection) return false;

    _normal = Point(m_A, m_B, m_C);
    if (_normal.cos(_ray.getDirection()) > 0) _normal = - _normal;

    return true;
}
}}
