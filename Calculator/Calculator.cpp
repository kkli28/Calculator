// Calculator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "lexical.h"
#include "syntax.h"
using namespace std;

const int MAX_SIZE = 1000;			//表达式最大支持1000个符号

int main() {
	cout << "计算器--v1.0  @kkli28\n\n支持带括号浮点数的 加、减、乘、除、乘方运算.\n输入 # 结束。\n" << endl;
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
			lexer.driver(expr, lexs, vals, count);
			//for (int i = 0; i < count; ++i) cout << lexs[i] << " : " << vals[i] << endl;
			cout << "result: " << syntaxer.driver(lexs, vals, count) << endl;
		}
		catch (Error e) {
			cout << e.what() << endl;
		}
		catch (exception e) {
			cout << "未知错误!Calculator::main()." << endl;
		}
	} while (true);
	return 0;
}

