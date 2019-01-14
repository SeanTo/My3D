#if !defined(AFX_COND2_H__11B29137_FF05_457D_B3DF_5905CBB8430A__INCLUDED_)
#define AFX_COND2_H__11B29137_FF05_457D_B3DF_5905CBB8430A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Cond2.h : header file
//
#include "bitset"
using std::bitset;

#include "..\Share\IniFile.h"

/////////////////////////////////////////////////////////////////////////////
// CCond2 dialog

class CCond2 : public CDialog
{
// Construction
public:
	CCond2(CWnd* pParent = NULL);   // standard constructor
	VOID Init();
	VOID ReadPara();
	BOOL IsValid();
	UINT FilterNum(UINT num, UINT nOffset = 0);
	
public:
	CString ExportComment();
	VOID SaveCondition(CIniFile &fin);
	VOID LoadCondition(CIniFile &fin);

// Dialog Data
	//{{AFX_DATA(CCond2)
	enum { IDD = IDD_COND2 };
	BOOL	m_bC201;
	BOOL	m_bC202;
	BOOL	m_bC203;
	BOOL	m_bC204;
	CComboBox	m_cmbAllowError;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCond2)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	afx_msg VOID OnSelectCond(UINT nID);
	afx_msg VOID OnBtnCls(UINT nID);
	afx_msg VOID OnBtnReverse(UINT nID);
	afx_msg VOID OnBtnReference(UINT nID);
	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCond2)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMy3DApp *pApp;

	bitset<28> sel1;
	bitset<27> sel2;
	
	VOID EnableCond();
	VOID SaveCondition();
	VOID LoadCondition();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COND2_H__11B29137_FF05_457D_B3DF_5905CBB8430A__INCLUDED_)
