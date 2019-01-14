#if !defined(AFX_OTHERSTAT_H__25965E51_1486_48B6_A3C7_8F31A647C735__INCLUDED_)
#define AFX_OTHERSTAT_H__25965E51_1486_48B6_A3C7_8F31A647C735__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OtherStat.h : header file
//
#include "My3D.h"
#include "History.h"

#include "..\Share\SortListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CStat4 dialog

class CStat4 : public CDialog
{
	CMy3DApp *pApp;
	CHistory *pHistory;
	
	// Construction
public:
	CStat4(CWnd* pParent = NULL);   // standard constructor
	VOID RefreshList(int iPeriod = 50);
	
// Dialog Data
	//{{AFX_DATA(CStat4)
	enum { IDD = IDD_STAT4 };
	CSortListCtrl	m_List;
	CString m_strTip;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStat4)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStat4)
	virtual BOOL OnInitDialog();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTHERSTAT_H__25965E51_1486_48B6_A3C7_8F31A647C735__INCLUDED_)
