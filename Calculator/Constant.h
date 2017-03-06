#pragma once

#include"stdafx.h"

namespace constant {
	//��������
	static const int FUNC_SIZE = 11;

	//LOG�ļ�
	static const string LOG_FILE = "log.txt";

	//����
	static const string functions[FUNC_SIZE] = {
		"abs","ceil","exp","floor","cos","sin","sqrt","tan","log","log2","log10"
	};

	//����־
	static void writeLog(string _str) {
		std::ofstream logFile(LOG_FILE, std::ofstream::app);
		logFile << _str << std::endl;
		logFile.close();
	}

	//�����־�ļ�
	static void clearLogFile() {
		std::ofstream logFile(LOG_FILE);
		logFile << std::endl;
		logFile.close();
	}

	//�Ǻ���
	static bool isFunction(string::iterator _begIter, string::iterator _endIter) {
		for (int i = 0; i < FUNC_SIZE; ++i) if (string(_begIter, _endIter) == functions[i]) return true;
		return false;
	}

	//��ȡ����
	static auto getFunction(string _str) -> double(*)(double) {
		if (_str == "abs") return abs;
		if (_str == "ceil") return ceil;
		if (_str == "exp") return exp;
		if (_str == "floor") return floor;
		if (_str == "cos") return cos;
		if (_str == "sin") return sin;
		if (_str == "sqrt") return sqrt;
		if (_str == "tan") return tan;
		if (_str == "log") return log;
		if (_str == "log2") return log2;
		if (_str == "log10") return log10;
		else throw Error("Error! Constant::getFunction().");
	}
}