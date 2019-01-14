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
	
	// 历史记录文件
	int LoadFromFile(const CString &strFile, BOOL bIs3D = FALSE);
	int SaveToFile(const CString &strFile) const;

	// 历史记录编辑
	VOID AddRecord(int iPeriod, int iNum);
	VOID DelRecord(int iSequence);
	VOID ModifyRecord(int iSequence, int iPeriod, int iNum)
	{
		ASSERT( iSequence < GetCount() );
		m_aPeriod.SetAt(iSequence, iPeriod);
		m_aNum.SetAt(iSequence, iNum);
	}
	
public:
	BOOL Is3D() const { return m_bIs3D; }					// 彩票类型
	BOOL IsNull() const { return 0 == GetCount(); }			// 记录为空
	int  GetCount() const { return m_aPeriod.GetSize(); }	// 历史记录条数

	// 期号
	CString GetPeriodStr(int iSequence) const { return EMFC::Int2Str( GetPeriod(iSequence) ); }
	int GetPeriod(int iSequence) const;
	// 号码
	C3D GetCNum(int iSequence) const { return GetNum(iSequence); }
	int GetNum(int iSequence) const;
	int P5Tail(int iSequence) const;
	CString GetNumStr(int iSequence) const { ASSERT(iSequence < GetCount()); return EMFC::Int2Str( GetNum(iSequence), _T("%03d") ); }
	CString P5TailStr(int iSequence) const { ASSERT(iSequence < GetCount()); return EMFC::Int2Str( P5Tail(iSequence), _T("%02d") ); }
		
public:
	// 查找开奖号码，返回索引，未找到返回 -1
	int  FindNum(int iNum, int iStart = 0) const;
	BOOL IsInside(int iNum, int iStart = 0) const { return -1 != FindNum(iNum); }
	
	// 定位号码遗漏统计
	int StatMiss(int iStart, int iBit, int n);
	// 开奖号码遗漏统计
	int StatMiss(int iStart, C3D CNum);
	// 两码和差积遗漏
	CString MissTwoNum(int iPeriod, int iStart = 0, int iType = 0);

	// 近期开出的号码
	VOID NearNum(CUIntArray &aNear, int iStart = 0, int iCount = 5);
	// 冷热号统计
	VOID HotNum(int st, CString &sHot, CString &sWarm, CString &sCool, int iCnt = 5);

	// 百十个位号码增幅统计排序
	VOID StatAMP(int iPeriods, CUIntArray &arrAMP, int iBit, int st = 0);
	// 分析大底的历史中奖情况
	BOOL Success(const CUIntArray &pSrc, int iPeriodCnt, CUIntArray &aRes);

public:

	// 自动大底，全部匹配返回0，-1:容错下限，否则返回出错算法索引号
	int FilterAutoBase(const int iNum, bitset<32> bSel, int iHistory = 0, int iErr1 = 0, int iErr2 = 0);

	// 人工算法，返回-1:全部匹配，否则返回出错子算法号
	int FilterManual(const int iNum, const int iHistory = 0, const int iEnErr = 0, const int iBack = 135);

	// 段式过滤，返回完全匹配的段数
	int Filter3Sect(const int iNum, int iLast, const CString *pSect = FIXED_SECT_STR, const int iSects = 15) const;

	// 金三角过滤，全部匹配返回-1，否则返回出错子算法索引号
	int FilterTriangle(const int iNum, int iHistory = 0, int iErr = 1, int iCnt1 = 1, int iCnt2 = 3);

	// 查找号码 CNum 在3个串中分别出现的次数
	C3D Find3Sect(const int iNum, const CString *pSect) const;

	// 金三角分解, 9组字符串
	int TriangleCourage(CStringArray &arrTriangle, int iHistory = 0, BOOL bUp = TRUE);
	
	// 胆码推荐(7组)
	int RecommandCourage(CStringArray &arrCour, int iHistory = 0, int iBack = 136);

	// 5码期尾定胆法
	CString PeriodTail5Courage(int iTail = 0);
	
	// 合差胆组(近期开奖号、合差)
	BOOL GetNearCourage(int iPeriods, CUIntArray &a1, UINT nOffset = 0);

	// 杀码推荐(3组)
	int Kill1Nums(CUIntArray &arrOneNums, const int iHistory = 0);

	// 定位杀码推荐(1组3位)
	int Kill1NumsPos(const int iHistory = 0);

	// 定位杀码推荐(每组3位)
	int Kill1NumsPos(CUIntArray &arrOnePos, const int iHistory = 0);

	// 杀2码推荐(8组)
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
