#if !defined(AFX_LAYERSCONTROL_H__B7FEFB03_40A8_4FF4_8180_1F3396E48EB2__INCLUDED_)
#define AFX_LAYERSCONTROL_H__B7FEFB03_40A8_4FF4_8180_1F3396E48EB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LAYERSCONTROL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLAYERSCONTROL dialog

class CLAYERSCONTROL : public CDialog
{
// Construction
public:
	CLAYERSCONTROL(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLAYERSCONTROL)
	enum { IDD = IDD_LAYERSCONTROL };
	BOOL	m_terrain;
	BOOL	m_web;
	BOOL	m_awareness;
	BOOL	m_roads;
	BOOL	m_borders;
	BOOL	m_weather;
	BOOL	m_3DBuild;
	BOOL	m_pictures;
	BOOL	m_street;
	BOOL	m_ocean;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLAYERSCONTROL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLAYERSCONTROL)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck10();
	afx_msg void OnBnClickedCheck9();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYERSCONTROL_H__B7FEFB03_40A8_4FF4_8180_1F3396E48EB2__INCLUDED_)
