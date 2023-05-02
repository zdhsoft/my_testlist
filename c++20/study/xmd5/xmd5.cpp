// xmd5.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include "xmd5.h"

namespace zdh {

	const char* XHashMD5::hashName()
	{
		return "md5";
	}

	void XHashMD5::update(const void* paramData, const int paramDataBytes)
	{

	}

	const vector<unsigned char>& XHashMD5::digest(vector<unsigned char>& paramDigestData)
	{
		return paramDigestData;
	}

	const string & XHashMD5::digest(string& paramDigestString)
	{
		return paramDigestString;
	}

}


void calcMD5(const char * paramFileName) {
    zdh::XMD5 stMD5;
    stMD5.Init();
    zdh::XChar buff[4096];
    zdh::XChar md5sum[33];
    std::ifstream inFile(paramFileName, std::ifstream::binary);
	if (!inFile) {
		std::cout << "error" << std::endl;
		return;
	}
	while (inFile.read(buff, 4096)) { //一直读到文件结束
		auto readedBytes = (int)inFile.gcount(); //看刚才读了多少字节
        stMD5.Update(buff, readedBytes);
	}
    stMD5.Finish();
	inFile.close();
    std::cout << stMD5.GetMD5String(md5sum, false) << std::endl;
}

int main(int argc, char * argv[])
{
    for (int i = 0; i < argc; i++) {
        std::cout << "argv[" << i << "]=" << argv[i] << std::endl;
        if (i > 0) {
            calcMD5(argv[i]);
        }
    }
    std::cout << "Hello World!\n";
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
