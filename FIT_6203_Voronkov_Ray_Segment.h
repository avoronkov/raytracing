#pragma once

#include "FIT_6203_Voronkov_Ray_Point.h"

class CFIT_6203_Voronkov_Ray_Segment
{
private:
	Point begin;
	Point end;
	COLORREF m_color;
	int m_width;
public:
	CFIT_6203_Voronkov_Ray_Segment();
	CFIT_6203_Voronkov_Ray_Segment
		(const CFIT_6203_Voronkov_Ray_Segment & another);
	CFIT_6203_Voronkov_Ray_Segment(const Point & s, const Point & f);
	CFIT_6203_Voronkov_Ray_Segment
		(double sx, double sy, double sz, double fx, double fy, double fz);
	CFIT_6203_Voronkov_Ray_Segment
		(double sx, double sy, double sz, double fx, double fy, double fz, COLORREF color);
	~CFIT_6203_Voronkov_Ray_Segment();

	CFIT_6203_Voronkov_Ray_Segment& operator=
		(const CFIT_6203_Voronkov_Ray_Segment & obj);
	CFIT_6203_Voronkov_Ray_Segment& operator+=
		(const CFIT_6203_Voronkov_Ray_Segment & obj);
	CFIT_6203_Voronkov_Ray_Segment operator+
		(const Point & point);
	const Point & start() const;
	const Point & finish() const;

	void setStart(const Point & s);
	void setFinish(const Point & f);

	COLORREF color() const;
	void setColor(COLORREF color);
	void setColor(int r, int g, int b);
	
	int width() const;
	void setWidth(int w);

	CString show() const;
	void normalizeW();
};

typedef CFIT_6203_Voronkov_Ray_Segment Segment; 