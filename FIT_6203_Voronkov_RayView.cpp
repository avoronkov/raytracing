// FIT_6203_Voronkov_RayView.cpp : implementation of the CFIT_6203_Voronkov_RayView class
//

#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray.h"

#include "FIT_6203_Voronkov_RayDoc.h"
#include "FIT_6203_Voronkov_RayView.h"

#include "FIT_6203_Voronkov_Ray_Io.h"

#include "FIT_6203_Voronkov_Ray_DialogOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFIT_6203_Voronkov_RayView

IMPLEMENT_DYNCREATE(CFIT_6203_Voronkov_RayView, CScrollView)

BEGIN_MESSAGE_MAP(CFIT_6203_Voronkov_RayView, CScrollView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_BUTTON_RENDER_LOAD, &CFIT_6203_Voronkov_RayView::OnButtonRenderLoad)
	ON_COMMAND(ID_BUTTON_RENDER_STORE, &CFIT_6203_Voronkov_RayView::OnButtonRenderStore)
	ON_COMMAND(ID_BUTTON_INIT, &CFIT_6203_Voronkov_RayView::OnButtonInit)
	ON_COMMAND(ID_BUTTON_OPTIONS, &CFIT_6203_Voronkov_RayView::OnButtonOptions)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_BUTTON_RENDER, &CFIT_6203_Voronkov_RayView::OnButtonRender)
	ON_COMMAND(ID_BUTTON_VIEW, &CFIT_6203_Voronkov_RayView::OnButtonView)
	ON_COMMAND(ID_BUTTON_SAVE_BMP, &CFIT_6203_Voronkov_RayView::OnButtonSaveBmp)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_BUTTON_MOVE_FAR, &CFIT_6203_Voronkov_RayView::OnButtonMoveFar)
	ON_COMMAND(ID_BUTTON_MOVE_NEAR, &CFIT_6203_Voronkov_RayView::OnButtonMoveNear)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_INIT, &CFIT_6203_Voronkov_RayView::OnUpdateButtonInit)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_MOVE_FAR, &CFIT_6203_Voronkov_RayView::OnUpdateButtonMoveFar)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_MOVE_NEAR, &CFIT_6203_Voronkov_RayView::OnUpdateButtonMoveNear)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_OPTIONS, &CFIT_6203_Voronkov_RayView::OnUpdateButtonOptions)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_RENDER, &CFIT_6203_Voronkov_RayView::OnUpdateButtonRender)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_RENDER_LOAD, &CFIT_6203_Voronkov_RayView::OnUpdateButtonRenderLoad)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_RENDER_STORE, &CFIT_6203_Voronkov_RayView::OnUpdateButtonRenderStore)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SAVE_BMP, &CFIT_6203_Voronkov_RayView::OnUpdateButtonSaveBmp)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_VIEW, &CFIT_6203_Voronkov_RayView::OnUpdateButtonView)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CFIT_6203_Voronkov_RayView construction/destruction

CFIT_6203_Voronkov_RayView::CFIT_6203_Voronkov_RayView()
{
	// TODO: add construction code here
	flag_l_button_down = false;
	prev_d_fi = 0;
	prev_d_tetta = 0;

	memDC = NULL;
	memBitmap = NULL;

	offset = 10;
}

CFIT_6203_Voronkov_RayView::~CFIT_6203_Voronkov_RayView()
{
}

BOOL CFIT_6203_Voronkov_RayView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CFIT_6203_Voronkov_RayView drawing

void CFIT_6203_Voronkov_RayView::OnDraw(CDC* pDC)
{
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CRect rect;
	GetClientRect(&rect);
	CPoint scroll_pos = GetScrollPosition();

	if (memDC == NULL || pDoc->params.flag_raster_modified)
	{
		raster_size =  CSize(pDoc->params.scrollX(), pDoc->params.scrollY());
		SetScrollSizes(MM_TEXT, raster_size);
		if (raster_size.cx > 0 && raster_size.cy > 0){
			view_port.cx = raster_size.cx - 2 * (offset + 1);
			view_port.cx = (view_port.cx > 0)?view_port.cx:0;
			view_port.cy = raster_size.cy - 2 * (offset + 1);
			view_port.cy = (view_port.cy > 0)?view_port.cy:0;
		}
		delete memDC;
		delete memBitmap;
		memDC = new CDC();
		memDC->CreateCompatibleDC(pDC);
		memBitmap = new CBitmap();
		memBitmap->DeleteObject();
		memBitmap->CreateCompatibleBitmap (pDC,raster_size.cx,raster_size.cy);
		memDC->SelectObject(memBitmap);
		
		memDC->FillSolidRect(0, 0, raster_size.cx, raster_size.cy, pDC->GetBkColor());
		pDC->BitBlt(0,0,rect.right,rect.bottom,memDC,0,0,SRCCOPY);
		pDoc->params.flag_raster_modified = false;
	}
	memDC->FillSolidRect(0, 0, raster_size.cx, raster_size.cy, pDC->GetBkColor());
	if (pDoc->params.flag_doc_opeded)
	{
		if (pDoc->params.flag_render_in_process)
		{
			CString str;
			str.Format("Render in progress...");
			memDC->TextOut(offset, offset, str);
		}
		else if (!pDoc->params.flag_render_ready)
		{
			drawArena(memDC, pDoc->m_wire_frame_finish, pDoc->params.flag_colorful);
			drawBorder(memDC);
		}
		else
		{
			// show rendered picture
			COLORREF back = pDoc->render_set.background();
			drawRenderedImage(memDC, pDoc->m_render_image, back);
		}
	}

	pDC->BitBlt(scroll_pos.x,scroll_pos.y,rect.right,rect.bottom,memDC,
			scroll_pos.x,scroll_pos.y,SRCCOPY);
	drawWhiteSpace(pDC);
}

void CFIT_6203_Voronkov_RayView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CFIT_6203_Voronkov_RayView::drawSegment(CDC* pDC, const Segment & segment, bool colorful)
{
	CPoint start, finish;
	Segment s;
	Segment s1 = segment;
	if (s1.start().get(3) < 0 && s1.finish().get(3) < 0){
		return;
	}
	s1.normalizeW();
	if (! clipSegment(s1, &s) ) {
		return;
	}
	start.x = (int)((s.start().x() + 1.0) * view_port.cx / 2.0 + offset + 1.5);
//	start.y = (int)((s.start().y() + 1.0) * view_port.cy / 2.0 + offset + 1.5);
	start.y = (int)(view_port.cy + offset - (s.start().y() + 1.0) * view_port.cy / 2.0 + 1.5);
	finish.x = (int)((s.finish().x() + 1.0) * view_port.cx / 2.0 + offset + 1.5);
//	finish.y = (int)((s.finish().y() + 1.0) * view_port.cy / 2.0 + offset + 1.5);
	finish.y = (int)(view_port.cy + offset - (s.finish().y() + 1.0) * view_port.cy / 2.0 + 1.5);

	CPen pen;
	COLORREF c = segment.color();
	if (c == RGB(0, 0, 0) && colorful)
	{
		double dist = 0.5 *(s.start().z() + s.finish().z());
		c = colorByDistance(dist);
	}
	int w = segment.width();
	pen.CreatePen(PS_SOLID, w, c);
	CPen * prev_pen = pDC->SelectObject(&pen);
	pDC->MoveTo(start);
	pDC->LineTo(finish);
	pDC->LineTo(start);
	pDC->SelectObject(prev_pen);
}
void CFIT_6203_Voronkov_RayView::drawArena(CDC* pDC, const WireFrame & arena, bool colorful)
{
	const CList<Segment> & list = arena.content();
	POSITION pos = list.GetHeadPosition();
	Segment seg;
//	CString str;
	while (pos)
	{
		seg = list.GetNext(pos);
		drawSegment(pDC, seg, colorful);
		//str.AppendFormat("(%.4lf, %.4lf -> %.4lf, %.4lf)\n", seg.start().x(), seg.start().y(), 
		//	seg.finish().x(), seg.finish().y());
	}
//	AfxMessageBox(str);
}
void CFIT_6203_Voronkov_RayView::drawBorder(CDC* pDC)
{
	pDC->MoveTo(offset, offset);
	pDC->LineTo(raster_size.cx - offset, offset);
	pDC->LineTo(raster_size.cx - offset, raster_size.cy - offset);
	pDC->LineTo(offset, raster_size.cy - offset);
	pDC->LineTo(offset, offset);
}
void CFIT_6203_Voronkov_RayView::drawWhiteSpace(CDC* pDC)
{
	CPoint scroll_pos = GetScrollPosition();
	CSize ml_size = raster_size;
	CRect client_rect;
	GetClientRect(&client_rect);
	int x_off = client_rect.right + scroll_pos.x - ml_size.cx;

	int y_off = client_rect.bottom + scroll_pos.y - ml_size.cy;

	CRect target;

	target.left = client_rect.right - x_off;
	target.right = client_rect.right;
	target.top = client_rect.top;
	target.bottom = client_rect.bottom;
	if (x_off > 0) {
		pDC->FillSolidRect(&target, pDC->GetBkColor());
	}

	target.left = client_rect.left;
	target.top = client_rect.bottom - y_off;
	if (y_off > 0) {
		pDC->FillSolidRect(&target, pDC->GetBkColor());
	}
}
void CFIT_6203_Voronkov_RayView::drawRenderedImage(CDC* pDC, const Image & img, COLORREF back)
{
	CSize size = img.size();
	for (int i=0; i<size.cy; i++)
	{
		for (int j=0; j<size.cx; j++)
		{
			if (img.getReal(j, i).isBackground())
			{
				pDC->SetPixelV(offset + j, offset + i, back);
			}
			else
			{
				pDC->SetPixelV(offset + j, offset + i, img.rgb(j, i));
			}
		}
	}
}
bool CFIT_6203_Voronkov_RayView::clipSegment(const Segment & src, Segment * dest)
{
	Segment res = src;
	double sx = res.start().x();
	double fx = res.finish().x();
	Point ptmp;
	Point vec;
	if (sx < -1 && fx < -1) return false;
	// clip right
	if ((sx + 1)*(fx + 1) < 0)
	{
		if (sx > -1)
		{
			vec = Point(res.finish().x() - res.start().x(), res.finish().y() - res.start().y(),
				res.finish().z() - res.start().z());
			double tau = (sx + 1) / (sx - fx);
			ptmp.setX(res.start().x() + tau * vec.x());
			ptmp.setY(res.start().y() + tau * vec.y());
			ptmp.setZ(res.start().z() + tau * vec.z());
			res.setFinish(ptmp);
		}
		else // fx > -1
		{
			vec = Point(- res.finish().x() + res.start().x(), - res.finish().y() + res.start().y(),
				- res.finish().z() + res.start().z());
			double tau = (fx + 1) / (fx - sx);
			ptmp.setX(res.finish().x() + tau * vec.x());
			ptmp.setY(res.finish().y() + tau * vec.y());
			ptmp.setZ(res.finish().z() + tau * vec.z());
			res.setStart(ptmp);
		}
	}
	sx = res.start().x();
	fx = res.finish().x();
	// clip left
	if (sx > 1 && fx > 1) return false;
	if ((sx - 1)*(fx - 1) < 0)
	{
		if (sx < 1)
		{
			vec = Point(res.finish().x() - res.start().x(), res.finish().y() - res.start().y(),
				res.finish().z() - res.start().z());
			double tau = (1 - sx) / (fx - sx);
			ptmp.setX(res.start().x() + tau * vec.x());
			ptmp.setY(res.start().y() + tau * vec.y());
			ptmp.setZ(res.start().z() + tau * vec.z());
			res.setFinish(ptmp);
		}
		else // fx < 1
		{
			vec = Point(- res.finish().x() + res.start().x(), - res.finish().y() + res.start().y(),
				- res.finish().z() + res.start().z());
			double tau = (1 - fx) / (sx - fx);
			ptmp.setX(res.finish().x() + tau * vec.x());
			ptmp.setY(res.finish().y() + tau * vec.y());
			ptmp.setZ(res.finish().z() + tau * vec.z());
			res.setStart(ptmp);
		}
	}
	double sy = res.start().y();
	double fy = res.finish().y();
	// clip top
	if (sy < -1 && fy < -1) return false;
	if ((sy + 1)*(fy + 1) < 0)
	{
		if (sy > -1)
		{
			vec = Point(res.finish().x() - res.start().x(), res.finish().y() - res.start().y(),
				res.finish().z() - res.start().z());
			double tau = (sy + 1) / (sy - fy);
			ptmp.setX(res.start().x() + tau * vec.x());
			ptmp.setY(res.start().y() + tau * vec.y());
			ptmp.setZ(res.start().z() + tau * vec.z());
			res.setFinish(ptmp);
		}
		else // fy > -1
		{
			vec = Point(- res.finish().x() + res.start().x(), - res.finish().y() + res.start().y(),
				- res.finish().z() + res.start().z());
			double tau = (fy + 1) / (fy - sy);
			ptmp.setX(res.finish().x() + tau * vec.x());
			ptmp.setY(res.finish().y() + tau * vec.y());
			ptmp.setZ(res.finish().z() + tau * vec.z());
			res.setStart(ptmp);
		}
	}
	sy = res.start().y();
	fy = res.finish().y();
	if (sy > 1 && fy > 1) return false;
	// clip bottom
	if ((sy - 1)*(fy - 1) < 0)
	{
		if (sy < 1)
		{
			vec = Point(res.finish().x() - res.start().x(), res.finish().y() - res.start().y(),
				res.finish().z() - res.start().z());
			double tau = (1 - sy) / (fy - sy);
			ptmp.setX(res.start().x() + tau * vec.x());
			ptmp.setY(res.start().y() + tau * vec.y());
			ptmp.setZ(res.start().z() + tau * vec.z());
			res.setFinish(ptmp);
		}
		else // fy < 1
		{
			vec = Point(- res.finish().x() + res.start().x(), - res.finish().y() + res.start().y(),
				- res.finish().z() + res.start().z());
			double tau = (1 - fy) / (sy - fy);
			ptmp.setX(res.finish().x() + tau * vec.x());
			ptmp.setY(res.finish().y() + tau * vec.y());
			ptmp.setZ(res.finish().z() + tau * vec.z());
			res.setStart(ptmp);
		}
	}
	double sz = res.start().z();
	double fz = res.finish().z();
	if (sz < 0 && fz < 0) return false;
	if ( sz * fz < 0)
	{
		if (sz > 0)
		{
			vec = Point(res.finish().x() - res.start().x(), res.finish().y() - res.start().y(),
				res.finish().z() - res.start().z());
			double tau = sz  / (sz - fz);
			ptmp.setX(res.start().x() + tau * vec.x());
			ptmp.setY(res.start().y() + tau * vec.y());
			ptmp.setZ(res.start().z() + tau * vec.z());
			res.setFinish(ptmp);
		}
		else // fz > 0
		{
			vec = Point(- res.finish().x() + res.start().x(), - res.finish().y() + res.start().y(),
				- res.finish().z() + res.start().z());
			double tau = fz / (fz - sz);
			ptmp.setX(res.finish().x() + tau * vec.x());
			ptmp.setY(res.finish().y() + tau * vec.y());
			ptmp.setZ(res.finish().z() + tau * vec.z());
			res.setStart(ptmp);
		}
	}
	sz = res.start().z();
	fz = res.finish().z();
	if (sz > 1 && fz > 1) return false;
	if ((sz - 1)*(fz - 1) < 0)
	{
		if (sz < 1)
		{
			vec = Point(res.finish().x() - res.start().x(), res.finish().y() - res.start().y(),
				res.finish().z() - res.start().z());
			double tau = (1 - sz) / (fz - sz);
			ptmp.setX(res.start().x() + tau * vec.x());
			ptmp.setY(res.start().y() + tau * vec.y());
			ptmp.setZ(res.start().z() + tau * vec.z());
			res.setFinish(ptmp);
		}
		else // fz < 1
		{
			vec = Point(- res.finish().x() + res.start().x(), - res.finish().y() + res.start().y(),
				- res.finish().z() + res.start().z());
			double tau = (1 - fz) / (sz - fz);
			ptmp.setX(res.finish().x() + tau * vec.x());
			ptmp.setY(res.finish().y() + tau * vec.y());
			ptmp.setZ(res.finish().z() + tau * vec.z());
			res.setStart(ptmp);
		}
	}
	*dest = res;
	return true;
}
COLORREF CFIT_6203_Voronkov_RayView::colorByDistance(double z)
{
	int r;
	int g;
	int b;
	ASSERT(z >= 0 && z <=1);
	r = (z >= 0.5)?((int)(510 * (z - 0.5) +0.5)):0;
	g = (z <= 0.5)?((int)(510 * (0.5 - z) +0.5)):0;
	b = 255 - (int)(510 * abs(z - 0.5) + 0.5);
	r = (r < 0)?0:r;
	g = (g < 0)?0:g;
	b = (b < 0)?0:b;
	r = (r > 255)?255:r;
	g = (g > 255)?255:g;
	b = (b > 255)?255:b;
	return RGB(r, g, b);
}

// CFIT_6203_Voronkov_RayView diagnostics

#ifdef _DEBUG
void CFIT_6203_Voronkov_RayView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CFIT_6203_Voronkov_RayView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CFIT_6203_Voronkov_RayDoc* CFIT_6203_Voronkov_RayView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFIT_6203_Voronkov_RayDoc)));
	return (CFIT_6203_Voronkov_RayDoc*)m_pDocument;
}
#endif //_DEBUG


// CFIT_6203_Voronkov_RayView message handlers

void CFIT_6203_Voronkov_RayView::OnMouseMove(UINT nFlags, CPoint point)
{
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	if (!pDoc->params.flag_doc_opeded) return;
	if (pDoc->params.flag_render_ready) return;
	if((nFlags & MK_LBUTTON) != 0){
		if((flag_l_button_down)){
			//TODO
			CPoint current_point = point + GetScrollPosition();
			CPoint dPos = current_point - prev_mouse_pos;
			prev_mouse_pos = current_point;
//			prev_d_fi = dPos.y * pDoc->params.r; // 
			prev_d_fi = - dPos.y * pDoc->params.r;
			prev_d_tetta = - dPos.x * pDoc->params.r; // magic minus
//			prev_d_tetta = dPos.x * pDoc->params.r;
			pDoc->m_rotate_x.createRotateX(prev_d_fi);
			pDoc->m_rotate_y.createRotateY(prev_d_tetta);
			
//			AfxMessageBox(pDoc->m_rotate_y.show());
			pDoc->m_pre_final = pDoc->m_trans_forward * pDoc->m_rotate_y *
					pDoc->m_rotate_x * pDoc->m_trans_backwards * pDoc->m_pre_final;
			pDoc->m_final = pDoc->m_proj * pDoc->m_pre_final;
			pDoc->m_wire_frame_finish = pDoc->m_final * pDoc->m_wire_frame_start;
//			AfxMessageBox(pDoc->a_scene_finish.show());
			
			// 
			if (pDoc->params.flag_render_ready)
			{
				pDoc->prepareRendering();
				pDoc->render();
			}
			pDoc->UpdateAllViews(NULL);
		}
	}else{
		flag_l_button_down = false;
		CPoint current_point = point + GetScrollPosition();
		CPoint dPos = current_point - prev_mouse_pos;
	}
}

void CFIT_6203_Voronkov_RayView::OnLButtonDown(UINT /*nFlags*/, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->params.flag_render_ready) return;
	prev_mouse_pos = point + GetScrollPosition();
	flag_l_button_down = true;
}

void CFIT_6203_Voronkov_RayView::OnLButtonUp(UINT /*nFlags*/, CPoint /*point*/)
{
	// TODO: Add your message handler code here and/or call default
	
	flag_l_button_down = false;
}

void CFIT_6203_Voronkov_RayView::OnButtonRenderLoad()
{
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CFileDialog fDialog(TRUE);
	OPENFILENAME& ofn = fDialog.GetOFN();
	ofn.lpstrFilter = "Text Files (*.txt)\0*.*\0";
	ofn.lpstrTitle = "Load render settings";
	ofn.lpstrInitialDir = "./";

	if (fDialog.DoModal() == IDOK)
	{
		CString in = fDialog.GetFileName();
		CFile m_in(in, CFile::modeRead);
		CArchive ar(&m_in, CArchive::load);
		RenderSet set;

		Io::loadRenderSet(&ar, &set);
		pDoc->prepareWireFrame(set);
		pDoc->UpdateAllViews(NULL);
	}
}

void CFIT_6203_Voronkov_RayView::OnButtonRenderStore()
{
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CFileDialog fDialog(FALSE);
	OPENFILENAME& ofn = fDialog.GetOFN();
	ofn.lpstrFilter = "Text Files (*.txt)\0*.*\0";
	ofn.lpstrTitle = "Save render settings";
	ofn.lpstrInitialDir = "./";
	if (fDialog.DoModal() == IDOK)
	{
		CString in = fDialog.GetFileName();
		CFile m_in(in, CFile::modeWrite|CFile::modeCreate);
		CArchive ar(&m_in, CArchive::store);

		Matrix rotate = pDoc->m_trans_backwards * pDoc->m_pre_final * pDoc->m_trans_from_center;
		Camera cam(pDoc->params.distance, rotate);
		pDoc->render_set.setCamera(cam);
		Io::saveRenderSet(&ar, pDoc->render_set);
	}
}

void CFIT_6203_Voronkov_RayView::OnButtonInit()
{
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!pDoc->params.flag_doc_opeded) return;
	if (pDoc->params.flag_render_ready) return;
	pDoc->prepareWireFrame();
	//pDoc->m_pre_final = pDoc->m_trans_forward * pDoc->m_trans_to_center;
	//pDoc->m_final = pDoc->m_proj * pDoc->m_pre_final;
	//pDoc->m_wire_frame_finish = pDoc->m_final * pDoc->m_wire_frame_start;
	pDoc->UpdateAllViews(NULL);
}

void CFIT_6203_Voronkov_RayView::OnButtonOptions()
{
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (!pDoc->params.flag_doc_opeded) return;

	CFIT_6203_Voronkov_Ray_DialogOptions dlg;
	dlg.m_var_width = pDoc->params.getWidth();
	dlg.m_var_height = pDoc->params.getHeight();
	dlg.m_var_gamma = pDoc->render_set.gamma();
	dlg.m_var_depth = pDoc->render_set.treeDepth();
	dlg.m_var_quality = pDoc->render_set.quality();
	dlg.m_var_background = pDoc->render_set.background();
	if (dlg.DoModal() == IDOK)
	{
		bool flag_render_again = false;
		if (pDoc->params.getWidth() != dlg.m_var_width)flag_render_again = true;
		if (pDoc->params.getHeight() != dlg.m_var_height)flag_render_again = true;
		pDoc->params.setWidth(dlg.m_var_width);
		pDoc->params.setHeight(dlg.m_var_height);
		pDoc->render_set.setScrollSize(dlg.m_var_width, dlg.m_var_height);

		pDoc->render_set.setGamma(dlg.m_var_gamma);
		pDoc->m_render_image.setGamma(dlg.m_var_gamma);
		if (pDoc->render_set.treeDepth() != dlg.m_var_depth)flag_render_again = true;
		pDoc->render_set.setTreeDepth(dlg.m_var_depth);
		
		if (pDoc->render_set.quality() != dlg.m_var_quality)flag_render_again = true;
		pDoc->render_set.setQuality(dlg.m_var_quality);
		pDoc->render_set.setBackground(dlg.m_var_background);

		pDoc->params.s_h = (pDoc->params.s_w * dlg.m_var_height) / dlg.m_var_width;
		pDoc->m_proj.createMproj(pDoc->params.s_w, pDoc->params.s_h, 
				pDoc->params.z_near, pDoc->params.z_far);
		pDoc->m_final = pDoc->m_proj * pDoc->m_pre_final;
		pDoc->m_wire_frame_finish = pDoc->m_final * pDoc->m_wire_frame_start;
		pDoc->params.flag_raster_modified = true;
		if (flag_render_again && pDoc->params.flag_render_ready) {
			pDoc->prepareRendering();
			m_time_id = SetTimer(1, 100, 0);
		}
		pDoc->UpdateAllViews(NULL);
	}

}

void CFIT_6203_Voronkov_RayView::OnRButtonDown(UINT nFlags, CPoint point)
{
#ifdef _DEBUG
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Matrix rotate = pDoc->m_trans_backwards * pDoc->m_pre_final * pDoc->m_trans_from_center;
	Matrix back_rotate = rotate.transpose();
	Matrix e = rotate * back_rotate;

	AfxMessageBox( rotate.show() + back_rotate.show() + e.show() );
#endif
	CScrollView::OnRButtonDown(nFlags, point);
}

void CFIT_6203_Voronkov_RayView::OnButtonRender()
{
	// TODO: Add your command handler code here
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	pDoc->prepareRendering();
	m_time_id = SetTimer(1, 100, 0);
	
	pDoc->UpdateAllViews(NULL);
}

void CFIT_6203_Voronkov_RayView::OnButtonView()
{
	// TODO: Add your command handler code here
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->params.flag_render_in_process = false;
	pDoc->params.flag_render_ready = false;
	pDoc->UpdateAllViews(NULL);
}

void CFIT_6203_Voronkov_RayView::OnButtonSaveBmp()
{
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CFileDialog fDialog(FALSE);
	OPENFILENAME& ofn = fDialog.GetOFN();
//	ofn.lpstrFilter = "Bmp-Files (*.bmp)\0*.*\0";
	ofn.lpstrFilter = "Bmp-Files\0*.bmp\0All Files\0*.*\0\0";
	ofn.lpstrTitle = "Save bmp";
	ofn.lpstrInitialDir = "./";
	if (fDialog.DoModal() == IDOK)
	{
		CString in = fDialog.GetFileName();
		CFile m_in(in, CFile::modeWrite|CFile::modeCreate);
		CArchive ar(&m_in, CArchive::store);

		Io::saveBmp(&ar, memDC, pDoc->render_set.scrollSize(), offset);
	}
}

BOOL CFIT_6203_Voronkov_RayView::OnEraseBkgnd(CDC* /*pDC*/)
{
	// TODO: Add your message handler code here and/or call default

	return FALSE;
}

void CFIT_6203_Voronkov_RayView::OnButtonMoveFar()
{
	// TODO: Add your command handler code here
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (!pDoc->params.flag_doc_opeded) return;
	if (pDoc->params.flag_render_ready) return;
	pDoc->moveZoom(-1);
}

void CFIT_6203_Voronkov_RayView::OnButtonMoveNear()
{
	// TODO: Add your command handler code here
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (!pDoc->params.flag_doc_opeded) return;
	if (pDoc->params.flag_render_ready) return;
	pDoc->moveZoom(1);
}

void CFIT_6203_Voronkov_RayView::OnUpdateButtonInit(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->params.flag_doc_opeded && !pDoc->params.flag_render_ready){
		pCmdUI->Enable(TRUE);
	}
	else{
		pCmdUI->Enable(FALSE);
	}
}

void CFIT_6203_Voronkov_RayView::OnUpdateButtonMoveFar(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->params.flag_doc_opeded && !pDoc->params.flag_render_ready){
		pCmdUI->Enable(TRUE);
	}
	else{
		pCmdUI->Enable(FALSE);
	}
}

void CFIT_6203_Voronkov_RayView::OnUpdateButtonMoveNear(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->params.flag_doc_opeded && !pDoc->params.flag_render_ready){
		pCmdUI->Enable(TRUE);
	}
	else{
		pCmdUI->Enable(FALSE);
	}
}

void CFIT_6203_Voronkov_RayView::OnUpdateButtonOptions(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->params.flag_doc_opeded){
		pCmdUI->Enable(TRUE);
	}
	else{
		pCmdUI->Enable(FALSE);
	}
}

void CFIT_6203_Voronkov_RayView::OnUpdateButtonRender(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->params.flag_doc_opeded){
		pCmdUI->Enable(TRUE);
		if (pDoc->params.flag_render_ready || pDoc->params.flag_render_in_process){
			pCmdUI->SetCheck(TRUE);
		}
		else{
			pCmdUI->SetCheck(FALSE);
		}
	}
	else{
		pCmdUI->Enable(FALSE);
	}
	

}

void CFIT_6203_Voronkov_RayView::OnUpdateButtonRenderLoad(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->params.flag_doc_opeded && !pDoc->params.flag_render_ready){
		pCmdUI->Enable(TRUE);
	}
	else{
		pCmdUI->Enable(FALSE);
	}
}

void CFIT_6203_Voronkov_RayView::OnUpdateButtonRenderStore(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->params.flag_doc_opeded){
		pCmdUI->Enable(TRUE);
	}
	else{
		pCmdUI->Enable(FALSE);
	}
}

void CFIT_6203_Voronkov_RayView::OnUpdateButtonSaveBmp(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->params.flag_doc_opeded){
		pCmdUI->Enable(TRUE);
	}
	else{
		pCmdUI->Enable(FALSE);
	}
}

void CFIT_6203_Voronkov_RayView::OnUpdateButtonView(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->params.flag_doc_opeded){
		pCmdUI->Enable(TRUE);
		if (!pDoc->params.flag_render_ready && !pDoc->params.flag_render_in_process){
			pCmdUI->SetCheck(TRUE);
		}
		else{
			pCmdUI->SetCheck(FALSE);
		}
	}
	else{
		pCmdUI->Enable(FALSE);
	}
}

void CFIT_6203_Voronkov_RayView::OnTimer(UINT_PTR /*nIDEvent*/)
{
	// TODO: Add your message handler code here and/or call default
	CFIT_6203_Voronkov_RayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	KillTimer(m_time_id);
	pDoc->render();
	pDoc->UpdateAllViews(NULL);
	//CScrollView::OnTimer(nIDEvent);
}
