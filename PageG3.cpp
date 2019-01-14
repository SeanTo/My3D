// PageG3.cpp : implementation file
//

#include "stdafx.h"
#include "My3D.h"
#include "My3DDlg.h"
#include "PageG3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageG3 dialog


CPageG3::CPageG3(CUIntArray *p/* = NULL*/, CWnd* pParent /* = NULL */)
	: CDialog(CPageG3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageG3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	pData = p;
}

void CPageG3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageG3)
	DDX_Control(pDX, IDC_LIST_G3, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageG3, CDialog)
	//{{AFX_MSG_MAP(CPageG3)
	ON_NOTIFY(NM_CLICK, IDC_LIST_G3, OnClickListG3)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_G3, OnRclickListG3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageG3 message handlers

BOOL CPageG3::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);//|LVS_EX_GRIDLINES);
	m_List.SetHeadings(_T("ÐòºÅ, 45;½á¹û,45;"), LVCFMT_CENTER );
	m_List.SetBkColor(RGB(128,128,128));
	m_List.LoadColumnInfo();
	
	RefreshList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPageG3::PreTranslateMessage(MSG* pMsg) 
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

void CPageG3::OnClickListG3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	((CMy3DDlg*)(GetParent()->GetParent()))->EnableButton();
	
	*pResult = 0;
}

void CPageG3::OnRclickListG3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	((CMy3DDlg*)(GetParent()->GetParent()))->EnableButton();
	
	*pResult = 0;
}

void CPageG3::SetSrcData(CUIntArray *p)
{
	ASSERT(p);
	pData = p;
}

void CPageG3::RefreshList()
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

void CPageG3::DelCurSel()
{
	int iSel = GetCurSel();
	
	if(-1 == iSel)
	{
		return;
	}
	
	pData->RemoveAt(iSel);
	RefreshList();
}

int CPageG3::GetCurSel()
{
	return m_List.GetCurSel();
}
