#pragma once

#include "FIT_6203_Voronkov_Ray_Matrix.h"

class CFIT_6203_Voronkov_Ray_Camera
{
private:
	double m_center_z;
//	int m_scroll_width;
//	int m_scroll_height;
	Matrix m_rotate;
public:
	CFIT_6203_Voronkov_Ray_Camera(void);
	CFIT_6203_Voronkov_Ray_Camera(const CFIT_6203_Voronkov_Ray_Camera &);
	CFIT_6203_Voronkov_Ray_Camera(const double & z, const Matrix & rotate); 
	~CFIT_6203_Voronkov_Ray_Camera(void);
	CFIT_6203_Voronkov_Ray_Camera & operator=(const CFIT_6203_Voronkov_Ray_Camera &);

	void setCenterZ(const double &);
	void setMatrixRotate(const Matrix &);

	const double & centerZ()const;
	const Matrix & matrixRotate() const;
};

typedef CFIT_6203_Voronkov_Ray_Camera Camera;
