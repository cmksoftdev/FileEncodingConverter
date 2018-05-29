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

//TODO adjust expected char array
int test_file2()
{
	char expected[] =
	{
		0x01, 0x02, 0xC3, 0xBC, 0xC3, 0xA4, 0x20, 0x48,
		0x61, 0x6C, 0x6C, 0x6F, 0x20, 0x68, 0x61, 0x6C,
		0x6C, 0x6F, 0x20, 0xC3, 0xB6, 0xC3, 0xBC, 0xC3,
		0xA4, 0x20, 0xC3, 0xA4, 0xC3, 0xBC, 0xC3, 0xB6
	};
	auto file = get_file_content("output2.txt");

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

void create_file2()
{
	ofstream ofs("input2.txt");
	char filecontent[224];
	for (size_t i = 32; i < 255; i++) filecontent[i-32] = i;
	filecontent[223] = '\0';
	ofs << filecontent;
	ofs.close();
}

int tinyTest()
{
	//Arrange
	create_file();
	FileEncodingConverter sut;

	//Act
	sut.convert_win1252_to_utf8("input.txt", "output.txt");

	//Assert to be 0
	return test_file();
}

int NilsTest()
{
	//Arrange
	create_file2();
	FileEncodingConverter sut;

	//Act
	sut.convert_win1252_to_utf8("input2.txt", "output2.txt");

	//Assert to be 0
	return test_file();
}

int main()
{
	int testResult_1 = tinyTest();
	int testResult_2 = NilsTest();
	return testResult_1 + testResult_2;
}