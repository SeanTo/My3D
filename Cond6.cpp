// Cond6.cpp : implementation file
//

#include "stdafx.h"
#include "Cond6.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCond6 dialog


CCond6::CCond6(CWnd* pParent /*=NULL*/)
	: CDialog(CCond6::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCond6)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCond6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCond6)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCond6, CDialog)
	//{{AFX_MSG_MAP(CCond6)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCond6 message handlers
