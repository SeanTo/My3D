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
	
	VOID DispatchNum();					// 号码分类
	VOID CompoundNum(CUIntArray &arr);	// 号码组合

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

	// 全局变量
public:
	CUIntArray aBase;		// 预生成大底
	CUIntArray aResult[3];	// 过滤结果
	
	// 参数记忆
	int iRecommandPeriod;	// 推荐期数
	int iRecommandNum;		// 推荐码数
	int iAnalyesPage;		// 数据当前页
	int iHot;				// 热温冷统计期数
	
	// 环境配置
	int			iMinToTray;		// 最小化到通知区
	int			iSaveAndOpen;	// 保存后打开
	int			iWarnRecommand;	// 推荐警告
	int			iDeleteTip;		// 删除条件提示
	CRect rcScreen;				// 屏幕大小
	CString		strVersion;		// 版本号
	CString		strAuthor;
	
	// 自动大底选项
	bitset<32> bAutoBaseSel;
	int iErr1;
	int iErr2;
		
private:
	CHistory m_History;
	HANDLE m_hMutex;			// 多实例互斥量
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_My3D_H__705A277B_5A4F_427C_8607_7219E1D825BA__INCLUDED_)
