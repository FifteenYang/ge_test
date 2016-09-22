// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include <fstream>
#include <windows.h>
#include <shellapi.h>
#include <math.h>
#include <windef.h>
#include "LAYERSCONTROL.h"
#include "Manyou.h"
#include "m_cbmy.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const CLSID CLSID_ApplicationGE = {0x8097D7E9,0xDB9E,0x4AEF, 
{0x9B,0x28,0x61,0xD8,0x2A,0x1D,0xF7,0x84}};

//open file related
#define MAX_PROC_NUM 4096
static HWND enum_window[MAX_PROC_NUM] = {0};
static DWORD test_pid[MAX_PROC_NUM] = {0};
static int enum_w = 0;
static int needkill_pid[MAX_PROC_NUM] = {0};
static int needkill_num = 0;

//tree related
const DWORD Error_FileOrFolderNotFound = -1;//自定义返回码，表示未找到
const DWORD Return_IsFolder = 1;//自定义返回码，表示树节点对应为文件夹
const DWORD Return_IsFile = 0;//自定义返回码，表示树节点对应为文件

OLE_HANDLE renderhwnd;
HWND GEParentHrender;
//test start #1

//---------------------------------------------------------------------------
#define CRNBUFFERMAXLEN 255
//---------------------------------------------------------------------------
// 枚举当前所有窗口的回调函数
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    //TList *pWndList= (TList *)lParam;
    //pWndList->Add(hWnd);
 
	if (enum_w > lParam)
	{
		enum_window[enum_w] = hWnd;
	}
	enum_w++;
    return TRUE;
}

//---------------------------------------------------------------------------
// 运行一个应用程序，并获取其主窗口，参数越指明详细越准确
// lpAppFile：应用程序文件名
// lpWndClass：主窗口的类名，可留空
// lpWndText：主窗口的标题，可留空

HWND CrnRunAppAndGetMainWnd(LPSTR lpAppFile, LPSTR lpWndClass, LPSTR lpWndText)
{
    PROCESS_INFORMATION pi = { 0 };
    STARTUPINFO si = { 0 };
 
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_MINIMIZE; // 隐藏进程的窗口先 SW_HIDE SW_MINIMIZE SW_HIDE
	int num_tmp = -1;
 
    HWND hRetWnd(NULL);
 
    bool bRet = CreateProcess(NULL, lpAppFile, NULL, NULL, true, 0, 0, NULL, &si, &pi);
    if(bRet)
    {
        // 适当延时，这里暂取1秒，看情况调整
		Sleep(1000);
 
        try
        {
            // 列举所有窗口
            EnumWindows((WNDENUMPROC)EnumWindowsProc, num_tmp);
 
            // 遍历所有顶级窗口，判断该窗口所属进程是否为CreateProcess创建的进程
            HWND hWnd;
            DWORD dwPID;
            int nTextLen;
            char szWndClass[CRNBUFFERMAXLEN], szWndText[CRNBUFFERMAXLEN];
 
            // 63 63 72 75 6E 2E 63 6F 6D
            for(int i=0; i<enum_w; i++)
            {
                hWnd = enum_window[i];
                GetWindowThreadProcessId(hWnd, &dwPID);
				test_pid[i] = dwPID;
                if(dwPID == pi.dwProcessId) // 如果进程相同
                {
                    if(strlen(lpWndClass) > 0) // 判断窗口类名是否与指定的相符
                    {
                        GetClassName(hWnd, szWndClass, nTextLen);
                        if(!strcmp(lpWndClass, szWndClass))
                        {
                            hRetWnd = hWnd;
 
                            break;
                        }
                    }
                    else // 如指定的窗口类名为空就不判断窗口类名了
                    {
                        if(strlen(lpWndText) > 0) // 判断窗口标题是否与指定的相符
                        {
                            nTextLen = GetWindowTextLength(hWnd);
                            if(nTextLen > CRNBUFFERMAXLEN)
                                nTextLen = CRNBUFFERMAXLEN;
                            GetWindowText(hWnd, szWndText, nTextLen);
 
                            if(!strcmp(lpWndText, szWndText))
                            {
                                hRetWnd = hWnd;
                                break;
                            }
                        }
                        else // 如指定的窗口标题为空就不判断窗口标题了
                        {
                            hRetWnd = hWnd;
							needkill_pid[needkill_num++] = dwPID;
							break;
                        }
                    }
                }
            }
            if(hRetWnd == NULL) //　失败鸟，可能没有找到目标窗口
            {
                TerminateProcess(pi.hProcess, 0);
                MessageBox(NULL, "未找到主窗口，程序已关闭.",
                        "ccrun.com", MB_OK | MB_ICONERROR);
            }
        }
        catch(...)
        {
            enum_w = 0;
        }
		enum_w = 0;
    }
 
    return hRetWnd;
}

//test end #1

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	//IApplicationGE m_geApplication;

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Control(pDX, IDC_TREE1, m_TreeCtrl);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//ON_CBN_EDITCHANGE(IDC_COMBO1, OnEditchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT3, &CTestDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT2, &CTestDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT4, &CTestDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CTestDlg::OnEnChangeEdit5)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT8, &CTestDlg::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT7, &CTestDlg::OnEnChangeEdit7)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTestDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CTestDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CTestDlg::OnBnClickedButton8)
	ON_EN_CHANGE(IDC_EDIT11, &CTestDlg::OnEnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT10, &CTestDlg::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT9, &CTestDlg::OnEnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT13, &CTestDlg::OnEnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT12, &CTestDlg::OnEnChangeEdit12)
	ON_STN_CLICKED(IDCANCEL2, &CTestDlg::OnStnClickedCancel2)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CTestDlg::OnTvnSelchangedTree1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
{
	//test start
	if(IDNO == ::MessageBox(NULL, "欢迎进入高中地理教学系统！ \n\n\n是否现在进入系统？","WELCOME", MB_YESNO|MB_DEFBUTTON1))
	{
		EndDialog(0);
		return TRUE;//表示窗口出来
	}
	//test end
	CDialog::OnInitDialog();

	m_geApplication.CreateDispatch(CLSID_ApplicationGE);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
    //m_geApplication.SetCameraParams(34.2667,108.9,0.0,1,40800.0,0.0,45.6,1.0);
	
	// TODO: Add extra initialization here
	//test start
	//获取客户端框架窗口句柄
    long m_hMainWnd = m_geApplication.GetMainHwnd();	 
    //设置窗口的位置和大小
    //::SetWindowPos((HWND)m_hMainWnd, HWND_BOTTOM, 0, 0, STATIC_GOOGLEEARTH_WIDTH+AP_GOOGLEEARTH_LEFTWIDTH+AP_GOOGLEEARTH_RIGHTWIDTH, STATIC_GOOGLEEARTH_HEIGHT+AP_GOOGLEEARTH_TOPHEIGHT+AP_GOOGLEEARTH_BOTTOMHEIGHT, SWP_HIDEWINDOW);
    renderhwnd = m_geApplication.GetRenderHwnd();	
    GEParentHrender = ::GetParent((HWND)renderhwnd);
    ::ShowWindow(GEParentHrender, SW_HIDE);	
    //把HWND和窗口上的一个静态文本控件绑定
    ::SetParent((HWND)renderhwnd, this->GetDlgItem(IDCANCEL2)->GetSafeHwnd());// ppWnd->GetDlgItem(IDC_STATIC7)->GetSafeHwnd());
	 ::MoveWindow((HWND)renderhwnd, 0, 0, 800, 620, false);
	//::SetParent((HWND)m_hMainWnd, this->GetDlgItem(IDCANCEL2)->GetSafeHwnd());// ppWnd->GetDlgItem(IDC_STATIC7)->GetSafeHwnd());
	//test end

	 //tree test
	 /*
	 HTREEITEM hTreeItemParent=NULL;
     HTREEITEM hTreeItemChild=NULL;
     CString strParentData=L"";
     CString strChildData=L"";
     for (int i=1;i<5;i++)
     {
         strParentData.Format("%d-Parent", i);
         hTreeItemParent=m_TreeCtrl.InsertItem(strParentData);
         m_TreeCtrl.SetItemData(hTreeItemParent,i);
 
         strChildData.Format("%d-Child", i);
         hTreeItemChild=m_TreeCtrl.InsertItem(strChildData,hTreeItemParent);
         m_TreeCtrl.SetItemData(hTreeItemChild,i*100);
     }*/
	 //tree end
	m_TreeRoot = m_TreeCtrl.InsertItem("课程章节");//插入根节点
	ShowFile(L"C:\\vc6\\run\\run", m_TreeRoot);//以E:\\test为根目录进行遍历
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDlg::OnButton1() 
{
CString strFileName;

static char BASED_CODE szFilter[] = "jpg Files (*.jpg)|All Files (*.*)|*.*||";
CFileDialog dlgFile(FALSE, "jpg", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);

if (dlgFile.DoModal() == IDOK)
{
     CWaitCursor wait;
     strFileName = dlgFile.GetPathName();
     m_geApplication.SaveScreenShot(strFileName, 10000);
}
	
}



void CTestDlg::OnEditchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	
}

void CTestDlg::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
void CTestDlg::OnButton2() 
{
	int i,j,k,n,num, total_times, current_times;//k,n为横纵向采样点个数
	double longitude,latitude,altitude,px,py;
	char cholon1[10],cholon2[10], cholon3[10], cholon4[10];
	char file_path[128];//{"PositionInfo.txt"};
	//getcwd(file_path, 512); 
	//printf("current dir is:\n");
	//sprintf(file_path + strlen(file_path),"%s\\PositionInfo.txt", file_path);
	memset(file_path, 0, 128);
	GetDlgItem(IDC_EDIT1)->GetWindowText(cholon1,10);
    GetDlgItem(IDC_EDIT2)->GetWindowText(cholon2,10);
	GetDlgItem(IDC_EDIT7)->GetWindowText(cholon3,10);
    GetDlgItem(IDC_EDIT8)->GetWindowText(cholon4,10);
	k=atoi(cholon1);
	n=atoi(cholon2);
	total_times = atoi(cholon3);
	current_times = atoi(cholon4);
	sprintf(file_path, "d:\\PositionInfo%d.txt", current_times);
	num=1;
	m_camera=m_geApplication.GetCamera(1); 
	double range;
	range=m_camera.GetRange();
	int each_times = k * n / total_times;
	//m_camera.SetAzimuth(azimuth);
    ofstream fop(file_path,ios::out);
    fop<<"当前地形的视高为："<<range<<"米"<<"\n"<<"num,"<<"longitude,"<<"latitude,"<<"altitude"<<endl;
	fop.close();
	ofstream outfile(file_path,ios::app);
	k = k - 1;
	n = n - 1;
	for(i=0;i<=k;i++)
		for(j=0;j<=n;j++)
		{
			if (((i * n + i + j + 1)> (current_times -1) * each_times) && ((i * n + i + j + 1) <= current_times * each_times))
			{
			px=2.0*(i - k/2.0)/k;
			py=2.0*(n/2.0 - j)/n;
			PointOnTerrain=m_geApplication.GetPointOnTerrainFromScreenCoords(px,py);
            longitude=PointOnTerrain.GetLongitude();
			latitude=PointOnTerrain.GetLatitude();
			altitude=PointOnTerrain.GetAltitude();		
        outfile<<num<<","<<longitude<<","<<latitude<<","<<altitude<<endl;
        num++;
			}
		}
		outfile.close();




	//string
	//k=AxGEViewer3.Width;
	//j=AxGEViewer3.Height;


}
void CTestDlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CTestDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CTestDlg::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CTestDlg::OnEnChangeEdit5()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CTestDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	double focus_lon, focus_lat, range, azimuth;//azimuth 为视角与正北方向的夹角
	char cholon1[10],cholon2[10], cholon3[10], cholon4[10];
	GetDlgItem(IDC_EDIT3)->GetWindowText(cholon1,10);
    GetDlgItem(IDC_EDIT4)->GetWindowText(cholon2,10);
	GetDlgItem(IDC_EDIT5)->GetWindowText(cholon3,10);
	GetDlgItem(IDC_EDIT6)->GetWindowText(cholon4,10);
	focus_lon=atof(cholon1);
	focus_lat=atof(cholon2);
	range=atof(cholon3);
	azimuth=atof(cholon4);
	m_geApplication.SetCameraParams(focus_lat,focus_lon,0.0,1,range,0.0,azimuth,1.0);

}

void CTestDlg::OnEnChangeEdit8()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CTestDlg::OnEnChangeEdit7()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CTestDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	 // TODO: 在此添加控件通知处理程序代码
    CString FilePathName;
    CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
        NULL, 
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        (LPCTSTR)_TEXT("All Files (*.*)|*.*||"),
        NULL);
    if(dlg.DoModal()==IDOK)
    {
        FilePathName=dlg.GetPathName(); //文件名保存在了FilePathName里
    }
    else
    {
         return;
    }

	//test code start

	LPSTR lpAppFile;
	//lpAppFile = "C:\\Program Files (x86)\\Microsoft Office\\Office12\\WINWORD.EXE G:\\G\\TPWD.doc";
	//lpAppFile = "C:\\Program Files (x86)\\Microsoft Office\\Office12\\POWERPNT.EXE G:\\G\\Ctest.ppt";
	//lpAppFile = "C:\\Windows\\system32\\cmd.exe";
	lpAppFile = (LPSTR)malloc(sizeof(LPSTR) * 256);
	//sprintf(lpAppFile, "C:\\Windows\\system32\\notepad.exe %s", FilePathName.GetBuffer(0));
	//sprintf(lpAppFile, "C:\\Program Files\\Windows Media Player\\wmplayer.exe %s", FilePathName.GetBuffer(0));
	//sprintf(lpAppFile, "C:\\Program Files (x86)\\Baofeng\\StormPlayer\\StormPlayer.exe %s", FilePathName.GetBuffer(0));
	//sprintf(lpAppFile, "C:\\Program Files (x86)\\Microsoft Office\\Office12\\POWERPNT.EXE %s", FilePathName.GetBuffer(0));
	sprintf(lpAppFile, "C:\\Program Files (x86)\\Microsoft Office\\Office15\\WINWORD.EXE %s", FilePathName.GetBuffer(0));
	//sprintf(lpAppFile, "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\wpp.exe %s", FilePathName.GetBuffer(0));
	//lpAppFile = "C:\\Program Files (x86)\\Windows Media Player\\wmplayer.exe";
	//LPSTR lpFileName;
	//lpFileName = (LPSTR)malloc(sizeof(LPSTR) * 256);
	//sprintf(lpFileName, " %s", FilePathName.GetBuffer(0));
	HWND hWnd = CrnRunAppAndGetMainWnd(lpAppFile, "", "");//Notepad
	//Sleep(3000);
    if(hWnd)
	{
	    //::ShowWindow(hWnd, SW_HIDE);
       ::SetParent(hWnd, this->GetDlgItem(IDCANCEL2)->GetSafeHwnd());
		//if (NULL != ::SetParent(hWnd, this->GetDlgItem(IDCANCEL2)->GetSafeHwnd()))
		//{
		//	::MessageBox(NULL, "setparent OK", "demo", MB_OK);
		//}
		//::MessageBox(NULL, "setparent OK", "demo", MB_OK);
	   ::MoveWindow(hWnd, 0, 0, 800, 620, false);

	   //if (::GetParent(hWnd) == this->GetDlgItem(IDCANCEL2)->GetSafeHwnd())
	   //{
		//   ::MessageBox(NULL, "MoveWindow", "demo", MB_OK);
	  // }
	   //::MessageBox(NULL, "MoveWindow", "demo", MB_OK);
	   ::ShowWindow(hWnd, SW_SHOW);
	   //free(lpAppFile);
	   //free(lpFileName);
	}

	//test cond end

	//test start
/*
	//test creatProcess start
	 STARTUPINFO si = { sizeof(si) };   
    PROCESS_INFORMATION pi;   
  
    si.dwFlags = STARTF_USESHOWWINDOW;   
    si.wShowWindow = TRUE; //TRUE表示显示创建的进程的窗口  
    TCHAR cmdline[] =TEXT("c://program files//internet explorer//iexplore.exe http://community.csdn.net/");  
    BOOL bRet = ::CreateProcess (   
        NULL,  
        cmdline, //在Unicode版本中此参数不能为常量字符串，因为此参数会被修改    
        NULL,   
        NULL,   
        FALSE,   
        CREATE_NEW_CONSOLE,   
        NULL,   
        NULL,   
        &si,   
        &pi); 
	//test creatprocess end

	//获取客户端框架窗口句柄
    long m_hMainWnd = m_geApplication.GetMainHwnd();	 
    //设置窗口的位置和大小
    //::SetWindowPos((HWND)m_hMainWnd, HWND_BOTTOM, 0, 0, STATIC_GOOGLEEARTH_WIDTH+AP_GOOGLEEARTH_LEFTWIDTH+AP_GOOGLEEARTH_RIGHTWIDTH, STATIC_GOOGLEEARTH_HEIGHT+AP_GOOGLEEARTH_TOPHEIGHT+AP_GOOGLEEARTH_BOTTOMHEIGHT, SWP_HIDEWINDOW);
    OLE_HANDLE renderhwnd = m_geApplication.GetRenderHwnd();	
    HWND GEParentHrender = ::GetParent((HWND)renderhwnd);
    //::ShowWindow(GEParentHrender, SW_HIDE);	
    //把HWND和窗口上的一个静态文本控件绑定
	//CWnd* ppWnd;
  */ 
	//test end

	//long m_hMainWnd = m_geApplication.GetMainHwnd();
	ShellExecute((HWND)m_geApplication.GetMainHwnd(),"open",FilePathName,"","",SW_SHOWNORMAL);
	//::SetParent((HWND)m_geApplication.GetMainHwnd(), this->GetDlgItem(IDCANCEL2)->GetSafeHwnd());
/*
	ShellExecute(GEParentHrender,"open",FilePathName,"","",SW_SHOWNORMAL);
	::SetParent(GEParentHrender, this->GetDlgItem(IDCANCEL2)->GetSafeHwnd());// ppWnd->GetDlgItem(IDC_STATIC7)->GetSafeHwnd());
	*/
}



void CTestDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	timeControl++;
	IFeatureGE feature1,feature2,feature3;
	IFeatureCollectionGE collect1,collect2;
	switch(timeControl)
	{
	case 1:
		//显示国家边界和国名
		m_geApplication.SetCameraParams(31.5233,108.9261,50.0,1,7098550,0.0,0.0,1.5);
		collect1=m_geFeature[5].GetChildren();
		feature1=collect1.GetItem(1);
		collect2=feature1.GetChildren();
		feature2=collect2.GetItem(1);
		feature2.SetVisibility(TRUE);
		feature3=collect2.GetItem(2);
		feature3.SetVisibility(TRUE);
		break;
	case 2:
		//显示省级边界和地名
		m_geApplication.SetCameraParams(31.5233,108.9261,50.0,1,2254490,0.0,0.0,0.05);
		collect1=m_geFeature[5].GetChildren();
		feature1=collect1.GetItem(1);
		collect2=feature1.GetChildren();
		feature2=collect2.GetItem(5);
		feature2.SetVisibility(TRUE);
		feature3=collect2.GetItem(6);
		feature3.SetVisibility(TRUE);
		break;
	case 3:
		//显示交通设施
		m_geApplication.SetCameraParams(39.2267,117.4622,50.0,1,838950,0.0,0.0,0.5);
		m_geFeature[2].SetVisibility(TRUE);
		break;
	case 4:
		//延缓交通设施的显示时间
		m_geApplication.SetCameraParams(39.2267,117.4622,50.0,1,838000,0.0,0.0,0.05);
		break;
	case 5:
		//显示市级地名
		m_geApplication.SetCameraParams(30.2764,114.1250,50.0,1,166860,0.0,0.0,0.05);
		collect1=m_geFeature[5].GetChildren();
		feature1=collect1.GetItem(3);
		feature1.SetVisibility(TRUE);
		break;
	case 6:
		KillTimer(1);					//关闭定时器
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CTestDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	int i;
	CLAYERSCONTROL layersDlg;
	BOOL* boolLayer1=new BOOL[countSum];	//当前图层设置
	BOOL* boolLayer2=new BOOL[countSum];	//用户图层设置
	//获取当前的图层设置
	for(i=0;i<countSum;i++)
	{
		boolLayer1[i]=m_geFeature[i].GetVisibility();		
	}
	//初始化用户设置
	for(i=0;i<countSum;i++)
	{
		boolLayer2[i]=FALSE;
	}
	//获取用户对图层的选择
	if(IDOK==layersDlg.DoModal())
	{
		boolLayer2[1]=layersDlg.m_web;
		boolLayer2[2]=layersDlg.m_roads;
		boolLayer2[3]=layersDlg.m_3DBuild;
		boolLayer2[4]=layersDlg.m_street;
		boolLayer2[5]=layersDlg.m_borders;
		boolLayer2[6]=layersDlg.m_weather;
		boolLayer2[7]=layersDlg.m_pictures;
		boolLayer2[8]=layersDlg.m_ocean;
		boolLayer2[9]=layersDlg.m_awareness;
		boolLayer2[0]=layersDlg.m_terrain;
	}
	
	//根据用户的选择重新设置图层
	for(i=0;i<countSum;i++)
	{
		if(boolLayer1[i]!=boolLayer2[i])
		{
			if(TRUE==boolLayer2[i])
			{
				m_geFeature[i].SetVisibility(TRUE);
			}
			else
			{
				m_geFeature[i].SetVisibility(FALSE);
			}
		}
	}
	//释放数组
	delete [] boolLayer1;
	delete [] boolLayer2;
}

void CTestDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	IFeatureGE feature;
	IFeatureCollectionGE collect;
	int i;

	timeControl=0;						//控制OnTimer()函数
	//获取Goolge Earth的图层数据集
	m_geCollect=m_geApplication.GetLayersDatabases();
	feature=m_geCollect.GetItem(1);
	collect=feature.GetChildren();
	countSum=collect.GetCount();

	m_geFeature=new IFeatureGE[countSum];
	m_geFeature[0]=collect.GetItem(countSum);	//获取地形图层
	m_geFeature[0].SetVisibility(TRUE);	//设置地形图层可见

	//设置其它图层不可见
	for(i=1;i<countSum;i++)
	{
		m_geFeature[i]=collect.GetItem(i);
		if(TRUE==m_geFeature[i].GetVisibility())
		{
			m_geFeature[i].SetVisibility(FALSE);
		}
	}

	SetTimer(1,2000,NULL);				//启动定时器
}

void CTestDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	CString place;
	CManyou test;   //新建新对话框的对象page.DoModal(); 
	if( IDOK == test.DoModal())
		place = test.place;
	//MessageBox(place,"定位",MB_OKCANCEL);
	if (!strcmp(place, "北京"))
		//case "北京":
		m_geApplication.SetCameraParams(39.9,116.467,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "天津"))
		//case "北京":
		m_geApplication.SetCameraParams(39.15,117.183,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "石家庄"))
		//case "北京":
		m_geApplication.SetCameraParams(38.033,114.467,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "上海"))
		//case "北京":
		m_geApplication.SetCameraParams(31.233,121.483,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "重庆"))
		//case "北京":
		m_geApplication.SetCameraParams(29.533,106.533,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "哈尔滨"))
		//case "北京":
		m_geApplication.SetCameraParams(45.75,126.683,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "长春"))
		//case "北京":
		m_geApplication.SetCameraParams(43.867,125.317,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "沈阳"))
		//case "北京":
		m_geApplication.SetCameraParams(41.833,123.4,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "呼和浩特"))
		//case "北京":
		m_geApplication.SetCameraParams(40.817,111.8,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "太原"))
		//case "北京":
		m_geApplication.SetCameraParams(37.867,112.567,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "济南"))
		//case "北京":
		m_geApplication.SetCameraParams(36.517,117,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "郑州"))
		//case "北京":
		m_geApplication.SetCameraParams(34.8,113.6,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "西安"))
		//case "北京":
		m_geApplication.SetCameraParams(34.267,108.9,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "兰州"))
		//case "北京":
		m_geApplication.SetCameraParams(36.05,103.817,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "银川"))
		//case "北京":
		m_geApplication.SetCameraParams(38.333,106.267,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "西宁"))
		//case "北京":
		m_geApplication.SetCameraParams(36.633,101.75,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "乌鲁木齐"))
		//case "北京":
		m_geApplication.SetCameraParams(43.8,87.6,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "合肥"))
		//case "北京":
		m_geApplication.SetCameraParams(31.85,117.3,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "南京"))
		//case "北京":
		m_geApplication.SetCameraParams(32.033,118.833,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "杭州"))
		//case "北京":
		m_geApplication.SetCameraParams(30.233,120.15,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "长沙"))
		//case "北京":
		m_geApplication.SetCameraParams(28.183,113,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "南昌"))
		//case "北京":
		m_geApplication.SetCameraParams(28.683,115.867,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "武汉"))
		//case "北京":
		m_geApplication.SetCameraParams(30.617,114.35,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "成都"))
		//case "北京":
		m_geApplication.SetCameraParams(30.65,104.083,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "贵阳"))
		//case "北京":
		m_geApplication.SetCameraParams(26.583,106.7,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "福州"))
		//case "北京":
		m_geApplication.SetCameraParams(26.083,119.3,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "台北"))
		//case "北京":
		m_geApplication.SetCameraParams(25.05,121.517,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "广州"))
		//case "北京":
		m_geApplication.SetCameraParams(23.133,113.25,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "海口"))
		//case "北京":
		m_geApplication.SetCameraParams(20.033,110.333,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "南宁"))
		//case "北京":
		m_geApplication.SetCameraParams(22.8,108.333,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "昆明"))
		//case "北京":
		m_geApplication.SetCameraParams(25,102.683,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "拉萨"))
		//case "北京":
		m_geApplication.SetCameraParams(29.65,90.133,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "香港"))
		//case "北京":
		m_geApplication.SetCameraParams(22.3,114.167,0.0,1,10000,0.0,0,1.0);
	if (!strcmp(place, "澳门"))
		//case "北京":
		m_geApplication.SetCameraParams(22.233,113.583,0.0,1,10000,0.0,0,1.0);
	//MessageBox(place,"定位",MB_OKCANCEL);
		//break;
	// CManyou *dlg=new CManyou(this); 
//dlg->Create(IDD_MANYOU); 
//dlg->ShowWindow(SW_SHOW);
}

void CTestDlg::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	char cholon1[10],cholon2[10], cholon3[10], cholon4[10];
	double R = 6371.04;
	double C;
	double start_lon,start_lat,end_lon,end_lat,dis;
	CString dis_str = "test";
	double PI = 3.141593;
	GetDlgItem(IDC_EDIT11)->GetWindowText(cholon1,10);
    GetDlgItem(IDC_EDIT9)->GetWindowText(cholon2,10);
	GetDlgItem(IDC_EDIT10)->GetWindowText(cholon3,10);
	GetDlgItem(IDC_EDIT12)->GetWindowText(cholon4,10);
	start_lon=atof(cholon1);
	start_lat=atof(cholon2);
	end_lon=atof(cholon3);
	end_lat=atof(cholon4);
	C = sin(start_lat*PI/180.0) * sin(end_lat*PI/180.0) +
		cos(start_lat*PI/180.0) * cos(end_lat*PI/180.0)*
		cos((start_lon - end_lon)*PI/180.0);
	dis = R * acos(C);
	//sprintf(dis_str,"%fkm", dis);
	dis_str.Format("%fkm",dis);
    //CString m_strREData = "test";
	SetDlgItemText(IDC_EDIT13,dis_str);  //前一个是ID号，后一个是编辑框的成员变量
	//IDC_EDIT13
}

void CTestDlg::OnEnChangeEdit11()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CTestDlg::OnEnChangeEdit10()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CTestDlg::OnEnChangeEdit9()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CTestDlg::OnEnChangeEdit13()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CTestDlg::OnEnChangeEdit12()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CTestDlg::OnStnClickedCancel2()
{
	// TODO: Add your control notification handler code here
}


//关闭界面时不是在CloseWindow中，是在DestroyWindow中
BOOL CTestDlg::DestroyWindow()
{
	m_geApplication.DetachDispatch();
	system("taskkill /IM googleearth.exe");

	int i;
	LPSTR lpkillCmd;
	lpkillCmd = (LPSTR)malloc(sizeof(LPSTR) * 256);
	for(i = 0; i < needkill_num; i++)
	{
		sprintf(lpkillCmd, "taskkill /F /PID %d", needkill_pid[i]);
		system(lpkillCmd);
		memset(lpkillCmd, 0, 256);
	}

	CDialog::DestroyWindow();
	return TRUE;
}

void CTestDlg::ShowFile(CString str_Dir, HTREEITEM tree_Root)
{
    CFileFind FileFind;

    //临时变量，用以记录返回的树节点
    HTREEITEM tree_Temp;

    //判断输入目录最后是否存在'\'，不存在则补充
    if (str_Dir.Right(1) != "\\")
        str_Dir += "\\";
    str_Dir += "*.*";
    BOOL res = FileFind.FindFile(str_Dir);
    while (res)
    {
        tree_Temp = tree_Root;
        res = FileFind.FindNextFile();
        if (FileFind.IsDirectory() && !FileFind.IsDots())//目录是文件夹
        {
            CString strPath = FileFind.GetFilePath(); //得到路径，做为递归调用的开始
            CString strTitle = FileFind.GetFileName();//得到目录名，做为树控的结点
            tree_Temp = m_TreeCtrl.InsertItem(strTitle, 0, 0, tree_Root);
            ShowFile(strPath, tree_Temp);
        }
        else if (!FileFind.IsDirectory() && !FileFind.IsDots() && (NULL == strstr(FileFind.GetFilePath(),"main_background.")))//如果是文件
        {
            CString strPath = FileFind.GetFilePath(); //得到路径，做为递归调用的开始
            CString strTitle = FileFind.GetFileName();//得到文件名，做为树控的结点
            m_TreeCtrl.InsertItem(strTitle, 0, 0, tree_Temp);
        }
    }
    FileFind.Close();
}

HTREEITEM CTestDlg::GetSelectTree()
{
	/*
    CPoint pt;
    GetCursorPos(&pt);//得到当前鼠标的位置
    m_TreeCtrl.ScreenToClient(&pt);//将屏幕坐标转换为客户区坐标
    HTREEITEM tree_Item = m_TreeCtrl.HitTest(pt);//调用HitTest找到对应点击的树节点
		*/
	HTREEITEM tree_Item = m_TreeCtrl.GetSelectedItem();
    return tree_Item;
}

DWORD CTestDlg::GetFilePathByTreeItem()
{
    //临时变量
    bool IsDirectory;
    CString str_TempDir;
    HTREEITEM tree_CurTreeTemp;

    //获取到当前鼠标选择的树节点
    m_CurTree = GetSelectTree();

    if (m_CurTree == NULL)
    {
		::MessageBox(NULL, "获取失败",
			"ccrun.com", MB_OK | MB_ICONERROR);
        //MessageBox(L"获取当前树节点失败！！");
    }
    tree_CurTreeTemp = m_CurTree;

    //获取当前节点的父节点，以便得到文件路径
    m_CurTreeParent = m_TreeCtrl.GetParentItem(m_CurTree);
    str_TempDir = m_TreeCtrl.GetItemText(m_CurTree);

    //为根节点时不作处理
    if (!str_TempDir.IsEmpty() && m_CurTreeParent != NULL)
    {
        m_CurTreeDir = str_TempDir;
        while (m_CurTreeParent != m_TreeCtrl.GetRootItem())//当父节点不为根节点时循环
        {
            //此处就是不断向上层层拼接文件路径的过程，比如123.txt的父节点是test1,然后经过             //一步循环后m_CurTreeDir就为：test1\\123.txt
            str_TempDir = m_TreeCtrl.GetItemText(m_CurTreeParent);
            m_CurTreeDir = str_TempDir + L"\\" + m_CurTreeDir;
            tree_CurTreeTemp = m_CurTreeParent;
            m_CurTreeParent = m_TreeCtrl.GetParentItem(tree_CurTreeTemp);
         }
         m_CurTreeDir = L"C:\\vc6\\run\\run\\" + m_CurTreeDir;
         CFileFind FileFind;
         BOOL res = FileFind.FindFile(m_CurTreeDir);
         if (res == true)
         {
             if (res = FileFind.FindNextFile());
             {
                 if (FileFind.IsDirectory() && !FileFind.IsDots())//如果是文件夹
                     return Return_IsFolder;
                 else if (!FileFind.IsDirectory() && !FileFind.IsDots() && (-1 == m_CurTreeDir.Find("main_background.")))//如果是文件
                     return Return_IsFile;
              }
          }
    }
    return Error_FileOrFolderNotFound;
}

void CTestDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	//kill current open files
    int i;
	LPSTR lpkillCmd;
	lpkillCmd= (LPSTR)malloc(sizeof(LPSTR) * 256);
	for(i = 0; i < needkill_num; i++)
	{
		sprintf(lpkillCmd, "taskkill /F /PID %d", needkill_pid[i]);
		system(lpkillCmd);
		memset(lpkillCmd, 0, 256);
	}
	needkill_num = 0;
	free(lpkillCmd);

	DWORD res = GetFilePathByTreeItem();

	//如果当前选择节点为文件夹，则打开main_background.*
	if (res == Return_IsFolder)
	{
		if (-1 != m_CurTreeDir.Find("三维教学"))
		{
			::SetParent((HWND)renderhwnd, this->GetDlgItem(IDCANCEL2)->GetSafeHwnd());// ppWnd->GetDlgItem(IDC_STATIC7)->GetSafeHwnd());
		} else
		{
            ::ShowWindow(GEParentHrender, SW_SHOW);	
            //把HWND和窗口上的一个静态文本控件绑定
            ::SetParent((HWND)renderhwnd, GEParentHrender);// ppWnd->GetDlgItem(IDC_STATIC7)->GetSafeHwnd());

		    m_CurTreeDir = m_CurTreeDir + L"\\main_background.jpg";
		    //设置静态控件的样式，使其可以使用位图，并使位图显示居中  
            ((CStatic*)GetDlgItem(IDCANCEL2))-> ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);  
  
            CDC *pDC=NULL;  
            pDC=GetDlgItem(IDCANCEL2)->GetDC();  
           //ShowJpgGif(pDC,dlg.GetPathName(),0,0);  
		    ShowImage(pDC,m_CurTreeDir.GetBuffer(0),0,0);  
  
            ReleaseDC(pDC); // 记得释放资源，不然会导致内存泄露
		}

	}

    //如果当前选择节点为文件，则将其打开
    if (res == Return_IsFile)
    {
		if (-1 == m_CurTreeDir.Find(".jpg") || m_CurTreeDir.Find(".png") || m_CurTreeDir.Find(".bmp") || m_CurTreeDir.Find(".gif"))
		{
			::ShowWindow(GEParentHrender, SW_SHOW);	
            //把HWND和窗口上的一个静态文本控件绑定
            ::SetParent((HWND)renderhwnd, GEParentHrender);// ppWnd->GetDlgItem(IDC_STATIC7)->GetSafeHwnd());

			 //设置静态控件的样式，使其可以使用位图，并使位图显示居中  
            ((CStatic*)GetDlgItem(IDCANCEL2))-> ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);  
  
            CDC *pDC=NULL;  
            pDC=GetDlgItem(IDCANCEL2)->GetDC();  
           //ShowJpgGif(pDC,dlg.GetPathName(),0,0);  
		    ShowImage(pDC,m_CurTreeDir.GetBuffer(0),0,0);  
  
            ReleaseDC(pDC); // 记得释放资源，不然会导致内存泄露
		} else if (-1 == m_CurTreeDir.Find(".doc") && -1 == m_CurTreeDir.Find(".ppt") && -1 == m_CurTreeDir.Find(".txt"))
		{
			ShellExecute(NULL, NULL, m_CurTreeDir, NULL, NULL, SW_SHOWNORMAL);
		} else
		{
		    LPSTR lpAppFile;
	        lpAppFile = (LPSTR)malloc(sizeof(LPSTR) * 256);
		    //judge file type
		    if (-1 != m_CurTreeDir.Find(".doc"))
		    {
			    sprintf(lpAppFile, "C:\\Program Files (x86)\\Microsoft Office\\Office15\\WINWORD.EXE %s", m_CurTreeDir.GetBuffer(0));
		    } else if (-1 != m_CurTreeDir.Find(".ppt"))
		    {
			    sprintf(lpAppFile, "C:\\Program Files (x86)\\Microsoft Office\\Office15\\POWERPNT.EXE %s", m_CurTreeDir.GetBuffer(0));
		    } else if (-1 != m_CurTreeDir.Find(".txt"))
		    {
			    sprintf(lpAppFile, "C:\\Windows\\system32\\notepad.exe %s", m_CurTreeDir.GetBuffer(0));
		    }

			HWND hWnd = CrnRunAppAndGetMainWnd(lpAppFile, "", "");//Notepad
            if(hWnd)
	        {
               ::SetParent(hWnd, this->GetDlgItem(IDCANCEL2)->GetSafeHwnd());
			   ::MoveWindow(hWnd, 0, 0, 800, 620, false);
	           ::ShowWindow(hWnd, SW_SHOW);
	           free(lpAppFile);
			}


			/*
			//test show image
			// TODO: Add your control notification handler code here

	::ShowWindow(GEParentHrender, SW_SHOW);	
    //把HWND和窗口上的一个静态文本控件绑定
    ::SetParent((HWND)renderhwnd, GEParentHrender);// ppWnd->GetDlgItem(IDC_STATIC7)->GetSafeHwnd());

    CFileDialog dlg(TRUE,"jpg","*.jpg", OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,   
        "JPEG文件(*.jpg)|*.jpg|GIF文件(*.gif)|*.gif|bmp文件(*.bmp)|*.bmp|",NULL);   
    if(dlg.DoModal()==IDOK)   
    {   
  
        //设置静态控件的样式，使其可以使用位图，并使位图显示居中  
        ((CStatic*)GetDlgItem(IDCANCEL2))-> ModifyStyle(0xF,SS_BITMAP|SS_CENTERIMAGE);  
  
        CDC *pDC=NULL;  
        pDC=GetDlgItem(IDCANCEL2)->GetDC();  
        //ShowJpgGif(pDC,dlg.GetPathName(),0,0);  
        ShowImage(pDC,dlg.GetPathName(),0,0);  
  
        ReleaseDC(pDC); // 记得释放资源，不然会导致内存泄露  
    }
	*/

		}
	}
	*pResult = 0;
}

//************************************  
// 方法说明:    显示JPG和GIF、BMP图片  
// 参数说明:    CDC * pDC           设备环境对象  
// 参数说明:    CString strPath     要显示的图片路径   
// 参数说明:    int x               要显示的X位置  
// 参数说明:    int y               要显示的Y位置  
// 返回值:      BOOL                成功返回TRUE,否则返回FALSE  
//************************************  
BOOL CTestDlg::ShowImage(CDC* pDC,CString strPath, int x, int y)  
{  
     
    IPicture *pPic=NULL;   
    OleLoadPicturePath(CComBSTR(strPath.GetBuffer()), (LPUNKNOWN)NULL, 0, 0, IID_IPicture,(LPVOID*)&pPic);  
    if (NULL==pPic)  
    {  
        return FALSE;  
    }  
  
    // 获取图像宽和高,注意这里的宽和高不是图像的分辨率  
    OLE_XSIZE_HIMETRIC hmWidth;    
    OLE_YSIZE_HIMETRIC hmHeight;    
    pPic->get_Width(&hmWidth);    
    pPic->get_Height(&hmHeight);    
  
    // 将图像宽度和高度单位转化为像素单位  
   //#define HIMETRIC_PER_INCH 2540  
   //int nPicWidth =  MulDiv(hmWidth, GetDeviceCaps(GetDC()->m_hDC, LOGPIXELSX),2540);  
   //int nPicHeight = MulDiv(hmHeight, GetDeviceCaps(GetDC()->m_hDC, LOGPIXELSY),2540);  
  
   // 获取显示图片窗口的宽度和高度  
   RECT rtWnd;  
   pDC->GetWindow()->GetWindowRect(&rtWnd);  
   int iWndWidth=rtWnd.right-rtWnd.left;  
   int iWndHeight=rtWnd.bottom-rtWnd.top;  
  
   if(FAILED(pPic->Render(*pDC,x,y,iWndWidth,iWndHeight,0,hmHeight,hmWidth,-hmHeight,NULL)))    
   {  
       pPic->Release();  
       return false;  
   }  
  
   //记得释放资源，不然会导致内存泄露  
   pPic->Release();   
     
   return true;  
}  
  