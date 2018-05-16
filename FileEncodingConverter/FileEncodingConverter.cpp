#include "FileEncodingConverter.h"

FileEncodingConverter::FileEncodingConverter()
{
}

FileEncodingConverter::~FileEncodingConverter()
{
}

void FileEncodingConverter::convert_win1252_to_utf8(string filename)
{
	convert_win1252_to_utf8(filename, filename);
}

void FileEncodingConverter::convert_win1252_to_utf8(string filename_input, string filename_output)
{
	ifstream in(filename_input);
	string inputString;

	in.seekg(0, ios::end);
	inputString.reserve(in.tellg());
	in.seekg(0, ios::beg);

	inputString.assign((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
	auto utf8string = _convert_win1252_to_utf8(inputString);
	in.close();

	ofstream out(filename_output);
	out << utf8string;
	out.close();
}

string FileEncodingConverter::_convert_win1252_to_utf8(string &str)
{
	string strOut;
	for (string::iterator it = str.begin(); it != str.end(); ++it)
	{
		uint8_t ch = *it;
		if (ch < 0x80)
		{
			strOut.push_back(ch);
		}
		else
		{
			strOut.push_back(0xc0 | ch >> 6);
			strOut.push_back(0x80 | (ch & 0x3f));
		}
	}
	return strOut;
}