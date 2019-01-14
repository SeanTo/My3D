// Stat5.cpp : implementation file
//

#include "stdafx.h"
#include "Stat5.h"

#include "..\Share\WND.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStat5 dialog


CStat5::CStat5(CWnd* pParent /*=NULL*/)
	: CDialog(CStat5::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStat5)
	m_strTip = _T("");
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	pApp = (CMy3DApp *)AfxGetApp();
	pHistory = pApp->GetHistory();
}


void CStat5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStat5)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_OTHER_STAT_TIP, m_strTip);
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStat5, CDialog)
	//{{AFX_MSG_MAP(CStat5)
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY(NM_RCLICK, IDC_LIST, OnRclickList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStat5 message handlers

BOOL CStat5::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rc;
	rc = pApp->rcScreen;
	MoveWindow(&rc);
	
	rc.DeflateRect(0, 0, 200, 100);
	GetDlgItem(IDC_LIST)->MoveWindow(&rc);
	
	rc.SetRect(rc.Width(), rc.top, rc.Width() + 190, rc.bottom);
	GetDlgItem(IDC_OTHER_STAT_TIP)->MoveWindow(&rc);
	
	// TODO: Add extra initialization here
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.SetHeadings(_T("期号,36;开奖,36;动态智能,60;段式-强,60;段式-弱,60;\
		号码继承,60;012继承,60;形态反转,120;均值2-7,60;金三角,60;步长法,60;近期相关,60;\
		当前选择,60;"), LVCFMT_CENTER );
	m_List.SetBkColor(RGB(128,128,128));
	m_List.LoadColumnInfo();

	m_strTip = CString(_T("\r\n　　红色: 表示当期用该方法生成大底，用下期开奖号验证，结果错误。"))
		+ _T("\r\n　　第二行的准确率按红色标记数计算。")
		+ _T("\r\n\r\n　　灰色: 降一级的提示，未用作自动大底过滤生成。")
		+ _T("\r\n　　号码继承: 1个号继承")
		+ _T("\r\n　　012 继承: 1或2个路数继承")
		+ _T("\r\n　　形态反转: 1个形态反转")
		+ _T("\r\n\r\n\r\n当前选择：")
		+ _T("\r\n\r\n　　这一列是动态的，可以用来查看组合算法或未列出统计的单个算法的统计结果。")
		+ _T("\r\n\r\n　　①打开自动大底选项")
		+ _T("\r\n　　②勾选参与统计的大底")
		+ _T("\r\n　　③关闭对话框")
		+ _T("\r\n　　④再打开数据分析")
		+ _T("\r\n　　④当前选择即为统计结果")
		+ _T("\r\n\r\n　　即用该列可以查任一算法、或任意多个算法组合的准确率统计结果。")
		;
	
//	RefreshList();
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStat5::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	GetParent()->GetParent()->SendMessage(WM_CLOSE);
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CStat5::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	GetParent()->GetParent()->SendMessage(WM_CLOSE);
	
	*pResult = 0;
}

BOOL CStat5::PreTranslateMessage(MSG* pMsg) 
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

void CStat5::RefreshList(int iPeriod/* = 50*/)
{
	int iCountHistory = pHistory->GetCount();
	if(iCountHistory < 7)
		return;
	
	m_List.DeleteAllItems();
	
	CString str = _T(" ");

	m_List.AddItem(str, _T("正:误"), str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str);
	m_List.AddItem(str, _T("准确率"), str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str);
	
	C3D CNum, CNum1, CNum2, CNumNext;
	int loopCnt, iBlank = 2;		// 空行
	
	// 历史
	loopCnt = iPeriod + 1 <= iCountHistory ? iPeriod + 1 : iCountHistory;
	for(int i = 0; i < loopCnt; ++i)
	{
		CNum = pHistory->GetCNum(i);

		str.Empty();
		m_List.AddItem(pHistory->GetPeriodStr(i).Right(5), CNum.ToString(),
			str, str, str, str, str, str, str, str, str, str,
			str, str, str, str, str, str, str, str, str);
		
		if(CNum.IsG1())
		{
			m_List.SetItemColor(i + iBlank, 0, crText, crRed);
			m_List.SetItemColor(i + iBlank, 1, crText, crRed);
		}
		else if(CNum.IsG3())
		{
			m_List.SetItemColor(i + iBlank, 0, crText, crYellow);
			m_List.SetItemColor(i + iBlank, 1, crText, crYellow);
		}
		else if(i & 1 )
		{
			m_List.SetItemColor(i + iBlank, 0, crText, crBack);
			m_List.SetItemColor(i + iBlank, 1, crText, crBack);
		}
	}

	// 辅助控制键
	BOOL bCtrl = WND::IsCtrlDown();
	BOOL bShift = WND::IsShiftDown() && !bCtrl;
	BOOL bAlt = WND::IsAltDown();
	
	int iLines = m_List.GetItemCount() - iBlank;
	int iCntOk[12], iCntErr[12], n;
	int iCol = 2, loop;

	bitset<32> bSel;

	// 自动大底
	ZeroMemory( iCntOk, 12 * sizeof(UINT) );
	ZeroMemory( iCntErr, 12 * sizeof(UINT) );

	loop = 10;
	loopCnt = iLines <= iCountHistory ? iLines : iCountHistory - 1;
	for(int i = 1; i < loopCnt; ++i)
	{
		CNum = pHistory->GetNum(i - 1);
		
		if( !( !bCtrl && !bShift || bCtrl && CNum.IsG6() || bShift && CNum.IsG3() ) )
			continue;
		
		CNumNext = pHistory->GetCNum(i);
		for(int j = 0; j < loop; ++j)
		{
			bSel.reset();
			bSel.set(j);

			n = pHistory->FilterAutoBase(CNum, bSel, i, 0, 0);
			
			if( 0 == n )
			{
				++iCntOk[j];

				// 降级提示，灰色标记
				if( 3 == j)
				{
					if( CNum.CountSame(CNumNext) > 0 ) // 号码继承
					{
						m_List.SetItemText(iBlank + i - 1, iCol + j, CNum.ToString());
						m_List.SetItemText(iBlank + i, iCol + j, CNumNext.ToString());
						
						m_List.SetItemColor(iBlank + i, iCol + j, crText, crGray);
					}
				}
				else if( 4 == j ) // 012 继承
				{
					CNum1 = CNum.AC3ModNum();
					CNum2 = CNumNext.AC3ModNum();

					if( CNum1.CountSame(CNum2) > 0)
					{
						m_List.SetItemText(iBlank + i - 1, iCol + j, CNum.AC3Str());
						m_List.SetItemText(iBlank + i, iCol + j, CNumNext.AC3Str());

						m_List.SetItemColor(iBlank + i, iCol + j, crText, crGray);
					}
				}
				else if( 5 == j ) // 形态反转
				{
					// 奇偶
					n = 0;
					CNum1 = CNumNext.OddModNum();
					CNum2 = CNum.OddModNum();
					n += (0 == CNum1.CountSame(CNum2));
					// 大小
					CNum1 = CNumNext.LargeModNum();
					CNum2 = CNum.LargeModNum();
					n += (0 == CNum1.CountSame(CNum2));
					// 质合
					CNum1 = CNumNext.PrimeModNum();
					CNum2 = CNum.PrimeModNum();
					n += (0 == CNum1.CountSame(CNum2));
					
					if( n > 0 )
					{
						// 显示当期和下期的形态
						str = CNum.OddStr() + _T("-")
							+ CNum.LargeStr() + _T("-")
							+ CNum.PrimeStr();
						m_List.SetItemText(iBlank + i - 1, iCol + j, str);
						
						str = CNumNext.OddStr() + _T("-")
							+ CNumNext.LargeStr() + _T("-")
							+ CNumNext.PrimeStr();
						m_List.SetItemText(iBlank + i, iCol + j, str);

						m_List.SetItemColor(iBlank + i, iCol + j, crText, crGray);
					}
				}
			}
			else
			{
				++iCntErr[j];
				m_List.SetItemColor(iBlank + i, iCol + j, crText, crRed);

				if(0 == j) // 动态智能
				{
					// 显示出错的子算法号
					int e = pHistory->FilterManual(CNum, i);
					ASSERT(e >= 0);
#ifdef _UNRESTRICT_
#ifdef _UNRESTRICT2_
					m_List.SetItemText(iBlank + i, iCol + j, APTITUD_STR[e]);
#else
					m_List.SetItemText(iBlank + i, iCol + j, EMFC::Int2Str(e));
#endif //_UNRESTRICT2_
#endif //_UNRESTRICT_

					continue;
				}
				
				if(3 == j || 8 == j)	// 号码继承、等长步距
				{
					// 显示当期和下期号码
					m_List.SetItemText(iBlank + i - 1, iCol + j, CNum.ToString());
					m_List.SetItemText(iBlank + i, iCol + j, CNumNext.ToString());
				}
				else if( 4 == j) // 012 继承
				{
					// 显示当期和下期012路数
					m_List.SetItemText(iBlank + i - 1, iCol + j, CNum.AC3Str());
					m_List.SetItemText(iBlank + i, iCol + j, CNumNext.AC3Str());
						
				}
				else if( 5 == j) // 形态反转
				{
					// 显示当期和下期形态
					str = CNum.OddStr() + _T("-")
						+ CNum.LargeStr() + _T("-")
						+ CNum.PrimeStr();
					m_List.SetItemText(iBlank + i - 1, iCol + j, str);
					
					str = CNumNext.OddStr() + _T("-")
						+ CNumNext.LargeStr() + _T("-")
						+ CNumNext.PrimeStr();
					m_List.SetItemText(iBlank + i, iCol + j, str);
				}
				else if( 6 == j) // 常规均值
				{
					// 显示当期和下期均值
					m_List.SetItemText(iBlank + i - 1, iCol + j, EMFC::Int2Str(CNum.Ave()));
					m_List.SetItemText(iBlank + i, iCol + j, EMFC::Int2Str(CNumNext.Ave()));
				}
			}
		}
	}
	// 准确率统计
	for(int i = 0; i < loop; ++i)
	{
		str.Format(_T("%d:%d"), iCntOk[i], iCntErr[i]);
		m_List.SetItemText(0, iCol + i, str);
		
		if(0 != iCntOk[i] + iCntErr[i])
		{
			str.Format(_T("%.1f%%"), iCntOk[i] * 100.0 / (iCntOk[i] + iCntErr[i]));
			m_List.SetItemText(1, iCol + i, str);
		}
	}
	iCol += loop;	
	
	// 当前选择
	ZeroMemory(iCntOk, 3 * sizeof(UINT));
	ZeroMemory(iCntErr, 3 * sizeof(UINT));

	loop = 1;
	loopCnt = iLines <= iCountHistory ? iLines : iCountHistory - 1;
	for(int i = 1; i < loopCnt; ++i)
	{
		CNum = pHistory->GetCNum(i - 1);
		CNumNext = pHistory->GetCNum(i);

		// 按住 CTRL 只统计下期出组六
		// 按住 SHIFT 只统计期出组三
		if( !bCtrl && !bShift
			|| bCtrl && CNum.IsG6()
			|| bShift && CNum.IsG3())
		{
			n = pHistory->FilterAutoBase(CNum, pApp->bAutoBaseSel, i, pApp->iErr1, pApp->iErr2);

			if(  0 != n )
			{
				++iCntErr[0];
				m_List.SetItemColor(iBlank + i, iCol, crText, crRed);

				if( n > 0)
					m_List.SetItemText(iBlank + i, iCol, AUTO_BASE_STR[n - 1] );
				else
					m_List.SetItemText(iBlank + i, iCol, _T("容错下限") );
			}
			else
				++iCntOk[0];
		}
	}
	// 准确率统计
	for(int i = 0; i < loop; ++i)
	{
		str.Format(_T("%d:%d"), iCntOk[i], iCntErr[i]);
		m_List.SetItemText(0, iCol + i, str);
		
		if(0 != iCntOk[i] + iCntErr[i])
		{
#ifdef _UNRESTRICT2_
			if( bAlt )
				str.Format(_T("%.1f%%"), iCntOk[i] * 100.0 / (loopCnt- 1));
			else
				str.Format(_T("%.1f%%"), iCntOk[i] * 100.0 / (iCntOk[i] + iCntErr[i]));
#else
			str.Format(_T("%.1f%%"), iCntOk[i] * 100.0 / (iCntOk[i] + iCntErr[i]));
#endif // _UNRESTRICT2_
			
			m_List.SetItemText(1, iCol + i, str);
		}
	}
	iCol += loop;
	
	// 第一行未统计
	for(int i = 2; i < m_List.GetColumns(); ++i)
	{
		m_List.SetItemColor(iBlank, i, crText, crBack);
	}
}
