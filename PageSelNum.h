#if !defined(AFX_PAGESELNUM_H__B95D7FCF_78E9_456D_AF77_4875786FC970__INCLUDED_)
#define AFX_PAGESELNUM_H__B95D7FCF_78E9_456D_AF77_4875786FC970__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageSelNum.h : header file
//

#include "My3D.h"

#include "bitset"
using std::bitset;

#include "..\Share\IniFile.h"

/////////////////////////////////////////////////////////////////////////////
// CPageSelNum dialog

class CPageSelNum : public CDialog
{
// Construction
public:
	CPageSelNum(CWnd* pParent = NULL);   // standard constructor

public:
	VOID Init();
	VOID SaveCondition(CIniFile &fin);
	VOID LoadCondition(CIniFile &fin);

public:
	VOID GetBase(CUIntArray *p);
	
// Dialog Data
	//{{AFX_DATA(CPageSelNum)
	enum { IDD = IDD_DIALOG_NUMBER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageSelNum)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageSelNum)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg void OnClearAll(UINT nID);
	afx_msg void OnReverseSel(UINT nID);
	afx_msg void OnRecommendSel(UINT nID);
	afx_msg void OnSelectNum(UINT nID);
	DECLARE_MESSAGE_MAP()
	
private:
	CMy3DApp	*pApp;
	bitset<30> bsMask;
	VOID SetCond(bitset<30> &bc);
	VOID GetCond(bitset<30> &bc);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESELNUM_H__B95D7FCF_78E9_456D_AF77_4875786FC970__INCLUDED_)
