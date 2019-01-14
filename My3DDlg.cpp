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

	strName[0] = _T("��Ƥ");
	strTip[0] = _T("INI �����ļ���");
	strUrl[0] = _T("http://www.vckbase.com/code/viewcode.asp?id=1736");

	strName[1] = _T("�Ƴ���");
	strTip[1] = _T("������ҳ����");
	strUrl[1] = _T("http://www.vckbase.com/document/viewdoc/?id=398");

	strName[2] = _T("Javen");
	strTip[2] = _T("IDC Link �ؼ�");
	strUrl[2] = _T("http://blog.csdn.net/jun_01/archive/2007/03/06/1521694.aspx");

	strName[3] = _T("smiletiger");
	strTip[3] = _T("�ɱ���ɫ�������б��");
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

	strExName1 = _T("Ŀ¼");
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
	// Ͷע����������ҳ
	m_tabNumBase.AddPage(_T("ѡ�����"), &m_page1, IDD_DIALOG_NUMBER);
	m_tabNumBase.AddPage(_T("ʹ�ô��"), &m_page2, IDD_DIALOG_BASE);
	m_tabNumBase.Show();
	
	// ��������������ҳ
	m_tabCond.AddPage(_T("����"), &m_Cond1, IDD_COND1);
	m_tabCond.AddPage(_T("����"), &m_Cond3, IDD_COND3);
	m_tabCond.AddPage(_T("��̬"), &m_Cond2, IDD_COND2);
	m_tabCond.AddPage(_T("��λ"), &m_Cond4, IDD_COND4);
	m_tabCond.AddPage(_T("��Χ"), &m_Cond5, IDD_COND5);
//	m_tabCond.AddPage(_T("�Զ���"), &m_Cond6, IDD_COND6);
	m_tabCond.Show();
	
	// ���˽��������ҳ
	m_tabResult.AddPage(_T("����"), &m_pageG6, IDD_DIALOG_G6);
	m_tabResult.AddPage(_T("����"), &m_pageG3, IDD_DIALOG_G3);
	m_tabResult.AddPage(_T("����"), &m_pageG1, IDD_DIALOG_G1);
	m_tabResult.Show();
	
	CString str;
	
	// ȫ���ݴ�
	for(int i = 0; i <= 300; ++i)
	{
		str.Format(_T("%d"), i);
		m_cmbAllowErrorAll.AddString(str);
	}
	// ҳ���ݴ�
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
	// ��Ļ��С
	CPaintDC dc(this); 
	int cx = ::GetDeviceCaps(dc.m_hDC, HORZRES); //��Ļ���
	int cy = ::GetDeviceCaps(dc.m_hDC, VERTRES); //��Ļ�߶�
	
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

	
	// ��ť������ʾ
	EnableToolTips(TRUE);
	m_tt.Create(this);
	m_tt.Activate(TRUE);
			
	m_tt.SetMaxTipWidth(250); //��ʾ�����п�ȣ��Ǳ���
	m_tt.SetTipTextColor(RGB(0,0,255)); //��ʾ������ɫ���Ǳ���
//	m_tt.SetDelayTime(100);    //��ʾ��ʾʱ�䣬�Ǳ���

	m_tt.AddTool(GetDlgItem(IDC_CHK_REPLACE_BASE),"��ѡ��, ����������ť�Ĳ�������Ḵ�Ƶ���ױ༭���С�����Ӱ���ױ༭���е����ݡ�");
	m_tt.AddTool(GetDlgItem(IDC_CHK_UNITE),"��ѡ��, ����������ť���������������������̬ͬʱ����������ֻ�뵱ǰ�������̬������");
	
	m_tt.AddTool(GetDlgItem(IDC_INTER_BASE),"���˽�� = ���˽�� �� ��ױ༭��");
	m_tt.AddTool(GetDlgItem(IDC_EXCLUDE_BASE),"���˽�� = ���˽�� �� ��ױ༭��");

	m_tt.AddTool(GetDlgItem(IDC_SINGLE_TO_GROUP),"���˽��ת����ѡ (ע��������̬��ѡ��״̬)");
	m_tt.AddTool(GetDlgItem(IDC_GROUP_TO_SINGLE),"���˽��ת��ֱѡ (ע��������̬��ѡ��״̬)");
	m_tt.AddTool(GetDlgItem(IDC_SENT_TO_BASE),"��ױ༭�� = ��ױ༭�� + ���˽��");
	
	InitOnce();
	GetScreenInfo();
	Init();

	CString strCfgFile = WND::GetAbsPath() + _T("\\My3D.ini");

	// ���Ĭ�������ļ��Ƿ���ڣ���������ڣ��ʹ���һ��
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

	// ������ʱ�����ļ�
	if( !WND::IsExistFile(strCfgFile) )
	{
		CStdioFile fini;
		if( fini.Open(strCfgFile, CFile::modeCreate | CFile::modeWrite | CFile::typeText) )
			fini.Close();
	}
	
	ReadHistory();		// ��ȡ��ʷ��¼
	SetTitle();			// ���ñ�����
	m_iOldType = m_iLotType;
	
	DisplaySummary();	// ��ʾ�����Ҫ��Ϣ
	EnableButton();		// ʹ�ܰ�ť

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
 *	[����] ��ť
 */
void CMy3DDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

// 	AfxMessageBox(ExportAllComment());
// 	return;

	int nOffset = 0;

	// ��ʷ����
	if( WND::IsShiftDown() )
		nOffset = 1; // ����һ����ʷ���ݹ���

	// ��ס CTRL ��ֻ��������������֤
	BOOL bCtrl = WND::IsCtrlDown();
	
	// Ԥ���ɴ��
	pApp->aBase.RemoveAll();

	if( bCtrl )
	{
		// ��֤����
		// �����µĿ���������Ϊ���
		nOffset = 1;
		if( pHistory->GetCount() > nOffset )
			pApp->aBase.Add( pHistory->GetNum(0) );
		else
		{
			AfxMessageBox(_T("�޿������ݣ�������֤������"));
			return;
		}
	}
	else
	{
		// ��Ͷע�����е�����Ԥ���ɴ��
		if(0 == m_tabNumBase.GetCurSel())	// ѡ����� 
			m_page1.GetBase(&pApp->aBase);
		else // ʹ�ô��
			m_page2.GetBase(&pApp->aBase);
	}

	// ����ҳ���ʼ��
	m_Cond1.ReadPara();
	m_Cond2.ReadPara();
	m_Cond3.ReadPara();
	m_Cond4.ReadPara();
	m_Cond5.ReadPara();

	int err1, err2, err3, err4, err5;	// ҳ���ݴ����
	int err = 0;						// ȫ���ݴ����
	int i = 0;
	while(i < pApp->aBase.GetSize() )
	{
		err = err1 = err2 = err3 = err4 = err5 = 0;

		// ��������
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
		// ��̬����
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
		// ��������
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
		// ��λ����
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
		// ��Χ����
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

		// ȫ���ݴ�
		if( err1 + err2 + err3 + err4 + err5 > m_cmbAllowErrorAll.GetCurSel() )
		{
			if(!bCtrl)
			{
				pApp->aBase.RemoveAt(i);
				continue;
			}
		}
		// ҳ���ݴ�
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
		// ������࣬����ʾ
		pApp->DispatchNum();
		DisplayResult();
		DisplaySummary();
		
		// ѡ����ҳ
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
		
		// ʹ�ð�ť
		EnableButton();
		
		// �滻���
		if(IsAutoBase())
		{
			ReplaceBase();
		}
	}
	else // ������֤���
	{
		err = err1 + err2 + err3 + err4 + err5;
		CString str = CString(_T("���¿������� = ")) + pHistory->GetCNum(0).ToString()
			+ _T("\n")
			+ _T("\n������������ = ") + EMFC::Int2Str(err1) + _T("���ݴ� = ") + EMFC::Int2Str( m_Cond1.m_cmbAllowError.GetCurSel() ) + (err1 > m_Cond1.m_cmbAllowError.GetCurSel() ? _T("����") : _T("����"))
			+ _T("\n������������ = ") + EMFC::Int2Str(err3) + _T("���ݴ� = ") + EMFC::Int2Str( m_Cond3.m_cmbAllowError.GetCurSel() ) + (err3 > m_Cond3.m_cmbAllowError.GetCurSel() ? _T("����") : _T("����"))
			+ _T("\n��̬�������� = ") + EMFC::Int2Str(err2) + _T("���ݴ� = ") + EMFC::Int2Str( m_Cond2.m_cmbAllowError.GetCurSel() ) + (err2 > m_Cond2.m_cmbAllowError.GetCurSel() ? _T("����") : _T("����"))
			+ _T("\n��λ�������� = ") + EMFC::Int2Str(err4) + _T("���ݴ� = ") + EMFC::Int2Str( m_Cond4.m_cmbAllowError.GetCurSel() ) + (err4 > m_Cond4.m_cmbAllowError.GetCurSel() ? _T("����") : _T("����"))
			+ _T("\n��Χ�������� = ") + EMFC::Int2Str(err5) + _T("���ݴ� = ") + EMFC::Int2Str( m_Cond5.m_cmbAllowError.GetCurSel() ) + (err5 > m_Cond5.m_cmbAllowError.GetCurSel() ? _T("����") : _T("����"))
			+ _T("\n")
			+ _T("\nȫ���������� = ") + EMFC::Int2Str(err) + _T("���ݴ� = ") + EMFC::Int2Str( m_cmbAllowErrorAll.GetCurSel() ) + (err > m_cmbAllowErrorAll.GetCurSel() ? _T("����") : _T("����"))
			;

		err = (err1 > 0) + (err2 > 0) + (err3 > 0) + (err4 > 0) + (err5 > 0);
		str += _T("\n�ۼ�ҳ����� = ") + EMFC::Int2Str(err) + _T("���ݴ� = ") + EMFC::Int2Str( m_cmbAllowErrorPage.GetCurSel() ) + (err > m_cmbAllowErrorPage.GetCurSel() ? _T("����") : _T("����"));

		if( err1 <= m_Cond1.m_cmbAllowError.GetCurSel()
			&& err2 <= m_Cond2.m_cmbAllowError.GetCurSel()
			&& err3 <= m_Cond3.m_cmbAllowError.GetCurSel()
			&& err4 <= m_Cond4.m_cmbAllowError.GetCurSel()
			&& err5 <= m_Cond5.m_cmbAllowError.GetCurSel()
			&& err <= m_cmbAllowErrorPage.GetCurSel()
			&& err1 + err2 + err3 + err4 + err5 <= m_cmbAllowErrorAll.GetCurSel()
			)
		{
			str += _T("\n\n��ϲ���н���!");
		}

		CString strCaption = _T("����������֤");
		MessageBox(str, strCaption, MB_OK);
	}
	
	GetDlgItem(IDOK)->SetWindowText( _T("����") );
	UpdateData(FALSE);
}

/*
 *	ˢ�¹��˽���б��
 */
void CMy3DDlg::DisplayResult()
{
	m_pageG6.RefreshList();
	m_pageG3.RefreshList();
	m_pageG1.RefreshList();
	
	UpdateData(FALSE);
}

/*
 *	������Ҫ��Ϣ
 */
VOID CMy3DDlg::DisplaySummary()
{
	UINT nG6 = pApp->aResult[0].GetSize();
	UINT nG3 = pApp->aResult[1].GetSize();
	UINT nG1 = pApp->aResult[2].GetSize();
	UINT cnt = nG6 + nG3 + nG1;

	m_strTip1.Format(_T("%-4d ע,�� %-4d Ԫ"), nG6, nG6 << 1);
	m_strTip2.Format(_T("%-4d ע,�� %-4d Ԫ"), nG3, nG3 << 1);
	m_strTip3.Format(_T("%-4d ע,�� %-4d Ԫ"), nG1, nG1 << 1);
	m_strTip4.Format(_T("%-4d ע,�� %-4d Ԫ"), cnt, cnt << 1);
	
	UpdateData(FALSE);
}

/*
 *	[��ת��] ��ť
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
 *	[��ת��] ��ť
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
 *	[�ӵ����] ��ť
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
 *	ѡ���Ʊ����
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
 *	���ô��ڱ�������
 */
void CMy3DDlg::SetTitle()
{
	CString strCaption, str;
	strCaption.LoadString(IDS_TITLE);
	str.LoadString(IDS_VERSION);
	str = str.Left(3);
	strCaption += CString(_T(" ")) + str;

	// ��Ʊ����
	str.LoadString(IDS_TITLE1 + Is3D());
	strCaption += CString(_T("��")) + str;

	// ���ڿ�����¼
	UINT nCount = pHistory->GetCount();
	if(1 <= nCount)
	{
		strCaption += _T(" [") + pHistory->GetPeriodStr(0).Right(5) + _T("]=[")
			+ pHistory->GetNumStr(0) + _T("]");

		CString sHot, sWarm, sCool;
		pHistory->HotNum(0, sHot, sWarm, sCool, pApp->iHot);
		strCaption += CString(_T(" [��]=[")) +  sHot + _T("]")
			_T(" [��]=[") + sWarm + _T("]") + _T(" [��]=[") + sCool + _T("]");
	}
	
	SetWindowText(strCaption);
}

/*
 *	[��Ͷ����] ��ť
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
		if( IDYES == MessageBox(_T("�Ҳ��������ļ�:\n") + strCmd + _T("\n\n�������ϵ���������Ҫ����, �ָ�����?"),
			strCaption, MB_YESNO | MB_ICONWARNING) )
		{
			OnCheckUpdate();
		}
	}
}

/*
 *	[����...] ��ť
 */
void CMy3DDlg::OnSaveFile() 
{
	// TODO: Add your control notification handler code here
	CSaveOption dlg;
	dlg.m_bSaveAndOpen = (1 == pApp->iSaveAndOpen);
	dlg.DoModal();
}

/*
 *	[¼������] ��ť
 */
void CMy3DDlg::OnDataInput() 
{
	// TODO: Add your control notification handler code here

	CDataInput dlg;
	dlg.DoModal();
}

/*
 *	[���ݷ���] ��ť
 */
void CMy3DDlg::OnDataAnalyse() 
{
	// TODO: Add your control notification handler code here
	if(pHistory->IsNull())
	{
		CString str;
		str.LoadString(IDS_TITLE);
		MessageBox(_T("��ʷ��¼Ϊ�ա�"), str, MB_ICONINFORMATION);
		return;
	}
		
	CDataAnalyse dlg;
	dlg.DoModal();
}

/*
 *	[����] ��ť
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
		if( IDYES == MessageBox(_T("�Ҳ��������ļ�:\n") + strCmd + _T("\n\n�������ϵ���������Ҫ����, �ָ�����?"),
			strCaption, MB_YESNO | MB_ICONWARNING) )
		{
			OnCheckUpdate();
		}
	}
}

BOOL CMy3DDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	// ��ǰ�������浽��ʱ�ļ�
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
	
	// ������
	CString str, ss;
	ss.LoadString(IDS_TITLE);
	str = CString(_T("���� ")) + ss/* + _T("  (���������/����3D)�������")*/;
	SetWindowText(str);

	// ������� + �汾�� + ��������
	str = ss;
	ss.LoadString(IDS_VERSION);
	str = str + CString(_T("(C) ")) + ss + CString(_T("  ")) + tczDate;
	GetDlgItem(IDC_STATIC_NAME)->SetWindowText(str);

	// ��ҳ����
	lnkHomePage.Attach(GetDlgItem(IDC_STATIC_HOME)->GetSafeHwnd());
	lnkHomePage.SetLink(_T("������վ"), _T("https://seanto.github.io/"), TRUE);

	// �ʼ�
	lnkMail.Attach(GetDlgItem(IDC_STATIC_MAIL)->GetSafeHwnd());
	lnkMail.SetLink(_T("����BUG"), _T("https://github.com/SeanTo/My3D"), TRUE);

	// ��л
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
 *	[����] ��ť
 */
void CMy3DDlg::OnBtnAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}

/*
 *	[�ļ�����] ��ť
 */
void CMy3DDlg::OnInterFile() 
{
	// TODO: Add your control notification handler code here
	CIntersection dlg;
	dlg.DoModal();
	
	DisplayResult();
	DisplaySummary();
	
	// ʹ�ð�ť
	EnableButton();
}

/*
 *	[�Զ�����] ��ť
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
 *	[����] ��ť
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
		MessageBox(_T("��ױ༭��Ϊ�գ�"), str, MB_ICONINFORMATION);
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
 *	[�]��ť
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
		MessageBox(_T("��ױ༭��Ϊ�գ�"), str, MB_ICONINFORMATION);
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
 *	���°�ʹ��״̬
 */
VOID CMy3DDlg::EnableButton()
{
	UpdateData(TRUE);

	BOOL bG6 = pApp->aResult[0].GetSize() > 0;
	BOOL bG3 = pApp->aResult[1].GetSize() > 0;
	BOOL bG1 = pApp->aResult[2].GetSize() > 0;
	
	BOOL bValid;
	int iSelResult = m_tabResult.GetCurSel();
	
	// ���桢����������������(���ȫ��������ǿ�ʱ��Ч)
	bValid = bG6 || bG3 || bG1;
	GetDlgItem(IDC_SAVE_FILE)->EnableWindow(bValid);
//	GetDlgItem(IDC_ANALYSE_RESULT)->EnableWindow(bValid);
	GetDlgItem(IDC_INTER_BASE)->EnableWindow(bValid);
	GetDlgItem(IDC_EXCLUDE_BASE)->EnableWindow(bValid);

	// ����ѡת��(�������/��������ǿ�ʱ��Ч)
	bValid = iSelResult == 0 && bG6
		|| iSelResult == 1 && bG3;
	GetDlgItem(IDC_SINGLE_TO_GROUP)->EnableWindow(bValid);
	GetDlgItem(IDC_GROUP_TO_SINGLE)->EnableWindow(bValid);

	// ������(��Ե�ǰѡ�����̬������ǿ�ʱ��Ч
	bValid = iSelResult == 0 && bG6
		|| iSelResult == 1 && bG3
		|| iSelResult == 2 && bG1;
	GetDlgItem(IDC_SENT_TO_BASE)->EnableWindow(bValid);

	// �ֶ���ɾ
	bValid = 0 == iSelResult && bG6 && -1 != m_pageG6.GetCurSel()
		|| 1 == iSelResult && bG3 && -1 != m_pageG3.GetCurSel()
		|| 2 == iSelResult && bG1 && -1 != m_pageG1.GetCurSel();
	GetDlgItem(IDC_BTN_HAND_DEL)->EnableWindow(bValid);
}

/*
 *	���˽������ҳ������Ӧ�¼�
 */
void CMy3DDlg::OnSelchangeTabResult(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	EnableButton();
	
	*pResult = 0;
}

/*
 *	[���Ʒ���] ��ť
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
 *	[������]��ť
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
		if( IDYES == MessageBox(_T("���³�������:\n") + strExeFile + _T("\n")
			+ strIniFile + _T("\n") + _T("\n�������ҳ�ֶ������£����ڼ����?"),
			strCaption, MB_YESNO | MB_ICONQUESTION ) )
		{
			ShellExecute(NULL, _T("open"),
				_T("http://www.tuxw.cn/blog/article.asp?id=50"),
				NULL, NULL, SW_SHOWNORMAL);
		}

		return;
	}

	if(IDYES == MessageBox(_T("�ò�����رձ�������������³���\n���½�����������������С�")
		, strCaption, MB_YESNO | MB_ICONQUESTION) )
	{
		ShellExecute(NULL, _T("open"), strExeFile, NULL, NULL, SW_SHOWNORMAL);
		CDialog::OnCancel();
	}
}

/*
 *	[��������] ��ť
 */
void CMy3DDlg::OnCondSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString strFile = WND::GetAbsPath(TRUE);

	// ����ΪĬ������
	if( WND::IsCtrlDown() )
	{
		strFile += _T("My3D.ini");
		CondSave(strFile, TRUE);

		AfxMessageBox(CString(_T("��ǰ�����ѱ���ΪĬ��ֵ\n\n"))
			+ _T("�Ժ��[��λ]ʱ���ָ�������\n��ȫ��λ�밴סCTRL���ٵ�[��λ]"), 
			MB_OK, MB_ICONINFORMATION);
		return;
	}

	// ����
	if( m_bSaveAsOpenCond )
	{
		int iPeriod = pHistory->IsNull() ? 1 : pHistory->GetPeriod(0) + 1;

		CString strName;
		strName.Format(_T("Output\\%s-������-%07d.ini"), Is3D() ? _T("3D") : _T("P3"), iPeriod);
		strFile += strName;
		strFile = WND::SelectFile(FALSE, strFile, _T("ini"), _T("�����ļ�(*.ini)|*.ini||"));
	}
	else
		strFile += _T("temp.ini");

	// д�ļ�
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
 *	[��ȡ����] ��ť
 */
void CMy3DDlg::OnCondRead() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strFile = WND::GetAbsPath(TRUE);
	//strFile = CString(pApp->GetPath()) + _T("\\temp.ini");

	// ����
	if( m_bSaveAsOpenCond )
	{
		int iPeriod = pHistory->IsNull() ? 1 : pHistory->GetPeriod(0) + 1;

		CString strName;
		strName.Format(_T("Output\\%s-������-%07d.ini"), Is3D() ? _T("3D") : _T("P3"), iPeriod);
		strFile += strName;
		strFile = WND::SelectFile(TRUE, strFile, _T("ini"), _T("�����ļ�(*.ini)|*.ini||"));
	}
	else 
		strFile += _T("temp.ini");

	// ���ļ�
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
 *	[��λ����] ��ť
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
 *	[����ֲ�] ��ť
 */
void CMy3DDlg::OnDistribute() 
{
	// TODO: Add your control notification handler code here
	CDataDistribute dlg;
	dlg.DoModal();
}

/*
 *	�ӡ�����������ҳ�ж�ȡ��������
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
 *	[ս��] ��ť
 */
void CMy3DDlg::OnAnalyseResult() 
{
	// TODO: Add your control notification handler code here
	if(pHistory->IsNull())
	{
		CString str;
		str.LoadString(IDS_TITLE);
		MessageBox(_T("��ʷ��¼Ϊ�ա�"), str, MB_ICONINFORMATION);
		return;
	}
	
	// ��ǰ���+�̶����
 	CString strHeader = _T("���˽��,60;��˳,36;����,36;����,36;����ż��,60;�������,60;������,48;���,36;С��,36;");
	int iWidth = 60 + 36 + 36 + 36 + 60 + 60 + 48 + 36 + 36;
	int iBaseCnt = 9;
	
	// �Զ�����
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

	// ͳ������
	UINT nPeriodCnt = GetPeriods();
	CUIntArray aNumber;
	CUIntArray aRes0, aRes1, aRes2, aRes3, aRes4, aRes5, aRes6, aRes7, aRes8;
	CUIntArray aRes9, aRes10, aRes11, aRes12, aRes13, aRes14, aRes15, aRes16, aRes17, aRes18;

	// ������ǰ���
	pApp->CompoundNum(aNumber);
	if( 0 == aNumber.GetSize() )
	{
		for(int i = 0; i < 7; ++i)
			aRes0.Add(0);
	}
	else
		pHistory->Success(aNumber, nPeriodCnt, aRes0);
		
	// ��˳
	m_page2.GetBase(&aNumber, m_page2.LoadProBase(1, FALSE));
	pHistory->Success(aNumber, nPeriodCnt, aRes1);
	// ����
	m_page2.GetBase(&aNumber, m_page2.LoadProBase(2, FALSE));
	pHistory->Success(aNumber, nPeriodCnt, aRes2);
	// ����
	m_page2.GetBase(&aNumber, m_page2.LoadProBase(4, FALSE));
	pHistory->Success(aNumber, nPeriodCnt, aRes3);
	// ����ż��
	m_page2.GetBase(&aNumber, m_page2.LoadProBase(6, FALSE));
	pHistory->Success(aNumber, nPeriodCnt, aRes4);
	// �������
	m_page2.GetBase(&aNumber, m_page2.LoadProBase(7, FALSE));
	pHistory->Success(aNumber, nPeriodCnt, aRes5);
	// ������
	m_page2.GetBase(&aNumber, m_page2.LoadProBase(8, FALSE));
	pHistory->Success(aNumber, nPeriodCnt, aRes6);
	// ���
	m_page2.GetBase(&aNumber, m_page2.LoadProBase(9, FALSE));
	pHistory->Success(aNumber, nPeriodCnt, aRes7);
	// С��
	m_page2.GetBase(&aNumber, m_page2.LoadProBase(10, FALSE));
	pHistory->Success(aNumber, nPeriodCnt, aRes8);

	// �����Զ�����
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
		
	CWinHistory dlg(_T("ս��ͳ��"), nPeriodCnt);
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
 * �ֶ���ɾ
 */
void CMy3DDlg::OnBtnHandDel() 
{
	// TODO: Add your control notification handler code here

	switch(m_tabResult.GetCurSel())
	{
	case 0: // ����
		m_pageG6.DelCurSel();
		break;
	case 1: // ����
		m_pageG3.DelCurSel();
		break;
	case 2: // ����
		m_pageG1.DelCurSel();
		break;
	}

	DisplaySummary();
	EnableButton();
}

/*
 * �ӵ����
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
 *	�滻���
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
 * ������Ϣ
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
	// ��������������ͼ��
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
	// ɾ���������е�ͼ��
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
	
	// ���ش���
// 	if( ::GetForegroundWindow() != m_hWnd )
// 	{
// 		if(nType == SIZE_MINIMIZED && pApp->iMinToTray > 0)
// 		{
// 			// ���ش��ڣ�ע�⣬��ʱ(����OnSize�ѽ�)������С����
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
		// �Ҽ��˵�
	case WM_RBUTTONDOWN:
		{
			// ��굥��λ��
			CPoint point;
			GetCursorPos(&point);
			// װ��˵�
			LoadContextMenu(point);
		}
		break;
		// ����ָ�����
	case WM_LBUTTONDOWN:
		if(!m_bDisp)
		{
//			ShowWindow(SW_SHOW);	// ��ʾ����(��ʱ��������С����)
//			ShowWindow(SW_RESTORE);	// ��ԭ����
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
	// װ��ͼ������˵�
	CMenu menu;
	menu.LoadMenu(IDR_MENU_ICON);
	
	// ���������ڼ���
	SetForegroundWindow();
	
	// ��ʾͼ��˵�
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTBUTTON,
		point.x, point.y, this, NULL); 
	
	// ����һ��������Ϣ��ʹ�˵�������ȷ
	PostMessage(WM_USER, 0, 0);
}

void CAboutDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
}

/*
 *	[��л] ��ť �����ڶԻ���
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
	
	GetDlgItem(IDC_THANK)->SetWindowText(bMost ? _T("<< ��л") : _T("��л >>"));
	
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
		if( IDYES == MessageBox(_T("����Ϣֻ����һ�Σ�\n\n")
			_T("��Ը������������?\n\n")
			_T("ѡ�� [��] �鿴������Ϣ...\n")
			_T("ѡ�� [��] �Ժ���˵...\n\n")
			
			_T("5Ԫ10Ԫ�Ǿ�����1Ԫ2ԪҲ�Ǿ�����\n")
			_T("������1עͶע�֧�ֱ�����������ơ�\n")
			_T("�Ƿ��������Ӱ�������ʹ�ñ������\n\n")
			
			_T("��л��ʹ�ñ������\n")
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
		MessageBox(_T("��ȡ�����ļ�����"), str, MB_ICONERROR);
		return FALSE;
	}
	
	// �汾���
	CString strVer;
	fin.GetVarStr(_T("DEFAULT"), _T("���ð汾"), strVer);
	strVer.TrimLeft();
	strVer.TrimRight();
	if( 0 != strVer.Left(3).Compare(pApp->strVersion.Left(3)) )
	{
		int iSel = MessageBox(CString(_T("����汾: ")) + pApp->strVersion
			+ CString(_T("\n���ð汾: ")) + strVer
			+ CString(_T("\n\n�����ļ��汾�뵱ǰ�����ƥ�䣬�п��ܴ��ڼ���������"))
			+ CString(_T("\n�Ƿ��������?"))
			+ CString(_T("\n\n����������ʱ�Ϳ�������ʾ����ѡ�����²���֮һ:"))
			+ CString(_T("\n����ɾ��My3D.ini����������(�Զ��ؽ�һ��Ĭ������)"))
			+ CString(_T("\n������������CTFL+[��λ]����CTRL+[����]���ָ�Ĭ������"))
			+ CString(_T("\n�������߸������"))
			, CString(_T("������")), MB_YESNO | MB_ICONWARNING );

		if(IDNO == iSel)
			return FALSE;
	}
		
	if(bDefault)
	{
		// ��С����֪ͨ��
		fin.GetVarInt(_T("CONFIG"), _T("��С����֪ͨ��"), pApp->iMinToTray);
		// ������
		fin.GetVarInt(_T("CONFIG"), _T("������"), pApp->iSaveAndOpen);
		// �Ƽ�����
		fin.GetVarInt(_T("CONFIG"), _T("�Ƽ�����"), pApp->iWarnRecommand);
		// �Ƽ�����
		fin.GetVarInt(_T("CONFIG"), _T("ȷ��ɾ��"), pApp->iDeleteTip);
		// �������
		fin.GetVarStr(_T("CONFIG"), _T("�������"), pApp->strAuthor);


		// �ⲿ����1
		CString str;
		fin.GetVarStr(_T("CONFIG"), _T("����1"), str);
		if( !str.IsEmpty() )
		{
			str.TrimRight();
			str.TrimLeft();
			strExTool1 = str;
			GetDlgItem(IDC_BTN_TEST)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_TEST)->ShowWindow(SW_SHOW);

			fin.GetVarStr(_T("CONFIG"), _T("����1"), str);
			if( !str.IsEmpty() )
			{
				strExName1 = str;
				GetDlgItem(IDC_BTN_TEST)->SetWindowText( str );
			}

			fin.GetVarStr(_T("CONFIG"), _T("����2"), str);
			if( !str.IsEmpty() )
			{
				str.TrimRight();
				str.TrimLeft();
				strExTool2 = str;
				GetDlgItem(IDC_BTN_TEST2)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_TEST2)->ShowWindow(SW_SHOW);

				fin.GetVarStr(_T("CONFIG"), _T("����2"), str);
				if( !str.IsEmpty() )
				{
					strExName2 = str;
					GetDlgItem(IDC_BTN_TEST2)->SetWindowText( str );
				}
			}

		}
	}
	
	int n = 0;
	
	// ��Ʊ����
	if( fin.GetVarInt(_T("DEFAULT"), _T("��Ʊ����"), m_iLotType) )
	
	// Ͷע����
	if( fin.GetVarInt(_T("DEFAULT"), _T("Ͷע����"), n) )
		m_tabNumBase.SetCurSel(n < m_tabNumBase.GetItemCount() ? n : 0);
	
	// ��ǰ����
	if( fin.GetVarInt(_T("DEFAULT"), _T("��ǰ����"), n) )
		m_tabCond.SetCurSel(n < m_tabCond.GetItemCount() ? n : 0);
		
	// �滻���
	if( fin.GetVarInt(_T("DEFAULT"), _T("�滻���"), n) )
		m_bReplaceBase = (n != 0);
	
	// ͳ��ս��
	if( fin.GetVarInt(_T("DEFAULT"), _T("ս��ͳ��"), n) )
		m_iStatPeriods = n;
	
	// ���˽��ҳ��
	if( fin.GetVarInt(_T("DEFAULT"), _T("���˽��"), n) )
		m_tabResult.SetCurSel(n < m_tabResult.GetItemCount() ? n : 0);
	
	// ȫ���ݴ�
	if( fin.GetVarInt(_T("DEFAULT"), _T("ȫ���ݴ�"), n) )
	{
		if(n < 0 || n >= m_cmbAllowErrorAll.GetCount())
			n = m_cmbAllowErrorAll.GetCount() - 1;
		m_cmbAllowErrorAll.SetCurSel(n);
	}
	
	// ҳ���ݴ�
	if( fin.GetVarInt(_T("DEFAULT"), _T("ҳ���ݴ�"), n) )
	{
		if(n < 0 || n >= m_cmbAllowErrorPage.GetCount())
			n = m_cmbAllowErrorPage.GetCount() - 1;
		m_cmbAllowErrorPage.SetCurSel(n);
	}
		
	// ѡ�����
	m_page1.LoadCondition(fin);
	// ����
	m_Cond1.LoadCondition(fin);
	// ��̬
	m_Cond2.LoadCondition(fin);
	// ����
	m_Cond3.LoadCondition(fin);
	// ��λ
	m_Cond4.LoadCondition(fin);
	// ��Χ
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
		MessageBox(_T("д�����ļ�����\n")+strFile, str, MB_ICONERROR);
		
		return FALSE;
	}

	if(bDefault)
	{
		// �汾����С����֪ͨ���������򿪡��Ƽ�����
		fin.SetVarInt(_T("CONFIG"), _T("��С����֪ͨ��"), pApp->iMinToTray, 0);
		fin.SetVarInt(_T("CONFIG"), _T("������"), pApp->iSaveAndOpen, 0);
		fin.SetVarInt(_T("CONFIG"), _T("�Ƽ�����"), pApp->iWarnRecommand, 0);
		fin.SetVarInt(_T("CONFIG"), _T("ȷ��ɾ��"), pApp->iDeleteTip, 0);

		// �ⲿ����
		fin.SetVarStr(_T("CONFIG"), _T("����1"), strExTool1, 0);
		fin.SetVarStr(_T("CONFIG"), _T("����1"), strExName1, 0);
		fin.SetVarStr(_T("CONFIG"), _T("����2"), strExTool2, 0);
		fin.SetVarStr(_T("CONFIG"), _T("����2"), strExName2, 0);
	}
	
	// ϵͳ����
	fin.SetVarStr(_T("DEFAULT"), _T("���ð汾"), pApp->strVersion, 0);
	fin.SetVarInt(_T("DEFAULT"), _T("��Ʊ����"), m_iLotType, 0);
	fin.SetVarInt(_T("DEFAULT"), _T("Ͷע����"), m_tabNumBase.GetCurSel(), 0);
	fin.SetVarInt(_T("DEFAULT"), _T("��ǰ����"), m_tabCond.GetCurSel(), 0);

	fin.SetVarInt(_T("DEFAULT"), _T("�滻���"), IsAutoBase() ? 1 : 0, 0);
	fin.SetVarInt(_T("DEFAULT"), _T("ս��ͳ��"), m_iStatPeriods, 0);
	fin.SetVarInt(_T("DEFAULT"), _T("ȫ���ݴ�"), m_cmbAllowErrorAll.GetCurSel(), 0);
	fin.SetVarInt(_T("DEFAULT"), _T("ҳ���ݴ�"), m_cmbAllowErrorPage.GetCurSel(), 0);
	fin.SetVarInt(_T("DEFAULT"), _T("���˽��"), m_tabResult.GetCurSel(), 0);

	// ѡ�����
	m_page1.SaveCondition(fin);
	// ��������
	m_Cond1.SaveCondition(fin);
	// ��̬����
	m_Cond2.SaveCondition(fin);
	// ����
	m_Cond3.SaveCondition(fin);
	// ��λ
	m_Cond4.SaveCondition(fin);
	// ��Χ
	m_Cond5.SaveCondition(fin);
	
	return TRUE;
}

/*
 *	[�ⲿ����]��ť1
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
		UINT nRet = AfxMessageBox( _T("�Ҳ����ⲿ����:\n") + strExTool1
			+ _T("\n\n��༭ My3D.ini������1=�ⲿ����\n\n���ھͱ༭��"), MB_YESNO );

		if(IDYES == nRet)
		{
			strCmd = WND::GetAbsPath() + _T("\\My3D.ini") ;
			ShellExecute(NULL, _T("open"), strCmd, NULL, NULL, SW_SHOWNORMAL);
		}
	}
}

/*
 *	[�ⲿ����]��ť1
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
		UINT nRet = AfxMessageBox( _T("�Ҳ����ⲿ����:\n") + strExTool2
			+ _T("\n\n��༭ My3D.ini������1=�ⲿ����\n\n���ھͱ༭��"), MB_YESNO );

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
		GetDlgItem(IDOK)->SetWindowText( _T("����") );
	}
	else
	{
		GetDlgItem(IDOK)->SetWindowText( _T("��֤") );
	}
//	GetDlgItem(IDOK)->UpdateData(FALSE);
//	GetDlgItem(IDOK)->Invalidate();
	
	CDialog::OnTimer(nIDEvent);
}

BOOL CMy3DDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	
	m_tt.RelayEvent(pMsg); // ��ť������ʾ
	
	if(WM_KEYDOWN == pMsg->message)
	{
		if(VK_ESCAPE == pMsg->wParam/* || VK_RETURN == pMsg->wParam*/)
		{   
			return TRUE;   
		}
		else if(VK_CONTROL == pMsg->wParam)
		{
			// ���� CTRL ʱ��[����] �� [��֤]
			GetDlgItem(IDOK)->SetWindowText( _T("��֤") );
			return TRUE;
		}
	}
	else if(WM_KEYUP == pMsg->message)
	{
		if(VK_CONTROL == pMsg->wParam)
		{
			// �ͷ� CTRL ʱ��[��֤] �� [����]
			GetDlgItem(IDOK)->SetWindowText( _T("����") );
			return TRUE;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

CString CMy3DDlg::ExportAllComment()
{
	CString str;
	CString strCond = _T("\n=========��Ҫ��������=========\n");
	
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

	strCond += _T("=========������������=========");

	return strCond;
}
