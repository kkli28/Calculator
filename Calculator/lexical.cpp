#include"stdafx.h"
#include"lexical.h"
using namespace std;

//匹配
bool lexical::matchNumber(string::iterator& _iter1, string::iterator& _iter2, string::iterator& _endIter, string& _preType) {

	//第一个字符为+或-，可能是数字的符号，也可能是操作数
	if (_iter2!=_endIter && (*_iter2 == '+' || *_iter2 == '-')) {

		//根据前一个词法单元是什么，断定这个符号是正负号还是加减号
		if (_iter2 + 1 != _endIter && isNumber(*(_iter2 + 1))) {
			if (_preType == "ADD" || _preType=="SUB" || _preType=="MUL"
				|| _preType== "MOD" || _preType=="POW" || _preType==""
				|| _preType=="LB") {
				++_iter2;
			}
			else return false;
		}

		//+或-后面不是数字，则直接退出
		else return false;
	}

	//跳过所有数字部分
	while (_iter2 != _endIter && isNumber(*_iter2)) ++_iter2;
	if (_iter1 == _iter2) return false;

	//出现了'.'，若小数点后一位为数字，则判定为小数点，否则数字匹配到此结束
	if (_iter2 != _endIter && *_iter2 == '.') {

		//小数点后面是数字
		if ((_iter2 + 1) != _endIter && isNumber(*(_iter2 + 1))) {

			//跳过小数点，并跳过所有后续数字
			++_iter2;
			while (_iter2 != _endIter && isNumber(*_iter2)) ++_iter2;
			return true;
		}
		else return false;
	}
	return true;
}

bool lexical::matchOperator(string::iterator& _iter1, string::iterator& _iter2, string::iterator& _endIter) {
	if (_iter2 != _endIter && isOperator(*_iter2)) {
		++_iter2;
		return true;
	}
	else return false;
}

bool lexical::matchBracket(string::iterator& _iter1, string::iterator& _iter2, string::iterator& _endIter) {
	if (_iter2 != _endIter && (*_iter2 == '(' || *_iter2 == ')')) {
		++_iter2;
		return true;
	}
	else return false;
}

bool lexical::matchConstant(string::iterator& _iter1, string::iterator& _iter2, string::iterator& _endIter) {
	if (_iter2 != _endIter){

		//自然底数e
		if (*_iter2 == 'e') {
			++_iter2;
			return true;
		}
		else if (_iter2 + 1 != _endIter) {
			//圆周率pi
			if (*_iter2 == 'p' && *(_iter2 + 1) == 'i') {
				_iter2 += 2;
				return true;
			}
			else if (*_iter2 == '+' || *_iter2 == '-') {
				//+e或-e
				if (*(_iter2+1) == 'e') {
					_iter2 += 2;
					return true;
				}
				//+pi或-pi
				else if (_iter2 + 2 != _endIter && *(_iter2 + 1) == 'p' && *(_iter2 + 2) == 'i') {
					_iter2 += 3;
					return true;
				}
			}
		}
	}

	//匹配失败
	return false;
}

bool lexical::matchFunction(string::iterator& _iter1, string::iterator& _iter2, string::iterator& _endIter) {
	if (_iter2 == _endIter) return false;
	
	//需要先匹配长的函数，因为writeLog为writeLog10的子集，所以如果先匹配短的函数，就会导致writeLog10被匹配为writeLog
	//五个字符长度的函数
	if (_iter2+1 != _endIter && (_iter2 + 2) != _endIter && (_iter2+3)!=_endIter
		&& (_iter2+4)!=_endIter) {
		if (constant::isFunction(_iter1, _iter2+5)) {
			_iter2 += 5;
			return true;
		}

		//四个字符长度的函数
		else if (_iter2 + 1 != _endIter && (_iter2 + 2) != _endIter && (_iter2 + 3) != _endIter) {
			if (constant::isFunction(_iter1, _iter2+4)) {
				_iter2 += 4;
				return true;
			}

			//三个字符长度的函数
			else if (_iter2 + 1 != _endIter && (_iter2 + 2) != _endIter) {
				if (constant::isFunction(_iter1, _iter2+3)) {
					_iter2 += 3;
					return true;
				}
			}
		}
	}
	return false;
}

//驱动函数
void lexical::driver(string& _expr, string _lexs[], string _vals[], int& _count) {

	//iter1标记匹配项的首位置，iter2通过调用matchXXX函数修改，标记匹配项的尾位置
	//若匹配成功，则[*iter1,*iter2)为匹配的结果
	auto iter1 = _expr.begin();
	auto iter2 = iter1;
	auto endIter = _expr.end();
	string preType;						//前一次匹配的词法单元名字
	_count = 0;
	
	while (iter2 != endIter) {

		//匹配函数
		if (matchFunction(iter1, iter2, endIter)) {
			_lexs[_count] = "FUNC";
			_vals[_count] = string(iter1,iter2);

			//writeLog
			constant::writeLog(string("match: ") + _lexs[_count]+"\t["+_vals[_count]+"]");

			iter1 = iter2;
			preType = _vals[_count];
			++_count;
			continue;
		}

		//匹配常量
		if (matchConstant(iter1, iter2, endIter)) {
			//e
			if (iter1+1 == iter2) {
				_lexs[_count] = "E";
				_vals[_count] = "2.718281828459";
			}
			//+e或-e或pi
			else if (iter1+2 == iter2) {
				//+e或-e
				if (*(iter1 + 1) == 'e') {
					_lexs[_count] = "E";
					if (*iter1 == '+') _vals[_count] = "2.718281828459";
					else _vals[_count] = "-2.718281828459";
				}
				//pi
				else {
					_lexs[_count] = "PI";
					_vals[_count] = "3.141592653589";
				}
			}
			//+pi或-pi
			else if (iter1 + 3 == iter2) {
				_lexs[_count] = "PI";
				if(*(iter1)=='+') _vals[_count] = "3.141592653589";
				else _vals[_count] = "-3.141592653589";
			}
			else throw Error(string("Error! lexical::driver()."));

			//writeLog
			constant::writeLog("match: " + _lexs[_count] + "\t[" + _vals[_count] + "]");

			iter1 = iter2;
			preType = _lexs[_count];
			++_count;
			continue;
		}
		
		//匹配数字
		if (matchNumber(iter1, iter2, endIter, preType)) {
			_lexs[_count] = "NUM";
			_vals[_count] = string(iter1, iter2);

			//writeLog
			constant::writeLog(string("match: ") + _lexs[_count] + "\t[" + _vals[_count] + "]");

			iter1 = iter2;
			preType = "NUM";
			++_count;
			continue;
		}

		//匹配运算符
		if (matchOperator(iter1, iter2, endIter)) {
			if (*iter1 == '+') {
				_lexs[_count] = "ADD";
				_vals[_count] = "+";
			}
			else if (*iter1 == '-') {
				_lexs[_count] = "SUB";
				_vals[_count] = "-";
			}
			else if (*iter1 == '*') {
				_lexs[_count] = "MUL";
				_vals[_count] = "*";
			}
			else if (*iter1 == '/') {
				_lexs[_count] = "DIV";
				_vals[_count] = "/";
			}
			else if(*iter1=='^'){
				_lexs[_count] = "POW";
				_vals[_count] = "^";
			}
			else throw Error(string("Error! lexical::driver()."));

			//writeLog
			constant::writeLog(string("match: ") + _lexs[_count] + "\t[" + _vals[_count] + "]");

			iter1 = iter2;
			preType = _lexs[_count];
			++_count;
			continue;
		}

		//匹配括号
		if (matchBracket(iter1, iter2, endIter)) {
			if (*iter1 == '(') {
				_lexs[_count] = "LB";
				_vals[_count] = "(";
			}
			else if(*iter1==')'){
				_lexs[_count] = "RB";
				_vals[_count] = ")";
			}
			else throw Error(string("Error! lexical::driver()."));

			//writeLog
			constant::writeLog(string("match: ") + _lexs[_count] + "\t[" + _vals[_count] + "]");

			iter1 = iter2;
			preType = _lexs[_count];
			++_count;
			continue;
		}
		
		//匹配空格
		if (iter2 != endIter && isWhiteSpace(*iter2)) {
			++iter2;
			++iter1;
			continue;
		}

		throw Error(string("NaN"));
	}
}