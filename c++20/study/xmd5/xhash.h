#pragma once
#ifndef _X_HASH_H_
#define _X_HASH_H_
#include <cstddef>
#include <vector>
#include <string>
using namespace std;
namespace zdh {
	// 数据计算hash的接口
	class IHash {
	public:
		virtual const char* hashName() = 0;
		virtual void update(const void* paramData, const int paramDataBytes) = 0;
		virtual const vector<unsigned char> & digest(vector<unsigned char>& paramDigestData) = 0;
		virtual const string & digest(string& paramDigestString) = 0;
	};
}

#endif