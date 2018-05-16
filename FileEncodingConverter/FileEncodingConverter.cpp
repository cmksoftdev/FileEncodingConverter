#include "FileEncodingConverter.h"

FileEncodingConverter::FileEncodingConverter(int buffersize = 512)
{
	iBuffersize = buffersize;
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
	ifstream t(filename_input);
	string str;

	t.seekg(0, ios::end);
	str.reserve(t.tellg());
	t.seekg(0, ios::beg);

	str.assign((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
	auto utf8string = iso_8859_1_to_utf8(str);
	t.close();

	ofstream out(filename_output);
	out << utf8string;
	out.close();
}

string FileEncodingConverter::iso_8859_1_to_utf8(string &str)
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