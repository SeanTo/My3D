#if !defined(AFX_COMMONSTAT_H__0F05650A_EBE3_4E12_AA7D_57E7E4EBA8BE__INCLUDED_)
#define AFX_COMMONSTAT_H__0F05650A_EBE3_4E12_AA7D_57E7E4EBA8BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommonStat.h : header file
//
#include "My3D.h"
#include "History.h"

#include "..\Share\SortListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CStat1 dialog

class CStat1 : public CDialog
{
	CMy3DApp *pApp;
	CHistory *pHistory;
	
	// Construction
public:
	CStat1(CWnd* pParent = NULL);   // standard constructor
	VOID RefreshList(int iPeriod);
	
	inline BOOL IsPrime(UINT n)
	{
		return 2 == n || 3 == n || 5 == n || 7 == n;
	}
	inline BOOL IsContinue(int n1, int n2)
	{
		return 1 == abs(n1 - n2) || 9 == abs(n1 - n2);
	}
	
// Dialog Data
	//{{AFX_DATA(CStat1)
	enum { IDD = IDD_STAT1 };
	CSortListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStat1)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStat1)
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMONSTAT_H__0F05650A_EBE3_4E12_AA7D_57E7E4EBA8BE__INCLUDED_)
