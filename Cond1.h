#if !defined(AFX_COND1_H__89FA9EAF_C25E_43C3_9479_D35019C23B9D__INCLUDED_)
#define AFX_COND1_H__89FA9EAF_C25E_43C3_9479_D35019C23B9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Cond1.h : header file
//
#include "..\Share\IniFile.h"
#include "My3D.h"

#include "History.h"

#include "bitset"
using std::bitset;


/////////////////////////////////////////////////////////////////////////////
// CCond1 dialog

class CCond1 : public CDialog
{
// Construction
public:
	CCond1(CWnd* pParent = NULL);   // standard constructor
	VOID Init();
	VOID ReadPara();
	BOOL IsValid();
	UINT FilterNum(UINT num, int nOffset = 0);

public:
	CString ExportComment();
	VOID SaveCondition(CIniFile& fin);
	VOID LoadCondition(CIniFile& fin);
	
// Dialog Data
	//{{AFX_DATA(CCond1)
	enum { IDD = IDD_COND1 };
	CString	m_strC101;
	CString	m_strC102;
	CString	m_strC103;
	CString	m_strC104;
	CString	m_strC105;
	CString	m_strC106;
	CString	m_strC107;
	CString	m_strC108;
	CString	m_strC109;
	CString	m_strC110;
	CString	m_strC111;
	CString	m_strC112;
	CString	m_strC113;
	CString	m_strC114;
	CString	m_strC115;
	BOOL	m_bC101;
	BOOL	m_bC102;
	BOOL	m_bC103;
	BOOL	m_bC104;
	BOOL	m_bC105;
	BOOL	m_bC106;
	BOOL	m_bC107;
	BOOL	m_bC108;
	BOOL	m_bC109;
	BOOL	m_bC110;
	BOOL	m_bC111;
	BOOL	m_bC112;
	BOOL	m_bC113;
	BOOL	m_bC114;
	BOOL	m_bC115;
	int	m_iC201;
	int	m_iC202;
	int	m_iC203;
	int	m_iC204;
	int	m_iC205;
	int	m_iC206;
	int	m_iC207;
	int	m_iC208;
	int	m_iC209;
	int	m_iC210;
	int	m_iC211;
	int	m_iC212;
	int	m_iC213;
	int	m_iC214;
	int	m_iC215;
	CComboBox	m_cmbAllowError;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCond1)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	afx_msg void OnBtnReference(UINT nID);
	afx_msg VOID OnSelectCond(UINT nID);
	
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCond1)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
	CFont font;
	CMy3DApp *pApp;
	CHistory *pHistory;
	
	bitset<30> bitCond;
	CString* aSTR_COND[15];

	CUIntArray arrSum;
	
	void EnableCond();
	void LoadCondition();
	void SaveCondition();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COND1_H__89FA9EAF_C25E_43C3_9479_D35019C23B9D__INCLUDED_)
