#pragma once

#include "FIT_6203_Voronkov_Ray_Point.h"
#include "FIT_6203_Voronkov_Ray_Primitive.h"

class CFIT_6203_Voronkov_Ray_Sphere : public Primitive
{
private:
	Point m_center;
	double m_radius;

private:
	Point spherePoint(double s, double t)const;
public:
	CFIT_6203_Voronkov_Ray_Sphere();
	CFIT_6203_Voronkov_Ray_Sphere(const Point& center, const double& radius);
	~CFIT_6203_Voronkov_Ray_Sphere();

	const double & getRadius() const;
	const Point & getCenter() const;

	void setRadius(const double & value);
	void setCenter(const Point & center);
	void setCenter(const double& x, const double& y, const double& z);

	CFIT_6203_Voronkov_Ray_Sphere & operator=(const CFIT_6203_Voronkov_Ray_Sphere & obj);

	CString toString() const;
	bool isCorrect() const;

	enum PrimitiveType getType() const {return SPH;}
	WireFrame getWireFrame() const;
	double getMax(int coord) const;
	double getMin(int coord) const;

	virtual bool calculateIntersection();
	virtual bool calculateNormal();
};

typedef CFIT_6203_Voronkov_Ray_Sphere Sphere;