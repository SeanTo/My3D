#if !defined(AFX_DATACHART_H__624A36E7_8DB0_4326_B445_201237D9C09B__INCLUDED_)
#define AFX_DATACHART_H__624A36E7_8DB0_4326_B445_201237D9C09B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataChart.h : header file
//

#include "My3D.h"
#include "History.h"

/////////////////////////////////////////////////////////////////////////////
// CDataChart dialog

class CDataChart : public CDialog
{
// Construction
public:
	CDataChart(CWnd* pParent = NULL);   // standard constructor
	VOID SetType(UINT nType);

// Dialog Data
	//{{AFX_DATA(CDataChart)
	enum { IDD = IDD_DATA_CHART };
	CComboBox	m_cmbAnalyseType;
	int		m_iPeriod;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataChart)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDataChart)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCmbAnalyseType();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg void OnSelectPeriod(UINT nID);
	DECLARE_MESSAGE_MAP()
private:
	CMy3DApp *pApp;
	CHistory *pHistory;
	CUIntArray m_Data;
	UINT m_nType;
	UINT nPeriod;
	
	CPen * pOldPen;
	CPen penLine;
	CFont *pOldFont;
	CFont fontVert;
	CFont fontHori;

	CRect rcPaint;
	int yMin, yMax;
	int xMin, xMax;
	int cx, cy;
	
	VOID Graph(CPaintDC *pDC, const CRect &rc);
	VOID GetPeriod(int iSel);
	BOOL DrawCoord(CPaintDC *pDC, const CRect &rc);
	int StatData(UINT nType, CUIntArray *p);

	inline BOOL Is3D() { return pHistory->Is3D(); }
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATACHART_H__624A36E7_8DB0_4326_B445_201237D9C09B__INCLUDED_)
