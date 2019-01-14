// DonateInfo.cpp : implementation file
//

#include "stdafx.h"
#include "My3D.h"
#include "DonateInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDonateInfo dialog


CDonateInfo::CDonateInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDonateInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDonateInfo)
	m_strMSN = _T("tuxw2005@gmail.com");
	//}}AFX_DATA_INIT
}


void CDonateInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDonateInfo)
	DDX_Text(pDX, IDC_EDIT_MSN, m_strMSN);
	DDX_Text(pDX, IDC_EDIT_QQ, m_strQQ);
	DDX_Text(pDX, IDC_EDIT_ZFB, m_strZFB);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDonateInfo, CDialog)
	//{{AFX_MSG_MAP(CDonateInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDonateInfo message handlers

BOOL CDonateInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
