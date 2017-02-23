#pragma once

#include "FIT_6203_Voronkov_Ray_Point.h"
#include "FIT_6203_Voronkov_Ray_Primitive.h"

class CFIT_6203_Voronkov_Ray_Polygon : public Primitive
{
private:
	CArray<Point> m_vertexes;

	bool is_correct; // flag if correct
	
	double m_A;
	double m_B;
	double m_C;
	double m_D;
public:
	bool checkPolygon();
	CFIT_6203_Voronkov_Ray_Polygon();
	~CFIT_6203_Voronkov_Ray_Polygon();
	void addPoint(const Point & point);
	void insertPoint(int idx, const Point & point);
	void insertPoint(int idx, const double& x, const double& y, const double& z);
	void setVertexCount(int count);
	int count()const;
	const Point & getVertex(int idx)const;

	const CFIT_6203_Voronkov_Ray_Polygon & operator=(const CFIT_6203_Voronkov_Ray_Polygon&);
//	const Point &  getNormal() const;
	double getD() const;
	bool isInside(const Point &) const;

	bool isCorrect() const;
	CString toString() const;

	enum PrimitiveType getType() const {return PLG;}
	WireFrame getWireFrame() const;
	double getMax(int coord) const;
	double getMin(int coord) const;

	virtual bool calculateIntersection();
	virtual bool calculateNormal();
};

typedef CFIT_6203_Voronkov_Ray_Polygon Polygone;