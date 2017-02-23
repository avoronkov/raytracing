#pragma once

#include "FIT_6203_Voronkov_Ray_WireFrame.h"
#include "FIT_6203_Voronkov_Ray_Point.h"
#include "FIT_6203_Voronkov_Ray_Ray.h"
#include "FIT_6203_Voronkov_Ray_Color.h"

enum PrimitiveType {SPH, BOX, PLG, QDR};

class CFIT_6203_Voronkov_Ray_Primitive
{
protected:
	//double m_k_Ar;
	//double m_k_Ag; // Кооф отр рассеянного света в формате 0..1
	//double m_k_Ab;
	Color m_k_A;

	//double m_k_Dr;
	//double m_k_Dg; // Кооф диффузного отр света в формате 0..1
	//double m_k_Db;
	Color m_k_D;

	//double m_k_Sr;
	//double m_k_Sg; // Кооф зеркального отр света в формате 0..1
	//double m_k_Sb;
	Color m_k_S;

	double m_power;

	double m_kt;

	double m_n_outside;
	double m_n_inside;

	Ray m_ray;

	bool has_intersection;
	Point m_intersection;
	Point m_normal;
	Point m_reflected;
	bool has_refracted;
	Point m_refracted;

	double m_t;

	bool ray_from_outside;

public:
	virtual enum PrimitiveType getType() const = 0;
	virtual WireFrame getWireFrame() const = 0;
	virtual double getMax(int coord) const = 0;
	virtual double getMin(int coord) const = 0;
	void setOptics(double k_Ar, double k_Ag, double k_Ab, double k_Dr, double k_Dg, double k_Db,
				double k_Sr, double k_Sg, double k_Sb, double power, double kt, double n1, double n2);
	const Color & getAmbientFactor()const;
	const Color & getDiffuseFactor() const;
	const Color & getSpecularFactor() const;
	
	const double & getPower() const{return m_power;}

	virtual void intersect(const Ray & ray);

	virtual bool calculateIntersection() = 0;
	virtual bool calculateNormal() = 0;
	bool calculateReflected();
	bool calculateRefracted();

	virtual bool hasIntersection()const {return has_intersection;}
	virtual const Point & getIntersection()const {return m_intersection;}
	virtual const double & getT()const {return m_t;}
	virtual const Point & getNormal()const {return m_normal;}
	virtual const Point & getReflected()const {return m_reflected;}
	virtual bool hasRefracted()const {return has_refracted;}
	virtual const Point & getRefracted()const {return m_refracted;}

	virtual bool isCorrect()const = 0;

};

typedef CFIT_6203_Voronkov_Ray_Primitive Primitive;