#ifndef _LOTTERY_NUMBER_H_
#define _LOTTERY_NUMBER_H_

// #include "..\Share\wnd.h"
#include "..\Share\EMFC.h"

#define  IS_3D(x)		ASSERT(x >= 0 && x <= 999)
#define  IS_INDEX(x)	ASSERT(x >=0 && x < 3)
#define  IS_ONE(x)		ASSERT(x >= 0 && x <= 9)
#define  IS_FORM1(x)	ASSERT(x >=0 && x < FORM1)
#define  IS_FORM2(x)	ASSERT(x >=0 && x < FORM2)
#define  IS_AC3(x)		ASSERT(x >=0 && x < AC3)

class C3D
{
public:
	enum {TYPE_G6=0, TYPE_G3=1, TYPE_G1=2};	// 组六、组三、豹子
	enum {FORM1=3, FORM2=8, AC3=27};		// 形态数
	
	// 构造
public:
	C3D(int iNum = 0) { IS_3D(iNum); m_iNum = iNum; Initialize(); }
	C3D(const C3D &obj) { m_iNum = obj.m_iNum; Initialize(); }
// 	C3D operator = (const C3D &obj) { m_iNum = obj.m_iNum; Initialize(); return *this; }

public:	
	operator int () const { return m_iNum; }
	int operator [](int i) const { IS_INDEX(i); return GetAt(i); }

	BOOL operator ==(const C3D &obj) const { return obj.m_iNum == m_iNum; }
// 	int operator * (int n) const { return m_iNum * n; }
// 	C3D operator -(const C3D &obj) const { return C3D( abs(Hun()-obj.Hun()), abs(Ten()-obj.Ten()), abs(Ent()-obj.Ent()) ); }
// 	C3D operator +(const C3D &obj) const { return C3D( (Hun()+obj.Hun())%10, (Ten()+obj.Ten())%10, abs(Ent()+obj.Ent())%10 ); }
// 	C3D operator *(const C3D &obj) const { return C3D( (Hun()*obj.Hun())%10, (Ten()*obj.Ten())%10, abs(Ent()*obj.Ent())%10 ); }

	C3D     ToG6(BOOL bUp=TRUE)     const { return bUp ? C3D(Min(), Mid(), Max()) : C3D(Max(), Mid(), Min()); }
	CString ToString() const { CString str; str.Format(_T("%03d"), m_iNum); return str; }
	
	// 成员
public:
	const int Hun() const { return (int)m_iBit[0]; }	// 百位
	const int Ten() const { return (int)m_iBit[1]; }	// 十位
	const int Ent() const { return (int)m_iBit[2]; }	// 个位
	const int GetAt(int i) const { IS_INDEX(i); return (int)m_iBit[i]; }
	// 组三中的重号
	int Same() const { ASSERT(IsG3()); return (Hun()==Ten() || Hun()==Ent()) ? Hun() : Ten(); }
	
	// 分类
public:
	int  Type() const { return (int)(IsG1() ? (int)TYPE_G1 : (IsG3() ? (int)TYPE_G3 : (int)TYPE_G6)); }
	BOOL IsG1() const { return Hun() == Ten() && Hun() == Ent(); }
	BOOL IsG3() const { return !IsG1() && (Hun() == Ten() || Hun() == Ent() || Ten() == Ent()); }
	BOOL IsG6() const { return !IsG1() && !IsG3(); }

	// 常规属性
public:
	int Max() const { return max(Hun(), max(Ten(), Ent())); }	// 最大号码
	int Min() const { return min(Hun(), min(Ten(), Ent())); }	// 最小号码
	int Mid() const { return Sum() - Max() - Min(); }			// 中间号码

	int Sum() const  { return Hun() + Ten() + Ent(); }			// 和值
	int Tail() const { return Sum() % 10; }						// 和尾
	int Ave() const  { return (int)(Sum() / 3.0 + 0.5); }		// 均值
	int Span() const { return Max() - Min(); }					// 跨度

	// 奇偶、大小、质合码数
	int OddCnt() const { return IsOdd(Hun()) + IsOdd(Ten()) + IsOdd(Ent()); }
	int EvenCnt() const { return 3 - OddCnt(); }
	int LargeCnt() const { return IsLarge(Hun()) + IsLarge(Ten()) + IsLarge(Ent()); }
	int SmallCnt() const { return 3 - LargeCnt(); }
	int PrimeCnt() const { return IsPrime(Hun()) + IsPrime(Ten()) + IsPrime(Ent()); }
	int CompositeCnt() const { return 3 - PrimeCnt(); }
	
	// 号码连续次数 : 连号、大号、小号、奇号、偶号、质号
	int ContinueCnt() const { return IsContinue(Hun(), Ten()) + IsContinue(Hun(), Ent()) + IsContinue(Ten(), Ent()); }
	int ContinueLarge() const { return (IsLarge(Hun()) && IsLarge(Ten())) + (IsLarge(Ten()) && IsLarge(Ent())); }
	int ContinueSmall() const { return (!IsLarge(Hun()) && !IsLarge(Ten())) + (!IsLarge(Ten()) && !IsLarge(Ent())); }
	int ContinueOdd() const { return (IsOdd(Hun()) && IsOdd(Ten())) + (IsOdd(Ten()) && IsOdd(Ent())); }
	int ContinueEven() const { return (!IsOdd(Hun()) && !IsOdd(Ten())) + (!IsOdd(Ten()) && !IsOdd(Ent())); }
	int ContinuePrime() const { return (IsPrime(Hun()) && IsPrime(Ten())) + (IsPrime(Ten()) && IsPrime(Ent())); }
	
	// 两码 : 百十、百个、十个
public:
	C3D TwoNumSpan() const { return C3D( abs(Hun()-Ten()), abs(Hun()-Ent()), abs(Ten()-Ent()) ); }
	C3D TwoNumSum() const  { return C3D( (Hun()+Ten())%10, (Hun()+Ent())%10, (Ten()+Ent())%10 ); }
	C3D TwoNumMul() const  { return C3D( (Hun()*Ten())%10, (Hun()*Ent())%10, (Ten()*Ent())%10 ); }
	void Swing(const C3D &obj, int *pSwing) const;	// 两码差

	// 形态 : 奇偶、大小、质合、012路
public:
	// 形态数组
	C3D OddModNum() const { return C3D(IsOdd(Hun()), IsOdd(Ten()), IsOdd(Ent())); }
	C3D LargeModNum() const { return C3D(IsLarge(Hun()), IsLarge(Ten()), IsLarge(Ent())); }
	C3D PrimeModNum() const { return C3D(IsPrime(Hun()), IsPrime(Ten()), IsPrime(Ent())); }
	C3D AC3ModNum() const { return C3D((Hun()%3), (Ten()%3), + (Ent()%3)); }

	// 形态编号
	int OddModality() const { return (IsOdd(Hun())<<2) + (IsOdd(Ten())<<1) + IsOdd(Ent()); }
	int LargeModality() const { return (IsLarge(Hun())<<2) + (IsLarge(Ten())<<1) + IsLarge(Ent()); }
	int PrimeModality() const { return (IsPrime(Hun())<<2) + (IsPrime(Ten())<<1) + IsPrime(Ent()); }
	int AC3Modality() const { return (Hun()%3) * 9 + (Ten()%3) * 3 + (Ent()%3); }

	// 形态字符串
	const CString& OddStr()   const { return strModality[0][OddModality()]; }
	const CString& LargeStr() const { return strModality[1][LargeModality()]; }
	const CString& PrimeStr() const { return strModality[2][PrimeModality()]; }
	const CString& AC3Str()   const { return str012[AC3Modality()]; }
	
	// 数字判断
public:
	// 传码、邻码、孤码、左斜码、右斜码、新码
	BOOL IsMember(int n) const { IS_ONE(n); return Hun()==n || Ten()==n || Ent() == n; }
	BOOL IsNeighbor(int n) const;
	BOOL IsAlone(int n) const { IS_ONE(n); return !IsMember(n) && !IsNeighbor(n); }
	BOOL IsLeft(int n) const { IS_ONE(n); return n < Min(); }
	BOOL IsRight(int n) const { IS_ONE(n); return n > Max(); }
	BOOL IsNew(int n) const { IS_ONE(n); return !IsMember(n); }
	// 两码
	BOOL IsMember2(int iTwo, BOOL bOrder = TRUE) const;

	int  Find(int n, int st=0) const;
	
	// 统计
public:
	// 号码在 str 中出现的次数
	int CountInStr(const CString &str, BOOL bOnce = FALSE) const;
	int CountIn3D(const C3D &obj, BOOL bOnce = FALSE) const { return CountInStr(obj.ToString(), bOnce); }
	
	// 新码、邻码、孤码、斜码、左斜、右斜 计数
	int CountNew(const C3D &obj) const { return IsNew(obj.Hun()) + IsNew(obj.Ten()) + IsNew(obj.Ent()); }
	int CountNeighbor(const C3D &obj) const { return IsNeighbor(obj.Hun()) + IsNeighbor(obj.Ten()) + IsNeighbor(obj.Ent()); }
	int CountAlone(const C3D &obj) const { return IsAlone(obj.Hun()) + IsAlone(obj.Ten()) + IsAlone(obj.Ent()); }
	int CountTilted(const C3D &obj) const { return CountLeft(obj) + CountRight(obj); }
	int CountLeft(const C3D &obj) const { return IsLeft(obj.Hun()) + IsLeft(obj.Ten()) + IsLeft(obj.Ent()); }
	int CountRight(const C3D &obj) const { return IsRight(obj.Hun()) + IsRight(obj.Ten()) + IsRight(obj.Ent()); }
	
	// 继承个数
	int CountSame(const C3D &obj) const { return (Hun()==obj.Hun()) + (Ten()==obj.Ten()) + (Ent()==obj.Ent()); }
	
// 静态
public:
	// 形态字符串
	static const CString& GetFormStr(int x, int y) { IS_FORM1(x); IS_FORM2(y); return strModality[x][y]; }
	static const CString& GetAC3Str(int x) { IS_AC3(x); return str012[x]; }

	// 大号、奇号、质号(1按质号处理)
	static BOOL IsLarge(const int n) { IS_ONE(n); return (n >= 5); }
	static BOOL IsOdd(const int n)   { IS_ONE(n); return (n & 1);	}
	static BOOL IsPrime(const int n) { IS_ONE(n); return (1<=n && n<=3) || 5==n || 7==n; }
	// 连号(90按连号处理)
	static BOOL IsContinue(int n1, int n2) { return 1==abs(n1-n2) || 9==abs(n1-n2); }
	
	// 字符串/和值互转
	static int ExcludeTwo(CUIntArray &arr, BOOL bOrder = TRUE);
	static int Str2Sum(const CString &str, CUIntArray &arrSum, BOOL bConti = TRUE, int iMax = 27);
	static CString Sum2Str(const CUIntArray &arrSum, BOOL bTwo = FALSE, BOOL bConti = TRUE);
	
	// 字符串/大底号互转
	static int Str2Array(const CString &str, CUIntArray &arr, BOOL bSort = TRUE);
	static CString& Array2Str(const CUIntArray &arr, CString &str, const CString &sFmt = _T("%03d ") );

	// 单组选互转
	static int G2S(CUIntArray &arr);	// 组转单
	static int S2G(CUIntArray &arr);	// 单转组
	
private:
	C3D(int iHun, int iTen, int iEnt) {
		m_iNum=(int)iHun*100+iTen*10+iEnt;
		m_iBit[0]=iHun;
		m_iBit[1]=iTen;
		m_iBit[2]=iEnt;
	}
	VOID Initialize() {
		m_iBit[0] = (BYTE)(m_iNum / 100);
		m_iBit[1] = (BYTE)(m_iNum / 10 % 10);
		m_iBit[2] = (BYTE)(m_iNum % 10);
	}

public:
	static const CString strModality[3][8];
	static const CString str012[27];
	
private:
	int  m_iNum;	// 号码
	BYTE m_iBit[3];	// 百、十、个位
};

#endif // _LOTTERY_NUMBER_H_