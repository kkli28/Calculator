// Calculator.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "lexical.h"
#include "syntax.h"
using namespace std;

const int MAX_SIZE = 1000;			//���ʽ���֧��1000������

//���������
void printFuncs() {
	cout << "-------------------- " << endl;
	cout << "e 	��Ȼ����" << endl;
	cout << "pi  	Բ����" << endl;
	cout << endl << "--------------------" << endl;
	cout << "abs 	ȡ����ֵ" << endl;
	cout << "ceil 	����ȡ��" << endl;
	cout << "exp 	e��n�η�" << endl;
	cout << "floor 	����ȡ��" << endl;
	cout << "cos 	����" << endl;
	cout << "sin 	����" << endl;
	cout << "sqrt 	��ƽ��" << endl;
	cout << "tan 	����" << endl;
	cout << "log 	������eΪ�ף�" << endl;
	cout << "log2 	������2Ϊ�ף�" << endl;
	cout << "log10 	������10Ϊ�ף�" << endl;
}

int main() {
	cout << "������--v1.0  @kkli28" << endl;
	cout << "#: ����\n*: ������\n" << endl;
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
			else if (expr[0] == '*') {
				printFuncs();
				continue;
			}
			lexer.driver(expr, lexs, vals, count);
			cout << "\n = " << syntaxer.driver(lexs, vals, count) << endl;
		}
		catch (Error e) {
			cout << e.what() << endl;
		}
		catch (exception e) {
			cout << "Error! Calculator::main()." << endl;
		}
	} while (true);

	system("pause");
	return 0;
}

