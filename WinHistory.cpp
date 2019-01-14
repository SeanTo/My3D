// WinHistory.cpp : implementation file
//

#include "stdafx.h"
#include "WinHistory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinHistory dialog


CWinHistory::CWinHistory(const CString &strCaption, UINT nPeriod, CWnd* pParent /* = NULL */)
	: CDialog(CWinHistory::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinHistory)
	//}}AFX_DATA_INIT

	m_strCaption = strCaption;

	m_strHeader = _T("期号,36;开奖,36;");
	m_strMark = _T("中奖");
	m_nCols = 2;
	m_nAddWidth = 0;
	m_nPeriod = nPeriod;

	pApp = (CMy3DApp *)AfxGetApp();
	pHistory = pApp->GetHistory();
}


void CWinHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinHistory)
	DDX_Control(pDX, IDC_LIST_WIN, m_listWin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWinHistory, CDialog)
	//{{AFX_MSG_MAP(CWinHistory)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_WIN, OnRclickListWin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinHistory message handlers

BOOL CWinHistory::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_listWin.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listWin.SetHeadings(m_strHeader, LVCFMT_CENTER);
	m_listWin.SetBkColor(RGB(128,128,128));
	m_listWin.LoadColumnInfo();

	CString str;
	str.Format(_T(": 最近 %d 期"), m_nPeriod);
	SetWindowText(m_strCaption + str);

	if(m_nCols > 2)
	{
		CRect rcClient;
		GetWindowRect(&rcClient);
		rcClient.right += m_nAddWidth;
		SetWindowPos(0, 0, 0, rcClient.Width(), rcClient.Height(), SWP_NOMOVE | SWP_NOZORDER);
		
		CRect rcList;
		GetDlgItem(IDC_LIST_WIN)->GetWindowRect(&rcList);
		rcList.right += m_nAddWidth;
		GetDlgItem(IDC_LIST_WIN)->SetWindowPos(0, rcList.left, rcList.top,
			rcList.Width(), rcList.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}

	DisplayRes();
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

VOID CWinHistory::AddColumn(const CString &str, UINT nColumns, UINT nExWidth)
{
#define MAX_ADD_WIDTH 900

	m_strHeader = m_strHeader + str;
	m_nCols += nColumns;
	m_nAddWidth = nExWidth;

	m_nAddWidth = m_nAddWidth > MAX_ADD_WIDTH ? MAX_ADD_WIDTH : m_nAddWidth;

#undef MAX_ADD_WIDTH
}

VOID CWinHistory::SetStatData(CUIntArray *pRes0,
							  CUIntArray *pRes1 /* = NULL */,
							  CUIntArray *pRes2 /* = NULL */,
							  CUIntArray *pRes3 /* = NULL */,
							  CUIntArray *pRes4 /* = NULL */,
							  CUIntArray *pRes5 /* = NULL */,
							  CUIntArray *pRes6 /* = NULL */,
							  CUIntArray *pRes7 /* = NULL */,
							  CUIntArray *pRes8 /* = NULL */,
							  CUIntArray *pRes9 /* = NULL */,
							  CUIntArray *pRes10 /* = NULL */,
							  CUIntArray *pRes11 /* = NULL */,
							  CUIntArray *pRes12 /* = NULL */,
							  CUIntArray *pRes13 /* = NULL */,
							  CUIntArray *pRes14 /* = NULL */,
							  CUIntArray *pRes15 /* = NULL */,
							  CUIntArray *pRes16 /* = NULL */,
							  CUIntArray *pRes17 /* = NULL */,
							  CUIntArray *pRes18 /* = NULL */
							  )
{
	p[0] = pRes0;
	p[1] = pRes1;
	p[2] = pRes2;
	p[3] = pRes3;
	p[4] = pRes4;
	p[5] = pRes5;
	p[6] = pRes6;
	p[7] = pRes7;
	p[8] = pRes8;
	p[9] = pRes9;
	p[10] = pRes10;
	p[11] = pRes11;
	p[12] = pRes12;
	p[13] = pRes13;
	p[14] = pRes14;
	p[15] = pRes15;
	p[16] = pRes16;
	p[17] = pRes17;
	p[18] = pRes18;
}

VOID CWinHistory::DisplayRes()
{
	if(pHistory->IsNull())
		return;
	
	CString strPeriod = _T(" ");
	CString strNum = _T(" ");
	CString strRes = _T(" ");
	int iStart = 7;

	strPeriod = _T("  大底");
	strNum = _T("注数");
	m_listWin.AddItem(strPeriod, strNum,
		strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,
		strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes);
	
	strPeriod = _T("  理论");
	strNum = _T("周期");
	m_listWin.AddItem(strPeriod, strNum,
		strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,
		strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes);
	
	strPeriod = _T("  理论");
	strNum = _T("次数");
	m_listWin.AddItem(strPeriod, strNum,
		strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,
		strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes);
	
	strPeriod = _T("  实际");
	strNum = _T("中出");
	m_listWin.AddItem(strPeriod, strNum,
		strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,
		strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes);
	
	strPeriod = _T("  当前");
	strNum = _T("遗漏");
	m_listWin.AddItem(strPeriod, strNum,
		strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,
		strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes);
	
	strPeriod = _T("  最大");
	m_listWin.AddItem(strPeriod, strNum,
		strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,
		strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes);
	
	strNum = _T("连中");
	m_listWin.AddItem(strPeriod, strNum,
		strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,
		strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes);
	
	C3D CNum;
	UINT type;
	for(UINT i = 0; i < m_nPeriod; ++i)
	{
		CNum = pHistory->GetCNum(i);
		strPeriod = pHistory->GetPeriodStr(i).Right(5);
		strNum = CNum.ToString();

		m_listWin.AddItem(strPeriod, strNum,
			strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,
			strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes,strRes);
		
		type = CNum.Type();
		if(type == 2)
		{
			m_listWin.SetItemColor(i + iStart, 0, crText, crRed);
			m_listWin.SetItemColor(i + iStart, 1, crText, crRed);
		}
		else if(type == 1)
		{
			m_listWin.SetItemColor(i + iStart, 0, crText, crYellow);
			m_listWin.SetItemColor(i + iStart, 1, crText, crYellow);
		}
		else if(i & 1 )
		{
			m_listWin.SetItemColor(i + iStart, 0, crText, crBack);
			m_listWin.SetItemColor(i + iStart, 1, crText, crBack);
		}
	}

	const CUIntArray *pp;
	for(int j = 0; j < 19; ++j)
	{
		pp = p[j];
		
		if(j > 0 && NULL == pp)
			break;

		// 分析结果
		for(int i = 0; i < 7; ++i)
		{
			strRes.Format(_T("%d"), pp->GetAt(i));
			m_listWin.SetItemText(i, j + 2, strRes);

			if( !(i & 1) )
				m_listWin.SetItemColor(i, j + 2, crText, crBack);
		}
		strRes.Format(_T("%d.%02d"), pp->GetAt(1) / 100, pp->GetAt(1) % 100);

		if(0 == pp->GetAt(0))
		{
			m_listWin.SetItemText(0, 2, _T("空"));
			for(int i = 1; i < 7; ++i)
				m_listWin.SetItemText(i, 2, _T(" "));
		}
		else
			m_listWin.SetItemText(1, j + 2, strRes);

		m_listWin.SetItemColor(3, j + 2, RGB(255, 255, 255), RGB(0, 0, 255));
		
		for(int i = iStart; i < pp->GetSize(); ++i)
		{
			m_listWin.SetItemText(iStart + pp->GetAt(i), j + 2, m_strMark);
			
			if(0 == j)
				m_listWin.SetItemColor(iStart + pp->GetAt(i), j + 2, RGB(255, 255, 255), RGB(0, 128, 0));
			else
				m_listWin.SetItemColor(iStart + pp->GetAt(i), j + 2, crText, RGB(0, 0, 255));
		}
	}
}

void CWinHistory::OnRclickListWin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnCancel();
	*pResult = 0;
}

BOOL CWinHistory::PreTranslateMessage(MSG* pMsg) 
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
