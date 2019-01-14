#if !defined(AFX_SAVEOPTION_H__3FDE89CA_2374_4538_80FC_FF0EDE896558__INCLUDED_)
#define AFX_SAVEOPTION_H__3FDE89CA_2374_4538_80FC_FF0EDE896558__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveOption.h : header file
//
#include "My3D.h"

/////////////////////////////////////////////////////////////////////////////
// CSaveOption dialog

class CSaveOption : public CDialog
{
// Construction
public:
	CSaveOption(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSaveOption)
	enum { IDD = IDD_DIALOG_SAVE };
	BOOL	m_bG6;
	BOOL	m_bG3;
	BOOL	m_bG1;
	int		m_iLine;
	BOOL	m_bSeparator;
	BOOL	m_bAddLineNum;
	BOOL	m_bFileNameSuffix;
	BOOL	m_bSaveAndOpen;
	BOOL	m_bExportCondNote;
	//}}AFX_DATA

	CMy3DApp *pApp;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveOption)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSaveOption)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckLinenum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEOPTION_H__3FDE89CA_2374_4538_80FC_FF0EDE896558__INCLUDED_)
