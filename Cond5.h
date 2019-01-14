#if !defined(AFX_COND5_H__C2C0B28D_299D_494A_BE9F_4F37DD80302A__INCLUDED_)
#define AFX_COND5_H__C2C0B28D_299D_494A_BE9F_4F37DD80302A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Cond5.h : header file
//
#include "My3D.h"
#include "History.h"

#include "bitset"
using std::bitset;

#include "..\Share\ListCtrlEx.h"
#include "..\Share\IniFile.h"

/////////////////////////////////////////////////////////////////////////////
// CCond5 dialog

class CCond5 : public CDialog
{
// Construction
public:
	CCond5(CWnd* pParent = NULL);   // standard constructor
	VOID Init();
	VOID ReadPara();
	BOOL IsValid();
	UINT FilterNum(const C3D &CNum, UINT nOffset = 0);
	
public:
	CString ExportComment();
	VOID SaveCondition(CIniFile &fin);
	VOID LoadCondition(CIniFile &fin);
	
// Dialog Data
	//{{AFX_DATA(CCond5)
	enum { IDD = IDD_COND5 };
	CListCtrlEx		m_List;
	int				m_iErr1;
	BOOL			m_bC501;
	CComboBox		m_cmbAllowError;
	BOOL			m_bOnceG3;
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCond5)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCond5)
	afx_msg void OnSelectCond();
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// 	afx_msg void OnLclickList(NMHDR* pNMHDR, LRESULT* pResult);
// 	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

private:
	VOID EnableCond();
	int AddCond(BOOL bSel = FALSE, const CString strCond = _T(""), const CString strRange = _T(""));

	CMy3DApp *pApp;
	CHistory *pHistory;
	CStringArray asRange;
	CUIntArray aiRange;
	
	CToolTipCtrl m_tt;	// °´Å¥Ðü¸¡ÌáÊ¾
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COND5_H__C2C0B28D_299D_494A_BE9F_4F37DD80302A__INCLUDED_)
