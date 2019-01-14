// My3D.h : main header file for the My3D application
//

#if !defined(AFX_My3D_H__705A277B_5A4F_427C_8607_7219E1D825BA__INCLUDED_)
#define AFX_My3D_H__705A277B_5A4F_427C_8607_7219E1D825BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "History.h"

#include "bitset"
using std::bitset;

////////////////////////////////////////////////////////////////////////////////
// CMy3DApp:
// See My3D.cpp for the implementation of this class
//

class CMy3DApp : public CWinApp
{
public:
	CMy3DApp();
	LPCTSTR GetMyClassName() { return _T("My3DClassName"); }
	
	VOID DispatchNum();					// �������
	VOID CompoundNum(CUIntArray &arr);	// �������

	CHistory* GetHistory() { return &m_History; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy3DApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// ȫ�ֱ���
public:
	CUIntArray aBase;		// Ԥ���ɴ��
	CUIntArray aResult[3];	// ���˽��
	
	// ��������
	int iRecommandPeriod;	// �Ƽ�����
	int iRecommandNum;		// �Ƽ�����
	int iAnalyesPage;		// ���ݵ�ǰҳ
	int iHot;				// ������ͳ������
	
	// ��������
	int			iMinToTray;		// ��С����֪ͨ��
	int			iSaveAndOpen;	// ������
	int			iWarnRecommand;	// �Ƽ�����
	int			iDeleteTip;		// ɾ��������ʾ
	CRect rcScreen;				// ��Ļ��С
	CString		strVersion;		// �汾��
	CString		strAuthor;
	
	// �Զ����ѡ��
	bitset<32> bAutoBaseSel;
	int iErr1;
	int iErr2;
		
private:
	CHistory m_History;
	HANDLE m_hMutex;			// ��ʵ��������
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_My3D_H__705A277B_5A4F_427C_8607_7219E1D825BA__INCLUDED_)
