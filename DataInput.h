#if !defined(AFX_DATAINPUT_H__A47D6787_C407_4051_AEBA_0FE326F2E9A8__INCLUDED_)
#define AFX_DATAINPUT_H__A47D6787_C407_4051_AEBA_0FE326F2E9A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataInput.h : header file
//
#include "My3D.h"
#include "My3DDlg.h"
#include "History.h"

#include "..\Share\SortListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDataInput dialog

class CDataInput : public CDialog
{
// Construction
public:
	CDataInput(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CDataInput)
	enum { IDD = IDD_DATA_INPUT };
	CSortListCtrl	m_listData;
	CString	m_strNumber;
	CString	m_strPeriod;
	CString	m_strTail;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDataInput)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnExport();
	afx_msg void OnImport();
	afx_msg void OnModify();
	afx_msg void OnClickListDatabase(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnRclickListDatabase(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bModified;
	
	CMy3DApp *pApp;
	CHistory *pHistory;
	
	inline BOOL Is3D() { return pHistory->Is3D(); }
	INT  GetCurSel();
	VOID SetEditer(int index = -1);
	VOID Refresh();
	VOID Save();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAINPUT_H__A47D6787_C407_4051_AEBA_0FE326F2E9A8__INCLUDED_)
