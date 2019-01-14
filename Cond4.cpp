// Cond4.cpp : implementation file
//

#include "stdafx.h"
#include "Cond4.h"

#include "..\Share\wnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCond4 dialog


CCond4::CCond4(CWnd* pParent /*=NULL*/)
	: CDialog(CCond4::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCond4)
	m_iErr3 = -1;
	m_iErr4 = -1;
	m_bC401 = FALSE;
	m_bC402 = FALSE;
	m_bC403 = FALSE;
	m_bC404 = FALSE;
	m_bC405 = FALSE;
	m_bCNoOrder1 = FALSE;
	m_bCNoOrder2 = FALSE;
	m_strC4101 = _T("");
	m_strC4201 = _T("");
	m_strC4501 = _T("");
	m_strC4502 = _T("");
	m_strC4503 = _T("");
	m_strC4511 = _T("");
	m_strC4512 = _T("");
	m_strC4513 = _T("");
	//}}AFX_DATA_INIT

	pApp = (CMy3DApp*)AfxGetApp();
	UINT nSumCounter1 = 0;
	UINT nSumCounter2 = 0;
}


void CCond4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCond4)
	DDX_Control(pDX, IDC_C4_CMB_ERROR, m_cmbAllowError);	
	DDX_Text(pDX, IDC_C4_ERR3, m_iErr3);
	DDX_Text(pDX, IDC_C4_ERR4, m_iErr4);
	DDX_Check(pDX, IDC_CHECK_C4_1, m_bC401);
	DDX_Check(pDX, IDC_CHECK_C4_2, m_bC402);
	DDX_Check(pDX, IDC_CHECK_C4_3, m_bC403);
	DDX_Check(pDX, IDC_CHECK_C4_4, m_bC404);
	DDX_Check(pDX, IDC_CHECK_C4_5, m_bC405);
	DDX_Check(pDX, IDC_CHECK_NOORDER1, m_bCNoOrder1);
	DDX_Check(pDX, IDC_CHECK_NOORDER2, m_bCNoOrder2);
	DDX_Text(pDX, IDC_EDIT_C41_01, m_strC4101);
	DDX_Text(pDX, IDC_EDIT_C42_01, m_strC4201);
	DDX_Control(pDX, IDC_LIST43, m_List);
	DDX_Control(pDX, IDC_LIST44, m_List4);
	DDX_Text(pDX, IDC_EDIT_C45_01, m_strC4501);
	DDV_MaxChars(pDX, m_strC4501, 10);
	DDX_Text(pDX, IDC_EDIT_C45_02, m_strC4502);
	DDV_MaxChars(pDX, m_strC4502, 10);
	DDX_Text(pDX, IDC_EDIT_C45_03, m_strC4503);
	DDV_MaxChars(pDX, m_strC4503, 10);
	DDX_Text(pDX, IDC_EDIT_C45_11, m_strC4511);
	DDV_MaxChars(pDX, m_strC4511, 10);
	DDX_Text(pDX, IDC_EDIT_C45_12, m_strC4512);
	DDV_MaxChars(pDX, m_strC4512, 10);
	DDX_Text(pDX, IDC_EDIT_C45_13, m_strC4513);
	DDV_MaxChars(pDX, m_strC4513, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCond4, CDialog)
	//{{AFX_MSG_MAP(CCond4)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST43, OnDblclkList)
	ON_NOTIFY(NM_RCLICK, IDC_LIST43, OnRclickList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST44, OnDblclkList4)
	ON_NOTIFY(NM_RCLICK, IDC_LIST44, OnRclickList4)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_CHECK_C4_1, IDC_CHECK_C4_5, OnSelectCond)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCond4 message handlers

BOOL CCond4::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString str;
	for(int i = 0; i < 100; ++i)
	{
		str.Format(_T("%d"), i);
		m_cmbAllowError.AddString(str);
	}
	
	m_List.SetExtendedStyle(m_List.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES );
	
	// 垃圾复式列表头
	m_List.InsertColumn(0, "编号", LVCFMT_LEFT, 35);
	m_List.InsertColumn(1, "百位", LVCFMT_LEFT, 72);
	m_List.InsertColumn(2, "十位", LVCFMT_LEFT, 72);
	m_List.InsertColumn(3, "个位", LVCFMT_CENTER, 72);
	//m_List.InsertColumn(4, "处理", LVCFMT_LEFT, 70);
	
	m_List.SetReadOnlyColumn(0);
	m_List.SetValidCharsColumn(_T("0123456789"), 10);
	
	m_List4.SetExtendedStyle(m_List4.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES );
	
	// 3段断路列表头
	m_List4.InsertColumn(0, "编号", LVCFMT_LEFT, 35);
	m_List4.InsertColumn(1, "1段", LVCFMT_LEFT, 72);
	m_List4.InsertColumn(2, "2段", LVCFMT_LEFT, 72);
	m_List4.InsertColumn(3, "3段", LVCFMT_CENTER, 72);
	//m_List4.InsertColumn(4, "处理", LVCFMT_LEFT, 70);
	
	m_List4.SetReadOnlyColumn(0);//read only
	m_List4.SetValidCharsColumn(_T("0123456789"), 10);
	
	Init();
	
	// 按钮悬浮提示
	EnableToolTips(TRUE);
	m_tt.Create(this);
	m_tt.Activate(TRUE);
	
	m_tt.SetMaxTipWidth(140); //提示文字行宽度，非必需
	m_tt.SetTipTextColor(RGB(255,0,0)); //提示文字颜色，非必需
// 	m_tt.SetDelayTime(100);    //提示显示时间，非必需
	
	m_tt.AddTool(GetDlgItem(IDC_LIST43), "双击百十个：编辑条件；双击第一列：添加条件；右键点击行：删除条件；");
 	m_tt.AddTool(GetDlgItem(IDC_LIST44), "杀分别落在3段中的号码，三段中的号码不要重复。双击三个段：编辑条件；双击第一列：添加条件；右键点击行：删除条件；");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

UINT CCond4::FilterNum(UINT num, UINT nOffse /*= 0*/)
{
	int err = 0;	// 页面错误计数

	C3D CNum(num);
	BOOL bYes;

	TCHAR buf[12];

	// 定两码
	if(m_bC401 && !m_strC4101.IsEmpty())
	{
		bYes = FALSE;
		for(int i = 0; i < arrTwo1.GetSize(); ++i)
		{
			if( CNum.IsMember2(arrTwo1[i], !m_bCNoOrder1) )
			{
				bYes = TRUE;
				break;
			}
		}
		err += !bYes;
	}

	// 杀两码
	if(m_bC402 && !m_strC4201.IsEmpty())
	{
		bYes = FALSE;
		for(int i = 0; i < arrTwo2.GetSize(); ++i)
		{
			if( CNum.IsMember2(arrTwo2[i], !m_bCNoOrder2) )
			{
				bYes = TRUE;
				break;
			}
		}
		err += bYes;
	}
	
	// 垃圾复式
	if(m_bC403)
	{
		int err2 = 0;	// 本级错误计数

		int iLines = m_List.GetItemCount();
		CString str1, str2, str3;

		for(int i = 0; i < iLines && (-1 == m_iErr3 || err2 <= m_iErr3); ++i)
		{
			if( !m_List.GetCheck(i) )
				continue;

			m_List.GetItemText(i, 1, buf, 12);
			str1 = buf;
			if( str1.IsEmpty() )
				continue;

			m_List.GetItemText(i, 2, buf, 12);
			str2 = buf;
			if( str1.IsEmpty() )
				continue;

			m_List.GetItemText(i, 3, buf, 12);
			str3 = buf;
			if( str1.IsEmpty() )
				continue;

			bYes = EMFC::IsInArray(CNum.Hun(), str1)
				&& EMFC::IsInArray(CNum.Ten(), str2)
				&& EMFC::IsInArray(CNum.Ent(), str3);
			
			err2 += bYes;
		}

		if( -1 == m_iErr3)
			err += err2;
		else
			err += err2 > m_iErr3;
	}
	
	// 3 段断路
	if(m_bC404)
	{
		int err2 = 0;	// 本级错误计数
		int n1 = -1, n2 = -1, n3 = -1;
		
		int iLines = m_List4.GetItemCount();
		CString str1, str2, str3;
		
		for(int i = 0; i < iLines && (-1 == m_iErr4 || err2 <= m_iErr4); ++i)
		{
			if( !m_List4.GetCheck(i) )
				continue;
			
			m_List4.GetItemText(i, 1, buf, 12);
			str1 = buf;
			if( str1.IsEmpty() )
				continue;
			
			m_List4.GetItemText(i, 2, buf, 12);
			str2 = buf;
			if( str1.IsEmpty() )
				continue;
			
			m_List4.GetItemText(i, 3, buf, 12);
			str3 = buf;
			if( str1.IsEmpty() )
				continue;

			n1 = FilterNum_4(CNum.Hun(), str1, str2, str3);
			n2 = FilterNum_4(CNum.Ten(), str1, str2, str3);
			n3 = FilterNum_4(CNum.Ent(), str1, str2, str3);
			
			err2 += (3 == n1 + n2 + n3) && !(1 == n1 && 1 == n2 && 1 == n3);
		}
		
		if( -1 == m_iErr4)
			err += err2;
		else
			err += err2 > m_iErr4;
	}
	
	// 定位胆杀
	if(m_bC405)
	{		
		err += !m_strC4501.IsEmpty() && !EMFC::IsInArray(CNum.Hun(), m_strC4501);
		err += !m_strC4502.IsEmpty() && !EMFC::IsInArray(CNum.Ten(), m_strC4502);
		err += !m_strC4503.IsEmpty() && !EMFC::IsInArray(CNum.Ent(), m_strC4503);
			
		err += !m_strC4511.IsEmpty() && EMFC::IsInArray(CNum.Hun(), m_strC4511);
		err += !m_strC4512.IsEmpty() && EMFC::IsInArray(CNum.Ten(), m_strC4512);
		err += !m_strC4513.IsEmpty() && EMFC::IsInArray(CNum.Ent(), m_strC4513);
	}
	
	return err;
}

BOOL CCond4::PreTranslateMessage(MSG* pMsg) 
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

VOID CCond4::Init()
{
	m_bC401 = m_bC402 = m_bC403 = m_bC404 = m_bC405
		= m_bCNoOrder1 = m_bCNoOrder2 = FALSE;
	m_cmbAllowError.SetCurSel(m_cmbAllowError.GetCount() - 1);
	m_iErr3 = -1;
	m_iErr4 = -1;
	
	// 编辑框
	m_strC4101.Empty();
	m_strC4201.Empty();

	m_List.DeleteAllItems();
	AddCond3();
	AddCond3();
	AddCond3();
	AddCond3();
	
	m_List4.DeleteAllItems();
	AddCond4();
	AddCond4();

	m_strC4501.Empty();
	m_strC4502.Empty();
	m_strC4503.Empty();
	m_strC4511.Empty();
	m_strC4512.Empty();
	m_strC4513.Empty();

	EnableCond();
	UpdateData(FALSE);
}

void CCond4::OnSelectCond(UINT nID)
{
	ASSERT(IDC_CHECK_C4_1 <= nID && IDC_CHECK_C4_5 >= nID);

	UpdateData();
	EnableCond();

#ifdef _UNRESTRICT_
	CHistory *pHistory = pApp->GetHistory();
	int iCount = pHistory->GetCount();
	// 按住 CTRL 推荐或清除
	if( WND::IsCtrlDown() )
	{
		switch(nID - IDC_CHECK_C4_1)
		{
		case 0:
			if(!m_bC401)
				m_strC4101.Empty();
			break;
		case 1: // 杀两码:统计中的杀两码
			if(!m_bC402)
				m_strC4201.Empty();
			else if(iCount >= 2 && iCount >= 2)
			{
				CUIntArray arrTwoNums;
				pHistory->Kill2Nums(arrTwoNums);

				m_strC4201 = EMFC::PrintArray(arrTwoNums, -1, 0, -1, _T("%02d,"));
			}
			break;
		case 2: // 垃圾复式: 百十个推荐码
			if(!m_bC403)
			{
				// Init();
				m_List.DeleteAllItems();
			}
			else if(iCount >= pApp->iRecommandPeriod  && iCount >= 31)
			{
				CUIntArray arrAMP[3];
				CString str[3];

				for(int i = 0; i < 3; ++i)
				{
					pHistory->StatAMP(pApp->iRecommandPeriod, arrAMP[i], i);
					str[i] = EMFC::PrintArray(arrAMP[i], pApp->iRecommandNum, 0);
				}
				AddCond3(FALSE, str[0], str[1], str[2]);
			}
			break;
		case 3: // 3段断路
			if(!m_bC404)
			{
				// Init();
				m_List4.DeleteAllItems();
			}
			else
			{
				AddCond4(FALSE, _T("012"), _T("3456"), _T("789"));
				AddCond4(FALSE, _T("0369"), _T("147"), _T("258"));

				if(iCount >= pApp->iHot)
				{
					CString str1, str2, str3;
					pHistory->HotNum(0, str1, str2, str3, pApp->iHot);
					AddCond4(FALSE, str1, str2, str3);
				}
			}
			pApp->iHot = 5;
			break;
		case 4: // 定位杀
			if(!m_bC405)
			{
				m_strC4501.Empty();
				m_strC4502.Empty();
				m_strC4503.Empty();
				m_strC4511.Empty();
				m_strC4512.Empty();
				m_strC4513.Empty();
			}
			else if(iCount >= 21)
			{
				// 间隔10期，分别取百十个的和尾杀百十个
				if(iCount >= 21)
				{
					C3D CNum = pHistory->Kill1NumsPos(0);
					
					m_strC4511 = EMFC::Int2Str(CNum.Hun());
					m_strC4512 = EMFC::Int2Str(CNum.Ten());
					m_strC4513 = EMFC::Int2Str(CNum.Ent());
				}
				
				// 杀推荐码最冷值
				if(iCount >= 30)
				{
					CUIntArray arrAMP;
					int n7 = 0, n8 = 0, n9 = 0;

					for(UINT i = 0; i < 3; ++i)
					{
						pHistory->StatAMP(pApp->iRecommandPeriod, arrAMP, i);

						n7 = n7 * 10 + arrAMP[7];
						n8 = n8 * 10 + arrAMP[8];
						n9 = n9 * 10 + arrAMP[9];
					}
					
					if( WND::IsShiftDown() || WND::IsAltDown() )
					{
						m_strC4511 += EMFC::Int2Str(n9 / 100);
						m_strC4512 += EMFC::Int2Str(n9 / 10 % 10);
						m_strC4513 += EMFC::Int2Str(n9 % 10);
						
						if( WND::IsShiftDown() && WND::IsAltDown() )
						{
							m_strC4511 += EMFC::Int2Str(n8 / 100);
							m_strC4512 += EMFC::Int2Str(n8 / 10 % 10);
							m_strC4513 += EMFC::Int2Str(n8 % 10);
							
							m_strC4511 += EMFC::Int2Str(n7 / 100);
							m_strC4512 += EMFC::Int2Str(n7 / 10 % 10);
							m_strC4513 += EMFC::Int2Str(n7 % 10);
						}
					}
				}
			}
			break;
		default:
			break;
		}
	}
#endif
	
	UpdateData(FALSE);
}

VOID CCond4::EnableCond()
{
	// 定两码、杀两码
	GetDlgItem(IDC_EDIT_C41_01)->EnableWindow(m_bC401);
	GetDlgItem(IDC_CHECK_NOORDER1)->EnableWindow(m_bC401);

	GetDlgItem(IDC_EDIT_C42_01)->EnableWindow(m_bC402);
	GetDlgItem(IDC_CHECK_NOORDER2)->EnableWindow(m_bC402);

	GetDlgItem(IDC_LIST43)->EnableWindow(m_bC403);
	GetDlgItem(IDC_C4_ERR3)->EnableWindow(m_bC403);
	
	GetDlgItem(IDC_LIST44)->EnableWindow(m_bC404);
	GetDlgItem(IDC_C4_ERR4)->EnableWindow(m_bC404);
	
	for(UINT i = 0; i < 3; ++i)
	{
		GetDlgItem(IDC_EDIT_C45_01 + i)->EnableWindow(m_bC405);
		GetDlgItem(IDC_EDIT_C45_11 + i)->EnableWindow(m_bC405);
	}
}

/*
 *	查找给定数字 num, 落在哪一段中字符串中
 */
int CCond4::FilterNum_4(int num, const CString &str1, const CString &str2, const CString &str3)
{
	if( EMFC::IsInArray(num, str1) )
	{
		return 0;
	}
	
	if( EMFC::IsInArray(num, str2) )
	{
		return 1;
	}
	
	if( EMFC::IsInArray(num, str3) )
	{
		return 2;
	}
	
	return -1;
}

VOID CCond4::SaveCondition(CIniFile &fin)
{
	UpdateData(TRUE);
	
	// 条件选择状态
	bitset<7> bitSel;
	bitSel[0] = m_bC401 ? true : false;
	bitSel[1] = m_bC402 ? true : false;
	bitSel[2] = m_bC403 ? true : false;
	bitSel[3] = m_bC404 ? true : false;
	bitSel[4] = m_bC405 ? true : false;
	bitSel[5] = m_bCNoOrder1 ? true : false;
	bitSel[6] = m_bCNoOrder2 ? true : false;
	fin.SetVarStr(_T("定位"), _T("COND"), EMFC::STL2MFC(bitSel.to_string()), 0);

	// 容错值
	int cnt = (m_iErr4+1) * 100000 + (m_iErr3+1) * 1000 + m_cmbAllowError.GetCurSel();
	fin.SetVarInt(_T("定位"), _T("ERR"), cnt, 0);

	// 定杀两码
	fin.SetVarStr(_T("定位"), _T("C101"), m_strC4101, 0);
	fin.SetVarStr(_T("定位"), _T("C201"), m_strC4201, 0);

	TCHAR buf[12];
	CString strName, strValue;

	// 垃圾复式
	cnt = m_List.GetItemCount();
	fin.SetVarInt(_T("定位"), _T("C03"), cnt, 0);

	for(int i = 0; i < cnt; ++i)
	{
		strValue = m_List.GetCheck(i) ? _T("1|") : _T("0|");
		
		strName.Format(_T("C3%02d"), i + 1);
		
		m_List.GetItemText(i, 1, buf, 12);
		strValue = strValue + buf;
		
		m_List.GetItemText(i, 2, buf, 12);
		strValue = strValue + _T("|") + buf;
		
		m_List.GetItemText(i, 3, buf, 12);
		strValue = strValue + _T("|") + buf;
		
		fin.SetVarStr(_T("定位"), strName, strValue, 0);
	}
	
	// 3段断路
	cnt = m_List4.GetItemCount();
	fin.SetVarInt(_T("定位"), _T("C04"), cnt, 0);
	
	for(int i = 0; i < cnt; ++i)
	{
		strValue = m_List4.GetCheck(i) ? _T("1|") : _T("0|");
		
		strName.Format(_T("C4%02d"), i + 1);
		
		m_List4.GetItemText(i, 1, buf, 12);
		strValue = strValue + buf;
		
		m_List4.GetItemText(i, 2, buf, 12);
		strValue = strValue + _T("|") + buf;
		
		m_List4.GetItemText(i, 3, buf, 12);
		strValue = strValue + _T("|") + buf;
		
		fin.SetVarStr(_T("定位"), strName, strValue, 0);
	}

	// 定位胆
	fin.SetVarStr(_T("定位"), _T("C501"), m_strC4501, 0);
	fin.SetVarStr(_T("定位"), _T("C502"), m_strC4502, 0);
	fin.SetVarStr(_T("定位"), _T("C503"), m_strC4503, 0);

	// 定位杀
	fin.SetVarStr(_T("定位"), _T("C504"), m_strC4511, 0);
	fin.SetVarStr(_T("定位"), _T("C505"), m_strC4512, 0);
	fin.SetVarStr(_T("定位"), _T("C506"), m_strC4513, 0);
}

VOID CCond4::LoadCondition(CIniFile &fin)
{
	BOOL bChk;
	int cnt = 0, fnd1 = -1, fnd2 = -1;
	CString str, str1, str2, str3, str4;

	// 条件选择状态
	fin.GetVarStr(_T("定位"), _T("COND"), str);
	bitset<7> bSel(EMFC::MFC2STL(str));

	m_bC401 = bSel[0] ? TRUE : FALSE;
	m_bC402 = bSel[1] ? TRUE : FALSE;
	m_bC403 = bSel[2] ? TRUE : FALSE;
	m_bC404 = bSel[3] ? TRUE : FALSE;
	m_bC405 = bSel[4] ? TRUE : FALSE;
	m_bCNoOrder1 = bSel[5] ? TRUE : FALSE;
	m_bCNoOrder2 = bSel[6] ? TRUE : FALSE;
	
	// 容错值
	fin.GetVarInt(_T("定位"), _T("ERR"), cnt);

	m_iErr4 = (cnt / 100000) - 1;
	cnt %= 100000;

	m_iErr3 = (cnt / 1000) - 1;
	cnt %= 1000;

	if( cnt < 0 || cnt > m_cmbAllowError.GetCount() - 1 )
		cnt = m_cmbAllowError.GetCount() - 1;
	m_cmbAllowError.SetCurSel(cnt);

	//定杀两码
	fin.GetVarStr(_T("定位"), _T("C101"), m_strC4101);
	fin.GetVarStr(_T("定位"), _T("C201"), m_strC4201);

	//垃圾复式
	m_List.DeleteAllItems();
	fin.GetVarInt(_T("定位"), _T("C03"), cnt);

	for(int i = 0; i < cnt; ++i)
	{
		str3.Format(_T("C3%02d"), i + 1);
		fin.GetVarStr(_T("定位"), str3, str);

		bChk = _T('1') == str[0];

		fnd1 = str.Find(_T('|'), 2);
		fnd2 = str.ReverseFind(_T('|'));

		str1 = str.Mid(2, fnd1 - 2);
		str2 = str.Mid(fnd1 + 1, fnd2 - fnd1 - 1);
		str3 = str.Mid(fnd2 + 1);
			
		AddCond3(bChk, str1, str2, str3);
	}

	//3段断路
	m_List4.DeleteAllItems();
	fin.GetVarInt(_T("定位"), _T("C04"), cnt);
	
	for(int i = 0; i < cnt; ++i)
	{
		str3.Format(_T("C4%02d"), i + 1);
		fin.GetVarStr(_T("定位"), str3, str);
		
		bChk = _T('1') == str[0];
		
		fnd1 = str.Find(_T('|'), 2);
		fnd2 = str.ReverseFind(_T('|'));

		str1 = str.Mid(2, fnd1 - 2);
		str2 = str.Mid(fnd1 + 1, fnd2 - fnd1 - 1);
		str3 = str.Mid(fnd2 + 1);
		
		AddCond4(bChk, str1, str2, str3);
	}

	//定位胆杀
	fin.GetVarStr(_T("定位"), _T("C501"), m_strC4501);
	fin.GetVarStr(_T("定位"), _T("C502"), m_strC4502);
	fin.GetVarStr(_T("定位"), _T("C503"), m_strC4503);
	fin.GetVarStr(_T("定位"), _T("C504"), m_strC4511);
	fin.GetVarStr(_T("定位"), _T("C505"), m_strC4512);
	fin.GetVarStr(_T("定位"), _T("C506"), m_strC4513);

	EnableCond();
	UpdateData(FALSE);
}
/*
HBRUSH CCond4::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
// 	if (nCtlColor == CTLCOLOR_STATIC && 
// 		pWnd->GetDlgCtrlID () == IDC_STATIC_C4_TIP)
// 	{
// 		pDC->SetTextColor(RGB(0, 0, 255));
// 		pDC->SetBkMode(TRANSPARENT);
// 	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
*/
BOOL CCond4::IsValid()
{
	return m_bC401 || m_bC402 || m_bC403 || m_bC404 || m_bC405;
}

VOID CCond4::ReadPara()
{
	UpdateData(TRUE);

	if( m_iErr3 > 50)
		m_iErr3 = 50;
	if( m_iErr3 < 0 )
		m_iErr3 = -1;

	if( m_iErr4 > 20)
		m_iErr4 = 20;
	if( m_iErr4 < 0 )
		m_iErr4 = -1;

// 	BOOL bExclude = WND::IsAltDown();

	if(m_bC401)
	{
		C3D::Str2Sum(m_strC4101, arrTwo1, TRUE, 99);
// 		if( bExclude )
// 			C3D::ExcludeTwo(arrTwo1, !m_bCNoOrder1);

		m_strC4101 = EMFC::PrintArray(arrTwo1, -1, 0, -1, _T("%02d,"));
		m_strC4101.TrimRight(_T(','));
	}
	
	if(m_bC402)
	{
		C3D::Str2Sum(m_strC4201, arrTwo2, TRUE, 99);
// 		if( bExclude )
// 			C3D::ExcludeTwo(arrTwo2, !m_bCNoOrder2);

		m_strC4201 = EMFC::PrintArray(arrTwo2, -1, 0, -1, _T("%02d,"));
		m_strC4201.TrimRight(_T(','));
	}

	UpdateData(FALSE);
}

void CCond4::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CPoint point;
	GetCursorPos(&point);
	
	int iRow = -1, iCol = -1;
	
	if( ! m_List.HitTestEx(point, iRow, iCol, TRUE) )
	{
		int cnt = m_List.GetItemCount();
		if(cnt < 50)
			AddCond3(TRUE);
	}
	
	*pResult = 0;
}

void CCond4::OnDblclkList4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CPoint point;
	GetCursorPos(&point);
	
	int iRow = -1, iCol = -1;
	
	if( ! m_List4.HitTestEx(point, iRow, iCol, TRUE) )
	{
		int cnt = m_List4.GetItemCount();
		if(cnt < 30)
			AddCond4(TRUE);
	}
	
	*pResult = 0;
}

void CCond4::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	int iCnt = m_List.GetItemCount();
	int iRow = m_List.GetCurSel();	
	
	if( iRow < iCnt )
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

void CCond4::OnRclickList4(NMHDR* pNMHDR, LRESULT* pResult)
{
	int iCnt = m_List4.GetItemCount();
	int iRow = m_List4.GetCurSel();	
	
	if( iRow < iCnt )
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

		m_List4.DeleteItem(iRow);
		iCnt--;
		
		for(int i = 0; i < iCnt; ++i)
		{
			str.Format(_T("%d"), i + 1);
			m_List4.SetItemText(i, 0, str);
		}
	}
}

int CCond4::AddCond3(BOOL bSel /* = FALSE */, const CString str1 /* = _T */,
					  const CString str2 /* = _T */, const CString str3 /* = _T */)
{
	int cnt = m_List.GetItemCount();
	if( cnt >= 50)
		return -1;

	CString str;
	str.Format(_T("%d"), cnt + 1);
	m_List.InsertItem(cnt, str);
	m_List.SetCheck(cnt, bSel);

	if( !str1.IsEmpty() )
		m_List.SetItemText(cnt, 1, str1);
	if( !str2.IsEmpty() )
		m_List.SetItemText(cnt, 2, str2);
	if( !str3.IsEmpty() )
		m_List.SetItemText(cnt, 3, str3);

	return cnt + 1;
}

int CCond4::AddCond4(BOOL bSel /* = FALSE */, const CString str1 /* = _T */,
					 const CString str2 /* = _T */, const CString str3 /* = _T */)
{
	int cnt = m_List4.GetItemCount();
	if( cnt >= 20)
		return -1;

	CString str;
	str.Format(_T("%d"), cnt + 1);
	m_List4.InsertItem(cnt, str);
	m_List4.SetCheck(cnt, bSel);
	
	if( !str1.IsEmpty() )
		m_List4.SetItemText(cnt, 1, str1);
	if( !str2.IsEmpty() )
		m_List4.SetItemText(cnt, 2, str2);
	if( !str3.IsEmpty() )
		m_List4.SetItemText(cnt, 3, str3);
	
	return cnt + 1;
}

CString CCond4::ExportComment()
{
	static CString NAME[] = {
		_T("定两码"), _T("杀两码"), _T("垃圾复式"), _T("3段断路"), _T("定位胆码"), _T("定位杀码")
	};

	UpdateData(TRUE);

	CString str = _T("");

	if( m_bC401 )	str += NAME[0] + _T("：") + m_strC4101 + _T("\n");
	if( m_bC402 )	str += NAME[1] + _T("：") + m_strC4201 + _T("\n");

	// 垃圾复式
	if( m_bC403 )
	{
		int cnt = m_List.GetItemCount();
		if(cnt > 0)
		{
			str += NAME[2] + _T("：");

			BOOL bFirst = TRUE;
			for(int i=0; i<cnt; ++i)
			{
				if( m_List.GetCheck(i) )
				{
					if(!bFirst)
						str += _T("          ");
					bFirst = FALSE;

					str += m_List.GetItemText(i, 1) + _T("|")
						+ m_List.GetItemText(i, 2) + _T("|")
						+ m_List.GetItemText(i, 3) + _T("\n");
				}
			}
		}
	}
	
	// 3段断路
	if( m_bC404 )
	{
		int cnt = m_List4.GetItemCount();
		if(cnt > 0)
		{
			str += NAME[3] + _T("：");
			
			BOOL bFirst = TRUE;
			for(int i=0; i<cnt; ++i)
			{
				if( m_List4.GetCheck(i) )
				{
					if(!bFirst)
						str += _T("         ");
					bFirst = FALSE;

					str += m_List4.GetItemText(i, 1) + _T("|")
						+ m_List4.GetItemText(i, 2) + _T("|")
						+ m_List4.GetItemText(i, 3) + _T("\n");
				}
			}
		}
	}
	
	// 定位胆杀
	if( m_bC405 )
	{
		if( !m_strC4501.IsEmpty() || !m_strC4502.IsEmpty() || !m_strC4503.IsEmpty() )
		{
			str += NAME[4] + _T("：")
				+ m_strC4501 + _T("|")
				+ m_strC4502 + _T("|")
				+ m_strC4503 + _T("\n");
			str.Replace(_T("||"), _T("| |"));
		}

		if( !m_strC4511.IsEmpty() || !m_strC4512.IsEmpty() || !m_strC4513.IsEmpty() )
		{
			str += NAME[5] + _T("：")
				+ m_strC4511 + _T("|")
				+ m_strC4512 + _T("|")
				+ m_strC4513 + _T("\n");
			str.Replace(_T("||"), _T("| |"));
		}
	}

	return str;
}
