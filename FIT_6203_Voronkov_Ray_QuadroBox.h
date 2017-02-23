#pragma once

#include "FIT_6203_Voronkov_Ray_Primitive.h"
#include "FIT_6203_Voronkov_Ray_Box.h"
#include "FIT_6203_Voronkov_Ray_Quadric.h"

class CFIT_6203_Voronkov_Ray_QuadroBox : public Primitive
{
private:
	Box m_box;
	Quadric m_quadric;
public:
	CFIT_6203_Voronkov_Ray_QuadroBox();
	CFIT_6203_Voronkov_Ray_QuadroBox(const Quadric & q, const Box & b);
	~CFIT_6203_Voronkov_Ray_QuadroBox();

	enum PrimitiveType getType() const{return QDR;}
	WireFrame getWireFrame() const;
	double getMax(int coord) const;
	double getMin(int coord) const;
	bool isCorrect() const;

	virtual bool calculateIntersection();
	virtual bool calculateNormal();
};

typedef CFIT_6203_Voronkov_Ray_QuadroBox QuadroBox;