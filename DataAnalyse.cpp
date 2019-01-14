// DataAnalyse.cpp : implementation file
//

#include "stdafx.h"
#include "DataAnalyse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataAnalyse dialog


CDataAnalyse::CDataAnalyse(CWnd* pParent /*=NULL*/)
	: CDialog(CDataAnalyse::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataAnalyse)
	m_iSelPeriod = 0;
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	pApp = (CMy3DApp*)AfxGetApp();
	pHistory = pApp->GetHistory();
	iPeriod = 50;
}


void CDataAnalyse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataAnalyse)
	DDX_Control(pDX, IDC_CMB_RECOMMAND, m_cmbNums);	
	DDX_Control(pDX, IDC_COM_AHP, m_cmbPeriod);	
	DDX_Control(pDX, IDC_TAB_STAT, m_tabStat);
	DDX_Radio(pDX, IDC_RAD_WP01, m_iSelPeriod);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataAnalyse, CDialog)
	//{{AFX_MSG_MAP(CDataAnalyse)
	ON_WM_RBUTTONDOWN()
	ON_CBN_SELCHANGE(IDC_COM_AHP, OnSelchangeComAhp)
	ON_CBN_SELCHANGE(IDC_CMB_RECOMMAND, OnSelchangeComNum)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_STAT, OnSelchangeTabStat)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RAD_WP01, IDC_RAD_WP04, OnSelectPeriod)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataAnalyse message handlers

BOOL CDataAnalyse::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_tabStat.AddPage(_T("常规数据"), &m_pageStat1, IDD_STAT1);
	m_tabStat.AddPage(_T("统计数据"), &m_pageStat2, IDD_STAT2);
	m_tabStat.AddPage(_T("定位/推荐"), &m_pageStat3, IDD_STAT3);
	m_tabStat.AddPage(_T("胆码/杀码"), &m_pageStat4, IDD_STAT4);
	m_tabStat.AddPage(_T("金三角"), &m_pageStat6, IDD_STAT6);
	m_tabStat.AddPage(_T("自动底算法"), &m_pageStat5, IDD_STAT5);
	m_tabStat.Show();
	
	CRect rc = pApp->rcScreen;
	MoveWindow(rc);
	
	GetClientRect(&rc);
	rc.DeflateRect(0, 50, 0, 0);
	GetDlgItem(IDC_TAB_STAT)->MoveWindow(&rc);
	
	m_tabStat.SetRect();
	m_tabStat.SetCurSel(pApp->iAnalyesPage);
	UpdateSubWnd(pApp->iAnalyesPage, 50);

	m_cmbNums.AddString("9码");
	m_cmbNums.AddString("8码");
	m_cmbNums.AddString("7码");
	m_cmbNums.AddString("6码");
	m_cmbNums.AddString("5码");
	m_cmbNums.AddString("4码");
	m_cmbNums.AddString("3码");
	m_cmbNums.SetCurSel(0);
	
	m_cmbPeriod.AddString("20期");
	m_cmbPeriod.AddString("30期");
	m_cmbPeriod.AddString("40期");
	m_cmbPeriod.AddString("50期");
	m_cmbPeriod.AddString("60期");
	m_cmbPeriod.AddString("70期");
	m_cmbPeriod.AddString("80期");
	m_cmbPeriod.AddString("90期");
	m_cmbPeriod.AddString("100期");
	m_cmbPeriod.SetCurSel(0);

	m_cmbNums.SetCurSel(9 - pApp->iRecommandNum);
	m_cmbPeriod.SetCurSel(pApp->iRecommandPeriod / 10 - 2);
	
	EnableCond();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDataAnalyse::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnCancel();
	CDialog::OnRButtonDown(nFlags, point);
}

BOOL CDataAnalyse::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(WM_KEYDOWN == pMsg->message)
	{
		if(VK_RETURN == pMsg->wParam/* || VK_ESCAPE == pMsg->wParam*/)
		{   
			return TRUE;   
		}
	}	
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDataAnalyse::OnSelchangeComAhp() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	pApp->iRecommandPeriod = (m_cmbPeriod.GetCurSel() + 2) * 10;

	m_pageStat3.RefreshList(pApp->iRecommandNum, pApp->iRecommandPeriod);
}

void CDataAnalyse::OnSelchangeComNum()
{
	UpdateData(TRUE);
	pApp->iRecommandNum = 9 - m_cmbNums.GetCurSel();

	m_pageStat3.RefreshList(pApp->iRecommandNum, pApp->iRecommandPeriod);
}

void CDataAnalyse::OnSelchangeTabStat(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	pApp->iAnalyesPage = m_tabStat.GetCurSel();
	
	EnableCond();

	int iLines = 0;
	switch(pApp->iAnalyesPage) {
	case 0:
		iLines = m_pageStat1.m_List.GetItemCount();
		break;
	case 1:
		iLines = m_pageStat2.m_List.GetItemCount();
		break;
	case 2:
		iLines = m_pageStat3.m_List.GetItemCount();
		break;
	case 3:
		iLines = m_pageStat4.m_List.GetItemCount();
		break;
	case 4:
		iLines = m_pageStat6.m_List.GetItemCount();
		break;
	case 5:
		iLines = m_pageStat5.m_List.GetItemCount();
		break;
	}

	if(abs(iPeriod - iLines) > 5)
		UpdateSubWnd(pApp->iAnalyesPage, iPeriod);
	
	*pResult = 0;
}

void CDataAnalyse::EnableCond()
{
	GetDlgItem(IDC_CMB_RECOMMAND)->EnableWindow(2 == pApp->iAnalyesPage);
	GetDlgItem(IDC_COM_AHP)->EnableWindow(2 == pApp->iAnalyesPage);
	
	GetDlgItem(IDC_CMB_RECOMMAND)->ShowWindow(2 == pApp->iAnalyesPage ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_COM_AHP)->ShowWindow(2 == pApp->iAnalyesPage ? SW_SHOW : SW_HIDE);

	GetDlgItem(IDC_STATIC_SEL_COND)->ShowWindow(2 == pApp->iAnalyesPage ? SW_SHOW : SW_HIDE);

	GetDlgItem(IDC_STATIC_TIP)->ShowWindow(m_tabStat.GetCurSel() >= 3 ? SW_SHOW : SW_HIDE);
}

void CDataAnalyse::OnSelectPeriod(UINT nID)
{
	ASSERT(IDC_RAD_WP01 <= nID && IDC_RAD_WP04 >= nID);
	UpdateData(TRUE);
		
	int iCount = pHistory->GetCount();
	
	switch(m_iSelPeriod)
	{
	case 0:
		iPeriod = 50;
		break;
	case 1:
		iPeriod = 100;
		break;
	case 2:
		iPeriod = pHistory->GetPeriod(0) % 1000;
		break;
	default:
		iPeriod = iCount;
		break;
	}
	
	if(iPeriod > iCount)
		iPeriod = iCount;
	
	UpdateSubWnd( m_tabStat.GetCurSel(), iPeriod);
}

void CDataAnalyse::UpdateSubWnd(int iPage, int iPeriod)
{
	ASSERT( 0 <= iPage && iPage <= m_tabStat.GetItemCount() );

	switch( iPage )
	{
	case 0:
		m_pageStat1.RefreshList(iPeriod);
		break;
	case 1:
		m_pageStat2.RefreshList(iPeriod);
		break;
	case 2:
		m_pageStat3.RefreshList(pApp->iRecommandNum, pApp->iRecommandPeriod, iPeriod);
		break;
	case 3:
		m_pageStat4.RefreshList(iPeriod);
		break;
	case 4:
		m_pageStat6.RefreshList(iPeriod);
		break;
	case 5:
		m_pageStat5.RefreshList(iPeriod);
		break;
	}
}
