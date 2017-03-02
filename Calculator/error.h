#pragma once

#include"stdafx.h"

using std::string;

class Error {
private:
	string err;
public:
	Error(string e="error") :err(e) {}
	string what()const { return err; }
};