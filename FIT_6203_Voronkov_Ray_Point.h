#pragma once

class CFIT_6203_Voronkov_Ray_Point
{
private:
	double v[4];// x, y, z, w
public:
	CFIT_6203_Voronkov_Ray_Point();
	CFIT_6203_Voronkov_Ray_Point(double x, double y, double z);
	~CFIT_6203_Voronkov_Ray_Point();

	CFIT_6203_Voronkov_Ray_Point & operator=(const CFIT_6203_Voronkov_Ray_Point &);
	CFIT_6203_Voronkov_Ray_Point & operator+=(const CFIT_6203_Voronkov_Ray_Point &);
	CFIT_6203_Voronkov_Ray_Point   operator+(const CFIT_6203_Voronkov_Ray_Point &) const;
	CFIT_6203_Voronkov_Ray_Point   operator-(const CFIT_6203_Voronkov_Ray_Point &) const;

	CFIT_6203_Voronkov_Ray_Point operator*(const double &) const;
	double operator*(const CFIT_6203_Voronkov_Ray_Point &) const;
	CFIT_6203_Voronkov_Ray_Point operator-() const;

	double x() const;
	double y() const;
	double z() const;

	void setX(double value);
	void setY(double value);
	void setZ(double value);

	double get(int idx) const;
	void set(int idx, double value);

	double length() const;
	double cos(CFIT_6203_Voronkov_Ray_Point another)const;

	CPoint toRaster() const;
	void normalizeW();
	void normalizeLength();

	CFIT_6203_Voronkov_Ray_Point vectorProduct(const CFIT_6203_Voronkov_Ray_Point &)const;
};

typedef CFIT_6203_Voronkov_Ray_Point Point;