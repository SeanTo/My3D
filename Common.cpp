#include "stdafx.h"
#include "Common.h"

////////////////////////////////////////////////////////////////////////////////
// global variable

COLORREF crText = RGB(0, 0, 0);
COLORREF crText2 = RGB(255, 255, 255);
COLORREF crBack = RGB(203, 233, 241);
COLORREF crYellow = RGB(255, 255, 0);
COLORREF crPurple = RGB(255, 0, 255);
COLORREF crRed = RGB(255, 0, 0);
COLORREF crGreen = RGB(0, 128, 0);
COLORREF crBlue = RGB(0, 0, 255);
COLORREF crCyan = RGB(0, 128, 128);
COLORREF crGray = RGB(208, 208, 208);

// �̶�45�κ���
const CString FIXED_SECT_STR[] = {
	_T("015"), _T("236"), _T("125"),
		_T("017"), _T("456"), _T("019"),
		_T("458"), _T("026"), _T("346"),
		_T("028"), _T("349"), _T("127"),
		_T("036"), _T("258"), _T("138"),
		_T("569"), _T("578"), _T("456"),
		_T("347"), _T("048"), _T("479"),
		_T("056"), _T("279"), _T("058"),
		_T("069"), _T("239"), _T("126"),
		_T("035"), _T("128"), _T("235"),
		_T("016"), _T("129"), _T("237"),
		_T("039"), _T("029"), _T("345"),
		_T("027"), _T("347"), _T("459"),
		_T("018"), _T("457"), _T("025"),
		_T("348"), _T("123"), _T("028")
};

// �Զ�����㷨
const CString AUTO_BASE_STR[] = {
	_T("��̬����"), _T("��ʽ-ǿ"), _T("��ʽ-��"), _T("����̳�"), _T("012 �̳�"),
		_T("��̬��ת"), _T("��ֵ 2-7"), _T("������"), _T("������"), _T("�������"),
		_T("�����4��"), _T("�����3��"), _T("�����3��"), _T("���3��"), _T("��β3��"),
		_T("��ż3��"), _T("��С3��"), _T("��̬3��"), _T("012·3��"), _T("б����2��"),
		_T("����"), _T("����"), _T("����")
};

// ��̬�������㷨
const CString APTITUD_STR[] = {
	_T("���õ���"), _T("���Ƹ���"), _T("�������"), _T("ɱ����"), _T("��λɱ"),
		_T("�����"), _T("�����"), _T("�����"), _T("����1"), _T("����1"), _T("����1")
};
