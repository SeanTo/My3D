#if !defined(AFX_COND3_H__99183D43_C8F7_49E7_A2D8_D68D670A1F7F__INCLUDED_)
#define AFX_COND3_H__99183D43_C8F7_49E7_A2D8_D68D670A1F7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Cond3.h : header file
//

#include "My3D.h"
#include "History.h"

#include "bitset"
using std::bitset;

#include "..\Share\IniFile.h"

/////////////////////////////////////////////////////////////////////////////
// CCond3 dialog

class CCond3 : public CDialog
{
// Construction
public:
	CCond3(CWnd* pParent = NULL);   // standard constructor
	
	VOID Init();
	VOID ReadPara();
	BOOL IsValid();
	UINT FilterNum(UINT num, int iOffset = 0);

public:
	CString ExportComment();
	VOID SaveCondition(CIniFile &fin);
	VOID LoadCondition(CIniFile &fin);
	
	CToolTipCtrl m_tt;	// °´Å¥Ðü¸¡ÌáÊ¾	
	
// Dialog Data
	//{{AFX_DATA(CCond3)
	enum { IDD = IDD_COND3 };
	CComboBox	m_cmbC3206;
	CComboBox	m_cmbC3205;
	CComboBox	m_cmbC3202;
	CComboBox	m_cmbC3203;
	CComboBox	m_cmbC3204;
	CComboBox	m_cmbC3201;
	CComboBox	m_cmbC3104;
	CComboBox	m_cmbC3103;
	CComboBox	m_cmbC3102;
	CComboBox	m_cmbC3106;
	CComboBox	m_cmbC3105;
	CComboBox	m_cmbC3101;
	BOOL	m_bC301;
	BOOL	m_bC302;
	BOOL	m_bC303;
	BOOL	m_bC304;
	BOOL	m_bC305;
	BOOL	m_bC306;
	BOOL	m_bC307;
	BOOL	m_bC308;
	BOOL	m_bC309;
	BOOL	m_bC310;
	BOOL	m_bC311;
	BOOL	m_bC312;
	BOOL	m_bC314;
	BOOL	m_bC315;
	BOOL	m_bC316;
	BOOL	m_bC317;
	BOOL	m_bC318;
	BOOL	m_bC319;
	BOOL	m_bC320;
	BOOL	m_bExcludeSame;
	CString	m_strC301;
	CString	m_strC302;
	CString	m_strC303;
	CString	m_strC304;
	CString	m_strC305;
	CString	m_strC306;
	CString	m_strC307;
	CString	m_strC308;
	CString	m_strC309;
	CString	m_strC310;
	CString	m_strC311;
	CString	m_strC312;
	CString	m_strC320;
	CString m_strDecCnt;
	CString m_strSumCnt;
	CString m_strMulCnt;
	BOOL	m_iC301;
	BOOL	m_iC302;
	BOOL	m_iC303;
	BOOL	m_iC304;
	BOOL	m_iC305;
	BOOL	m_iC306;
	BOOL	m_iC307;
	BOOL	m_iC308;
	BOOL	m_iC309;
	BOOL	m_iC310;
	BOOL	m_iC311;
	BOOL	m_iC312;
	BOOL	m_iC313;
	CComboBox	m_cmbAllowError;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCond3)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	//}}AFX_VIRTUAL
	afx_msg VOID OnSelectCond(UINT nID);
	afx_msg VOID OnBtnReference(UINT nID);
	
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCond3)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CUIntArray *pData;
	CMy3DApp *pApp;
	CHistory *pHistory;

	bitset<20> bitCond;
	bitset<12> bitCond2;
	CString* aSTR_COND[16];

	VOID EnableCond();
	VOID SaveCondition();
	VOID LoadCondition();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COND3_H__99183D43_C8F7_49E7_A2D8_D68D670A1F7F__INCLUDED_)
