#pragma once

#include "FIT_6203_Voronkov_Ray_Segment.h"
#include "FIT_6203_Voronkov_Ray_WireFrame.h"
#include "FIT_6203_Voronkov_Ray_Eye.h"

class CFIT_6203_Voronkov_Ray_Matrix
{
public:
	double m[4][4];
private:
	void clear();
public:
	CFIT_6203_Voronkov_Ray_Matrix();
	~CFIT_6203_Voronkov_Ray_Matrix();

	void createTranslate(double tx, double ty, double tz);
	void createScale(double sx, double sy, double sz);
	void createRotateX(double radian);
	void createRotateY(double radian);
	void createRotateZ(double radian);
	void createMproj(double Sw, double Sh, double zf, double zb);
	
	CFIT_6203_Voronkov_Ray_Matrix& operator=
		(const CFIT_6203_Voronkov_Ray_Matrix & another);
	CFIT_6203_Voronkov_Ray_Matrix operator*
		(const CFIT_6203_Voronkov_Ray_Matrix & another) const;
	Point operator*(const Point & another) const;
	Segment operator*(const Segment & another) const;
	CFIT_6203_Voronkov_Ray_Matrix& operator*=
		(const CFIT_6203_Voronkov_Ray_Matrix & another);
	WireFrame operator*(const WireFrame& another) const;
	Eye operator*(const Eye& another) const; 

	CFIT_6203_Voronkov_Ray_Matrix transpose() const;

	void setRaw(int row, int col, double value);
	const double & getRaw(int row, int col) const;

	CString show() const;
};

typedef CFIT_6203_Voronkov_Ray_Matrix Matrix;