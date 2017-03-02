#pragma once
#include"stdafx.h"

using std::string;
using std::stack;

class syntax {

		/*
		����ʽ��
		E --> TA
		A --> +TA
		A --> -TA
		A --> null		//null��ʾ��
		T --> FB
		B --> *FB
		B --> /FB
		B --> null
		F --> MN
		N --> ^MN
		N --> null
		M --> i			//i��ʾ����
		M --> (E)
		*/
private:

	//_lexs: �ʷ���Ԫ��		_vals: �ʷ���Ԫֵ		_begIndex: ��ǰ�ʷ���Ԫ		_endIndex: ���һ���ʷ���Ԫ
	//format: �����ʽ		stk: �ʷ���Ԫֵ�ķ���׺ʽ����ջ�׵�ջ��Ϊ��׺ʽ��
	void E(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk);
	void A(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk);
	void T(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk);
	void B(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk);
	void F(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk);
	void N(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk);
	void M(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk);

	//���ַ���ת��Ϊ����
	double strToDouble(string& _str);
public:

	//����������_lexs��_valsͬ�ϣ�_count��ʾ�ʷ���Ԫ���������ؼ�����
	double driver(string _lexs[], string _vals[], int _count);
};