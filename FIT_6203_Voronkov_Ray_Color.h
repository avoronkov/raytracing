#pragma once

class CFIT_6203_Voronkov_Ray_Color
{
private:
	double m_r;
	double m_g;
	double m_b;
	bool is_background;
public:
	CFIT_6203_Voronkov_Ray_Color();
	CFIT_6203_Voronkov_Ray_Color(const double & _r, const double & _g, const double & _b);
	~CFIT_6203_Voronkov_Ray_Color();
	
	CFIT_6203_Voronkov_Ray_Color & operator=(const CFIT_6203_Voronkov_Ray_Color & obj);

	const double & r() const {return m_r;}
	const double & g() const {return m_g;}
	const double & b() const {return m_b;}
	void setR(const double & _r){m_r = _r;}
	void setG(const double & _g){m_g = _g;}
	void setB(const double & _b){m_b = _b;}
	void set(const double & _r, const double & _g, const double & _b);

	CFIT_6203_Voronkov_Ray_Color operator*(const CFIT_6203_Voronkov_Ray_Color&)const;
	CFIT_6203_Voronkov_Ray_Color operator*(const double&)const;
	CFIT_6203_Voronkov_Ray_Color operator/(const double&)const;
	CFIT_6203_Voronkov_Ray_Color& operator/=(const double&);
	CFIT_6203_Voronkov_Ray_Color operator+(const CFIT_6203_Voronkov_Ray_Color&)const;
	CFIT_6203_Voronkov_Ray_Color& operator+=(const CFIT_6203_Voronkov_Ray_Color&);

	void setBackground(bool value){	is_background = value;}
	bool isBackground()const{return is_background;}
};

typedef CFIT_6203_Voronkov_Ray_Color Color;