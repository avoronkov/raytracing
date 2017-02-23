#pragma once

#include "FIT_6203_Voronkov_Ray_Ray.h"

class CFIT_6203_Voronkov_Ray_Quadric
{
private:
	double m_a;
	double m_e;
	double m_h;
	double m_b;
	double m_c;
	double m_f;
	double m_d;
	double m_g;
	double m_i;
	double m_j;
public:
	CFIT_6203_Voronkov_Ray_Quadric();
	CFIT_6203_Voronkov_Ray_Quadric(double A, double E, double H, double B, 
									double C, double F, double D,
									double G, double I, double J);
	~CFIT_6203_Voronkov_Ray_Quadric();

	CFIT_6203_Voronkov_Ray_Quadric & operator=(const CFIT_6203_Voronkov_Ray_Quadric &);
	
	const double & getA() const { return m_a;}
	const double & getE() const { return m_e;}
	const double & getH() const { return m_h;}
	const double & getB() const { return m_b;}
	const double & getC() const { return m_c;}
	const double & getF() const { return m_f;}
	const double & getD() const { return m_d;}
	const double & getG() const { return m_g;}
	const double & getI() const { return m_i;}
	const double & getJ() const { return m_j;}

	bool isCorrect() const;
	CString toString() const;

	int intersectRay(const Ray & ray, Point * i_near, Point * n_near, Point * refl_near, 
		double * t_near, Point * i_far, Point * n_far, Point * refl_far, double * t_far);
	Point getReflected(const Point & ray, const Point & normal)const;
};

typedef CFIT_6203_Voronkov_Ray_Quadric Quadric;