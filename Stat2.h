#if !defined(AFX_STATSTAT_H__D95E9A44_137E_4C38_9AF0_9364A8C138FC__INCLUDED_)
#define AFX_STATSTAT_H__D95E9A44_137E_4C38_9AF0_9364A8C138FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatStat.h : header file
//

#include "My3D.h"
#include "History.h"

#include "..\Share\SortListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CStat2 dialog

class CStat2 : public CDialog
{
	CMy3DApp *pApp;
	CHistory *pHistory;
	
	// Construction
public:
	CStat2(CWnd* pParent = NULL);   // standard constructor
	VOID RefreshList(int iPeriod = 50);
	
// Dialog Data
	//{{AFX_DATA(CStat2)
	enum { IDD = IDD_STAT2 };
	CSortListCtrl	m_List;
	CString m_strTip;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStat2)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStat2)
	virtual BOOL OnInitDialog();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATSTAT_H__D95E9A44_137E_4C38_9AF0_9364A8C138FC__INCLUDED_)
