#include "StdAfx.h"
#include "FIT_6203_Voronkov_Ray_Img.h"

CFIT_6203_Voronkov_Ray_Img::CFIT_6203_Voronkov_Ray_Img(void)
{
	max_value = 0;
	m_gamma = 1.0;
}
CFIT_6203_Voronkov_Ray_Img::CFIT_6203_Voronkov_Ray_Img
		(const CFIT_6203_Voronkov_Ray_Img& obj)
{
	this->setSize(obj.size());
	for (int i=0; i<m_height; i++)
	{
		for (int j=0; j<m_width; j++)
		{
			m_img[i][j] = obj.m_img[i][j];
		}
	}
	this->max_value = obj.max_value;
	this->m_gamma = obj.m_gamma;
}
CFIT_6203_Voronkov_Ray_Img::~CFIT_6203_Voronkov_Ray_Img(void)
{
}

CFIT_6203_Voronkov_Ray_Img& CFIT_6203_Voronkov_Ray_Img::operator=
		(const CFIT_6203_Voronkov_Ray_Img & obj)
{
	this->setSize(obj.size());
	for (int i=0; i<m_height; i++)
	{
		for (int j=0; j<m_width; j++)
		{
			m_img[i][j] = obj.m_img[i][j];
		}
	}
	this->max_value = obj.max_value;
	this->m_gamma = obj.m_gamma;
	return * this;
}
void CFIT_6203_Voronkov_Ray_Img::setSize(int width, int height)
{
	m_height = height;
	m_width = width;
	m_img.SetSize(height);
	for (int i=0; i<height; i++)
	{
		m_img[i].SetSize(width);
	}
}
void CFIT_6203_Voronkov_Ray_Img::setSize(const CSize & size)
{
	setSize(size.cx, size.cy);
}
CSize CFIT_6203_Voronkov_Ray_Img::size() const
{
	return CSize(m_width, m_height);
}

void CFIT_6203_Voronkov_Ray_Img::setReal(int x, int y, const Color & color)
{
	ASSERT (x >= 0 && x < m_width);
	ASSERT (y >= 0 && y <= m_height);
	m_img[y][x] = color;
	if (color.r() > max_value) max_value = color.r();
	if (color.g() > max_value) max_value = color.g();
	if (color.b() > max_value) max_value = color.b();
}
const Color & CFIT_6203_Voronkov_Ray_Img::getReal(int x, int y)const
{
	ASSERT (x >= 0 && x < m_width);
	ASSERT (y >= 0 && y <= m_height);
	return m_img[y][x];
}

COLORREF CFIT_6203_Voronkov_Ray_Img::rgb(int x, int y)const
{
	// TODO
	ASSERT (x >= 0 && x < m_width);
	ASSERT (y >= 0 && y <= m_height);
	ASSERT (m_img[y][x].r() >= 0 && m_img[y][x].g() >= 0 && m_img[y][x].b() >= 0);
	int r = (int)(pow (m_img[y][x].r() / max_value, m_gamma) * 255 + 0.5);
	int g = (int)(pow (m_img[y][x].g() / max_value, m_gamma) * 255 + 0.5);
	int b = (int)(pow (m_img[y][x].b() / max_value, m_gamma) * 255 + 0.5);
#ifdef _DEBUG
	if  (r <0 || r > 255)
	{
		double rf = m_img[y][x].r();
		double gf = m_img[y][x].g();
		double bf = m_img[y][x].b();
		ASSERT (false);
	}
	if (g <0 || g > 255)
	{
		double rf = m_img[y][x].r();
		double gf = m_img[y][x].g();
		double bf = m_img[y][x].b();
		ASSERT (false);
	}
	if (b <0 || b > 255)
	{
		double rf = m_img[y][x].r();
		double gf = m_img[y][x].g();
		double bf = m_img[y][x].b();
		ASSERT (false);
	}
#endif
	return RGB(r,g,b);
}
void CFIT_6203_Voronkov_Ray_Img::setGamma (const double & value)
{
	m_gamma = value;
}

CFIT_6203_Voronkov_Ray_Img CFIT_6203_Voronkov_Ray_Img::toHalfSize()
{
	ASSERT ((m_height) % 2 == 0);
	ASSERT ((m_width) % 2 == 0);
	int res_width = (m_width) / 2;
	int res_height = (m_height) / 2;
	Image res;
	res.setSize(res_width, res_height);
	res.setGamma(m_gamma);
	for (int i=0; i<res_height; i++)
	{
		for (int j=0; j<res_width; j++)
		{
			Color res_color;
			res_color += this->getReal(2*j, 2*i);
			res_color += this->getReal(2*j+1, 2*i);
			res_color += this->getReal(2*j, 2*i+1);
			res_color += this->getReal(2*j+1, 2*i+1);
			res_color /= 4.0;
			res.setReal(j, i, res_color);
		}
	}
	return res;
}
CFIT_6203_Voronkov_Ray_Img CFIT_6203_Voronkov_Ray_Img::toDoubleSize(const CSize & res_size)
{
	Image res;

	res.setSize(res_size);
	res.setGamma(m_gamma);

	for (int i=0; i<res_size.cy; i++)
	{
		for (int j=0; j<res_size.cx; j++)
		{
			Color color;
			if ((i % 2 == 0) && (j % 2 == 0)){
				res.setReal(j, i, this->getReal(j/2, i/2));
			}
			else if ((i % 2 == 1) && (j % 2 == 0)){
				color = (getReal(j/2, i/2) + getReal(j/2, (i+1)/2)) / 2.0;
				res.setReal(j, i, color);
			}
			else if ((i % 2 == 0) && (j % 2 == 1)){
				color = (getReal(j/2, i/2) + getReal((j+1)/2, i/2)) / 2.0;
				res.setReal(j, i, color);
			}
			else{
				color = (getReal(j/2, i/2) + getReal((j+1)/2, i/2) +
						getReal(j/2, (i+1)/2) + getReal((j+1)/2, (i+1)/2)) / 4.0;
				res.setReal(j, i, color);
			}
		}
	}
	return res;
}