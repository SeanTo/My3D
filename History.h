#ifndef _LOTTERY_HISTORY_H_
#define _LOTTERY_HISTORY_H_

#include "Number.h"

#include "bitset"
using std::bitset;

class CHistory
{
public:
	CHistory() { m_aPeriod.RemoveAll(); m_aNum.RemoveAll(); m_bIs3D = FALSE; }
	~CHistory() { m_aPeriod.RemoveAll(); m_aNum.RemoveAll(); }

public:
	
	// ��ʷ��¼�ļ�
	int LoadFromFile(const CString &strFile, BOOL bIs3D = FALSE);
	int SaveToFile(const CString &strFile) const;

	// ��ʷ��¼�༭
	VOID AddRecord(int iPeriod, int iNum);
	VOID DelRecord(int iSequence);
	VOID ModifyRecord(int iSequence, int iPeriod, int iNum)
	{
		ASSERT( iSequence < GetCount() );
		m_aPeriod.SetAt(iSequence, iPeriod);
		m_aNum.SetAt(iSequence, iNum);
	}
	
public:
	BOOL Is3D() const { return m_bIs3D; }					// ��Ʊ����
	BOOL IsNull() const { return 0 == GetCount(); }			// ��¼Ϊ��
	int  GetCount() const { return m_aPeriod.GetSize(); }	// ��ʷ��¼����

	// �ں�
	CString GetPeriodStr(int iSequence) const { return EMFC::Int2Str( GetPeriod(iSequence) ); }
	int GetPeriod(int iSequence) const;
	// ����
	C3D GetCNum(int iSequence) const { return GetNum(iSequence); }
	int GetNum(int iSequence) const;
	int P5Tail(int iSequence) const;
	CString GetNumStr(int iSequence) const { ASSERT(iSequence < GetCount()); return EMFC::Int2Str( GetNum(iSequence), _T("%03d") ); }
	CString P5TailStr(int iSequence) const { ASSERT(iSequence < GetCount()); return EMFC::Int2Str( P5Tail(iSequence), _T("%02d") ); }
		
public:
	// ���ҿ������룬����������δ�ҵ����� -1
	int  FindNum(int iNum, int iStart = 0) const;
	BOOL IsInside(int iNum, int iStart = 0) const { return -1 != FindNum(iNum); }
	
	// ��λ������©ͳ��
	int StatMiss(int iStart, int iBit, int n);
	// ����������©ͳ��
	int StatMiss(int iStart, C3D CNum);
	// ����Ͳ����©
	CString MissTwoNum(int iPeriod, int iStart = 0, int iType = 0);

	// ���ڿ����ĺ���
	VOID NearNum(CUIntArray &aNear, int iStart = 0, int iCount = 5);
	// ���Ⱥ�ͳ��
	VOID HotNum(int st, CString &sHot, CString &sWarm, CString &sCool, int iCnt = 5);

	// ��ʮ��λ��������ͳ������
	VOID StatAMP(int iPeriods, CUIntArray &arrAMP, int iBit, int st = 0);
	// ������׵���ʷ�н����
	BOOL Success(const CUIntArray &pSrc, int iPeriodCnt, CUIntArray &aRes);

public:

	// �Զ���ף�ȫ��ƥ�䷵��0��-1:�ݴ����ޣ����򷵻س����㷨������
	int FilterAutoBase(const int iNum, bitset<32> bSel, int iHistory = 0, int iErr1 = 0, int iErr2 = 0);

	// �˹��㷨������-1:ȫ��ƥ�䣬���򷵻س������㷨��
	int FilterManual(const int iNum, const int iHistory = 0, const int iEnErr = 0, const int iBack = 135);

	// ��ʽ���ˣ�������ȫƥ��Ķ���
	int Filter3Sect(const int iNum, int iLast, const CString *pSect = FIXED_SECT_STR, const int iSects = 15) const;

	// �����ǹ��ˣ�ȫ��ƥ�䷵��-1�����򷵻س������㷨������
	int FilterTriangle(const int iNum, int iHistory = 0, int iErr = 1, int iCnt1 = 1, int iCnt2 = 3);

	// ���Һ��� CNum ��3�����зֱ���ֵĴ���
	C3D Find3Sect(const int iNum, const CString *pSect) const;

	// �����Ƿֽ�, 9���ַ���
	int TriangleCourage(CStringArray &arrTriangle, int iHistory = 0, BOOL bUp = TRUE);
	
	// �����Ƽ�(7��)
	int RecommandCourage(CStringArray &arrCour, int iHistory = 0, int iBack = 136);

	// 5����β������
	CString PeriodTail5Courage(int iTail = 0);
	
	// �ϲ��(���ڿ����š��ϲ�)
	BOOL GetNearCourage(int iPeriods, CUIntArray &a1, UINT nOffset = 0);

	// ɱ���Ƽ�(3��)
	int Kill1Nums(CUIntArray &arrOneNums, const int iHistory = 0);

	// ��λɱ���Ƽ�(1��3λ)
	int Kill1NumsPos(const int iHistory = 0);

	// ��λɱ���Ƽ�(ÿ��3λ)
	int Kill1NumsPos(CUIntArray &arrOnePos, const int iHistory = 0);

	// ɱ2���Ƽ�(8��)
	int Kill2Nums(CUIntArray &arrTwoNums, const int iHistory = 0);
	
	// static
public:
	static int  LoadFile3DToArray(const CString &strFile, BOOL bIs3D, CUIntArray &aHistory);
	static BOOL CheckPeriod(const CString &sPeriod);
	static BOOL CheckNum(const CString &sNum, BOOL bIs3D = FALSE);

	static const CString& GetDmbFileName(BOOL bIs3D) { return m_strDataName[bIs3D ? 0 : 1]; }
	static const CString& GetBakFileName(BOOL bIs3D) { return m_strDataName[bIs3D ? 2 : 3]; }
	static const CString& GetType(BOOL bIs3D)        { return m_strDataName[bIs3D ? 4 : 5]; }

private:
	static const CString m_strDataName[];

	CUIntArray	m_aPeriod;
	CUIntArray	m_aNum;
	BOOL		m_bIs3D;
};

#endif // _LOTTERY_HISTORY_H_
