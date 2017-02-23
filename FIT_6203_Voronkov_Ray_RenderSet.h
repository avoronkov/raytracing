#pragma once

#include "FIT_6203_Voronkov_Ray_Camera.h"

class CFIT_6203_Voronkov_Ray_RenderSet
{
private:
	Camera m_camera;
	CSize m_scroll_size;
	COLORREF m_background;
	double m_gamma;
	int m_tree;
	int m_quality;
public:
	static const int Q_ROUGH = 0;
	static const int Q_NORMAL = 1;
	static const int Q_FINE = 2;
public:
	CFIT_6203_Voronkov_Ray_RenderSet();
	~CFIT_6203_Voronkov_Ray_RenderSet();

	void setCamera(const Camera &);
	void setScrollSize(int width, int height);
	void setScrollSize(const CSize & size);
	void setBackground(COLORREF );
	void setGamma(const double & gamma);
	void setTreeDepth(int depth);
	void setQuality(int quality);
	
	const Camera & camera() const;
	const CSize & scrollSize() const;
	COLORREF background() const;
	const double & gamma() const;
	int treeDepth() const;
	int quality() const;
};

typedef CFIT_6203_Voronkov_Ray_RenderSet RenderSet;