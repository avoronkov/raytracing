#ifndef COLOR_H
#define COLOR_H

namespace rt { namespace model {

class Color
{
    double _r;
    double _g;
    double _b;
    bool _background;
public:
    Color();
    Color(const double & _r, const double & _g, const double & _b);
    virtual ~Color() = default;

    Color & operator=(const Color & obj) = default;

    const double & r() const {return _r;}
    const double & g() const {return _g;}
    const double & b() const {return _b;}
    void setR(const double & r){_r = r;}
    void setG(const double & g){_g = g;}
    void setB(const double & b){_b = b;}
    void set(const double & _r, const double & _g, const double & _b);

    Color operator*(const Color&)const;
    Color operator*(const double&)const;
    Color operator/(const double&)const;
    Color& operator/=(const double&);
    Color operator+(const Color&)const;
    Color& operator+=(const Color&);

    void setBackground(bool value){ _background = value;}
    bool isBackground()const{return _background;}
};

}}

#endif // COLOR_H
