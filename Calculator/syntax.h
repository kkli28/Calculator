#pragma once
#include"stdafx.h"

using std::string;
using std::stack;

class syntax {

		/*
		产生式：
		E --> TA
		A --> +TA
		A --> -TA
		A --> null		//null表示空
		T --> FB
		B --> *FB
		B --> /FB
		B --> null
		F --> MN
		N --> ^MN
		N --> null
		M --> i			//i表示数字
		M --> (E)
		*/
private:

	//_lexs: 词法单元名		_vals: 词法单元值		_begIndex: 当前词法单元		_endIndex: 最后一个词法单元
	//format: 输出格式		stk: 词法单元值的反后缀式（从栈底到栈顶为后缀式）
	void E(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk);
	void A(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk);
	void T(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk);
	void B(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk);
	void F(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk);
	void N(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk);
	void M(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk);

	//将字符串转化为数字
	double strToDouble(string& _str);
public:

	//驱动函数，_lexs、_vals同上，_count标示词法单元个数，返回计算结果
	double driver(string _lexs[], string _vals[], int _count);
};