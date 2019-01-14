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
	m_List.SetHeadings(_T("�ں�,36;����,45;��λ�Ƽ�,80;ʮλ�Ƽ�,80;��λ�Ƽ�,80;\
		ɱ��λ,48;ɱʮλ,48;ɱ��λ,48;�������,60;�������,60;�������,60;"), LVCFMT_CENTER );
	m_List.SetBkColor(RGB(128,128,128));
	m_List.LoadColumnInfo();
	
	m_strTip = CString(_T("�ٰ�ʮ��λ�Ƽ���\r\n\r\n"))
		+_T("���������Ƽ������������ѡ�����������������Ŀ������ݣ���һ�����㷨�� 0-9 ����������")
		+_T("ѡ�������������ͬ�Ƽ���Ľ��Ҳ��ͬ��")
		+_T("����ѡ����Ƽ���������������ǰn������ƥ�����ڵĿ����������������ɫ��ǡ�\r\n")
		+_T("������ɫ=��Ӧλ����\r\n")
		+_T("������ɫ=��Ӧλ��ȷ\r\n")
		+_T("������ɫ=��ʮ��λ����ȷ\r\n\r\n")
		+_T("����������ѡ������е��Ƽ���ť����ʹ������� 9 ���Ƽ������\r\n")
		+_T("����6 ������׼ȷ�ʺܵͣ�������Ϊ������ʽ��ɱ��9���Ƽ�+6��������ɱ��һ��š�\r\n\r\n")
		+_T("�ڰ�ʮ��λɱ��\r\n\r\n")
		+_T("������ɫ=ɱ�����\r\n")
		+_T("������ɫ=ɱ����ȷ\r\n\r\n")
		+_T("�۶�����͡����\r\n\r\n")
		+_T("������ɫ=����\r\n")
		+_T("������ɫ=��1��\r\n")
		+_T("������ɫ=��2��\r\n")
		+_T("������ɫ=��3��\r\n\r\n")
		+_T("��������硢�͡���ͳ�ƴ���Ĭ����ֵ�ƶ�Σ���ס ALT ˢ��(��������ں�)����ֵ��1��ͳ�ơ�\r\n\r\n")
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
	int nBlank = 2;	// �ն���
	int loopCnt;		// ѭ������
	int nCntOK[3], nCntErr[3];	// ����ͳ��

	m_List.AddItem(str, _T("��:��"), str, str, str, str, str, str, str, str, str/*, str, str, str, str, str, str*/);
	m_List.AddItem(str, _T("׼ȷ��"), str, str, str, str, str, str, str, str, str/*, str, str, str, str, str, str*/);

	// ��ʷ
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
	
	// �Ƽ�
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
	// ׼ȷ��ͳ��
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
	
	// ��λɱ
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
	// ׼ȷ��ͳ��
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
	
	// �����͡���
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
	// ׼ȷ��ͳ��
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

	// ��һ��δͳ��
	for(int i = 2; i < m_List.GetColumns(); ++i)
	{
		m_List.SetItemColor(nBlank, i, crText, crBack);
	}
}
