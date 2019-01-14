#if !defined(AFX_PAGEG6_H__3DE2B18D_9878_4BD5_82AA_84607F774B3A__INCLUDED_)
#define AFX_PAGEG6_H__3DE2B18D_9878_4BD5_82AA_84607F774B3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageG6.h : header file
//
#include "..\Share\SortListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CPageG6 dialog

class CPageG6 : public CDialog
{
// Construction
public:
	CPageG6(CUIntArray *p = NULL, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageG6)
	enum { IDD = IDD_DIALOG_G6 };
	CSortListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageG6)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void SetSrcData(CUIntArray *p);
	void RefreshList();
	void DelCurSel();
	int GetCurSel();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageG6)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListG6(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListG6(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CUIntArray *pData;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEG6_H__3DE2B18D_9878_4BD5_82AA_84607F774B3A__INCLUDED_)
