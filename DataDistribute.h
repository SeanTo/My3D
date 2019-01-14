#if !defined(AFX_DATADISTRIBUTE_H__60BAA3C4_13B4_407A_BBC2_6FEEE2554893__INCLUDED_)
#define AFX_DATADISTRIBUTE_H__60BAA3C4_13B4_407A_BBC2_6FEEE2554893__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataDistribute.h : header file
//
#include "My3D.h"
#include "History.h"

#include "..\Share\SortListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDataDistribute dialog

class CDataDistribute : public CDialog
{
// Construction
public:
	CDataDistribute(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDataDistribute)
	enum { IDD = IDD_DATA_DISTRIBUTE };
	CSortListCtrl	m_list1;
	int		m_iSel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataDistribute)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDataDistribute)
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg void OnSelectPeriod(UINT nID);
	DECLARE_MESSAGE_MAP()
private:
	CMy3DApp *pApp;
	CHistory *pHistory;
	UINT nPeriod;
	CString strPeriod;
	CString strNum;
	CString str[40];
	VOID GetPeriod(int iSel);
	VOID StatData();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATADISTRIBUTE_H__60BAA3C4_13B4_407A_BBC2_6FEEE2554893__INCLUDED_)
