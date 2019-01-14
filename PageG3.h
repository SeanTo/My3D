#if !defined(AFX_PAGEG3_H__BD2A9BAD_499D_4FDA_8DE9_5E5B097F4714__INCLUDED_)
#define AFX_PAGEG3_H__BD2A9BAD_499D_4FDA_8DE9_5E5B097F4714__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageG3.h : header file
//
#include "..\Share\SortListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CPageG3 dialog

class CPageG3 : public CDialog
{
// Construction
public:
	CPageG3(CUIntArray *p = NULL, CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CPageG3)
	enum { IDD = IDD_DIALOG_G3 };
	CSortListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageG3)
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
	//{{AFX_MSG(CPageG3)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListG3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListG3(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CUIntArray *pData;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEG3_H__BD2A9BAD_499D_4FDA_8DE9_5E5B097F4714__INCLUDED_)
