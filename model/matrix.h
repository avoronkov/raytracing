#ifndef MATRIX_H
#define MATRIX_H

#include "model/point.h"
#include "model/segment.h"
#include "model/eye.h"
#include "model/wireframe.h"

namespace rt { namespace model {

class Matrix
{
public:
    double m[4][4];
public:
    Matrix();
    Matrix(const Matrix &);
    ~Matrix() = default;

    void createTranslate(double tx, double ty, double tz);
    void createScale(double sx, double sy, double sz);
    void createRotateX(double radian);
    void createRotateY(double radian);
    void createRotateZ(double radian);
    void createMproj(double Sw, double Sh, double zf, double zb);

    Matrix& operator=(const Matrix & another);
    Matrix operator*(const Matrix & another) const;
    Point operator*(const Point & another) const;
    Segment operator*(const Segment & another) const;
    Matrix& operator*=(const Matrix & another);
    WireFrame operator*(const WireFrame& another) const;
    Eye operator*(const Eye& another) const;

    Matrix transpose() const;

    void setRaw(int row, int col, double value);
    const double & getRaw(int row, int col) const;

private:
    void clear();
};

}}

#endif // MATRIX_H
