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
	
	// �б���
	m_List.InsertColumn(0,"���",LVCFMT_LEFT,43);    //����б���
	m_List.InsertColumn(1,"����",LVCFMT_LEFT,150);
	m_List.InsertColumn(2,"����",LVCFMT_LEFT,500);
	
	int iCount = 0;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("��̬����"));
	m_List.SetItemText(iCount, 2, _T("�����ڵ�������ο�ͳ�����ݾ����Ƿ�ʹ��"));
	bitSelDef[iCount] = true;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("��ʽ�� - ǿ����"));
	m_List.SetItemText(iCount, 2, _T("�Ƚϸ��ӣ���ο���ȷ��ͳ�ƾ����Ƿ�ʹ��"));
	bitSelDef[iCount] = true;
	++iCount;
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("��ʽ�� - ������"));
	m_List.SetItemText(iCount, 2, _T("�Ѱ�����ǿ�����У�ͬʱѡ�л�Ӱ���ݴ�Ч��"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("���벻ͬʱ�̳�"));
	m_List.SetItemText(iCount, 2, _T("���붨λ��������ͬ���1��"));
	bitSelDef[iCount] = true;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("012 ·��ȫ�̳�"));
	m_List.SetItemText(iCount, 2, _T("012 ·��λ����������ȫ��ͬ"));
	bitSelDef[iCount] = true;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("��̬��ͬʱ��ת"));
	m_List.SetItemText(iCount, 2, _T("��ż����С���ʺ����һ����̬��ȫ��ת���� [�ʺ���] �� [���ʺ�]"));
	bitSelDef[iCount] = true;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("�����ֵ"));
	m_List.SetItemText(iCount, 2, _T("��Χ: 2-7"));
	bitSelDef[iCount] = true;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("������"));
	m_List.SetItemText(iCount, 2, _T("�Ƚϸ��ӣ���ο���ȷ��ͳ�ƾ����Ƿ�ʹ��"));
	bitSelDef[iCount] = true;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("�ȳ����෨"));
	m_List.SetItemText(iCount, 2, _T("�������ں����ʮ��λ�����������ͬ"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("���ں������"));
	m_List.SetItemText(iCount, 2, _T("�����š�λ�λ��"));
	bitSelDef[iCount] = false;
	++iCount;
	
	// �����㷨
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("������粻4����"));
	m_List.SetItemText(iCount, 2, _T(""));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("������Ͳ�3����"));
	m_List.SetItemText(iCount, 2, _T("10-19 ��һ��ÿ��ɱ��"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("���������3����(0����)"));
	m_List.SetItemText(iCount, 2, _T("��һ���ض����ݳ���"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("��Ȳ�����3��"));
	m_List.SetItemText(iCount, 2, _T("ɱ�ŷǳ���Ч"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("��β������3��"));
	m_List.SetItemText(iCount, 2, _T("��׼ȷ���൱��"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("��ż��̬������3��"));
	m_List.SetItemText(iCount, 2, _T("����ѡ����10���ݴ�1-2"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("��С��̬������3��"));
	m_List.SetItemText(iCount, 2, _T("��Ϊһ�������ĵ�"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("�ʺ���̬������3��"));
	m_List.SetItemText(iCount, 2, _T(""));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("012 ·���ڳ�3��"));
	m_List.SetItemText(iCount, 2, _T(""));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("б��3������2��"));
	m_List.SetItemText(iCount, 2, _T(""));
	bitSelDef[iCount] = false;
	++iCount;
	
	// ɱ��ѡ��̬
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("ɱ����"));
	m_List.SetItemText(iCount, 2, _T("�������ݴ�"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("ɱ����"));
	m_List.SetItemText(iCount, 2, _T("�������ݴ�"));
	bitSelDef[iCount] = false;
	++iCount;
	
	m_List.InsertItem(iCount, EMFC::Int2Str(iCount + 1));
	m_List.SetItemText(iCount, 1, _T("ɱ����"));
	m_List.SetItemText(iCount, 2, _T("�������ݴ�"));
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
 *	ȫѡ
 */
void CAutoBase::OnSelAll() 
{
	m_List.SetCheckAll();

	m_iErr1 = 0;
	m_iErr2 = 1;

	// ������ѡ
	int iCount = m_List.GetItemCount();
	for(int i = iCount - 3; i < iCount; ++i)
		m_List.SetCheck(i, FALSE);

	UpdateData(FALSE);
}

/*
 *	ȫ��
 */
void CAutoBase::OnClearAll() 
{
	m_List.SetCheckAll(FALSE);

	m_iErr1 = 0;
	m_iErr2 = 0;

	UpdateData(FALSE);
}

/*
 *	Ĭ��
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
 *	����ѡ��״̬
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
 *	����ѡ��״̬
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
 *	ɱ��Ч��
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
	
	// �ݴ�������
	if(m_iErr1 > m_iErr2)
	{
		AfxMessageBox(_T("�ݴ�Χ���ô���"));
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
