#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_RenderSet.h"

CFIT_6203_Voronkov_Ray_RenderSet::CFIT_6203_Voronkov_Ray_RenderSet()
{
}
CFIT_6203_Voronkov_Ray_RenderSet::~CFIT_6203_Voronkov_Ray_RenderSet()
{
}

void CFIT_6203_Voronkov_Ray_RenderSet::setCamera(const Camera & cam)
{
	m_camera = cam;
}
void CFIT_6203_Voronkov_Ray_RenderSet::setScrollSize(int width, int height)
{
	m_scroll_size.SetSize(width, height);
}
void CFIT_6203_Voronkov_Ray_RenderSet::setScrollSize(const CSize & size)
{
	m_scroll_size = size;
}
void CFIT_6203_Voronkov_Ray_RenderSet::setBackground(COLORREF back)
{
	m_background = back;
}
void CFIT_6203_Voronkov_Ray_RenderSet::setGamma(const double & value)
{
	m_gamma = value;
}
void CFIT_6203_Voronkov_Ray_RenderSet::setTreeDepth(int depth)
{
	m_tree = depth;
}
void CFIT_6203_Voronkov_Ray_RenderSet::setQuality(int quality)
{
	ASSERT (CFIT_6203_Voronkov_Ray_RenderSet::Q_ROUGH == quality || 
		CFIT_6203_Voronkov_Ray_RenderSet::Q_NORMAL == quality ||
		CFIT_6203_Voronkov_Ray_RenderSet::Q_FINE == quality);
	m_quality = quality;
}

const Camera & CFIT_6203_Voronkov_Ray_RenderSet::camera() const
{
	return m_camera;
}
const CSize & CFIT_6203_Voronkov_Ray_RenderSet::scrollSize() const
{
	return m_scroll_size;
}
COLORREF CFIT_6203_Voronkov_Ray_RenderSet::background() const
{
	return m_background;
}
const double & CFIT_6203_Voronkov_Ray_RenderSet::gamma() const
{
	return m_gamma;
}
int CFIT_6203_Voronkov_Ray_RenderSet::treeDepth() const
{
	return m_tree;
}
int CFIT_6203_Voronkov_Ray_RenderSet::quality() const
{
	return m_quality;
}

