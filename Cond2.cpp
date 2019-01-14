// Cond2.cpp : implementation file
//

#include "stdafx.h"
#include "My3D.h"
#include "Cond2.h"
#include "DataChart.h"

#include "..\Share\wnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCond2 dialog


CCond2::CCond2(CWnd* pParent /*=NULL*/)
	: CDialog(CCond2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCond2)
	m_bC201 = FALSE;
	m_bC202 = FALSE;
	m_bC203 = FALSE;
	m_bC204 = FALSE;
	//}}AFX_DATA_INIT

	pApp = (CMy3DApp*)AfxGetApp();
}


void CCond2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCond2)
	DDX_Check(pDX, IDC_CHECK_C2_01, m_bC201);
	DDX_Check(pDX, IDC_CHECK_C2_02, m_bC202);
	DDX_Check(pDX, IDC_CHECK_C2_03, m_bC203);
	DDX_Check(pDX, IDC_CHECK_C2_04, m_bC204);
	DDX_Control(pDX, IDC_C2_CMB_ERROR, m_cmbAllowError);	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCond2, CDialog)
	//{{AFX_MSG_MAP(CCond2)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_CHECK_C2_01, IDC_CHECK_C2_04, OnSelectCond)
	ON_COMMAND_RANGE(IDC_BTN_C201, IDC_BTN_C204, OnBtnCls)
	ON_COMMAND_RANGE(IDC_BTN_R201, IDC_BTN_R204, OnBtnReverse)
	ON_COMMAND_RANGE(IDC_BTN_F201, IDC_BTN_F204, OnBtnReference)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCond2 message handlers

BOOL CCond2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString str;
	for(int i = 0; i <= 4; ++i)
	{
		str.Format(_T("%d"), i);
		m_cmbAllowError.AddString(str);
	}
	
	Init();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

VOID CCond2::Init()
{
	m_bC201 = m_bC202 = m_bC203 = m_bC204 = FALSE;
	EnableCond();

	for(UINT i = 0; i < 8 ; ++i)
	{
		((CButton*)GetDlgItem(IDC_CHECK_C2_01_0 + i))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_C2_02_0 + i))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK_C2_03_0 + i))->SetCheck(FALSE);
	}

	for(UINT i = 0; i < 27 ; ++i)
	{
		((CButton*)GetDlgItem(IDC_CHECK_C2_04_00 + i))->SetCheck(FALSE);
	}
	
	m_cmbAllowError.SetCurSel(m_cmbAllowError.GetCount() - 1);
	UpdateData(FALSE);
}

UINT CCond2::FilterNum(UINT num, UINT nOffse /*= 0*/)
{
	UINT err = 0;
	UINT cnt;
	C3D CNum(num);
	
	// 奇偶
	if(m_bC201)
	{
		cnt = CNum.OddModality();
		err += !((CButton*)GetDlgItem(IDC_CHECK_C2_01_0 + cnt))->GetState();
	}
	
	// 大小
	if(m_bC202)
	{
		cnt = CNum.LargeModality();
		err += !((CButton*)GetDlgItem(IDC_CHECK_C2_02_0 + cnt))->GetState();
	}
	
	// 质合
	if(m_bC203)
	{
		cnt = CNum.PrimeModality();
		err += !((CButton*)GetDlgItem(IDC_CHECK_C2_03_0 + cnt))->GetState();
	}
	
	// 012 路
	if(m_bC204)
	{
		cnt = CNum.AC3Modality();
		err += !((CButton*)GetDlgItem(IDC_CHECK_C2_04_00 + cnt))->GetState();
	}

	return err;
}

VOID CCond2::EnableCond()
{
	for(UINT i = 0; i < 8; ++i)
	{
		GetDlgItem(IDC_CHECK_C2_01_0 + i)->EnableWindow(m_bC201);
		GetDlgItem(IDC_CHECK_C2_02_0 + i)->EnableWindow(m_bC202);
		GetDlgItem(IDC_CHECK_C2_03_0 + i)->EnableWindow(m_bC203);
	}

	for(UINT i = 0; i < 27; ++i)
	{
		GetDlgItem(IDC_CHECK_C2_04_00 + i)->EnableWindow(m_bC204);
	}

	for(UINT i = 0; i < 2; ++i)
	{
		GetDlgItem(IDC_BTN_C201 + (i << 2))->EnableWindow(m_bC201);
		GetDlgItem(IDC_BTN_C202 + (i << 2))->EnableWindow(m_bC202);
		GetDlgItem(IDC_BTN_C203 + (i << 2))->EnableWindow(m_bC203);
		GetDlgItem(IDC_BTN_C204 + (i << 2))->EnableWindow(m_bC204);
	}
}

VOID CCond2::OnSelectCond(UINT nID)
{
	ASSERT(IDC_CHECK_C2_01 <= nID && IDC_CHECK_C2_04 >= nID);

	UpdateData(TRUE);
	EnableCond();

#ifdef _UNRESTRICT_
	//推荐
	if( WND::IsCtrlDown() )
	{
		if( !pApp->GetHistory()->IsNull() )
		{
			C3D CNum = (pApp->GetHistory())->GetCNum(0);

			SaveCondition();

			int n;
			switch(nID - IDC_CHECK_C2_01)
			{
			case 0:
				n = CNum.OddModality() + 4;
				for(int i=4; i < 12; ++i)
				{
					sel1.set( i, m_bC201 && n != i );
				}
				break;
			case 1:
				n = CNum.LargeModality() + 12;
				for(int i=12; i < 20; ++i)
				{
					sel1.set(i, m_bC202 && n != i);
				}
				break;
			case 2:
				n = CNum.PrimeModality() + 20;
				for(int i = 20; i < 28; ++i)
				{
					sel1.set(i, m_bC203 && n != i);
				}
				break;
			case 3:
				n = CNum.AC3Modality();
				if(m_bC204)
				{
					sel2.set();
					
					sel2.reset(n);
					sel2.reset((n + 26) % 27);
					sel2.reset((n + 1) % 27);
				}
				else
					sel2.reset();
				break;
			}
			
			LoadCondition();
		}
	}
#endif

	UpdateData(FALSE);
}

VOID CCond2::OnBtnCls(UINT nID)
{
	UpdateData(TRUE);

	ASSERT(IDC_BTN_C201 <= nID && IDC_BTN_C204 >= nID);

	nID -= IDC_BTN_C201;

	UINT nLoop = nID < 3 ? 8 : 27;

	for(UINT i = 0; i < nLoop; ++i)
	{
		((CButton*)GetDlgItem(IDC_CHECK_C2_01_0 + nID * 10 + i))->SetCheck(FALSE);
	}

	UpdateData(FALSE);
}

VOID CCond2::OnBtnReverse(UINT nID)
{
	UpdateData(TRUE);

	ASSERT(IDC_BTN_R201 <= nID && IDC_BTN_R204 >= nID);

	nID -= IDC_BTN_R201;

	UINT nLoop = nID < 3 ? 8 : 27;
	BOOL bState;

	for(UINT i = 0; i < nLoop; ++i)
	{
		bState = !((CButton*)GetDlgItem(IDC_CHECK_C2_01_0 + nID * 10 + i))->GetState();
		((CButton*)GetDlgItem(IDC_CHECK_C2_01_0 + nID * 10 + i))->SetCheck(bState);
	}

	UpdateData(FALSE);
}

VOID CCond2::OnBtnReference(UINT nID)
{
	ASSERT(IDC_BTN_F201 <= nID && IDC_BTN_F204 >= nID);
	CDataChart dlg;
	dlg.SetType(nID - IDC_BTN_F201 + 34);
	dlg.DoModal();
}

BOOL CCond2::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(WM_KEYDOWN == pMsg->message)
	{
		if(VK_RETURN == pMsg->wParam || VK_ESCAPE == pMsg->wParam)
		{   
			return TRUE;   
		}
	}	
	
	return CDialog::PreTranslateMessage(pMsg);
}

VOID CCond2::SaveCondition(CIniFile &fin)
{
	SaveCondition();
	
	fin.SetVarStr(_T("形态"), _T("COND1"), EMFC::STL2MFC(sel1.to_string()), 0);
	fin.SetVarStr(_T("形态"), _T("COND2"), EMFC::STL2MFC(sel2.to_string()), 0);

	fin.SetVarInt(_T("形态"), _T("ERR"), m_cmbAllowError.GetCurSel(), 0);
}

VOID CCond2::SaveCondition()
{
	UpdateData(TRUE);

	// 条件选择
	sel1[0] = m_bC201 ? true : false;
	sel1[1] = m_bC202 ? true : false;
	sel1[2] = m_bC203 ? true : false;
	sel1[3] = m_bC204 ? true : false;
	
	// 奇偶
	for(UINT j = 0; j < 8; ++j)
		sel1[j + 4] = ((CButton*)GetDlgItem(IDC_CHECK_C2_01_0 + j))->GetState() ? true : false;
	// 大小
	for(UINT j = 0; j < 8; ++j)
		sel1[j + 12] = ((CButton*)GetDlgItem(IDC_CHECK_C2_02_0 + j))->GetState() ? true : false;
	// 质合
	for(UINT j = 0; j < 8; ++j)
		sel1[j + 20] = ((CButton*)GetDlgItem(IDC_CHECK_C2_03_0 + j))->GetState() ? true : false;

	// 012路
	for(UINT j = 0; j < 27; ++j)
		sel2[j] = ((CButton*)GetDlgItem(IDC_CHECK_C2_04_00 + j))->GetState() ? true : false;
}

VOID CCond2::LoadCondition(CIniFile &fin)
{
	CString str;
	
	fin.GetVarStr(_T("形态"), _T("COND1"), str);
	bitset<28> bc1(EMFC::MFC2STL(str));
	sel1 = bc1;

	fin.GetVarStr(_T("形态"), _T("COND2"), str);
	bitset<27> bc2(EMFC::MFC2STL(str));
	sel2 = bc2;

	LoadCondition();
	
	// 容错
	int c3 = -1;
	fin.GetVarInt(_T("形态"), _T("ERR"), c3);
	
	if(c3 < 0 || c3 > m_cmbAllowError.GetCount() - 1 )
		c3 = m_cmbAllowError.GetCount() - 1;
	m_cmbAllowError.SetCurSel(c3);
}

VOID CCond2::LoadCondition()
{
	UpdateData(TRUE);
	
	m_bC201 = sel1[0];
	m_bC202 = sel1[1];
	m_bC203 = sel1[2];
	m_bC204 = sel1[3];
	EnableCond();
	
	for(UINT j = 0; j < 8; ++j)
		((CButton*)GetDlgItem(IDC_CHECK_C2_01_0 + j))->SetCheck(sel1[j + 4]);

	for(UINT j = 0; j < 8; ++j)
		((CButton*)GetDlgItem(IDC_CHECK_C2_02_0 + j))->SetCheck(sel1[j + 12]);

	for(UINT j = 0; j < 8; ++j)
		((CButton*)GetDlgItem(IDC_CHECK_C2_03_0 + j))->SetCheck(sel1[j + 20]);

	for(UINT j = 0; j < 27; ++j)
		((CButton*)GetDlgItem(IDC_CHECK_C2_04_00 + j))->SetCheck(sel2[j]);

	UpdateData(FALSE);
}

HBRUSH CCond2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_STATIC && 
		pWnd->GetDlgCtrlID () == IDC_STATIC_C2_TIP)
	{
		pDC->SetTextColor(RGB(0, 0, 255));
		pDC->SetBkMode(TRANSPARENT);
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CCond2::IsValid()
{
	return m_bC201 || m_bC202 || m_bC203 || m_bC204;
}

VOID CCond2::ReadPara()
{
	UpdateData(TRUE);
}

CString CCond2::ExportComment()
{
	static CString NAME[] = { _T("奇偶排列"), _T("大小排列"), _T("质合排列"), _T("012路") };
	
	ReadPara();
	SaveCondition();
	
	CString str = _T("");	
	
	// 奇偶、大小、质合
	for(int j = 0; j < 3; ++j)
	{
		if( sel1[j] )
		{
			str += NAME[j] + _T("：");
			
			for(int i = 0; i < 8; ++i)
			{
				if( sel1[4+j*8+i] )
					str += C3D::strModality[j][i] + _T("+");
			}
			str.TrimRight(_T("+"));
			str += _T("\n");
		}
	}
	// 012路
	if( sel1[3] )
	{
		str += NAME[3] + _T("：");
		
		for(int i = 0; i < 27; ++i)
		{
			if( sel2[i] )
				str += C3D::str012[i] + _T("+");
		}
		str.TrimRight(_T("+"));
		str += _T("\n");
	}
	
	return str;
}
