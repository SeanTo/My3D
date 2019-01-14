// PageG6.cpp : implementation file
//

#include "stdafx.h"
#include "My3D.h"
#include "My3DDlg.h"
#include "PageG6.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageG6 dialog


CPageG6::CPageG6(CUIntArray *p /* = NULL */, CWnd* pParent /* = NULL */)
	: CDialog(CPageG6::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageG6)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	pData = p;
}

void CPageG6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageG6)
	DDX_Control(pDX, IDC_LIST_G6, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageG6, CDialog)
	//{{AFX_MSG_MAP(CPageG6)
	ON_NOTIFY(NM_CLICK, IDC_LIST_G6, OnClickListG6)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_G6, OnRclickListG6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageG6 message handlers

BOOL CPageG6::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	RefreshList();
	
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);//|LVS_EX_GRIDLINES);
	m_List.SetHeadings(_T("ÐòºÅ, 45;½á¹û,45;"), LVCFMT_CENTER );
	m_List.SetBkColor(RGB(128,128,128));
	m_List.LoadColumnInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPageG6::PreTranslateMessage(MSG* pMsg) 
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

void CPageG6::OnClickListG6(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	((CMy3DDlg*)(GetParent()->GetParent()))->EnableButton();

	*pResult = 0;
}

void CPageG6::OnRclickListG6(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	((CMy3DDlg*)(GetParent()->GetParent()))->EnableButton();
	
	*pResult = 0;
}

void CPageG6::SetSrcData(CUIntArray *p)
{
	ASSERT(p);
	pData = p;
}

void CPageG6::RefreshList()
{
	m_List.DeleteAllItems();

	if(NULL == pData)
	{
		return;
	}

	int iCount = pData->GetSize();
	if(0 == iCount)
	{
		return;
	}

	CString str1 = _T("");
	CString str2 = _T("");
	
	for(int i = 0; i < iCount; ++i)
	{
		str1.Format(_T("%5d"), i + 1);
		str2.Format(_T("%03d"), pData->GetAt(i));

		m_List.AddItem(str1, str2);

		if( i & 1)
		{
			m_List.SetItemColor(i, 0, RGB(0,0,0), RGB(203, 233, 241));
			m_List.SetItemColor(i, 1, RGB(0,0,0), RGB(203, 233, 241));
		}
	}

	UpdateData(FALSE);
}

void CPageG6::DelCurSel()
{
	int iSel = GetCurSel();

	if(-1 == iSel)
	{
		return;
	}

	pData->RemoveAt(iSel);
	RefreshList();
}

int CPageG6::GetCurSel()
{
	return m_List.GetCurSel();
}
