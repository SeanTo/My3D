// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__B2059836_BE8B_4136_9172_C2CFE11EFC54__INCLUDED_)
#define AFX_STDAFX_H__B2059836_BE8B_4136_9172_C2CFE11EFC54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

////////////////////////////////////////////////////////////////////////////////
#include "Common.h"

// VC6 下允许并列的for语名定义同名索引变量
#if _MSC_VER <= 1200
#define for if(TRUE) for
#endif // _MSC_VER

//#pragma warning(disable : 4996)

// #define _XDLCP_

#if !defined(_UNRESTRICT_)
	#define _UNRESTRICT_
	#if !defined(_UNRESTRICT2_)
		#define _UNRESTRICT2_
	#endif //_UNRESTRICT2_
#endif //_UNRESTRICT_

////////////////////////////////////////////////////////////////////////////////
 

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__B2059836_BE8B_4136_9172_C2CFE11EFC54__INCLUDED_)
