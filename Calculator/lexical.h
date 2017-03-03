#pragma once
#include"stdafx.h"

using std::string;

class lexical {
	/*
	NUM: ����
	ADD: ��
	SUB: ��
	MUL: ��
	DIV: ��
	POW: �˷�
	LB:  ������
	RB:  ������
	E:   ��Ȼ����
	PI:  Բ����
	FUNC: ����

	cmathͷ�ļ��еĲ�������
	e:	 ��Ȼ����
	pi:  Բ����
	abs: ����ֵ
	ceil: ����ȡ��
	exp: e��n�η�
	floor: ����ȡ��
	cos: ����
	sin: ����
	sqrt: ��ƽ��
	tan: ����
	log: ������eΪ�ף�
	log2: ������2Ϊ�ף�
	log10: ������10Ϊ�ף�
	*/
private:
	//�����֣�
	inline bool isNumber(char c) {
		if (c >= 0x30 && c <= 0x39) return true;
		else return false;
	}

	//���������
	inline bool isOperator(char c) {
		if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') return true;
		else return false;
	}

	//�ǿհ׷�
	inline bool isWhiteSpace(char c) {
		if (c == ' ' || c == '\t' || c == '\n') return true;
		else return false;
	}
	/*
	ƥ�亯����
	matchNumber: ƥ������
	matchOperator: ƥ�������
	matchBracket: ƥ������
	matchConstant: ƥ�䳣��
	matchFunction: ƥ�亯�������ã�

	_iter1ָʾ��ʾ��ʼƥ���λ�ã�_ite2ָʾƥ�䵽���ֺ�Ľ���λ�á�ƥ�䵽�����ݷ�ΧΪ[*_iter1,*_iter2)��
	���_iter1==_iter2�����ʾƥ��ʧ�ܡ�����ƥ��ɹ������ô˺����ĵط��Ϳ���ͨ��_iter1��_iter2��ȡ���ݣ�
	ͬʱ��Ҫ�޸�_iter1��ֵΪ_iter2���Ա������ƥ����˳�����С�
	*/

	bool matchNumber(string::iterator& _iter1, string::iterator& _iter2, string::iterator& _endIter,string& _preType);
	bool matchOperator(string::iterator& _iter1, string::iterator& _iter2, string::iterator& _endIter);
	bool matchBracket(string::iterator& _iter1, string::iterator& _iter2, string::iterator& _endIter);
	bool matchConstant(string::iterator& _iter1, string::iterator& _iter2, string::iterator& _endIter);
	bool matchFunction(string::iterator& _iter1, string::iterator& _iter2, string::iterator& _endIter);
public:
	/*
	��������
	
	��ͨ�������_expr�����ʽ������ȡ��Ӧ�Ĵʷ���Ԫ��
	�ʷ���Ԫ���ַ���_lexs�ַ��������У��ʷ���Ԫֵ����_vals�ַ��������С�
	_count���ڼ�¼�ʷ���Ԫ�������Ա��﷨����ʹ�á�
	*/
	void driver(string& _expr, string _lexs[], string _vals[], int& _count);
};