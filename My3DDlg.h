// My3DDlg.h : header file
//

#if !defined(AFX_My3DDLG_H__D34345EC_29B2_46D2_B29F_F4A09FCF1326__INCLUDED_)
#define AFX_My3DDLG_H__D34345EC_29B2_46D2_B29F_F4A09FCF1326__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "My3D.h"

#include "PageSelNum.h"
#include "PageUseBase.h"

#include "Cond1.h"
#include "Cond2.h"
#include "Cond3.h"
#include "Cond4.h"
#include "Cond5.h"
#include "Cond6.h"

#include "PageG1.h"
#include "PageG3.h"
#include "PageG6.h"

#include "..\Share\TabSheet.h"


//#define USE_BTN_ST
#ifdef USE_BTN_ST
#include "BtnSt.h"
#endif // USE_BTN_ST



// 自定义消息，对应通知区图标事件
#define UM_ICONNOTIFY WM_USER+3000

/////////////////////////////////////////////////////////////////////////////
// CMy3DDlg dialog

class CMy3DDlg : public CDialog
{
// Construction
public:
	CMy3DDlg(CWnd* pParent = NULL);	// standard constructor

	CPageSelNum		m_page1;
	CPageUseBase	m_page2;

	CCond1			m_Cond1;
	CCond2			m_Cond2;
	CCond3			m_Cond3;
	CCond4			m_Cond4;
	CCond5			m_Cond5;
	CCond6			m_Cond6;
	
	CPageG1			m_pageG1;
	CPageG3			m_pageG3;
	CPageG6			m_pageG6;

	CToolTipCtrl m_tt;	// 按钮悬浮提示

public:
	CString ExportAllComment();		// 导出条件描述
	inline BOOL Is3D() { return pHistory->Is3D(); }

	UINT GetPeriods();
	VOID EnableButton();

	VOID DisplayResult();
	VOID DisplaySummary();
	VOID SetTitle();
	
// Dialog Data
	//{{AFX_DATA(CMy3DDlg)
	enum { IDD = IDD_My3D_DIALOG };
	CTabSheet	m_tabCond;
	CTabSheet	m_tabResult;
	CTabSheet	m_tabNumBase;
	CString	m_strTip1;
	CString	m_strTip2;
	CString	m_strTip3;
	CString	m_strTip4;
	int		m_iLotType;
	int		m_iStatPeriods;
	BOOL	m_bReplaceBase;
	BOOL	m_bSaveAsOpenCond;
	BOOL	m_bUnite;
	CComboBox	m_cmbAllowErrorAll;
	CComboBox	m_cmbAllowErrorPage;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DDlg)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// 处理通知区图标
	BOOL AddIcon();
	BOOL DeleteIcon();
	
	// 右键菜单
	void LoadContextMenu(CPoint &point);

	// Generated message map functions
	//{{AFX_MSG(CMy3DDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnBtnTest();
	afx_msg void OnBtnTest2();
	afx_msg void OnSingleToGroup();
	afx_msg void OnGroupToSingle();
	afx_msg void OnSentToBase();
	afx_msg void OnMutiCalc();
	afx_msg void OnSaveFile();
	afx_msg void OnDataInput();
	afx_msg void OnDataAnalyse();
	afx_msg void OnHelp();
	afx_msg void OnBtnAbout();
	afx_msg void OnInterBase();
	afx_msg void OnInterFile();
	afx_msg void OnAutoBase();
	afx_msg void OnExcludeBase();
	afx_msg void OnSelchangeTabResult(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAnalyseTrend();
	afx_msg void OnCheckUpdate();
	afx_msg void OnCondRead();
	afx_msg void OnCondReset();
	afx_msg void OnCondSave();
	afx_msg void OnDistribute();
	afx_msg void OnAnalyseResult();
	afx_msg void OnBtnHandDel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnIconNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSelectLottery(UINT nID);
	DECLARE_MESSAGE_MAP()


private:
	int m_iOldType;
	BOOL m_bOnce;
	BOOL m_bDisp;

/*
#ifdef USE_BTN_ST
	CButtonST m_btnDataInput;
	CButtonST m_btnDistribute;
	CButtonST m_btnTrend;
	CButtonST m_btnDataAnalyse;
	CButtonST m_btnCalcer;
	CButtonST m_btnHelp;
	CButtonST m_btnUpdate;
	CButtonST m_btnAbout;
	CButtonST m_btnExit;
#endif
*/
	
	CMy3DApp	*pApp;
	CHistory	*pHistory;

	CString		strExTool1;
	CString		strExTool2;
	CString		strExName1;
	CString		strExName2;

	VOID GetScreenInfo();
	VOID Init();
	VOID InitOnce();
	VOID ReadHistory();
	BOOL ReadVersion(CString &strExe, CString &strMdb, CString &strCalc);

	VOID ReplaceBase();
	VOID AddToBase(UINT type);
	
	BOOL CondSave(const CString &strFile, BOOL bDefault = FALSE);
	BOOL CondRead(const CString &strFile, BOOL bDefault = FALSE);

	inline BOOL IsAutoBase()
	{
		UpdateData(TRUE);
		return m_bReplaceBase;
	}
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_My3DDLG_H__D34345EC_29B2_46D2_B29F_F4A09FCF1326__INCLUDED_)
