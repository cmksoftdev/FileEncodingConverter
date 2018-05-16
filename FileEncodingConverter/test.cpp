#include "FileEncodingConverter.h"
#include <vector>

vector<char> get_file_content(string filename)
{
	ifstream ifs(filename, ios::binary | ios::ate);
	ifstream::pos_type pos = ifs.tellg();
	vector<char> result(pos);

	ifs.seekg(0, ios::beg);
	ifs.read(&result[0], pos);
	ifs.close();

	return result;
}

int test_file()
{
	char expected[] = 
	{ 
		0xC3, 0xB6, 0xC3, 0xBC, 0xC3, 0xA4, 0x20, 0x48,
		0x61, 0x6C, 0x6C, 0x6F, 0x20, 0x68, 0x61, 0x6C,
		0x6C, 0x6F, 0x20, 0xC3, 0xB6, 0xC3, 0xBC, 0xC3,
		0xA4, 0x20, 0xC3, 0xA4, 0xC3, 0xBC, 0xC3, 0xB6 
	};
	auto file = get_file_content("output.txt");

	if (file.size() != 32) return -2;
	for (size_t i = 0; i < file.size(); i++)
		if (file.at(i) != expected[i]) return -1;
	return 0;
}

void create_file()
{
	ofstream ofs("input.txt");
	char filecontent[] = 
	{
		0xF6, 0xFC, 0xE4, 0x20, 0x48, 0x61, 0x6C, 0x6C,
		0x6F, 0x20, 0x68, 0x61, 0x6C, 0x6C, 0x6F, 0x20,
		0xF6, 0xFC, 0xE4, 0x20, 0xE4, 0xFC, 0xF6, 0x00
	};
	ofs << filecontent;
	ofs.close();
}

int main()
{
	//Arrange
	create_file();
	FileEncodingConverter sut;

	//Act
	sut.convert_win1252_to_utf8("input.txt", "output.txt");

	//Assert to be 0
	return test_file();
}