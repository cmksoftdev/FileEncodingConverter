#pragma once
#include <string>
#include <fstream>
using namespace std;

class FileEncodingConverter
{
public:
	FileEncodingConverter();
	~FileEncodingConverter();

	void convert_win1252_to_utf8(string filename);
	void convert_win1252_to_utf8(string filename_input, string filename_output);

private:
	string _convert_win1252_to_utf8(string &str);
};