#pragma once

#include "FIT_6203_Voronkov_Ray_Segment.h"

class CFIT_6203_Voronkov_Ray_WireFrame
{
protected:
	CList<Segment> segms; // состовл€ющие
	POSITION pos;

	double m_max_coord[3];
	double m_min_coord[3];
public:
	CFIT_6203_Voronkov_Ray_WireFrame();
	CFIT_6203_Voronkov_Ray_WireFrame(const CFIT_6203_Voronkov_Ray_WireFrame & obj);
	~CFIT_6203_Voronkov_Ray_WireFrame();

	CFIT_6203_Voronkov_Ray_WireFrame& operator=(const CFIT_6203_Voronkov_Ray_WireFrame& obj);
	CFIT_6203_Voronkov_Ray_WireFrame& operator+=(const Segment& seg);
	CFIT_6203_Voronkov_Ray_WireFrame& operator+=(const CFIT_6203_Voronkov_Ray_WireFrame& obj);
	CFIT_6203_Voronkov_Ray_WireFrame operator+(const CFIT_6203_Voronkov_Ray_WireFrame& obj);

	void restartIterator();
	boolean hasNextSegment();
	Segment nextSegment();

	const CList<Segment> & content() const;

	// outer box
	void setOuterBoxMax(int coord, const double & value);
	void setOuterBoxMin(int coord, const double & value);
	const double & getOuterBoxMax(int coord) const;
	const double & getOuterBoxMin(int coord) const;

	void clear();
	CString show() const;

	static CFIT_6203_Voronkov_Ray_WireFrame cube
		(double xs, double ys, double zs, double xf, double yf, double zf);

	static CFIT_6203_Voronkov_Ray_WireFrame orts
		(const Point & center, double size);
	static CFIT_6203_Voronkov_Ray_WireFrame orts
		(const Point & center, double xsize, double ysize, double zsize);
	static CFIT_6203_Voronkov_Ray_WireFrame orts
	(const Point & center, const Point & sizes);
};

typedef CFIT_6203_Voronkov_Ray_WireFrame WireFrame;