// FIT_6203_Voronkov_Ray.h : main header file for the FIT_6203_Voronkov_Ray application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CFIT_6203_Voronkov_RayApp:
// See FIT_6203_Voronkov_Ray.cpp for the implementation of this class
//

class CFIT_6203_Voronkov_RayApp : public CWinApp
{
public:
	CFIT_6203_Voronkov_RayApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFIT_6203_Voronkov_RayApp theApp;