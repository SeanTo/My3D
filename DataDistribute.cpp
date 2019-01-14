// DataDistribute.cpp : implementation file
//

#include "stdafx.h"
#include "DataDistribute.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataDistribute dialog


CDataDistribute::CDataDistribute(CWnd* pParent /* = NULL */)
	: CDialog(CDataDistribute::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataDistribute)
	m_iSel = 0;
	//}}AFX_DATA_INIT

	pApp = (CMy3DApp *)AfxGetApp();
	pHistory = pApp->GetHistory();
	nPeriod = 0;
}


void CDataDistribute::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataDistribute)
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Radio(pDX, IDC_RAD_DD1, m_iSel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataDistribute, CDialog)
	//{{AFX_MSG_MAP(CDataDistribute)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RAD_DD1, IDC_RAD_DD5, OnSelectPeriod)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataDistribute message handlers

BOOL CDataDistribute::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_list1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list1.SetHeadings(_T("期号,36;开奖,36;")
		_T("0,15;1,15;2,15;3,15;4,15;5,15;6,15;7,15;8,15;9,15;")
		_T("0,20;1,20;2,20;3,20;4,20;5,20;6,20;7,20;8,20;9,20;")
		_T("0,20;1,20;2,20;3,20;4,20;5,20;6,20;7,20;8,20;9,20;")
		_T("0,20;1,20;2,20;3,20;4,20;5,20;6,20;7,20;8,20;9,20;"),
		LVCFMT_CENTER
		);
	m_list1.SetBkColor(RGB(128,128,128));
	m_list1.LoadColumnInfo();

	m_iSel = 0;
	UpdateData(FALSE);

	GetPeriod(m_iSel);
	StatData();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDataDistribute::PreTranslateMessage(MSG* pMsg) 
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

VOID CDataDistribute::OnSelectPeriod(UINT nID)
{
	ASSERT(IDC_RAD_DD1 <= nID && IDC_RAD_DD5 >= nID);
	UpdateData(TRUE);
	
	GetPeriod(nID - IDC_RAD_DD1);
	StatData();	
}

VOID CDataDistribute::GetPeriod(int iSel)
{
	UpdateData(TRUE);
	
	if(NULL == pHistory)
	{
		nPeriod = 0;
		return;
	}
	
	UINT n = pHistory->GetCount();
	
	switch(iSel)
	{
	case 0:
		nPeriod = n > 50 ? 50 : n;
		break;
	case 1:
		nPeriod = n > 100 ? 100 : n;
		break;
	case 2:
		nPeriod = n > 200 ? 200 : n;
		break;
	case 3:
		nPeriod = pHistory->GetPeriod(0) % 1000;
		nPeriod = n > nPeriod ? nPeriod : n;
		break;
	default:
		nPeriod = n;
		break;
	}
}

VOID CDataDistribute::StatData()
{
	m_list1.DeleteAllItems();

	if(0 == nPeriod)
	{
		return;
	}
	
	C3D CNum;
	CString str = _T("");
	for(UINT i = 0; i < nPeriod; ++i)
	{
		CNum = pHistory->GetCNum(i);
		str.Empty();
		m_list1.AddItem(pHistory->GetPeriodStr(i).Right(5), CNum.ToString(),
			str, str, str, str, str, str, str, str, str, str,
			str, str, str, str, str, str, str, str, str, str,
			str, str, str, str, str, str, str, str, str, str,
			str, str, str, str, str, str, str, str, str, str );

		// 组选
		m_list1.SetItemText(i, 2 + CNum.Hun(), EMFC::Int2Str(CNum.Hun()));
		m_list1.SetItemText(i, 2 + CNum.Ten(), EMFC::Int2Str(CNum.Ten()));
		m_list1.SetItemText(i, 2 + CNum.Ent(), EMFC::Int2Str(CNum.Ent()));

		// 遗漏总值
		for(int j = 0; j < 3; ++j)
		{
			int iMiss;
			for(int k = 0; k < 10; ++k)
			{
				iMiss = pHistory->StatMiss(i, j, k);
				m_list1.SetItemText(i, 12 + j * 10 + k, EMFC::Int2Str(iMiss));
			}
		}
		
		// 百十个
		m_list1.SetItemText(i, 12 + CNum.Hun(), EMFC::Int2Str(CNum.Hun()));
		m_list1.SetItemText(i, 22 + CNum.Ten(), EMFC::Int2Str(CNum.Ten()));
		m_list1.SetItemText(i, 32 + CNum.Ent(), EMFC::Int2Str(CNum.Ent()));

		// 组选隔行底色
		if(i & 1)
		{
			for(int j = 0; j < 10; ++j)
				m_list1.SetItemColor(i, 2 + j, crText, crBack);
		}

		// 颜色
		if(CNum.IsG3())
		{
			// 历史
			m_list1.SetItemColor(i, 0, crText, crYellow);
			m_list1.SetItemColor(i, 1, crText, crYellow);
			// 组选
			m_list1.SetItemColor(i, 2 + CNum.Same(), crText, crYellow);
		}
		else if(CNum.IsG1())
		{
			// 历史
			m_list1.SetItemColor(i, 0, crText, crPurple);
			m_list1.SetItemColor(i, 1, crText, crPurple);
			// 组选
			m_list1.SetItemColor(i, 2 + CNum.Hun(), crText, crPurple);
		}
		
		// 百十个颜色
		m_list1.SetItemColor(i, 12 + CNum.Hun(), crText, crRed );
		m_list1.SetItemColor(i, 22 + CNum.Ten(), crText, crGreen );
		m_list1.SetItemColor(i, 32 + CNum.Ent(), RGB(255,255,255), crBlue );
	}
}

void CDataDistribute::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
	*pResult = 0;
}

void CDataDistribute::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	OnCancel();
	CDialog::OnRButtonDown(nFlags, point);
}
