// FIT_6203_Voronkov_Ray_DialogOptions.cpp : implementation file
//

#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray.h"
#include "FIT_6203_Voronkov_Ray_DialogOptions.h"


// CFIT_6203_Voronkov_Ray_DialogOptions dialog

IMPLEMENT_DYNAMIC(CFIT_6203_Voronkov_Ray_DialogOptions, CDialog)

CFIT_6203_Voronkov_Ray_DialogOptions::CFIT_6203_Voronkov_Ray_DialogOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CFIT_6203_Voronkov_Ray_DialogOptions::IDD, pParent)
	, m_var_width(0)
	, m_var_height(0)
	, m_var_gamma(0)
	, m_var_depth(0)
	, m_var_quality(0)
{

}

CFIT_6203_Voronkov_Ray_DialogOptions::~CFIT_6203_Voronkov_Ray_DialogOptions()
{
}

void CFIT_6203_Voronkov_Ray_DialogOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_var_width);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_var_height);
	DDX_Text(pDX, IDC_EDIT_GAMMA, m_var_gamma);
	DDX_Text(pDX, IDC_EDIT_DEPTH, m_var_depth);
	DDX_Radio(pDX, IDC_RADIO1, m_var_quality);
}


BEGIN_MESSAGE_MAP(CFIT_6203_Voronkov_Ray_DialogOptions, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_BACKGROUND, &CFIT_6203_Voronkov_Ray_DialogOptions::OnBnClickedButtonSelectBackground)
END_MESSAGE_MAP()


// CFIT_6203_Voronkov_Ray_DialogOptions message handlers

void CFIT_6203_Voronkov_Ray_DialogOptions::OnBnClickedButtonSelectBackground()
{
	CColorDialog color_d(m_var_background);
	if (color_d.DoModal() == IDOK)
	{
		m_var_background = color_d.GetColor();
	}
}
