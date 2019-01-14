// My3DDlg.cpp : implementation file
//

#include "stdafx.h"
#include "My3D.h"
#include "My3DDlg.h"

#include "DataInput.h"
#include "DataDistribute.h"
#include "DataChart.h"
#include "DataAnalyse.h"
#include "AutoBase.h"
#include "Intersection.h"
#include "DonateInfo.h"

#include "WinHistory.h"
#include "SaveOption.h"

#include "Number.h"

#include "..\Share\HyperLink.h"
#include "..\Share\WND.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define _TIMER_REFRESH_BTN_OK_ 0

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
	enum {THANKS = 7};

	CHyperLink lnkHomePage;
	CHyperLink lnkMail;
	CHyperLink lnk[THANKS];

	CString strName[THANKS];
	CString strTip[THANKS];
	CString strUrl[THANKS];
	
	int cx, cy;
	int cyMin;

public:
	CAboutDlg();
	BOOL bMost;

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
	afx_msg void OnThank();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonDonate();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT

	bMost = FALSE;
	cyMin = 246;

	strName[0] = _T("阿皮");
	strTip[0] = _T("INI 配置文件类");
	strUrl[0] = _T("http://www.vckbase.com/code/viewcode.asp?id=1736");

	strName[1] = _T("黄晨量");
	strTip[1] = _T("多属性页方案");
	strUrl[1] = _T("http://www.vckbase.com/document/viewdoc/?id=398");

	strName[2] = _T("Javen");
	strTip[2] = _T("IDC Link 控件");
	strUrl[2] = _T("http://blog.csdn.net/jun_01/archive/2007/03/06/1521694.aspx");

	strName[3] = _T("smiletiger");
	strTip[3] = _T("可变颜色的排序列表框");
	strUrl[3] = _T("http://www.vckbase.com/document/viewdoc/?id=891");
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_THANK, OnThank)
	ON_BN_CLICKED(IDC_BUTTON_DONATE, OnButtonDonate)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DDlg dialog

CMy3DDlg::CMy3DDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy3DDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy3DDlg)
	m_strTip1 = _T("");
	m_strTip2 = _T("");
	m_strTip3 = _T("");
	m_strTip4 = _T("");
	m_iLotType = 0;
	m_bReplaceBase = TRUE;
	m_bSaveAsOpenCond = FALSE;
	m_bUnite = TRUE;
	m_iStatPeriods = 100;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_iOldType = m_iLotType;
	pApp = (CMy3DApp *)AfxGetApp();
	pHistory = pApp->GetHistory();

	m_pageG6.SetSrcData(&pApp->aResult[0]);
	m_pageG3.SetSrcData(&pApp->aResult[1]);
	m_pageG1.SetSrcData(&pApp->aResult[2]);

	if( WND::IsExistFile(WND::GetAbsPath() + _T("\\Upload")) )
		strExTool1 = _T("\\Upload");
	else
		strExTool1 = _T("\\");
	strExTool2.Empty();

	strExName1 = _T("目录");
	strExName2.Empty();
	m_bOnce = FALSE;
	m_bDisp = TRUE;
}

void CMy3DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy3DDlg)
	DDX_Control(pDX, IDC_TAB_COND, m_tabCond);
	DDX_Control(pDX, IDC_TAB_RESULT, m_tabResult);
	DDX_Control(pDX, IDC_TAB_NUM_BASE, m_tabNumBase);
	DDX_Control(pDX, IDC_CMB_ALLOW_ERROR, m_cmbAllowErrorAll);
	DDX_Control(pDX, IDC_CMB_ALLOW_ERROR2, m_cmbAllowErrorPage);
	DDX_Text(pDX, IDC_EDIT_TIP1, m_strTip1);
	DDX_Text(pDX, IDC_EDIT_TIP2, m_strTip2);
	DDX_Text(pDX, IDC_EDIT_TIP3, m_strTip3);
	DDX_Text(pDX, IDC_EDIT_TIP4, m_strTip4);
	DDX_Radio(pDX, IDC_RADIO_P3, m_iLotType);
	DDX_Check(pDX, IDC_CHK_REPLACE_BASE, m_bReplaceBase);
	DDX_Check(pDX, IDC_CHK_SAVEAS_OPEN, m_bSaveAsOpenCond);
	DDX_Check(pDX, IDC_CHK_UNITE, m_bUnite);
	DDX_Text(pDX, IDC_EDIT_ANALYSE_PERIODS, m_iStatPeriods);
	//}}AFX_DATA_MAP

#ifdef USE_BTN_ST	
// 	DDX_Control(pDX, IDC_DATA_INPUT, m_btnDataInput);
// 	DDX_Control(pDX, IDC_DISTRIBUTE, m_btnDistribute);
// 	DDX_Control(pDX, IDC_ANALYSE_TREND, m_btnTrend);
// 	DDX_Control(pDX, IDC_DATA_ANALYSE, m_btnDataAnalyse);
// 	DDX_Control(pDX, IDC_MUTI_CALC, m_btnCalcer);
// 	DDX_Control(pDX, IDHELP, m_btnHelp);
// 	DDX_Control(pDX, IDC_CHECK_UPDATE, m_btnUpdate);
// 	DDX_Control(pDX, IDC_BTN_ABOUT, m_btnAbout);
// 	DDX_Control(pDX, IDCANCEL, m_btnExit);
#endif
}

BEGIN_MESSAGE_MAP(CMy3DDlg, CDialog)
	//{{AFX_MSG_MAP(CMy3DDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_TEST, OnBtnTest)
	ON_BN_CLICKED(IDC_BTN_TEST2, OnBtnTest2)
	ON_BN_CLICKED(IDC_SINGLE_TO_GROUP, OnSingleToGroup)
	ON_BN_CLICKED(IDC_GROUP_TO_SINGLE, OnGroupToSingle)
	ON_BN_CLICKED(IDC_SENT_TO_BASE, OnSentToBase)
	ON_BN_CLICKED(IDC_MUTI_CALC, OnMutiCalc)
	ON_BN_CLICKED(IDC_SAVE_FILE, OnSaveFile)
	ON_BN_CLICKED(IDC_DATA_INPUT, OnDataInput)
	ON_BN_CLICKED(IDC_DATA_ANALYSE, OnDataAnalyse)
	ON_BN_CLICKED(IDHELP, OnHelp)
	ON_BN_CLICKED(IDC_BTN_ABOUT, OnBtnAbout)
	ON_BN_CLICKED(IDC_INTER_BASE, OnInterBase)
	ON_BN_CLICKED(IDC_INTER_FILE, OnInterFile)
	ON_BN_CLICKED(IDC_AUTO_BASE, OnAutoBase)
	ON_BN_CLICKED(IDC_EXCLUDE_BASE, OnExcludeBase)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_RESULT, OnSelchangeTabResult)
	ON_BN_CLICKED(IDC_ANALYSE_TREND, OnAnalyseTrend)
	ON_BN_CLICKED(IDC_CHECK_UPDATE, OnCheckUpdate)
	ON_BN_CLICKED(IDC_COND_READ, OnCondRead)
	ON_BN_CLICKED(IDC_COND_RESET, OnCondReset)
	ON_BN_CLICKED(IDC_COND_SAVE, OnCondSave)
	ON_BN_CLICKED(IDC_DISTRIBUTE, OnDistribute)
	ON_BN_CLICKED(IDC_ANALYSE_RESULT, OnAnalyseResult)
	ON_BN_CLICKED(IDC_BTN_HAND_DEL, OnBtnHandDel)
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_ICONNOTIFY, OnIconNotify)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_P3, IDC_RADIO_3D, OnSelectLottery)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DDlg message handlers

VOID CMy3DDlg::InitOnce()
{
	// 投注方法多属性页
	m_tabNumBase.AddPage(_T("选择号码"), &m_page1, IDD_DIALOG_NUMBER);
	m_tabNumBase.AddPage(_T("使用大底"), &m_page2, IDD_DIALOG_BASE);
	m_tabNumBase.Show();
	
	// 过滤条件多属性页
	m_tabCond.AddPage(_T("常规"), &m_Cond1, IDD_COND1);
	m_tabCond.AddPage(_T("其它"), &m_Cond3, IDD_COND3);
	m_tabCond.AddPage(_T("形态"), &m_Cond2, IDD_COND2);
	m_tabCond.AddPage(_T("定位"), &m_Cond4, IDD_COND4);
	m_tabCond.AddPage(_T("范围"), &m_Cond5, IDD_COND5);
//	m_tabCond.AddPage(_T("自定义"), &m_Cond6, IDD_COND6);
	m_tabCond.Show();
	
	// 过滤结果多属性页
	m_tabResult.AddPage(_T("组六"), &m_pageG6, IDD_DIALOG_G6);
	m_tabResult.AddPage(_T("组三"), &m_pageG3, IDD_DIALOG_G3);
	m_tabResult.AddPage(_T("豹子"), &m_pageG1, IDD_DIALOG_G1);
	m_tabResult.Show();
	
	CString str;
	
	// 全局容错
	for(int i = 0; i <= 300; ++i)
	{
		str.Format(_T("%d"), i);
		m_cmbAllowErrorAll.AddString(str);
	}
	// 页面容错
	for(int i = 0; i <= 5; ++i)
	{
		str.Format(_T("%d"), i);
		m_cmbAllowErrorPage.AddString(str);
	}
}

VOID CMy3DDlg::Init()
{
	pApp->strVersion.LoadString(IDS_VERSION);
	m_tabNumBase.SetCurSel(0);
	m_tabCond.SetCurSel(0);
	m_tabResult.SetCurSel(0);
	
	m_cmbAllowErrorAll.SetCurSel(0);
	m_cmbAllowErrorPage.SetCurSel(m_cmbAllowErrorPage.GetCount() - 1);
	
	m_bReplaceBase = TRUE;
	m_bSaveAsOpenCond = FALSE;
	m_iStatPeriods = 100;
	
	m_iLotType = m_iOldType = 0;
}

VOID CMy3DDlg::	GetScreenInfo()
{
	// 屏幕大小
	CPaintDC dc(this); 
	int cx = ::GetDeviceCaps(dc.m_hDC, HORZRES); //屏幕宽度
	int cy = ::GetDeviceCaps(dc.m_hDC, VERTRES); //屏幕高度
	
	CRect rc;
	HWND hWnd=::FindWindow("Shell_TrayWnd", "");
	::GetWindowRect(hWnd, &rc);
	cy -= rc.bottom - rc.top;
	pApp->rcScreen.SetRect(0, 0, cx, cy);
}

BOOL CMy3DDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

/*
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
*/

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog

	
	// 按钮悬浮提示
	EnableToolTips(TRUE);
	m_tt.Create(this);
	m_tt.Activate(TRUE);
			
	m_tt.SetMaxTipWidth(250); //提示文字行宽度，非必需
	m_tt.SetTipTextColor(RGB(0,0,255)); //提示文字颜色，非必需
//	m_tt.SetDelayTime(100);    //提示显示时间，非必需

	m_tt.AddTool(GetDlgItem(IDC_CHK_REPLACE_BASE),"若选中, 下面三个按钮的操作结果会复制到大底编辑框中。否则不影响大底编辑框中的内容。");
	m_tt.AddTool(GetDlgItem(IDC_CHK_UNITE),"若选中, 下面三个按钮针对组六、组三、豹子形态同时操作。否则只针当前激活的形态操作。");
	
	m_tt.AddTool(GetDlgItem(IDC_INTER_BASE),"过滤结果 = 过滤结果 ∩ 大底编辑框");
	m_tt.AddTool(GetDlgItem(IDC_EXCLUDE_BASE),"过滤结果 = 过滤结果 － 大底编辑框");

	m_tt.AddTool(GetDlgItem(IDC_SINGLE_TO_GROUP),"过滤结果转成组选 (注意联合形态的选择状态)");
	m_tt.AddTool(GetDlgItem(IDC_GROUP_TO_SINGLE),"过滤结果转成直选 (注意联合形态的选择状态)");
	m_tt.AddTool(GetDlgItem(IDC_SENT_TO_BASE),"大底编辑框 = 大底编辑框 + 过滤结果");
	
	InitOnce();
	GetScreenInfo();
	Init();

	CString strCfgFile = WND::GetAbsPath() + _T("\\My3D.ini");

	// 检查默认配置文件是否存在，如果不存在，就创建一个
	if( !WND::IsExistFile(strCfgFile) )
	{
		CStdioFile fini;
		if( fini.Open(strCfgFile, CFile::modeCreate | CFile::modeWrite | CFile::typeText) )
			fini.Close();
		CondSave(strCfgFile, TRUE);
		m_bOnce = TRUE;
	}
	else
		CondRead(strCfgFile, TRUE);

	strCfgFile = WND::GetAbsPath() + _T("\\temp.ini");

	// 创建临时配置文件
	if( !WND::IsExistFile(strCfgFile) )
	{
		CStdioFile fini;
		if( fini.Open(strCfgFile, CFile::modeCreate | CFile::modeWrite | CFile::typeText) )
			fini.Close();
	}
	
	ReadHistory();		// 读取历史记录
	SetTitle();			// 设置标题栏
	m_iOldType = m_iLotType;
	
	DisplaySummary();	// 显示结果概要信息
	EnableButton();		// 使能按钮

	SetTimer(_TIMER_REFRESH_BTN_OK_, 500, NULL);

	UpdateData(FALSE);
	
	if( pApp->iMinToTray > 0)
	{
		// TODO: Add extra initialization here
		AddIcon();
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy3DDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
/*
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
*/
		CDialog::OnSysCommand(nID, lParam);

// 	MsgBox(EMFC::Int2Str(nID, _T("%04X")));
// 	MsgBox((::GetForegroundWindow() == m_hWnd) ? "yes" : "no");

// 	if( ::GetForegroundWindow() != m_hWnd /*&& SC_MINIMIZE == nID*/)
// 	{
// 		CDialog::OnSysCommand(SC_MINIMIZE, lParam);
// 		CDialog::OnSysCommand(SC_RESTORE, lParam);
// 		WND::ActiveWindow(pApp->GetMyClassName());
// 	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy3DDlg::OnPaint() 
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
HCURSOR CMy3DDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*
 *	[过滤] 按钮
 */
void CMy3DDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

// 	AfxMessageBox(ExportAllComment());
// 	return;

	int nOffset = 0;

	// 历史过滤
	if( WND::IsShiftDown() )
		nOffset = 1; // 忽略一期历史数据过滤

	// 按住 CTRL 则只进行上期条件验证
	BOOL bCtrl = WND::IsCtrlDown();
	
	// 预生成大底
	pApp->aBase.RemoveAll();

	if( bCtrl )
	{
		// 验证条件
		// 用最新的开奖号码作为大底
		nOffset = 1;
		if( pHistory->GetCount() > nOffset )
			pApp->aBase.Add( pHistory->GetNum(0) );
		else
		{
			AfxMessageBox(_T("无开奖数据，不能验证条件。"));
			return;
		}
	}
	else
	{
		// 用投注方法中的条件预生成大底
		if(0 == m_tabNumBase.GetCurSel())	// 选择号码 
			m_page1.GetBase(&pApp->aBase);
		else // 使用大底
			m_page2.GetBase(&pApp->aBase);
	}

	// 条件页面初始化
	m_Cond1.ReadPara();
	m_Cond2.ReadPara();
	m_Cond3.ReadPara();
	m_Cond4.ReadPara();
	m_Cond5.ReadPara();

	int err1, err2, err3, err4, err5;	// 页内容错计数
	int err = 0;						// 全局容错计数
	int i = 0;
	while(i < pApp->aBase.GetSize() )
	{
		err = err1 = err2 = err3 = err4 = err5 = 0;

		// 常规条件
		if(m_Cond1.IsValid())
		{
			err1 = m_Cond1.FilterNum( pApp->aBase.GetAt(i), nOffset );

			if( err1 > m_Cond1.m_cmbAllowError.GetCurSel() )
			{
				if(!bCtrl)
				{
					pApp->aBase.RemoveAt(i);
					continue;
				}
			}
		}
		// 形态条件
		if(m_Cond2.IsValid())
		{
			err2 = m_Cond2.FilterNum( pApp->aBase.GetAt(i), nOffset );
			if( err2 > m_Cond2.m_cmbAllowError.GetCurSel() )
			{
				if(!bCtrl)
				{
					pApp->aBase.RemoveAt(i);
					continue;
				}
			}
		}
		// 其它条件
		if(m_Cond3.IsValid())
		{
			err3 = m_Cond3.FilterNum( pApp->aBase.GetAt(i), nOffset );
			if( err3 > m_Cond3.m_cmbAllowError.GetCurSel() )
			{
				if(!bCtrl)
				{
					pApp->aBase.RemoveAt(i);
					continue;
				}
			}
		}
		// 定位条件
		if(m_Cond4.IsValid())
		{
			err4 = m_Cond4.FilterNum( pApp->aBase.GetAt(i), nOffset );
			if( err4 > m_Cond4.m_cmbAllowError.GetCurSel() )
			{
				if(!bCtrl)
				{
					pApp->aBase.RemoveAt(i);
					continue;
				}
			}
		}
		// 范围条件
		if(m_Cond5.IsValid())
		{
			err5 = m_Cond5.FilterNum( pApp->aBase.GetAt(i), nOffset );
			if( err5 > m_Cond5.m_cmbAllowError.GetCurSel() )
			{
				if(!bCtrl)
				{
					pApp->aBase.RemoveAt(i);
					continue;
				}
			}
		}

		// 全局容错
		if( err1 + err2 + err3 + err4 + err5 > m_cmbAllowErrorAll.GetCurSel() )
		{
			if(!bCtrl)
			{
				pApp->aBase.RemoveAt(i);
				continue;
			}
		}
		// 页面容错
		err = (err1 > 0) + (err2 > 0) + (err3 > 0) + (err4 > 0) + (err5 > 0);
		if( err > m_cmbAllowErrorPage.GetCurSel() )
		{
			if(!bCtrl)
			{
				pApp->aBase.RemoveAt(i);
				continue;
			}
		}
		++i;		
	}
	if( !bCtrl )
	{
		// 号码分类，与显示
		pApp->DispatchNum();
		DisplayResult();
		DisplaySummary();
		
		// 选择结果页
		if(pApp->aResult[0].GetSize() > 0)
		{
			m_tabResult.SetCurSel(0);
		}
		else if(pApp->aResult[1].GetSize() > 0)
		{
			m_tabResult.SetCurSel(1);
		}
		else if(pApp->aResult[2].GetSize() > 0)
		{
			m_tabResult.SetCurSel(2);
		}
		
		// 使用按钮
		EnableButton();
		
		// 替换大底
		if(IsAutoBase())
		{
			ReplaceBase();
		}
	}
	else // 条件验证结果
	{
		err = err1 + err2 + err3 + err4 + err5;
		CString str = CString(_T("最新开奖号码 = ")) + pHistory->GetCNum(0).ToString()
			+ _T("\n")
			+ _T("\n常规条件错误 = ") + EMFC::Int2Str(err1) + _T("　容错 = ") + EMFC::Int2Str( m_Cond1.m_cmbAllowError.GetCurSel() ) + (err1 > m_Cond1.m_cmbAllowError.GetCurSel() ? _T("　×") : _T("　　"))
			+ _T("\n其它条件错误 = ") + EMFC::Int2Str(err3) + _T("　容错 = ") + EMFC::Int2Str( m_Cond3.m_cmbAllowError.GetCurSel() ) + (err3 > m_Cond3.m_cmbAllowError.GetCurSel() ? _T("　×") : _T("　　"))
			+ _T("\n形态条件错误 = ") + EMFC::Int2Str(err2) + _T("　容错 = ") + EMFC::Int2Str( m_Cond2.m_cmbAllowError.GetCurSel() ) + (err2 > m_Cond2.m_cmbAllowError.GetCurSel() ? _T("　×") : _T("　　"))
			+ _T("\n定位条件错误 = ") + EMFC::Int2Str(err4) + _T("　容错 = ") + EMFC::Int2Str( m_Cond4.m_cmbAllowError.GetCurSel() ) + (err4 > m_Cond4.m_cmbAllowError.GetCurSel() ? _T("　×") : _T("　　"))
			+ _T("\n范围条件错误 = ") + EMFC::Int2Str(err5) + _T("　容错 = ") + EMFC::Int2Str( m_Cond5.m_cmbAllowError.GetCurSel() ) + (err5 > m_Cond5.m_cmbAllowError.GetCurSel() ? _T("　×") : _T("　　"))
			+ _T("\n")
			+ _T("\n全局条件错误 = ") + EMFC::Int2Str(err) + _T("　容错 = ") + EMFC::Int2Str( m_cmbAllowErrorAll.GetCurSel() ) + (err > m_cmbAllowErrorAll.GetCurSel() ? _T("　×") : _T("　　"))
			;

		err = (err1 > 0) + (err2 > 0) + (err3 > 0) + (err4 > 0) + (err5 > 0);
		str += _T("\n累计页面错误 = ") + EMFC::Int2Str(err) + _T("　容错 = ") + EMFC::Int2Str( m_cmbAllowErrorPage.GetCurSel() ) + (err > m_cmbAllowErrorPage.GetCurSel() ? _T("　×") : _T("　　"));

		if( err1 <= m_Cond1.m_cmbAllowError.GetCurSel()
			&& err2 <= m_Cond2.m_cmbAllowError.GetCurSel()
			&& err3 <= m_Cond3.m_cmbAllowError.GetCurSel()
			&& err4 <= m_Cond4.m_cmbAllowError.GetCurSel()
			&& err5 <= m_Cond5.m_cmbAllowError.GetCurSel()
			&& err <= m_cmbAllowErrorPage.GetCurSel()
			&& err1 + err2 + err3 + err4 + err5 <= m_cmbAllowErrorAll.GetCurSel()
			)
		{
			str += _T("\n\n恭喜您中奖了!");
		}

		CString strCaption = _T("当期条件验证");
		MessageBox(str, strCaption, MB_OK);
	}
	
	GetDlgItem(IDOK)->SetWindowText( _T("过滤") );
	UpdateData(FALSE);
}

/*
 *	刷新过滤结果列表框
 */
void CMy3DDlg::DisplayResult()
{
	m_pageG6.RefreshList();
	m_pageG3.RefreshList();
	m_pageG1.RefreshList();
	
	UpdateData(FALSE);
}

/*
 *	操作概要信息
 */
VOID CMy3DDlg::DisplaySummary()
{
	UINT nG6 = pApp->aResult[0].GetSize();
	UINT nG3 = pApp->aResult[1].GetSize();
	UINT nG1 = pApp->aResult[2].GetSize();
	UINT cnt = nG6 + nG3 + nG1;

	m_strTip1.Format(_T("%-4d 注,共 %-4d 元"), nG6, nG6 << 1);
	m_strTip2.Format(_T("%-4d 注,共 %-4d 元"), nG3, nG3 << 1);
	m_strTip3.Format(_T("%-4d 注,共 %-4d 元"), nG1, nG1 << 1);
	m_strTip4.Format(_T("%-4d 注,共 %-4d 元"), cnt, cnt << 1);
	
	UpdateData(FALSE);
}

/*
 *	[单转组] 按钮
 */
void CMy3DDlg::OnSingleToGroup() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if( m_bUnite )
	{   
		C3D::S2G(pApp->aResult[0]);
		C3D::S2G(pApp->aResult[1]);
	}
	else
	{
		C3D::S2G(pApp->aResult[m_tabResult.GetCurSel()]);
	}
	
	DisplayResult();
	DisplaySummary();
	EnableButton();
}

/*
 *	[组转单] 按钮
 */
void CMy3DDlg::OnGroupToSingle() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if( m_bUnite )
	{   
		C3D::G2S(pApp->aResult[0]);
		C3D::G2S(pApp->aResult[1]);
	}
	else
	{
		C3D::G2S(pApp->aResult[m_tabResult.GetCurSel()]);
	}
	
	DisplayResult();
	DisplaySummary();
	EnableButton();
}

/*
 *	[加到大底] 按钮
 */
void CMy3DDlg::OnSentToBase() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if( m_bUnite )
	{
		AddToBase(0);
		AddToBase(1);
		AddToBase(2);
	}
	else
	{
		AddToBase(m_tabResult.GetCurSel());
	}
}

/*
 *	选择彩票类型
 */
void CMy3DDlg::OnSelectLottery(UINT nID)
{
	ASSERT(nID >= IDC_RADIO_P3 && nID <= IDC_RADIO_3D);

	UpdateData(TRUE);

	if(m_iLotType != m_iOldType)
	{
		m_iOldType = m_iLotType;

		ReadHistory();
		SetTitle();
	}
}

/*
 *	设置窗口标题文字
 */
void CMy3DDlg::SetTitle()
{
	CString strCaption, str;
	strCaption.LoadString(IDS_TITLE);
	str.LoadString(IDS_VERSION);
	str = str.Left(3);
	strCaption += CString(_T(" ")) + str;

	// 彩票类型
	str.LoadString(IDS_TITLE1 + Is3D());
	strCaption += CString(_T("　")) + str;

	// 上期开奖记录
	UINT nCount = pHistory->GetCount();
	if(1 <= nCount)
	{
		strCaption += _T(" [") + pHistory->GetPeriodStr(0).Right(5) + _T("]=[")
			+ pHistory->GetNumStr(0) + _T("]");

		CString sHot, sWarm, sCool;
		pHistory->HotNum(0, sHot, sWarm, sCool, pApp->iHot);
		strCaption += CString(_T(" [热]=[")) +  sHot + _T("]")
			_T(" [温]=[") + sWarm + _T("]") + _T(" [冷]=[") + sCool + _T("]");
	}
	
	SetWindowText(strCaption);
}

/*
 *	[倍投计算] 按钮
 */
void CMy3DDlg::OnMutiCalc() 
{
	// TODO: Add your control notification handler code here
	CString strCmd = WND::GetAbsPath() + _T("\\LotPlan.exe");

	if( WND::IsExistFile(strCmd) )
	{
		ShellExecute(NULL, _T("open"), strCmd, NULL, NULL, SW_SHOWNORMAL);				
	}
	else
	{
		CString strCaption;
		strCaption.LoadString(IDS_TITLE);
		if( IDYES == MessageBox(_T("找不到以下文件:\n") + strCmd + _T("\n\n您机器上的醉排三需要更新, 现更新吗?"),
			strCaption, MB_YESNO | MB_ICONWARNING) )
		{
			OnCheckUpdate();
		}
	}
}

/*
 *	[保存...] 按钮
 */
void CMy3DDlg::OnSaveFile() 
{
	// TODO: Add your control notification handler code here
	CSaveOption dlg;
	dlg.m_bSaveAndOpen = (1 == pApp->iSaveAndOpen);
	dlg.DoModal();
}

/*
 *	[录入数据] 按钮
 */
void CMy3DDlg::OnDataInput() 
{
	// TODO: Add your control notification handler code here

	CDataInput dlg;
	dlg.DoModal();
}

/*
 *	[数据分析] 按钮
 */
void CMy3DDlg::OnDataAnalyse() 
{
	// TODO: Add your control notification handler code here
	if(pHistory->IsNull())
	{
		CString str;
		str.LoadString(IDS_TITLE);
		MessageBox(_T("历史记录为空。"), str, MB_ICONINFORMATION);
		return;
	}
		
	CDataAnalyse dlg;
	dlg.DoModal();
}

/*
 *	[帮助] 按钮
 */
void CMy3DDlg::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CString strCmd = WND::GetAbsPath() + _T("\\Help.chm");
	
	if( WND::IsExistFile(strCmd) )
	{
		ShellExecute(NULL, _T("open"), strCmd, NULL, NULL, SW_SHOWNORMAL);
// 		WND::WinExec(strCmd);
	}
	else
	{
		CString strCaption;
		strCaption.LoadString(IDS_TITLE);
		if( IDYES == MessageBox(_T("找不到以下文件:\n") + strCmd + _T("\n\n您机器上的醉排三需要更新, 现更新吗?"),
			strCaption, MB_YESNO | MB_ICONWARNING) )
		{
			OnCheckUpdate();
		}
	}
}

BOOL CMy3DDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	// 当前条件保存到临时文件
	CString strFile;
	strFile = WND::GetAbsPath() + _T("\\temp.ini");
	CondSave(strFile);

	if(pApp->iMinToTray > 0)
		DeleteIcon();

	KillTimer(_TIMER_REFRESH_BTN_OK_);
	return CDialog::DestroyWindow();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rc;
	TCHAR tczDate[] = __DATE__;

	GetWindowRect(&rc);
	ClientToScreen(&rc);
	cx = rc.Width();
	cy = rc.Height();
	
	SetWindowPos(0, 0, 0, cx, cyMin, SWP_NOMOVE | SWP_NOZORDER);
	bMost = FALSE;
	
	// 标题栏
	CString str, ss;
	ss.LoadString(IDS_TITLE);
	str = CString(_T("关于 ")) + ss/* + _T("  (体彩排列三/福彩3D)过滤软件")*/;
	SetWindowText(str);

	// 软件名称 + 版本号 + 编译日期
	str = ss;
	ss.LoadString(IDS_VERSION);
	str = str + CString(_T("(C) ")) + ss + CString(_T("  ")) + tczDate;
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(str);

	// 主页链接
	lnkHomePage.Attach(GetDlgItem(IDC_STATIC_HOME)->GetSafeHwnd());
	lnkHomePage.SetLink(_T("访问网站"), _T("https://seanto.github.io/"), TRUE);

	// 邮件
	lnkMail.Attach(GetDlgItem(IDC_STATIC_MAIL)->GetSafeHwnd());
	lnkMail.SetLink(_T("反馈BUG"), _T("https://github.com/SeanTo/My3D"), TRUE);

	// 致谢
	for(UINT i = 0; i < THANKS; ++i)
	{
		GetDlgItem(IDC_STATIC_NAME1 + i)->SetWindowText(strName[i]);
		if(0 == strUrl[i].GetLength())
		{
			GetDlgItem(IDC_STATIC_URL1 + i)->SetWindowText(strTip[i]);
		}
		else
		{
			lnk[i].Attach(GetDlgItem(IDC_STATIC_URL1 + i)->GetSafeHwnd());
			lnk[i].SetLink(strTip[i], strUrl[i], TRUE);
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*
 *	[关于] 按钮
 */
void CMy3DDlg::OnBtnAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}

/*
 *	[文件交集] 按钮
 */
void CMy3DDlg::OnInterFile() 
{
	// TODO: Add your control notification handler code here
	CIntersection dlg;
	dlg.DoModal();
	
	DisplayResult();
	DisplaySummary();
	
	// 使用按钮
	EnableButton();
}

/*
 *	[自动荐底] 按钮
 */
void CMy3DDlg::OnAutoBase()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CAutoBase dlg;
	int iRet = dlg.DoModal();

	if( IDOK == iRet )
		m_tabNumBase.SetCurSel(1);

	UpdateData(FALSE);
}

/*
 *	[交集] 按钮
 */
void CMy3DDlg::OnInterBase() 
{
	// TODO: Add your control notification handler code here
	m_tabNumBase.SetCurSel(1);
	
	m_page2.GetBase(&pApp->aBase);
	if(0 == pApp->aBase.GetSize())
	{
		CString str;
		str.LoadString(IDS_TITLE);
		MessageBox(_T("大底编辑框为空！"), str, MB_ICONINFORMATION);
		return;
	}

	for(int i = 0; i < 3; ++i)
	{
		EMFC::IntersectArray( pApp->aResult[i], pApp->aBase );
	}

	DisplayResult();
	DisplaySummary();
	EnableButton();
	
	if(IsAutoBase())
	{
		ReplaceBase();
	}
}

/*
 *	[差集]按钮
 */
void CMy3DDlg::OnExcludeBase() 
{
	// TODO: Add your control notification handler code here

	m_tabNumBase.SetCurSel(1);

	UpdateData(FALSE);
	
	m_page2.GetBase(&pApp->aBase);
	if(0 == pApp->aBase.GetSize())
	{
		CString str;
		str.LoadString(IDS_TITLE);
		MessageBox(_T("大底编辑框为空！"), str, MB_ICONINFORMATION);
		return;
	}
	
	for(int i = 0; i < 3; ++i)
	{
// 		ExcludeBase(&pApp->aResult[i], &pApp->aBase);
		EMFC::ExcludeArray( pApp->aResult[i], pApp->aBase );
	}
	
	DisplayResult();
	DisplaySummary();
	EnableButton();
	
	if(IsAutoBase())
	{
		ReplaceBase();
	}
}

/*
 *	更新按使能状态
 */
VOID CMy3DDlg::EnableButton()
{
	UpdateData(TRUE);

	BOOL bG6 = pApp->aResult[0].GetSize() > 0;
	BOOL bG3 = pApp->aResult[1].GetSize() > 0;
	BOOL bG1 = pApp->aResult[2].GetSize() > 0;
	
	BOOL bValid;
	int iSelResult = m_tabResult.GetCurSel();
	
	// 保存、分析结果、交集、差集(针对全部结果，非空时有效)
	bValid = bG6 || bG3 || bG1;
	GetDlgItem(IDC_SAVE_FILE)->EnableWindow(bValid);
//	GetDlgItem(IDC_ANALYSE_RESULT)->EnableWindow(bValid);
	GetDlgItem(IDC_INTER_BASE)->EnableWindow(bValid);
	GetDlgItem(IDC_EXCLUDE_BASE)->EnableWindow(bValid);

	// 单组选转换(针对组六/三，结果非空时有效)
	bValid = iSelResult == 0 && bG6
		|| iSelResult == 1 && bG3;
	GetDlgItem(IDC_SINGLE_TO_GROUP)->EnableWindow(bValid);
	GetDlgItem(IDC_GROUP_TO_SINGLE)->EnableWindow(bValid);

	// 加入大底(针对当前选择的形态，结果非空时有效
	bValid = iSelResult == 0 && bG6
		|| iSelResult == 1 && bG3
		|| iSelResult == 2 && bG1;
	GetDlgItem(IDC_SENT_TO_BASE)->EnableWindow(bValid);

	// 手动再删
	bValid = 0 == iSelResult && bG6 && -1 != m_pageG6.GetCurSel()
		|| 1 == iSelResult && bG3 && -1 != m_pageG3.GetCurSel()
		|| 2 == iSelResult && bG1 && -1 != m_pageG1.GetCurSel();
	GetDlgItem(IDC_BTN_HAND_DEL)->EnableWindow(bValid);
}

/*
 *	过滤结果属性页单击响应事件
 */
void CMy3DDlg::OnSelchangeTabResult(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	EnableButton();
	
	*pResult = 0;
}

/*
 *	[走势分析] 按钮
 */
void CMy3DDlg::OnAnalyseTrend() 
{
	// TODO: Add your control notification handler code here

	CDataChart dlg;

	switch(m_tabCond.GetCurSel())
	{
	case 1:
		dlg.SetType(27);
		break;
	case 2:
		dlg.SetType(21);
		break;
	default:
		break;
	}
	dlg.DoModal();
}

/*
 *	[检查更新]按钮
 */
void CMy3DDlg::OnCheckUpdate() 
{
	// TODO: Add your control notification handler code here
	CString strExeFile = WND::GetAbsPath() + _T("\\LiveUpdate.exe");
	CString strIniFile = WND::GetAbsPath() + _T("\\LiveUpdate.ini");
	
	CString strCaption;
	strCaption.LoadString(IDS_TITLE);


	if( !WND::IsExistFile(strIniFile) || !WND::IsExistFile(strExeFile) )
	{
		if( IDYES == MessageBox(_T("更新程序不完整:\n") + strExeFile + _T("\n")
			+ strIniFile + _T("\n") + _T("\n请访问网页手动检查更新，现在检查吗?"),
			strCaption, MB_YESNO | MB_ICONQUESTION ) )
		{
			ShellExecute(NULL, _T("open"),
				_T("http://www.tuxw.cn/blog/article.asp?id=50"),
				NULL, NULL, SW_SHOWNORMAL);
		}

		return;
	}

	if(IDYES == MessageBox(_T("该操作会关闭本软件并启动更新程序，\n更新结束后本软件会重新运行。")
		, strCaption, MB_YESNO | MB_ICONQUESTION) )
	{
		ShellExecute(NULL, _T("open"), strExeFile, NULL, NULL, SW_SHOWNORMAL);
		CDialog::OnCancel();
	}
}

/*
 *	[保存条件] 按钮
 */
void CMy3DDlg::OnCondSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString strFile = WND::GetAbsPath(TRUE);

	// 保存为默认设置
	if( WND::IsCtrlDown() )
	{
		strFile += _T("My3D.ini");
		CondSave(strFile, TRUE);

		AfxMessageBox(CString(_T("当前设置已保存为默认值\n\n"))
			+ _T("以后点[复位]时将恢复此设置\n完全复位请按住CTRL键再点[复位]"), 
			MB_OK, MB_ICONINFORMATION);
		return;
	}

	// 导出
	if( m_bSaveAsOpenCond )
	{
		int iPeriod = pHistory->IsNull() ? 1 : pHistory->GetPeriod(0) + 1;

		CString strName;
		strName.Format(_T("Output\\%s-过滤器-%07d.ini"), Is3D() ? _T("3D") : _T("P3"), iPeriod);
		strFile += strName;
		strFile = WND::SelectFile(FALSE, strFile, _T("ini"), _T("配置文件(*.ini)|*.ini||"));
	}
	else
		strFile += _T("temp.ini");

	// 写文件
	if( !strFile.IsEmpty() )
	{
		if( !WND::IsExistFile(strFile) )
		{
			CStdioFile fin(strFile, CFile::modeCreate | CFile::modeWrite | CFile::typeText );			
			fin.Close();
		}
		CondSave(strFile);
		m_bSaveAsOpenCond = FALSE;
		UpdateData(FALSE);
	}
}

/*
 *	[读取条件] 按钮
 */
void CMy3DDlg::OnCondRead() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strFile = WND::GetAbsPath(TRUE);
	//strFile = CString(pApp->GetPath()) + _T("\\temp.ini");

	// 导入
	if( m_bSaveAsOpenCond )
	{
		int iPeriod = pHistory->IsNull() ? 1 : pHistory->GetPeriod(0) + 1;

		CString strName;
		strName.Format(_T("Output\\%s-过滤器-%07d.ini"), Is3D() ? _T("3D") : _T("P3"), iPeriod);
		strFile += strName;
		strFile = WND::SelectFile(TRUE, strFile, _T("ini"), _T("配置文件(*.ini)|*.ini||"));
	}
	else 
		strFile += _T("temp.ini");

	// 读文件
	if( !strFile.IsEmpty() )
	{
		m_bSaveAsOpenCond = FALSE;
		CondRead(strFile);
	}

	if( m_iOldType != m_iLotType )
	{
		ReadHistory();
		SetTitle();
		m_iOldType = m_iLotType;
	}

	UpdateData(FALSE);
}

/*
 *	[复位条件] 按钮
 */
void CMy3DDlg::OnCondReset() 
{
	// TODO: Add your control notification handler code here

	if( WND::IsCtrlDown() )
	{
		m_page1.Init();
		m_Cond1.Init();
		m_Cond2.Init();
		m_Cond3.Init();
		m_Cond4.Init();
		m_Cond5.Init();
		Init();
	}
	else
	{
		CString strFile = WND::GetAbsPath(TRUE) + _T("My3D.ini");
		CondRead(strFile);
	}
	
	if( m_iOldType != m_iLotType )
	{
		ReadHistory();
		SetTitle();
		m_iOldType = m_iLotType;
	}
	
	UpdateData(FALSE);
}

/*
 *	[号码分布] 按钮
 */
void CMy3DDlg::OnDistribute() 
{
	// TODO: Add your control notification handler code here
	CDataDistribute dlg;
	dlg.DoModal();
}

/*
 *	从“其它”属性页中读取分析期数
 */
UINT CMy3DDlg::GetPeriods()
{
	UpdateData(TRUE);

	int iCountHistory = pHistory->GetCount();
	if(0 == iCountHistory)
		return 0;

	int iPeriodCnt = m_iStatPeriods;
	if(iPeriodCnt < 0 )
	{
		m_iStatPeriods = -1;
		iPeriodCnt = pHistory->GetPeriod(0) % 1000;
		if(iPeriodCnt < 30 && pHistory->GetCount() >= 30)
			iPeriodCnt = 30;
	}
	else if(0 == iPeriodCnt || iPeriodCnt > iCountHistory)
	{
		m_iStatPeriods = 0;
		iPeriodCnt = iCountHistory;
	}

	UpdateData(FALSE);
	
	return iPeriodCnt;
}

/*
 *	[战绩] 按钮
 */
void CMy3DDlg::OnAnalyseResult() 
{
	// TODO: Add your control notification handler code here
	if(pHistory->IsNull())
	{
		CString str;
		str.LoadString(IDS_TITLE);
		MessageBox(_T("历史记录为空。"), str, MB_ICONINFORMATION);
		return;
	}
	
	// 当前结果+固定大底
 	CString strHeader = _T("过滤结果,60;半顺,36;杂六,36;组三,36;组六偶和,60;组六奇和,60;正常和,48;大和,36;小和,36;");
	int iWidth = 60 + 36 + 36 + 36 + 60 + 60 + 48 + 36 + 36;
	int iBaseCnt = 9;
	
	// 自定义大底
	CString str, ss;
	iBaseCnt += m_page2.m_cmbBase.GetCount() - 12;
	
	int iWid;
	for(int i = 0; i < iBaseCnt - 9; ++i)
	{
		ss = m_page2.m_strName[i];
		iWid = (ss.GetLength() - 4) * 6 + 36;
		str.Format(_T(",%d;"), iWid);

		strHeader += ss + str;
		iWidth += iWid;
	}

	// 统计期数
	UINT nPeriodCnt = GetPeriods();
	CUIntArray aNumber;
	CUIntArray aRes0, aRes1, aRes2, aRes3, aRes4, aRes5, aRes6, aRes7, aRes8;
	CUIntArray aRes9, aRes10, aRes11, aRes12, aRes13, aRes14, aRes15, aRes16, aRes17, aRes18;

	// 分析当前结果
	pApp->CompoundNum(aNumber);
	if( 0 == aNumber.GetSize() )
	{
		for(int i = 0; i < 7; ++i)
			aRes0.Add(0);
	}
	else
		pHistory->Success(aNumber, nPeriodCnt, aRes0);
		
	// 半顺
	m_page2.GetBase(&aNumber, m_page2.LoadProBase(1, FALSE));
	pHistory->Success(aNumber, nPeriodCnt, aRes1);
	// 杂六
	m_page2.GetBase(&aNumber, m_page2.LoadProBase(2, FALSE));
	pHistory->Success(aNumber, nPeriodCnt, aRes2);
	// 组三
	m_page2.GetBase(&aNumber, m_page2.LoadProBase(4, FALSE));
	pHistory->Success(aNumber, nPeriodCnt, aRes3);
	// 组六偶和
	m_page2.GetBase(&aNumber, m_page2.LoadProBase(6, FALSE));
	pHistory->Success(aNumber, nPeriodCnt, aRes4);
	// 组六奇和
	m_page2.GetBase(&aNumber, m_page2.LoadProBase(7, FALSE));
	pHistory->Success(aNumber, nPeriodCnt, aRes5);
	// 正常和
	m_page2.GetBase(&aNumber, m_page2.LoadProBase(8, FALSE));
	pHistory->Success(aNumber, nPeriodCnt, aRes6);
	// 大和
	m_page2.GetBase(&aNumber, m_page2.LoadProBase(9, FALSE));
	pHistory->Success(aNumber, nPeriodCnt, aRes7);
	// 小和
	m_page2.GetBase(&aNumber, m_page2.LoadProBase(10, FALSE));
	pHistory->Success(aNumber, nPeriodCnt, aRes8);

	// 分析自定义大底
	switch(iBaseCnt)
	{
	case 19:
		m_page2.GetBase(&aNumber, m_page2.m_strBaseStr[9]);
		pHistory->Success(aNumber, nPeriodCnt, aRes18);
	case 18:
		m_page2.GetBase(&aNumber, m_page2.m_strBaseStr[8]);
		pHistory->Success(aNumber, nPeriodCnt, aRes17);
	case 17:
		m_page2.GetBase(&aNumber, m_page2.m_strBaseStr[7]);
		pHistory->Success(aNumber, nPeriodCnt, aRes16);
	case 16:
		m_page2.GetBase(&aNumber, m_page2.m_strBaseStr[6]);
		pHistory->Success(aNumber, nPeriodCnt, aRes15);
	case 15:
		m_page2.GetBase(&aNumber, m_page2.m_strBaseStr[5]);
		pHistory->Success(aNumber, nPeriodCnt, aRes14);
	case 14:
		m_page2.GetBase(&aNumber, m_page2.m_strBaseStr[4]);
		pHistory->Success(aNumber, nPeriodCnt, aRes13);
	case 13:
		m_page2.GetBase(&aNumber, m_page2.m_strBaseStr[3]);
		pHistory->Success(aNumber, nPeriodCnt, aRes12);
	case 12:
		m_page2.GetBase(&aNumber, m_page2.m_strBaseStr[2]);
		pHistory->Success(aNumber, nPeriodCnt, aRes11);
	case 11:
		m_page2.GetBase(&aNumber, m_page2.m_strBaseStr[1]);
		pHistory->Success(aNumber, nPeriodCnt, aRes10);
	case 10:
		m_page2.GetBase(&aNumber, m_page2.m_strBaseStr[0]);
		pHistory->Success(aNumber, nPeriodCnt, aRes9);
	}
		
	CWinHistory dlg(_T("战绩统计"), nPeriodCnt);
	dlg.AddColumn(strHeader, iBaseCnt, iWidth);
	dlg.SetStatData(&aRes0, &aRes1, &aRes2, &aRes3, &aRes4, &aRes5, &aRes6, &aRes7, &aRes8,
		aRes9.GetSize() >= 7 ? &aRes9 : NULL,
		aRes10.GetSize() >= 7 ? &aRes10 : NULL,
		aRes11.GetSize() >= 7 ? &aRes11 : NULL,
		aRes12.GetSize() >= 7 ? &aRes12 : NULL,
		aRes13.GetSize() >= 7 ? &aRes13 : NULL,
		aRes14.GetSize() >= 7 ? &aRes14 : NULL,
		aRes15.GetSize() >= 7 ? &aRes15 : NULL,
		aRes16.GetSize() >= 7 ? &aRes16 : NULL,
		aRes17.GetSize() >= 7 ? &aRes17 : NULL,
		aRes18.GetSize() >= 7 ? &aRes18 : NULL
		);

	dlg.DoModal();
}

BOOL CMy3DDlg::ReadVersion(CString &strExe, CString &strMdb, CString &strCalc)
{
	CString strCofigFile;
	strCofigFile.LoadString(IDS_UPDATE_CFG);
	strCofigFile = WND::GetAbsPath(TRUE) + strCofigFile;

	CIniFile fUpdate;
	if( fUpdate.Create(strCofigFile) )
	{
		fUpdate.GetVarStr(_T("UPDATE"), _T("EXE"), strExe);
		fUpdate.GetVarStr(_T("UPDATE"), _T("MDB"), strMdb);
		fUpdate.GetVarStr(_T("UPDATE"), _T("CALCER"), strCalc);

		strExe.TrimLeft();
		strExe.TrimRight();
		strMdb.TrimLeft();
		strMdb.TrimRight();
		strCalc.TrimLeft();
		strCalc.TrimRight();

		if(0 == strExe.GetLength()
			|| 0 == strMdb.GetLength()
			|| 0 == strCalc.GetLength())
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

/*
 * 手动再删
 */
void CMy3DDlg::OnBtnHandDel() 
{
	// TODO: Add your control notification handler code here

	switch(m_tabResult.GetCurSel())
	{
	case 0: // 组六
		m_pageG6.DelCurSel();
		break;
	case 1: // 组三
		m_pageG3.DelCurSel();
		break;
	case 2: // 豹子
		m_pageG1.DelCurSel();
		break;
	}

	DisplaySummary();
	EnableButton();
}

/*
 * 加到大底
 */
VOID CMy3DDlg::AddToBase(UINT type)
{
	m_page2.UpdateData(TRUE);
	
	m_tabNumBase.SetCurSel(1);
	
	CString str1 = _T("");
	CString str2 = _T("");
	for(int i = 0; i < pApp->aResult[type].GetSize(); ++i)
	{
		str2.Format(_T("%03d "), pApp->aResult[type][i]);
		str1 += str2;
	}
	
	m_page2.AddBase(str1);
	m_page2.m_cmbBase.SetCurSel(-1);
}

/*
 *	替换大底
 */
VOID CMy3DDlg::ReplaceBase()
{
	m_page2.SetBase(_T(""));
	
	for(int i=0; i<3; ++i)
	{
		if( pApp->aResult[i].GetSize() > 0 )
			AddToBase(i);
	}
}

VOID CMy3DDlg::ReadHistory()
{
	CString strFile = WND::GetAbsPath(TRUE) + pHistory->GetDmbFileName(1 == m_iLotType);
	
	pHistory->LoadFromFile(strFile, 1 == m_iLotType);
}

/*
 * 捐助信息
 */
void CAboutDlg::OnButtonDonate() 
{
	// TODO: Add your control notification handler code here
	CDonateInfo dlg;
	dlg.DoModal();
	
	OnOK();
}

BOOL CMy3DDlg::AddIcon()
{
	// 在任务条中增加图标
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd; 
	nid.uID = IDR_MAINFRAME; 
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage = UM_ICONNOTIFY;
	nid.hIcon = m_hIcon;
	
	CString str;
	str.LoadString(IDS_TITLE);
	lstrcpyn(nid.szTip, (LPCTSTR)str, sizeof(nid.szTip)/sizeof(nid.szTip[0]));
	
	return Shell_NotifyIcon(NIM_ADD, &nid);
}

BOOL CMy3DDlg::DeleteIcon()
{
	// 删除任务条中的图标
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;
	nid.uID = IDR_MAINFRAME;
	
	return Shell_NotifyIcon(NIM_DELETE, &nid);
}

void CMy3DDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
	// 隐藏窗口
// 	if( ::GetForegroundWindow() != m_hWnd )
// 	{
// 		if(nType == SIZE_MINIMIZED && pApp->iMinToTray > 0)
// 		{
// 			// 隐藏窗口，注意，此时(基类OnSize已将)窗口最小化了
// 			ShowWindow(SW_HIDE);
// 
// 			m_bDisp = FALSE;
// 		}
// 	}
}

LRESULT CMy3DDlg::OnIconNotify(WPARAM wParam, LPARAM lParam)
{
	switch ((UINT)lParam)
	{
		// 右键菜单
	case WM_RBUTTONDOWN:
		{
			// 鼠标单击位置
			CPoint point;
			GetCursorPos(&point);
			// 装入菜单
			LoadContextMenu(point);
		}
		break;
		// 左键恢复窗口
	case WM_LBUTTONDOWN:
		if(!m_bDisp)
		{
//			ShowWindow(SW_SHOW);	// 显示窗口(此时窗口是最小化的)
//			ShowWindow(SW_RESTORE);	// 还原窗口
			WND::ActiveWindow(pApp->GetMyClassName());
		}
		else
			ShowWindow(SW_HIDE);
		
		m_bDisp = !m_bDisp;
		break;
	}

	return 0;
}

void CMy3DDlg::LoadContextMenu(CPoint &point)
{
	// 装入图标操作菜单
	CMenu menu;
	menu.LoadMenu(IDR_MENU_ICON);
	
	// 将背景窗口激活
	SetForegroundWindow();
	
	// 显示图标菜单
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTBUTTON,
		point.x, point.y, this, NULL); 
	
	// 增加一个额外消息，使菜单操作正确
	PostMessage(WM_USER, 0, 0);
}

void CAboutDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
}

/*
 *	[致谢] 按钮 （关于对话框）
 */
void CAboutDlg::OnThank() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CRect rc;
	GetWindowRect(&rc);
	ClientToScreen(&rc);
	SetWindowPos(0, 0, 0, cx, bMost ? cyMin : cy, SWP_NOMOVE | SWP_NOZORDER);

	bMost = !bMost;
	
	GetDlgItem(IDC_THANK)->SetWindowText(bMost ? _T("<< 致谢") : _T("致谢 >>"));
	
	UpdateData(FALSE);
}

void CMy3DDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	if(m_bOnce)
	{
		m_bOnce = FALSE;
		
		CString strCaption;
		strCaption.LoadString(IDS_TITLE);
		if( IDYES == MessageBox(_T("本信息只出现一次！\n\n")
			_T("您愿意捐助本软件吗?\n\n")
			_T("选择 [是] 查看捐助信息...\n")
			_T("选择 [否] 以后再说...\n\n")
			
			_T("5元10元是捐助，1元2元也是捐助，\n")
			_T("用您的1注投注额，支持本软件更加完善。\n")
			_T("是否捐助并不影响你继续使用本软件。\n\n")
			
			_T("感谢您使用本软件！\n")
			, strCaption, MB_YESNO | MB_ICONINFORMATION) )
		{
			OnBtnAbout();
			return;
		}
	}
	
	CDialog::OnCancel();
}

BOOL CMy3DDlg::CondRead(const CString &strFile, BOOL bDefault/* = FALSE*/)
{
	CIniFile fin;
	if( !fin.Create(strFile) )
	{
		CString str;
		str.LoadString(IDS_TITLE);
		MessageBox(_T("读取配置文件错误！"), str, MB_ICONERROR);
		return FALSE;
	}
	
	// 版本检查
	CString strVer;
	fin.GetVarStr(_T("DEFAULT"), _T("配置版本"), strVer);
	strVer.TrimLeft();
	strVer.TrimRight();
	if( 0 != strVer.Left(3).Compare(pApp->strVersion.Left(3)) )
	{
		int iSel = MessageBox(CString(_T("软件版本: ")) + pApp->strVersion
			+ CString(_T("\n配置版本: ")) + strVer
			+ CString(_T("\n\n配置文件版本与当前软件不匹配，有可能存在兼容性问题"))
			+ CString(_T("\n是否继续加载?"))
			+ CString(_T("\n\n如果软件启动时就看到此提示，请选择以下操作之一:"))
			+ CString(_T("\n　①删除My3D.ini后重新运行(自动重建一个默认配置)"))
			+ CString(_T("\n　②启动后先CTFL+[复位]，再CTRL+[保存]，恢复默认配置"))
			+ CString(_T("\n　③在线更新软件"))
			, CString(_T("醉排三")), MB_YESNO | MB_ICONWARNING );

		if(IDNO == iSel)
			return FALSE;
	}
		
	if(bDefault)
	{
		// 最小化到通知区
		fin.GetVarInt(_T("CONFIG"), _T("最小化到通知区"), pApp->iMinToTray);
		// 保存后打开
		fin.GetVarInt(_T("CONFIG"), _T("保存后打开"), pApp->iSaveAndOpen);
		// 推荐警告
		fin.GetVarInt(_T("CONFIG"), _T("推荐警告"), pApp->iWarnRecommand);
		// 推荐警告
		fin.GetVarInt(_T("CONFIG"), _T("确认删除"), pApp->iDeleteTip);
		// 大底作者
		fin.GetVarStr(_T("CONFIG"), _T("大底作者"), pApp->strAuthor);


		// 外部工具1
		CString str;
		fin.GetVarStr(_T("CONFIG"), _T("工具1"), str);
		if( !str.IsEmpty() )
		{
			str.TrimRight();
			str.TrimLeft();
			strExTool1 = str;
			GetDlgItem(IDC_BTN_TEST)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_TEST)->ShowWindow(SW_SHOW);

			fin.GetVarStr(_T("CONFIG"), _T("名字1"), str);
			if( !str.IsEmpty() )
			{
				strExName1 = str;
				GetDlgItem(IDC_BTN_TEST)->SetWindowText( str );
			}

			fin.GetVarStr(_T("CONFIG"), _T("工具2"), str);
			if( !str.IsEmpty() )
			{
				str.TrimRight();
				str.TrimLeft();
				strExTool2 = str;
				GetDlgItem(IDC_BTN_TEST2)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_TEST2)->ShowWindow(SW_SHOW);

				fin.GetVarStr(_T("CONFIG"), _T("名字2"), str);
				if( !str.IsEmpty() )
				{
					strExName2 = str;
					GetDlgItem(IDC_BTN_TEST2)->SetWindowText( str );
				}
			}

		}
	}
	
	int n = 0;
	
	// 彩票类型
	if( fin.GetVarInt(_T("DEFAULT"), _T("彩票类型"), m_iLotType) )
	
	// 投注方法
	if( fin.GetVarInt(_T("DEFAULT"), _T("投注方法"), n) )
		m_tabNumBase.SetCurSel(n < m_tabNumBase.GetItemCount() ? n : 0);
	
	// 当前条件
	if( fin.GetVarInt(_T("DEFAULT"), _T("当前条件"), n) )
		m_tabCond.SetCurSel(n < m_tabCond.GetItemCount() ? n : 0);
		
	// 替换大底
	if( fin.GetVarInt(_T("DEFAULT"), _T("替换大底"), n) )
		m_bReplaceBase = (n != 0);
	
	// 统计战绩
	if( fin.GetVarInt(_T("DEFAULT"), _T("战绩统计"), n) )
		m_iStatPeriods = n;
	
	// 过滤结果页面
	if( fin.GetVarInt(_T("DEFAULT"), _T("过滤结果"), n) )
		m_tabResult.SetCurSel(n < m_tabResult.GetItemCount() ? n : 0);
	
	// 全局容错
	if( fin.GetVarInt(_T("DEFAULT"), _T("全局容错"), n) )
	{
		if(n < 0 || n >= m_cmbAllowErrorAll.GetCount())
			n = m_cmbAllowErrorAll.GetCount() - 1;
		m_cmbAllowErrorAll.SetCurSel(n);
	}
	
	// 页面容错
	if( fin.GetVarInt(_T("DEFAULT"), _T("页面容错"), n) )
	{
		if(n < 0 || n >= m_cmbAllowErrorPage.GetCount())
			n = m_cmbAllowErrorPage.GetCount() - 1;
		m_cmbAllowErrorPage.SetCurSel(n);
	}
		
	// 选择号码
	m_page1.LoadCondition(fin);
	// 常规
	m_Cond1.LoadCondition(fin);
	// 形态
	m_Cond2.LoadCondition(fin);
	// 其它
	m_Cond3.LoadCondition(fin);
	// 定位
	m_Cond4.LoadCondition(fin);
	// 范围
	m_Cond5.LoadCondition(fin);

	UpdateData(FALSE);

	return TRUE;
}

BOOL CMy3DDlg::CondSave(const CString &strFile, BOOL bDefault/* = FALSE*/)
{
	UpdateData(TRUE);

	CIniFile fin;
	if( !fin.Create(strFile) )
	{
		CString str;
		str.LoadString(IDS_TITLE);
		MessageBox(_T("写配置文件错误！\n")+strFile, str, MB_ICONERROR);
		
		return FALSE;
	}

	if(bDefault)
	{
		// 版本、最小化到通知区、保存后打开、推荐警告
		fin.SetVarInt(_T("CONFIG"), _T("最小化到通知区"), pApp->iMinToTray, 0);
		fin.SetVarInt(_T("CONFIG"), _T("保存后打开"), pApp->iSaveAndOpen, 0);
		fin.SetVarInt(_T("CONFIG"), _T("推荐警告"), pApp->iWarnRecommand, 0);
		fin.SetVarInt(_T("CONFIG"), _T("确认删除"), pApp->iDeleteTip, 0);

		// 外部工具
		fin.SetVarStr(_T("CONFIG"), _T("工具1"), strExTool1, 0);
		fin.SetVarStr(_T("CONFIG"), _T("名字1"), strExName1, 0);
		fin.SetVarStr(_T("CONFIG"), _T("工具2"), strExTool2, 0);
		fin.SetVarStr(_T("CONFIG"), _T("名字2"), strExName2, 0);
	}
	
	// 系统设置
	fin.SetVarStr(_T("DEFAULT"), _T("配置版本"), pApp->strVersion, 0);
	fin.SetVarInt(_T("DEFAULT"), _T("彩票类型"), m_iLotType, 0);
	fin.SetVarInt(_T("DEFAULT"), _T("投注方法"), m_tabNumBase.GetCurSel(), 0);
	fin.SetVarInt(_T("DEFAULT"), _T("当前条件"), m_tabCond.GetCurSel(), 0);

	fin.SetVarInt(_T("DEFAULT"), _T("替换大底"), IsAutoBase() ? 1 : 0, 0);
	fin.SetVarInt(_T("DEFAULT"), _T("战绩统计"), m_iStatPeriods, 0);
	fin.SetVarInt(_T("DEFAULT"), _T("全局容错"), m_cmbAllowErrorAll.GetCurSel(), 0);
	fin.SetVarInt(_T("DEFAULT"), _T("页面容错"), m_cmbAllowErrorPage.GetCurSel(), 0);
	fin.SetVarInt(_T("DEFAULT"), _T("过滤结果"), m_tabResult.GetCurSel(), 0);

	// 选择号码
	m_page1.SaveCondition(fin);
	// 常规条件
	m_Cond1.SaveCondition(fin);
	// 形态条件
	m_Cond2.SaveCondition(fin);
	// 其它
	m_Cond3.SaveCondition(fin);
	// 定位
	m_Cond4.SaveCondition(fin);
	// 范围
	m_Cond5.SaveCondition(fin);
	
	return TRUE;
}

/*
 *	[外部工具]按钮1
 */
void CMy3DDlg::OnBtnTest()
{
	CString strCmd = strExTool1;
	
	if( -1 == strCmd.Find(_T(':')) )
		strCmd = WND::GetAbsPath(TRUE) + strCmd;
	
	if( WND::IsExistFile(strCmd) )
	{
		ShellExecute(NULL, _T("open"), strCmd, NULL, NULL, SW_SHOWNORMAL);				
	}
	else
	{
		UINT nRet = AfxMessageBox( _T("找不到外部工具:\n") + strExTool1
			+ _T("\n\n请编辑 My3D.ini，工具1=外部命令\n\n现在就编辑吗？"), MB_YESNO );

		if(IDYES == nRet)
		{
			strCmd = WND::GetAbsPath() + _T("\\My3D.ini") ;
			ShellExecute(NULL, _T("open"), strCmd, NULL, NULL, SW_SHOWNORMAL);
		}
	}
}

/*
 *	[外部工具]按钮1
 */
void CMy3DDlg::OnBtnTest2()
{
	CString strCmd = strExTool2;

	if( -1 == strCmd.Find(_T(':')) )
		strCmd = WND::GetAbsPath(TRUE) + strCmd;

	if( WND::IsExistFile(strCmd) )
	{
		ShellExecute(NULL, _T("open"), strCmd, NULL, NULL, SW_SHOWNORMAL);				
	}
	else
	{
		UINT nRet = AfxMessageBox( _T("找不到外部工具:\n") + strExTool2
			+ _T("\n\n请编辑 My3D.ini，工具1=外部命令\n\n现在就编辑吗？"), MB_YESNO );

		if(IDYES == nRet)
		{
			strCmd = WND::GetAbsPath() + _T("\\My3D.ini") ;
			ShellExecute(NULL, _T("open"), strCmd, NULL, NULL, SW_SHOWNORMAL);
		}
	}
}

void CMy3DDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if( _TIMER_REFRESH_BTN_OK_ == nIDEvent && !WND::IsCtrlDown() )
	{
		GetDlgItem(IDOK)->SetWindowText( _T("过滤") );
	}
	else
	{
		GetDlgItem(IDOK)->SetWindowText( _T("验证") );
	}
//	GetDlgItem(IDOK)->UpdateData(FALSE);
//	GetDlgItem(IDOK)->Invalidate();
	
	CDialog::OnTimer(nIDEvent);
}

BOOL CMy3DDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	
	m_tt.RelayEvent(pMsg); // 按钮悬浮提示
	
	if(WM_KEYDOWN == pMsg->message)
	{
		if(VK_ESCAPE == pMsg->wParam/* || VK_RETURN == pMsg->wParam*/)
		{   
			return TRUE;   
		}
		else if(VK_CONTROL == pMsg->wParam)
		{
			// 按下 CTRL 时，[过滤] 变 [验证]
			GetDlgItem(IDOK)->SetWindowText( _T("验证") );
			return TRUE;
		}
	}
	else if(WM_KEYUP == pMsg->message)
	{
		if(VK_CONTROL == pMsg->wParam)
		{
			// 释放 CTRL 时，[验证] 变 [过滤]
			GetDlgItem(IDOK)->SetWindowText( _T("过滤") );
			return TRUE;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

CString CMy3DDlg::ExportAllComment()
{
	CString str;
	CString strCond = _T("\n=========主要条件描述=========\n");
	
	str = m_Cond1.ExportComment();
	strCond += str;
	if( !str.IsEmpty() )
		strCond += _T("\n");

	str = m_Cond2.ExportComment();
	strCond += str;
	if( !str.IsEmpty() )
		strCond += _T("\n");
		
	str = m_Cond3.ExportComment();
	strCond += str;
	if( !str.IsEmpty() )
		strCond += _T("\n");
	
	str = m_Cond4.ExportComment();
	strCond += str;
	if( !str.IsEmpty() )
		strCond += _T("\n");
	
	str = m_Cond5.ExportComment();
	strCond += str;
	if( !str.IsEmpty() )
		strCond += _T("\n");

	strCond += _T("=========条件描述结束=========");

	return strCond;
}
