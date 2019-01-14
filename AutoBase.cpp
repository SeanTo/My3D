// AutoBase.cpp : implementation file
//

#include "stdafx.h"
#include "My3D.h"
#include "My3DDlg.h"
#include "AutoBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoBase dialog


CAutoBase::CAutoBase(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoBase::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAutoBase)
	m_iErr1 = 0;
	m_iErr2 = 1;
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	pApp = (CMy3DApp*)AfxGetApp();
	pHistory = pApp->GetHistory();
}

void CAutoBase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAutoBase)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_SPIN1, m_Spin1);
	DDX_Control(pDX, IDC_SPIN2, m_Spin2);
	DDX_Text(pDX, IDC_EDIT_ERR1, m_iErr1);
	DDV_MinMaxInt(pDX, m_iErr1, 0, 99);
	DDX_Text(pDX, IDC_EDIT_ERR2, m_iErr2);
	DDV_MinMaxInt(pDX, m_iErr2, 0, 99);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAutoBase, CDialog)
	//{{AFX_MSG_MAP(CAutoBase)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnLclickList)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, OnRclickList)
	ON_BN_CLICKED(IDC_KILL_EFFECT, OnKillEffect)
	ON_BN_CLICKED(IDC_SEL_ALL, OnSelAll)
	ON_BN_CLICKED(IDC_CLEAR_ALL, OnClearAll)
	ON_BN_CLICKED(IDC_DEFAULT_SEL, OnDefaultSel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoBase message handlers

BOOL CAutoBase::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
// #ifdef _UNRESTRICT2_
// 	GetDlgItem(IDC_KILL_EFFECT)->EnableWindow(TRUE);
// 	GetDlgItem(IDC_KILL_EFFECT)->ShowWindow(SW_SHOW);
// #endif // _UNRESTRICT2_
	
	m_Spin1.SetRange(0, 10);
	m_Spin1.SetPos(pApp->iErr1);
	m_Spin2.SetRange(0, 15);
	m_Spin2.SetPos(pApp->iErr2);

	m_iErr1 = pApp->iErr1;
	m_iErr2 = pApp->iErr2;
	
	m_List.SetExtendedStyle( m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT
		| LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES );
	m_List.SetReadOnlyColumn(-1);
	
	// 列标题
	m_List.InsertColumn(0,"序号",LVCFMT_LEFT,43);    //添加列标题
	m_List.InsertColumn(1,"方法",LVCFMT_LEFT,150);
	m_List.InsertColumn(2,"描述",LVCFMT_LEFT,500);
	
	int iCount = 0;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("动态智能"));
	m_List.SetItemText(iCount, 2, _T("不定期调整，请参考统计数据决定是否使用"));
	bitSelDef[iCount] = true;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("段式法 - 强过滤"));
	m_List.SetItemText(iCount, 2, _T("比较复杂，请参考正确率统计决定是否使用"));
	bitSelDef[iCount] = true;
	++iCount;
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("段式法 - 弱过滤"));
	m_List.SetItemText(iCount, 2, _T("已包含在强过滤中，同时选中会影响容错效果"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("号码不同时继承"));
	m_List.SetItemText(iCount, 2, _T("号码定位与上期相同最多1个"));
	bitSelDef[iCount] = true;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("012 路不全继承"));
	m_List.SetItemText(iCount, 2, _T("012 路定位不与上期完全相同"));
	bitSelDef[iCount] = true;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("形态不同时反转"));
	m_List.SetItemText(iCount, 2, _T("奇偶、大小、质合最多一种形态完全反转，如 [质合质] 变 [合质合]"));
	bitSelDef[iCount] = true;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("常规均值"));
	m_List.SetItemText(iCount, 2, _T("范围: 2-7"));
	bitSelDef[iCount] = true;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("金三角"));
	m_List.SetItemText(iCount, 2, _T("比较复杂，请参考正确率统计决定是否使用"));
	bitSelDef[iCount] = true;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("等长步距法"));
	m_List.SetItemText(iCount, 2, _T("相邻两期号码百十个位有向振幅不相同"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("近期号码相关"));
	m_List.SetItemText(iCount, 2, _T("开奖号、位差、位和"));
	bitSelDef[iCount] = false;
	++iCount;
	
	// 特殊算法
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("任两码跨不4连出"));
	m_List.SetItemText(iCount, 2, _T(""));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("任两码和不3连出"));
	m_List.SetItemText(iCount, 2, _T("10-19 不一定每期杀号"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("任两码积不3连出(0除外)"));
	m_List.SetItemText(iCount, 2, _T("但一旦特定数据出现"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("跨度不连出3期"));
	m_List.SetItemText(iCount, 2, _T("杀号非常有效"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("和尾不连出3期"));
	m_List.SetItemText(iCount, 2, _T("且准确率相当高"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("奇偶形态不连出3期"));
	m_List.SetItemText(iCount, 2, _T("可以选中这10个容错1-2"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("大小形态不连出3期"));
	m_List.SetItemText(iCount, 2, _T("作为一个单独的底"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("质合形态不连出3期"));
	m_List.SetItemText(iCount, 2, _T(""));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("012 路不邻出3期"));
	m_List.SetItemText(iCount, 2, _T(""));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("斜码3不连出2期"));
	m_List.SetItemText(iCount, 2, _T(""));
	bitSelDef[iCount] = false;
	++iCount;
	
	// 杀组选形态
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("杀豹子"));
	m_List.SetItemText(iCount, 2, _T("不参与容错"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("杀组三"));
	m_List.SetItemText(iCount, 2, _T("不参与容错"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("杀组六"));
	m_List.SetItemText(iCount, 2, _T("不参与容错"));
	bitSelDef[iCount] = false;
	++iCount;
	
	LoadSel();

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAutoBase::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
#ifdef _UNRESTRICT2_
	const int iCount = m_List.GetItemCount();
	const int iSel = m_List.GetCurSel();

	if(0 <= iSel && iSel < iCount)
	{
		OnSelAll();
	}
#endif // _UNRESTRICT2_
	
	*pResult = 0;
}

void CAutoBase::OnLclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_List.ReverseCheck(m_List.GetCurSel());
	
	*pResult = 0;
}

void CAutoBase::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_List.SetCheckAll(FALSE);
	m_List.ReverseCheck(m_List.GetCurSel());

	m_iErr1 = 0;
	m_iErr2 = 0;

	UpdateData(FALSE);
	
	*pResult = 0;
}

/*
 *	全选
 */
void CAutoBase::OnSelAll() 
{
	m_List.SetCheckAll();

	m_iErr1 = 0;
	m_iErr2 = 1;

	// 最后三项不选
	int iCount = m_List.GetItemCount();
	for(int i = iCount - 3; i < iCount; ++i)
		m_List.SetCheck(i, FALSE);

	UpdateData(FALSE);
}

/*
 *	全清
 */
void CAutoBase::OnClearAll() 
{
	m_List.SetCheckAll(FALSE);

	m_iErr1 = 0;
	m_iErr2 = 0;

	UpdateData(FALSE);
}

/*
 *	默认
 */
void CAutoBase::OnDefaultSel() 
{
	int iCount = m_List.GetItemCount();

	for(int i = 0; i < iCount; ++i)
		m_List.SetCheck(i, bitSelDef[i] == true);

	m_iErr1 = 0;
	m_iErr2 = 1;
	
	UpdateData(FALSE);
}

/*
 *	加载选择状态
 */
void CAutoBase::LoadSel()
{
	bitset<32> bSel;

	if(pApp->bAutoBaseSel.count() > 0)
		bSel = pApp->bAutoBaseSel;
	else
		bSel = bitSelDef;

	int iCount = m_List.GetItemCount();
	for(int i = 0; i < iCount; ++i)
		m_List.SetCheck(i, bSel[i] == true);

	m_iErr1 = pApp->iErr1;
	m_iErr2 = pApp->iErr2;

	UpdateData(FALSE);
}

/*
 *	保存选择状态
 */
void CAutoBase::SaveSel()
{
	UpdateData(TRUE);
	int iCount = m_List.GetItemCount();

	for(int i = 0; i < iCount; ++i)
	{
		pApp->bAutoBaseSel[i] = m_List.GetCheck(i) ? true : false;
	}

	pApp->iErr1 = m_iErr1;
	pApp->iErr2 = m_iErr2;
}

/*
 *	杀号效果
 */
void CAutoBase::OnKillEffect() 
{
	SaveSel();
	
	CString str(_T(""));
	int cnt, err=0;
	
	for(int i = 0; i < 10; ++i)
	{
		cnt = 0;
		for(int j = 0; j < 1000; ++j)
		{
			cnt += ( 0 != pHistory->FilterAutoBase(j, pApp->bAutoBaseSel, i, pApp->iErr1, pApp->iErr2) );
		}
		str += pHistory->GetPeriodStr(i) + _T(" : ") +  EMFC::Int2Str(cnt, _T("%d\n"));
	}
	str.TrimRight();
	AfxMessageBox(str);
}

void CAutoBase::OnCancel() 
{
	UpdateData(TRUE);
	SaveSel();

	CDialog::OnCancel();
}

void CAutoBase::OnOK() 
{
	// TODO: Add extra cleanup here
	UpdateData(TRUE);
	SaveSel();
	
	// 容错参数检查
	if(m_iErr1 > m_iErr2)
	{
		AfxMessageBox(_T("容错范围设置错误！"));
		return;
	}
	
	CString strBase = _T("");

	for(int i = 0; i < 1000; ++i)
	{
		if( 0 == pHistory->FilterAutoBase(i, pApp->bAutoBaseSel, 0, m_iErr1, m_iErr2) )
		{
			strBase += EMFC::Int2Str(i, _T("%03d "));
		}
	}
	strBase.TrimRight();
	
	((CMy3DDlg*)GetParent())->m_page2.SetBase(strBase);	
		
	CDialog::OnOK();
}
