#include "FileEncodingConverter.h"

void main()
{
	auto converter = new FileEncodingConverter();
	converter->convert_win1252_to_utf8("test.txt", "output.txt");
}