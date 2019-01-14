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
	m_List.SetHeadings(_T("�ں�,36;����,36;��̬����,60;��ʽ-ǿ,60;��ʽ-��,60;\
		����̳�,60;012�̳�,60;��̬��ת,120;��ֵ2-7,60;������,60;������,60;�������,60;\
		��ǰѡ��,60;"), LVCFMT_CENTER );
	m_List.SetBkColor(RGB(128,128,128));
	m_List.LoadColumnInfo();

	m_strTip = CString(_T("\r\n������ɫ: ��ʾ�����ø÷������ɴ�ף������ڿ�������֤���������"))
		+ _T("\r\n�����ڶ��е�׼ȷ�ʰ���ɫ��������㡣")
		+ _T("\r\n\r\n������ɫ: ��һ������ʾ��δ�����Զ���׹������ɡ�")
		+ _T("\r\n��������̳�: 1���ż̳�")
		+ _T("\r\n����012 �̳�: 1��2��·���̳�")
		+ _T("\r\n������̬��ת: 1����̬��ת")
		+ _T("\r\n\r\n\r\n��ǰѡ��")
		+ _T("\r\n\r\n������һ���Ƕ�̬�ģ����������鿴����㷨��δ�г�ͳ�Ƶĵ����㷨��ͳ�ƽ����")
		+ _T("\r\n\r\n�����ٴ��Զ����ѡ��")
		+ _T("\r\n�����ڹ�ѡ����ͳ�ƵĴ��")
		+ _T("\r\n�����۹رնԻ���")
		+ _T("\r\n�������ٴ����ݷ���")
		+ _T("\r\n�����ܵ�ǰѡ��Ϊͳ�ƽ��")
		+ _T("\r\n\r\n�������ø��п��Բ���һ�㷨�����������㷨��ϵ�׼ȷ��ͳ�ƽ����")
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

	m_List.AddItem(str, _T("��:��"), str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str);
	m_List.AddItem(str, _T("׼ȷ��"), str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str, str);
	
	C3D CNum, CNum1, CNum2, CNumNext;
	int loopCnt, iBlank = 2;		// ����
	
	// ��ʷ
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

	// �������Ƽ�
	BOOL bCtrl = WND::IsCtrlDown();
	BOOL bShift = WND::IsShiftDown() && !bCtrl;
	BOOL bAlt = WND::IsAltDown();
	
	int iLines = m_List.GetItemCount() - iBlank;
	int iCntOk[12], iCntErr[12], n;
	int iCol = 2, loop;

	bitset<32> bSel;

	// �Զ����
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

				// ������ʾ����ɫ���
				if( 3 == j)
				{
					if( CNum.CountSame(CNumNext) > 0 ) // ����̳�
					{
						m_List.SetItemText(iBlank + i - 1, iCol + j, CNum.ToString());
						m_List.SetItemText(iBlank + i, iCol + j, CNumNext.ToString());
						
						m_List.SetItemColor(iBlank + i, iCol + j, crText, crGray);
					}
				}
				else if( 4 == j ) // 012 �̳�
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
				else if( 5 == j ) // ��̬��ת
				{
					// ��ż
					n = 0;
					CNum1 = CNumNext.OddModNum();
					CNum2 = CNum.OddModNum();
					n += (0 == CNum1.CountSame(CNum2));
					// ��С
					CNum1 = CNumNext.LargeModNum();
					CNum2 = CNum.LargeModNum();
					n += (0 == CNum1.CountSame(CNum2));
					// �ʺ�
					CNum1 = CNumNext.PrimeModNum();
					CNum2 = CNum.PrimeModNum();
					n += (0 == CNum1.CountSame(CNum2));
					
					if( n > 0 )
					{
						// ��ʾ���ں����ڵ���̬
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

				if(0 == j) // ��̬����
				{
					// ��ʾ��������㷨��
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
				
				if(3 == j || 8 == j)	// ����̳С��ȳ�����
				{
					// ��ʾ���ں����ں���
					m_List.SetItemText(iBlank + i - 1, iCol + j, CNum.ToString());
					m_List.SetItemText(iBlank + i, iCol + j, CNumNext.ToString());
				}
				else if( 4 == j) // 012 �̳�
				{
					// ��ʾ���ں�����012·��
					m_List.SetItemText(iBlank + i - 1, iCol + j, CNum.AC3Str());
					m_List.SetItemText(iBlank + i, iCol + j, CNumNext.AC3Str());
						
				}
				else if( 5 == j) // ��̬��ת
				{
					// ��ʾ���ں�������̬
					str = CNum.OddStr() + _T("-")
						+ CNum.LargeStr() + _T("-")
						+ CNum.PrimeStr();
					m_List.SetItemText(iBlank + i - 1, iCol + j, str);
					
					str = CNumNext.OddStr() + _T("-")
						+ CNumNext.LargeStr() + _T("-")
						+ CNumNext.PrimeStr();
					m_List.SetItemText(iBlank + i, iCol + j, str);
				}
				else if( 6 == j) // �����ֵ
				{
					// ��ʾ���ں����ھ�ֵ
					m_List.SetItemText(iBlank + i - 1, iCol + j, EMFC::Int2Str(CNum.Ave()));
					m_List.SetItemText(iBlank + i, iCol + j, EMFC::Int2Str(CNumNext.Ave()));
				}
			}
		}
	}
	// ׼ȷ��ͳ��
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
	
	// ��ǰѡ��
	ZeroMemory(iCntOk, 3 * sizeof(UINT));
	ZeroMemory(iCntErr, 3 * sizeof(UINT));

	loop = 1;
	loopCnt = iLines <= iCountHistory ? iLines : iCountHistory - 1;
	for(int i = 1; i < loopCnt; ++i)
	{
		CNum = pHistory->GetCNum(i - 1);
		CNumNext = pHistory->GetCNum(i);

		// ��ס CTRL ֻͳ�����ڳ�����
		// ��ס SHIFT ֻͳ���ڳ�����
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
					m_List.SetItemText(iBlank + i, iCol, _T("�ݴ�����") );
			}
			else
				++iCntOk[0];
		}
	}
	// ׼ȷ��ͳ��
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
	
	// ��һ��δͳ��
	for(int i = 2; i < m_List.GetColumns(); ++i)
	{
		m_List.SetItemColor(iBlank, i, crText, crBack);
	}
}
