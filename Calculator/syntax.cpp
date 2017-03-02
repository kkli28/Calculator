#include"stdafx.h"
#include"syntax.h"
using namespace std;

//E
void syntax::E(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	//cout << _format << "E: " << endl;

	if (_begIndex == _endIndex) {
		//cout << _format << "    match: null" << endl;
		return;
	}

	//E --> TA
	T(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
	A(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
}

//A
void syntax::A(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	//cout << _format << "A: " << endl;
	if (_begIndex != _endIndex) {
		string str = _lexs[_begIndex];

		//A --> +TA
		if (str == "ADD" || str == "SUB") {
			//cout << _format + "    match: " << _vals[_begIndex] << endl;
			int index = _begIndex;
			++_begIndex;
			T(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
			_stk.push(_vals[index]);
			A(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
		}
	}

	//A --> null
	//cout << _format + "    match: null" << endl;
}

//T
void syntax::T(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	//cout << _format << "T: " << endl;

	//T --> FB
	F(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
	B(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
}

//B
void syntax::B(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	//cout << _format << "B: " << endl;
	if (_begIndex != _endIndex) {
		string str = _lexs[_begIndex];

		//B --> *FB
		if (str == "MUL" || str == "DIV") {
			//cout << _format + "    match: " << _vals[_begIndex] << endl;
			int index = _begIndex;
			++_begIndex;
			F(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
			_stk.push(_vals[index]);
			A(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
		}
	}

	//B --> null
	//cout << _format + "    match: null" << endl;
}

//F
void syntax::F(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	//cout << _format << "F: " << endl;

	//F --> MN
	M(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
	N(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
}

//N
void syntax::N(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	//cout << _format << "N: " << endl;
	if (_begIndex != _endIndex) {
		string str = _lexs[_begIndex];

		//N --> ^MN
		if (str == "POW") {
			//cout << _format + "    match: " << _vals[_begIndex] << endl;
			int index = _begIndex;
			++_begIndex;
			M(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
			_stk.push(_vals[index]);
			N(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
		}
	}
	//N --> null
	//cout << _format + "    match: null" << endl;
}

//M
void syntax::M(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	//cout << _format << "M: " << endl;
	if (_begIndex != _endIndex) {

		//M --> i
		if (_lexs[_begIndex] == "NUM") {
			//cout << _format << "    match: " << _vals[_begIndex] << endl;
			_stk.push(_vals[_begIndex]);
			++_begIndex;
			return;
		}

		//M --> (E)
		else if (_lexs[_begIndex] == "LB") {
			//cout << _format << "    match: " << _vals[_begIndex] << endl;
			++_begIndex;
			E(_lexs, _vals, _begIndex, _endIndex, _format + "    ", _stk);
			if (_begIndex != _endIndex && _lexs[_begIndex] == "RB") {
				//cout << _format << "    match: " << _vals[_begIndex] << endl;
				++_begIndex;
				return;
			}
		}
	}
	throw Error(string("错误的符号: ") + _vals[_begIndex]);
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
			int j=i+1;
			int cnt = size - j;
			for (; j < size; ++j) temp = _str[j] - 0x30 + temp * 10;
			for (j = 0; j < cnt; ++j) temp /= 10;
			result = result + temp;
			break;
		}
		else throw Error(string("未知的符号!")+_str[i]);
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
	E(_lexs, _vals, index, _count, "", stk);
	if (stk.empty()) return 0;

	stack<string> rvStack;		//保存正序的后缀式
	while (!stk.empty()) {
		rvStack.push(stk.top());
		stk.pop();
	}

	string topStr = "";					//栈顶元素
	string numStr1 = "";				//存储第一个操作数的字符串
	string numStr2 = "";				//存储第二个操作数的字符串
	double result = 0;					//计算结果

	while (!rvStack.empty()) {
		topStr = rvStack.top();
		rvStack.pop();
		if (topStr == "+" || topStr == "-" || topStr == "*" || topStr == "/" || topStr == "^") {
			if (stk.size() < 2) throw Error("未知错误!syntax::driver().");
			numStr1 = stk.top();						//注意！！！第二个操作数（在栈顶）
			stk.pop();
			numStr2 = stk.top();						//第一个操作数
			stk.pop();

			double num1 = strToDouble(numStr2);
			double num2 = strToDouble(numStr1);
			//cout << num1 << topStr << num2 << endl;
			if (topStr == "+") result = num1 + num2;
			else if (topStr == "-") result = num1 - num2;
			else if (topStr == "*") result = num1*num2;
			else if (topStr == "/") result = num1 / num2;
			else if (topStr == "^") result = pow(num1, num2);	//没法自己实现浮点数的乘方，故调用标准库pow函数
			else throw Error("未知错误!syntax::driver().");

			stk.push(to_string(result));				//保存结果
		}
		else stk.push(topStr);							//是数字，则保存与另一个栈中
	}
	if (stk.empty()) throw Error("未知错误!syntax::driver().");
	return strToDouble(stk.top());
}