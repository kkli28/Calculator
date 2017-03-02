#include"stdafx.h"
#include"lexical.h"
using namespace std;

//ƥ��
bool lexical::matchNumber(string::iterator& _iter1, string::iterator& _iter2, string::iterator& _endIter, string& _preType) {
	//��һ���ַ�Ϊ+��-�����������ֵķ��ţ�Ҳ�����ǲ�����
	if (_iter2!=_endIter && (*_iter2 == '+' || *_iter2 == '-')) {

		//��������ַ������֣����ж�ǰһ��ƥ�䵽���Ƿ������֡�
		//����ǣ���Ϊ�����������ǰһ��ƥ�䵽��������ж�Ϊ���ֵķ��š�
		if (_iter2 + 1 != _endIter && isNumber(*(_iter2 + 1))) {
			if (_preType == "NUM")
				return false;
			else
				++_iter2;
		}

		//+��-���治�����֣���ֱ���˳�
		else return false;
	}

	//�����������ֲ���
	while (_iter2 != _endIter && isNumber(*_iter2)) ++_iter2;
	if (_iter1 == _iter2) return false;

	//������'.'����С�����һλΪ���֣����ж�ΪС���㣬��������ƥ�䵽�˽���
	if (_iter2 != _endIter && *_iter2 == '.') {

		//С�������������
		if ((_iter2 + 1) != _endIter && isNumber(*(_iter2 + 1))) {

			//����С���㣬���������к�������
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
		//cout << "match Operator: " << *_iter2 << endl;
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

//��������
void lexical::driver(string& _expr, string _lexs[], string _vals[], int& _count) {

	//iter1���ƥ�������λ�ã�iter2ͨ������matchXXX�����޸ģ����ƥ�����βλ��
	//��ƥ��ɹ�����[*iter1,*iter2)Ϊƥ��Ľ��
	auto iter1 = _expr.begin();
	auto iter2 = iter1;
	auto endIter = _expr.end();
	string preType;						//ǰһ��ƥ��Ĵʷ���Ԫ����
	_count = 0;
	
	while (iter2 != endIter) {
		//cout << *iter2 << endl;

		//ƥ������
		if (matchNumber(iter1, iter2, endIter, preType)) {
			_lexs[_count] = "NUM";
			_vals[_count] = string(iter1, iter2);

			//cout << "match NUM: " << _vals[_count] << endl;

			iter1 = iter2;
			preType = "NUM";
			++_count;
			continue;
		}

		//ƥ�������
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
			else throw Error(string("����ķ���: ")+*iter1);

			//cout << "match OP: " << _vals[_count] << endl;

			iter1 = iter2;
			preType = _lexs[_count];
			++_count;
			continue;
		}

		//ƥ������
		if (matchBracket(iter1, iter2, endIter)) {
			if (*iter1 == '(') {
				_lexs[_count] = "LB";
				_vals[_count] = "(";
			}
			else {
				_lexs[_count] = "RB";
				_vals[_count] = ")";
			}

			//cout << "match BR: " << _vals[_count] << endl;

			iter1 = iter2;
			preType = _lexs[_count];
			++_count;
			continue;
		}
		 
		//ƥ��ո�
		if (iter2 != endIter && isWhiteSpace(*iter2)) {
			++iter2;
			++iter1;
			continue;
		}

		throw Error(string("����ķ���: ") + *iter1);
	}
}