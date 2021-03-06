#if !defined(AFX_STAT5_H__F2C5A987_B24F_43AE_B0B6_347A1A52025F__INCLUDED_)
#define AFX_STAT5_H__F2C5A987_B24F_43AE_B0B6_347A1A52025F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Stat5.h : header file
//

#include "My3D.h"
#include "History.h"

#include "..\Share\SortListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CStat5 dialog

class CStat5 : public CDialog
{
	CMy3DApp *pApp;
	CHistory *pHistory;

// Construction
public:
	CStat5(CWnd* pParent = NULL);   // standard constructor
	VOID RefreshList(int iPeriod = 50);
	
// Dialog Data
	//{{AFX_DATA(CStat5)
	enum { IDD = IDD_STAT5 };
	CSortListCtrl	m_List;
	CString m_strTip;
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStat5)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStat5)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAT5_H__F2C5A987_B24F_43AE_B0B6_347A1A52025F__INCLUDED_)
