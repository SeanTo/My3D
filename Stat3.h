#if !defined(AFX_WINSTAT_H__B2186B17_16EB_4880_BA62_DEEFA74F5325__INCLUDED_)
#define AFX_WINSTAT_H__B2186B17_16EB_4880_BA62_DEEFA74F5325__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WinStat.h : header file
//
#include "My3D.h"
#include "History.h"

#include "..\Share\SortListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CStat3 dialog

class CStat3 : public CDialog
{
	CMy3DApp *pApp;
	CHistory *pHistory;
	
// Construction
public:
	CStat3(CWnd* pParent = NULL);   // standard constructor
	BOOL Is3D() { return pHistory->Is3D(); }
	
	VOID RefreshList(int iNum = 9, int iNumPeriod = 20, int iPeriod = 50);
	
// Dialog Data
	//{{AFX_DATA(CStat3)
	enum { IDD = IDD_STAT3 };
	CSortListCtrl	m_List;
	CString m_strTip;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStat3)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStat3)
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINSTAT_H__B2186B17_16EB_4880_BA62_DEEFA74F5325__INCLUDED_)
