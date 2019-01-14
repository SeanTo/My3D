#if !defined(AFX_STAT6_H__DD39E7B9_4105_48CB_8F8A_56081047A670__INCLUDED_)
#define AFX_STAT6_H__DD39E7B9_4105_48CB_8F8A_56081047A670__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Stat6.h : header file
//

#include "My3D.h"
#include "History.h"

#include "..\Share\SortListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CStat6 dialog

class CStat6 : public CDialog
{
	CMy3DApp *pApp;
	CHistory *pHistory;
	
	// Construction
public:
	CStat6(CWnd* pParent = NULL);   // standard constructor
	VOID RefreshList(int iPeriod = 50);
	
// Dialog Data
	//{{AFX_DATA(CStat6)
	enum { IDD = IDD_STAT6 };
	CSortListCtrl	m_List;
	CString m_strTip;
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStat6)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStat6)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAT6_H__DD39E7B9_4105_48CB_8F8A_56081047A670__INCLUDED_)
