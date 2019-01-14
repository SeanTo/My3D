// Cond1.cpp : implementation file
//

#include "stdafx.h"
#include "Cond1.h"

#include "My3D.h"
#include "DataChart.h"

#include "..\Share\wnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCond1 dialog


CCond1::CCond1(CWnd* pParent /*=NULL*/)
	: CDialog(CCond1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCond1)
	m_strC101 = _T("");
	m_strC102 = _T("");
	m_strC103 = _T("");
	m_strC104 = _T("");
	m_strC105 = _T("");
	m_strC106 = _T("");
	m_strC107 = _T("");
	m_strC108 = _T("");
	m_strC109 = _T("");
	m_strC110 = _T("");
	m_strC111 = _T("");
	m_strC112 = _T("");
	m_strC113 = _T("");
	m_strC114 = _T("");
	m_strC115 = _T("");
	m_bC101 = FALSE;
	m_bC102 = FALSE;
	m_bC103 = FALSE;
	m_bC104 = FALSE;
	m_bC105 = FALSE;
	m_bC106 = FALSE;
	m_bC107 = FALSE;
	m_bC108 = FALSE;
	m_bC109 = FALSE;
	m_bC110 = FALSE;
	m_bC111 = FALSE;
	m_bC112 = FALSE;
	m_bC113 = FALSE;
	m_bC114 = FALSE;
	m_bC115 = FALSE;
	m_iC201 = 1;
	m_iC202 = 1;
	m_iC203 = 1;
	m_iC204 = 1;
	m_iC205 = 1;
	m_iC206 = 1;
	m_iC207 = 1;
	m_iC208 = 1;
	m_iC209 = 1;
	m_iC210 = 1;
	m_iC211 = 1;
	m_iC212 = 1;
	m_iC213 = 1;
	m_iC214 = 1;
	m_iC215 = 1;
	//}}AFX_DATA_INIT

	pApp = (CMy3DApp*)AfxGetApp();
	pHistory = pApp->GetHistory();

	bitCond.reset();

	aSTR_COND[0] = 	&m_strC101;
	aSTR_COND[1] = 	&m_strC102;
	aSTR_COND[2] = 	&m_strC103;
	aSTR_COND[3] = 	&m_strC104;
	aSTR_COND[4] = 	&m_strC105;
	aSTR_COND[5] = 	&m_strC106;
	aSTR_COND[6] = 	&m_strC107;
	aSTR_COND[7] = 	&m_strC108;
	aSTR_COND[8] = 	&m_strC109;
	aSTR_COND[9] = 	&m_strC110;
	aSTR_COND[10] = &m_strC111;
	aSTR_COND[11] = &m_strC112;
	aSTR_COND[12] = &m_strC113;
	aSTR_COND[13] = &m_strC114;
	aSTR_COND[14] = &m_strC115;
}


void CCond1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCond1)
	DDX_Text(pDX, IDC_EDIT_C101, m_strC101);
	DDV_MaxChars(pDX, m_strC101, 4);
	DDX_Text(pDX, IDC_EDIT_C102, m_strC102);
	DDV_MaxChars(pDX, m_strC102, 4);
	DDX_Text(pDX, IDC_EDIT_C103, m_strC103);
	DDV_MaxChars(pDX, m_strC103, 4);
	DDX_Text(pDX, IDC_EDIT_C104, m_strC104);
	DDV_MaxChars(pDX, m_strC104, 4);
	DDX_Text(pDX, IDC_EDIT_C105, m_strC105);
	DDV_MaxChars(pDX, m_strC105, 4);
	DDX_Text(pDX, IDC_EDIT_C106, m_strC106);
	DDV_MaxChars(pDX, m_strC106, 4);
	DDX_Text(pDX, IDC_EDIT_C107, m_strC107);
	DDV_MaxChars(pDX, m_strC107, 4);
	DDX_Text(pDX, IDC_EDIT_C108, m_strC108);
	DDV_MaxChars(pDX, m_strC108, 4);
	DDX_Text(pDX, IDC_EDIT_C109, m_strC109);
	DDV_MaxChars(pDX, m_strC109, 4);
	DDX_Text(pDX, IDC_EDIT_C110, m_strC110);
	DDV_MaxChars(pDX, m_strC110, 4);
	DDX_Text(pDX, IDC_EDIT_C111, m_strC111);
	DDV_MaxChars(pDX, m_strC111, 4);
	DDX_Text(pDX, IDC_EDIT_C112, m_strC112);
	DDV_MaxChars(pDX, m_strC112, 10);
	DDX_Text(pDX, IDC_EDIT_C113, m_strC113);
	DDV_MaxChars(pDX, m_strC113, 10);
	DDX_Text(pDX, IDC_EDIT_C114, m_strC114);
	DDV_MaxChars(pDX, m_strC114, 100);
	DDX_Text(pDX, IDC_EDIT_C115, m_strC115);
	DDV_MaxChars(pDX, m_strC115, 10);
	DDX_Check(pDX, IDC_CHECK_C101, m_bC101);
	DDX_Check(pDX, IDC_CHECK_C102, m_bC102);
	DDX_Check(pDX, IDC_CHECK_C103, m_bC103);
	DDX_Check(pDX, IDC_CHECK_C104, m_bC104);
	DDX_Check(pDX, IDC_CHECK_C105, m_bC105);
	DDX_Check(pDX, IDC_CHECK_C106, m_bC106);
	DDX_Check(pDX, IDC_CHECK_C107, m_bC107);
	DDX_Check(pDX, IDC_CHECK_C108, m_bC108);
	DDX_Check(pDX, IDC_CHECK_C109, m_bC109);
	DDX_Check(pDX, IDC_CHECK_C110, m_bC110);
	DDX_Check(pDX, IDC_CHECK_C111, m_bC111);
	DDX_Check(pDX, IDC_CHECK_C112, m_bC112);
	DDX_Check(pDX, IDC_CHECK_C113, m_bC113);
	DDX_Check(pDX, IDC_CHECK_C114, m_bC114);
	DDX_Check(pDX, IDC_CHECK_C115, m_bC115);
	DDX_Radio(pDX, IDC_C1_RAD_011, m_iC201);
	DDX_Radio(pDX, IDC_C1_RAD_021, m_iC202);
	DDX_Radio(pDX, IDC_C1_RAD_031, m_iC203);
	DDX_Radio(pDX, IDC_C1_RAD_041, m_iC204);
	DDX_Radio(pDX, IDC_C1_RAD_051, m_iC205);
	DDX_Radio(pDX, IDC_C1_RAD_061, m_iC206);
	DDX_Radio(pDX, IDC_C1_RAD_071, m_iC207);
	DDX_Radio(pDX, IDC_C1_RAD_081, m_iC208);
	DDX_Radio(pDX, IDC_C1_RAD_091, m_iC209);
	DDX_Radio(pDX, IDC_C1_RAD_101, m_iC210);
	DDX_Radio(pDX, IDC_C1_RAD_111, m_iC211);
	DDX_Radio(pDX, IDC_C1_RAD_121, m_iC212);
	DDX_Radio(pDX, IDC_C1_RAD_131, m_iC213);
	DDX_Radio(pDX, IDC_C1_RAD_141, m_iC214);
	DDX_Radio(pDX, IDC_C1_RAD_151, m_iC215);
	DDX_Control(pDX, IDC_C1_CMB_ERROR, m_cmbAllowError);	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCond1, CDialog)
	//{{AFX_MSG_MAP(CCond1)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_CHECK_C101, IDC_CHECK_C115, OnSelectCond)
	ON_COMMAND_RANGE(IDC_BUTTON_C101, IDC_BUTTON_C115, OnBtnReference)
	ON_COMMAND_RANGE(IDC_CHECK_C101, IDC_CHECK_C115, OnSelectCond)
	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCond1 message handlers

BOOL CCond1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString str;
	for(int i = 0; i <= 15; ++i)
	{
		str.Format(_T("%d"), i);
		m_cmbAllowError.AddString(str);
	}
	
	Init();
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

VOID CCond1::OnSelectCond(UINT nID)
{
	ASSERT(IDC_CHECK_C101 <= nID && IDC_CHECK_C115 >= nID);

	UpdateData(TRUE);
	SaveCondition();

	UINT n = nID - IDC_CHECK_C101;

	// 奇偶互斥
	if(0 == n && bitCond[0])
	{
		bitCond.reset(1);
	}
	if(1 == n && bitCond[1])
	{
		bitCond.reset(0);
	}

	// 大小互斥
	if(2 == n && bitCond[2])
	{
		bitCond.reset(3);
	}
	if(3 == n && bitCond[3])
	{
		bitCond.reset(2);
	}

	// 斜码单全互斥(三个斜码条件不能同时选择)
	if(7 == n && bitCond[7])
	{
		bitCond.reset(8);
		bitCond.reset(9);
	}
	if(8 == n || 9 == n)
	{
		if(bitCond[8] && bitCond[9])
		{
			bitCond.reset(7);
		}
	}

	LoadCondition();
	EnableCond();

#ifdef _UNRESTRICT_

	BOOL bCtrl	= WND::IsCtrlDown();
	BOOL bShift	= WND::IsShiftDown();
	BOOL bAlt	= WND::IsAltDown();

	// 按住CTRL选择条件时，推荐或清除
	if(bCtrl)
	{
		if( !pHistory->IsNull() )
		{
			C3D CNum = pHistory->GetCNum(0);
			
			switch(n)
			{
			case 0:
				if(!m_bC101)
					m_strC101.Empty();
				break;
			case 1:
				if(!m_bC102)
					m_strC102.Empty();
				break;
			case 2:
				if(!m_bC103)
					m_strC103.Empty();
				break;
			case 3:
				if(!m_bC104)
					m_strC104.Empty();
				break;
			case 4:
				if(!m_bC105)
					m_strC105.Empty();
				break;
			case 5: // 新码数
				if(!m_bC106)
					m_strC106.Empty();
				else
					m_strC106 = _T("0");
				break;
			case 6:
				if(!m_bC107)
					m_strC107.Empty();
				break;
			case 7:
				if(!m_bC108)
					m_strC108.Empty();
				break;
			case 8:
				if(!m_bC109)
					m_strC109.Empty();
				break;
			case 9:
				if(!m_bC110)
					m_strC110.Empty();
				break;
			case 10: // 连号数
				if(!m_bC111)
					m_strC111.Empty();
				else
					m_strC111 = _T("2");
			case 11: // 平均值
				if(!m_bC112)
					m_strC112.Empty();
				else
				{
					m_strC112 = _T("34567");
					m_iC212 = 0;
				}
				break;
			case 12: // 跨度
				if(!m_bC113)
					m_strC113.Empty();
				else
				{
					if(bShift)
						m_strC113 += EMFC::Int2Str( CNum.Tail() );
					else
						m_strC113 += EMFC::Int2Str( CNum.Ent() );
				}
				break;
			case 13: // 和值
				if(!m_bC114)
					m_strC114.Empty();
				else
					m_strC114 = EMFC::Int2Str( CNum.Sum() );
				break;
			case 14: // 和尾
				if(m_bC115)
				{
					if(bShift)
						m_strC115 += EMFC::Int2Str( CNum.Hun() );
					else
						m_strC115 += EMFC::Int2Str( CNum.Span() );
				}
				else
					m_strC115.Empty();
				break;
			default:
				break;
			}
		}
	}
#endif
	UpdateData(FALSE);
}

UINT CCond1::FilterNum(UINT num, int iOffset /*= 0*/)
{
	C3D  CNumLast;	// 最近一期开奖号码
	BOOL IsNotNull;	// 历史非空
	if(IsNotNull = pHistory->GetCount() > iOffset)
		CNumLast = pHistory->GetCNum(iOffset);
	
	UINT err = 0;
	int cnt;
	C3D CNum(num);
	
	// 奇码数
	if(m_bC101 && !m_strC101.IsEmpty() )
	{
		cnt = CNum.OddCnt();
		err += EMFC::IsInArray(cnt, m_strC101) == (m_iC201 == 1);
	}

	// 偶码
	if(m_bC102 && !m_strC102.IsEmpty() )
	{
		cnt = CNum.EvenCnt();
		err += EMFC::IsInArray(cnt, m_strC102) == (m_iC202 == 1);
	}
	
	// 小码
	if(m_bC103 && !m_strC103.IsEmpty() )
	{
		cnt = CNum.SmallCnt();
		err += EMFC::IsInArray(cnt, m_strC103) == (m_iC203 == 1);
	}
	
	// 大码
	if(m_bC104 && !m_strC104.IsEmpty() )
	{
		cnt = CNum.LargeCnt();
		err += EMFC::IsInArray(cnt, m_strC104) == (m_iC204 == 1);
	}
	
	// 质号
	if(m_bC105 && !m_strC105.IsEmpty() )
	{
		cnt = CNum.PrimeCnt();
		err += EMFC::IsInArray(cnt, m_strC105) == (m_iC205 == 1);
	}
	
	// 新码
	if(m_bC106 && !m_strC106.IsEmpty() && IsNotNull)
	{
		cnt = CNumLast.CountNew(CNum);
		err += EMFC::IsInArray(cnt, m_strC106) == (m_iC206 == 1);
	}
	
	// 孤码
	if(m_bC107 && !m_strC107.IsEmpty() && IsNotNull)
	{
		cnt = CNumLast.CountAlone(CNum);
		err += EMFC::IsInArray(cnt, m_strC107) == (m_iC207 == 1);
	}
	
	// 斜码
	if(m_bC108 && !m_strC108.IsEmpty() && IsNotNull)
	{
		cnt = CNumLast.CountLeft(CNum) + CNumLast.CountRight(CNum);
		err += EMFC::IsInArray(cnt, m_strC108) == (m_iC208 == 1);
	}
	
	// 左斜
	if(m_bC109 && !m_strC109.IsEmpty() && IsNotNull)
	{
		cnt = CNumLast.CountLeft(CNum);
		err += EMFC::IsInArray(cnt, m_strC109) == (m_iC209 == 1);
	}
	
	// 右斜
	if(m_bC110 && !m_strC110.IsEmpty() && IsNotNull)
	{
		cnt = CNumLast.CountRight(CNum);
		err += EMFC::IsInArray(cnt, m_strC110) == (m_iC210 == 1);
	}
	
	// 连号
	if(m_bC111 && !m_strC111.IsEmpty())
	{
		cnt = CNum.ContinueCnt();
		err += EMFC::IsInArray(cnt, m_strC111) == (m_iC211 == 1);
	}
	
	// 均值
	if(m_bC112 && !m_strC112.IsEmpty())
	{
		cnt = CNum.Ave();
		err += EMFC::IsInArray(cnt, m_strC112) == (m_iC212 == 1);
	}
	
	// 跨度
	if(m_bC113 && !m_strC113.IsEmpty())
	{
		cnt = CNum.Span();
		err += EMFC::IsInArray(cnt, m_strC113) == (m_iC213 == 1);
	}
	
	// 和值
	if(m_bC114 && arrSum.GetSize() > 0)
	{
		cnt = CNum.Sum();
		err += EMFC::IsInArray((UINT)cnt, arrSum) == (m_iC214 == 1);
	}
	
	// 和尾
	if(m_bC115 && !m_strC115.IsEmpty() )
	{
		cnt = CNum.Tail();
		err += EMFC::IsInArray(cnt, m_strC115) == (m_iC215 == 1);
	}
	
	return err;
}

VOID CCond1::Init()
{
	for(int i=0; i<15; ++i)
		aSTR_COND[i]->Empty();

// 	m_strC101.Empty();
// 	m_strC102.Empty();
// 	m_strC103.Empty();
// 	m_strC104.Empty();
// 	m_strC105.Empty();
// 	m_strC106.Empty();
// 	m_strC107.Empty();
// 	m_strC108.Empty();
// 	m_strC109.Empty();
// 	m_strC110.Empty();
// 	m_strC111.Empty();
// 	m_strC112.Empty();
// 	m_strC113.Empty();
// 	m_strC114.Empty();
// 	m_strC115.Empty();
// 	m_iC201 = 1;
// 	m_iC202 = 1;
// 	m_iC203 = 1;
// 	m_iC204 = 1;
// 	m_iC205 = 1;
// 	m_iC206 = 1;
// 	m_iC207 = 1;
// 	m_iC208 = 1;
// 	m_iC209 = 1;
// 	m_iC210 = 1;
// 	m_iC211 = 1;
// 	m_iC212 = 1;
// 	m_iC213 = 1;
// 	m_iC214 = 1;
// 	m_iC215 = 1;
	
	bitCond.reset();
	
	for(int i=15; i<30; ++i)
		bitCond[i] = 1;
	
	LoadCondition();
	EnableCond();
	
	m_cmbAllowError.SetCurSel(m_cmbAllowError.GetCount() - 1);
	UpdateData(FALSE);
}

VOID CCond1::OnBtnReference(UINT nID)
{
	ASSERT(IDC_BUTTON_C101 <= nID && IDC_BUTTON_C115 >= nID);

	int iSel = nID - IDC_BUTTON_C101;
	CDataChart dlg;
	dlg.SetType(iSel != 14 ? iSel : iSel + 10 - 1);
	dlg.DoModal();
}

VOID CCond1::SaveCondition(CIniFile& fin)
{
	UpdateData(TRUE);
	SaveCondition();
	
	fin.SetVarStr(_T("常规"), _T("COND"), EMFC::STL2MFC(bitCond.to_string()), 0);
	
	// 编辑框
	CString str;
	for(int i = 0; i<15; ++i)
	{
		str.Format(_T("C%02d"), i+1);
		fin.SetVarStr(_T("常规"), str, *aSTR_COND[i], 0);
	}
	
	// 容错值
	fin.SetVarInt(_T("常规"), _T("ERR"), m_cmbAllowError.GetCurSel(), 0);
}

void CCond1::SaveCondition()
{
#define BOOL_2_BITSET(x)	(bitCond[_ttoi(#x)-1] = m_bC1##x ? true : false)
	BOOL_2_BITSET(01);
	BOOL_2_BITSET(02);
	BOOL_2_BITSET(03);
	BOOL_2_BITSET(04);
	BOOL_2_BITSET(05);
	BOOL_2_BITSET(06);
	BOOL_2_BITSET(07);
	BOOL_2_BITSET(08);
	BOOL_2_BITSET(09);
	BOOL_2_BITSET(10);
	BOOL_2_BITSET(11);
	BOOL_2_BITSET(12);
	BOOL_2_BITSET(13);
	BOOL_2_BITSET(14);
	BOOL_2_BITSET(15);
#undef BOOL_2_BITSET

#define INT_2_BITSET(x)		(bitCond[_ttoi(#x)+14] = (m_iC2##x == 1 ? true : false))
	INT_2_BITSET(01);
	INT_2_BITSET(02);
	INT_2_BITSET(03);
	INT_2_BITSET(04);
	INT_2_BITSET(05);
	INT_2_BITSET(06);
	INT_2_BITSET(07);
	INT_2_BITSET(08);
	INT_2_BITSET(09);
	INT_2_BITSET(10);
	INT_2_BITSET(11);
	INT_2_BITSET(12);
	INT_2_BITSET(13);
	INT_2_BITSET(14);
	INT_2_BITSET(15);
#undef  INT_2_BITSET
}

VOID CCond1::LoadCondition(CIniFile& fin)
{
	CString str;

	// 逻辑选择状态
	fin.GetVarStr(_T("常规"), _T("COND"), str);
	bitset<30> bc(EMFC::MFC2STL(str));
	bitCond = bc;
	LoadCondition();
	
	// 编辑框
	for(int i=0; i<15; ++i)
	{
		str.Format(_T("C%02d"), i+1);
		fin.GetVarStr(_T("常规"), str, *aSTR_COND[i]);
	}
	
	// 容错值
	int err = 0;
	fin.GetVarInt(_T("常规"), _T("ERR"), err);
	if(err < 0 || err > m_cmbAllowError.GetCount() - 1)
		err = m_cmbAllowError.GetCount() - 1;
	m_cmbAllowError.SetCurSel(err);
	
	EnableCond();
	UpdateData(FALSE);
}

void CCond1::LoadCondition()
{
#define BITSET_2_BOOT(x)	(m_bC1##x = (bitCond[_ttoi(#x)-1] == true))
	BITSET_2_BOOT(01);
	BITSET_2_BOOT(02);
	BITSET_2_BOOT(03);
	BITSET_2_BOOT(04);
	BITSET_2_BOOT(05);
	BITSET_2_BOOT(06);
	BITSET_2_BOOT(07);
	BITSET_2_BOOT(08);
	BITSET_2_BOOT(09);
	BITSET_2_BOOT(10);
	BITSET_2_BOOT(11);
	BITSET_2_BOOT(12);
	BITSET_2_BOOT(13);
	BITSET_2_BOOT(14);
	BITSET_2_BOOT(15);
#undef BITSET_2_BOOT
	
#define BITSET_2_INT(x)		(m_iC2##x = (bitCond[_ttoi(#x)+14] ? 1 : 0))
	BITSET_2_INT(01);
	BITSET_2_INT(02);
	BITSET_2_INT(03);
	BITSET_2_INT(04);
	BITSET_2_INT(05);
	BITSET_2_INT(06);
	BITSET_2_INT(07);
	BITSET_2_INT(08);
	BITSET_2_INT(09);
	BITSET_2_INT(10);
	BITSET_2_INT(11);
	BITSET_2_INT(12);
	BITSET_2_INT(13);
	BITSET_2_INT(14);
	BITSET_2_INT(15);
#undef BITSET_2_INT
}

void CCond1::EnableCond()
{
	for(int i = 0; i < 15; ++i)
	{
		GetDlgItem(IDC_EDIT_C101 + i)->EnableWindow(bitCond[i]);
		GetDlgItem(IDC_C1_RAD_011 + (i << 1))->EnableWindow(bitCond[i]);
		GetDlgItem(IDC_C1_RAD_012 + (i << 1))->EnableWindow(bitCond[i]);
	}
}

BOOL CCond1::PreTranslateMessage(MSG* pMsg) 
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
			if( pMsg->hwnd != GetDlgItem(IDC_EDIT_C114)->GetSafeHwnd() )
			{
				return TRUE;
			}
		}
	}	
	
	return CDialog::PreTranslateMessage(pMsg);
}

HBRUSH CCond1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here

	if (nCtlColor == CTLCOLOR_STATIC && 
		pWnd->GetDlgCtrlID () == IDC_STATIC_C1_TIP1)
	{
		pDC->SetTextColor(RGB(0, 0, 255));
		pDC->SetBkMode(TRANSPARENT);
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

VOID CCond1::ReadPara()
{
	UpdateData(TRUE);

	int n = C3D::Str2Sum(m_strC114, arrSum);
	m_strC114 = C3D::Sum2Str(arrSum);

	UpdateData(FALSE);
}

BOOL CCond1::IsValid()
{
	return m_bC101 || m_bC102 || m_bC103 || m_bC104 || m_bC105
		|| m_bC106 || m_bC107 || m_bC108 || m_bC109 || m_bC110
		|| m_bC111 || m_bC112 || m_bC113 || m_bC114 || m_bC115;
}

CString CCond1::ExportComment()
{
	static CString NAME[] = {
		_T("奇码数"), _T("偶码数"), _T("小码数"), _T("大码数"), _T("质码数"),
		_T("新码数"), _T("孤码数"), _T("斜码数"), _T("左斜数"), _T("右斜数"),
		_T("连号数"), _T("平均值"), _T("跨度"),   _T("和值"),   _T("和尾")
	};

	ReadPara();
	SaveCondition();

	CString str = _T("");

	for(int i = 0; i < 15; ++i)
	{
		if( bitCond[i] )
		{
			str += NAME[i] + _T("：")
				+ (bitCond[15+i] ? _T("杀") : _T(""))
				+ *aSTR_COND[i] + _T("\n");
		}
	}
	
	return str;
}
