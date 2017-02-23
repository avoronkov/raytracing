#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_Params.h"

CFIT_6203_Voronkov_Ray_Params::CFIT_6203_Voronkov_Ray_Params()
{
	this->offset = 10;
	this->r = 0.01;
	this->d = 0.1;
	this->flag_raster_modified = false;
	this->m_width = 240;
	this->m_height = 240;
	this->flag_doc_opeded = false;
	this->TG_15 = tan(M_PI * 15.0 / 180);
	this->flag_colorful = false;
	this->flag_render_in_process = false;
	this->flag_render_ready = false;
}
CFIT_6203_Voronkov_Ray_Params::~CFIT_6203_Voronkov_Ray_Params()
{

}