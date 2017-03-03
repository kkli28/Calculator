#pragma once
#include"stdafx.h"

using std::string;

class lexical {
	/*
	NUM: 数字
	ADD: 加
	SUB: 减
	MUL: 乘
	DIV: 除
	POW: 乘方
	LB:  左括号
	RB:  右括号
	E:   自然对数
	PI:  圆周率
	FUNC: 函数

	cmath头文件中的部分内容
	e:	 自然对数
	pi:  圆周率
	abs: 绝对值
	ceil: 向上取整
	exp: e的n次方
	floor: 向下取整
	cos: 余弦
	sin: 正弦
	sqrt: 开平方
	tan: 正切
	log: 对数（e为底）
	log2: 对数（2为底）
	log10: 对数（10为底）
	*/
private:
	//是数字？
	inline bool isNumber(char c) {
		if (c >= 0x30 && c <= 0x39) return true;
		else return false;
	}

	//是运算符？
	inline bool isOperator(char c) {
		if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') return true;
		else return false;
	}

	//是空白符
	inline bool isWhiteSpace(char c) {
		if (c == ' ' || c == '\t' || c == '\n') return true;
		else return false;
	}
	/*
	匹配函数：
	matchNumber: 匹配数字
	matchOperator: 匹配运算符
	matchBracket: 匹配括号
	matchConstant: 匹配常量
	matchFunction: 匹配函数（内置）

	_iter1指示表示开始匹配的位置，_ite2指示匹配到数字后的结束位置。匹配到的内容范围为[*_iter1,*_iter2)。
	如果_iter1==_iter2，则表示匹配失败。否则匹配成功，调用此函数的地方就可以通过_iter1和_iter2获取内容，
	同时需要修改_iter1的值为_iter2，以便后续的匹配能顺利进行。
	*/

	bool matchNumber(string::iterator& _iter1, string::iterator& _iter2, string::iterator& _endIter,string& _preType);
	bool matchOperator(string::iterator& _iter1, string::iterator& _iter2, string::iterator& _endIter);
	bool matchBracket(string::iterator& _iter1, string::iterator& _iter2, string::iterator& _endIter);
	bool matchConstant(string::iterator& _iter1, string::iterator& _iter2, string::iterator& _endIter);
	bool matchFunction(string::iterator& _iter1, string::iterator& _iter2, string::iterator& _endIter);
public:
	/*
	驱动函数
	
	可通过传入的_expr（表达式），获取对应的词法单元。
	词法单元名字放入_lexs字符串数组中，词法单元值放入_vals字符串数字中。
	_count用于记录词法单元个数，以便语法分析使用。
	*/
	void driver(string& _expr, string _lexs[], string _vals[], int& _count);
};