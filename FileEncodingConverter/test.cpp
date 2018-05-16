#include "FileEncodingConverter.h"

void main()
{
	auto a = new FileEncodingConverter(512);
	a->convert_win1252_to_utf8("test.txt");
}