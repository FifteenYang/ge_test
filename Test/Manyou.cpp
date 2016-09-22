// Manyou.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "Manyou.h"
#include "m_cbmy.h"


// CManyou dialog

IMPLEMENT_DYNAMIC(CManyou, CDialog)

CManyou::CManyou(CWnd* pParent /*=NULL*/)
	: CDialog(CManyou::IDD, pParent)
{

}

CManyou::~CManyou()
{
}

void CManyou::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, cbox2);
	DDX_Text(pDX, IDC_COMBO2, place);
	if (strcmp(place, ""))
	return;
	DDX_Text(pDX, IDC_COMBO7, place);
	if (strcmp(place, ""))
	return;
	DDX_Text(pDX, IDC_COMBO3, place);
	if (strcmp(place, ""))
	return;
	DDX_Text(pDX, IDC_COMBO4, place);
	if (strcmp(place, ""))
	return;
	DDX_Text(pDX, IDC_COMBO8, place);
	if (strcmp(place, ""))
	return;
	if (strcmp(place, ""))
	return;
	DDX_Text(pDX, IDC_COMBO9, place);
	if (strcmp(place, ""))
	return;
	DDX_Text(pDX, IDC_COMBO5, place);
	if (strcmp(place, ""))
	return;
}


BEGIN_MESSAGE_MAP(CManyou, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CManyou::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO7, &CManyou::OnCbnSelchangeCombo7)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CManyou::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CManyou::OnCbnSelchangeCombo4)
	ON_CBN_SELCHANGE(IDC_COMBO8, &CManyou::OnCbnSelchangeCombo8)
	ON_CBN_SELCHANGE(IDC_COMBO9, &CManyou::OnCbnSelchangeCombo9)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CManyou::OnCbnSelchangeCombo5)
END_MESSAGE_MAP()


// CManyou message handlers


void CManyou::OnCbnSelchangeCombo2()
{
	// TODO: Add your control notification handler code here
	//cbox2.AddString(_T("one"));

	CString csValue;
    int index = cbox2.GetCurSel();
	cbox2.GetLBText(index,csValue);//选项的值保存到csValues中
	//cbox2.SetCurSel(2); //不过我们不太可能去记住每个选项的索引,所以先查找下它的索引是多少
//int index = cbox2.FindStringExact(0,_T("北京")); //0表示从索引为0的选项开始查找.如果找到
	//CString text;
	
    //GetWindowText(IDC_COMBO2,text);
	//MessageBox(csValue,"打印",MB_OKCANCEL);

	//IntPtr hwnd;


	//HWND hwndCombo1 = GetDlgItem(hwnd,IDC_COMBO2);
//CString str;
//ComboBox_GetLBText(hwndCombo1,2, str);
//ComboBox_GetLBText不返回值,实际是通过str储存并传递字符串.
//MessageBox(hwnd,str,TEXT("标题"),MB_OK);

}

void CManyou::OnCbnSelchangeCombo7()
{
	// TODO: Add your control notification handler code here
}

void CManyou::OnCbnSelchangeCombo3()
{
	// TODO: Add your control notification handler code here
}

void CManyou::OnCbnSelchangeCombo4()
{
	// TODO: Add your control notification handler code here
}

void CManyou::OnCbnSelchangeCombo8()
{
	// TODO: Add your control notification handler code here
}

void CManyou::OnCbnSelchangeCombo9()
{
	// TODO: Add your control notification handler code here
}

void CManyou::OnCbnSelchangeCombo5()
{
	// TODO: Add your control notification handler code here
}
