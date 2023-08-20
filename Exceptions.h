#pragma once

#include<iostream>
using namespace std;

#pragma region Exceptions


class Exception {

public:
	string text;
	string source;
	int line;
	string date;


	Exception(const string& text,
		const string& source,
		const int& line,
		const string& date)
		:text(text), source(source), line(line), date(date)
	{

	}

	virtual void PrintMessage() const {
		cout << "+++++++Error Info+++++++" << endl;
		cout << "Error content : " << text << endl;
		cout << "Source : " << source << endl;
		cout << "Line Number : " << line << endl;
		cout << "Date : " << date << endl;
	}
};

class DataBaseException :public Exception {

public:

	DataBaseException(const string& text, const string& source,
		const int& line, const string& date)
		:Exception(text, source, line, date)
	{
	}


	void PrintMessage()const override {
		cout << "+++++++ DATA BASE EXCEPTION +++++++" << endl;
		Exception::PrintMessage();
	}
};


class InvalidArgumentException :public Exception {

public:


	InvalidArgumentException(const string& text,
		const string& source, const int& line,
		const string& date)
		:Exception(text, source, line, date)
	{

	}

	void PrintMessage()const override {
		cout << "+++++++INVALID ARGUMENT EXCEPTION+++++++" << endl;
		Exception::PrintMessage();
	}
};

#pragma endregion




