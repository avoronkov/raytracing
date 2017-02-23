// FIT_6203_Voronkov_RayDoc.cpp : implementation of the CFIT_6203_Voronkov_RayDoc class
//

#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray.h"

#include "FIT_6203_Voronkov_RayDoc.h"

#include "FIT_6203_Voronkov_Ray_Io.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MOUSE_ZOOM 20

// CFIT_6203_Voronkov_RayDoc

IMPLEMENT_DYNCREATE(CFIT_6203_Voronkov_RayDoc, CDocument)

BEGIN_MESSAGE_MAP(CFIT_6203_Voronkov_RayDoc, CDocument)
END_MESSAGE_MAP()


// CFIT_6203_Voronkov_RayDoc construction/destruction

CFIT_6203_Voronkov_RayDoc::CFIT_6203_Voronkov_RayDoc()
{
	// TODO: add one-time construction code here
	m_scene = NULL;
	m_scene_loaded = false;
	m_wire_frame_loaded = false;
}

CFIT_6203_Voronkov_RayDoc::~CFIT_6203_Voronkov_RayDoc()
{
	delete m_scene;
}

BOOL CFIT_6203_Voronkov_RayDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	delete m_scene;
	m_scene = NULL;
	m_scene_loaded = false;
	m_wire_frame_loaded = false;
	params.flag_doc_opeded = false;
	params.flag_render_in_process = false;
	params.flag_render_ready = false;

	return TRUE;
}




// CFIT_6203_Voronkov_RayDoc serialization

void CFIT_6203_Voronkov_RayDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		Matrix rotate = this->m_trans_backwards * this->m_pre_final * this->m_trans_from_center;
		// TODO
//		Camera cam(params.getWidth(), params.getHeight(), params.distance, rotate);
//		Io::saveCamera(&ar, cam);
	}
	else
	{
		// TODO: add loading code here
		m_scene = new Scene();
		bool no_warning = Io::loadScene(&ar, m_scene);
		if (!no_warning)
		{
			AfxMessageBox(CString("One or more primitives are incorrent"));
		}
		TRACE("Done loading scene\n");
		m_scene_loaded = true;
		m_wire_frame_start = m_scene->getWireFrame();
		m_wire_frame_loaded = true;
		// Try to load camera-file
		try{
			CString cam_filename = ar.GetFile()->GetFileName();
			
			CString path = ar.GetFile()->GetFilePath();
			path = path.Left(path.ReverseFind('\\')+1);
			
			cam_filename = path + CString("rnd_") + cam_filename;
			CFile cam_file(cam_filename, CFile::modeRead);
			CArchive cam_archive(&cam_file, CArchive::load);
			Camera camera;
			// TODO
			Io::loadRenderSet(&cam_archive, &render_set);
			prepareWireFrame(render_set);
//			AfxMessageBox(CString("Loaded camera"));
		}
		catch(...)
		{
//			AfxMessageBox(CString("No camera camera"));
			prepareWireFrame();
			initRenderSet();
		}
		
		UpdateAllViews(NULL);
	}
}

bool CFIT_6203_Voronkov_RayDoc::prepareWireFrame()
{
	double xss = m_wire_frame_start.getOuterBoxMin(0);
	double xff = m_wire_frame_start.getOuterBoxMax(0);
	double yss = m_wire_frame_start.getOuterBoxMin(1);
	double yff = m_wire_frame_start.getOuterBoxMax(1);
	double zss = m_wire_frame_start.getOuterBoxMin(2);
	double zff = m_wire_frame_start.getOuterBoxMax(2);
	
	Point center((xss+xff)/2.0, (yss+yff)/2.0, (zss+zff)/2.0);
	Point ort_sizes(abs(xss-xff)/1.8, abs(yss-yff)/1.8, abs(yss-yff)/1.8);

	m_wire_frame_start += WireFrame::orts(center, ort_sizes);
	m_wire_frame_start += WireFrame::cube(xss, yss, zss, xff, yff, zff);

	params.flag_doc_opeded = true;
	params.flag_raster_modified = true;
	params.d = (abs(xss-xff) + abs(yss-yff) + abs(yss-yff)) / MOUSE_ZOOM;
	// translating
	params.s_w = abs(xss-xff);
	params.s_h = ((double) params.s_w) * params.getHeight() / params.getWidth();
//	params.s_h = abs(yss-yff);

	
	params.z_near = 0.5 * params.s_w / params.TG_15;
	params.z_far = params.z_near + 1.5 * abs(zss-zff);
	m_trans_to_center.createTranslate(- center.x(), - center.y(), - center.z());
	m_trans_from_center.createTranslate(center.x(), center.y(), center.z());
	params.distance = params.z_near + 0.5 * abs(zff - zss);
	m_trans_forward.createTranslate(0, 0,params.distance);
	m_trans_backwards.createTranslate(0, 0, -params.distance);
	m_proj.createMproj(params.s_w, params.s_h, params.z_near, params.z_far);
	m_pre_final = m_trans_forward * m_trans_to_center;
	m_final = m_proj * m_pre_final;

	m_wire_frame_finish = m_final * m_wire_frame_start;

	return true;
}
bool CFIT_6203_Voronkov_RayDoc::prepareWireFrame(const RenderSet & set)
{
	double xss = m_wire_frame_start.getOuterBoxMin(0);
	double xff = m_wire_frame_start.getOuterBoxMax(0);
	double yss = m_wire_frame_start.getOuterBoxMin(1);
	double yff = m_wire_frame_start.getOuterBoxMax(1);
	double zss = m_wire_frame_start.getOuterBoxMin(2);
	double zff = m_wire_frame_start.getOuterBoxMax(2);
	
	Point center((xss+xff)/2.0, (yss+yff)/2.0, (zss+zff)/2.0);
	Point ort_sizes(abs(xss-xff)/1.8, abs(yss-yff)/1.8, abs(yss-yff)/1.8);

	m_wire_frame_start += WireFrame::orts(center, ort_sizes);
	m_wire_frame_start += WireFrame::cube(xss, yss, zss, xff, yff, zff);

	params.flag_doc_opeded = true;
	params.flag_raster_modified = true;
	const CSize & scroll_size = set.scrollSize();
	params.setWidth(scroll_size.cx);
	params.setHeight(scroll_size.cy);

	params.d = (abs(xss-xff) + abs(yss-yff) + abs(yss-yff)) / MOUSE_ZOOM;

	// translating
	params.s_w = abs(xss-xff);
	params.s_h = ((double) params.s_w) * params.getHeight() / params.getWidth();
//	params.s_h = abs(yss-yff);

	
	params.z_near = 0.5 * params.s_w / params.TG_15;
	params.z_far = params.z_near + 1.5 * abs(zss-zff);
	m_trans_to_center.createTranslate(- center.x(), - center.y(), - center.z());
	m_trans_from_center.createTranslate(center.x(), center.y(), center.z());

	const Camera & camera = set.camera();
	params.distance = camera.centerZ();

	m_trans_forward.createTranslate(0, 0, params.distance);
	m_trans_backwards.createTranslate(0, 0, -params.distance);

	const Matrix & rotate = camera.matrixRotate();

	m_proj.createMproj(params.s_w, params.s_h, params.z_near, params.z_far);
	m_pre_final = m_trans_forward * rotate * m_trans_to_center;
	m_final = m_proj * m_pre_final;

	m_wire_frame_finish = m_final * m_wire_frame_start;

	return true;
}
bool CFIT_6203_Voronkov_RayDoc::initRenderSet()
{
	render_set.setBackground(RGB(0,0,0));
	render_set.setGamma(1.0);
	render_set.setQuality(RenderSet::Q_ROUGH);
	render_set.setTreeDepth(3);
	render_set.setScrollSize(params.getWidth(), params.getHeight());
	return true;
}

void CFIT_6203_Voronkov_RayDoc::prepareRendering()
{
	Matrix rotate = m_trans_backwards * m_pre_final * m_trans_from_center;
	Matrix back_rotate = rotate.transpose();
	Matrix res = m_trans_from_center * back_rotate /* * m_trans_backwards */;
	// FIND BORDERS
	Point origin = Point(0, 0, -params.distance);
	const double z_offset = 10.0;
	double x_offset = (z_offset * params.TG_15);
	double y_offset = (x_offset * params.getHeight()) / params.getWidth();
	m_render_eye.setOrigin(origin);
	m_render_eye.setBorder(0, Point(-x_offset, y_offset, z_offset - params.distance));
	m_render_eye.setBorder(1, Point(x_offset, y_offset, z_offset - params.distance));
	m_render_eye.setBorder(2, Point(-x_offset, -y_offset, z_offset - params.distance));
	m_render_eye.setBorder(3, Point(x_offset, -y_offset, z_offset - params.distance));
	
	
	m_render_eye = res * m_render_eye;
	
	if (render_set.quality() == RenderSet::Q_NORMAL){
		m_render_pre_image.setSize(render_set.scrollSize());
		m_render_eye.setFreq(params.getWidth(), params.getHeight());
	}
	else if(render_set.quality() == RenderSet::Q_ROUGH){
		m_render_pre_image.setSize((render_set.scrollSize().cx / 2 )+ 1,
				(render_set.scrollSize().cy / 2 )+ 1);
		m_render_eye.setFreq((params.getWidth() / 2)+1, (params.getHeight()/2) +1);
	}
	else if(render_set.quality() == RenderSet::Q_FINE){
		m_render_pre_image.setSize(render_set.scrollSize().cx * 2,
				render_set.scrollSize().cy * 2);
		m_render_eye.setFreq(params.getWidth()*2, params.getHeight()*2);
	}
	else{
		ASSERT (false);
	}
	m_render_image.setSize(params.getWidth(), params.getHeight());
	
	params.flag_render_in_process = true;
	params.render_percents_ready = 0;
}
// key function
void CFIT_6203_Voronkov_RayDoc::render()
{
	CSize size = m_render_pre_image.size();
	Ray orig;
	for (int i=0; i<size.cy; i++){
		for (int j=0; j<size.cx; j++){
			orig = m_render_eye.getRay(j, i);
			Color c = renderRay(orig, render_set.treeDepth(), NULL);
			ASSERT (c.r() >= 0);
			ASSERT (c.g() >= 0);
			ASSERT (c.b() >= 0);

			m_render_pre_image.setReal(j, i, c);
		}
		params.render_percents_ready = 100 * i / size.cy;
		UpdateAllViews(NULL);
#ifdef _DEBUG
		CString tmp;
		tmp.Format("%03d percents \n", (100 * i / size.cy));
		TRACE (tmp);
#endif
	}
	m_render_pre_image.setGamma(render_set.gamma());
	if (render_set.quality() == RenderSet::Q_NORMAL){
		m_render_image = m_render_pre_image;
	}
	else if(render_set.quality() == RenderSet::Q_ROUGH){
		m_render_image = m_render_pre_image.toDoubleSize(render_set.scrollSize());
	}
	else if(render_set.quality() == RenderSet::Q_FINE){
		m_render_image = m_render_pre_image.toHalfSize();
	}
	else{
		ASSERT (false);
	}
	params.flag_render_in_process = false;
	params.flag_render_ready = true;
}
Color CFIT_6203_Voronkov_RayDoc::renderRay(const Ray & orig, int depth, double * distance_out)
{
	if (depth == 0) {
		if (distance_out != NULL) *distance_out = 1.0;
		return Color(0,0,0);
	}
	Color color;
	Ray refl;
	Ray normal;
	Primitive * pprim;
	const Color & ambient_light = m_scene->ambientColor();
	int light_count = m_scene->countLights();
	bool has_int = m_scene->intersect(orig, & refl, &normal, &pprim);
	if (has_int)
	{
		// ambient light
		Point shifted_int = normal.getOrigin() + (normal.getDirection() * EPS);
		Color ambient = ambient_light * (pprim->getAmbientFactor());
		ASSERT (ambient.r() >= 0);
		ASSERT (ambient.g() >= 0);
		ASSERT (ambient.b() >= 0);
		Color diffuse(0, 0, 0);
		Color specular(0, 0, 0);
		for (int ii=0; ii<light_count; ii++)
		{
			if (m_scene->lightIsVisible(shifted_int, ii))
			{
				// check normal
				//if (orig.getDirection().cos(normal.getDirection()) > 0){
				//	normal.setDirection(-normal.getDirection());
				//}
				// eval difuuse light
				double dist = (refl.getOrigin() - m_scene->light(ii).position()).length();
				diffuse = m_scene->countDiffuseLight(normal, pprim->getDiffuseFactor(), ii);
				ASSERT (diffuse.r() >= 0);
				ASSERT (diffuse.g() >= 0);
				ASSERT (diffuse.b() >= 0);
				specular = m_scene->countSpecularLight(normal, -orig.getDirection(), 
						pprim->getSpecularFactor(), ii, pprim->getPower());
				ASSERT (specular.r() >= 0);
				ASSERT (specular.g() >= 0);
				ASSERT (specular.b() >= 0);
				color += ((m_scene->light(ii).color() * (diffuse + specular)) / (dist + 1));
			}
		}
		color += ambient;
		ASSERT (color.r() >= 0);
		ASSERT (color.g() >= 0);
		ASSERT (color.b() >= 0);
		color.setBackground(false);
		refl.setOrigin(refl.getOrigin() + (refl.getDirection() * EPS));
		double next_distance;
		Color next = renderRay(refl, depth - 1, &next_distance);
		ASSERT (next.r() >= 0);
		ASSERT (next.g() >= 0);
		ASSERT (next.b() >= 0);
		if (distance_out != NULL) *distance_out = (normal.getOrigin() - orig.getOrigin()).length();
		return color + (next * pprim->getSpecularFactor() / (next_distance + 1));
	}
	else
	{
		color.setBackground(true);
		if (distance_out != NULL) *distance_out = 1.0;
		return color;
	}
}
void CFIT_6203_Voronkov_RayDoc::moveZoom(int gradation)
{
	if (!params.flag_doc_opeded) return;
	m_pre_final = m_trans_backwards * m_pre_final;
	params.distance -= params.d * gradation;
	m_trans_forward.createTranslate(0, 0, params.distance);
	m_trans_backwards.createTranslate(0, 0, -params.distance);
	m_pre_final = m_trans_forward * m_pre_final;
	m_final = m_proj * m_pre_final;
	m_wire_frame_finish = m_final * m_wire_frame_start;
	UpdateAllViews(NULL);
}


// CFIT_6203_Voronkov_RayDoc diagnostics

#ifdef _DEBUG
void CFIT_6203_Voronkov_RayDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFIT_6203_Voronkov_RayDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFIT_6203_Voronkov_RayDoc commands
