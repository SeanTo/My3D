// My3D.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "My3D.h"
#include "My3DDlg.h"

#include "..\Share\WND.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3DApp

BEGIN_MESSAGE_MAP(CMy3DApp, CWinApp)
	//{{AFX_MSG_MAP(CMy3DApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DApp construction

CMy3DApp::CMy3DApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	aBase.RemoveAll();
	aResult[0].RemoveAll();
	aResult[1].RemoveAll();
	aResult[2].RemoveAll();

	iRecommandPeriod = 20;
	iRecommandNum = 9;
	iAnalyesPage = 0;
	iHot = 5;
	iMinToTray = 1;
	iSaveAndOpen = 1;
	iWarnRecommand = 1;
	iDeleteTip = 1;
	strVersion.Empty();
	strAuthor = _T("");

	rcScreen.SetRect(0, 0, 800, 600);

	bAutoBaseSel = (UINT)251;
	iErr1 = 0;
	iErr2 = 1;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMy3DApp object

CMy3DApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMy3DApp initialization

BOOL CMy3DApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

// #ifdef _AFXDLL
// 	Enable3dControls();			// Call this when using MFC in a shared DLL
// #else
// 	Enable3dControlsStatic();	// Call this when linking to MFC statically
// #endif


	// �������
#if !defined(_UNRESTRICT_)
	const CString strCurName = WND::GetExeName();
	CString strExeName;
	strExeName.LoadString(IDS_EXENAME);
	if(0 != strCurName.CompareNoCase(strExeName))
	{
		AfxMessageBox( _T("Ĭ���ļ��� My3D.exe��") );
		return FALSE;
	}
#endif // _UNRESTRICT_

	// ����·��
	const CString strPath = WND::GetAbsPath(TRUE);

	// �������Ŀ¼
	const CString strOutput = strPath + _T("Output");
	if( !WND::IsExistFile(strOutput) )
		CreateDirectory(strOutput, NULL);

	// �����³���
	const CString strUpdName = strPath + _T("LiveUpdate.upd");
	if( WND::IsExistFile(strUpdName) )
	{
		Sleep(1000);
		BOOL bUpdate = TRUE;
		const CString strExeName = strPath + _T("LiveUpdate.exe");

		int id = WND::FindExePID(_T("LiveUpdate.exe"));
		if(-1 != id)
		{
			if( IDYES == AfxMessageBox(_T("���ֿ��ø���������� LiveUpdate.exe ����������...\n")
				_T("�Ƿ�ǿ�ƽ��� LiveUpdate.exe ? (ѡ��[��]���´�����ʱ����)"), MB_YESNO | MB_ICONQUESTION) )
			{
				HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
				if(ProcessHandle)
					TerminateProcess(ProcessHandle,0);
			}
			else
				bUpdate = FALSE;
		}

		if(bUpdate)
		{
			if( !WND::IsExistFile(strPath + _T("Backup")) )
				CreateDirectory(strPath + _T("Backup"), NULL);
			
			CopyFile(strExeName, strPath + _T("Backup\\LiveUpdate.ex_"), FALSE);
			CopyFile(strUpdName, strExeName, FALSE);
			DeleteFile(strUpdName);
			
// 			AfxMessageBox(_T("���߸�������Ѹ��£�"), MB_OK | MB_ICONINFORMATION);
		}
	}

	// ��ʵ�����
	const CString strClassName= GetMyClassName();
	m_hMutex = OpenMutex (MUTEX_ALL_ACCESS, FALSE, strClassName) ;
	if (NULL == m_hMutex)
	{
		m_hMutex = CreateMutex(NULL, TRUE, strClassName) ;
	}
	else if(ERROR_ALREADY_EXISTS == ::GetLastError())
	{
		// �ϴ��쳣�˳�����ֹ�쳣ʵ��
		AfxMessageBox(_T("�ϴγ����쳣�˳���"));
	}
	else
	{
		// ����һ��ʵ���ᵽǰ̨
		WND::ActiveWindow(strClassName);
		return FALSE;
	}

	// ע���Լ��Ĵ�����
	WNDCLASS  wc  =  {0};  
	::GetClassInfo(AfxGetInstanceHandle(), "#32770", &wc); 
	wc.lpszClassName = strClassName;
	AfxRegisterClass(&wc);

	// ������
	CMy3DDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

/*
 *	�������
 */
VOID CMy3DApp::DispatchNum()
{
	aResult[0].RemoveAll();
	aResult[1].RemoveAll();
	aResult[2].RemoveAll();

	for(int i = 0; i < aBase.GetSize(); ++i)
		aResult[ C3D(aBase[i]).Type() ].Add(aBase[i]);
}

/*
 *	�ϳɺ���
 */
VOID CMy3DApp::CompoundNum(CUIntArray &arr)
{
	arr.RemoveAll();

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < aResult[i].GetSize(); ++j)
			arr.Add(aResult[i][j]);
	}
}

int CMy3DApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class

	if(m_hMutex != NULL)
		ReleaseMutex(m_hMutex);
	
	return CWinApp::ExitInstance();
}

////////////////////////////////////////////////////////////////
