// PageSelNum.cpp : implementation file
//

#include "stdafx.h"
#include "My3D.h"
#include "My3DDlg.h"
#include "PageSelNum.h"

#include "..\Share\WND.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageSelNum dialog


CPageSelNum::CPageSelNum(CWnd* pParent /* = NULL */)
	: CDialog(CPageSelNum::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageSelNum)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	pApp = (CMy3DApp *)AfxGetApp();
	bsMask.set();
}

/*
 *	根据选择的号码预生成大底号
 */
VOID CPageSelNum::GetBase(CUIntArray *p)
{
	GetCond(bsMask);
	p->RemoveAll();

	UINT num;
	for(UINT i = 0; i < 10; ++i)
	{
		if( !bsMask[i] )
		{
			continue;
		}
		
		for(UINT j = 0; j < 10; ++j)
		{
			if( !bsMask[j + 10] )
			{
				continue;
			}
			
			for(UINT k = 0; k < 10; ++k)
			{
				if( !bsMask[k + 20] )
				{
					continue;
				}
				
				num = i * 100 + j * 10 + k;
				p->Add(num);
			}
		}
	}
	
	EMFC::SortArray(*p);
}

void CPageSelNum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSelNum)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageSelNum, CDialog)
	//{{AFX_MSG_MAP(CPageSelNum)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CLS_ALL1, IDC_CLS_ALL3, OnClearAll)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_REVERSE1, IDC_REVERSE3, OnReverseSel)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RECOMMEND1, IDC_RECOMMEND3, OnRecommendSel)
	ON_COMMAND_RANGE(IDC_CHECK_B10, IDC_CHECK_B39, OnSelectNum)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageSelNum message handlers


void CPageSelNum::OnClearAll(UINT nID)
{
	ASSERT(nID >= IDC_CLS_ALL1 && nID <= IDC_CLS_ALL3);
	
	UINT i = nID - IDC_CLS_ALL1;

	for (UINT j = 0; j < 10; ++j)
	{
		bsMask.reset(i * 10 + j);
	}
	
	SetCond(bsMask);
}

void CPageSelNum::OnReverseSel(UINT nID)
{
	ASSERT(nID >= IDC_REVERSE1 && nID <= IDC_REVERSE3);
	
	UINT i = nID - IDC_REVERSE1;

	for (UINT j = 0; j < 10; ++j)
	{
		bsMask.flip(i * 10 + j);
	}

	SetCond(bsMask);
}

VOID CPageSelNum::SetCond(bitset<30> &bc)
{
	bsMask = bc;
	for(int i = 0; i < 30; ++i)
	{
		((CButton*)GetDlgItem(IDC_CHECK_B10 + i))->SetCheck(bsMask[i] == true);
	}
	
	UpdateData(FALSE);
}

VOID CPageSelNum::GetCond(bitset<30> &bc)
{
	UpdateData(TRUE);
	for(int i = 0; i < 30; ++i)
	{
		bsMask[i] = ((CButton*)GetDlgItem(IDC_CHECK_B10 + i))->GetCheck() ? true : false;
	}
	bc = bsMask;
}

BOOL CPageSelNum::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	Init();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPageSelNum::PreTranslateMessage(MSG* pMsg) 
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

void CPageSelNum::OnRecommendSel(UINT nID)
{
	ASSERT(nID >= IDC_RECOMMEND1 && nID <= IDC_RECOMMEND3);
	
	UINT k = nID - IDC_RECOMMEND1;
	
	int cnt = ((CMy3DDlg*)(GetParent()->GetParent()))->GetPeriods();
	CHistory *pHistory = pApp->GetHistory();
	
	if( cnt > 0 && !pHistory->IsNull() )
	{
		UINT nSelNums = 9;
#ifdef _UNRESTRICT_
		if(WND::IsCharDown(_T('8')))
			nSelNums = 8;
		else if(WND::IsCharDown(_T('7')))
			nSelNums = 7;
		else if(WND::IsCharDown(_T('6')))
			nSelNums = 6;
		else if(WND::IsCharDown(_T('5')))
			nSelNums = 5;
		else if(WND::IsCharDown(_T('4')))
			nSelNums = 4;
		else if(WND::IsCharDown(_T('3')))
			nSelNums = 3;
		else if(WND::IsCharDown(_T('2')))
			nSelNums = 2;
		else if(WND::IsCharDown(_T('1')))
			nSelNums = 1;
#endif

		CUIntArray arrAMP;
		pHistory->StatAMP(pApp->iRecommandPeriod, arrAMP, k);

		for(UINT i = 0; i < (UINT)10; ++i)
		{
			if(i < (UINT)pApp->iRecommandNum /*nSelNums*/)
				
				bsMask.set(k * 10 + arrAMP[i]);
			else
				bsMask.reset(k * 10 + arrAMP[i]);

			SetCond(bsMask);
		}

		if( pApp->iWarnRecommand > 0)
		{
			CString strCaption;
			strCaption.LoadString(IDS_TITLE);
			
			CString str = EMFC::PrintArray(arrAMP, -1, 0, -1, _T("%d "));

			str = _T("本次推荐结果(概率由高到低):\n\n")
				+ str
				+ _T("\n\n注意：\n        推荐结果受统计历史期数影响，期数和码数自动适应")
				+ _T("\n        数据分析页中最后选择状态，即推荐排序与数据分析")
				+ _T("\n        页中最后看到的结果一致。")
				+ _T("\n\n使用推荐有风险，请自行决定是否使用，作者不负责赔偿!")
				+ _T("\n\n如需禁止此提示，可编辑 My3D.ini，修改：推荐警告=0")
				;
			
			MessageBox(str, strCaption, MB_ICONINFORMATION);
		}

		UpdateData(FALSE);
	}
	else
		AfxMessageBox(_T("历史开奖数据不足!"));
}

VOID CPageSelNum::Init()
{
	bsMask.set();
	SetCond(bsMask);

	UpdateData(FALSE);
}

VOID CPageSelNum::OnSelectNum(UINT nID)
{
	ASSERT( IDC_CHECK_B10 <= nID && nID <= IDC_CHECK_B39 );

	GetCond(bsMask);
	bsMask[nID - IDC_CHECK_B10] = ((CButton*)GetDlgItem(nID))->GetCheck() ? true : false;
	SetCond(bsMask);

	UpdateData(FALSE);
}

VOID CPageSelNum::SaveCondition(CIniFile &fin)
{
	GetCond(bsMask);
	
	CString str = EMFC::STL2MFC(bsMask.to_string());

	fin.SetVarStr(_T("投注方法"), _T("BW"), str.Mid(20, 10), 0);
	fin.SetVarStr(_T("投注方法"), _T("SW"), str.Mid(10, 10), 0);
	fin.SetVarStr(_T("投注方法"), _T("GW"), str.Mid(0, 10), 0);
}

VOID CPageSelNum::LoadCondition(CIniFile &fin)
{
	CString str, ss;

	fin.GetVarStr(_T("投注方法"), _T("BW"), ss);
	str = ss;
	fin.GetVarStr(_T("投注方法"), _T("SW"), ss);
	str += ss;
	fin.GetVarStr(_T("投注方法"), _T("GW"), ss);
	str += ss;

	bitset<30> bc(EMFC::MFC2STL(str));
	bsMask = bc;
	SetCond(bsMask);
}
