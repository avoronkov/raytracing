#pragma once

#include "FIT_6203_Voronkov_Ray_Ray.h"

class CFIT_6203_Voronkov_Ray_Eye
{
private:
	Point m_origin;
	Point m_view_border[4];
	/*
	0 - 1
	|   |
	2 - 3
	*/
	CSize m_freq;
public:
	CFIT_6203_Voronkov_Ray_Eye(void);
	~CFIT_6203_Voronkov_Ray_Eye(void);
	CFIT_6203_Voronkov_Ray_Eye & operator=(const CFIT_6203_Voronkov_Ray_Eye &);
	void setOrigin(const Point & origin);
	void setBorder(int i, const Point & point);
	void setBorder(const Point &, const Point &, const Point &, const Point &);
	void setFreq(const CSize &);
	void setFreq(int hor, int vert);

	const Point & origin() const;
	const Point & border(int i) const;
	const CSize & frequency() const;

	Ray getRay(int x, int y) const;
};

typedef CFIT_6203_Voronkov_Ray_Eye Eye;
