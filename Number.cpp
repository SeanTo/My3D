#include "stdafx.h"
#include "Number.h"

////////////////////////////////////////////////////////////////////////////////
// static member

// 奇偶、大小、质合形态
const CString C3D::strModality[3][8] = {
	{ _T("偶偶偶"), _T("偶偶奇"), _T("偶奇偶"), _T("偶奇奇"),
		_T("奇偶偶"), _T("奇偶奇"), _T("奇奇偶"), _T("奇奇奇") },
		
	{ _T("小小小"), _T("小小大"), _T("小大小"), _T("小大大"),
	_T("大小小"), _T("大小大"), _T("大大小"), _T("大大大") },
	
	{ _T("合合合"), _T("合合质"), _T("合质合"), _T("合质质"),
	_T("质合合"), _T("质合质"), _T("质质合"), _T("质质质") }
};

// 012 路
const CString C3D::str012[27] = {
	_T("000"), _T("001"), _T("002"), _T("010"),
	_T("011"), _T("012"), _T("020"), _T("021"), _T("022"),
	_T("100"), _T("101"), _T("102"), _T("110"),
	_T("111"), _T("112"), _T("120"), _T("121"), _T("122"),
	_T("200"), _T("201"), _T("202"), _T("210"),
	_T("211"), _T("212"), _T("220"), _T("221"), _T("222")
};

////////////////////////////////////////////////////////////////////////////////
// implementation

/*
 *	返回数字 n 在号码中出现的位置，未找到返回 -1
 */
int C3D::Find(int n, int st/* =0 */) const
{
	IS_ONE(n);
	IS_INDEX(st);

	for(int i = st; i < 3; ++i)
	{
		if( GetAt(i) == n )
			return i;
	}
	return -1;
}

/*
 *	两码差：百位、十位、个位
 */
void C3D::Swing(const C3D &obj, int *pSwing) const
{
	pSwing[0] = Hun() - obj.Hun();	// 百位
	pSwing[1] = Ten() - obj.Ten();	// 十位
	pSwing[2] = Ent() - obj.Ent();	// 个位
}

/*
 *	邻码判断
 */
BOOL C3D::IsNeighbor(int n) const
{
	ASSERT(0 <= n && n <= 9);
	if( IsMember(n) )
		return FALSE;

	for(int i = 0; i < 3; ++i)
	{
		if( 1 == abs(n - GetAt(i)) || 9 == abs(n - GetAt(i)))
			return TRUE;
	}
	return FALSE;
}

/*
 *	给定两码是否在当前号码中
 */
BOOL C3D::IsMember2(int iTwo, BOOL bOrder/* = TRUE*/) const
{
	ASSERT( 0 <= iTwo && iTwo <= 99);
	int n1 = iTwo / 10 % 10;
	int n2 = iTwo % 10;

	if( Hun()==n1 && (Ten()==n2 || Ent()==n2) || Ten()==n1 && Ent()==n2 )
		return TRUE;
	
	if( bOrder )
		return FALSE;
	else
		n1 ^= n2 ^= n1 ^= n2;

	return Hun()==n1 && (Ten()==n2 || Ent()==n2) || Ten()==n1 && Ent()==n2;
}

/*
 *	号码在 str 中出现的次数
 */
int C3D::CountInStr(const CString &str, BOOL bOnce /* = FALSE */) const
{
	if( IsG1() ) 
		return !EMFC::IsInArray(Hun(), str) ? 0 : (bOnce ? 1 : 3);

	int cnt = 0;
	for(int i = 0; i < 3; ++i)
		cnt += EMFC::IsInArray(GetAt(i), str);

	if( bOnce && IsG3() )
	{
		if(3 == cnt)
			cnt = 2;
		else
			cnt -= EMFC::IsInArray(Same(), str);
	}
	
	return cnt;
}

////////////////////////////////////////////////////////////////////////////////
// static method

/*
 *	排除两码
 */
int C3D::ExcludeTwo(CUIntArray &arr, BOOL bOrder /* = TRUE */)
{
	EMFC::ExcludeSame(arr);

	if( !bOrder )
	{
		UINT n;
		int i = arr.GetSize() - 1;
		while( i > 0 )
		{
			n = (arr[i] % 10) * 10 + arr[i] / 10 % 10;
			
			if( EMFC::IsInArray(n, arr, i) )
				arr.RemoveAt(i);

			--i;
		}
	}

	return arr.GetSize();
}

/*
 * 字符串转和值(两码)数组
 */
int C3D::Str2Sum(const CString &str, CUIntArray &arrSum, BOOL bConti /* = TRUE */, int iMax /* = 27 */)
{
	arrSum.RemoveAll();
	if(str.IsEmpty())
		return 0;
	
	CString st(str);
	st.TrimLeft();
	st.TrimRight();

	// 删除尾部非数字字符
	while( !st.IsEmpty() && !_istdigit(st.GetAt(st.GetLength() - 1)) )
		st.Delete(st.GetLength() - 1);
	
	CString sDigit = _T("0123456789");
	if(0 == st.GetLength() || -1 == st.FindOneOf(sDigit))
		return 0;
	
	int iDigit = 0, iSepar = 0;
	int i = 0;
	int n = 0;
	int num = iMax + 1;
	BOOL bContinue = FALSE;
	
	CString ss;
	while( 0 < st.GetLength() )
	{
		// 查找下一个数字
		iDigit = st.FindOneOf(sDigit);
		
		if(-1 != iDigit)
		{
			st = st.Mid(iDigit);				// 从第一个数字截取到尾部
			ss = st.SpanIncluding(sDigit);		// 截取头部数字串
			st = st.Mid(ss.GetLength());
			ss = ss.Left(2);
			
			num = _ttoi(ss);
			
			if(iMax >= num && ! EMFC::IsInArray((UINT)num, arrSum))
			{
				n = arrSum.GetSize();

				if(!bContinue || 0 == n)
				{
					arrSum.Add(num);
				}
				else
				{
					if((UINT)num > arrSum[n - 1])
					{
						for(int i = arrSum[n - 1] + 1; i <= num; ++i)
							arrSum.Add(i);
					}
					else
						arrSum.Add(num);
					
					bContinue = FALSE;
				}
			}
			
			st.TrimLeft();
			if(bConti)
			{
				if(0 < st.GetLength() && st.GetAt(0) == _T('-'))
				{
					bContinue = TRUE;
				}
			}
		}
	}
	
	if(n > 0)
		EMFC::SortArray(arrSum);
	
	return arrSum.GetSize();
}

/*
 * 和值(两码)数组转字符串
 */
CString C3D::Sum2Str(const CUIntArray &arrSum, BOOL bTwo /* = FALSE  */, BOOL bConti /* = TRUE */)
{
	CString str = _T("");
	const int len = arrSum.GetSize();
	
	if(0 == len)
		return str;
	
	CString sFmt = bTwo ? _T("%02d") : _T("%d");
	
	CString ss;
	
	ss.Format(sFmt, arrSum[0]);
	str += ss;

	for(int i = 1, k = 0; i < len; ++i)
	{
		k = 0;

		if(bConti)
		{
			while(i + k < len)
			{
				if( arrSum[i + k] == arrSum[i + k -1] + 1 )
					++k;
				else
					break;
			}
		}
		else
			k = 0;
		
		if(0 == k)
		{
			sFmt = bTwo ? _T(",%02d") : _T(",%d");
			ss.Format(sFmt, arrSum[i]);
			str += ss;
		}
		else
		{
			sFmt = bTwo ? _T(",%02d") : _T("-%d");
			ss.Format(sFmt, arrSum[i + k - 1]);
			str += ss;
			i += k - 1;
			k = 0;
		}
	}
	
	return str;
}

/*
 * 字符串转数组
 */
int C3D::Str2Array(const CString &str, CUIntArray &arr, BOOL bSort/* = TRUE*/)
{
	arr.RemoveAll();
	
	int len = str.GetLength();
	if(0 == len)
		return 0;

	int B[3], j = 0, num;
		
	for(int i = 0; i < len && arr.GetSize() < 1000; ++i)
	{
		if(_istdigit(str.GetAt(i)))
			B[j++] = str.GetAt(i) - _T('0');
		
		if(3 == j)
		{
			j = 0;
			num = B[0] * 100 + B[1] * 10 + B[2];

			if( !EMFC::IsInArray((UINT)num, arr) )
				arr.Add(num);
		}
	}

	j = arr.GetSize();
	if(j > 1 && bSort)
		EMFC::SortArray(arr);

	return j;
}

/*
 * 数组转字符串
 */
CString& C3D::Array2Str(const CUIntArray &arr, CString &str, const CString &sFmt /* = _T("%03d ") */)
{
	str.Empty();

	CString ss = _T("");
	int cnt = arr.GetSize();

	for(int i = 0; i < cnt; ++i)
	{
		ss.Format(sFmt, arr[i]);
		str += ss;
	}

	return str;
}

/*
 *	单转组
 */
int C3D::S2G(CUIntArray &arr)
{
	C3D CNum;
	int i = 0;

	while(i < arr.GetSize() )
	{
		CNum = arr[i];
		arr[i] = CNum.Min() * 100 + CNum.Mid() * 10 + CNum.Max();

		if( EMFC::IsInArray(arr[i], arr, i) )
			arr.RemoveAt(i);
		else
			++i;
	}

	EMFC::SortArray(arr);
	return arr.GetSize();
}

/*
 *	组转单
 */
int C3D::G2S(CUIntArray &arr)
{
	C3D CNum;
	int A[3], B[6];
	int i = 0;

	while(i < arr.GetSize() )
	{
		CNum = arr[i];
		A[0] = CNum.Min();
		A[1] = CNum.Mid();
		A[2] = CNum.Max();
				
		B[0] = A[0] * 100 + A[1] * 10 + A[2];
		B[1] = A[0] * 100 + A[2] * 10 + A[1];
		B[2] = A[1] * 100 + A[0] * 10 + A[2];
		B[3] = A[1] * 100 + A[2] * 10 + A[0];
		B[4] = A[2] * 100 + A[0] * 10 + A[1];
		B[5] = A[2] * 100 + A[1] * 10 + A[0];

		for(int j = 0; j < 6; ++j)
		{
			if( !EMFC::IsInArray((UINT)B[j], arr, i) )
			{
				arr.InsertAt(0, B[j]);
				++i;
			}

		}
		arr.RemoveAt(i);
	}

	EMFC::SortArray(arr);
	return arr.GetSize();
}

////////////////////////////////////////////////////////////////////////////////
