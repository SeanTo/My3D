#if !defined(AFX_PAGEG1_H__F0E3DFAD_3D98_461E_BECD_3DAB0ED3EE35__INCLUDED_)
#define AFX_PAGEG1_H__F0E3DFAD_3D98_461E_BECD_3DAB0ED3EE35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageG1.h : header file
//
#include "..\Share\SortListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CPageG1 dialog

class CPageG1 : public CDialog
{
// Construction
public:
	CPageG1(CUIntArray *p = NULL, CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CPageG1)
	enum { IDD = IDD_DIALOG_G1 };
	CSortListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageG1)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
public:
	void SetSrcData(CUIntArray *p);
	void RefreshList();
	void DelCurSel();
	int GetCurSel();
		
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageG1)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListG1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListG1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CUIntArray *pData;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEG1_H__F0E3DFAD_3D98_461E_BECD_3DAB0ED3EE35__INCLUDED_)
