#if !defined(AFX_INTERSECTION_H__B8CDC5B1_3188_4FCC_A0CD_E104752D2D92__INCLUDED_)
#define AFX_INTERSECTION_H__B8CDC5B1_3188_4FCC_A0CD_E104752D2D92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Intersection.h : header file
//

#include "My3D.h"

#define MAX_BASES 999

/////////////////////////////////////////////////////////////////////////////
// CIntersection dialog

class CIntersection : public CDialog
{
private:
	CString strTip;
	int GetCurSel();
	void EnEdit();
	
// Construction
public:
	CIntersection(CWnd* pParent = NULL);   // standard constructor
	
	VOID GetNumberFromFile(const CString &strFile, CUIntArray *arrNum);
	
	CUIntArray aG6;
	CUIntArray aG3;
	CUIntArray aG1;

	CStringArray arrFiles;

	CUIntArray arrBase[MAX_BASES+1];

	CMy3DApp *pApp;
	
// Dialog Data
	//{{AFX_DATA(CIntersection)
	enum { IDD = IDD_INTERSECTION };
	CListCtrl	m_List;
	CSpinButtonCtrl m_Spin1;
	CSpinButtonCtrl m_Spin2;
	int m_iErr1;
	int m_iErr2;
	CString m_strTip;
	CString m_strResult;
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIntersection)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIntersection)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelFile();
	afx_msg void OnClearAll();
	afx_msg void OnReverseSel();
	afx_msg void OnDelFile();
	afx_msg void OnEditFile();
	afx_msg void OnResort();
	afx_msg void OnSaveResult();
	afx_msg void OnClearResult();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERSECTION_H__B8CDC5B1_3188_4FCC_A0CD_E104752D2D92__INCLUDED_)
