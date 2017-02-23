#pragma once

#include "FIT_6203_Voronkov_Ray_Color.h"
#include "FIT_6203_Voronkov_Ray_Point.h"

class CFIT_6203_Voronkov_Ray_Light
{
private:
	Point m_pos;
	Color m_color;
public:
	CFIT_6203_Voronkov_Ray_Light();
	CFIT_6203_Voronkov_Ray_Light(const Point & pos, const Color & color);
	CFIT_6203_Voronkov_Ray_Light(const double & px, const double & py, const double & pz, 
								const double & r, const double & g, const double & b);
	~CFIT_6203_Voronkov_Ray_Light();

	CFIT_6203_Voronkov_Ray_Light & operator=(const CFIT_6203_Voronkov_Ray_Light & obj);

	const Point & position() const {return m_pos;}
	const Color & color() const {return m_color;}
	void setPosition(const Point & pos){m_pos = pos;}
	void setColor(const Color & color){m_color = color;}
};

typedef CFIT_6203_Voronkov_Ray_Light Light;