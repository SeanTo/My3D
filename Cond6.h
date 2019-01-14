#if !defined(AFX_COND6_H__F78C3361_FF4B_42C3_B629_D351DA5065C4__INCLUDED_)
#define AFX_COND6_H__F78C3361_FF4B_42C3_B629_D351DA5065C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Cond6.h : header file
//
#include "My3D.h"

/////////////////////////////////////////////////////////////////////////////
// CCond6 dialog

class CCond6 : public CDialog
{
// Construction
public:
	CCond6(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCond6)
	enum { IDD = IDD_COND6 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCond6)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCond6)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COND6_H__F78C3361_FF4B_42C3_B629_D351DA5065C4__INCLUDED_)
