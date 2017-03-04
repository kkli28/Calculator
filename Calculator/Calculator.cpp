// Calculator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "lexical.h"
#include "syntax.h"
using namespace std;

const int MAX_SIZE = 1000;			//表达式最大支持1000个符号

//输出函数表
void printFuncs() {
	cout << "-------------------- " << endl;
	cout << "e 	自然底数" << endl;
	cout << "pi  	圆周率" << endl;
	cout << endl << "--------------------" << endl;
	cout << "abs 	取绝对值" << endl;
	cout << "ceil 	向上取整" << endl;
	cout << "exp 	e的n次方" << endl;
	cout << "floor 	向下取整" << endl;
	cout << "cos 	余弦" << endl;
	cout << "sin 	正弦" << endl;
	cout << "sqrt 	开平方" << endl;
	cout << "tan 	正切" << endl;
	cout << "log 	对数（e为底）" << endl;
	cout << "log2 	对数（2为底）" << endl;
	cout << "log10 	对数（10为底）" << endl;
}

int main() {
	cout << "计算器--v1.0  @kkli28" << endl;
	cout << "#: 结束\n*: 函数表\n" << endl;
	lexical lexer;
	syntax syntaxer;
	string expr;
	string lexs[MAX_SIZE];		//词法单元名
	string vals[MAX_SIZE];		//词法单元值
	int count = 0;				//词法单元个数
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

