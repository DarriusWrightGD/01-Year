#pragma once
#include "DigitEncoder.h"
#include <string>

using std::string;


class Soundex {

public:
	string encode(const string & word) const
	{
		return padWithZeros(uppercaseFront(getWordHead(word)) + digitEncoder.encodeDigits(getWordTail(word)));
	}
private:
	static const int MAX_ENCODE_LENGTH = 4;
	DigitEncoder digitEncoder;
	string getWordHead(const string & word) const 
	{
		return word.substr(0, 1);
	}

	string uppercaseFront(const string & word) const
	{
		return std::string(1, toupper(static_cast<char>(word.front())));
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