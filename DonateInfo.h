#if !defined(AFX_DONATEINFO_H__5B147130_D8D6_4C47_BF1E_A5D3B0B631BC__INCLUDED_)
#define AFX_DONATEINFO_H__5B147130_D8D6_4C47_BF1E_A5D3B0B631BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DonateInfo.h : header file
//

#include "..\Share\HyperLink.h"

/////////////////////////////////////////////////////////////////////////////
// CDonateInfo dialog

class CDonateInfo : public CDialog
{
	CHyperLink lnk1;
	CHyperLink lnk2;
	
// Construction
public:
	CDonateInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDonateInfo)
	enum { IDD = IDD_DONATE };
	CString	m_strMSN;
	CString	m_strQQ;
	CString	m_strZFB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDonateInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDonateInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DONATEINFO_H__5B147130_D8D6_4C47_BF1E_A5D3B0B631BC__INCLUDED_)
