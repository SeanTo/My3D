// PageUseBase.cpp : implementation file
//

#include "stdafx.h"
#include "PageUseBase.h"

#include "..\Share\IniFile.h"
#include "..\Share\TXT.h"
#include "..\Share\WND.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageUseBase dialog


CPageUseBase::CPageUseBase(CWnd* pParent /*=NULL*/)
	: CDialog(CPageUseBase::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageUseBase)
	m_strBase = _T("");
	//}}AFX_DATA_INIT

	bOnce = TRUE;
	m_nNameCnt = 0;
	pApp = (CMy3DApp *)AfxGetApp();
	m_strBase = _T("输入/粘贴号码\r\n或选择预置大底");

	m_strBaseIniFile.LoadString(IDS_BASE_INI_FILE);
	m_strBaseIniFile = WND::GetAbsPath() + CString(_T("\\")) + m_strBaseIniFile;
}


void CPageUseBase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageUseBase)
	DDX_Control(pDX, IDC_CMB_BASE, m_cmbBase);
	DDX_Text(pDX, IDC_EDIT_BASE, m_strBase);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageUseBase, CDialog)
	//{{AFX_MSG_MAP(CPageUseBase)
	ON_BN_CLICKED(IDC_DEL_BASE, OnDelBase)
	ON_CBN_SELCHANGE(IDC_CMB_BASE, OnSelchangeCmbBase)
	ON_BN_CLICKED(IDC_BASE_EDIT, OnBaseEdit)
	ON_BN_CLICKED(IDC_BASE_REFRESH, OnBaseRefresh)
	ON_BN_CLICKED(IDC_LOAD_BASEFILE, OnLoadBasefile)
	ON_EN_KILLFOCUS(IDC_EDIT_BASE, OnKillFocusBase)
	ON_EN_SETFOCUS(IDC_EDIT_BASE, OnSetFocusBase)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageUseBase message handlers

BOOL CPageUseBase::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	if(bOnce)
	{
		OnBaseRefresh();
	}

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

VOID CPageUseBase::GetBase(CUIntArray *p, const CString &str/* = _T("")*/)
{
	UpdateData(TRUE);

	if(0 == str.GetLength())
		C3D::Str2Array(m_strBase, *p);
	else
		C3D::Str2Array(str, *p);

	EMFC::SortArray(*p);
}

void CPageUseBase::SetBase(const CString &str)
{
	CString ss = str;
	ss.TrimLeft();
	ss.TrimRight();

	m_strBase = str;
	UpdateData(FALSE);
}

void CPageUseBase::AddBase(const CString &str)
{
	CString ss = str;
	ss.TrimLeft();
	ss.TrimRight();
	
	if( 0 == ss.GetLength() )
	{
		return;
	}

	m_strBase.TrimLeft();
	m_strBase.TrimRight();
	
	if( !m_strBase.IsEmpty() )
		m_strBase += CString(_T("\r\n\r\n"));

	m_strBase += ss;

	UpdateData(FALSE);
}

void CPageUseBase::OnDelBase() 
{
	m_strBase.Empty();
	m_cmbBase.SetCurSel(-1);
	UpdateData(FALSE);
}

void CPageUseBase::OnBaseEdit() 
{
	if( !WND::IsExistFile(m_strBaseIniFile) )
	{
		CString msg;
		msg.Format("找不到自定义大底文件\n%s\n\n是否需要生成一个默认文件?", m_strBaseIniFile);

		CString strCaption;
		strCaption.LoadString(IDS_TITLE);

		if( IDNO == MessageBox(msg, strCaption, MB_YESNO) )
		{
			return;
		}

		CStdioFile fini;

		if( fini.Open(m_strBaseIniFile, CFile::modeCreate | CFile::modeWrite | CFile::typeText) )
		{
			fini.WriteString(_T("# 醉排三 自定义大底文件\n"));

			fini.WriteString(_T("\n[NAME]\n"));
			fini.WriteString(_T("NAME00 = 自定义一\n"));
			fini.WriteString(_T("NAME01 = 自定义二\n"));
			fini.WriteString(_T("NAME02 = \n"));
			fini.WriteString(_T("NAME03 = \n"));
			fini.WriteString(_T("NAME04 = \n"));
			fini.WriteString(_T("NAME05 = \n"));
			fini.WriteString(_T("NAME06 = \n"));
			fini.WriteString(_T("NAME07 = \n"));
			fini.WriteString(_T("NAME08 = \n"));
			fini.WriteString(_T("NAME09 = \n"));

			fini.WriteString(_T("\n[自定义一]\n"));
			fini.WriteString(_T("LINES = 3\n"));
			fini.WriteString(_T("L00 = 123 456 789\n"));
			fini.WriteString(_T("L01 = 000 111 222\n"));
			fini.WriteString(_T("L02 = 358 289 334\n"));
			
			fini.WriteString(_T("\n[自定义二]\n"));
			fini.WriteString(_T("LINES = 3\n"));
			fini.WriteString(_T("L00 = 123 456 789\n"));
			fini.WriteString(_T("L01 = 000 111 222\n"));
			fini.WriteString(_T("L02 = 358 289 334\n"));
			
			fini.Close();
		}
		else
		{
			MessageBox(_T("创建文件失败！"), strCaption, MB_ICONERROR);
			return;
		}
	}
	
	ShellExecute(NULL, _T("open"), m_strBaseIniFile, NULL, NULL, SW_SHOWNORMAL);
}

void CPageUseBase::OnBaseRefresh() 
{
	if(!bOnce)
	{
		CString str;
		str.LoadString(IDS_TITLE);

		if(  MessageBox(_T("手工编辑自定义大底文件后才需要刷新...\r\n\r\n继续吗?"),
			str, MB_OKCANCEL|MB_ICONQUESTION) == IDCANCEL)
		{
			return;
		}
	}
	
	m_cmbBase.ResetContent();
	
	CIniFile fIniBase;
	if( !fIniBase.Create(m_strBaseIniFile) )
	{
		if( !bOnce )
		{
			CString str;
			str.LoadString(IDS_TITLE);
			
			MessageBox( _T("找不到自定义大底文件!"), str, MB_ICONERROR );
		}
	}
	
	CString str;
	int lines = 0;
	
	for(int i = 0; i < MAX_DIY_BASE; ++i)
	{
		m_strBaseStr[i].Empty();
		
		str.Format(_T("NAME%02d"), i);
		m_strName[i].Empty();
		
		fIniBase.GetVarStr(_T("NAME"), str, m_strName[i]);
		m_strName[i].TrimLeft();
		m_strName[i].TrimRight();
		
		if(!m_strName[i].IsEmpty())
		{
			m_cmbBase.AddString(m_strName[i]);
			
			lines = -1;
			fIniBase.GetVarInt(m_strName[i], "LINES", lines);
			
			if(lines > 0)
			{
				CString strLine;
				for(int j = 0; j < lines && j < 100; ++j)
				{
					strLine.Format(_T("L%02d"), j);
					str.Empty();
					
					fIniBase.GetVarStr(m_strName[i], strLine, str);
					str.TrimLeft();
					str.TrimRight();
					
					m_strBaseStr[i] = m_strBaseStr[i] + CString(_T(" ")) + str;
				}
				m_strBaseStr[i].TrimLeft();
				m_strBaseStr[i].TrimRight();
			}
		}
		else
		{
			break;
		}
	}

	m_cmbBase.AddString(_T("=历史"));
	m_cmbBase.AddString(_T("=半顺"));
	m_cmbBase.AddString(_T("=杂六"));
	m_cmbBase.AddString(_T("=拖拉机"));
	m_cmbBase.AddString(_T("=组三"));
	m_cmbBase.AddString(_T("=豹子"));
	m_cmbBase.AddString(_T("=组六偶和"));
	m_cmbBase.AddString(_T("=组六奇和"));
	m_cmbBase.AddString(_T("=正常和"));
	m_cmbBase.AddString(_T("=大和"));
	m_cmbBase.AddString(_T("=小和"));
	m_cmbBase.AddString(_T("=超级冷态"));
	
	bOnce = FALSE;
}

void CPageUseBase::OnSelchangeCmbBase() 
{
	const int pro = 12;
	int diy = m_cmbBase.GetCount() - pro;
	int sel = m_cmbBase.GetCurSel();
	
	if(sel < diy)
	{
		SetBase(m_strBaseStr[sel]);
	}
	else
	{
		LoadProBase(sel - diy);
	}
	
	UpdateData(FALSE);
}

CString CPageUseBase::LoadProBase(int iIndex, BOOL bUpdate /* = TRUE */)
{
	// 历史、半顺、杂六、拖拉机、组三、豹子
	// 组六偶和、组六奇和、正常和、大和、小和

	CString str = _T("");
	
	if(0 == iIndex) // 历史
	{
		LoadHistory();
		return m_strBase;
	}
	else if(5 == iIndex) // 豹子
	{
		str = _T("000 111 222 333 444 555 666 777 888 999");
		if(bUpdate)
		{
			m_strBase = str;
		}
		return str;
	}

	CString ss;
	int v;
	BOOL bYes;
	C3D CNum;

	const CHistory *pHistory = ((CMy3DApp*)AfxGetApp())->GetHistory();

	for(int i = 0; i < 10; ++i)
	{
		for(int j = 0; j < 10; ++j)
		{
			for(int k = 0; k < 10; ++k)
			{
				CNum = C3D( i * 100 + j * 10 + k );

				bYes = FALSE;
				switch(iIndex)
				{
				case 1: // 半顺
					if( CNum.IsG6() )
					{
						v = (1 == abs(i - j) || 9 == abs(i - j))
							+ (1 == abs(i - k) || 9 == abs(i - k))
							+ (1 == abs(j - k) || 9 == abs(j - k));
						if( 1 == v )
						{
							bYes = TRUE;
						}
					}
					break;
				case 2: // 杂六
					if( CNum.IsG6() )
					{
						v = (1 == abs(i - j) || 9 == abs(i - j))
							+ (1 == abs(i - k) || 9 == abs(i - k))
							+ (1 == abs(j - k) || 9 == abs(j - k));
						if( 0 == v )
						{
							bYes = TRUE;
						}
					}
					break;
				case 3: // 拖拉机
					if( CNum.IsG6())
					{
						int imax = max(i, max(j, k));
						int imin = min(i, min(j, k));
						v = i + j + k - imax - imin;
						if(imax - imin == 2
							|| (imax - imin == 9 && (1 == v || 8 == v) ) )
						{
							bYes = TRUE;
						}
					}
					break;
				case 4: // 组三
					if( CNum.IsG3())
					{
						bYes = TRUE;
					}
					break;
				case 6: // 组六偶和
					if(i != j && i != k && j != k)
					{
						if( !((i + j + k) & 1) )
						{
							bYes = TRUE;
						}
					}
					break;
				case 7: // 组六奇和
					if(i != j && i != k && j != k)
					{
						if( (i + j + k) & 1 )
						{
							bYes = TRUE;
						}
					}
					break;
				case 8: // 正常和
					if(i + j + k >= 9 && i + j + k <= 18)
					{
						bYes = TRUE;
					}
					break;
				case 9: // 大和
					if(i + j + k > 18)
					{
						bYes = TRUE;
					}
					break;
				case 10: // 小和
					if(i + j + k < 9)
					{
						bYes = TRUE;
					}
					break;
				case 11: // 超级冷态
					bYes = !pHistory->IsInside(i * 100 + j * 10 + k);
					break;
				}

				if(bYes)
				{
					str += CNum.ToString() + _T(" ");
				}
			}
		}
	}

	if(bUpdate)
	{
		m_strBase = str;
	}
	
	return str;
}

void CPageUseBase::OnLoadBasefile() 
{
	// TODO: Add your control notification handler code here
	CString strFileName = WND::SelectFile(TRUE);

	if( !strFileName.IsEmpty() )
	{
		m_strBase = TXT::Txt2String(strFileName, _T("\r\n"));
		m_strBase.TrimRight();
		UpdateData(FALSE);
	}
}

BOOL CPageUseBase::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(WM_KEYDOWN == pMsg->message)
	{
		if(VK_ESCAPE == pMsg->wParam/* || VK_RETURN == pMsg->wParam*/)
		{   
			return TRUE;   
		}
		if(VK_RETURN == pMsg->wParam)
		{
			if( pMsg->hwnd != GetDlgItem(IDC_EDIT_BASE)->GetSafeHwnd() )
			{
				return TRUE;
			}
		}
	}	
	
	return CDialog::PreTranslateMessage(pMsg);
}

VOID CPageUseBase::LoadHistory()
{
	m_strBase.Empty();

	const CHistory *pHistory = pApp->GetHistory();

	UINT n = pHistory->GetCount();

	if(n > 0)
	{
		C3D CNum;
		CString str;
		for(UINT i = 0; i < n; ++i)
			m_strBase += pHistory->GetNumStr(i) + _T(" ");
	}
}

void CPageUseBase::OnSetFocusBase() 
{
	// 注册热键
	RegisterHotKey(m_hWnd,1001,MOD_CONTROL,'A');
	RegisterHotKey(m_hWnd,1002,MOD_CONTROL,'a');
	
	// 全选
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_BASE);
	int n = pEdit->GetWindowTextLength();
	pEdit->SetSel(0, n);
	pEdit = NULL;
}

void CPageUseBase::OnKillFocusBase() 
{
	// 注销热键
	UnregisterHotKey(m_hWnd,1001);
	UnregisterHotKey(m_hWnd,1002);
}

LRESULT CPageUseBase::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	if(wParam == 1001 || wParam == 1002)
	{
		::SendMessage(GetDlgItem(IDC_EDIT_BASE)->m_hWnd, EM_SETSEL, 0, -1);
	}
	return 0;
}
