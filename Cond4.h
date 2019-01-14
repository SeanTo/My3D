#if !defined(AFX_COND4_H__A3C8221A_23F5_4F2E_9CA1_163CFE2F6D83__INCLUDED_)
#define AFX_COND4_H__A3C8221A_23F5_4F2E_9CA1_163CFE2F6D83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Cond4.h : header file
//

#include "My3D.h"

#include "bitset"
using std::bitset;

#include "..\Share\IniFile.h"
#include "..\Share\ListCtrlEx.h"

/////////////////////////////////////////////////////////////////////////////
// CCond4 dialog

class CCond4 : public CDialog
{
private:
	CMy3DApp * pApp;
	
// Construction
public:
	CCond4(CWnd* pParent = NULL);   // standard constructor

	VOID Init();
	VOID ReadPara();
	BOOL IsValid();
	UINT FilterNum(UINT num, UINT nOffset = 0);

public:
	CString ExportComment();
	VOID SaveCondition(CIniFile &fin);
	VOID LoadCondition(CIniFile &fin);
	
	
// Dialog Data
	//{{AFX_DATA(CCond4)
	enum { IDD = IDD_COND4 };
	CComboBox	m_cmbAllowError;
	int		m_iErr3;
	int		m_iErr4;
	BOOL	m_bC401;
	BOOL	m_bC402;
	BOOL	m_bC403;
	BOOL	m_bC404;
	BOOL	m_bC405;
	BOOL	m_bCNoOrder1;
	BOOL	m_bCNoOrder2;
	CString	m_strC4101;
	CString	m_strC4201;
	CString	m_strC4501;
	CString	m_strC4502;
	CString	m_strC4503;
	CString	m_strC4511;
	CString	m_strC4512;
	CString	m_strC4513;
	CListCtrlEx	m_List;
	CListCtrlEx	m_List4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCond4)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCond4)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickList4(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg VOID OnSelectCond(UINT nID);
	DECLARE_MESSAGE_MAP()
		
private:
	VOID EnableCond();
	int FilterNum_4(int num, const CString &str1, const CString &str2, const CString &str3);
	int AddCond3(BOOL bSel = FALSE, const CString str1 = _T(""), const CString str2 = _T(""), const CString str3 = _T(""));
	int AddCond4(BOOL bSel = FALSE, const CString str1 = _T(""), const CString str2 = _T(""), const CString str3 = _T(""));

	CUIntArray arrTwo1;
	CUIntArray arrTwo2;
	
	CToolTipCtrl m_tt;	// °´Å¥Ðü¸¡ÌáÊ¾
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COND4_H__A3C8221A_23F5_4F2E_9CA1_163CFE2F6D83__INCLUDED_)
