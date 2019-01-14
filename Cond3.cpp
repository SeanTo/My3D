// Cond3.cpp : implementation file
//

#include "stdafx.h"
#include "My3D.h"
#include "Cond3.h"
#include "DataChart.h"

#include "..\Share\wnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCond3 dialog


CCond3::CCond3(CWnd* pParent /*=NULL*/)
	: CDialog(CCond3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCond3)
	m_bC301 = FALSE;
	m_bC302 = FALSE;
	m_bC303 = FALSE;
	m_bC304 = FALSE;
	m_bC305 = FALSE;
	m_bC306 = FALSE;
	m_bC307 = FALSE;
	m_bC308 = FALSE;
	m_bC309 = FALSE;
	m_bC310 = FALSE;
	m_bC311 = FALSE;
	m_bC312 = FALSE;
	m_bC314 = FALSE;
	m_bC315 = FALSE;
	m_bC316 = FALSE;
	m_bC317 = FALSE;
	m_bC318 = FALSE;
	m_bC319 = FALSE;
	m_bC320 = FALSE;
	m_bExcludeSame = FALSE;
	m_strC301 = _T("");
	m_strC302 = _T("");
	m_strC303 = _T("");
	m_strC304 = _T("");
	m_strC305 = _T("");
	m_strC306 = _T("");
	m_strC307 = _T("");
	m_strC308 = _T("");
	m_strC309 = _T("");
	m_strC310 = _T("");
	m_strC311 = _T("");
	m_strC312 = _T("");
	m_strC320 = _T("");
	m_strDecCnt = _T("123");
	m_strSumCnt = _T("123");
	m_strMulCnt = _T("123");
	m_iC301 = 1;
	m_iC302 = 1;
	m_iC303 = 1;
	m_iC304 = 1;
	m_iC305 = 1;
	m_iC306 = 1;
	m_iC307 = 1;
	m_iC308 = 1;
	m_iC309 = 1;
	m_iC310 = 1;
	m_iC311 = 1;
	m_iC312 = 1;
	m_iC313 = 1;
	//}}AFX_DATA_INIT
	
	pApp = (CMy3DApp*)AfxGetApp();
	pHistory = pApp->GetHistory();
	pData = NULL;
	
	aSTR_COND[0] = 	&m_strC301;
	aSTR_COND[1] = 	&m_strC302;
	aSTR_COND[2] = 	&m_strC303;
	aSTR_COND[3] = 	&m_strC304;
	aSTR_COND[4] = 	&m_strC305;
	aSTR_COND[5] = 	&m_strC306;
	aSTR_COND[6] = 	&m_strC307;
	aSTR_COND[7] = 	&m_strC308;
	aSTR_COND[8] = 	&m_strC309;
	aSTR_COND[9] = 	&m_strC310;

	aSTR_COND[10] = &m_strC311;
	aSTR_COND[11] = &m_strC312;
	aSTR_COND[12] = &m_strDecCnt;
	aSTR_COND[13] = &m_strSumCnt;
	aSTR_COND[14] = &m_strMulCnt;
}

void CCond3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCond3)
	DDX_Control(pDX, IDC_COMB_C3_01, m_cmbC3101);
	DDX_Control(pDX, IDC_COMB_C3_02, m_cmbC3201);
	DDX_Control(pDX, IDC_COMB_C3_03, m_cmbC3102);
	DDX_Control(pDX, IDC_COMB_C3_04, m_cmbC3202);
	DDX_Control(pDX, IDC_COMB_C3_05, m_cmbC3103);
	DDX_Control(pDX, IDC_COMB_C3_06, m_cmbC3203);
	DDX_Control(pDX, IDC_COMB_C3_07, m_cmbC3104);
	DDX_Control(pDX, IDC_COMB_C3_08, m_cmbC3204);
	DDX_Control(pDX, IDC_COMB_C3_09, m_cmbC3105);
	DDX_Control(pDX, IDC_COMB_C3_10, m_cmbC3205);
	DDX_Control(pDX, IDC_COMB_C3_11, m_cmbC3106);
	DDX_Control(pDX, IDC_COMB_C3_12, m_cmbC3206);
	DDX_Check(pDX, IDC_C3_CHK_01, m_bC301);
	DDX_Check(pDX, IDC_C3_CHK_02, m_bC302);
	DDX_Check(pDX, IDC_C3_CHK_03, m_bC303);
	DDX_Check(pDX, IDC_C3_CHK_04, m_bC304);
	DDX_Check(pDX, IDC_C3_CHK_05, m_bC305);
	DDX_Check(pDX, IDC_C3_CHK_06, m_bC306);
	DDX_Check(pDX, IDC_C3_CHK_07, m_bC307);
	DDX_Check(pDX, IDC_C3_CHK_08, m_bC308);
	DDX_Check(pDX, IDC_C3_CHK_09, m_bC309);
	DDX_Check(pDX, IDC_C3_CHK_10, m_bC310);
	DDX_Check(pDX, IDC_C3_CHK_11, m_bC311);
	DDX_Check(pDX, IDC_C3_CHK_12, m_bC312);
	DDX_Check(pDX, IDC_C3_CHK_14, m_bC314);
	DDX_Check(pDX, IDC_C3_CHK_15, m_bC315);
	DDX_Check(pDX, IDC_C3_CHK_16, m_bC316);
	DDX_Check(pDX, IDC_C3_CHK_17, m_bC317);
	DDX_Check(pDX, IDC_C3_CHK_18, m_bC318);
	DDX_Check(pDX, IDC_C3_CHK_19, m_bC319);
	DDX_Check(pDX, IDC_C3_CHK_20, m_bC320);
	DDX_Check(pDX, IDC_CHK_EXCLUDE_SAME, m_bExcludeSame);
	DDX_Radio(pDX, IDC_C3_RAD_011, m_iC301);
	DDX_Radio(pDX, IDC_C3_RAD_021, m_iC302);
	DDX_Radio(pDX, IDC_C3_RAD_031, m_iC303);
	DDX_Radio(pDX, IDC_C3_RAD_041, m_iC304);
	DDX_Radio(pDX, IDC_C3_RAD_051, m_iC305);
	DDX_Radio(pDX, IDC_C3_RAD_061, m_iC306);
	DDX_Radio(pDX, IDC_C3_RAD_071, m_iC307);
	DDX_Radio(pDX, IDC_C3_RAD_081, m_iC308);
	DDX_Radio(pDX, IDC_C3_RAD_091, m_iC309);
	DDX_Radio(pDX, IDC_C3_RAD_101, m_iC310);
	DDX_Radio(pDX, IDC_C3_RAD_111, m_iC311);
	DDX_Radio(pDX, IDC_C3_RAD_121, m_iC312);
	DDX_Text(pDX, IDC_C3_EDIT_01, m_strC301);
	DDV_MaxChars(pDX, m_strC301, 10);
	DDX_Text(pDX, IDC_C3_EDIT_02, m_strC302);
	DDV_MaxChars(pDX, m_strC302, 10);
	DDX_Text(pDX, IDC_C3_EDIT_03, m_strC303);
	DDV_MaxChars(pDX, m_strC303, 10);
	DDX_Text(pDX, IDC_C3_EDIT_04, m_strC304);
	DDV_MaxChars(pDX, m_strC304, 10);
	DDX_Text(pDX, IDC_C3_EDIT_05, m_strC305);
	DDV_MaxChars(pDX, m_strC305, 10);
	DDX_Text(pDX, IDC_C3_EDIT_06, m_strC306);
	DDV_MaxChars(pDX, m_strC306, 10);
	DDX_Text(pDX, IDC_C3_EDIT_07, m_strC307);
	DDV_MaxChars(pDX, m_strC307, 10);
	DDX_Text(pDX, IDC_C3_EDIT_08, m_strC308);
	DDV_MaxChars(pDX, m_strC308, 5);
	DDX_Text(pDX, IDC_C3_EDIT_09, m_strC309);
	DDV_MaxChars(pDX, m_strC309, 10);
	DDX_Text(pDX, IDC_C3_EDIT_10, m_strC310);
	DDV_MaxChars(pDX, m_strC310, 10);
	DDX_Text(pDX, IDC_C3_EDIT_11, m_strC311);
	DDV_MaxChars(pDX, m_strC311, 10);
	DDX_Text(pDX, IDC_C3_EDIT_12, m_strC312);
	DDV_MaxChars(pDX, m_strC312, 10);
	DDX_Text(pDX, IDC_C3_EDIT_20, m_strC320);
	DDV_MaxChars(pDX, m_strC320, 10);
	DDX_Text(pDX, IDC_EDIT_CNT_DEC, m_strDecCnt);
	DDV_MaxChars(pDX, m_strDecCnt, 3);
	DDX_Text(pDX, IDC_EDIT_CNT_SUM, m_strSumCnt);
	DDV_MaxChars(pDX, m_strSumCnt, 3);
	DDX_Text(pDX, IDC_EDIT_CNT_MUL, m_strMulCnt);
	DDV_MaxChars(pDX, m_strMulCnt, 3);
	DDX_Control(pDX, IDC_C3_CMB_ERROR, m_cmbAllowError);	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCond3, CDialog)
	//{{AFX_MSG_MAP(CCond3)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_C3_CHK_01, IDC_C3_CHK_20, OnSelectCond)
	ON_COMMAND_RANGE(IDC_C3_BTN_01, IDC_C3_BTN_12, OnBtnReference)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCond3 message handlers

BOOL CCond3::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString str;
	for(int i = 0; i <= 19; ++i)
	{
		str.Format(_T("%d"), i);
		m_cmbAllowError.AddString(str);
	}
	
	Init();
	
	// 按钮悬浮提示
	EnableToolTips(TRUE);
	m_tt.Create(this);
	m_tt.Activate(TRUE);
	
	m_tt.SetMaxTipWidth(130); //提示文字行宽度，非必需
	m_tt.SetTipTextColor(RGB(255,0,0)); //提示文字颜色，非必需
	//	m_tt.SetDelayTime(100);    //提示显示时间，非必需
	
	m_tt.AddTool(GetDlgItem(IDC_CHK_EXCLUDE_SAME),"如号码225, 两码和为477选中则7只计一次");
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

UINT CCond3::FilterNum(UINT num, int iOffset /*= 0*/)
{
	int err = 0;
	int cnt;
	C3D CNum(num), CNum2;

	// 任两码跨
 	CNum2 = CNum.TwoNumSpan();
	
	// 百十跨
	if(m_bC301 && !m_strC301.IsEmpty() )
	{
		err += EMFC::IsInArray(CNum2.Hun(), m_strC301) == (m_iC301 == 1);
	}
	// 百个跨
	if(m_bC302 && !m_strC302.IsEmpty() )
	{
		cnt = CNum2[1];
		err += EMFC::IsInArray(cnt, m_strC302) == (m_iC302 == 1);
	}
	// 十个跨
	if(m_bC303 && !m_strC303.IsEmpty() )
	{
		cnt = CNum2[2];
		err += EMFC::IsInArray(cnt, m_strC303) == (m_iC303 == 1);
	}

	// 两码跨
	if(m_bC310 && !m_strC310.IsEmpty() )
	{
		cnt = CNum2.CountInStr(m_strC310, m_bExcludeSame);
		err += ( EMFC::IsInArray(cnt, m_strDecCnt) ) == (m_iC310 == 1) ;
	}

	// 任两码和
	CNum2 = CNum.TwoNumSum();
	
	// 百十位和
	if(m_bC304 && !m_strC304.IsEmpty() )
	{
		cnt = CNum2[0];
		err += EMFC::IsInArray(cnt, m_strC304) == (m_iC304 == 1);
	}
	// 百个位和
	if(m_bC305 && !m_strC305.IsEmpty() )
	{
		cnt = CNum2[1];
		err += EMFC::IsInArray(cnt, m_strC305) == (m_iC305 == 1);
	}
	// 十个位和
	if(m_bC306 && !m_strC306.IsEmpty())
	{
		cnt = CNum2[2];
		err += EMFC::IsInArray(cnt, m_strC306) == (m_iC306 == 1);
	}
	// 两码和
	if(m_bC311 && !m_strC311.IsEmpty())
	{
		cnt = CNum2.CountInStr(m_strC311, m_bExcludeSame);
		err += ( EMFC::IsInArray(cnt, m_strSumCnt) ) == (m_iC311 == 1) ;
	}

	// 任两码积
	CNum2 = CNum.TwoNumMul();
	
	// 百十位积
	if(m_bC307 && !m_strC307.IsEmpty() )
	{
		cnt = CNum2[0];
		err += EMFC::IsInArray(cnt, m_strC307, 10) == (m_iC307 == 1);
	}
	// 百个位积
	if(m_bC308 && !m_strC308.IsEmpty())
	{
		cnt = CNum2[1];
		err += EMFC::IsInArray(cnt, m_strC308, 10) == (m_iC308 == 1);
	}
	// 十个位积
	if(m_bC309 && !m_strC309.IsEmpty())
	{
		cnt = CNum2[2];
		err += EMFC::IsInArray(cnt, m_strC309, 10) == (m_iC309 == 1);
	}
	// 两码积
	if(m_bC312 && !m_strC312.IsEmpty())
	{
		cnt = CNum2.CountInStr(m_strC312, m_bExcludeSame);
		err += ( EMFC::IsInArray(cnt, m_strMulCnt) ) == (m_iC312 == 1) ;
	}
	
	// 历史
	if(m_bC320 && !m_strC320.IsEmpty())
	{
		cnt = pHistory->GetCount();
		
		if(cnt > iOffset)
		{
			int n = _ttoi(m_strC320);
			if(-1 == n)
				n = pHistory->GetPeriod(iOffset) % 1000;
			else if(n > cnt || 0 == n)
				n = cnt - iOffset;
			
			BOOL bYes = FALSE;
			for(int i = 0; i < n; ++i)
			{
				if(pHistory->GetNum(i + iOffset) == CNum)
				{
					bYes = TRUE;
					break;
				}
			}
			err += bYes;
		}
	}
	
	// 大号连续
	if(m_bC314)
	{
		cnt = CNum.ContinueLarge();
		err += cnt < m_cmbC3101.GetCurSel() || cnt > m_cmbC3201.GetCurSel();
	}
	
	// 小号连续
	if(m_bC315)
	{
		cnt = CNum.ContinueSmall();
		err += m_cmbC3102.GetCurSel() > cnt || cnt > m_cmbC3202.GetCurSel();
	}
	
	// 奇号连续
	if(m_bC316)
	{
		cnt = CNum.ContinueOdd();
		err += m_cmbC3103.GetCurSel() > cnt || cnt > m_cmbC3203.GetCurSel();
	}
	
	// 偶号连续
	if(m_bC317)
	{
		cnt = CNum.ContinueEven();
		err += m_cmbC3104.GetCurSel() > cnt || cnt > m_cmbC3204.GetCurSel();
	}
	
	// 质号连续
	if(m_bC318)
	{
		cnt = CNum.ContinuePrime();
		err += m_cmbC3105.GetCurSel() > cnt || cnt > m_cmbC3205.GetCurSel();
	}
	
	// 遗漏总值
	if(m_bC319)
	{
		cnt = pHistory->StatMiss(iOffset, CNum);
		err += m_cmbC3106.GetCurSel() > cnt || cnt > m_cmbC3206.GetCurSel();
	}

	return err;
}

BOOL CCond3::PreTranslateMessage(MSG* pMsg) 
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

VOID CCond3::Init()
{
	m_cmbAllowError.SetCurSel(m_cmbAllowError.GetCount() - 1);
	
	for(int i=0; i<13; ++i)
		aSTR_COND[i]->Empty();

	m_strC320 = _T("30");

	m_strDecCnt = _T("123");
	m_strSumCnt = _T("123");
	m_strMulCnt = _T("123");
	m_bExcludeSame = FALSE;
	
	m_cmbC3101.SetCurSel(0);
	m_cmbC3102.SetCurSel(0);
	m_cmbC3103.SetCurSel(0);
	m_cmbC3104.SetCurSel(0);
	m_cmbC3105.SetCurSel(0);
	m_cmbC3106.SetCurSel(0);
	m_cmbC3201.SetCurSel(m_cmbC3201.GetCount() - 1);
	m_cmbC3202.SetCurSel(m_cmbC3202.GetCount() - 1);
	m_cmbC3203.SetCurSel(m_cmbC3203.GetCount() - 1);
	m_cmbC3204.SetCurSel(m_cmbC3204.GetCount() - 1);
	m_cmbC3205.SetCurSel(m_cmbC3205.GetCount() - 1);
	m_cmbC3206.SetCurSel(m_cmbC3206.GetCount() - 1);

	bitCond.reset();
	bitCond2.set();
	SaveCondition();
	EnableCond();
	
	UpdateData(FALSE);
}

void CCond3::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::CalcWindowRect(lpClientRect, nAdjustType);
}

VOID CCond3::OnSelectCond(UINT nID)
{
	ASSERT(nID >= IDC_C3_CHK_01 && nID <= IDC_C3_CHK_20);
	UINT nSel = nID - IDC_C3_CHK_01;

	if( nSel == 12)
		return;

	UpdateData(TRUE);
	SaveCondition();
	EnableCond();
	
#ifdef _UNRESTRICT_
	// 推荐
	if(WND::IsCtrlDown() && !pHistory->IsNull())
	{
		C3D CNum = pHistory->GetCNum(0);
		CString str = _T("0123456789");
		UINT n;

		switch(nSel)
		{
		case 0: // 百十差
			if(m_bC301)
			{
				n = abs(CNum.Hun() - CNum.Ten());
				m_strC301 = EMFC::Int2Str( n );
			}
			else
				m_strC301.Empty();
			break;
		case 1: // 百个差
			if(m_bC302)
			{
				n = abs(CNum.Hun() - CNum.Ent());
				m_strC302 = EMFC::Int2Str( n );
			}
			else
				m_strC302.Empty();
			break;
		case 2: // 十个差
			if(m_bC303)
			{
				n = abs(CNum.Ten() - CNum.Ent());
				m_strC303 = EMFC::Int2Str( n );
			}
			else
				m_strC303.Empty();
			break;
		case 3: // 百十和
			if(m_bC304)
			{
				n = (CNum.Hun() + CNum.Ten()) % 10;
				m_strC304 = EMFC::Int2Str( n );
			}
			else
				m_strC304.Empty();
			break;
		case 4: // 百个和
			if(m_bC305)
			{
				n = (CNum.Hun() + CNum.Ent()) % 10;
				m_strC305 = EMFC::Int2Str( n );
			}
			else
				m_strC305.Empty();
			break;
		case 5: // 十个和
			if(m_bC306)
			{
				n = (CNum.Ten() + CNum.Ent()) % 10;
				m_strC306 = EMFC::Int2Str( n );
			}
			else
				m_strC306.Empty();
			break;
		case 6: // 百十积
			if(m_bC307)
			{
				n = (CNum.Hun() * CNum.Ten()) % 10;
				m_strC307 = EMFC::Int2Str( n );
			}
			else
				m_strC307.Empty();
			break;
		case 7: // 百个积
			if(m_bC308)
			{
				n = (CNum.Hun() * CNum.Ent()) % 10;
				m_strC308 = EMFC::Int2Str( n );
			}
			else
				m_strC308.Empty();

			break;
		case 8: // 十个积
			if(m_bC309)
			{
				n = (CNum.Ten() * CNum.Ent()) % 10;
				m_strC309 = EMFC::Int2Str( n );
			}
			else
				m_strC309.Empty();

			break;
		case 9: // 两码差
			if(m_bC310)
			{
				int iPeriod = 1;
				if( WND::IsCharDown(_T('2')) )
					iPeriod = 2;
				else if( WND::IsCharDown(_T('3')) )
					iPeriod = 3;
				else if( WND::IsCharDown(_T('4')) )
					iPeriod = 4;
				
				if( pHistory->GetCount() >= iPeriod )
				{
					m_strC310 = pHistory->MissTwoNum(iPeriod, 0, 0);
					m_strDecCnt = _T("123");
					m_bExcludeSame = FALSE;
					m_iC310 = 0;
				}
			}
			else
			{
				m_strC310.Empty();
				m_strDecCnt = _T("123");
				m_bExcludeSame = FALSE;
				m_iC310 = 1;
			}
			break;
		case 10: // 两码和
			if(m_bC311)
			{
				int iPeriod = 1;
				if( WND::IsCharDown(_T('2')) )
					iPeriod = 2;
				else if( WND::IsCharDown(_T('3')) )
					iPeriod = 3;
				else if( WND::IsCharDown(_T('4')) )
					iPeriod = 4;
				
				if( pHistory->GetCount() >= iPeriod )
				{
					m_strC311 = pHistory->MissTwoNum(iPeriod, 0, 1);
					m_strSumCnt = _T("123");
					m_bExcludeSame = FALSE;
					m_iC311 = 0;
				}
			}
			else
			{
				m_strC311.Empty();
				m_strSumCnt = _T("123");
				m_bExcludeSame = FALSE;
				m_iC311 = 1;
			}
			break;
		case 11: // 两码积
			if(m_bC312)
			{
				int iPeriod = 1;
				if( WND::IsCharDown(_T('2')) )
					iPeriod = 2;
				else if( WND::IsCharDown(_T('3')) )
					iPeriod = 3;
				else if( WND::IsCharDown(_T('4')) )
					iPeriod = 4;
				
				if( pHistory->GetCount() >= iPeriod )
				{
					m_strC312 = pHistory->MissTwoNum(iPeriod, 0, 2);
					m_strMulCnt = _T("123");
					m_bExcludeSame = FALSE;
					m_iC312 = 0;
				}
			}
			else
			{
				m_strC312.Empty();
				m_strMulCnt = _T("123");
				m_bExcludeSame = FALSE;
				m_iC312 = 1;
			}
			break;
		case 12: // 和尾
			/*
			 *	此条件已移到常规页面中
			 */
			break;

			// 以下是打开走势图参考
		case 13: // 大号连续
			m_bC314 = !m_bC314;
			break;
		case 14: // 小号连续
			m_bC315 = !m_bC315;
			break;
		case 15: // 奇号连续
			m_bC316 = !m_bC316;
			break;
		case 16: // 偶号连续
			m_bC317 = !m_bC317;
			break;
		case 17: // 质号连续
			m_bC318 = !m_bC318;
			break;
		case 18: // 遗漏总值
			m_bC319 = !m_bC319;
			break;
		case 19: // 历史
			if( m_bC320 )
			{
				m_strC320 = _T("0");
			}
			else
			{
				m_strC320 = _T("30");
			}
			break;
		}

		if(13 <= nSel && nSel <= 18)
		{
			LoadCondition();
			EnableCond();
			
			CDataChart dlg;
			dlg.SetType(nSel - 13 + 24);
			dlg.DoModal();
		}
	}
#endif
	
	UpdateData(FALSE);
}

VOID CCond3::EnableCond()
{
	for(UINT i = 0; i < 12; ++i)
	{
		GetDlgItem(IDC_C3_EDIT_01 + i)->EnableWindow(bitCond[i]);
		GetDlgItem(IDC_C3_RAD_011 + (i<<1))->EnableWindow(bitCond[i]);
		GetDlgItem(IDC_C3_RAD_012 + (i<<1))->EnableWindow(bitCond[i]);
	}

	for(UINT i = 0; i < 6; ++i)
	{
		GetDlgItem(IDC_COMB_C3_01 + (i << 1))->EnableWindow(bitCond[i + 13]);
		GetDlgItem(IDC_COMB_C3_02 + (i << 1))->EnableWindow(bitCond[i + 13]);
	}

	GetDlgItem(IDC_C3_EDIT_20)->EnableWindow(bitCond[19]);

	GetDlgItem(IDC_EDIT_CNT_DEC)->EnableWindow(m_bC310);
	GetDlgItem(IDC_EDIT_CNT_SUM)->EnableWindow(m_bC311);
	GetDlgItem(IDC_EDIT_CNT_MUL)->EnableWindow(m_bC312);
	GetDlgItem(IDC_CHK_EXCLUDE_SAME)->EnableWindow(m_bC310 || m_bC311 || m_bC312);
	GetDlgItem(IDC_STATIC_EXCLUDE_SAME2)->EnableWindow(m_bC310 || m_bC311 || m_bC312);
	GetDlgItem(IDC_STATIC_EXCLUDE_SAME3)->EnableWindow(m_bC310 || m_bC311 || m_bC312);
}

VOID CCond3::SaveCondition(CIniFile &fin)
{
	UpdateData(TRUE);
	SaveCondition();

	// 选择状态
	fin.SetVarStr(_T("其它"), _T("COND1"), EMFC::STL2MFC(bitCond.to_string()), 0);
	fin.SetVarStr(_T("其它"), _T("COND2"), EMFC::STL2MFC(bitCond2.to_string()), 0);

	// 两码跨、和、积，任两码
	CString str;
	for(int i=0; i<12; ++i)
	{
		str.Format(_T("C%02d"), i+1);
		fin.SetVarStr(_T("其它"), str, *aSTR_COND[i], 0);
	}

	// 任两码范围
	for(int i=0; i<3; ++i)
	{
		str.Format(_T("C1%d1"), i);
		fin.SetVarStr(_T("其它"), str, *aSTR_COND[i+12], 0);
	}

	// 范围条件
	int v = 0;
	v = v * 100 + m_cmbC3101.GetCurSel() * 10 + m_cmbC3201.GetCurSel();
	v = v * 100 + m_cmbC3102.GetCurSel() * 10 + m_cmbC3202.GetCurSel();
	v = v * 100 + m_cmbC3103.GetCurSel() * 10 + m_cmbC3203.GetCurSel();
	v = v * 100 + m_cmbC3104.GetCurSel() * 10 + m_cmbC3204.GetCurSel();
	fin.SetVarInt(_T("其它"), _T("C13"), v, 0);

	v = m_cmbC3105.GetCurSel() * 10 + m_cmbC3205.GetCurSel();
	v = v * 1000 + m_cmbC3106.GetCurSel();
	v = v * 1000 + m_cmbC3206.GetCurSel();
	fin.SetVarInt(_T("其它"), _T("C17"), v, 0);

	// 杀历史
	fin.SetVarStr(_T("其它"), _T("C19"), m_strC320, 0);

	//容错
	fin.SetVarInt(_T("其它"), _T("ERR"), m_cmbAllowError.GetCurSel(), 0);
}

VOID CCond3::LoadCondition(CIniFile &fin)
{
	CString str;
	
	//选择状态
	fin.GetVarStr(_T("其它"), _T("COND1"), str);
	bitset<20> b1(EMFC::MFC2STL(str));
	bitCond = b1;
	
	fin.GetVarStr(_T("其它"), _T("COND2"), str);
	bitset<12> b2(EMFC::MFC2STL(str));
	bitCond2 = b2;
	
	// 条件串
	for(int i=0; i<12; ++i)
	{
		str.Format(_T("C%02d"), i+1);
		fin.GetVarStr(_T("其它"), str, *aSTR_COND[i]);
	}
	
	// 	fin.GetVarStr(_T("其它"), _T("C10"), m_strC310);
	fin.GetVarStr(_T("其它"), _T("C101"), m_strDecCnt);
	// 	fin.GetVarStr(_T("其它"), _T("C11"), m_strC311);
	fin.GetVarStr(_T("其它"), _T("C111"), m_strSumCnt);
	// 	fin.GetVarStr(_T("其它"), _T("C12"), m_strC312);
	fin.GetVarStr(_T("其它"), _T("C121"), m_strMulCnt);
	
	// 范围条件
	int v = 0;
	
	fin.GetVarInt(_T("其它"), _T("C13"), v);
	m_cmbC3204.SetCurSel(v % 10);
	v /= 10;
	m_cmbC3104.SetCurSel(v % 10);
	v /= 10;
	m_cmbC3203.SetCurSel(v % 10);
	v /= 10;
	m_cmbC3103.SetCurSel(v % 10);
	v /= 10;
	m_cmbC3202.SetCurSel(v % 10);
	v /= 10;
	m_cmbC3102.SetCurSel(v % 10);
	v /= 10;
	m_cmbC3201.SetCurSel(v % 10);
	v /= 10;
	m_cmbC3101.SetCurSel(v % 10);
	
	fin.GetVarInt(_T("其它"), _T("C17"), v);
	m_cmbC3206.SetCurSel(v % 1000);
	v /= 1000;
	m_cmbC3106.SetCurSel(v % 1000);
	v /= 1000;
	m_cmbC3205.SetCurSel(v % 10);
	v /= 1000;
	m_cmbC3105.SetCurSel(v % 10);
	
	// 杀历史
	fin.GetVarStr(_T("其它"), _T("C19"), m_strC320);
	
	//容错
	fin.GetVarInt(_T("其它"), _T("ERR"), v);
	if(v < 0 || v >= m_cmbAllowError.GetCount())
		v = m_cmbAllowError.GetCount() - 1;
	m_cmbAllowError.SetCurSel(v);
	
	LoadCondition();
	EnableCond();
	UpdateData(FALSE);
}

VOID CCond3::SaveCondition()
{
	// 条件选择状态
#define BOOT_2_BITSET(x)	(bitCond[_ttoi(#x)-1] = m_bC3##x ? true : false)
	BOOT_2_BITSET(01);
	BOOT_2_BITSET(02);
	BOOT_2_BITSET(03);
	BOOT_2_BITSET(04);
	BOOT_2_BITSET(05);
	BOOT_2_BITSET(06);
	BOOT_2_BITSET(07);
	BOOT_2_BITSET(08);
	BOOT_2_BITSET(09);
	BOOT_2_BITSET(10);
	BOOT_2_BITSET(11);
	BOOT_2_BITSET(12);
	
	// 和尾条件移到常规页后，此条件改为排除重复的选项
	bitCond[12] = m_bExcludeSame ? true : false;
	
	BOOT_2_BITSET(14);
	BOOT_2_BITSET(15);
	BOOT_2_BITSET(16);
	BOOT_2_BITSET(17);
	BOOT_2_BITSET(18);
	BOOT_2_BITSET(19);
	BOOT_2_BITSET(20);
#undef BOOT_2_BITSET
	
	// 单选钮状态
#define INT_2_BITSET(x)	(bitCond2[_ttoi(#x)-1] = (m_iC3##x == 1 ? true : false))
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
#undef INT_2_BITSET
}

VOID CCond3::LoadCondition()
{
#define BITSET_2_BOOT(x)	(m_bC3##x = (bitCond[_ttoi(#x)-1] == true))
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
	
	// 和尾条件移到常规页后，此条件改为排除重复的选项
	m_bExcludeSame = (bitCond[12] == true);

	BITSET_2_BOOT(14);
	BITSET_2_BOOT(15);
	BITSET_2_BOOT(16);
	BITSET_2_BOOT(17);
	BITSET_2_BOOT(18);
	BITSET_2_BOOT(19);
	BITSET_2_BOOT(20);
#undef BITSET_2_BOOT
	
#define BITSET_2_INT(x)	(m_iC3##x = (bitCond2[_ttoi(#x)-1] == true ? 1 : 0))
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
#undef BITSET_2_INT
}

VOID CCond3::OnBtnReference(UINT nID)
{
	ASSERT(IDC_C3_BTN_01 <= nID && nID <= IDC_C3_BTN_09 );

	UINT iSel = nID - IDC_C3_BTN_01;
	
	CDataChart dlg;
	dlg.SetType(iSel + 14);
	dlg.DoModal();
}

BOOL CCond3::IsValid()
{
	return m_bC301 || m_bC302 || m_bC303 || m_bC304 || m_bC305
		|| m_bC306 || m_bC307 || m_bC308 || m_bC309 || m_bC310
		|| m_bC311 || m_bC312 /*|| m_bC313*/ || m_bC314 || m_bC315
		|| m_bC316 || m_bC317 || m_bC318 || m_bC319 || m_bC320;
}

VOID CCond3::ReadPara()
{
	UpdateData(TRUE);
}

CString CCond3::ExportComment()
{
	static CString NAME[] = {
		_T("百十跨"), _T("百个跨"), _T("十个跨"),
		_T("百十和"), _T("百个和"), _T("十个和"),
		_T("百十积"), _T("百个积"), _T("十个积"),
		_T("两码跨"), _T("两码和"), _T("两码积"),
	};
	
	ReadPara();
	LoadCondition();

	CString str = _T("");
	for(int i = 0; i < 12; ++i)
	{
		if( bitCond[i] )
		{
			str += NAME[i] + _T("：")
				+ (bitCond2[i] ? _T("杀") : _T(""))
				+ *aSTR_COND[i];

			if( i >= 9 )
				str += _T("=") + *aSTR_COND[i+3];

			str += _T("\n");
		}

	}

	return str;
}
