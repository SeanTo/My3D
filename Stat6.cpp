// Stat6.cpp : implementation file
//

#include "stdafx.h"
#include "Stat6.h"

#include "..\Share\WND.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStat6 dialog


CStat6::CStat6(CWnd* pParent /*=NULL*/)
	: CDialog(CStat6::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStat6)
	// NOTE: the ClassWizard will add member initialization here
	m_strTip = _T("");
	//}}AFX_DATA_INIT
	
	pApp = (CMy3DApp *)AfxGetApp();
	pHistory = pApp->GetHistory();
}


void CStat6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStat6)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_OTHER_STAT_TIP, m_strTip);
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStat6, CDialog)
	//{{AFX_MSG_MAP(CStat5)
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY(NM_RCLICK, IDC_LIST, OnRclickList)
	//}}AFX_MSG_MAP
//	ON_CONTROL_RANGE(BN_CLICKED, IDC_RAD_6WP1, IDC_RAD_6WP4, OnSelectPeriod)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStat6 message handlers

BOOL CStat6::OnInitDialog() 
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
	m_List.SetHeadings(_T("�ں�,36;����,36;������,55;������,55;������,55;������,55;������,55;������,55;\
		����,80;����,48;����,48;����,48;����,48;����,48;\
		б��,80;б��,48;б��,48;б��,48;б��,48;б��,48;"), LVCFMT_CENTER );
	m_List.SetBkColor(RGB(128,128,128));
	m_List.LoadColumnInfo();
	
	m_strTip = CString(_T("\r\n������ɫ: ���� 0 ��"))
		+ _T("\r\n������ɫ: ���� 1 ��")
		+ _T("\r\n������ɫ: ���� 2 ��")
		+ _T("\r\n������ɫ: ���� 3 ��")
		+ _T("\r\n����(�غżƶ��)")
		+ _T("\r\n\r\n����Ĭ�ϰ����� 1-3 ͳ�Ƶ�����ȷ�ʣ�")
		+ _T("��ס ALT ����ˢ��(���������һ���ں�ѡ��)�򰴳��� 1-2 ͳ�ơ�")
		;
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CStat6::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	// Do not call CDialog::OnPaint() for painting messages
}

void CStat6::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	GetParent()->GetParent()->SendMessage(WM_CLOSE);
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CStat6::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	GetParent()->GetParent()->SendMessage(WM_CLOSE);
	
	*pResult = 0;
}

BOOL CStat6::PreTranslateMessage(MSG* pMsg) 
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

void CStat6::RefreshList(int iPeriod/* = 50*/)
{
	int iCountHistory = pHistory->GetCount();
	if(iCountHistory < 7)
		return;
	
	m_List.DeleteAllItems();
	
	CString str = _T("");

	m_List.AddItem(str, _T("��:��"),
		str, str, str,  str, str, str,  str, str, str,
		str, str, str, str, str, str, str, str, str );
	m_List.AddItem(str, _T("׼ȷ��"),
		str, str, str, str, str, str, str, str, str,
		str, str, str, str, str, str, str, str, str );
	
	C3D CNum, CNumNext;
	int iBlank = 2;		// �ն���
	int loopCnt;
	
	// ��ʷ
	loopCnt = iPeriod + 1 <= iCountHistory ? iPeriod + 1 : iCountHistory;
	for(int i = 0; i < loopCnt; ++i)
	{
		CNum = pHistory->GetCNum(i);

		str.Empty();
		m_List.AddItem(pHistory->GetPeriodStr(i).Right(5), CNum.ToString(),
			str, str, str, str, str, str, str, str, str,
			str, str, str, str, str, str, str, str, str );
		
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
	BOOL bShift = WND::IsShiftDown();
	BOOL bAlt = WND::IsAltDown();

	UINT nCntOK[20], nCntErr[20];
	int iLines = m_List.GetItemCount() - iBlank;
	int iCol = 2, num;
	
	CStringArray arrUp, arrDn;

	ZeroMemory(nCntOK, 20 * sizeof(UINT));
	ZeroMemory(nCntErr, 20 * sizeof(UINT));

	loopCnt = iLines <= iCountHistory ? iLines : iCountHistory - 1;
	for(int i = 0; i < loopCnt; ++i)
	{
		pHistory->TriangleCourage(arrUp, i, TRUE);
		pHistory->TriangleCourage(arrDn, i, FALSE);
		
		if( 0 == i)
		{
			for(int k = 0; k < 3; ++k)
			{
				for(int j = 0; j < 3; ++j)
				{
					m_List.SetItemText(iBlank + i, iCol + k * 6 + j, arrUp[k * 3 + j + iCol - 2]);
					m_List.SetItemText(iBlank + i, iCol + k * 6 + j + 3, arrDn[k * 3 + j + iCol - 2]);
				}
			}
		}
		else
		{
			CNum = pHistory->GetCNum(i - 1);
			
			// ��ס CTRL ֻͳ�����ڳ�����
			// ��ס SHIFT ֻͳ���ڳ�����
			if( !bCtrl && !bShift
				|| bCtrl && CNum.IsG6()
				|| bShift && CNum.IsG3())
			{
				for(int k = 0; k < 3; ++k)
				{
					for(int j = 0; j < 3; ++j)
					{
						// ����
						m_List.SetItemText(iBlank + i, iCol + k * 6 + j, arrUp[k * 3 + j + iCol - 2]);

						// ��֤���ڿ�����
						num = CNum.CountInStr( arrUp[k * 3 + j + iCol - 2], TRUE);
						
						// ��ס ALT ͳ�Ʒ�ΧΪ���� 1-2
						if( num > 0  && (!bAlt || num < 3) )
						{
							if( 1 == num )
								m_List.SetItemColor(iBlank + i, iCol + k * 6 + j, crText, crGreen);
							else if( 2 == num )
								m_List.SetItemColor(iBlank + i, iCol + k * 6 + j, crText, crYellow);
							else
								m_List.SetItemColor(iBlank + i, iCol + k * 6 + j, crText, crRed);
							
							++nCntOK[k * 6 + j];
						}
						else
							++nCntErr[k * 6 + j];

						// ����
						m_List.SetItemText(iBlank + i, iCol + k * 6 + j + 3, arrDn[k * 3 + j + iCol - 2]);

						// ��֤���ڿ�����
						num = CNum.CountInStr( arrDn[k * 3 + j + iCol - 2], TRUE );
						
						// ��ס ALT ͳ�Ʒ�ΧΪ���� 1-2
						if( num > 0  && (!bAlt || num < 3) )
						{
							if( 1 == num )
								m_List.SetItemColor(iBlank + i, iCol + k * 6 + j + 3, crText, crGreen);
							else if( 2 == num )
								m_List.SetItemColor(iBlank + i, iCol + k * 6 + j + 3, crText, crYellow);
							else
								m_List.SetItemColor(iBlank + i, iCol + k * 6 + j + 3, crText, crRed);
							
							++nCntOK[k * 6 + j + 3];
						}
						else
							++nCntErr[k * 6 + j + 3];
						
					}
				}
			}
		}
	}
	// ׼ȷ��ͳ��
	for(int i = 0; i < 20; ++i)
	{
		str.Format(_T("%d:%d"), nCntOK[i], nCntErr[i]);
		m_List.SetItemText(0, iCol + i, str);
		
		if(0 != nCntOK[i] + nCntErr[i])
		{
			str.Format(_T("%.1f%%"), nCntOK[i] * 100.0 / (nCntOK[i] + nCntErr[i]));
			m_List.SetItemText(1, iCol + i, str);
		}
	}
	iCol += 10;
		
	// ��һ��δͳ��
	for(int i = 2; i < m_List.GetColumns(); ++i)
	{
		m_List.SetItemColor(iBlank, i, crText, crBack);
	}
}
