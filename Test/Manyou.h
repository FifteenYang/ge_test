#pragma once
#include "afxwin.h"


// CManyou dialog

class CManyou : public CDialog
{
	DECLARE_DYNAMIC(CManyou)

public:
	CManyou(CWnd* pParent = NULL);   // standard constructor
	virtual ~CManyou();

// Dialog Data
	enum { IDD = IDD_MANYOU };
	CString place;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo7();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnCbnSelchangeCombo8();
	CComboBox cbox2;
	afx_msg void OnCbnSelchangeCombo9();
	afx_msg void OnCbnSelchangeCombo5();
};
