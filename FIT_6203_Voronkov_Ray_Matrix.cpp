#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_Matrix.h"


CFIT_6203_Voronkov_Ray_Matrix::CFIT_6203_Voronkov_Ray_Matrix()
{
	clear();	
}
CFIT_6203_Voronkov_Ray_Matrix::~CFIT_6203_Voronkov_Ray_Matrix()
{
}

void CFIT_6203_Voronkov_Ray_Matrix::createTranslate(double tx, double ty, double tz)
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
void CFIT_6203_Voronkov_Ray_Matrix::createScale(double sx, double sy, double sz)
{
	clear();
	m[0][0] = sx;
	m[1][1] = sy;
	m[2][2] = sz;
	m[3][3] = 1.0;

}
void CFIT_6203_Voronkov_Ray_Matrix::createRotateX(double radian)
{
	clear();
	double sin_fi = sin(radian);
	double cos_fi = cos(radian);

	m[0][0] = 1.0;
	m[1][1] = cos_fi;
	m[1][2] = -sin_fi;
	m[2][1] = sin_fi;
	m[2][2] = cos_fi;
	m[3][3] = 1.0;
	ASSERT (m[0][0] <= 1);
}
void CFIT_6203_Voronkov_Ray_Matrix::createRotateY(double radian)
{
	clear();
	double sin_fi = sin(radian);
	double cos_fi = cos(radian);
	m[0][0] = cos_fi;
	m[0][2] = sin_fi;
	m[1][1] = 1.0;
	m[2][0] = -sin_fi;
	m[2][2] = cos_fi;
	m[3][3] = 1.0;
}
void CFIT_6203_Voronkov_Ray_Matrix::createRotateZ(double radian)
{
	clear();
	double sin_fi = sinh(radian);
	double cos_fi = cosh(radian);
	m[0][0] = cos_fi;
	m[0][1] = -sin_fi;
	m[1][0] = sin_fi;
	m[1][1] = cos_fi;
	m[2][2] = 1.0;
	m[3][3] = 1.0;
}
void CFIT_6203_Voronkov_Ray_Matrix::createMproj(double Sw, double Sh, double zf, double zb)
{
	clear();
	m[0][0] = 2.0 * zf / Sw;
	m[1][1] = 2.0 * zf / Sh;
	m[2][2] = zb / (zb - zf);
	m[2][3] = - zf * zb / (zb - zf);
	m[3][2] = 1.0;
}

CFIT_6203_Voronkov_Ray_Matrix& CFIT_6203_Voronkov_Ray_Matrix::operator=
	(const CFIT_6203_Voronkov_Ray_Matrix & another)
{
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			m[i][j] = another.m[i][j];
		}
	}
	return *this;
}
CFIT_6203_Voronkov_Ray_Matrix CFIT_6203_Voronkov_Ray_Matrix::operator*
	(const CFIT_6203_Voronkov_Ray_Matrix & another) const
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
Point CFIT_6203_Voronkov_Ray_Matrix::operator*(const Point & another) const
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
Segment CFIT_6203_Voronkov_Ray_Matrix::operator*
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
CFIT_6203_Voronkov_Ray_Matrix& CFIT_6203_Voronkov_Ray_Matrix::operator*=
	(const CFIT_6203_Voronkov_Ray_Matrix & another)
{
	Matrix mtx = (*this) * another;
	return *this = mtx;
}
WireFrame CFIT_6203_Voronkov_Ray_Matrix::operator*
	(const WireFrame & another) const
{
	WireFrame res;
	Segment seg;
	
	const CList<Segment> & list = another.content();
	POSITION pos = list.GetHeadPosition();
	while (pos)
	{
		seg = list.GetNext(pos);
		seg = (*this) * seg;
		res += seg;
	}
	return res;
}
Eye CFIT_6203_Voronkov_Ray_Matrix::operator*(const Eye& another) const
{
	Eye res;
	
	res.setFreq(another.frequency());

	res.setOrigin((*this) * another.origin());

	for (int i=0; i<4; i++){
		res.setBorder(i, (*this) * another.border(i));
	}

	return res;
}

CFIT_6203_Voronkov_Ray_Matrix CFIT_6203_Voronkov_Ray_Matrix::transpose() const
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

void CFIT_6203_Voronkov_Ray_Matrix::clear()
{
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			m[i][j] = 0.0;
		}
	}
}
CString CFIT_6203_Voronkov_Ray_Matrix::show() const
{
	CString str;
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			str.AppendFormat("%.2lf ", m[i][j]);
		}
		str.AppendFormat("\n");
	}
	return str;
}
void CFIT_6203_Voronkov_Ray_Matrix::setRaw(int row, int col, double value)
{
	ASSERT(col >=0 && col <= 3);
	ASSERT(row >=0 && row <= 3);
	m[row][col] = value;
}
const double & CFIT_6203_Voronkov_Ray_Matrix::getRaw(int row, int col) const
{
	ASSERT(col >=0 && col <= 3);
	ASSERT(row >=0 && row <= 3);
	return m[row][col];
}