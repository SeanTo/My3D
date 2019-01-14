// DataChart.cpp : implementation file
//

#include "stdafx.h"
#include "DataChart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataChart dialog


CDataChart::CDataChart(CWnd* pParent /*=NULL*/)
	: CDialog(CDataChart::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataChart)
	m_iPeriod = 1;
	//}}AFX_DATA_INIT

	pApp = (CMy3DApp *)AfxGetApp();
	pHistory = pApp->GetHistory();
	m_Data.RemoveAll();
	m_nType = 0;

	pOldPen = NULL;
	penLine.CreatePen(PS_SOLID, 0, RGB(0, 255, 0));

	fontVert.CreateFont(12, 0, 900, 0, 400, 0, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,DEFAULT_PITCH, _T("宋体"));

	fontHori.CreateFont(12, 0, 0, 0, 400, 0, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,DEFAULT_PITCH, _T("宋体"));

	xMin = 0;
	xMax = 0;
	yMin = 0;
	yMax = 0;
	cx = 0;
	cy = 0;
	
	nPeriod = 0;
}


void CDataChart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataChart)
	DDX_Control(pDX, IDC_CMB_ANALYSE_TYPE, m_cmbAnalyseType);
	DDX_Radio(pDX, IDC_RAD_DA1, m_iPeriod);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataChart, CDialog)
	//{{AFX_MSG_MAP(CDataChart)
	ON_CBN_SELCHANGE(IDC_CMB_ANALYSE_TYPE, OnSelchangeCmbAnalyseType)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RAD_DA1, IDC_RAD_DA4, OnSelectPeriod)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataChart message handlers

BOOL CDataChart::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDataChart::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	MoveWindow(pApp->rcScreen);
	
	m_cmbAnalyseType.AddString("奇码数");
	m_cmbAnalyseType.AddString("偶码数");
	m_cmbAnalyseType.AddString("小码数");
	m_cmbAnalyseType.AddString("大码数");
	m_cmbAnalyseType.AddString("质码数");
	m_cmbAnalyseType.AddString("新码数");
	m_cmbAnalyseType.AddString("孤码数");
	m_cmbAnalyseType.AddString("斜码数");
	m_cmbAnalyseType.AddString("左斜数");
	m_cmbAnalyseType.AddString("右斜数");
	m_cmbAnalyseType.AddString("连号数");
	m_cmbAnalyseType.AddString("平均值");
	m_cmbAnalyseType.AddString("跨度");
	m_cmbAnalyseType.AddString("和值");
	m_cmbAnalyseType.AddString("百十跨");
	m_cmbAnalyseType.AddString("百个跨");
	m_cmbAnalyseType.AddString("十个跨");
	m_cmbAnalyseType.AddString("百十和");
	m_cmbAnalyseType.AddString("百个和");
	m_cmbAnalyseType.AddString("十个和");
	m_cmbAnalyseType.AddString("百十积");
	m_cmbAnalyseType.AddString("百个积");
	m_cmbAnalyseType.AddString("十个积");
	m_cmbAnalyseType.AddString("和尾");
	m_cmbAnalyseType.AddString("大号连续");
	m_cmbAnalyseType.AddString("小号连续");
	m_cmbAnalyseType.AddString("奇号连续");
	m_cmbAnalyseType.AddString("偶号连续");
	m_cmbAnalyseType.AddString("质号连续");
	m_cmbAnalyseType.AddString("遗漏总值");
	m_cmbAnalyseType.AddString("和值振幅");
	m_cmbAnalyseType.AddString("百位号码");
	m_cmbAnalyseType.AddString("十位号码");
	m_cmbAnalyseType.AddString("个位号码");
	m_cmbAnalyseType.AddString("奇偶形态");
	m_cmbAnalyseType.AddString("大小形态");
	m_cmbAnalyseType.AddString("质合形态");
	m_cmbAnalyseType.AddString("012路");
	
	GetClientRect(&rcPaint);
	rcPaint.InflateRect(-5, -55);
	rcPaint.top += 10;
	rcPaint.left += 50;

	m_cmbAnalyseType.SetCurSel(m_nType);

	if( !pHistory->IsNull() )
	{
		int n = pHistory->GetCount();
		nPeriod = n > 100 ? 100 : n;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDataChart::OnSelchangeCmbAnalyseType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);	
	
	Invalidate();
}

void CDataChart::OnSelectPeriod(UINT nID)
{
	ASSERT(IDC_RAD_DA1 <= nID && IDC_RAD_DA4 >= nID);
	UpdateData(TRUE);

	GetPeriod(nID - IDC_RAD_DA1);
	
	Invalidate();
}

void CDataChart::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	dc.Rectangle(&rcPaint);
	if(NULL != pHistory)
	{
		Graph(&dc, rcPaint);
	}
	
	// Do not call CDialog::OnPaint() for painting messages
}

VOID CDataChart::Graph(CPaintDC *pDC, const CRect &rc)
{
	if(NULL == pHistory || 0 == nPeriod)
	{
		return;
	}
	
	m_Data.RemoveAll();
	yMax = StatData(m_cmbAnalyseType.GetCurSel(), &m_Data);
	xMax = m_Data.GetSize();

	BOOL bYes = 3 < yMax && yMax < 10 && m_Data.GetSize() >= 30;

	if(0 == xMax)
	{
		return;
	}

	if(0 == m_Data.GetSize())
	{
		return;
	}
	
	cx = rc.Width() / (xMax + 1);
	cy = rc.Height() / (yMax + 1);

	if(0 == cx)
	{
		cx = 1;
		xMax = rc.Width() - 10;
	}

	pDC->Rectangle(&rc);
	
	pOldPen = pDC->SelectObject(&penLine);

	xMin = rc.left + cx;
	yMin = rc.bottom - 1;
	pDC->MoveTo(xMin, yMin - m_Data.GetAt(xMax - 1) * cy);
	pDC->SetBkMode(TRANSPARENT);
	
	for(int i = xMax - 2; i >= 0; --i)
	{
		xMin += cx;
		pDC->LineTo(xMin, yMin - m_Data.GetAt(i) * cy);
	}
	pDC->SelectObject(pOldPen);

	CString str;
	UINT v;
	xMin = rc.left + cx;
	pOldFont = pDC->SelectObject(&fontHori);
	for(int i = xMax - 1; i >= 0; --i)
	{
		v = m_Data.GetAt(i);
		str.Format(_T("%d"), v);

		pDC->TextOut(xMin, yMin - v * cy - 20, str);
		xMin += cx;
	}

	str = _T("走势分析(右键可关闭窗口)");
	if(bYes)
	{
		int n0 = m_Data.GetAt(0);
		int n1 = n0;
		int n2;
		CUIntArray aHis;
		for(int i = 1; i < m_Data.GetSize(); ++i)
		{
			n2 = m_Data.GetAt(i);
			if(n2 == n0)
			{
				if( !EMFC::IsInArray((UINT)n1, aHis) )
					aHis.Add(n1);
			}
			n1 = n2;
		}

		if(aHis.GetSize() > 0)
		str += CString(" - 当前点位历史变化: ") + EMFC::PrintArray(aHis);
	}
	SetWindowText(str);
	
	pDC->SelectObject(pOldFont);
	
	DrawCoord(pDC, rc);
}

/*
 *	柱状图
 */
/*
VOID CDataChart::Histogram()
{

}
*/

VOID CDataChart::GetPeriod(int iSel)
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
		nPeriod = pHistory->GetPeriod(0) % 1000;
		nPeriod = n > nPeriod ? nPeriod : n;
		break;
	default:
		nPeriod = n;
		break;
	}
}

BOOL CDataChart::DrawCoord(CPaintDC *pDC, const CRect &rc)
{
	CString str;
	int y0 = rc.bottom - 1;
	int x0 = rc.left - 30;
	int x1 = rc.left;
	int iType = m_cmbAnalyseType.GetCurSel();

	pOldFont = pDC->SelectObject(&fontHori);
	for(int i = 0; i <= yMax; ++i)
	{
		if( yMax >= 30 && (i % 5 != 0) )
		{
			y0 -= cy;
			continue;
		}
		else if(yMax >= 10 && (i & 1) && iType != 37)
		{
			y0 -= cy;
			continue;
		}
		
		pDC->MoveTo(x0, y0);
		pDC->LineTo(x1, y0);

		if(iType <= 33)
		{
			str.Format(_T("%4d"), i);
			pDC->TextOut(x0, y0 - 16, str);
		}
		else if(iType < 37) // 大小、奇偶、质合形态
		{
			if(i < 8)
			{
				str.Format(_T("=%d"), i);
				str = C3D::GetFormStr(m_cmbAnalyseType.GetCurSel() - 34, i) + str;
				pDC->TextOut(x0 - 20, y0 - 16, str);
			}
		}
		else // 012 路
		{
			if(i < 30)
			{
				str.Format(_T("=%2d"), i);
				str = C3D::GetAC3Str(i) + str;
				pDC->TextOut(x0 - 15, y0 - 12, str);
			}
		}

		y0 -= cy;
	}

	x0 = rc.left + cx * xMax;
	y0 = rc.bottom;
	int y1 = rc.bottom + 45;

	pDC->SelectObject(&fontVert);
	for(int i = 0; i <= xMax; i += 5)
	{
		pDC->MoveTo(x0, y0);
		pDC->LineTo(x0, y1);

		str = pHistory->GetPeriodStr(i).Right(5);
		pDC->TextOut(x0 - 12, y1 - 10, str);

		x0 -= cx * 5;
	}	
	pDC->SelectObject(pOldFont);

	return FALSE;
}

int CDataChart::StatData(UINT nType, CUIntArray *p)
{
	p->RemoveAll();

	if(NULL == pHistory || pHistory->IsNull() || 0 == nPeriod )
		return -1;

	UINT nCount = pHistory->GetCount();
	int iMax = -1, cnt, loop;
	C3D CNum, CNumLast;

	switch( nType )
	{
	case 0: // 奇码数
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).OddCnt();
			p->Add(cnt);


			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 1: // 偶码数
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = 3 - pHistory->GetCNum(i).OddCnt();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 2: // 小码数
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = 3 - pHistory->GetCNum(i).LargeCnt();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 3: // 大码数
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).LargeCnt();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 4: // 质号数
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).PrimeCnt();
			
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 5: // 新码数
		loop = nPeriod + 1 <= nCount ? nPeriod + 1 : nCount;
		for(int i = 0; i < loop - 1; ++i)
		{
			CNum = pHistory->GetCNum(i);
			CNumLast = pHistory->GetCNum(i + 1);

			cnt = CNumLast.CountNew(CNum);
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 6: // 孤码数
		loop = nPeriod + 1 <= nCount ? nPeriod + 1 : nCount;
		for(int i = 0; i < loop - 1; ++i)
		{
			CNum = pHistory->GetCNum(i);
			CNumLast = pHistory->GetCNum(i + 1);

			cnt = CNumLast.CountAlone(CNum);
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 7: // 斜码数
		loop = nPeriod + 1 <= nCount ? nPeriod + 1 : nCount;
		for(int i = 0; i < loop - 1; ++i)
		{
			CNum = pHistory->GetCNum(i);
			CNumLast = pHistory->GetCNum(i + 1);

			cnt = CNumLast.CountTilted(CNum);
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 8: // 左斜数
		loop = nPeriod + 1 <= nCount ? nPeriod + 1 : nCount;
		for(int i = 0; i < loop - 1; ++i)
		{
			CNum = pHistory->GetCNum(i);
			CNumLast = pHistory->GetCNum(i + 1);

			cnt = CNumLast.CountLeft(CNum);
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 9: // 右斜数
		loop = nPeriod + 1 <= nCount ? nPeriod + 1 : nCount;
		for(int i = 0; i < loop - 1; ++i)
		{
			CNum = pHistory->GetCNum(i);
			CNumLast = pHistory->GetCNum(i + 1);

			cnt = CNumLast.CountRight(CNum);
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 10: // 连号数
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).ContinueCnt();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 11: // 平均值
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).Ave();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 12: // 跨度
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).Span();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 13: // 和值
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).Sum();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 14: // 百十跨
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).TwoNumSpan().Hun();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 15: // 百个跨
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).TwoNumSpan().Ten();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 16: // 十个跨
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).TwoNumSpan().Ent();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 17: // 百十和
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).TwoNumSum().Hun();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 18: // 百个和
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).TwoNumSum().Ten();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 19: // 十个和
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).TwoNumSum().Ent();
			p->Add(cnt);
			
			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 20: // 百十积
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).TwoNumMul().Hun();
			p->Add(cnt);
			
			if(cnt > iMax)
				iMax = cnt;
		}
		break;;
	case 21: // 百个积
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).TwoNumMul().Ten();
			p->Add(cnt);
			
			if(cnt > iMax)
				iMax = cnt;
		}
		break;;
	case 22: // 十个积
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).TwoNumMul().Ent();
			p->Add(cnt);
			
			if(cnt > iMax)
				iMax = cnt;
		}
		break;;

	case 23: // 和尾
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).Tail();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 24: // 大号连续
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).ContinueLarge();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 25: // 小号连续
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).ContinueSmall();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 26: // 奇号连续
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).ContinueOdd();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 27: // 偶号连续
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).ContinueEven();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 28: // 质号连续
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).ContinuePrime();
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 29: // 遗漏总值
		for(UINT i = 0; i < nPeriod; ++i)
		{
			CNum = pHistory->GetCNum(i);
			cnt = pHistory->StatMiss(i + 1, CNum);

			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 30: // 和值振幅
		for(UINT i = 0; i < nPeriod; ++i)
		{
			if(i + 1 >= nCount)
				break;
			
			cnt = abs(pHistory->GetCNum(i).Sum() - pHistory->GetCNum(i+1).Sum());
			p->Add(cnt);

			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 31: // 百位
		for(UINT i = 0; i < nPeriod; ++i)
		{
			p->Add( cnt = pHistory->GetCNum(i).Hun() );
			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 32: // 十位
		for(UINT i = 0; i < nPeriod; ++i)
		{
			p->Add( cnt = pHistory->GetCNum(i).Ten() );
			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 33: // 个位
		for(UINT i = 0; i < nPeriod; ++i)
		{
			p->Add( cnt = pHistory->GetCNum(i).Ent() );
			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 34: // 奇偶形态
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).OddModality();
			p->Add(cnt);
			
			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 35: // 大小形态
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).LargeModality();
			p->Add(cnt);
			
			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 36: // 质合形态
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).PrimeModality();
			p->Add(cnt);
			
			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	case 37: // 012路
		for(UINT i = 0; i < nPeriod; ++i)
		{
			cnt = pHistory->GetCNum(i).AC3Modality();
			p->Add(cnt);
			
			if(cnt > iMax)
				iMax = cnt;
		}
		break;
	default:
		break;
	}

	return iMax;
}

void CDataChart::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
	GetClientRect(&rcPaint);
	rcPaint.InflateRect(-5, -55);
	rcPaint.top += 10;
	rcPaint.left += 30;

	Invalidate();
}

VOID CDataChart::SetType(UINT nType)
{
	if(37 < nType)
	{
		return;
	}

	m_nType = nType;
}

void CDataChart::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnCancel();
	CDialog::OnRButtonDown(nFlags, point);
}
