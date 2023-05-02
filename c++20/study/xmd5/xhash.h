#pragma once
#ifndef _X_HASH_H_
#define _X_HASH_H_
#include <cstddef>
#include <vector>
#include <string>
using namespace std;

class IHash {
	virtual const char* hashName() = 0;
	virtual void update(const void* paramData, const int paramDataBytes) = 0;
	virtual void digest(vector<unsigned char> & paramDigestData) = 0;
	virtual void digest(string& paramDigestString) = 0;
};
#endif