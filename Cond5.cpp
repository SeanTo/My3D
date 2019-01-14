// Cond5.cpp : implementation file
//

#include "stdafx.h"
#include "Cond5.h"

#include "..\Share\wnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCond5 dialog


CCond5::CCond5(CWnd* pParent /*=NULL*/)
	: CDialog(CCond5::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCond5)
	m_iErr1 = -1;
	m_bC501 = FALSE;
	m_bOnceG3 = FALSE;
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	pApp = (CMy3DApp*)AfxGetApp();
	pHistory = pApp->GetHistory();
}


void CCond5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCond5)
	DDX_Control(pDX, IDC_LIST51, m_List);
	DDX_Text(pDX, IDC_C5_ERR1, m_iErr1);
	DDX_Check(pDX, IDC_C5_CHK_01, m_bC501);
	DDX_Control(pDX, IDC_C5_CMB_ERROR, m_cmbAllowError);
		DDX_Check(pDX, IDC_CHK_ONCE_G3, m_bOnceG3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCond5, CDialog)
	//{{AFX_MSG_MAP(CCond5)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST51, OnDblclkList)
	ON_NOTIFY(NM_RCLICK, IDC_LIST51, OnRclickList)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_C5_CHK_01, OnSelectCond)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// ON_NOTIFY(NM_CLICK, IDC_LIST51, OnLclickList)
// 	ON_MESSAGE(WM_VALIDATE, OnEndLabelEditVariableCriteria)
// 	ON_MESSAGE(WM_SET_ITEMS, PopulateComboList)

/////////////////////////////////////////////////////////////////////////////
// CCond5 message handlers

/*
HBRUSH CCond5::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	if (nCtlColor == CTLCOLOR_STATIC && 
		pWnd->GetDlgCtrlID () == IDC_STATIC_C5_TIP)
	{
		pDC->SetTextColor(RGB(0, 0, 255));
		pDC->SetBkMode(TRANSPARENT);
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
*/

BOOL CCond5::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	m_tt.RelayEvent(pMsg); // 按钮悬浮提示
	
	if(WM_KEYDOWN == pMsg->message)
	{
		if(VK_RETURN == pMsg->wParam || VK_ESCAPE == pMsg->wParam)
		{   
			return TRUE;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}
	
VOID CCond5::Init()
{
	m_bC501 = FALSE;
	m_iErr1 = -1;
	m_cmbAllowError.SetCurSel(m_cmbAllowError.GetCount() - 1);
	m_List.DeleteAllItems();
	
	CString str;
	for(int i = 0; i < 5; i++)
	{
		AddCond();
	}
	
	EnableCond();
	UpdateData(FALSE);
}

VOID CCond5::EnableCond()
{
	GetDlgItem(IDC_LIST51)->EnableWindow(m_bC501);
	GetDlgItem(IDC_C5_ERR1)->EnableWindow(m_bC501);
}

BOOL CCond5::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString str;

	for(int i = 0; i <= 100; ++i)
	{
		str.Format(_T("%d"), i);
		m_cmbAllowError.AddString(str);
	}
	
	m_List.SetExtendedStyle(m_List.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES );

	// 列表头
	m_List.InsertColumn(0, "编号", LVCFMT_LEFT, 40);
	m_List.InsertColumn(1, "条件(双击输入)", LVCFMT_LEFT, 100);
	m_List.InsertColumn(2, "=", LVCFMT_CENTER, 40);
	m_List.InsertColumn(3, "出号", LVCFMT_LEFT, 40);
	
	// 只读列
	m_List.SetReadOnlyColumn(0);
	m_List.SetReadOnlyColumn(2);

	// 输入范围限定
	m_List.SetValidCharsColumn(_T("0123456789"), 10, 1);
	m_List.SetValidCharsColumn(_T("0123"), 4, 3);

	Init();
	
	// 按钮悬浮提示
	EnableToolTips(TRUE);
	m_tt.Create(this);
	m_tt.Activate(TRUE);
	
	m_tt.SetMaxTipWidth(160); //提示文字行宽度，非必需
	m_tt.SetTipTextColor(RGB(255,0,0)); //提示文字颜色，非必需
// 	m_tt.SetDelayTime(100);    //提示显示时间，非必需
	
	m_tt.AddTool(GetDlgItem(IDC_CHK_ONCE_G3), "如条件：2=013，过滤号码225。选中则重号2计1次，匹配；不选计2次，不匹配。");
 	m_tt.AddTool(GetDlgItem(IDC_LIST51),      "双击“条件/出号”：编辑条件；双击其它或空行：添加条件；右键点击条件行：删除条件；支持TAB及SHIFT/CTRL组合键");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

VOID CCond5::OnSelectCond()
{
	UpdateData(TRUE);
	EnableCond();

/*
#ifdef _ONLY_TEST_
	if( WND::IsCtrlDown() )
	{
		CUIntArray a1;
		pHistory->GetNearCourage(10, a1);
		
		for( int i = 0; i < 30; ++i )
		{
			m_iErr1 = 5;
			AddCond( i < 10, EMFC::Int2Str(a1[i], _T("%03d")), _T("123") );
		}
	}
	UpdateData(FALSE);
	return;
#endif
*/

#ifdef _UNRESTRICT_
	// 按住CTRL时推荐
	if(WND::IsCtrlDown())
	{
		if(!m_bC501)
		{
			// Init();
			m_List.DeleteAllItems();
		}
		else
		{
			if( !pHistory->IsNull() )
			{
				CString str = _T("");
				
				if( ! WND::IsShiftDown() )
				{
					// 期尾 5码杀法
 					int cnt = (pHistory->GetPeriod(0) + 1) % 10;
 					str = pHistory->PeriodTail5Courage( cnt );
					AddCond(FALSE, str, _T("12"));

// 					CUIntArray a1;
// 					pHistory->GetNearCourage(10, a1);
// 					
// 					for( int i = 0; i < 30; ++i )
// 					{
// 						m_iErr1 = 15;
// 						AddCond( TRUE, EMFC::Int2Str(a1[i], _T("%03d")), _T("123") );
// 					}
				}
				else
				{
					CStringArray arrTriangle;

					// 升序三角形算胆法
					pHistory->TriangleCourage(arrTriangle);
					for(int i = 0; i < 3; ++i)
						AddCond(FALSE, arrTriangle[i], _T("012"));

					// 降序三角形算胆法
					pHistory->TriangleCourage(arrTriangle, 0, FALSE);
					for(int i = 0; i < 3; ++i)
						AddCond(FALSE, arrTriangle[i], _T("012"));
				}
			}
		}
	}
#endif
	UpdateData(FALSE);
}

VOID CCond5::SaveCondition(CIniFile &fin)
{
	UpdateData(TRUE);

	// 容错
	int iCnt = m_bC501 * 1000000 + (m_iErr1+1) * 1000 + m_cmbAllowError.GetCurSel();
	fin.SetVarInt(_T("范围"), _T("ERR"), iCnt, 0);
	
	// 范围行数
	iCnt = m_List.GetItemCount();
	fin.SetVarInt(_T("范围"), _T("C01"), iCnt, 0);

	TCHAR buf[12];
	CString strName, strValue;

	// 条件
	for(int i = 0; i < iCnt; ++i)
	{
		strValue = m_List.GetCheck(i) ? _T("1|") : _T("0|");

		strName.Format(_T("C1%03d"), i + 1);

		m_List.GetItemText(i, 1, buf, 12);
		strValue = strValue + buf;
		
		m_List.GetItemText(i, 3, buf, 5);
		strValue = strValue + _T("|") + buf;

		fin.SetVarStr(_T("范围"), strName, strValue, 0);
	}
}

VOID CCond5::LoadCondition(CIniFile &fin)
{
	int lines = 0;
	fin.GetVarInt(_T("范围"), _T("ERR"), lines);

	// 容错
	m_bC501 = lines >= 1000000;
	m_iErr1 = (lines % 1000000 / 1000) - 1;
	if(m_iErr1 < 0 )
		m_iErr1 = -1;
	if(m_iErr1 > 100 )
		m_iErr1 = 100;
	
	lines %= 1000;
	if( 0 <= lines && lines <= m_cmbAllowError.GetCount() - 1 )
		m_cmbAllowError.SetCurSel(lines);
	else
		m_cmbAllowError.SetCurSel(m_cmbAllowError.GetCount() - 1);

	m_List.DeleteAllItems();
	lines = 0;

	CString strName, strValue, str;
	int n;

	// 读条件数
 	fin.GetVarInt(_T("范围"), _T("C01"), lines);

	for(int i = 0; i < lines; ++i)
	{
		str.Format(_T("%d"), i + 1);
		m_List.InsertItem(i, str);

		strName.Format(_T("C1%03d"), i + 1);
		strValue.Empty();
		fin.GetVarStr(_T("范围"), strName, strValue);

		m_List.SetCheck(i, _T('1') == strValue.GetAt(0));
		
		n = strValue.Find(_T('|'), 2);
		str = strValue.Mid(2, n-2);
		strValue = strValue.Mid(n+1);

		m_List.SetItemText(i, 1, str);
		m_List.SetItemText(i, 2, _T("="));
		m_List.SetItemText(i, 3, strValue);
	}
	
	EnableCond();
	UpdateData(FALSE);
}

UINT CCond5::FilterNum(const C3D &CNum, UINT nOffse /*= 0*/)
{
	if( !m_bC501)
		return 0;
	
	TCHAR buf[12];
	CString str, str2;

	int err2 = 0;	//本级容错计数
	int iLines = m_List.GetItemCount();

	for(int i = 0; i < iLines && (-1 == m_iErr1 || err2 <= m_iErr1); ++i)
	{
		if( !m_List.GetCheck(i) )
			continue;

		m_List.GetItemText(i, 1, buf, 12);
		str = buf;
		if( str.IsEmpty() )
			continue;
		
		m_List.GetItemText(i, 3, buf, 5);
		str2 = buf;
		if( str2.IsEmpty() )
			continue;

		err2 += ! EMFC::IsInArray(CNum.CountInStr(str, m_bOnceG3), str2);
	}

	if( -1 == m_iErr1)
		return err2;
	else
		return err2 > m_iErr1;
}

BOOL CCond5::IsValid()
{
	return m_bC501;
}

VOID CCond5::ReadPara()
{
	UpdateData(TRUE);

	if(m_iErr1 > 100 )
	{
		m_iErr1 = 100;
		UpdateData(FALSE);
	}
	if(m_iErr1 < 0)
	{
		m_iErr1 = -1;
		UpdateData(FALSE);
	}
	
	asRange.RemoveAll();
	aiRange.RemoveAll();
	UpdateData(FALSE);
}
/*
void CCond5::OnLclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
}
*/
void CCond5::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CPoint point;
	GetCursorPos(&point);
	
	int iRow = -1, iCol = -1;
	
	if( ! m_List.HitTestEx(point, iRow, iCol, TRUE) )
	{
		int cnt = m_List.GetItemCount();
		if(cnt < 100)
			AddCond(TRUE);
	}

	*pResult = 0;
}

void CCond5::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	int iCnt = m_List.GetItemCount();
	int iRow = m_List.GetCurSel();	

 	if( iRow >= 0 && iRow < iCnt )
	{
		CString str;
		
		if( pApp->iDeleteTip > 0 )
		{
			str.Format(_T(" %d "), iRow + 1);
			str = CString(_T("确实要删除第")) + str + _T("行条件吗？")
				+ _T("\n\n如需禁止此提示，可编辑 My3D.ini，\n修改：确认删除=0");
			
			if( IDNO == AfxMessageBox(str, MB_YESNO) )
				return;
		}

		m_List.DeleteItem(iRow);
		iCnt--;

		for(int i = 0; i < iCnt; ++i)
		{
			str.Format(_T("%d"), i + 1);
			m_List.SetItemText(i, 0, str);
		}
	}

	*pResult = 0;
}

int CCond5::AddCond(BOOL bSel /*= FALSE*/, const CString strCond /* = _T */, const CString strRange/* = _T("")*/)
{
	int cnt = m_List.GetItemCount();
	if(cnt >= 100)
		return -1;

	CString str;
	str.Format(_T("%d"), cnt + 1);

	m_List.InsertItem(cnt, str);
	m_List.SetCheck(cnt, bSel);

	m_List.SetItemText(cnt, 2, _T("="));

	if( !strCond.IsEmpty() )
		m_List.SetItemText(cnt, 1, strCond);

	if( !strRange.IsEmpty() )
		m_List.SetItemText(cnt, 3, strRange);

	return cnt+1;
}

CString CCond5::ExportComment()
{
	static CString NAME = _T("号码范围");

	CString str = _T("");

	if( m_bC501 )
	{
		int cnt = m_List.GetItemCount();
		if(cnt > 0)
		{
			str += NAME + _T("：");
			
			BOOL bFirst = TRUE;
			for(int i=0; i<cnt; ++i)
			{
				if( m_List.GetCheck(i) )
				{
					if(!bFirst)
						str += _T("          ");
					bFirst = FALSE;
					
					str += m_List.GetItemText(i, 1)
						+ m_List.GetItemText(i, 2)
						+ m_List.GetItemText(i, 3) + _T("\n");
				}
			}
		}
	}
	return str;
}
