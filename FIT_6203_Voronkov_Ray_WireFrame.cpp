#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_WireFrame.h"

CFIT_6203_Voronkov_Ray_WireFrame::CFIT_6203_Voronkov_Ray_WireFrame()
{
	pos = NULL;
	for (int i=0; i<3; i++){
		m_max_coord[i] = -1;
		m_min_coord[i] = 1;
	}
}
CFIT_6203_Voronkov_Ray_WireFrame::CFIT_6203_Voronkov_Ray_WireFrame
		(const CFIT_6203_Voronkov_Ray_WireFrame & obj)
{
	pos = NULL;
	POSITION p = obj.segms.GetHeadPosition();
	while(p)
	{
		segms.AddTail(obj.segms.GetNext(p));
	}
	for (int i=0; i<3; i++){
		m_max_coord[i] = obj.m_max_coord[i];
		m_min_coord[i] = obj.m_min_coord[i];
	}
}
CFIT_6203_Voronkov_Ray_WireFrame::~CFIT_6203_Voronkov_Ray_WireFrame()
{

}

CFIT_6203_Voronkov_Ray_WireFrame& CFIT_6203_Voronkov_Ray_WireFrame::operator=
		(const CFIT_6203_Voronkov_Ray_WireFrame& obj)
{
	clear();
	pos = NULL;
	POSITION p = obj.segms.GetHeadPosition();
	while (p){
		segms.AddTail(obj.segms.GetNext(p));
	}
	for (int i=0; i<3; i++){
		m_max_coord[i] = obj.m_max_coord[i];
		m_min_coord[i] = obj.m_min_coord[i];
	}
	return *this;
}

CFIT_6203_Voronkov_Ray_WireFrame& CFIT_6203_Voronkov_Ray_WireFrame::operator+=
		(const Segment& seg)
{
	segms.AddTail(seg);
	return *this;
}
CFIT_6203_Voronkov_Ray_WireFrame& CFIT_6203_Voronkov_Ray_WireFrame::operator+=
		(const CFIT_6203_Voronkov_Ray_WireFrame& obj)
{
	POSITION p = obj.segms.GetHeadPosition();
	while (p){
		segms.AddTail(obj.segms.GetNext(p));
	}
	return *this;
}
CFIT_6203_Voronkov_Ray_WireFrame CFIT_6203_Voronkov_Ray_WireFrame::operator+
		(const CFIT_6203_Voronkov_Ray_WireFrame& obj)
{
	WireFrame res;
	res += obj;
	return res;
}
void CFIT_6203_Voronkov_Ray_WireFrame::setOuterBoxMax(int coord, const double & value)
{
	ASSERT (coord == 0 || coord == 1 || coord == 2);
	m_max_coord[coord] = value;
}
void CFIT_6203_Voronkov_Ray_WireFrame::setOuterBoxMin(int coord, const double & value)
{
	ASSERT (coord == 0 || coord == 1 || coord == 2);
	m_min_coord[coord] = value;
}
const double & CFIT_6203_Voronkov_Ray_WireFrame::getOuterBoxMax(int coord) const
{
	ASSERT (m_max_coord[0] >= m_min_coord[0]);
	ASSERT (m_max_coord[1] >= m_min_coord[1]);
	ASSERT (m_max_coord[2] >= m_min_coord[2]);
	ASSERT (coord == 0 || coord == 1 || coord == 2);
	return m_max_coord[coord];
}
const double & CFIT_6203_Voronkov_Ray_WireFrame::getOuterBoxMin(int coord) const
{
	ASSERT (m_max_coord[0] >= m_min_coord[0]);
	ASSERT (m_max_coord[1] >= m_min_coord[1]);
	ASSERT (m_max_coord[2] >= m_min_coord[2]);
	ASSERT (coord == 0 || coord == 1 || coord == 2);
	return m_min_coord[coord];
}
void CFIT_6203_Voronkov_Ray_WireFrame::restartIterator()
{
	pos = segms.GetHeadPosition();
}
boolean CFIT_6203_Voronkov_Ray_WireFrame::hasNextSegment()
{
	return (pos != NULL);
}
Segment CFIT_6203_Voronkov_Ray_WireFrame::nextSegment()
{
	return segms.GetNext(pos);
}

void CFIT_6203_Voronkov_Ray_WireFrame::clear()
{
	segms.RemoveAll();
	pos = segms.GetHeadPosition();
}
const CList<Segment> & CFIT_6203_Voronkov_Ray_WireFrame::content() const
{
	return segms;
}
CString CFIT_6203_Voronkov_Ray_WireFrame::show() const
{
	CString str;
	POSITION pos = this->segms.GetHeadPosition();
	Segment seg;
	while(pos)
	{
		seg = this->segms.GetNext(pos);
		str.AppendFormat("%s\n", seg.show());
	}
	return str;
}
CFIT_6203_Voronkov_Ray_WireFrame CFIT_6203_Voronkov_Ray_WireFrame::cube
	(double xss, double yss, double zss, double xff, double yff, double zff)
{
	WireFrame res;
	Segment seg;
	COLORREF color = RGB(8, 8, 128);
	double xs, ys, zs;
	double xf, yf, zf;
	xs = xss;
	xf = xff;

	ys = yss;
	yf = yss;
	zs = zss;
	zf = zss;
	res += Segment(xs, ys, zs, xf, yf, zf, color);
	ys = yff;
	yf = yff;
	res += Segment(xs, ys, zs, xf, yf, zf, color);
	zs = zff;
	zf = zff;
	res += Segment(xs, ys, zs, xf, yf, zf, color);
	ys = yss;
	yf = yss;
	res += Segment(xs, ys, zs, xf, yf, zf, color);

	ys = yss;
	yf = yff;

	xs = xss;
	xf = xss;
	zs = zss;
	zf = zss;
	res += Segment(xs, ys, zs, xf, yf, zf, color);
	xs = xff;
	xf = xff;
	res += Segment(xs, ys, zs, xf, yf, zf, color);
	zs = zff;
	zf = zff;
	res += Segment(xs, ys, zs, xf, yf, zf, color);
	xs = xss;
	xf = xss;
	res += Segment(xs, ys, zs, xf, yf, zf, color);
	
	zs = zss;
	zf = zff;

	xs = xss;
	xf = xss;
	ys = yss;
	yf = yss;
	res += Segment(xs, ys, zs, xf, yf, zf, color);
	xs = xff;
	xf = xff;
	res += Segment(xs, ys, zs, xf, yf, zf, color);
	ys = yff;
	yf = yff;
	res += Segment(xs, ys, zs, xf, yf, zf, color);
	xs = xss;
	xf = xss;
	res += Segment(xs, ys, zs, xf, yf, zf, color);
	return res;

}

CFIT_6203_Voronkov_Ray_WireFrame CFIT_6203_Voronkov_Ray_WireFrame::
		orts(const Point & center, double size)
{
	WireFrame res;
	Segment seg;
	seg.setColor(255, 0, 0);
	seg.setStart(center);
	seg.setFinish(center + Point(size, 0, 0));
	res += seg;
	
	seg.setColor(0, 255, 0);
	seg.setStart(center);
	seg.setFinish(center + Point(0, size, 0));
	res += seg;
	
	seg.setColor(0, 0, 255);
	seg.setStart(center);
	seg.setFinish(center + Point(0, 0, size));
	res += seg;
	return res;
}
CFIT_6203_Voronkov_Ray_WireFrame CFIT_6203_Voronkov_Ray_WireFrame::orts
	(const Point & center, const Point & sizes)
{
	return orts(center, sizes.x(), sizes.y(), sizes.z());
}
CFIT_6203_Voronkov_Ray_WireFrame CFIT_6203_Voronkov_Ray_WireFrame::orts
	(const Point & center, double xsize, double ysize, double zsize)
{
	WireFrame res;
	Segment seg;
	seg.setWidth(3);
	seg.setColor(255, 0, 0);

	seg.setStart(center);
	seg.setFinish(center + Point(xsize, 0, 0));
	res += seg;
	
	seg.setColor(0, 255, 0);
	seg.setStart(center);
	seg.setFinish(center + Point(0, ysize, 0));
	res += seg;
	
	seg.setColor(0, 0, 255);
	seg.setStart(center);
	seg.setFinish(center + Point(0, 0, zsize));
	res += seg;
	return res;
}