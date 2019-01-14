// SaveOption.cpp : implementation file
//

#include "stdafx.h"
#include "SaveOption.h"
#include "My3DDlg.h"

#include "..\Share\WND.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveOption dialog


CSaveOption::CSaveOption(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveOption::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaveOption)
	m_bG6 = TRUE;
	m_bG3 = TRUE;
	m_bG1 = FALSE;
	m_iLine = 0;
	m_bSeparator = TRUE;
	m_bAddLineNum = FALSE;
	m_bFileNameSuffix = FALSE;
	m_bSaveAndOpen = FALSE;
	m_bExportCondNote = FALSE;
	//}}AFX_DATA_INIT

	pApp = (CMy3DApp *)AfxGetApp();
}


void CSaveOption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveOption)
	DDX_Check(pDX, IDC_CHECK_SG6, m_bG6);
	DDX_Check(pDX, IDC_CHECK_SG3, m_bG3);
	DDX_Check(pDX, IDC_CHECK_SG1, m_bG1);
	DDX_Radio(pDX, IDC_RADIO_L01, m_iLine);
	DDX_Check(pDX, IDC_CHECK_SEPARATOR, m_bSeparator);
	DDX_Check(pDX, IDC_CHECK_LINENUM, m_bAddLineNum);
	DDX_Check(pDX, IDC_CHECK_SUFFIX, m_bFileNameSuffix);
	DDX_Check(pDX, IDC_SAVE_AND_OPEN, m_bSaveAndOpen);
	DDX_Check(pDX, IDC_EXPORT_COND_NOTE, m_bExportCondNote);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveOption, CDialog)
	//{{AFX_MSG_MAP(CSaveOption)
	ON_BN_CLICKED(IDC_CHECK_LINENUM, OnCheckLinenum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveOption message handlers

void CSaveOption::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	// 号码注数
	int iNumCnt = 0;
	if( m_bG6 )
		iNumCnt += pApp->aResult[0].GetSize();
	if( m_bG3 )
		iNumCnt += pApp->aResult[1].GetSize();
	if( m_bG1 )
		iNumCnt += pApp->aResult[2].GetSize();

	// 每行注数
	int cnt = 0 == m_iLine ? 1 : m_iLine * 10;
	CHistory *pHistory = pApp->GetHistory();
	int iPeriod = pHistory->IsNull() ? 1 : pHistory->GetPeriod(0) + 1;
	
	CString strFile;
	strFile.Format(_T("%s-%05d-%03d%s"),
		pHistory->Is3D() ? _T("3D") : _T("P3"),
		iPeriod%100000,
		iNumCnt,
		m_bFileNameSuffix ? _T("(组)") : _T("(直)")
		);

	if( ! pApp->strAuthor.IsEmpty() )
		strFile += _T("-") + pApp->strAuthor;

	strFile += _T(".txt");

	strFile = WND::GetAbsPath(TRUE) + _T("Output\\") + strFile;
	strFile = WND::SelectFile(FALSE, strFile);

	if( !strFile.IsEmpty() )
	{
		CStdioFile fo(strFile, CFile::modeCreate | CFile::modeWrite | CFile::typeText );
		
		CString str;
		CString str1 = _T("");
		CString str2 = _T("");
		int iLineNum = 0;
		
		if(fo != NULL)
		{
			for(int k = 0; k < 3; ++k)
			{
				int i = 0, j = 0;
				while(i < pApp->aResult[k].GetSize())
				{
					if(0 == k && !m_bG6 || 1 == k && !m_bG3 || 2 == k && !m_bG1)
					{
						break;
					}
					
					str1 = _T("");
					str2 = _T("");
					
					for(j = 0; j < cnt; ++j)
					{
						if(i + j >= pApp->aResult[k].GetSize())
							break;
						
						str1 += C3D(pApp->aResult[k].GetAt(i + j)).ToString() + _T(" ");
					}
					i += j;
					str1.TrimRight();
					str1 += CString(_T("\n"));
					
					if(m_bAddLineNum && iLineNum < 100)
					{
						str.Format(_T("L%02d = "), iLineNum);
						str1 = str + str1;
						++iLineNum;
					}
					fo.WriteString(str1);
				}
				
				if(m_bSeparator)
				{
					str1 = _T("\n");
					fo.WriteString(str1);
				}
			}

			// 导出条件
			if( m_bExportCondNote )
			{
				CString strComment = ((CMy3DDlg*)GetParent())->ExportAllComment();
				fo.Write(strComment.GetBuffer(strComment.GetLength()), strComment.GetLength());
				strComment.ReleaseBuffer();
			}
			
			fo.Close();
			
			if( m_bSaveAndOpen )
				ShellExecute(NULL, _T("open"), strFile, NULL, NULL, SW_SHOWNORMAL);				
		}
		else
		{
			str.LoadString(IDS_TITLE);
			MessageBox(_T("打开文件错误。"), str, MB_ICONERROR);
		}

/*
		if( m_bG6 )
		{
			if( !TXT::Array2Txt(pApp->aResult[0], strFile, _T("%03d "), cnt) )
				return;
		}
		if( m_bG3 )
		{
			if( !TXT::Array2Txt(pApp->aResult[1], strFile, _T("%03d "), cnt, m_bG6 && TRUE, m_bSeparator) )
				return;
		}
		if( m_bG1 )
		{
			if( !TXT::Array2Txt(pApp->aResult[2], strFile, _T("%03d "), cnt, (m_bG6 || m_bG3) && TRUE, m_bSeparator) )
				return;
		}
		if( m_bSaveAndOpen )
			ShellExecute(NULL, _T("open"), strFile, NULL, NULL, SW_SHOWNORMAL);				
*/
	}
	else
		return;

	CDialog::OnOK();
}

BOOL CSaveOption::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSaveOption::OnCheckLinenum() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_bAddLineNum)
	{
		m_iLine = 2;
	}

	UpdateData(FALSE);
}
