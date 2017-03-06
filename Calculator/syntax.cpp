#include"stdafx.h"
#include"syntax.h"
using namespace std;

//E
void syntax::E(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	//E --> null
	if (_begIndex == _endIndex) throw Error("NaN");

	//E --> TA

	//log
	constant::log(_format+"E --> TA");

	T(_lexs, _vals, _begIndex, _endIndex, _format + "E", _stk);
	A(_lexs, _vals, _begIndex, _endIndex, _format + "E", _stk);
}

//A
void syntax::A(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	if (_begIndex != _endIndex) {
		string str = _lexs[_begIndex];

		//A --> +TA
		if (str == "ADD" || str == "SUB") {

			//log
			constant::log(_format + "A --> +TA");

			int index = _begIndex;
			++_begIndex;
			T(_lexs, _vals, _begIndex, _endIndex, _format + "A", _stk);
			_stk.push(_vals[index]);
			A(_lexs, _vals, _begIndex, _endIndex, _format + "A", _stk);
		}
	}
	else {
		//A --> null
		//log
		constant::log(_format + "A --> null");
	}
}

//T
void syntax::T(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	//T --> FB

	//log
	constant::log(_format + "T --> TB");

	F(_lexs, _vals, _begIndex, _endIndex, _format + "T", _stk);
	B(_lexs, _vals, _begIndex, _endIndex, _format + "T", _stk);
}

//B
void syntax::B(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	if (_begIndex != _endIndex) {
		string str = _lexs[_begIndex];

		//B --> *FB
		if (str == "MUL" || str == "DIV") {

			//log
			constant::log(_format + "B --> *FB");

			int index = _begIndex;
			++_begIndex;
			F(_lexs, _vals, _begIndex, _endIndex, _format + "B", _stk);
			_stk.push(_vals[index]);
			B(_lexs, _vals, _begIndex, _endIndex, _format + "B", _stk);
		}
	}
	else {
		//B --> null
		//log
		constant::log(_format + "B --> null");
	}
}

//F
void syntax::F(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	//F --> MN

	//log
	constant::log(_format + "F --> MN");

	M(_lexs, _vals, _begIndex, _endIndex, _format + "F", _stk);
	N(_lexs, _vals, _begIndex, _endIndex, _format + "F", _stk);
}

//N
void syntax::N(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	if (_begIndex != _endIndex) {
		string str = _lexs[_begIndex];

		//N --> ^MN
		if (str == "POW") {

			//log
			constant::log(_format + "N --> ^MN");

			int index = _begIndex;
			++_begIndex;
			M(_lexs, _vals, _begIndex, _endIndex, _format + "N", _stk);
			_stk.push(_vals[index]);
			N(_lexs, _vals, _begIndex, _endIndex, _format + "N", _stk);
		}
	}
	else {
		//N --> null

		//log
		constant::log(_format + "N --> null");
	}
}

//M
void syntax::M(string _lexs[], string _vals[], int& _begIndex, int& _endIndex, string _format, stack<string>& _stk) {
	if (_begIndex != _endIndex) {

		string str = _lexs[_begIndex];
		//M --> i
		if (str == "NUM" || str=="E" || str=="PI") {

			//log
			constant::log(_format + "M --> i");

			_stk.push(_vals[_begIndex]);
			++_begIndex;
			return;
		}

		//M --> func(E)
		else if (str == "FUNC") {

			//log
			constant::log(_format + "M --> func(E)");

			string func = _vals[_begIndex];
			++_begIndex;
			if (_begIndex != _endIndex && _lexs[_begIndex] == "LB") {
				++_begIndex;
				E(_lexs, _vals, _begIndex, _endIndex, _format + "M", _stk);
				_stk.push(func);
				if (_begIndex != _endIndex && _lexs[_begIndex] == "RB") {
					++_begIndex;
					return;
				}
				else {
					throw Error("NaN");

					//log
					constant::log(_format + "û��ƥ�䵽������");
				}
			}
			else {
				throw Error("NaN");

				//log
				constant::log(_format + "û��ƥ�䵽������");
			}
		}

		//M --> (E)
		else if (str == "LB") {

			//log
			constant::log(_format + "M --> (E)");

			++_begIndex;
			E(_lexs, _vals, _begIndex, _endIndex, _format + "M", _stk);
			if (_begIndex != _endIndex && _lexs[_begIndex] == "RB") {
				++_begIndex;
				return;
			}
			else {
				throw Error("NaN");

				//log
				constant::log(_format + "û��ƥ�䵽������");
			}
		}
	}

	throw Error(string("NaN"));
}

//�ַ���ת��Ϊ����
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
		else throw Error(string("NaN"));
	}

	result = positive ? result : -result;

	//��result==0����positive==false��ԭ��Ϊ����ʱ���᷵��-0�����󣩣�������������������õķ�ʽ��
	if (result == 0) return 0;
	return result;
}

//��������
double syntax::driver(string _lexs[], string _vals[], int _count) {
	int index = 0;
	stack<string> stk;			//���淴��׺ʽ

	//TEST
	E(_lexs, _vals, index, _count, "", stk);

	if (stk.empty()) return 0;

	stack<string> rvStack;		//��������ĺ�׺ʽ
	while (!stk.empty()) {
		rvStack.push(stk.top());
		stk.pop();
	}

	string topStr = "";					//ջ��Ԫ��
	string numStr1 = "";				//�洢��һ�����������ַ���
	string numStr2 = "";				//�洢�ڶ������������ַ���
	double result = 0;					//������

	while (!rvStack.empty()) {
		topStr = rvStack.top();
		rvStack.pop();
		if (topStr == "+" || topStr == "-" || topStr == "*" || topStr == "/" || topStr == "^") {
			if (stk.size() < 2) throw Error("Error! syntax::driver().");
			numStr1 = stk.top();						//ע�⣡�����ڶ�������������ջ����
			stk.pop();
			numStr2 = stk.top();						//��һ��������
			stk.pop();

			double num1 = strToDouble(numStr2);
			double num2 = strToDouble(numStr1);
			if (topStr == "+") result = num1 + num2;
			else if (topStr == "-") result = num1 - num2;
			else if (topStr == "*") result = num1*num2;
			else if (topStr == "/") result = num1 / num2;
			else if (topStr == "^") result = pow(num1, num2);	//û���Լ�ʵ�ָ������ĳ˷����ʵ��ñ�׼��pow����
			else throw Error("Error! syntax::driver().");
			stk.push(to_string(result));				//������
		}
		else if (constant::isFunction(topStr.begin(), topStr.end())) {
			numStr1 = stk.top();
			stk.pop();
			double num1 = strToDouble(numStr1);
			result= constant::getFunction(topStr)(num1);
			stk.push(to_string(result));
		}
		else stk.push(topStr);							//�����֣��򱣴�����һ��ջ��
	}
	if (stk.empty()) throw Error("Error! syntax::driver().");

	return strToDouble(stk.top());
}