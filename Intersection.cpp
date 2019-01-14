// Intersection.cpp : implementation file
//

//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "My3DDlg.h"
#include "SaveOption.h"
#include "Intersection.h"

// for definition of FNERR_BUFFERTOOSMALL
#include "cderr.h"

#include "..\Share\wnd.h"

//////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIntersection dialog


CIntersection::CIntersection(CWnd* pParent /*=NULL*/)
	: CDialog(CIntersection::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIntersection)
	// NOTE: the ClassWizard will add member initialization here
	m_iErr1 = 0;
	m_iErr2 = 0;
	m_strTip = _T("");
	m_strResult = _T("");
	//}}AFX_DATA_INIT

	pApp = (CMy3DApp*)AfxGetApp();
	arrFiles.RemoveAll();
}


void CIntersection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIntersection)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_SPIN1, m_Spin1);
	DDX_Control(pDX, IDC_SPIN2, m_Spin2);
	DDX_Text(pDX, IDC_EDIT_ERR1, m_iErr1);
	DDV_MinMaxInt(pDX, m_iErr1, 0, 999);
	DDX_Text(pDX, IDC_EDIT_ERR2, m_iErr2);
	DDV_MinMaxInt(pDX, m_iErr2, 0, 999);
	DDX_Text(pDX, IDC_EDIT_INTER_TIP, m_strTip);
	DDX_Text(pDX, IDC_EDIT_INTER_RESULT, m_strResult);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIntersection, CDialog)
	//{{AFX_MSG_MAP(CIntersection)
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnLclickList)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, OnRclickList)
	ON_BN_CLICKED(IDC_SEL_FILE, OnSelFile)
	ON_BN_CLICKED(IDC_CLEAR_ALL, OnClearAll)
	ON_BN_CLICKED(IDC_REVERSE_SEL, OnReverseSel)
	ON_BN_CLICKED(IDC_DEL_FILE, OnDelFile)
	ON_BN_CLICKED(IDC_EDIT_FILE, OnEditFile)
	ON_BN_CLICKED(IDC_RESORT, OnResort)
	ON_BN_CLICKED(IDC_SAVE_RESULT, OnSaveResult)
	ON_BN_CLICKED(IDC_CLEAR_RESULT, OnClearResult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIntersection message handlers

BOOL CIntersection::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Spin1.SetRange(0, MAX_BASES);
	m_Spin1.SetPos(0);
	m_Spin2.SetRange(0, MAX_BASES);
	m_Spin2.SetPos(0);
	
	m_List.SetExtendedStyle( m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT
		| LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES );
	
	m_List.InsertColumn(0,"序号",LVCFMT_LEFT,43);    //添加列标题
	m_List.InsertColumn(1,"注数",LVCFMT_CENTER,43);
	m_List.InsertColumn(2,"文件",LVCFMT_LEFT,600);

	m_strResult = strTip = CString(_T("操作提示:"))
		+ _T("\r\n　　①添加文件(最多999个)")
		+ _T("\r\n　　　用鼠标拖动框选方式")
		+ _T("\r\n　　　或按住CTRL单击左键可以选择多个文件")
		+ _T("\r\n　　②勾选需要参与交集的大底")
		+ _T("\r\n　　③设置容错范围")
		+ _T("\r\n　　④求交集")
		+ _T("\r\n　　⑤保存")
		+ _T("\r\n\r\n　　容错若设为: 0 <= 容错 <= 大底数-1")
		+ _T("\r\n　　求得的是并集结果")
		+ _T("\r\n\r\n文件列表：")
		+ _T("\r\n　　双击 = 查看文件原始内容")
		+ _T("\r\n　　右键 = 查看从文件导出的大底号")
		+ _T("\r\n\r\n大底文件须为.txt文本(记事本格式):")
		+ _T("\r\n　　①文本格式随意，每行注数不要求固定")
		+ _T("\r\n　　②支持任意分隔符(非数字)、或无分隔符")
		+ _T("\r\n　　　分隔符位置任意，不一定要3个数字一组")
		+ _T("\r\n　　③但文件中不能出现除号码以外的半角数字")
		+ _T("\r\n　　　某些软件生成的大底含有广告和说明信息")
		+ _T("\r\n　　　如果其中含半角数字(如日期)须先删除")
		+ _T("\r\n\r\n　　第三方软件生成的大底，请先双击文件列表查看其内容")
		+ _T("是否符合要求，可以通过下面的 [编辑] 按钮打开它修改")
		;
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	      // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CIntersection::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(WM_KEYDOWN == pMsg->message)
	{
		if(VK_ESCAPE == pMsg->wParam || VK_RETURN == pMsg->wParam)
		{ 
			return TRUE; 
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CIntersection::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	OnCancel();
	CDialog::OnRButtonDown(nFlags, point);
}

int CIntersection::GetCurSel()
{
	// 获取列表当前选择序号
	int iSel = -1;
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if(pos != NULL)
	{
		while(pos)
		{
			iSel = m_List.GetNextSelectedItem(pos);
			break;
		}
	}
	
	return iSel;
}

/*
 *	左键单击
 */
void CIntersection::OnLclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	EnEdit();
}

/*
 *	右键列表事件，查看大底号码
 */
void CIntersection::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	int iSel = GetCurSel();
	
	if( -1 != iSel && iSel < arrFiles.GetSize() )
	{
		int iFiles = arrFiles.GetSize();
		int iCount = m_List.GetItemCount();
		
		CUIntArray arrNum;
		
		if(iSel < iFiles)
			GetNumberFromFile(arrFiles[iSel], &arrNum);
		else
			((CMy3DDlg*)GetParent())->m_page2.GetBase(&arrNum);		
		
		int cnt = arrNum.GetSize();
		m_List.SetItemText(iSel, 1, EMFC::Int2Str(cnt));
		
		C3D::Array2Str(arrNum, m_strResult);
	}
	else if( iSel == arrFiles.GetSize() )
	{
		CString str = ((CMy3DDlg*)GetParent())->m_page2.GetBase();
		
		C3D::Str2Array(str, arrBase[MAX_BASES]);
// 		C3D::Str2Array(str, arrBase[MAX_BASES]);
		C3D::Array2Str(arrBase[MAX_BASES], m_strResult );
		
		int cnt = arrBase[MAX_BASES].GetSize();
		m_List.SetItemText(iSel, 1, EMFC::Int2Str(cnt));
	}
	
	EnEdit();
	UpdateData(FALSE);
	
	*pResult = 0;
}

/*
 *	双击列表事件，查看文件内容
 */
void CIntersection::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int iSel = GetCurSel();

	if( -1 != iSel && iSel < arrFiles.GetSize() )
	{
		CStdioFile fin(arrFiles[iSel], CFile::modeRead | CFile::typeText);

		if( fin )
		{
			CString strLine = _T("");
			m_strResult.Empty();
			
			while(fin.ReadString(strLine))
			{
				m_strResult += strLine + _T("\r\n");
			}
			
		}
		else
			m_strResult = _T("打开文件错误!");
	}
	else if( iSel == arrFiles.GetSize() )
	{
		m_strResult = ((CMy3DDlg*)GetParent())->m_page2.GetBase();
	}
	
	EnEdit();
	UpdateData(FALSE);
	
	*pResult = 0;
}

/*
 *	添加文件
 */
void CIntersection::OnSelFile() 
{
	// TODO: Add extra cleanup here
	static CString strLastPath(_T(""));
	strLastPath = WND::SelectMutiFile(arrFiles, strLastPath, _T("文本文件(*.txt)\0*.txt"));

	m_List.DeleteAllItems();
	int iCount = m_List.GetItemCount();
	int iFiles = arrFiles.GetSize();
	
	for(int i = iCount; i < iFiles; ++i)
	{
		m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
		m_List.SetItemText(iCount, 2, arrFiles[i]);
		m_List.SetCheck(iCount);
		++iCount;
	}
	
	if(iFiles > 0)
	{
		m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
		m_List.SetItemText(iCount, 2, _T("内置大底编辑框内容"));
		++iCount;
	}
	
	m_strResult = CString(_T("共有大底文件 ")) + EMFC::Int2Str(iFiles) + _T(" 个");
	
	EnEdit();
	UpdateData(FALSE);
}

/*
 *	全清选择
 */
void CIntersection::OnClearAll() 
{
	int iCount = m_List.GetItemCount();
	
	for(int i = 0; i < iCount; ++i)
		m_List.SetCheck(i, FALSE);

	EnEdit();
	UpdateData(FALSE);
}

/*
 *	反转选择
 */
void CIntersection::OnReverseSel() 
{
	int iCount = m_List.GetItemCount();
	
	for(int i = 0; i < iCount; ++i)
		m_List.SetCheck(i, !m_List.GetCheck(i) );

	EnEdit();
	UpdateData(FALSE);
}

/*
 *	删除未选
 */
void CIntersection::OnDelFile() 
{
	// TODO: Add extra cleanup here
	int iCount = m_List.GetItemCount();
	int iFiles = arrFiles.GetSize();

	if( iFiles + 1 == iCount && (!m_List.GetCheck(iFiles)) )
		m_List.DeleteItem(iFiles);
	
	for(int i = iFiles - 1; i >= 0; --i)
	{
		if( !m_List.GetCheck(i) )
		{
			m_List.DeleteItem(i);
			arrFiles.RemoveAt(i);
			--iCount;
			--iFiles;
		}
	}

	m_strResult = CString(_T("共有大底文件 ")) + EMFC::Int2Str(iFiles) + _T(" 个");

	EnEdit();
	UpdateData(FALSE);
}

/*
 *	重排序号
 */
void CIntersection::OnResort()
{
	int iCount = m_List.GetItemCount();

	for(int i = 0; i < iCount; ++i)
	{
		m_List.SetItemText( i, 0, EMFC::Int2Str(i + 1) );
	}
	
	EnEdit();
	UpdateData(FALSE);
}

/*
 *	编辑文件
 */
void CIntersection::OnEditFile() 
{
	// TODO: Add extra cleanup here
	UpdateData(TRUE);

	int iSel = GetCurSel();

	if( 0 <= iSel && iSel < arrFiles.GetSize() )
	{
		ShellExecute(NULL, _T("open"), arrFiles[iSel], NULL, NULL, SW_SHOWNORMAL);
	}
	UpdateData(FALSE);
}

/*
 *	帮助
 */
void CIntersection::OnClearResult()
{
	m_strTip.Empty();
	m_strResult = strTip;
	
	pApp->aBase.RemoveAll();
	pApp->DispatchNum();
//	pApp->aResult[0].RemoveAll();
//	pApp->aResult[1].RemoveAll();
//	pApp->aResult[2].RemoveAll();

	for(int i = 0; i < MAX_BASES + 1; ++i)
		arrBase[i].RemoveAll();

	EnEdit();
	UpdateData(FALSE);
}

/*
 *	保存结果
 */
void CIntersection::OnSaveResult()
{
	CSaveOption dlg;
	dlg.m_bSaveAndOpen = (pApp->iSaveAndOpen > 0);
	dlg.DoModal();

	EnEdit();
}

/*
 *	关闭
 */
void CIntersection::OnCancel() 
{
	// TODO: Add extra cleanup here
	m_strTip.Empty();
	m_strResult = strTip;
		
	for(int i = 0; i < MAX_BASES + 1; ++i)
		arrBase[i].RemoveAll();
	
	arrFiles.RemoveAll();
	m_List.DeleteAllItems();
	
	CDialog::OnCancel();
}

/*
 *	从文件加载大底
 */
void CIntersection::GetNumberFromFile(const CString &strFile, CUIntArray *arrNum)
{
	arrNum->RemoveAll();

	CStdioFile fin(strFile, CFile::modeRead | CFile::typeText );
	
	if( fin )
	{
		CString strLine = _T("");
		CString strNum = _T("");
		
		while(fin.ReadString(strLine))
		{
			strNum += strLine + _T(" ");
		}

		if(strNum.GetLength() > 0)
			C3D::Str2Array(strNum, *arrNum);
	}
	
	fin.Close();
}

/*
 *	求交集
 */
void CIntersection::OnOK() 
{
	// TODO: Add extra cleanup here
	UpdateData(TRUE);
	OnClearResult();
	
	int err, num;
	
	// 容错参数检查
	if(m_iErr1 > m_iErr2)
	{
		m_strResult = _T("容错参数错误: 下限 > 上限");
		UpdateData(FALSE);
		return;
	}

	int iCount = m_List.GetItemCount();
	int iFiles = arrFiles.GetSize();
	
	// 检查列表文件是否为空
	if( 0 == iFiles )
	{
		m_strResult = _T("大底文件列表为空...");
		UpdateData(FALSE);
		return;
	}

	CUIntArray aMergeBase; // 大底并集
	aMergeBase.RemoveAll();
	int cnt;
	
	// 缓存文件号码
	int iSelected = 0;		// 已勾选的大底数
	for(int i = 0; i < iFiles; ++i)
	{
		if( m_List.GetCheck(i) )
		{
			GetNumberFromFile(arrFiles[i], &arrBase[iSelected]);

			cnt = arrBase[iSelected].GetSize();
			m_List.SetItemText(i, 1, EMFC::Int2Str(cnt));
			
			for(int j = 0; j < cnt; ++j)
			{
				num = arrBase[iSelected][j];

				if( ! EMFC::IsInArray((UINT)num, aMergeBase) )
					aMergeBase.Add(num);
			}
			++iSelected;
		}
	}

	// 处理内置大底
	if(iCount == iFiles + 1 && m_List.GetCheck(iFiles) )
	{
		CString str = ((CMy3DDlg*)GetParent())->m_page2.GetBase();
		C3D::Str2Array(str, arrBase[iSelected]);
		
		cnt = arrBase[iSelected].GetSize();
		m_List.SetItemText(iFiles, 1, EMFC::Int2Str(cnt));

		for(int i = 0; i < cnt; ++i)
			aMergeBase.Add(arrBase[iSelected][i]);
		
		++iSelected;
	}

	// 并集大底排序
	EMFC::SortArray(aMergeBase);
	
	// 是否勾选大底
	if( 0 == iSelected )
	{
		m_strResult = _T("请勾选需要进行交集的大底...");
		UpdateData(FALSE);
		return;
	}

	// 求交集
	pApp->aBase.RemoveAll();
	int iMergeBase = aMergeBase.GetSize();
	for(int i = 0; i < iMergeBase; ++i)
	{
		err = 0;
		num = aMergeBase[i];
		for(int j = 0; j < iSelected; ++j)
		{
			if( ! EMFC::IsInArray((UINT)num, arrBase[j]) )
				++err;
		}

		if( m_iErr1 <= err && err <= m_iErr2 )
			pApp->aBase.Add( num );
	}
	pApp->DispatchNum();

	// 显示提要
	int iResult[3];
	for(int i = 0; i < 3; ++i)
		iResult[i] = pApp->aResult[i].GetSize();

	m_strTip = CString(_T("交集结果: ")) + EMFC::Int2Str(pApp->aBase.GetSize())
		+ _T(" 注(组六") + EMFC::Int2Str(iResult[0])
		+ _T("、组三") + EMFC::Int2Str(iResult[1])
		+ _T("、豹子") + EMFC::Int2Str(iResult[2])	+ _T(")")
		+ _T("\r\n结果已导入醉排三过滤结果列表框中...");


	// 显示结果
	CString str;
	m_strResult.Empty();
	for(int i = 0; i < 3; ++i)
	{
		if(iResult[i] > 0)
		{
			C3D::Array2Str(pApp->aResult[i], str);
			m_strResult += str + _T("\r\n\r\n");
		}
	}
		
	EnEdit();
	
	UpdateData(FALSE);
}

void CIntersection::EnEdit()
{
	int iSel = GetCurSel();
	GetDlgItem(IDC_EDIT_FILE)->EnableWindow(-1 != iSel && iSel < arrFiles.GetSize());
	GetDlgItem(IDC_SAVE_RESULT)->EnableWindow(pApp->aBase.GetSize() > 0);
}
