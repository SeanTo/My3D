#if !defined(AFX_DATAANALYSE_H__26EF72C5_9303_4C6F_A945_354C4FFDC18E__INCLUDED_)
#define AFX_DATAANALYSE_H__26EF72C5_9303_4C6F_A945_354C4FFDC18E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataAnalyse.h : header file
//

#include "My3D.h"
#include "History.h"

#include "Stat1.h"
#include "Stat2.h"
#include "Stat3.h"
#include "Stat4.h"
#include "Stat5.h"
#include "Stat6.h"

#include "..\Share\TabSheet.h"

/////////////////////////////////////////////////////////////////////////////
// CDataAnalyse dialog

class CDataAnalyse : public CDialog
{
// Construction
public:
	CDataAnalyse(CWnd* pParent = NULL);   // standard constructor
	
	CMy3DApp *pApp;
	CHistory *pHistory;
	
//	UINT m_nNums;
//	UINT m_nAHP;

// Dialog Data
	//{{AFX_DATA(CDataAnalyse)
	enum { IDD = IDD_DATA_ANALYSE };
	CTabSheet	m_tabStat;
	CComboBox	m_cmbNums;
	CComboBox	m_cmbPeriod;
	int m_iSelPeriod;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataAnalyse)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDataAnalyse)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComAhp();
	afx_msg void OnSelchangeComNum();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSelchangeTabStat(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg void OnSelectPeriod(UINT nID);
	DECLARE_MESSAGE_MAP()

private:
	CStat1 m_pageStat1;
	CStat2 m_pageStat2;
	CStat3 m_pageStat3;
	CStat4 m_pageStat4;
	CStat5 m_pageStat5;
	CStat6 m_pageStat6;

	void EnableCond();
	void UpdateSubWnd(int iPage, int iPeriod);

	int iPeriod;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAANALYSE_H__26EF72C5_9303_4C6F_A945_354C4FFDC18E__INCLUDED_)
