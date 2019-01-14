// StatStat.cpp : implementation file
//

#include "stdafx.h"
#include "Stat2.h"

#include "..\Share\WND.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStat2 dialog


CStat2::CStat2(CWnd* pParent /*=NULL*/)
	: CDialog(CStat2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStat2)
	m_strTip = _T("");
	//}}AFX_DATA_INIT
	
	pApp = (CMy3DApp *)AfxGetApp();
	pHistory = pApp->GetHistory();
}


void CStat2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStat2)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_STAT_STAT_TIP, m_strTip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStat2, CDialog)
	//{{AFX_MSG_MAP(CStat2)
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY(NM_RCLICK, IDC_LIST, OnRclickList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStat2 message handlers

BOOL CStat2::PreTranslateMessage(MSG* pMsg) 
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

void CStat2::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	GetParent()->GetParent()->SendMessage(WM_CLOSE);
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CStat2::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	GetParent()->GetParent()->SendMessage(WM_CLOSE);
	
	*pResult = 0;
}

BOOL CStat2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rc;
	rc = pApp->rcScreen;
	MoveWindow(&rc);
//	rc.DeflateRect(0, 50, 200, 48);
	rc.DeflateRect(0, 0, 200, 100);
	GetDlgItem(IDC_LIST)->MoveWindow(&rc);
	
//	rc.SetRect(rc.Width(), rc.top, rc.Width() + 190, rc.bottom);
	rc.SetRect(rc.Width(), rc.top, rc.Width() + 190, rc.bottom);
	GetDlgItem(IDC_STAT_STAT_TIP)->MoveWindow(&rc);
	
	// TODO: Add extra initialization here
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.SetHeadings(_T("�ں�,36;����,36;��©��ֵ,60;����,36;����,36;��б,36;��б,36;\
		�����Ⱥ�,60;�����º�,60;�������,60;�º�,36;С��,36;�к�,36;���,36;0·,36;1·,36;2·,36;"), LVCFMT_CENTER );
	m_List.SetBkColor(RGB(128,128,128));
	m_List.LoadColumnInfo();

	m_strTip = CString(_T("��������\r\n\r\n"))
		+_T("����ͳ�����5�ڿ�����15�����֣�����2�εĺ�Ϊ�ºţ�2������Ϊ��ţ�2������Ϊ�Ⱥš�\r\n")
		+_T("������ɫ = ���� 1 ��\r\n")
		+_T("������ɫ = ���� 2 ��\r\n")
		+_T("������ɫ = ���� 3 ��\r\n\r\n")
		+_T("������ͳ�Ʊ�����1��1��1��������̬���ٳ��֣����Խ����������3�ζ�·������ɱ����\r\n\r\n")
		+_T("������һ���÷��ǽ��Ⱥź��º���ӣ��������ֽ�ʽ���ú��뷶Χ����=��š�1-2(��1-3)��\r\n\r\n")
		+_T("���º�\r\n\r\n")
		+_T("������ʾ���ڿ���������ʷ�е�һ�γ��֣����Ϊ��ɫ��������ʾ����������ں�����ںš�\r\n")
		+_T("�������Ը����ºŵķֲ������ж������Ƿ����ºţ����ǣ��������Լ���Ͷע��������ʷ������")
		+_T("(����ɱ��ʷ����������0)���������Ͷע��������ʷ�������������Ͷע��\r\n\r\n")
		+_T("��С�д�\r\n\r\n")
		+_T("������012-3456-789�ֶ���ȷ��С�д�ţ���ɫ����ͬ�����¡�\r\n")
		+_T("������������ͬ�������ʱ����Խ� 012-3456-789 ��Ϊ3�ζ�·��������\r\n\r\n")
		+_T("����С�д������в�ͬ����©���ڣ�����ͼ��������ĳ���������©���ڳ���ƽ������ʱ�������ڳ��ŵ�")
		+_T("���ʾͺܸߣ������ú��뷶Χ�����ˣ�\r\n012(3456��789)����1-2(1-3)\r\n\r\n")
		;
	
//	RefreshList();
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStat2::RefreshList(int iPeriod/* = 50*/)
{
	m_List.DeleteAllItems();
	
	int iCountHistory = pHistory->GetCount();
	if(0 == iCountHistory)
	{
		return;
	}
	
	CString str = _T(" ");
	C3D CNum;		// ���ں���
	C3D CNumLast;	// ���ں���
	
	// ��ʷ
	for(int i = 0; i < iPeriod; ++i)
	{
		CNum = pHistory->GetCNum(i);
		str.Empty();
		m_List.AddItem(pHistory->GetPeriodStr(i).Right(5), CNum.ToString(),
			str, str, str, str, str, str, str, str, str, str, str, str, str, str, str);
		
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
			for(int j = 2; j < 7; ++j)
				m_List.SetItemColor(i, j, crText, crBack);
		}
	}
	
	int iLines = m_List.GetItemCount();
	int loopCnt, n, iCol = 2;

	// ��©��ֵ
	loopCnt = iLines < iCountHistory ? iLines : iCountHistory - 1;
	for(int i = 0; i < loopCnt; ++i)
	{
		CNum = pHistory->GetCNum(i);
		n = pHistory->StatMiss(i + 1, CNum);
		
		m_List.SetItemText(i, iCol, EMFC::Int2Str(n));
	}
	++iCol;

	loopCnt = iLines < iCountHistory ? iLines : iCountHistory - 1;
	for(int i = 0; i < loopCnt; ++i)
	{
		CNum = pHistory->GetCNum(i);
		CNumLast = pHistory->GetCNum(i + 1);

		// ����
		n = CNumLast.CountNew(CNum);
		m_List.SetItemText(i, iCol, EMFC::Int2Str(n));

		// ����
		n = CNumLast.CountAlone(CNum);
		m_List.SetItemText(i, iCol + 1, EMFC::Int2Str(n));

		// ��б
		n = CNumLast.CountLeft(CNum);
		m_List.SetItemText(i, iCol + 2, EMFC::Int2Str(n));

		// ��б
		n = CNumLast.CountRight(CNum);
		m_List.SetItemText(i, iCol + 3, EMFC::Int2Str(n));
	}
	iCol += 4;

	// ������
#ifdef _UNRESTRICT_
	if( WND::IsCharDown( _T('7') ) )
	{
		pApp->iHot = 7;
	}
	else if( WND::IsCharDown( _T('5') ) )
	{
		pApp->iHot = 5;
	}
#endif
	CUIntArray aHot[3];
	int iCnt = pApp->iHot - 1;
	loopCnt = iLines + iCnt < iCountHistory ? iLines : iCountHistory - iCnt;
	for(int i = 0; i < loopCnt; ++i)
	{
		CString sHWC[3];
		pHistory->HotNum(i, sHWC[0], sHWC[1], sHWC[2], pApp->iHot);

		for(int j = 0; j < 3; ++j)
		{
			m_List.SetItemText(i, iCol + j, sHWC[j]);

			if(i > 0)
			{
				CNum = pHistory->GetCNum(i - 1);
				
				n = CNum.CountInStr(sHWC[j]);

				switch(n)
				{
				case 1:
					m_List.SetItemColor(i, iCol + j, crText, crGreen);
					break;
				case 2:
					m_List.SetItemColor(i, iCol + j, crText, crYellow);
					break;
				case 3:
					m_List.SetItemColor(i, iCol + j, crText, crRed);
					break;
				}
			}
		}
	}
	iCol += 3;
	
	// �º�
	int fnd;
	loopCnt = iLines;
	for(int i = 0; i < loopCnt; ++i)
	{
		CNum = pHistory->GetCNum(i);

		fnd = pHistory->FindNum(CNum, i + 1);
		if( -1 ==  fnd)
		{
			m_List.SetItemText(i, iCol, _T("��"));
			m_List.SetItemColor(i, iCol, crText, crGreen);
		}
		else
			m_List.SetItemText(i, iCol, pHistory->GetPeriodStr(fnd).Right(5));
	}
	++iCol;
	
	// С�д�
	loopCnt = iLines;
	for(int i = 0; i < loopCnt; ++i)
	{
		CNum = pHistory->GetCNum(i);
	
		for(int j = 0; j < 3; ++j)
		{
			str.Empty();
			if(0 == j)
			{
				for(int k = 0; k < 3; ++k)
					if(CNum[k] < 3)
					{
						str += (TCHAR)(_T('0') + CNum[k]);
					}
			}
			else if(1 == j)
			{
				for(int k = 0; k < 3; ++k)
					if(3 <= CNum[k] && CNum[k] <= 6)
					{
						str += (TCHAR)(_T('0') + CNum[k]);
					}
			}
			else
			{
				for(int k = 0; k < 3; ++k)
					if(CNum[k] > 6)
					{
						str += (TCHAR)(_T('0') + CNum[k]);
					}
			}
			
			m_List.SetItemText(i, iCol + j, str);
			
			switch( str.GetLength() )
			{
			case 1:
				m_List.SetItemColor(i, iCol + j, crText, crGreen);
				break;
			case 2:
				m_List.SetItemColor(i, iCol + j, crText, crYellow);
				break;
			case 3:
				m_List.SetItemColor(i, iCol + j, crText, crRed);
				break;
			}
		}
	}
	iCol += 3;
	
	// 012·
	loopCnt = iLines;
	for(int i = 0; i < loopCnt; ++i)
	{
		CNum = pHistory->GetCNum(i);
	
		for(int j = 0; j < 3; ++j)
		{
			str.Empty();
			if(0 == j)
			{
				for(int k = 0; k < 3; ++k)
					if(CNum[k] % 3 == 0)
					{
						str += (TCHAR)(_T('0') + CNum[k]);
					}
			}
			else if(1 == j)
			{
				for(int k = 0; k < 3; ++k)
					if(CNum[k] % 3 == 1)
					{
						str += (TCHAR)(_T('0') + CNum[k]);
					}
			}
			else
			{
				for(int k = 0; k < 3; ++k)
					if(CNum[k] % 3 == 2)
					{
						str += (TCHAR)(_T('0') + CNum[k]);
					}
			}
			
			m_List.SetItemText(i, iCol + j, str);
			
			switch( str.GetLength() )
			{
			case 1:
				m_List.SetItemColor(i, iCol + j, crText, crGreen);
				break;
			case 2:
				m_List.SetItemColor(i, iCol + j, crText, crYellow);
				break;
			case 3:
				m_List.SetItemColor(i, iCol + j, crText, crRed);
				break;
			}
		}
	}
	iCol += 3;
}
