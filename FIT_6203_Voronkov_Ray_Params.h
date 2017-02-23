#pragma once

class CFIT_6203_Voronkov_Ray_Params
{
private:
	int offset;
	int m_width; // x-component of scroll
	int m_height;  // y-component of scroll
public:
	void setWidth(int value){m_width = value;}
	void setHeight(int value){m_height = value;}
	void setXScroll(int value){m_height = value - 2 * offset;}
	void setYScroll(int value){m_width = value - 2 * offset;}
	int scrollX()const{return m_width + 2 * offset;}
	int scrollY()const{return m_height + 2 * offset;}
	int getHeight()const {return m_height;}
	int getWidth()const {return m_width;}
	int getOffset() const {return offset;}

public:
	bool flag_raster_modified; // set if raster-size if modified
	
	double r; // r  - for rotating
	double d; // d - for moving foreard/backwards

	bool flag_doc_opeded; // set is document is opened

	double z_near; // z_near for m_proj
	double z_far; // z_far for m_proj

	double s_w; // s_w
	double s_h; // s_h

	double distance; // z-distance

	double TG_15;

	bool flag_colorful;

	bool flag_render_in_process;
	int render_percents_ready;
	bool flag_render_ready;
public:
	CFIT_6203_Voronkov_Ray_Params();
	~CFIT_6203_Voronkov_Ray_Params();
};

typedef CFIT_6203_Voronkov_Ray_Params Params;