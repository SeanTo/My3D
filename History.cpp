#include "stdafx.h"
#include "History.h"

#include "..\Share\WND.h"
#include "..\Share\MyDT.h"

const CString CHistory::m_strDataName[] = {
	_T("3D.dat"), _T("P5.dat"),
	_T("3D.bak"), _T("P5.bak"),
	_T("����3D"), _T("���������")
};

/*
 *	���ı��ļ�������ʷ��¼���ⲿ����
 */
int CHistory::LoadFile3DToArray(const CString &strFile, BOOL bIs3D, CUIntArray &aHistory)
{
	aHistory.RemoveAll();
	
	CStdioFile fin;
	if( !fin.Open(strFile, CFile::modeRead | CFile::typeText ) )
	{
		AfxMessageBox(_T("���ļ�����!\n") + strFile);
		return 0;
	}
	
	int iCntErr = 0; // ��������
	int iCntOK = 0;  // ��ȷ����
	
	CString strLine;
	CString str1;
	CString str2;

	while(fin.ReadString(strLine))
	{
		strLine.TrimLeft();
		strLine.TrimRight();
		
		if(strLine.GetLength() >= (bIs3D ? 10 :12))
		{
			if(bIs3D)
				str2 = strLine.Right(3);
			else
				str2 = strLine.Right(5).Left(3);
			
			aHistory.Add(_ttoi(str2));
			++iCntOK;
		}
	}
	fin.Close();
	
	return iCntOK;
}

/*
 *	���ı��ļ�������ʷ��¼
 */
int CHistory::LoadFromFile(const CString &strFile, BOOL bIs3D /* = FALSE */)
{
	m_aPeriod.RemoveAll();
	m_aNum.RemoveAll();
	m_bIs3D = bIs3D;

	CStdioFile fin;
	if( !fin.Open(strFile, CFile::modeRead | CFile::typeText ) )
	{
		AfxMessageBox(_T("�޷�����ʷ��¼�ļ�!\n") + strFile);
		return 0;
	}

	int iCntErr = 0; // ��������
	int iCntOK = 0;  // ��ȷ����
	
	CString strLine;
	CString str1;
	CString str2;
	
	while(fin.ReadString(strLine))
	{
		strLine.TrimLeft();
		strLine.TrimRight();
		
		if(strLine.GetLength() >= (Is3D() ? 10 :12))
		{
			str1 = strLine.Left(7);
			str2 = strLine.Right(Is3D() ? 3 : 5);
			
			if( CheckPeriod(str1) && CheckNum(str2, Is3D()))
			{
				m_aPeriod.Add(_ttoi(str1));
				m_aNum.Add(_ttoi(str2));
				++iCntOK;
			}
			else
				++iCntErr;
		}
	}
	fin.Close();
	
	return iCntOK;
}

/*
 *	������ʷ���ı��ļ�
 */
int CHistory::SaveToFile(const CString &strFile) const
{

	CStdioFile fo;
	if( !fo.Open(strFile, CFile::modeCreate | CFile::modeWrite | CFile::typeText ) )
	{
		AfxMessageBox(_T("���ļ�����!\n") + strFile);
		return 0;
	}

	int i = 0;
	int iCount = GetCount();
		
	while(i < iCount)
	{
		if(Is3D())
			fo.WriteString(GetPeriodStr(i) + CString(_T("   ")) + GetNumStr(i) + CString(_T("\n")));
		else
			fo.WriteString(GetPeriodStr(i) + CString(_T("   "))	+ EMFC::Int2Str(m_aNum[i], _T("%05d")) + CString(_T("\n")));

		++i;
	}
	
	fo.Close();
		
	return i;
}

int CHistory::GetPeriod(int iSequence) const
{
	ASSERT( iSequence < GetCount() );

	if( iSequence >= 0)
		return m_aPeriod[iSequence];

	// ����
	int iPeriod = m_aPeriod[0] + 1;
	int iYear = iPeriod / 1000; // ���һ�ڵ��ں�
	int iMaxPeriod = MyDT::IsLeapYear(iYear) ? 366 : 365;

	if( iPeriod % 1000 > iMaxPeriod)
		iPeriod += 1000 - iMaxPeriod;
	
	return iPeriod;
}

int CHistory::GetNum(int iSequence) const
{
	ASSERT( iSequence < GetCount() );
	
	int n = m_aNum[iSequence];
	n = Is3D() ? n : n / 100;
	return n;
}

/*
 * �������������λ
 */
int CHistory::P5Tail(int iSequence) const
{
	ASSERT( iSequence < GetCount() && !Is3D());

	return m_aNum.GetAt(iSequence) % 100;
}

/*
 * ���ҿ������룬����������δ�ҵ����� -1
 */
int CHistory::FindNum(int iNum, int iStart /* = 0 */) const
{
	ASSERT( iNum < 1000 );
	int iCount = GetCount();
	if( IsNull() || iStart >= iCount)
		return -1;

	for(int i = iStart; i < iCount; ++i)
	{
		if(GetNum(i) == iNum)
			return i;
	}

	return -1;
}

VOID CHistory::AddRecord(int iPeriod, int iNum)
{
	m_aPeriod.InsertAt(0, iPeriod);
	m_aNum.InsertAt(0, iNum);
}

VOID CHistory::DelRecord(int iSequence)
{
	ASSERT( iSequence < GetCount() );

	m_aPeriod.RemoveAt(iSequence);
	m_aNum.RemoveAt(iSequence);
}

/*
 * ��λ������©ͳ��
 */
int CHistory::StatMiss(int iStart, int iBit, int n)
{
	int iCount = GetCount();
	if( 0 == iCount || iStart >= iCount || iBit > 2 )
		return -1;

	int num;
	int iMiss = 0;

	for(int i = iStart; i < iCount; ++i)
	{
		num = GetCNum(i)[iBit];

		if(n == num)
			break;

		++iMiss;
	}

	return iMiss;
}

/*
 * ����������©ͳ��
 */
int CHistory::StatMiss(int iStart, C3D CNum)
{
	int cnt = 0;

	for(int i = 0; i < 3; ++i)
		cnt += StatMiss(iStart, i, CNum[i]);

	return cnt;
}

/*
 * ����Ͳ����©
 */
CString CHistory::MissTwoNum(int iPeriod, int iStart /*= 0*/, int iType /* = 0 */)
{
	ASSERT(iPeriod > 0 && iPeriod < 5 && 0 <= iType && iType <= 2);
	
	CString str = _T("");
	int iCount = GetCount();
	
	if(0 == iCount || iStart >= iCount)
		return str;

	iCount = iPeriod + iStart < iCount ? iPeriod + iStart : iCount;

	CUIntArray aRes;
	C3D CNum;

	for(int i = iStart; i < iCount; ++i)
	{
		if(0 == iType)
			CNum = GetCNum(i).TwoNumSpan();
		else if(1 == iType)
			CNum = GetCNum(i).TwoNumSum();
		else if(2 == iType)
			CNum = GetCNum(i).TwoNumMul();

		aRes.Add(CNum[0]);
		aRes.Add(CNum[1]);
		aRes.Add(CNum[2]);
	}

	for(int i = 0; i < 10; ++i)
	{
		if( !EMFC::IsInArray((UINT)i, aRes) )
			str += (TCHAR)(_T('0') + i);
	}

	return str;
}

/*
 * ���ڿ����ĺ���
 */
VOID CHistory::NearNum(CUIntArray &aNear, int iStart /* = 0 */, int iCount /* = 5 */)
{
	aNear.RemoveAll();

	int iCnt = GetCount();
	if(iStart > iCnt)
		return;

	iCount += iStart;
	iCount = iCount < iCnt ? iCount : iCnt;

	C3D CNum;
	for(int i = iStart; i < iCount; ++i)
	{
		CNum = GetCNum(i);
		aNear.Add(CNum.Hun());
		aNear.Add(CNum.Ten());
		aNear.Add(CNum.Ent());
	}
}

VOID CHistory::HotNum(int st, CString &sHot, CString &sWarm, CString &sCool, int iCnt /*= 5*/)
{
	CUIntArray aHot, aWarm, aCool;
	
	int iCountHistory = GetCount();
	if(0 == iCountHistory || st == (UINT)iCountHistory)
		return;

	// ȡ�ý��ڸ�����
	CUIntArray aNear;
	NearNum(aNear, st, iCnt);
	EMFC::SortArray(aNear, FALSE);
	
	// ����ͳ��
	int num, loopCnt = aNear.GetSize();
	for(int i = 0; i < 10; ++i)
	{
		num = 0;
		for(int j = 0; j < loopCnt; ++j)
		{
			if(aNear[j] == i)
				++num;
		}
		
		if(num > 2) // ��
			aHot.Add(i);
		else if(num < 2) // ��
			aCool.Add(i);
		else // ��
			aWarm.Add(i);
	}

	sHot = EMFC::PrintArray(aHot);
	sWarm = EMFC::PrintArray(aWarm);
	sCool = EMFC::PrintArray(aCool);
}

/*
 *	ͳ��������
 *  iPeriods ͳ������
 *  arrAMP ͳ�ƽ�����������ɸߵ�������
 *  bit 0����λ��1��ʮλ��2����λ
 *  st ��ʼ����
 */
VOID CHistory::StatAMP(int iPeriods, CUIntArray &arrAMP, int iBit, int st /* = 0 */)
{
	ASSERT(iBit < 3);

	arrAMP.RemoveAll();
	for(int i = 0; i < 10; ++i)
		arrAMP.Add(0);
	
	int iCount = GetCount();
	iPeriods += st;
	iPeriods = iPeriods > iCount ? iCount : iPeriods;
	
	// ��һ������
	int next, C[10];
	next =GetCNum(st)[iBit];
	
	for(int i = 0; i < 10; ++i)
		C[i] = (next + i) % 10;
	
	int T[10];
	ZeroMemory(T, sizeof(int) * 10);

	int num, A[10];
	for(int i = st + 1; i < iPeriods; ++i)
	{
		num = GetCNum(i)[iBit];
		
		for(int j = 0; j < 10; ++j)
		{
			A[j] = (num + j) % 10;
			if(A[j] == next)
				++T[j];
		}
		
		next = num;
	}
	
	for(int i = 0; i < 10; ++i)
	{
		num = 0;
		for(int j = 0; j < 10; ++j)
		{
			if(T[j] > T[num])
				num = j;
		}
		
		T[num] = -1;
		arrAMP[i] = C[num];
	}
}

/*
 *	����һ����׵���ʷ�н����
 *  aSrc �������
 *  nPeriodCnt ��������
 *  aRes ���ؽ��
 *  [0] ���ע��
 *  [1] ��������
 *  [2] �����н�����
 *  [3] ʵ���н�����
 *  [4] ��ǰ��©
 *��[5] �����©
 *  [6] �������
 *  [7...] �н�����
 */
BOOL CHistory::Success(const CUIntArray &aSrc, int iPeriodCnt, CUIntArray &aRes)
{
	aRes.RemoveAll();
	
	int iCountHistory = GetCount();
	if(0 == iCountHistory || 0 == aSrc.GetSize())
		return FALSE;

	int iRecord = aSrc.GetSize();							// ���ע��
	int iCyc = (int)(1000.0 * 100.0 / (float)iRecord);		// ��������(100��)
	int iTheory = iRecord * iPeriodCnt / 1000;	// �����н�����
	int iFact = 0;								// ʵ���г�����
	int iCurErr = 0;							// ��ǰ��©
	int iMaxErr = 0;							// �����©
	int iMaxOK = 0;								// �������
	
	if(0 == iRecord)
		return FALSE;

	aRes.Add(iRecord);
	aRes.Add(iCyc);
	aRes.Add(iTheory);
	aRes.Add(iFact);
	aRes.Add(iCurErr);
	aRes.Add(iMaxErr);	
	aRes.Add(iMaxOK);

	int iNum;
	iPeriodCnt = iPeriodCnt < iCountHistory ? iPeriodCnt : iCountHistory;
	for(int i = 0; i < iPeriodCnt; ++ i)
	{
		iNum = GetNum(i);
		
		if( EMFC::IsInArray((UINT)iNum, aSrc) )
		{
			aRes.Add(i); // ��¼�н�����
			
			++iFact;
			++iMaxOK;
			
			// �����©
			if((UINT)iMaxErr > aRes.GetAt(5))
				aRes.SetAt(5, iMaxErr);

			iMaxErr = 0;
		}
		else
		{
			++iMaxErr;
			
			// �������
			if((UINT)iMaxOK > aRes.GetAt(6))
				aRes.SetAt(6, iMaxOK);

			iMaxOK = 0;
		}
	}

	// ʵ���н�
	aRes.SetAt(3, iFact);

	// ��ǰ��©
	aRes.SetAt(4, (0 == iFact ? iPeriodCnt : aRes.GetAt(7)));

	// �����©
	if((UINT)iMaxErr > aRes.GetAt(5))
		aRes.SetAt(5, iMaxErr);

	// �������
	if((UINT)iMaxOK > aRes.GetAt(6))
		aRes.SetAt(6, iMaxOK);

	return TRUE;
}

/*
 *	���Һ��� CNum ��3�����зֱ���ֵĴ���
 */
C3D CHistory::Find3Sect(const int iNum, const CString *pSect) const
{
	C3D CNum(iNum);
	int iCnt = 0;

	for(int i = 0; i < 3; ++i)
	{	
		iCnt = iCnt * 10 + CNum.CountInStr( *(pSect + i) );
	}
	CNum = iCnt;

	return CNum;
}

/*
 * ��ʽ����
 * �����źͱ�ѡ����ÿ3���г��ֵ�����ͬ�Ĵ���
 */
int CHistory::Filter3Sect(const int iNum, int iLast, const CString *pSect /* = FIXED_SECT_STR */, const int iSects /* = 15 */) const
{
	C3D CNum1, CNum2;
	int iSame = 0;

	for(int i = 0; i < iSects; ++i)
	{
		CNum1 = Find3Sect(iLast, pSect + 3 * i);
		CNum2 = Find3Sect(iNum, pSect + 3 * i);

		iSame += ( 3 == CNum1.CountSame(CNum2) );
	}

	return iSame;
}

int CHistory::FilterAutoBase(const int iNum, bitset<32> bSel, int iHistory /* = 0 */, int iErr1 /* = 0 */, int iErr2 /* = 0 */)
{
	ASSERT( 0 <= iNum && iNum <= 999 );

	C3D CNum = iNum;
	C3D CNumHistory = GetCNum(iHistory);
	C3D CNum1, CNum2;
	
	int iCntHistory = GetCount();
	int iChk, iCnt;

	int iDec = 0;
	
#ifdef _UNRESTRICT2_
	if( WND::IsCharDown(_T('1')) )
		iDec = 1;
#endif // _UNRESTRICT2_

	int err = 0, iCount = 0;
	
	// ��̬����
	if( true == bSel[iCount])
	{
		if( 0 <= FilterManual(iNum, iHistory, 0) )
		{
			++err;
			if( err > iErr2 )
				return iCount + 1;
		}
	}
	++iCount;
	
	// �̶���ʽɱ��1
	if( true == bSel[iCount])
	{
		if( Filter3Sect(iNum, CNumHistory) > 1 - iDec)
		{
			++err;
			if( err > iErr2 )
				return iCount + 1;
		}
	}
	++iCount;
	
	// �̶���ʽɱ��2
	if( true == bSel[iCount])
	{
		if( Filter3Sect(iNum, CNumHistory) > 2 - iDec )
		{
			++err;
			if( err > iErr2 )
				return iCount + 1;
		}
	}
	++iCount;
	
	// ����̳�
	if( true == bSel[iCount])
	{
		if( CNum.CountSame(CNumHistory) > 1 )
		{
			++err;
			if( err > iErr2 )
				return iCount + 1;
		}
	}
	++iCount;
	
	// 012·�̳�
	if( true == bSel[iCount])
	{
		CNum1 = CNumHistory.AC3ModNum();
		CNum2 = CNum.AC3ModNum();
		
		if( CNum1.CountSame(CNum2) > 2 )
		{
			++err;
			if( err > iErr2 )
				return iCount + 1;
		}
	}
	++iCount;
	
	// ��̬��ת
	if( true == bSel[iCount])
	{
		int cnt = 0;

		// ��ż
		CNum1 = CNumHistory.OddModNum();
		CNum2 = CNum.OddModNum();
		cnt += ( 0 == CNum1.CountSame(CNum2) );

		// ��С
		CNum1 = CNumHistory.LargeModNum();
		CNum2 = CNum.LargeModNum();
		cnt += ( 0 == CNum1.CountSame(CNum2) );

		// �ʺ�
		CNum1 = CNumHistory.PrimeModNum();
		CNum2 = CNum.PrimeModNum();
		cnt += ( 0 == CNum1.CountSame(CNum2) );

		if( cnt > 1 )
		{
			++err;
			if( err > iErr2 )
				return iCount + 1;
		}
	}
	++iCount;
	
	// �����ֵ 2-7
	if( true == bSel[iCount]&& (2 > CNum.Ave() || CNum.Ave() > 7) )
	{
		++err;
		if( err > iErr2 )
			return iCount + 1;
	}
	++iCount;
	
	// ������
	if( true == bSel[iCount])
	{
		if( -1 != FilterTriangle(CNum, iHistory, 1, 1, 3) )
		{
			++err;
			if( err > iErr2 )
				return iCount + 1;
		}
	}
	++iCount;

	// �ȳ����෨
	if( true == bSel[iCount])
	{
		int A[3];
		CNum.Swing(CNumHistory, A);
		
		if( A[0] == A[1] || A[1] == A[2] || A[2] == A[0] )
		{
			++err;
			if( err > iErr2 )
				return iCount + 1;
		}
	}
	++iCount;

	// �������
	if( true == bSel[iCount])
	{
		CUIntArray arr;
		GetNearCourage(10, arr, iHistory);
		
		int e[3] = {0, 0, 0};
		CString str, strFmt = _T("%03d"), strRange = _T("123");
		
		for(int i = 0; i < arr.GetSize(); ++i)
		{
			if(CNum.IsG6())
			{
				str = EMFC::Int2Str(arr[i], strFmt);
				e[i/10] += ! EMFC::IsInArray(CNum.CountInStr(str, TRUE), strRange);
			}
		}

		const int E = 5;
		
// 		if( e[0] > E || e[1] > E || e[2] > E )
		if( e[0] + e[1] + e[2] > 16)
		{
			++err;
			if( err > iErr2 )
				return iCount + 1;
		}
	}
	++iCount;

	// ====================
	// ��ɢ�㷨
	// ====================
			
	// ������粻����4��
	if( true == bSel[iCount] )
	{
		iChk = 3;

		CNum1 = CNum.TwoNumSpan();
		
		for(int j = 0; j < 3; ++j)
		{
			iCnt = 0;
			for(int i = 0; i < iChk; ++i)
			{
				if( iHistory + i >= iCntHistory )
					break;
				
				CNum2 = GetCNum(iHistory + i).TwoNumSpan();
				if( CNum1[j] == CNum2[j] )
					++iCnt;
				else
					break;
			}
			if( iChk == iCnt )
			{
				++err;
				if( err > iErr2 )
					return iCount + 1;
			}
		}
	}
	++iCount;
	
	// ������Ͳ�����3��
	if( true == bSel[iCount] )
	{
		iChk = 2;
		
		CNum1 = CNum.TwoNumSum();
		for(int j = 0; j < 3; ++j)
		{
			iCnt = 0;
			for(int i = 0; i < iChk; ++i)
			{
				if( iHistory + i >= iCntHistory )
					break;
				
				CNum2 = GetCNum(iHistory + i).TwoNumSum();
				if( CNum1[j] == CNum2[j] )
					++iCnt;
				else
					break;
			}
			if( iChk == iCnt )
			{
				++err;
				if( err > iErr2 )
					return iCount + 1;
			}
		}
	}
	++iCount;
	
	// �������������3��(0����)
	if( true == bSel[iCount] )
	{
		iChk = 2;
		CNum1 = CNum.TwoNumMul();
		for(int j = 0; j < 3; ++j)
		{
			if( 0 == CNum1[j] )
				continue;

			iCnt = 0;
			for(int i = 0; i < iChk; ++i)
			{
				if( iHistory + i >= iCntHistory )
					break;
				
				CNum2 = GetCNum(iHistory + i).TwoNumMul();
				if( CNum1[j] == CNum2[j] )
					++iCnt;
				else
					break;
			}
			if( iChk == iCnt )
			{
				++err;
				if( err > iErr2 )
					return iCount + 1;
			}
		}
	}
	++iCount;
	
	// ��Ȳ�����3��
	if( true == bSel[iCount] )
	{
		iChk = 2;

		iCnt = 0;
		for(int i = 0; i < iChk; ++i)
		{
			if( CNum.Span() == GetCNum(iHistory + i).Span() )
				++iCnt;
			else
				break;
		}
		if( iChk  == iCnt )
			return iCount + 1;
	}
	++iCount;
	
	// ��β������3��
	if( true == bSel[iCount] )
	{
		iChk = 2;
		iCnt = 0;

		for(int i = 0; i < iChk; ++i)
		{
			if( iHistory + i >= iCntHistory )
				break;
			
			if( CNum.Tail() == GetCNum(iHistory + i).Tail() )
				++iCnt;
			else
				break;
		}
		if( iChk  == iCnt )
		{
			++err;
			if( err > iErr2 )
				return iCount + 1;
		}
	}
	++iCount;
	
	// ��ż��̬������3��
	if( true == bSel[iCount] )
	{
		iChk = 2;
		iCnt = 0;
		
		for(int i = 0; i < iChk; ++i)
		{
			if( iHistory + i >= iCntHistory )
				break;
			
			if( CNum.OddModality() == GetCNum(iHistory + i).OddModality() )
				++iCnt;
			else
				break;
		}
		if( iChk  == iCnt )
		{
			++err;
			if( err > iErr2 )
				return iCount + 1;
		}
	}
	++iCount;
	
	// ��С��̬������3��
	if( true == bSel[iCount] )
	{
		iChk = 2;
		iCnt = 0;

		for(int i = 0; i < iChk; ++i)
		{
				if( iHistory + i >= iCntHistory )
					break;
				
				if( CNum.LargeModality() == GetCNum(iHistory + i).LargeModality() )
					++iCnt;
				else
					break;
		}
		if( iChk  == iCnt )
		{
			++err;
			if( err > iErr2 )
				return iCount + 1;
		}
	}
	++iCount;
	
	// �ʺ���̬������3��
	if( true == bSel[iCount] )
	{
		iChk = 2;
		iCnt = 0;

		for(int i = 0; i < iChk; ++i)
		{
			if( iHistory + i >= iCntHistory )
				break;
			
			if( CNum.PrimeModality() == GetCNum(iHistory + i).PrimeModality() )
				++iCnt;
			else
				break;
		}
		if( iChk  == iCnt )
		{
			++err;
			if( err > iErr2 )
				return iCount + 1;
		}
	}
	++iCount;
	
	// 012·��3������
	if( true == bSel[iCount] )
	{
		iChk = 2;
		iCnt = 0;
		
		CNum1 = CNum;
		for(int i = 0; i < iChk; ++i)
		{
			if( iHistory + i >= iCntHistory )
				break;
			
			CNum2 = GetCNum(iHistory + i);
			
			int v = abs( CNum1.AC3Modality() - CNum2.AC3Modality() );
			
			if( 26 == v || v <= 1 )
				++iCnt;
			else
				break;
			
			CNum1 = CNum2;
		}
		if( iChk == iCnt )
		{
			++err;
			if( err > iErr2 )
				return iCount + 1;
		}
	}
	++iCount;
	
	// б��3������2��
	if( true == bSel[iCount] )
	{
		iChk = 3;
		iCnt = 0;

		CNum1 = CNum;
		for(int i = 0; i < iChk; ++i)
		{
			if( iHistory + i >= iCntHistory )
				break;
			
			CNum2 = GetCNum(iHistory + i);
			
			if( 3 == CNum2.CountLeft(CNum1) + CNum2.CountRight(CNum1))
				++iCnt;
			else
				break;
			
			CNum1 = CNum2;
		}
		if( iChk - 1 == iCnt )
		{
			++err;
			if( err > iErr2 )
				return iCount + 1;
		}
	}
	++iCount;
	
	// ɱ����
	if( true == bSel[iCount])
	{
		if( CNum.IsG1() )
		{
			return iCount + 1;
		}		
	}
	++iCount;
	
	// ɱ����
	if( true == bSel[iCount])
	{
		if( CNum.IsG3() )
		{
			return iCount + 1;
		}
	}
	++iCount;
	
	// ɱ����
	if( true == bSel[iCount])
	{
		if( CNum.IsG6() )
		{
			return iCount + 1;
		}
	}
	++iCount;
	
	// �ݴ����޼��
	if( err < iErr1 )
		return -1;

	return 0;
}

/*
 *	�����Ƿֽ�
 */
int CHistory::TriangleCourage(CStringArray &arrTriangle, int iHistory /* = 0 */, BOOL bUp/* = TRUE*/)
{
	arrTriangle.RemoveAll();

	CString str = bUp ? _T("0123456789") : _T("9876543210");
	CString ss;

	C3D CNum  = GetCNum(iHistory);
	C3D CNum2 = CNum.ToG6(bUp);

	if( CNum.IsG6() )
	{
		str.Delete(bUp ? CNum2[2] : 9 - CNum2[2]);
		str.Delete(bUp ? CNum2[1] : 9 - CNum2[1]);
		str.Delete(bUp ? CNum2[0] : 9 - CNum2[0]);
		str = CNum.ToString() + str;
	}
	else if( CNum.IsG3() )
	{
		str.Delete(bUp ? CNum2[2] : 9 - CNum2[2]);
		str.Delete(bUp ? CNum2[0] : 9 - CNum2[0]);

		ss = CNum.ToString();
		for(int i = 0; i < 3; ++i)
		{
			if(CNum[i] == CNum2[1])
			{
				ss.Delete(1);
				break;
			}
		}
		str = ss + str;
	}
	else
	{
		str.Delete(bUp ? CNum2[0] : 9 - CNum2[0]);
		str += CNum.ToString().Left(1) + str;
	}

// 	int num;
// 	for(int j = 0; j < 3; ++j)
// 	{
// 		num = str.Find(EMFC::Int2Str(CNum[j]), 0);
// 		if( -1 != num )
// 			str.Delete(num);
// 	}
// 
// 	if( CNum.IsG6() )
// 		ss = CNum.ToString();
// 	else if( CNum.IsG1() )
// 		ss == EMFC::Int2Str(CNum.Hun());
// 	else
// 	{
// 		ss = CNum.ToString();
// 		num = 1 - ( CNum.Hun() == CNum.Ten() || CNum.Hun() == CNum.Ent() );
// 		ss.Delete(num);
// 	}
// 	str = ss + str;

	// ������
	ss = str.Left(6);
	arrTriangle.Add(ss);
	// ������
	ss = str.Mid(1, 1) + str.Mid(3, 2) + str.Mid(6, 3);
	arrTriangle.Add(ss);
	// ������
	ss = str.Mid(2, 1) + str.Mid(4, 2) + str.Right(3);
	arrTriangle.Add(ss);

	// ������
	ss = str.Left(3) + str.Mid(4, 1);
	arrTriangle.Add(ss);
	// ������
	ss = str.Mid(1,1) + str.Mid(3, 2) + str.Mid(7, 1);
	arrTriangle.Add(ss);
	// ������
	ss = str.Mid(2, 1) + str.Mid(4, 2) + str.Mid(8, 1);
	arrTriangle.Add(ss);

	// �����
	ss = str.Left(2) + str.Mid(3, 1) + str.Mid(6, 1);
	arrTriangle.Add(ss);
	// �Һ���
	ss = str.Left(1) + str.Mid(2, 1) + str.Mid(5, 1) + str.Right(1);
	arrTriangle.Add(ss);
	// �º���
	ss = str.Right(4);
	arrTriangle.Add(ss);

	return arrTriangle.GetSize();
}

/*
 *	�����ǹ���
 */
int CHistory::FilterTriangle(const int n, int iHistory /* = 0 */, int iErr /* = 1 */, int iCnt1 /* = 1 */, int iCnt2 /* = 3 */)
{
	ASSERT( 0 <= n && n <= 999);

	if( ! C3D(n).IsG6() )
		return -1;
	
	CStringArray arrUp, arrDn;

	TriangleCourage(arrUp, iHistory, TRUE);
	TriangleCourage(arrDn, iHistory, FALSE);

	const C3D CNum(n);
	int cnt, err;
	int iCount = 0;

	// ������
	err = 0;
	for(int i = 0; i < 3; ++i)
	{
		cnt = CNum.CountInStr(arrUp[i], TRUE);
		err += ( cnt < 1 || cnt > 2 );

		cnt = CNum.CountInStr(arrDn[i], TRUE);
		err += ( cnt < 1 || cnt > 2 );
	}
	if( err > 2 )
		return iCount;
	++iCount;

	// ����
	err = 0;
	for(int i = 0; i < 3; ++i)
	{
		cnt = CNum.CountInStr(arrUp[i+3], TRUE);
		err += ( cnt > 2 );

		cnt = CNum.CountInStr(arrDn[i+3], TRUE);
		err += ( cnt > 2 );
	}
	if( err > 1 )
		return iCount;
	++iCount;
	
	// б��
	err = 0;
	for(int i = 0; i < 3; ++i)
	{
		cnt = CNum.CountInStr(arrUp[i+6], TRUE);
		err += ( cnt > 2 );
		
		cnt = CNum.CountInStr(arrDn[i+6], TRUE);
		err += ( cnt > 2 );
	}
	if( err > 1 )
		return iCount;
	++iCount;
	
	return -1;
}

CString CHistory::PeriodTail5Courage(int n /* = 0 */)
{
/*
	switch( n )
	{
	case 0:	str = _T("01289");	break;
	case 1:	str = _T("12390");	break;
	case 2:	str = _T("23401");	break;
	case 3:	str = _T("34512");	break;
	case 4:	str = _T("45623");	break;
	case 5:	str = _T("56734");	break;
	case 6:	str = _T("67845");	break;
	case 7:	str = _T("78956");	break;
	case 8:	str = _T("89067");	break;
	case 9:	str = _T("90178");	break;
	}
*/

	CString str = _T("0123456789");
	str = str.Mid(n, n <= 7 ? 3 : 10 - n) + str.Mid(0, n <= 7 ? 0 : n - 7)
		+ str.Mid((n+8) % 10, 1 + (1 != n)) + ((1 == n) ? _T("0") : _T(""));

	return str;
}

/*
 *	ɱ�����Ƽ�
 */
int CHistory::Kill2Nums(CUIntArray &arrTwoNums, int iHistory /* = 0 */)
{
	arrTwoNums.RemoveAll();

	int iCount = GetCount();
	if(iHistory >= iCount)
		return 0;

	int i = iHistory, n;
	C3D CNum = GetNum(i);
	CString str;

	// �ں�ǰ������λ
	str = GetPeriodStr(i - 1);
	n = _ttoi(str.Right(3).Left(2));
	arrTwoNums.Add(n);
	n = _ttoi(str.Right(2));
	arrTwoNums.Add(n);

	// ������ʮλ���
	if(i + 1 < iCount)
	{
		n = CNum.Ten() * 10;
		n += GetCNum(i + 1).Ten();
		arrTwoNums.Add(n);
	}

	// ���ڿ����Ŵ���С������
	n = (CNum.Max() - CNum.Mid()) * 10 + (CNum.Mid() - CNum.Min());
	arrTwoNums.Add(n);
	
	// ���ڸ�λ���β�����
	n = CNum.Ent() * 10 + CNum.Tail();
	arrTwoNums.Add(n);
	
	// ���ڿ����ź����Ӧ���
	int d[] = {8, 5, 2, 7, 4, 1, 9, 6, 5, 0};
	for(int j = 0; j < 3; ++j)
	{
		n = CNum[j];
		n = n * 10 + d[n];
		arrTwoNums.Add(n);
	}

	return arrTwoNums.GetSize();
}

/*
 *	ɱ���Ƽ�
 */
int CHistory::Kill1Nums(CUIntArray &arrOneNums, int iHistory /* = 0 */)
{
	arrOneNums.RemoveAll();
	
	C3D CNum;
	CString str;
	int i = iHistory, n;

	CNum = GetCNum(i);

	// �����ɱ��
	int dd[] = { 0, 8, 6, 4, 7, 9, 1, 2, 4, 6 };
	n = dd[CNum.Hun()];
	arrOneNums.Add(n);

	// ��λ/��λ * 3��ȡβ��
	if( CNum.Ent() != 0 )
	{
		n = (int)(CNum.Hun() * 1.0 / CNum.Ent() * 3.0) % 10;
		arrOneNums.Add(n);
	}
	else if( CNum.Ten() != 0 )
	{
		n = (int)(CNum.Hun() * 1.0 / CNum.Ten() * 3.0) % 10;
		arrOneNums.Add(n);
	}
	else
		arrOneNums.Add(-1);

	// ��λ * 7 + 7��ȡβ��
	n = (CNum.Hun() * 7 + 7) % 10;
	arrOneNums.Add(n);

	return arrOneNums.GetSize();
}

/*
 * ��λɱ�Ƽ�(1��3λ)
 */
int CHistory::Kill1NumsPos(int iHistory /* = 0 */)
{
	if(iHistory + 20 >= GetCount())
		return -1;

	// ���10�ڣ��ֱ�ȡ��ʮ���ĺ�βɱ��ʮ��
	C3D CNum1, CNum2, CNum3;
	CNum1 = GetCNum(iHistory);
	CNum2 = GetCNum(iHistory + 10);
	CNum3 = GetCNum(iHistory + 20);

	int iNum = ((CNum1.Hun() + CNum2.Hun() + CNum3.Hun()) % 10) * 100
		+ ((CNum1.Ten() + CNum2.Ten() + CNum3.Ten()) % 10) * 10
		+ ((CNum1.Ent() + CNum2.Ent() + CNum3.Ent()) % 10);
	
	return iNum;
}

/*
 * ��λɱ�Ƽ�(ÿ��3λ)
 */
int CHistory::Kill1NumsPos(CUIntArray &arrOnePos, int iHistory /* = 0 */)
{
	arrOnePos.RemoveAll();

	if(GetCount() < 21)
		return 0;

	// ���10��ȡ3�������ţ�ɱ��Ӧλ��ӵĺ�β
	if(GetCount() >= 21)
	{
		C3D CNum = Kill1NumsPos(iHistory);
		arrOnePos.Add(CNum);
	}
	
	return arrOnePos.GetSize();
}

/*
 *	�����Ƽ�
 */
int CHistory::RecommandCourage(CStringArray &arrCour, int iHistory /* = 0 */, int iBack /*= 136*/)
{
	arrCour.RemoveAll();
	CString str;
	int n;
	int iCntHistory = GetCount();

	C3D CNum( GetNum(iHistory) );

	// ���Ƽ���
	str.Empty();
	if(iHistory + iBack < iCntHistory)
	{
		str = GetCNum(iHistory + iBack).ToString();
	}
	EMFC::ExcludeSame(str);
	arrCour.Add(str);

	// *PI ��
	str = EMFC::Int2Str(CNum * 314, _T("%03d")).Left(3);
	EMFC::ExcludeSame(str);
	arrCour.Add(str);
	
	// 1����: �������(��ֵ+��λ)
	str = EMFC::Int2Str((UINT)(CNum / (float)(CNum.Sum() + CNum.Ent()) * 100.0), _T("%03d")).Left(3);
	EMFC::ExcludeSame(str);
	arrCour.Add(str);
	
	// 2����: �̶������Ӧ��
	str.Empty();
	n = CNum.Hun();
	if(0 == n)			str = _T("349");
	else if(6 == n)		str = _T("479");
	else if(8 == n)		str = _T("019");
	else
	{
		n = CNum.Ent();
		if(1 == n)			str = _T("012");
		else if(2 == n)		str = _T("138");
		else if(8 == n)		str = _T("468");
		else if(9 == n)		str = _T("048");
		else
		{
			n = CNum.Ten();
			if(6 == n)		str = _T("347");
		}
	}
	EMFC::ExcludeSame(str);
	arrCour.Add(str);
	
	// 3������2��1ż������ɱ��
	str.Empty();
	if( 2 == CNum.OddCnt() )
	{
		n = 0;
		for(int j = 0; j < 3; ++j)
		{
			if( CNum[j] & 1)
				n += CNum[j];
		}
		n %= 10;
		str = EMFC::Int2Str((n % 10) * 10 + (n + 5) % 10, _T("%02d"));
	}
	EMFC::ExcludeSame(str);
	arrCour.Add(str);

	// 4����
	// �����������ֵ����
	str.Empty();
	if( CNum.PrimeCnt() < 3)
	{
		n = 0;
		for(int j = 0; j < 3; ++j)
		{
			if( !C3D::IsPrime(CNum[j]) )
			{
				n = n * 10 + ((CNum[j] + 1) % 10);
				n = n * 10 + ((CNum[j] + 9) % 10);
			}
		}
		str = EMFC::Int2Str(n);
	}
	EMFC::ExcludeSame(str);
	arrCour.Add(str);

	// 5�뵨
	n = (GetPeriod(iHistory) + 1) % 10;
	str = PeriodTail5Courage( n );
	arrCour.Add(str);

	return arrCour.GetSize();
}

/*
 * �����ۺϵ�
*/
BOOL CHistory::GetNearCourage(int iPeriods, CUIntArray &arr, UINT nOffset /*= 0*/)
{
	if( GetCount() < iPeriods )
		return FALSE;

	arr.RemoveAll();
	arr.SetSize(iPeriods * 3);

	C3D CNum;

	for(int i = 0; i < 10; ++i)
	{
		if(i + (int)nOffset < GetCount())
		{
			CNum = GetCNum(i + nOffset);
			
			arr[i] = CNum.ToG6();
			arr[iPeriods + i] = CNum.TwoNumSpan().ToG6();
			arr[(iPeriods << 1) + i] = CNum.TwoNumSum().ToG6();
		}
	}

	return TRUE;
}

/*
 *	��̬����
 */
int CHistory::FilterManual(const int iNum, const int iHistory /* = 0 */, const int iEnErr /*= 0*/, const int iBack /* = 136 */)
{
	const int iCount = GetCount();
	if( iCount <= iHistory )
		return -2;

	const C3D CNumHistory(GetNum(iHistory));
	const C3D CNum(iNum);
	C3D CNum1;

	int iErrCnt = 0;
	int iRet = 0;

	int cnt, err, err2;
	CString str;
	CStringArray arrCour;
	CUIntArray arrKill;
	
	// 7�����õ��� + P3���ںţ��ų��մ�
	// ÿ�鵨��� 0-2���ݴ�1
	cnt = RecommandCourage(arrCour, iHistory, iBack);
	if( !Is3D() )
		arrCour.Add(GetCNum(iHistory).ToString());
	cnt = EMFC::ExcludeNull(arrCour);
	
	err2 = 1;
	err = 0;
	for(int i = 0; i < cnt; ++i)
	{
		err += 3 == CNum.CountInStr(arrCour[i], FALSE);
	}
	iErrCnt += (err > err2);
	if(iErrCnt > iEnErr)
	{
		return iRet;
	}
	err2 = 0;
	err = 0;
	for(int i = 0; i < cnt; ++i)
	{
		if( arrCour[i].GetLength() == 4 )
			err += 3 == CNum.CountInStr(arrCour[i], TRUE);
	}
	iErrCnt += (err > err2);
	if(iErrCnt > iEnErr)
	{
		return iRet;
	}
	++iRet;

	// ����
	err2 = 1;
	err = 0;
	for(int i = 131; i < 140; ++i)
	{
		if( iHistory + i >= iCount )
			break;

		if(iBack == i)
			continue;

		err += CNum.CountIn3D(GetCNum(iHistory + i), FALSE) > 2;
	}
	iErrCnt += (err > err2);
	if(iErrCnt > iEnErr)
	{
		return iRet;
	}
	++iRet;
	
	// �������
	err2 = 1;
	err = 0;
	for(int i = 1; i < 10; ++i)
	{
		if( iHistory + i >= iCount )
			break;
		
		err += CNum.CountIn3D(GetCNum(iHistory + i), FALSE) == 3;
	}
	iErrCnt += (err > err2);
	if(iErrCnt > iEnErr)
	{
		return iRet;
	}
	++iRet;
	
	// ��ȡ����ɱ���룬�ų��ظ���
	Kill2Nums(arrKill, iHistory);
	EMFC::SortArray(arrKill);
	cnt = C3D::ExcludeTwo(arrKill, TRUE);

	// ɱ���룬�ݴ�1
	err2 = 2;
	err = 0;
	for(int i = 0; i < cnt; ++i)
	{
		err += CNum.IsMember2(arrKill[i], TRUE);
	}
	iErrCnt += (err > err2);
	if(iErrCnt > iEnErr)
	{
		return iRet;
	}
	++iRet;

// 	׼ȷ�ʹ��ͣ���ʱ����
// 	// ��ȡ���ö�λɱ�룬�ݴ�1
// 	err2 = 1;
// 	cnt = Kill1NumsPos(iHistory);
// 	if( cnt > 0)
// 	{
// 		C3D CNumPos = cnt;
// 
// 		// ɱ3����λɱ���ݴ�1
// 		err = CNumPos.CountSame(iNum);
// 		iErrCnt += (err > err2);
// 		if(iErrCnt > iEnErr)
// 		{
// 			return iRet;
// 		}
// 	}
	++iRet;

	// ��������ظ�
// 	CNum1 = CNumHistory.TwoNumMul().ToG6();
// 	iErrCnt += CNum.TwoNumMul().ToG6() == CNum1;
// 	if(iErrCnt > iEnErr)
// 	{
// 		return iRet;
// 	}
	++iRet;
	
	// ����Ͳ��ظ�
	CNum1 = CNumHistory.TwoNumSum().ToG6();
	iErrCnt += CNum.TwoNumSum().ToG6() == CNum1;
	if(iErrCnt > iEnErr)
	{
		return iRet;
	}
	++iRet;
		
	// ����粻�ظ�
// 	CNum1 = CNumHistory.TwoNumSpan().ToG6();
// 	iErrCnt += CNum.TwoNumSpan().ToG6() == CNum1;
// 	if(iErrCnt > iEnErr)
// 	{
// 		return iRet;
// 	}
	++iRet;

	return -1;
}

////////////////////////////////////////////////////////////////////////////////
// static method

BOOL CHistory::CheckPeriod(const CString &sPeriod)
{
	if( sPeriod.GetLength() != 7 )
		return FALSE;
	
	BOOL bRet = _istdigit(sPeriod[0])
		&& _istdigit(sPeriod[1])
		&& _istdigit(sPeriod[2])
		&& _istdigit(sPeriod[3])
		&& _istdigit(sPeriod[4])
		&& _istdigit(sPeriod[5])
		&& _istdigit(sPeriod[6])
		;
	if(!bRet)
		return FALSE;
	
	int iPeriod = _ttoi(sPeriod);
	if(iPeriod / 1000 < 2003 || iPeriod % 1000 > 366)
		return FALSE;
	
	return TRUE;
}

BOOL CHistory::CheckNum(const CString &sNum, BOOL bIs3D/* = FALSE*/)
{
	BOOL bRet = (sNum.GetLength() == (bIs3D ? 3 : 5))
		&& _istdigit(sNum[0]) && _istdigit(sNum[1]) && _istdigit(sNum[2]) ;
	
	if( !bIs3D )
		bRet = bRet	&& _istdigit(sNum[3]) && _istdigit(sNum[4]);
	
	int iNum = bIs3D ? _ttoi(sNum) : _ttoi(sNum) / 100;
	bRet = bRet && iNum < 1000;
	
	return bRet;
}
