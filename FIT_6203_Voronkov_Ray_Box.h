#pragma once

#include "FIT_6203_Voronkov_Ray_Point.h"
#include "FIT_6203_Voronkov_Ray_Primitive.h"

class CFIT_6203_Voronkov_Ray_Box : public Primitive
{
private:
	double m_x_low;
	double m_x_high;
	double m_y_low;
	double m_y_high;
	double m_z_low;
	double m_z_high;
public:
	CFIT_6203_Voronkov_Ray_Box();
	CFIT_6203_Voronkov_Ray_Box(const double & x_low, const double & y_low, const double & z_low,
								const double &x_high, const double &y_high, const double &z_high);
	CFIT_6203_Voronkov_Ray_Box(const CFIT_6203_Voronkov_Ray_Box &);
	~CFIT_6203_Voronkov_Ray_Box();

	const double & getXMax() const;
	const double & getXMin() const;
	const double & getYMax() const;
	const double & getYMin() const;
	const double & getZMax() const;
	const double & getZMin() const;

	Point getVertex(int num) const; // from 0 to 7

	Point getMin() const;
	Point getMax() const;

	void setMax(const double & x, const double & y, const double & z);
	void setMin(const double & x, const double & y, const double & z);

	CFIT_6203_Voronkov_Ray_Box & operator=(const CFIT_6203_Voronkov_Ray_Box &);

	CString toString() const;
	bool isCorrect() const;

	enum PrimitiveType getType() const{return BOX;}
	WireFrame getWireFrame() const;
	double getMax(int coord) const;
	double getMin(int coord) const;

	bool isInside(const Point & point)const;

	virtual bool calculateIntersection();
	virtual bool calculateNormal();
};

typedef CFIT_6203_Voronkov_Ray_Box Box;