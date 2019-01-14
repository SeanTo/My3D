// CommonStat.cpp : implementation file
//

#include "stdafx.h"
#include "Stat1.h"

#include "..\Share\WND.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStat1 dialog


CStat1::CStat1(CWnd* pParent /*=NULL*/)
	: CDialog(CStat1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStat1)
	//}}AFX_DATA_INIT
	
	pApp = (CMy3DApp *)AfxGetApp();
	pHistory = pApp->GetHistory();
}


void CStat1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStat1)
	DDX_Control(pDX, IDC_LIST, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStat1, CDialog)
	//{{AFX_MSG_MAP(CStat1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, OnRclickList)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStat1 message handlers

void CStat1::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	GetParent()->GetParent()->SendMessage(WM_CLOSE);
	*pResult = 0;
}

BOOL CStat1::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(WM_KEYDOWN == pMsg->message)
	{
		if(VK_RETURN == pMsg->wParam || VK_ESCAPE == pMsg->wParam)
		{   
			return TRUE;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CStat1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rc = pApp->rcScreen;
	MoveWindow(&rc);

	rc.DeflateRect(0, 0, 10, 100);
	GetDlgItem(IDC_LIST)->MoveWindow(&rc);
		
	// TODO: Add extra initialization here
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.SetHeadings(_T("期号,36;开奖,36;奇偶,36;大小,36;质合,36;连号,36;均值,36;和值,36;和尾,36;跨度,36;\
		奇偶形态,60;大小形态,60;质合形态,60;012路,45;\
		百十跨,48;百个跨,48;十个跨,48;百十和,48;百个和,48;十个和,48;百十积,48;百个积,48;十个积,48;\
		大号连,48;小号连,48;奇号连,48;偶号连,48;质号连,48;"), LVCFMT_CENTER );

	m_List.SetBkColor(RGB(128,128,128));
	m_List.LoadColumnInfo();
	
	RefreshList(50);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

VOID CStat1::RefreshList(int iPeriod)
{
	m_List.DeleteAllItems();

	CString strNum[] = {"⑩", "①", "②", "③", "④", "⑤", "⑥", "⑦", "⑧", "⑨"};
	CString str = _T(" ");
	UINT n1, n2, col;
	C3D CNum, CNumNext;

	BOOL bCtrl	= WND::IsCtrlDown();
	BOOL bShift	= WND::IsShiftDown();
	BOOL bAlt	= WND::IsAltDown();

	// 历史
	for(int i = 0; i < iPeriod; ++i)
	{
		if(i > 0)
			CNumNext = CNum;

		CNum = pHistory->GetCNum(i);

		str.Empty();
		m_List.AddItem(pHistory->GetPeriodStr(i).Right(5), CNum.ToString(),
			str, str, str, str, str, str, str, str, str, str, str, str,
			str, str, str, str, str, str, str, str, str, str, str, str, str, str
			);

		if(CNum.IsG1())
		{
			m_List.SetItemColor(i, 0, crText, crRed);
			m_List.SetItemColor(i, 1, crText, crRed);
		}
		else if(CNum.IsG3())
		{
			m_List.SetItemColor(i, 0, crText, crYellow);
			m_List.SetItemColor(i, 1, crText, crYellow);
		}
		else if(i & 1 )
		{
			m_List.SetItemColor(i, 0, crText, crBack);
			m_List.SetItemColor(i, 1, crText, crBack);
		}

		if(i & 1)
		{
			for(int j = 2; j < m_List.GetColumns(); ++j)
				m_List.SetItemColor(i, j, crText, crBack);
		}

		col = 2;

		// 奇偶码
		n1 = CNum.OddCnt();
		str.Format(_T("%d:%d"), n1, 3 - n1);
		m_List.SetItemText(i, col++, str);

		// 大小码
		n1 = CNum.LargeCnt();
		str.Format(_T("%d:%d"), n1, 3 - n1);
		m_List.SetItemText(i, col++, str);

		// 质合码
		n1 = CNum.PrimeCnt();
		str.Format(_T("%d:%d"), n1, 3 - n1);
		m_List.SetItemText(i, col++, str);

		// 连号
		n1 = CNum.ContinueCnt();
		str.Format(_T("%d"), n1);
		m_List.SetItemText(i, col++, str);
		
		// 均值
		n2 = CNum.Ave();
		str.Format(_T("%d"), n2);
		m_List.SetItemText(i, col++, str);
		
		// 和值
		n1 = CNum.Sum();
		str.Format(_T("%d"), n1);
		m_List.SetItemText(i, col++, str);

		// 和尾
		n2 = CNum.Tail();
		str.Format(_T("%d"), n2);
#ifdef _UNRESTRICT2_
		if(CNum.Ent() == n2)
			str += strNum[CNum.Ent()];
#endif
		m_List.SetItemText(i, col++, str);

#ifdef _UNRESTRICT2_
		if(i > 0)
		{
			if(bShift)
			{
				// 本期和尾杀下期跨度
				if( CNumNext.Span() == n2 )
					m_List.SetItemColor(i, col - 1, crText2, crPurple);
			}
			else
			{
				// 本期个位杀下期跨度
				if(CNumNext.Span() == CNum.Ent())
					m_List.SetItemColor(i, col - 1, crText2, crRed);
			}
		}
#endif

		// 跨度
		n1 = CNum.Span();
		str.Format(_T("%d"), n1);
#ifdef _UNRESTRICT2_
		if( CNum.Hun() == n1 )
			str += strNum[n1];
#endif
		m_List.SetItemText(i, col++, str);

#ifdef _UNRESTRICT2_
		if(i > 0)
		{
			if(bShift)
			{
				// 本期跨度杀下期和尾
				if(CNumNext.Tail() == n1)
					m_List.SetItemColor(i, col - 1, crText2, crPurple);
			}
			else
			{
				// 本期百位杀下期和尾
				if( CNumNext.Tail() == CNum.Hun() )
					m_List.SetItemColor(i, col - 1, crText2, crRed);
			}
		}
#endif
		
		// 形态
		m_List.SetItemText(i, col++, CNum.OddStr());	// 奇偶
		m_List.SetItemText(i, col++, CNum.LargeStr());	// 大小
		m_List.SetItemText(i, col++, CNum.PrimeStr());	// 质合
		m_List.SetItemText(i, col++, CNum.AC3Str());	// 012路

		C3D CNum2;

		// 两码差
		CNum2 = CNum.TwoNumSpan();
		for(int j = 0; j < 3; ++j)
			m_List.SetItemText(i, col++, EMFC::Int2Str(CNum2[j]));
		
		// 两码和
		CNum2 = CNum.TwoNumSum();
		for(int j = 0; j < 3; ++j)
			m_List.SetItemText(i, col++, EMFC::Int2Str(CNum2[j]));

		// 两积
		CNum2 = CNum.TwoNumMul();
		for(int j = 0; j < 3; ++j)
			m_List.SetItemText(i, col++, EMFC::Int2Str(CNum2[j]));
		
		// 大号连续
		m_List.SetItemText(i, col++, EMFC::Int2Str(CNum.ContinueLarge()));
		
		// 小号连续
		m_List.SetItemText(i, col++, EMFC::Int2Str(CNum.ContinueSmall()));
		
		// 奇号连续
		m_List.SetItemText(i, col++, EMFC::Int2Str(CNum.ContinueOdd()));
		
		// 偶号连续
		m_List.SetItemText(i, col++, EMFC::Int2Str(CNum.ContinueEven()));
		
		// 质号连续
		m_List.SetItemText(i, col++, EMFC::Int2Str(CNum.ContinuePrime()));
		
	}
}

void CStat1::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	GetParent()->GetParent()->SendMessage(WM_CLOSE);
	CDialog::OnRButtonDown(nFlags, point);
}
