// DataInput.cpp : implementation file
//

#include "stdafx.h"
#include "DataInput.h"

#include "..\Share\wnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataInput dialog


CDataInput::CDataInput(CWnd* pParent /*=NULL*/)
	: CDialog(CDataInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataInput)
	m_strNumber = _T("");
	m_strPeriod = _T("");
	m_strTail = _T("");
	//}}AFX_DATA_INIT
	
	pApp = (CMy3DApp *)AfxGetApp();
	pHistory = pApp->GetHistory();
	pParent = NULL;

	m_strPeriod.Empty();
	m_strNumber.Empty();

	m_bModified = FALSE;
}


void CDataInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataInput)
	DDX_Control(pDX, IDC_LIST_DATABASE, m_listData);
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_strNumber);
	DDV_MaxChars(pDX, m_strNumber, 3);
	DDX_Text(pDX, IDC_EDIT_PERIOD, m_strPeriod);
	DDV_MaxChars(pDX, m_strPeriod, 7);
	DDX_Text(pDX, IDC_EDIT_TAIL, m_strTail);
	DDV_MaxChars(pDX, m_strTail, 2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataInput, CDialog)
	//{{AFX_MSG_MAP(CDataInput)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_EXPORT, OnExport)
	ON_BN_CLICKED(IDC_IMPORT, OnImport)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DATABASE, OnClickListDatabase)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_DATABASE, OnRclickListDatabase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataInput message handlers

BOOL CDataInput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	CString strCaption = _T("历史记录 - ") + CHistory::GetType(Is3D());
	SetWindowText(strCaption);

	m_listData.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listData.SetHeadings(_T("期号, 45;开奖,45; ,18; ,18"), LVCFMT_CENTER );
	m_listData.SetBkColor(RGB(128,128,128));
	m_listData.LoadColumnInfo();
	
	Refresh();

	GetDlgItem(IDC_EDIT_TAIL)->EnableWindow(!Is3D());

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

VOID CDataInput::Refresh()
{
	m_listData.DeleteAllItems();
	
	if( pHistory->IsNull())
		return;
		
	CString str = _T("");
	UINT nTail4, nTail5;
	C3D CNum, CNumNext;

	int iCount = pHistory->GetCount();
	for(int i = 0; i < iCount; ++i)
	{
		if(Is3D())
		{
			m_listData.AddItem(pHistory->GetPeriodStr(i), pHistory->GetNumStr(i), str, str );
		}
		else
		{
			m_listData.AddItem(pHistory->GetPeriodStr(i), pHistory->GetNumStr(i),
				EMFC::Int2Str(pHistory->P5Tail(i) / 10),
				EMFC::Int2Str(pHistory->P5Tail(i) % 10) );
		}

		CNum = pHistory->GetCNum(i);

		// 号码分类颜色标记
		if(CNum.IsG1())
		{
			m_listData.SetItemColor(i, 0, crText, crRed);
			m_listData.SetItemColor(i, 1, crText, crRed);
		}
		else if(CNum.IsG3())
		{
			m_listData.SetItemColor(i, 0, crText, crYellow);
			m_listData.SetItemColor(i, 1, crText, crYellow);
		}
		else if(i & 1 )
		{
			m_listData.SetItemColor(i, 0, crText, crBack);
			m_listData.SetItemColor(i, 1, crText, crBack);
		}

		// 杀尾正误颜色标记
		if( !Is3D() && i > 0)
		{
			CNumNext = pHistory->GetCNum(i - 1);
			nTail4 = pHistory->P5Tail(i);
			nTail5 = nTail4 % 10;
			nTail4 /= 10;

			// 杀第4位重号
			if(CNum.IsMember(nTail4))
			{
				if( !CNumNext.IsMember(nTail4) ) // 杀号正确
				{
					if(CNum.IsG6())
						m_listData.SetItemColor(i, 2, crText2, crGreen);
					else
						m_listData.SetItemColor(i, 2, crText2, crCyan);
				}
				else // 杀号错误
				{
					if(CNum.IsG6())
						m_listData.SetItemColor(i, 2, crText2, crRed);
					else
						m_listData.SetItemColor(i, 2, crText2, crPurple);
				}
			}

			// 杀第5位重号
			if( !CNumNext.IsMember(nTail5) ) // 杀号正确
				m_listData.SetItemColor(i, 3, crText2, crGreen);
			else // 杀号错误
				m_listData.SetItemColor(i, 3, crText2, crRed);
		}
	}

	SetEditer();
	((CMy3DDlg *)GetParent())->SetTitle();
}

void CDataInput::OnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	UINT nPeriod, nNum;

	if( CHistory::CheckPeriod(m_strPeriod)
		&& CHistory::CheckNum( m_strNumber, TRUE ) )
	{
		nPeriod = _ttoi(m_strPeriod);
		nNum = _ttoi(m_strNumber);

		if(!Is3D())
			nNum = nNum * 100 + _ttoi(m_strTail);

		pHistory->AddRecord(nPeriod, nNum);
		Refresh();
		m_bModified = TRUE;
	}

	GetDlgItem(IDC_EDIT_NUMBER)->SetFocus();
}

void CDataInput::OnOK() 
{
	// TODO: Add extra validation here
	CString strTip, strCaption;
	strCaption.LoadString(IDS_TITLE);

// 	if(IDYES == MessageBox(_T("确定要保存吗?"), strCaption, MB_YESNO|MB_ICONQUESTION))
	{
		Save();
	}
}

void CDataInput::OnModify() 
{
	// TODO: Add your control notification handler code here

	int iSel = GetCurSel();

	if( -1 != iSel && iSel < pHistory->GetCount() )
	{

		CString strTip, strCaption;
		strTip.Format(_T("确实要修改记录 %d 吗?"), pHistory->GetPeriod(iSel));
		strCaption.LoadString(IDS_TITLE);

		if(MessageBox(strTip, strCaption, MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			UpdateData();
			if( CHistory::CheckPeriod(m_strPeriod)
				&& CHistory::CheckNum(m_strNumber, TRUE) )
			{
				UINT nPeriod = _ttoi(m_strPeriod);
				UINT nNum = _ttoi(m_strNumber);

				if( !Is3D() )
					nNum = nNum * 100 + _ttoi(m_strTail);
				
				pHistory->ModifyRecord(iSel, nPeriod, nNum);

				Refresh();
				m_bModified = TRUE;
			}
			else
			{
				CString strCaption;
				strCaption.LoadString(IDS_TITLE);
				MessageBox(_T("输入格式错误!"), strCaption, MB_ICONINFORMATION);
			}
		}
	}
	else
	{
		CString strCaption;
		strCaption.LoadString(IDS_TITLE);
		MessageBox(_T("请选择要修改的行。"), strCaption, MB_ICONINFORMATION);
	}
}

void CDataInput::OnDelete()
{
	// TODO: Add your control notification handler code here

	int iSel = GetCurSel();

	if(iSel != -1 && iSel < pHistory->GetCount())
	{
		pHistory->DelRecord(iSel);
		Refresh();
		m_bModified = TRUE;
	}
	else
	{
		CString strCaption;
		strCaption.LoadString(IDS_TITLE);
		MessageBox(_T("请选择要删除的行。"), strCaption, MB_ICONINFORMATION);
	}
}
void CDataInput::OnClickListDatabase(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	int iSel = GetCurSel();
	if(iSel != -1)
		SetEditer(iSel);

	*pResult = 0;
}

void CDataInput::OnRclickListDatabase(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnCancel();

	*pResult = 0;
}

int CDataInput::GetCurSel()
{
	POSITION pos = m_listData.GetFirstSelectedItemPosition();

	if(pos != NULL)
	{
		while(pos)
			return m_listData.GetNextSelectedItem(pos);
	}
	
	return -1;
}

VOID CDataInput::SetEditer(int index /* = -1 */)
{
	if(pHistory->IsNull())
	{
		m_strPeriod.Empty();
		m_strNumber.Empty();
		UpdateData(FALSE);
		
		return;
	}

	m_strTail.Empty();
	if(0 <= index && index < pHistory->GetCount())
	{
		m_strPeriod = pHistory->GetPeriodStr(index);
		m_strNumber = pHistory->GetNumStr(index);

		if( !Is3D() )
			m_strTail = pHistory->P5TailStr(index);
	}
	else
	{
		m_strPeriod = pHistory->GetPeriodStr(-1);
		m_strNumber.Empty();
	}

	UpdateData(FALSE);
}

void CDataInput::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(m_bModified)
	{
		CString strCaption;
		strCaption.LoadString(IDS_TITLE);

		int iSel = MessageBox(_T("历史记录已改变。需要保存修改吗?"), strCaption, MB_YESNOCANCEL);
		if(IDYES == iSel)
			Save();
		else if(IDCANCEL == iSel)
			return;
	}

	CDialog::OnCancel();
}

VOID CDataInput::Save()
{	
	CString sDmbFile = WND::GetAbsPath() + _T("\\") + CHistory::GetDmbFileName(pHistory->Is3D());
	CString sBakFile = WND::GetAbsPath() + _T("\\") + CHistory::GetBakFileName(pHistory->Is3D());
	
	CopyFile(sDmbFile, sBakFile, FALSE);
	pHistory->SaveToFile(sDmbFile);

	m_bModified = FALSE;
}

void CDataInput::OnImport() 
{
	// TODO: Add your control notification handler code here
	CString strFile = WND::GetAbsPath(TRUE) + pHistory->GetDmbFileName(Is3D());
	strFile = strFile.Left(strFile.GetLength()-4) + _T(".txt");
	strFile = WND::SelectFile(TRUE, strFile);

	if( !strFile.IsEmpty() )
	{
		pHistory->LoadFromFile(strFile, Is3D());
		Refresh();
		SetEditer();
	}
}

void CDataInput::OnExport() 
{
	// TODO: Add your control notification handler code here
	CString strFile = WND::GetAbsPath(TRUE) + pHistory->GetDmbFileName(Is3D());
	strFile = strFile.Left(strFile.GetLength()-4) + _T(".txt");
	strFile = WND::SelectFile(FALSE, strFile);
	
	if( !strFile.IsEmpty() )
	{
		pHistory->SaveToFile(strFile);
// 		ShellExecute(NULL, _T("open"), strFile, NULL, NULL, SW_SHOWNORMAL);				
	}
}
