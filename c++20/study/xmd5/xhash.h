#pragma once
#ifndef _X_HASH_H_
#define _X_HASH_H_


class IHash {
	virtual const char* hashName() = 0;
	virtual void update(const void* paramData, const int paramDataBytes) = 0;
	virtual void digest(const char[16] paramData) = 0;

};
#endif