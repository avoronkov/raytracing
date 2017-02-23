// FIT_6203_Voronkov_RayView.h : interface of the CFIT_6203_Voronkov_RayView class
//


#pragma once


class CFIT_6203_Voronkov_RayView : public CScrollView
{
protected: // create from serialization only
	CFIT_6203_Voronkov_RayView();
	DECLARE_DYNCREATE(CFIT_6203_Voronkov_RayView)

// Attributes
public:
	CFIT_6203_Voronkov_RayDoc* GetDocument() const;
	CPoint prev_mouse_pos;
	bool flag_l_button_down;
	double prev_d_fi;
	double prev_d_tetta;

	CDC * memDC;
	CSize raster_size;
	int offset;
	CSize view_port;
	CBitmap * memBitmap;

	UINT m_time_id;

// Operations
public:
	void drawSegment(CDC* pDC, const Segment & segment, bool colorful = false);
	void drawArena(CDC* pDC, const WireFrame & arena, bool colorful = false);
	void drawBorder(CDC* pDC);
	void drawWhiteSpace(CDC* pDC);
	void drawRenderedImage(CDC* pDC, const Image & img, COLORREF back);
 	bool clipSegment(const Segment & src, Segment * dest);
	COLORREF colorByDistance(double z);
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CFIT_6203_Voronkov_RayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnButtonRenderLoad();
	afx_msg void OnButtonRenderStore();
	afx_msg void OnButtonInit();
	afx_msg void OnButtonOptions();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButtonRender();
	afx_msg void OnButtonView();
	afx_msg void OnButtonSaveBmp();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnButtonMoveFar();
	afx_msg void OnButtonMoveNear();
	afx_msg void OnUpdateButtonInit(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonMoveFar(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonMoveNear(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonOptions(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonRender(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonRenderLoad(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonRenderStore(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonSaveBmp(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonView(CCmdUI *pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // debug version in FIT_6203_Voronkov_RayView.cpp
inline CFIT_6203_Voronkov_RayDoc* CFIT_6203_Voronkov_RayView::GetDocument() const
   { return reinterpret_cast<CFIT_6203_Voronkov_RayDoc*>(m_pDocument); }
#endif

