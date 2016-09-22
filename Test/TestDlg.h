// TestDlg.h : header file
//

#if !defined(AFX_TESTDLG_H__03DD1C71_3518_4859_AE76_30DA9689426D__INCLUDED_)
#define AFX_TESTDLG_H__03DD1C71_3518_4859_AE76_30DA9689426D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "googleearth.h"
#include "LAYERSCONTROL.h"
#include "Manyou.h"
#include "m_cbmy.h"
#include "afxcmn.h"

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

class CTestDlg : public CDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);	// standard constructor
	IApplicationGE m_geApplication;
	IPointOnTerrainGE PointOnTerrain;
	ICameraInfoGE m_camera;

	IFeatureGE* m_geFeature;
	IFeatureCollectionGE m_geCollect;
	int countSum;
	int timeControl;
	BOOL m_active;
	//CTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TEST_DIALOG };
	CTreeCtrl m_TreeCtrl;
	HTREEITEM m_TreeRoot;
	void ShowFile(CString str_Dir, HTREEITEM tree_Root);
	HTREEITEM GetSelectTree();
	DWORD GetFilePathByTreeItem();
	HTREEITEM m_CurTree;//用以记录当前的节点
    HTREEITEM m_CurTreeParent;//用以当前节点的父节点
    CString m_CurTreeDir;//用以记录当前节点的路径
	BOOL ShowImage(CDC* pDC,CString strPath, int x, int y);
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnEditchangeCombo1();
	afx_msg void OnChangeEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnEnChangeEdit11();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnEnChangeEdit13();
	afx_msg void OnEnChangeEdit12();
	afx_msg void OnStnClickedCancel2();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__03DD1C71_3518_4859_AE76_30DA9689426D__INCLUDED_)
