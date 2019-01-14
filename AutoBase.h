#if !defined(AFX_AUTOBASE_H__C4032E47_716B_423A_AEAB_C36DFAF50ABF__INCLUDED_)
#define AFX_AUTOBASE_H__C4032E47_716B_423A_AEAB_C36DFAF50ABF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AutoBase.h : header file
//

#include "..\Share\ListCtrlEx.h"


/////////////////////////////////////////////////////////////////////////////
// CAutoBase dialog

class CAutoBase : public CDialog
{
	bitset<32> bitSelDef;

// Construction
public:
	CAutoBase(CWnd* pParent = NULL);   // standard constructor

	void LoadSel();
	void SaveSel();

	CMy3DApp *pApp;
	CHistory *pHistory;

//	bitset<32> bitSel;

// Dialog Data
	//{{AFX_DATA(CAutoBase)
	enum { IDD = IDD_AUTO_BASE };
	CListCtrlEx		m_List;
	CSpinButtonCtrl m_Spin1;
	CSpinButtonCtrl m_Spin2;
	int m_iErr1;
	int m_iErr2;
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoBase)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAutoBase)
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillEffect();
	afx_msg void OnSelAll();
	afx_msg void OnClearAll();
	afx_msg void OnDefaultSel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOBASE_H__C4032E47_716B_423A_AEAB_C36DFAF50ABF__INCLUDED_)
