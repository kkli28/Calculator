// Calculator.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "lexical.h"
#include "syntax.h"
using namespace std;

const int MAX_SIZE = 1000;			//���ʽ���֧��1000������

int main() {
	cout << "������--v1.0  @kkli28\n\n֧�ִ����Ÿ������� �ӡ������ˡ������˷�����.\n���� # ������\n" << endl;
	lexical lexer;
	syntax syntaxer;
	string expr;
	string lexs[MAX_SIZE];		//�ʷ���Ԫ��
	string vals[MAX_SIZE];		//�ʷ���Ԫֵ
	int count = 0;				//�ʷ���Ԫ����
	do {
		count = 0;
		cout << "\n>> ";
		try {
			getline(cin, expr);
			if (expr[0] == '#') break;
			lexer.driver(expr, lexs, vals, count);
			//for (int i = 0; i < count; ++i) cout << lexs[i] << " : " << vals[i] << endl;
			cout << "result: " << syntaxer.driver(lexs, vals, count) << endl;
		}
		catch (Error e) {
			cout << e.what() << endl;
		}
		catch (exception e) {
			cout << "δ֪����!Calculator::main()." << endl;
		}
	} while (true);
	return 0;
}

