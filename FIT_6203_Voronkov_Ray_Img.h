#pragma once

#include "FIT_6203_Voronkov_Ray_Color.h"

class CFIT_6203_Voronkov_Ray_Img
{
private:
	CArray<CArray<Color>> m_img;
	int m_width;
	int m_height;
	double max_value;
	double m_gamma;
public:
	CFIT_6203_Voronkov_Ray_Img(void);
	CFIT_6203_Voronkov_Ray_Img(const CFIT_6203_Voronkov_Ray_Img&);
	~CFIT_6203_Voronkov_Ray_Img(void);
	
	void setSize(int width, int height);
	void setSize(const CSize & size);
	CSize size() const;

	void setReal(int x, int y, const Color & color);
	const Color & getReal(int x, int y)const;

	void setGamma (const double & );
	CFIT_6203_Voronkov_Ray_Img& operator=(const CFIT_6203_Voronkov_Ray_Img &);
	CFIT_6203_Voronkov_Ray_Img toHalfSize();
	CFIT_6203_Voronkov_Ray_Img toDoubleSize(const CSize & res_size);

	COLORREF rgb(int x, int y)const;
};

typedef CFIT_6203_Voronkov_Ray_Img Image;