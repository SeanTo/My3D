#if !defined(AFX_WINHISTORY_H__647BE8B8_426C_4546_A67B_80F690844564__INCLUDED_)
#define AFX_WINHISTORY_H__647BE8B8_426C_4546_A67B_80F690844564__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WinHistory.h : header file
//
#include "My3D.h"
#include "History.h"

#include "..\Share\SortListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CWinHistory dialog

class CWinHistory : public CDialog
{
// Construction
public:
	CWinHistory(const CString &strCaption, UINT nPeriod, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWinHistory)
	enum { IDD = IDD_WIN_HISTORY };
	CSortListCtrl	m_listWin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinHistory)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	VOID AddColumn(const CString &str, UINT nColumns, UINT nExWidth);
	VOID SetStatData(CUIntArray *pRes0,
		CUIntArray *pRes1 = NULL,
		CUIntArray *pRes2 = NULL,
		CUIntArray *pRes3 = NULL,
		CUIntArray *pRes4 = NULL,
		CUIntArray *pRes5 = NULL,
		CUIntArray *pRes6 = NULL,
		CUIntArray *pRes7 = NULL,
		CUIntArray *pRes8 = NULL,
		CUIntArray *pRes9 = NULL,
		CUIntArray *pRes10 = NULL,
		CUIntArray *pRes11 = NULL,
		CUIntArray *pRes12 = NULL,
		CUIntArray *pRes13 = NULL,
		CUIntArray *pRes14 = NULL,
		CUIntArray *pRes15 = NULL,
		CUIntArray *pRes16 = NULL,
		CUIntArray *pRes17 = NULL,
		CUIntArray *pRes18 = NULL
		);
	
//	VOID SetStatData(CUIntArray *pBase[], UINT cnt);
	
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWinHistory)
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickListWin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMy3DApp *pApp;
	CHistory *pHistory;
	CUIntArray *p[19];
	
	CString m_strCaption;
	CString m_strHeader;
	CString m_strMark;

	UINT m_nCols;
	UINT m_nAddWidth;
	UINT m_nPeriod;
	
	VOID DisplayRes();
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINHISTORY_H__647BE8B8_426C_4546_A67B_80F690844564__INCLUDED_)
