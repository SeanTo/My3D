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
	
	m_List.InsertColumn(0,"���",LVCFMT_LEFT,43);    //����б���
	m_List.InsertColumn(1,"ע��",LVCFMT_CENTER,43);
	m_List.InsertColumn(2,"�ļ�",LVCFMT_LEFT,600);

	m_strResult = strTip = CString(_T("������ʾ:"))
		+ _T("\r\n����������ļ�(���999��)")
		+ _T("\r\n������������϶���ѡ��ʽ")
		+ _T("\r\n��������סCTRL�����������ѡ�����ļ�")
		+ _T("\r\n�����ڹ�ѡ��Ҫ���뽻���Ĵ��")
		+ _T("\r\n�����������ݴ�Χ")
		+ _T("\r\n�������󽻼�")
		+ _T("\r\n�����ݱ���")
		+ _T("\r\n\r\n�����ݴ�����Ϊ: 0 <= �ݴ� <= �����-1")
		+ _T("\r\n������õ��ǲ������")
		+ _T("\r\n\r\n�ļ��б�")
		+ _T("\r\n����˫�� = �鿴�ļ�ԭʼ����")
		+ _T("\r\n�����Ҽ� = �鿴���ļ������Ĵ�׺�")
		+ _T("\r\n\r\n����ļ���Ϊ.txt�ı�(���±���ʽ):")
		+ _T("\r\n�������ı���ʽ���⣬ÿ��ע����Ҫ��̶�")
		+ _T("\r\n������֧������ָ���(������)�����޷ָ���")
		+ _T("\r\n�������ָ���λ�����⣬��һ��Ҫ3������һ��")
		+ _T("\r\n�����۵��ļ��в��ܳ��ֳ���������İ������")
		+ _T("\r\n������ĳЩ������ɵĴ�׺��й���˵����Ϣ")
		+ _T("\r\n������������к��������(������)����ɾ��")
		+ _T("\r\n\r\n����������������ɵĴ�ף�����˫���ļ��б�鿴������")
		+ _T("�Ƿ����Ҫ�󣬿���ͨ������� [�༭] ��ť�����޸�")
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
	// ��ȡ�б�ǰѡ�����
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
 *	�������
 */
void CIntersection::OnLclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	EnEdit();
}

/*
 *	�Ҽ��б��¼����鿴��׺���
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
 *	˫���б��¼����鿴�ļ�����
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
			m_strResult = _T("���ļ�����!");
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
 *	����ļ�
 */
void CIntersection::OnSelFile() 
{
	// TODO: Add extra cleanup here
	static CString strLastPath(_T(""));
	strLastPath = WND::SelectMutiFile(arrFiles, strLastPath, _T("�ı��ļ�(*.txt)\0*.txt"));

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
		m_List.SetItemText(iCount, 2, _T("���ô�ױ༭������"));
		++iCount;
	}
	
	m_strResult = CString(_T("���д���ļ� ")) + EMFC::Int2Str(iFiles) + _T(" ��");
	
	EnEdit();
	UpdateData(FALSE);
}

/*
 *	ȫ��ѡ��
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
 *	��תѡ��
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
 *	ɾ��δѡ
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

	m_strResult = CString(_T("���д���ļ� ")) + EMFC::Int2Str(iFiles) + _T(" ��");

	EnEdit();
	UpdateData(FALSE);
}

/*
 *	�������
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
 *	�༭�ļ�
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
 *	����
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
 *	������
 */
void CIntersection::OnSaveResult()
{
	CSaveOption dlg;
	dlg.m_bSaveAndOpen = (pApp->iSaveAndOpen > 0);
	dlg.DoModal();

	EnEdit();
}

/*
 *	�ر�
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
 *	���ļ����ش��
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
 *	�󽻼�
 */
void CIntersection::OnOK() 
{
	// TODO: Add extra cleanup here
	UpdateData(TRUE);
	OnClearResult();
	
	int err, num;
	
	// �ݴ�������
	if(m_iErr1 > m_iErr2)
	{
		m_strResult = _T("�ݴ��������: ���� > ����");
		UpdateData(FALSE);
		return;
	}

	int iCount = m_List.GetItemCount();
	int iFiles = arrFiles.GetSize();
	
	// ����б��ļ��Ƿ�Ϊ��
	if( 0 == iFiles )
	{
		m_strResult = _T("����ļ��б�Ϊ��...");
		UpdateData(FALSE);
		return;
	}

	CUIntArray aMergeBase; // ��ײ���
	aMergeBase.RemoveAll();
	int cnt;
	
	// �����ļ�����
	int iSelected = 0;		// �ѹ�ѡ�Ĵ����
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

	// �������ô��
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

	// �����������
	EMFC::SortArray(aMergeBase);
	
	// �Ƿ�ѡ���
	if( 0 == iSelected )
	{
		m_strResult = _T("�빴ѡ��Ҫ���н����Ĵ��...");
		UpdateData(FALSE);
		return;
	}

	// �󽻼�
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

	// ��ʾ��Ҫ
	int iResult[3];
	for(int i = 0; i < 3; ++i)
		iResult[i] = pApp->aResult[i].GetSize();

	m_strTip = CString(_T("�������: ")) + EMFC::Int2Str(pApp->aBase.GetSize())
		+ _T(" ע(����") + EMFC::Int2Str(iResult[0])
		+ _T("������") + EMFC::Int2Str(iResult[1])
		+ _T("������") + EMFC::Int2Str(iResult[2])	+ _T(")")
		+ _T("\r\n����ѵ������������˽���б����...");


	// ��ʾ���
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
