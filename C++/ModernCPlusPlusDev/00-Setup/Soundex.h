#pragma once
#include "DigitEncoder.h"
#include <string>
using std::string;


class Soundex {

public:
	string encode(const string & word) const
	{
		return padWithZeros(getWordHead(word) + digitEncoder.encodeDigits(getWordTail(word)));
	}
private:
	static const int MAX_ENCODE_LENGTH = 4;
	DigitEncoder digitEncoder;
	string getWordHead(const string & word) const 
	{
		return word.substr(0, 1);
	}

	string getWordTail(const string & word) const
	{
		return word.substr(1);
	}

	string padWithZeros(const string & word) const
	{
		auto zerosNeeded = MAX_ENCODE_LENGTH - word.length();
		return word + string(zerosNeeded,'0');
	}
};