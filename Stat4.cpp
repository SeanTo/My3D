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
	m_List.SetHeadings(_T("�ں�,36;����,36;���Ƶ�,48;*�е�,48;1����,48;2����,48;3����,48;4����,48;\
		5�뵨,48;P3��,36;3D��,36;ɱ��1,48;ɱ��2,48;ɱ��3,48;\
		ɱ����1,54;ɱ����2,54;ɱ����3,54;ɱ����4,54;ɱ����5,54;ɱ����6,54;ɱ����7,54;ɱ����8,54;"), LVCFMT_CENTER );
#else
	m_List.SetHeadings(_T("�ں�,36;����,36;���Ƶ�,48;*�е�,48;1����,48;2����,48;3����,48;4����,48;\
		5�뵨,48;ɱ��1,48;ɱ��2,48;ɱ��3,48;\
		ɱ����1,54;ɱ����2,54;ɱ����3,54;ɱ����4,54;ɱ����5,54;ɱ����6,54;ɱ����7,54;ɱ����8,54;"), LVCFMT_CENTER );
#endif
	m_List.SetBkColor(RGB(128,128,128));
	m_List.LoadColumnInfo();

	m_strTip = CString(_T("�ٵ���\r\n\r\n"))
		+ _T("������ɫ=δ����\r\n")
		+ _T("������ɫ=���� 1 ��\r\n")
		+ _T("������ɫ=���� 2 ��\r\n")
		+ _T("������ɫ=���� 3 ��\r\n\r\n")
		+ _T("��ɱ��\r\n\r\n")
		+ _T("������ɫ=ɱ�����\r\n")
		+ _T("������ɫ=ɱ����ȷ\r\n\r\n")
		+ _T("��ɱ����\r\n\r\n")
		+ _T("������ɫ=����\r\n")
		+ _T("������ɫ=��ȷ\r\n\r\n")
		+ _T("��ʾ��\r\n\r\n")
		+ _T("�����������и�������ͬ��ֻ��1����ͳ��\r\n")
		+ _T("������ס ALT ����������ں�ѡ�񣬰��غŶ��ͳ�ơ�\r\n\r\n")
		+ _T("����ɱ�����׼ȷ���ǰ�����ɱ������ͳ�ƺ�����ɫ�ġ�\r\n")
		+ _T("������ס ALT ����������ں�ѡ��ɱ���밴����ͳ�ơ�")
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

	m_List.AddItem(str, _T("��:��"),
		str, str, str, str, str, str, str, str, str,
		str, str, str, str,
		str, str, str, str, str, str, str, str);
	m_List.AddItem(str, _T("׼ȷ��"),
		str, str, str, str, str, str, str, str, str,
		str, str, str,
		str, str, str, str, str, str, str, str, str);
	
	C3D CNum, CNumNext;
	int loopCnt, loop2, iBlank = 2;		// �ն���
	
	// ��ʷ
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

	// �������Ƽ�
	BOOL bCtrl  = WND::IsCtrlDown();
	BOOL bShift = WND::IsShiftDown();
	BOOL bAlt   = WND::IsAltDown();
	
	int iLines = m_List.GetItemCount() - iBlank;
	int iCntOK[8], iCntErr[8], iCol = 2, n;

	// ����(7��)
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

				// ��ס CTRL ֻͳ�����ڳ�����
				// ��ס SHIFT ֻͳ���ڳ�����
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
	// ׼ȷ��ͳ��
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

	// P3 ���ں�
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
			
			// ��ס CTRL ֻͳ�����ڳ�����
			// ��ס SHIFT ֻͳ���ڳ�����
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
	// ׼ȷ��ͳ��
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

	// 3D ���ں�
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
			
			// ��ס CTRL ֻͳ�����ڳ�����
			// ��ס SHIFT ֻͳ���ڳ�����
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
	// ׼ȷ��ͳ��
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
	
	// ɱ��3��
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
				// ��ס CTRL ֻͳ�����ڳ�����
				// ��ס SHIFT ֻͳ���ڳ�����
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
	// ׼ȷ��ͳ��
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
	
	// ɱ����8��
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
				// ��ס CTRL ֻͳ�����ڳ�����
				// ��ס SHIFT ֻͳ���ڳ�����
				if( !bCtrl && !bShift
					|| bCtrl && CNum.IsG6()
					|| bShift && CNum.IsG3() )
				{
					m_List.SetItemText(i + iBlank, iCol + j, str);
					
					// ��ס ALT ��ɱ���밴����ͳ��
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
	// ׼ȷ��ͳ��
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
	
	// ��һ��δͳ��
	for(int i = 2; i < m_List.GetColumns(); ++i)
	{
		m_List.SetItemColor(iBlank, i, crText, crBack);
	}
}
