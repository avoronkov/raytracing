#pragma once


// CFIT_6203_Voronkov_Ray_DialogOptions dialog

class CFIT_6203_Voronkov_Ray_DialogOptions : public CDialog
{
	DECLARE_DYNAMIC(CFIT_6203_Voronkov_Ray_DialogOptions)

public:
	CFIT_6203_Voronkov_Ray_DialogOptions(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFIT_6203_Voronkov_Ray_DialogOptions();

// Dialog Data
	enum { IDD = IDD_DIALOG_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_var_width;
	int m_var_height;
	double m_var_gamma;
	int m_var_depth;
	int m_var_quality;
	COLORREF m_var_background;
	afx_msg void OnBnClickedButtonSelectBackground();
};
