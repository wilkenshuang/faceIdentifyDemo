#pragma once
#ifndef BASE64_H_
#define BASE64_H_
#include <string>
using namespace std;
string Encode(const unsigned char * Data, int DataByte);
string Decode(const char * Data, int DataByte, int & OutByte);
#endif
