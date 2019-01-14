// WinStat.cpp : implementation file
//

#include "stdafx.h"
#include "Stat3.h"

#include "..\Share\WND.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStat3 dialog


CStat3::CStat3(CWnd* pParent /*=NULL*/)
	: CDialog(CStat3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStat3)
	m_strTip = _T("");
	//}}AFX_DATA_INIT

	pApp = (CMy3DApp *)AfxGetApp();
	pHistory = pApp->GetHistory();
}


void CStat3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStat3)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_WIN_STAT_TIP, m_strTip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStat3, CDialog)
	//{{AFX_MSG_MAP(CStat3)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, OnRclickList)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//	ON_CBN_SELCHANGE(IDC_COM_AHP, OnSelchangeComAhp)

/////////////////////////////////////////////////////////////////////////////
// CStat3 message handlers

BOOL CStat3::PreTranslateMessage(MSG* pMsg) 
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

BOOL CStat3::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rc;
	rc = pApp->rcScreen;
	MoveWindow(&rc);

	rc.DeflateRect(0, 0, 200, 100);
	GetDlgItem(IDC_LIST)->MoveWindow(&rc);
	
	rc.SetRect(rc.Width(), rc.top, rc.Width() + 190, rc.bottom);
	GetDlgItem(IDC_WIN_STAT_TIP)->MoveWindow(&rc);
	
	// TODO: Add extra initialization here
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.SetHeadings(_T("期号,36;开奖,45;百位推荐,80;十位推荐,80;个位推荐,80;\
		杀百位,48;杀十位,48;杀个位,48;定两码跨,60;定两码和,60;定两码积,60;"), LVCFMT_CENTER );
	m_List.SetBkColor(RGB(128,128,128));
	m_List.LoadColumnInfo();
	
	m_strTip = CString(_T("①百十个位推荐码\r\n\r\n"))
		+_T("　　根据推荐码分析条件中选择的期数，分析最近的开奖数据，按一定的算法将 0-9 按概率排序，")
		+_T("选择分析的期数不同推荐码的结果也不同。")
		+_T("根据选择的推荐码数，用排序后的前n个号码匹配下期的开奖结果，做正误颜色标记。\r\n")
		+_T("　　红色=相应位错误\r\n")
		+_T("　　青色=相应位正确\r\n")
		+_T("　　绿色=百十个位均正确\r\n\r\n")
		+_T("　　主界面选择号码中的推荐按钮就是使用这里的 9 码推荐结果。\r\n")
		+_T("　　6 码以下准确率很低，可以作为垃圾复式来杀。9码推荐+6码垃可以杀近一半号。\r\n\r\n")
		+_T("②百十个位杀码\r\n\r\n")
		+_T("　　红色=杀码错误\r\n")
		+_T("　　绿色=杀码正确\r\n\r\n")
		+_T("③定两码和、差、积\r\n\r\n")
		+_T("　　白色=错误\r\n")
		+_T("　　绿色=出1个\r\n")
		+_T("　　黄色=出2个\r\n")
		+_T("　　红色=出3个\r\n\r\n")
		+_T("　　两码跨、和、积统计次数默认重值计多次，按住 ALT 刷新(点上面的期号)则按重值计1次统计。\r\n\r\n")
		;
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CStat3::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	GetParent()->GetParent()->SendMessage(WM_CLOSE);
	*pResult = 0;
}

void CStat3::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	GetParent()->GetParent()->SendMessage(WM_CLOSE);
	
	CDialog::OnRButtonDown(nFlags, point);
}

VOID CStat3::RefreshList(int iNum /* = 9 */, int iNumPeriod /* = 20 */, int iPeriod /* = 50 */)
{
	m_List.DeleteAllItems();

	int iCountHistory = pHistory->GetCount();
	if(iCountHistory < 7)
		return;

	C3D CNum, CNum2, CNumNext;
	CString str = _T(" ");
	int nBlank = 2;	// 空二行
	int loopCnt;		// 循环计数
	int nCntOK[3], nCntErr[3];	// 正误统计

	m_List.AddItem(str, _T("正:误"), str, str, str, str, str, str, str, str, str/*, str, str, str, str, str, str*/);
	m_List.AddItem(str, _T("准确率"), str, str, str, str, str, str, str, str, str/*, str, str, str, str, str, str*/);

	// 历史
	loopCnt = iPeriod + 1 < iCountHistory ? iPeriod + 1 : iCountHistory;
	for(int i = 0; i < loopCnt; ++i)
	{
		CNum = pHistory->GetCNum(i);
		
		str.Empty();
		m_List.AddItem(pHistory->GetPeriodStr(i).Right(5), CNum.ToString(),
			str, str, str, str, str, str, str, str, str, str, str, str, str);
		
		if(CNum.IsG1())
		{
			m_List.SetItemColor(i + nBlank, 0, crText, crRed);
			m_List.SetItemColor(i + nBlank, 1, crText, crRed);
		}
		else if(CNum.IsG3())
		{
			m_List.SetItemColor(i + nBlank, 0, crText, crYellow);
			m_List.SetItemColor(i + nBlank, 1, crText, crYellow);
		}
		else 
		if(i & 1 )
		{
			m_List.SetItemColor(i + nBlank, 0, crText, crBack);
			m_List.SetItemColor(i + nBlank, 1, crText, crBack);
		}
	}

	int iLines = m_List.GetItemCount() - nBlank;
	int iCol = 2;
	
	// 推荐
	ZeroMemory(nCntOK, 3 * sizeof(int));
	ZeroMemory(nCntErr, 3 * sizeof(int));
	CUIntArray arrAMP;

	loopCnt = iLines + iNumPeriod <= iCountHistory ? iLines : iCountHistory - iNumPeriod;
	for(int i = 0; i < loopCnt; ++i)
	{
		BOOL ff[3];
		for(int j = 0; j < 3; ++j)
		{
			pHistory->StatAMP(iNumPeriod, arrAMP, j, i);
			str = EMFC::PrintArray(arrAMP, iNum, 0, -1, _T("%d")) + _T("-")
				+ EMFC::PrintArray(arrAMP, -1, iNum);
			m_List.SetItemText(i + nBlank, j + iCol, str);

			if(i > 0)
			{
				CNum = pHistory->GetCNum(i - 1);

				ff[j] = EMFC::IsInArray(CNum[j], str, iNum);
				if( ff[j] )
					++nCntOK[j];
				else
					++nCntErr[j];
			}
		}

		if( ff[0] && ff[1] && ff[2] )
		{
			for(int j = 0; j < 3; ++j)
			{
				m_List.SetItemColor(i + nBlank, j + iCol, crText2, crGreen);
			}
		}
		else
		{
			for(int j = 0; j < 3; ++j)
			{
				if(ff[j])
					m_List.SetItemColor(i + nBlank, j + iCol, crText, crCyan);
				else
					m_List.SetItemColor(i + nBlank, j + iCol, crText, crRed);
			}
		}
	}
	// 准确率统计
	for(int i = 0; i < 3; ++i)
	{
		str.Format(_T("%d:%d"), nCntOK[i], nCntErr[i]);
		m_List.SetItemText(0, iCol + i, str);

		if(0 != nCntOK[i] + nCntErr[i])
		{
			str.Format(_T("%.1f%%"), nCntOK[i] * 100.0 / (nCntOK[i] + nCntErr[i]));
			m_List.SetItemText(1, iCol + i, str);
		}
	}
	iCol += 3;
	
	// 定位杀
	ZeroMemory(nCntOK, 3 * sizeof(int));
	ZeroMemory(nCntErr, 3 * sizeof(int));

	loopCnt = iLines + 20 < iCountHistory ? iLines : iCountHistory - 20;
	for(int i = 0; i < loopCnt; ++i)
	{
		CNum = pHistory->Kill1NumsPos(i);
		
		for(int j = 0; j < 3; ++j )
		{
			str = EMFC::Int2Str( CNum[j] );
			m_List.SetItemText(i + nBlank, iCol +j, str);

			if(0 == i)
				continue;

			CNumNext = pHistory->GetCNum(i - 1);
			if(CNumNext[j] != CNum[j])
			{
				m_List.SetItemColor(i + nBlank, iCol + j, crText, crGreen);
				++nCntOK[j];
			}
			else
			{
				m_List.SetItemColor(i + nBlank, iCol + j, crText, crRed);
				++nCntErr[j];
			}
		}
	}		
	// 准确率统计
	for(int i = 0; i < 3; ++i)
	{
		str.Format(_T("%d:%d"), nCntOK[i], nCntErr[i]);
		m_List.SetItemText(0, iCol + i, str);
		
		if(0 != nCntOK[i] + nCntErr[i])
		{
			str.Format(_T("%.1f%%"), nCntOK[i] * 100.0 / (nCntOK[i] + nCntErr[i]));
			m_List.SetItemText(1, iCol + i, str);
		}
	}
	iCol += 3;
	
	// 两码差、和、积
	ZeroMemory(nCntOK, 3 * sizeof(int));
	ZeroMemory(nCntErr, 3 * sizeof(int));
	int iPeriod2 = 1;
	int iTmp;

	BOOL bAlt = WND::IsAltDown();
	
#ifdef _UNRESTRICT_
	if( WND::IsCharDown( _T('2') ) )		iPeriod2 = 2;
	else if( WND::IsCharDown( _T('3') ) )	iPeriod2 = 3;
	else if( WND::IsCharDown( _T('4') ) )	iPeriod2 = 4;
#endif

	loopCnt = iLines + iPeriod2 - 1 <= iCountHistory ? iLines : iCountHistory - iPeriod2 + 1;
	for(int i = 0; i < loopCnt; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			str = pHistory->MissTwoNum(iPeriod2, i, j);
			if( !str.IsEmpty() )
				m_List.SetItemText(i + nBlank, iCol + j, str);

			if(i > 0)
			{
				CNumNext = pHistory->GetCNum(i - 1);
				if(0 == j)			CNum2 = CNumNext.TwoNumSpan();
				else if(1 == j)		CNum2 = CNumNext.TwoNumSum();
				else				CNum2 = CNumNext.TwoNumMul();

				iTmp = CNum2.CountInStr(str, bAlt);
				if( iTmp > 0 )
				{
					++nCntOK[j];
					if(1 == iTmp)
						m_List.SetItemColor(i + nBlank, iCol + j, crText, crGreen);
					else if(2 == iTmp)
						m_List.SetItemColor(i + nBlank, iCol + j, crText, crYellow);
					else
						m_List.SetItemColor(i + nBlank, iCol + j, crText, crRed);
				}
				else
				{
					++nCntErr[j];
//					m_List.SetItemColor(i + nBlank, iCol + j, crText, crRed);
				}
			}
		}
	}
	// 准确率统计
	for(int i = 0; i < 3; ++i)
	{
		str.Format(_T("%d:%d"), nCntOK[i], nCntErr[i]);
		m_List.SetItemText(0, iCol + i, str);
		
		if(0 != nCntOK[i] + nCntErr[i])
		{
			str.Format(_T("%.1f%%"), nCntOK[i] * 100.0 / (nCntOK[i] + nCntErr[i]));
			m_List.SetItemText(1, iCol + i, str);
		}
	}
	iCol += 3;

	// 第一行未统计
	for(int i = 2; i < m_List.GetColumns(); ++i)
	{
		m_List.SetItemColor(nBlank, i, crText, crBack);
	}
}
