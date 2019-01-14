#if !defined(AFX_PAGEUSEBASE_H__7FBAAB4C_EFF2_4276_AB02_6E4F24555651__INCLUDED_)
#define AFX_PAGEUSEBASE_H__7FBAAB4C_EFF2_4276_AB02_6E4F24555651__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageUseBase.h : header file
//

#include "My3D.h"

#define MAX_DIY_BASE 10

/////////////////////////////////////////////////////////////////////////////
// CPageUseBase dialog

class CPageUseBase : public CDialog
{
// Construction
public:
	CPageUseBase(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CPageUseBase)
	enum { IDD = IDD_DIALOG_BASE };
	CComboBox	m_cmbBase;
	CString	m_strBase;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageUseBase)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	VOID SetBase(const CString &str);
	VOID GetBase(CUIntArray *p, const CString &str = _T(""));
	CString GetBase() { UpdateData(TRUE); return m_strBase; }

	void AddBase(const CString &str);
	CString LoadProBase(int iIndex, BOOL bUpdate = TRUE);
	int LoadBaseFromFile(CUIntArray &arrBase, const CStdioFile *fin);

public:
	CString m_strName[MAX_DIY_BASE];
	CString m_strBaseStr[MAX_DIY_BASE];
	
protected:
	BOOL bOnce;
	UINT m_nNameCnt;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageUseBase)
	virtual BOOL OnInitDialog();
	afx_msg void OnDelBase();
	afx_msg void OnSelchangeCmbBase();
	afx_msg void OnBaseEdit();
	afx_msg void OnBaseRefresh();
	afx_msg void OnLoadBasefile();
	afx_msg void OnKillFocusBase();
	afx_msg void OnSetFocusBase();
	//}}AFX_MSG
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()


private:
	CMy3DApp	*pApp;
	CString		m_strBaseIniFile;
	
	VOID LoadHistory();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEUSEBASE_H__7FBAAB4C_EFF2_4276_AB02_6E4F24555651__INCLUDED_)
