#include"stdafx.h"
#include"syntax.h"
using namespace std;

//E
void syntax::E(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	if (_begIndex == _endIndex) throw Error("NaN");

	//E --> TA

	//writeLog
	constant::writeLog(_format + "E --> TA");

	T(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
	A(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
}

//A
void syntax::A(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	if (_begIndex != _endIndex) {
		string str = _lexs[_begIndex];

		//A --> +TA
		if (str == "ADD" || str == "SUB") {

			//writeLog
			if (str == "ADD") constant::writeLog(_format + "A --> +TA");
			else constant::writeLog(_format + "A --> -TA");

			//writeLog
			constant::writeLog(_format + "    [" + _vals[_begIndex] + "]");

			int index = _begIndex;
			++_begIndex;
			T(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
			_stk.push(_vals[index]);
			A(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
		}
	}
	else {
		//A --> null

		//writeLog
		constant::writeLog(_format + "A --> null");

		//writeLog
		constant::writeLog(_format + "    [null]");
	}
}

//T
void syntax::T(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	//T --> FB

	//writeLog
	constant::writeLog(_format + "T --> TB");

	F(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
	B(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
}

//B
void syntax::B(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	if (_begIndex != _endIndex) {
		string str = _lexs[_begIndex];

		//B --> *FB
		if (str == "MUL" || str == "DIV") {


			//writeLog
			if (str == "MUL") constant::writeLog(_format + "B --> *FB");
			else constant::writeLog(_format + "B --> /FB");

			//writeLog
			constant::writeLog(_format + "    [" + _vals[_begIndex] + "]");

			int index = _begIndex;
			++_begIndex;
			F(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
			_stk.push(_vals[index]);
			B(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
		}
	}
	else {
		//B --> null

		//writeLog
		constant::writeLog(_format + "B --> null");

		//writeLog
		constant::writeLog(_format + "    [null]");
	}
}

//F
void syntax::F(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	//F --> MN

	//writeLog
	constant::writeLog(_format + "F --> MN");

	M(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
	N(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
}

//N
void syntax::N(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	if (_begIndex != _endIndex) {
		string str = _lexs[_begIndex];

		//N --> ^MN
		if (str == "POW") {

			//writeLog
			constant::writeLog(_format + "N --> ^MN");

			//writeLog
			constant::writeLog(_format + "    [" + _vals[_begIndex] + "]");

			int index = _begIndex;
			++_begIndex;
			M(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
			_stk.push(_vals[index]);
			N(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
		}
	}
	else {
		//N --> null

		//writeLog
		constant::writeLog(_format + "N --> null");

		//writeLog
		constant::writeLog(_format + "    [null]");
	}
}

//M
void syntax::M(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	if (_begIndex != _endIndex) {

		string str = _lexs[_begIndex];
		//M --> i
		if (str == "NUM" || str == "E" || str == "PI") {

			//writeLog
			constant::writeLog(_format + "M --> i");

			//writeLog
			constant::writeLog(_format + "    [" + _vals[_begIndex] + "]");

			_stk.push(_vals[_begIndex]);
			++_begIndex;
			return;
		}

		//M --> func(E)
		else if (str == "FUNC") {

			//writeLog
			constant::writeLog(_format + "M --> func(E)");

			//writeLog
			constant::writeLog(_format + "    [" + _vals[_begIndex] + "]");

			string func = _vals[_begIndex];
			++_begIndex;
			if (_begIndex != _endIndex && _lexs[_begIndex] == "LB") {

				//writeLog
				constant::writeLog(_format + string("    [") + _vals[_begIndex] + string("]"));

				++_begIndex;
				E(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
				_stk.push(func);
				if (_begIndex != _endIndex && _lexs[_begIndex] == "RB") {

					//writeLog
					constant::writeLog(_format + "    [" + _vals[_begIndex] + "]");

					++_begIndex;
					return;
				}
				else {

					//writeLog
					constant::writeLog(_format + "没有匹配到右括号");

					throw Error("NaN");
				}
			}
			else {

				//writeLog
				constant::writeLog(_format + "没有匹配到左括号");

				throw Error("NaN");
			}
		}

		//M --> (E)
		else if (str == "LB") {

			//writeLog
			constant::writeLog(_format + "M --> (E)");

			//writeLog
			constant::writeLog(_format + "    [" + _vals[_begIndex] + "]");

			++_begIndex;
			E(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
			if (_begIndex != _endIndex && _lexs[_begIndex] == "RB") {

				//writeLog
				constant::writeLog(_format + "    [" + _vals[_begIndex] + "]");
				++_begIndex;
				return;
			}
			else {

				//writeLog
				constant::writeLog(_format + "没有匹配到右括号");

				throw Error("NaN");
			}
		}
	}
	else {

		//log
		constant::writeLog(string("到达表达式末尾") + "    _begIndex: " + to_string(_begIndex) + "    _endIndex: " + to_string(_endIndex));

		throw Error(string("NaN"));
	}
}

//字符串转化为数字
double syntax::strToDouble(string& _str) {
	int size = _str.size();
	double result = 0;
	bool positive = true;
	int i = 0;
	if (_str[i] == '+') ++i;
	else if (_str[i] == '-') {
		++i;
		positive = false;
	}
	for (; i < size; ++i) {
		if (_str[i] >= 0x30 && _str[i] <= 0x39) result = _str[i] - 0x30 + result * 10;
		else if (_str[i] == '.') {
			double temp = 0;
			int j = i + 1;
			int cnt = size - j;
			for (; j < size; ++j) temp = _str[j] - 0x30 + temp * 10;
			for (j = 0; j < cnt; ++j) temp /= 10;
			result = result + temp;
			break;
		}
		else throw Error(string("NaN"));
	}

	result = positive ? result : -result;

	//当result==0，且positive==false（原数为负）时，会返回-0（错误），所以在这里纠正（不好的方式）
	if (result == 0) return 0;
	return result;
}

//驱动函数
double syntax::driver(string _lexs[], string _vals[], int _count) {
	int index = 0;
	stack<string> stk;			//保存反后缀式

	//TEST
	E(_lexs, _vals, index, _count, "", stk);

	if (stk.empty()) return 0;

	//log
	constant::writeLog("\n栈信息: ");

	stack<string> rvStack;		//保存正序的后缀式
	while (!stk.empty()) {
		rvStack.push(stk.top());
		constant::writeLog(rvStack.top());
		stk.pop();
	}

	string topStr = "";					//栈顶元素
	string numStr1 = "";				//存储第一个操作数的字符串
	string numStr2 = "";				//存储第二个操作数的字符串
	double result = 0;					//计算结果

	//log
	string logStr;
	for (int i = 0; i < _count; ++i)
		logStr += _vals[i];
	constant::writeLog(string("\nExpr: ") + logStr + "\n");

	while (!rvStack.empty()) {
		topStr = rvStack.top();
		rvStack.pop();
		if (topStr == "+" || topStr == "-" || topStr == "*" || topStr == "/" || topStr == "^") {
			if (stk.size() < 2) throw Error("Error! syntax::driver().");
			numStr1 = stk.top();						//注意！！！第二个操作数（在栈顶）
			stk.pop();
			numStr2 = stk.top();						//第一个操作数
			stk.pop();

			double num1 = strToDouble(numStr2);
			double num2 = strToDouble(numStr1);

			if (topStr == "+") result = num1 + num2;
			else if (topStr == "-") result = num1 - num2;
			else if (topStr == "*") result = num1*num2;
			else if (topStr == "/") result = num1 / num2;
			else if (topStr == "^") result = pow(num1, num2);	//没法自己实现浮点数的乘方，故调用标准库pow函数
			else throw Error("Error! syntax::driver().");
			stk.push(to_string(result));				//保存结果

			//writeLog
			constant::writeLog(to_string(num1) + " " +
				topStr + " " + to_string(num2) + " = " + to_string(result));
		}
		else if (constant::isFunction(topStr.begin(), topStr.end())) {
			numStr1 = stk.top();
			stk.pop();
			double num1 = strToDouble(numStr1);

			result = constant::getFunction(topStr)(num1);

			//writeLog
			constant::writeLog(topStr + "(" + to_string(num1) + ")" + " = " + to_string(result));

			stk.push(to_string(result));
		}
		else stk.push(topStr);							//是数字，则保存与另一个栈中
	}
	if (stk.empty()) throw Error("Error! syntax::driver().");

	return strToDouble(stk.top());
}