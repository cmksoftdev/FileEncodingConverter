#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
using namespace std;

class FileEncodingConverter
{
public:
	FileEncodingConverter(int buffersize);
	~FileEncodingConverter();

	void convert_win1252_to_utf8(string filename);
	void convert_win1252_to_utf8(string filename_input, string filename_output);

private:
	int iBuffersize;

	string iso_8859_1_to_utf8(string &str);
};