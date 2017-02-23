#pragma once

#include "FIT_6203_Voronkov_Ray_Point.h"

class CFIT_6203_Voronkov_Ray_Ray
{
private:
	Point m_origin;
	Point m_direction;
public:
	CFIT_6203_Voronkov_Ray_Ray();
	CFIT_6203_Voronkov_Ray_Ray(const Point & origin, const Point & direction);
	CFIT_6203_Voronkov_Ray_Ray(const double& _x, const double& _y, const double& _z,
								const double& dx, const double& dy, const double& dz);
	CFIT_6203_Voronkov_Ray_Ray(const CFIT_6203_Voronkov_Ray_Ray & obj);
	~CFIT_6203_Voronkov_Ray_Ray();

	const Point & getOrigin() const;
	const Point & getDirection() const;

	void setOrigin(const Point & origin);
	void setDirection(const Point & direction);
	void setDirectionByPoint(const Point & direction);

	CFIT_6203_Voronkov_Ray_Ray & operator=(const CFIT_6203_Voronkov_Ray_Ray & obj);
	CFIT_6203_Voronkov_Ray_Ray operator-() const;

	bool isCorrect() const;
	CString toString() const;
};

typedef CFIT_6203_Voronkov_Ray_Ray Ray;
