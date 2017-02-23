// FIT_6203_Voronkov_RayDoc.h : interface of the CFIT_6203_Voronkov_RayDoc class
//


#pragma once

#include "FIT_6203_Voronkov_Ray_Scene.h"
#include "FIT_6203_Voronkov_Ray_WireFrame.h"
#include "FIT_6203_Voronkov_Ray_Matrix.h"
#include "FIT_6203_Voronkov_Ray_Params.h"
#include "FIT_6203_Voronkov_Ray_RenderSet.h"
#include "FIT_6203_Voronkov_Ray_Eye.h"
#include "FIT_6203_Voronkov_Ray_Img.h"

class CFIT_6203_Voronkov_RayDoc : public CDocument
{
protected: // create from serialization only
	CFIT_6203_Voronkov_RayDoc();
	DECLARE_DYNCREATE(CFIT_6203_Voronkov_RayDoc)

// Attributes
public:
	bool m_scene_loaded;
	bool m_wire_frame_loaded;

	Scene * m_scene;
	Matrix m_trans_forward; // перемещение назад по оси Z
	Matrix m_trans_backwards; // перемещение вперед по оси Z
	Matrix m_trans_to_center; // перемещение центра бокса в начало координат
	Matrix m_trans_from_center; // перемещение центра бокса в первоначальную позицию
//	Matrix m_scale;
	Matrix m_rotate_x;
	Matrix m_rotate_y;
	Matrix m_final;
	Matrix m_pre_final;
	Matrix m_proj;

// Attributes

	Params params;
	RenderSet render_set;
	WireFrame m_wire_frame_start; // первоначальное состояние сцены
	WireFrame m_wire_frame_finish; // финальное состояние сцены

	Eye m_render_eye; // "глаз" рендеринга
	Image m_render_image; // результат рендеринга
	Image m_render_pre_image;

// Operations
public:
	bool prepareWireFrame();
	bool prepareWireFrame(const RenderSet & set);
	bool initRenderSet();

	void prepareRendering();
	void render();
	Color renderRay(const Ray &, int depth, double * distance_out);

	void moveZoom(int gradation);
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CFIT_6203_Voronkov_RayDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


