#include "matrix.h"

#include <QtMath>

namespace rt {namespace model {

Matrix::Matrix()
{
    clear();
}

void Matrix::createTranslate(double tx, double ty, double tz)
{
    clear();
    m[0][0] = 1.0;
    m[1][1] = 1.0;
    m[2][2] = 1.0;
    m[3][3] = 1.0;

    m[0][3] = tx;
    m[1][3] = ty;
    m[2][3] = tz;
}
void Matrix::createScale(double sx, double sy, double sz)
{
    clear();
    m[0][0] = sx;
    m[1][1] = sy;
    m[2][2] = sz;
    m[3][3] = 1.0;

}
void Matrix::createRotateX(double radian)
{
    clear();
    double sin_fi = qSin(radian);
    double cos_fi = qCos(radian);

    m[0][0] = 1.0;
    m[1][1] = cos_fi;
    m[1][2] = -sin_fi;
    m[2][1] = sin_fi;
    m[2][2] = cos_fi;
    m[3][3] = 1.0;
    Q_ASSERT (m[0][0] <= 1);
}
void Matrix::createRotateY(double radian)
{
    clear();
    double sin_fi = qSin(radian);
    double cos_fi = qCos(radian);
    m[0][0] = cos_fi;
    m[0][2] = sin_fi;
    m[1][1] = 1.0;
    m[2][0] = -sin_fi;
    m[2][2] = cos_fi;
    m[3][3] = 1.0;
}
void Matrix::createRotateZ(double radian)
{
    clear();
    double sin_fi = sinh(radian); // FIXME ???
    double cos_fi = cosh(radian);
    m[0][0] = cos_fi;
    m[0][1] = -sin_fi;
    m[1][0] = sin_fi;
    m[1][1] = cos_fi;
    m[2][2] = 1.0;
    m[3][3] = 1.0;
}
void Matrix::createMproj(double Sw, double Sh, double zf, double zb)
{
    clear();
    m[0][0] = 2.0 * zf / Sw;
    m[1][1] = 2.0 * zf / Sh;
    m[2][2] = zb / (zb - zf);
    m[2][3] = - zf * zb / (zb - zf);
    m[3][2] = 1.0;
}

void Matrix::createIdentity()
{
    clear();
    for (int i: {0, 1, 2, 3}) {
        m[i][i] = 1.0;
    }
}

Matrix Matrix::identity() {
    Matrix m;
    m.createIdentity();
    return m;
}

Matrix Matrix::rotateX(double radian)
{
    Matrix r;
    r.createRotateX(radian);
    return r;
}

Matrix Matrix::rotateY(double radian)
{
    Matrix r;
    r.createRotateY(radian);
    return r;
}

Matrix Matrix::operator*(const Matrix & another) const
{
    Matrix mtx;
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            for (int k=0; k<4; k++)
            {
                mtx.m[i][j] += m[i][k] * another.m[k][j];
            }
        }
    }
    return mtx;
}
Point Matrix::operator*(const Point & another) const
{
    Point point;
    double res;
    for (int i=0; i<4; i++){
        res = 0.0;
        for (int j=0; j<4; j++){
            res += m[i][j] * another.get(j);
        }
        point.set(i, res);
    }
    return point;
}
Segment Matrix::operator*
        (const Segment & another) const
{
    Segment res;
    res.setStart((*this) * another.start());
    res.setFinish((*this) * another.finish());

    res.setColor(another.color());
    int w = another.width();
    res.setWidth(w);

    return res;
}
Matrix& Matrix::operator*=
    (const Matrix & another)
{
    Matrix mtx = (*this) * another;
    return *this = mtx;
}
WireFrame Matrix::operator*
    (const WireFrame & another) const
{
    WireFrame res;

    const QList<Segment> & list = another.content();
    for (Segment seg : list)
    {
        seg = (*this) * seg;
        res += seg;
    }
    return res;
}
Eye Matrix::operator*(const Eye& another) const
{
    Eye res;

    res.setFreq(another.frequency());

    res.setOrigin((*this) * another.origin());

    for (int i=0; i<4; i++){
        res.setBorder(i, (*this) * another.border(i));
    }

    return res;
}

Matrix Matrix::transpose() const
{
    Matrix mtrx;
    mtrx.clear();
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++){
            mtrx.setRaw(j, i, this->getRaw(i, j));
        }
    }
    return mtrx;
}

void Matrix::setRaw(int row, int col, double value)
{
    Q_ASSERT(col >=0 && col <= 3);
    Q_ASSERT(row >=0 && row <= 3);
    m[row][col] = value;
}
const double & Matrix::getRaw(int row, int col) const
{
    Q_ASSERT(col >=0 && col <= 3);
    Q_ASSERT(row >=0 && row <= 3);
    return m[row][col];
}

void Matrix::clear()
{
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            m[i][j] = 0.0;
        }
    }
}

}}

QDebug operator<<(QDebug out, const rt::model::Matrix & m) {
    for (int i: {0, 1, 2, 3}) {
        for (int j: {0, 1, 2, 3}) {
            out << m.getRaw(i, j);
        }
        out << "\n";
    }
    return out;
}
