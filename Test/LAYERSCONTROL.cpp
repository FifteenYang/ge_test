// LAYERSCONTROL.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "LAYERSCONTROL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLAYERSCONTROL dialog


CLAYERSCONTROL::CLAYERSCONTROL(CWnd* pParent /*=NULL*/)
	: CDialog(CLAYERSCONTROL::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLAYERSCONTROL)
	m_terrain = FALSE;
	m_web = FALSE;
	m_awareness = FALSE;
	m_roads = FALSE;
	m_borders = FALSE;
	m_weather = FALSE;
	m_3DBuild = FALSE;
	m_pictures = FALSE;
	m_street = FALSE;
	m_ocean = FALSE;
	//}}AFX_DATA_INIT
}


void CLAYERSCONTROL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLAYERSCONTROL)
	DDX_Check(pDX, IDC_CHECK1, m_terrain);
	DDX_Check(pDX, IDC_CHECK2, m_web);
	DDX_Check(pDX, IDC_CHECK3, m_awareness);
	DDX_Check(pDX, IDC_CHECK4, m_roads);
	DDX_Check(pDX, IDC_CHECK5, m_borders);
	DDX_Check(pDX, IDC_CHECK6, m_weather);
	DDX_Check(pDX, IDC_CHECK7, m_3DBuild);
	DDX_Check(pDX, IDC_CHECK8, m_pictures);
	DDX_Check(pDX, IDC_CHECK9, m_street);
	DDX_Check(pDX, IDC_CHECK10, m_ocean);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLAYERSCONTROL, CDialog)
	//{{AFX_MSG_MAP(CLAYERSCONTROL)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK1, &CLAYERSCONTROL::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK7, &CLAYERSCONTROL::OnBnClickedCheck7)
	ON_BN_CLICKED(IDOK, &CLAYERSCONTROL::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLAYERSCONTROL::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK2, &CLAYERSCONTROL::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CLAYERSCONTROL::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK6, &CLAYERSCONTROL::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK10, &CLAYERSCONTROL::OnBnClickedCheck10)
	ON_BN_CLICKED(IDC_CHECK9, &CLAYERSCONTROL::OnBnClickedCheck9)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLAYERSCONTROL message handlers

void CLAYERSCONTROL::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
}

void CLAYERSCONTROL::OnBnClickedCheck7()
{
	// TODO: Add your control notification handler code here
}

void CLAYERSCONTROL::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CLAYERSCONTROL::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CLAYERSCONTROL::OnBnClickedCheck2()
{
	// TODO: Add your control notification handler code here
}

void CLAYERSCONTROL::OnBnClickedCheck3()
{
	// TODO: Add your control notification handler code here
}

void CLAYERSCONTROL::OnBnClickedCheck6()
{
	// TODO: Add your control notification handler code here
}

void CLAYERSCONTROL::OnBnClickedCheck10()
{
	// TODO: Add your control notification handler code here
}

void CLAYERSCONTROL::OnBnClickedCheck9()
{
	// TODO: Add your control notification handler code here
}
