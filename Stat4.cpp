// OtherStat.cpp : implementation file
//

#include "stdafx.h"
#include "Stat4.h"

#include "..\Share\WND.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStat4 dialog


CStat4::CStat4(CWnd* pParent /*=NULL*/)
	: CDialog(CStat4::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStat4)
	m_strTip = _T("");
	//}}AFX_DATA_INIT
	
	pApp = (CMy3DApp *)AfxGetApp();
	pHistory = pApp->GetHistory();
}

BOOL CStat4::OnInitDialog() 
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
#ifdef _UNRESTRICT_
	m_List.SetHeadings(_T("期号,36;开奖,36;倒推胆,48;*π胆,48;1法胆,48;2法胆,48;3法胆,48;4法胆,48;\
		5码胆,48;P3号,36;3D号,36;杀码1,48;杀码2,48;杀码3,48;\
		杀两码1,54;杀两码2,54;杀两码3,54;杀两码4,54;杀两码5,54;杀两码6,54;杀两码7,54;杀两码8,54;"), LVCFMT_CENTER );
#else
	m_List.SetHeadings(_T("期号,36;开奖,36;倒推胆,48;*π胆,48;1法胆,48;2法胆,48;3法胆,48;4法胆,48;\
		5码胆,48;杀码1,48;杀码2,48;杀码3,48;\
		杀两码1,54;杀两码2,54;杀两码3,54;杀两码4,54;杀两码5,54;杀两码6,54;杀两码7,54;杀两码8,54;"), LVCFMT_CENTER );
#endif
	m_List.SetBkColor(RGB(128,128,128));
	m_List.LoadColumnInfo();

	m_strTip = CString(_T("①胆码\r\n\r\n"))
		+ _T("　　白色=未出号\r\n")
		+ _T("　　绿色=出号 1 个\r\n")
		+ _T("　　黄色=出号 2 个\r\n")
		+ _T("　　红色=出号 3 个\r\n\r\n")
		+ _T("②杀码\r\n\r\n")
		+ _T("　　红色=杀码错误\r\n")
		+ _T("　　绿色=杀码正确\r\n\r\n")
		+ _T("③杀两码\r\n\r\n")
		+ _T("　　红色=错误\r\n")
		+ _T("　　绿色=正确\r\n\r\n")
		+ _T("提示：\r\n\r\n")
		+ _T("　　胆码命中个数按相同号只计1个来统计\r\n")
		+ _T("　　按住 ALT 键点上面的期号选择，按重号多计统计。\r\n\r\n")
		+ _T("　　杀两码的准确率是按有序杀两码来统计后标记颜色的。\r\n")
		+ _T("　　按住 ALT 键点上面的期号选择，杀两码按无序统计。")
		;

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CStat4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStat4)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_OTHER_STAT_TIP, m_strTip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStat4, CDialog)
	//{{AFX_MSG_MAP(CStat4)
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY(NM_RCLICK, IDC_LIST, OnRclickList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStat4 message handlers

BOOL CStat4::PreTranslateMessage(MSG* pMsg) 
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

void CStat4::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	GetParent()->GetParent()->SendMessage(WM_CLOSE);
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CStat4::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	GetParent()->GetParent()->SendMessage(WM_CLOSE);
	
	*pResult = 0;
}

void CStat4::RefreshList(int iPeriod/* = 50*/)
{
	m_List.DeleteAllItems();
	
	int iCountHistory = pHistory->GetCount();
	if(iCountHistory < 7)
		return;
	
	CString str = _T(" ");

	m_List.AddItem(str, _T("正:误"),
		str, str, str, str, str, str, str, str, str,
		str, str, str, str,
		str, str, str, str, str, str, str, str);
	m_List.AddItem(str, _T("准确率"),
		str, str, str, str, str, str, str, str, str,
		str, str, str,
		str, str, str, str, str, str, str, str, str);
	
	C3D CNum, CNumNext;
	int loopCnt, loop2, iBlank = 2;		// 空二行
	
	// 历史
	loopCnt = iPeriod + 1 <= iCountHistory ? iPeriod + 1 : iCountHistory;
	for(int i = 0; i < loopCnt; ++i)
	{
		CNum = pHistory->GetCNum(i);

		str.Empty();
		m_List.AddItem(pHistory->GetPeriodStr(i).Right(5), CNum.ToString(),
			str, str, str, str, str, str, str, str, str,
			str, str, str, str,
			str, str, str, str, str, str, str, str);
		
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
	BOOL bCtrl  = WND::IsCtrlDown();
	BOOL bShift = WND::IsShiftDown();
	BOOL bAlt   = WND::IsAltDown();
	
	int iLines = m_List.GetItemCount() - iBlank;
	int iCntOK[8], iCntErr[8], iCol = 2, n;

	// 胆码(7组)
	ZeroMemory(iCntOK, 8 * sizeof(UINT));
	ZeroMemory(iCntErr, 8 * sizeof(UINT));
	CStringArray arrCour;
	int iBack = 136;

#ifdef _UNRESTRICT_
	if( WND::IsCharDown(_T('1')) )		iBack = 131;
	else if( WND::IsCharDown(_T('2')) )	iBack = 132;
	else if( WND::IsCharDown(_T('3')) )	iBack = 133;
	else if( WND::IsCharDown(_T('4')) )	iBack = 134;
	else if( WND::IsCharDown(_T('5')) )	iBack = 135;
	else if( WND::IsCharDown(_T('6')) )	iBack = 137;
	else if( WND::IsCharDown(_T('7')) )	iBack = 138;
	else if( WND::IsCharDown(_T('8')) )	iBack = 139;
	else if( WND::IsCharDown(_T('9')) )	iBack = 140;
	else if( WND::IsCharDown(_T('0')) )	iBack = 141;
#endif

	loop2 = 7;
	loopCnt = iLines;
	for(int i = 0; i < loopCnt; ++i)
	{
		n = pHistory->RecommandCourage(arrCour, i, iBack);
		n = n > loop2 ? loop2 : n;

		int cnt;
		for(int j = 0; j < n; ++j)
		{
			str = arrCour[j];

			if(i > 0)
			{
				CNum = pHistory->GetCNum(i - 1);

				// 按住 CTRL 只统计下期出组六
				// 按住 SHIFT 只统计期出组三
				if( !bCtrl && !bShift
					|| bCtrl && CNum.IsG6()
					|| bShift && CNum.IsG3())
				{
					m_List.SetItemText(i + iBlank, iCol + j, str);
					
					if( !str.IsEmpty() )
					{
						cnt = CNum.CountInStr(str, !bAlt);
						if( cnt > 0 )
						{
							++iCntOK[j];
							
							if(1 == cnt)		m_List.SetItemColor(i + iBlank, iCol + j, crText, crGreen);
							else if( 2 == cnt )	m_List.SetItemColor(i + iBlank, iCol + j, crText, crYellow);
							else				m_List.SetItemColor(i + iBlank, iCol + j, crText, crRed);
						}
						else
							++iCntErr[j];
					}
				}
			}
			else
				m_List.SetItemText(i + iBlank, iCol + j, str);
		}
	}
	// 准确率统计
	for(int i = 0; i < loop2; ++i)
	{
		str.Format(_T("%d:%d"), iCntOK[i], iCntErr[i]);
		m_List.SetItemText(0, iCol + i, str);
		
		if(0 != iCntOK[i] + iCntErr[i])
		{
			str.Format(_T("%.1f%%"), iCntOK[i] * 100.0 / (iCntOK[i] + iCntErr[i]));
			m_List.SetItemText(1, iCol + i, str);
		}
	}
	iCol += loop2;

#ifdef _UNRESTRICT_
	CUIntArray aHis;
	CString strFile;

	// P3 当期号
	if( pHistory->Is3D() )
	{
		//strFile = pApp->GetPath() + CString(_T("\\P5.dat"));
		strFile = WND::GetAbsPath(TRUE) + _T("P5.dat");
		CHistory::LoadFile3DToArray(strFile, FALSE, aHis);
	}

	ZeroMemory(iCntOK, 3 * sizeof(UINT));
	ZeroMemory(iCntErr, 3 * sizeof(UINT));

	loopCnt = iLines;
	for(int i = 0; i < loopCnt; ++i)
	{
		if(pHistory->Is3D())
			CNum = C3D(aHis[i]);
		else
			CNum = pHistory->GetCNum(i);
		
		str = CNum.ToString();

		if(i > 0)
		{
			CNumNext = pHistory->GetCNum(i - 1);
			n = CNumNext.CountInStr(str, !bAlt);
			
			// 按住 CTRL 只统计下期出组六
			// 按住 SHIFT 只统计期出组三
			if( !bCtrl && !bShift
				|| bCtrl && CNumNext.IsG6()
				|| bShift && CNumNext.IsG3())
			{
				m_List.SetItemText(i + iBlank, iCol, str);
				
				if( n > 0 )
				{
					++iCntOK[0];
					
					if(1 == n)			m_List.SetItemColor(i + iBlank, iCol, crText, crGreen);
					else if( 2 == n )	m_List.SetItemColor(i + iBlank, iCol, crText, crYellow);
					else				m_List.SetItemColor(i + iBlank, iCol, crText, crRed);
				}
				else
					++iCntErr[0];
			}
		}
		else
			m_List.SetItemText(i + iBlank, iCol, str);
	}
	// 准确率统计
	{
		int i = 0;
		str.Format(_T("%d:%d"), iCntOK[i], iCntErr[i]);
		m_List.SetItemText(0, iCol + i, str);
		
		if(0 != iCntOK[i] + iCntErr[i])
		{
			str.Format(_T("%.1f%%"), iCntOK[i] * 100.0 / (iCntOK[i] + iCntErr[i]));
			m_List.SetItemText(1, iCol + i, str);
		}
	}
	++iCol;

	// 3D 当期号
	if( !pHistory->Is3D() )
	{
		strFile = WND::GetAbsPath() + CString(_T("\\3D.dat"));
		CHistory::LoadFile3DToArray(strFile, TRUE, aHis);
	}

	ZeroMemory(iCntOK, 3 * sizeof(UINT));
	ZeroMemory(iCntErr, 3 * sizeof(UINT));

	loopCnt = iLines;
	for(int i = 0; i < loopCnt; ++i)
	{
		if( !pHistory->Is3D() )
			CNum = C3D(aHis[i]);
		else
			CNum = pHistory->GetCNum(i);

		str = CNum.ToString();
		
		if(i > 0)
		{
			CNumNext = pHistory->GetCNum(i - 1);
			n = CNumNext.CountInStr(str, !bAlt);
			
			// 按住 CTRL 只统计下期出组六
			// 按住 SHIFT 只统计期出组三
			if( !bCtrl && !bShift
				|| bCtrl && CNumNext.IsG6()
				|| bShift && CNumNext.IsG3())
			{
				m_List.SetItemText(i + iBlank, iCol, str);
				
				if( n > 0 )
				{
					++iCntOK[0];
					
					if(1 == n)			m_List.SetItemColor(i + iBlank, iCol, crText, crGreen);
					else if( 2 == n )	m_List.SetItemColor(i + iBlank, iCol, crText, crYellow);
					else				m_List.SetItemColor(i + iBlank, iCol, crText, crRed);
				}
				else
					++iCntErr[0];
			}
		}
		else
			m_List.SetItemText(i + iBlank, iCol, str);
	}
	// 准确率统计
	{
		int i = 0;
		str.Format(_T("%d:%d"), iCntOK[i], iCntErr[i]);
		m_List.SetItemText(0, iCol + i, str);
		
		if(0 != iCntOK[i] + iCntErr[i])
		{
			str.Format(_T("%.1f%%"), iCntOK[i] * 100.0 / (iCntOK[i] + iCntErr[i]));
			m_List.SetItemText(1, iCol + i, str);
		}
	}
	++iCol;
#endif // _UNRESTRICT_

	CUIntArray arrKillNum;
	
	// 杀码3个
	ZeroMemory(iCntOK, 3 * sizeof(UINT));
	ZeroMemory(iCntErr, 3 * sizeof(UINT));
	int dd[] = { 0, 8, 6, 4, 7, 9, 1, 2, 4, 6 };

	loop2 = 3;
	loopCnt = iLines;
	for(int i = 0; i < loopCnt; ++i)
	{
		n = pHistory->Kill1Nums(arrKillNum, i);
		n = n > loop2 ? loop2 : n;
		
		if( i > 0)
			CNum = pHistory->GetCNum(i - 1);
		
		for(int j = 0; j < n; ++j)
		{
			if(arrKillNum[j] != -1)
				str = EMFC::Int2Str(arrKillNum[j]);
			else
				str.Empty();

			m_List.SetItemText(i + iBlank, iCol + j, str);
		
			if(i > 0 && arrKillNum[j] != -1)
			{
				// 按住 CTRL 只统计下期出组六
				// 按住 SHIFT 只统计期出组三
				if( !bCtrl && !bShift
					|| bCtrl && CNum.IsG6()
					|| bShift && CNum.IsG3())
				{
					if( !CNum.IsMember(arrKillNum[j]) )
					{
						m_List.SetItemColor(i + iBlank, iCol + j, crText, crGreen);
						++iCntOK[j];
					}
					else
					{
						m_List.SetItemColor(i + iBlank, iCol + j, crText, crRed);
						//m_List.SetItemText(i + iBlank, iCol + j, CNum.ToString());
						++iCntErr[j];
					}
				}
			}
		}
	}
	// 准确率统计
	for(int i = 0; i < loop2; ++i)
	{
		str.Format(_T("%d:%d"), iCntOK[i], iCntErr[i]);
		m_List.SetItemText(0, iCol + i, str);
		
		if(0 != iCntOK[i] + iCntErr[i])
		{
			str.Format(_T("%.1f%%"), iCntOK[i] * 100.0 / (iCntOK[i] + iCntErr[i]));
			m_List.SetItemText(1, iCol + i, str);
		}
	}
	iCol += loop2;
	
	// 杀两码8个
	ZeroMemory(iCntOK, 8 * sizeof(UINT));
	ZeroMemory(iCntErr, 8 * sizeof(UINT));

	loop2 = 8;
	loopCnt = iLines + 1 <= iCountHistory ? iLines : iCountHistory - 1;
	for(int i = 0; i < loopCnt; ++i)
	{
		n = pHistory->Kill2Nums(arrKillNum, i);
		n = n > loop2 ? loop2 : n;

		if( i > 0)
			CNum = pHistory->GetCNum(i - 1);
		
		for(int j = 0; j < n; ++j)
		{
			str = EMFC::Int2Str(arrKillNum[j], _T("%02d"));
			
			if(i > 0)
			{
				// 按住 CTRL 只统计下期出组六
				// 按住 SHIFT 只统计期出组三
				if( !bCtrl && !bShift
					|| bCtrl && CNum.IsG6()
					|| bShift && CNum.IsG3() )
				{
					m_List.SetItemText(i + iBlank, iCol + j, str);
					
					// 按住 ALT 键杀两码按无序统计
					if( !CNum.IsMember2(arrKillNum[j], !bAlt) )
					{
						m_List.SetItemColor(i + iBlank, iCol + j, crText, crGreen);
						++iCntOK[j];
					}
					else
					{
						m_List.SetItemColor(i + iBlank, iCol + j, crText, crRed);
						++iCntErr[j];
					}
				}
			}
			else
				m_List.SetItemText(i + iBlank, iCol + j, str);
		}
	}
	// 准确率统计
	for(int i = 0; i < loop2; ++i)
	{
		str.Format(_T("%d:%d"), iCntOK[i], iCntErr[i]);
		m_List.SetItemText(0, iCol + i, str);
		
		if(0 != iCntOK[i] + iCntErr[i])
		{
			str.Format(_T("%.1f%%"), iCntOK[i] * 100.0 / (iCntOK[i] + iCntErr[i]));
			m_List.SetItemText(1, iCol + i, str);
		}
	}
	iCol += loop2;
	
	// 第一行未统计
	for(int i = 2; i < m_List.GetColumns(); ++i)
	{
		m_List.SetItemColor(iBlank, i, crText, crBack);
	}
}
