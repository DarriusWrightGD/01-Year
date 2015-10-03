#pragma once
#include <string>
#include <unordered_map>
using std::string;
class Soundex {

public:
	string encode(const string & word) const
	{
		return padWithZeros(getWordHead(word) + encodeDigits(getWordTail(word)));
	}
private:
	string getWordHead(const string & word) const 
	{
		return word.substr(0, 1);
	}

	string getWordTail(const string & word) const
	{
		return word.substr(1);
	}

	string encodeDigits(const string & word) const
	{
		string encoding;

		for (auto letter : word)
		{
			encoding += encodedDigit(letter);
		}

		return encoding;
	}

	string encodedDigit(char letter) const
	{
		const std::unordered_map<char, string> encodings{
			{'b', "1"},{'f', "1"}, {'p', "1"}, {'v', "1"},
			{'c', "2"},{'g', "2"}, {'j', "2"}, {'k', "2"}, {'q', "2"},{'s', "2"},{'x',"2"},{'z', "2"},
			{'d', "3"},{'t', "3"},
			{'l', "4"},
			{'m',"5"}, {'n', "5"},
			{'r', "6"}
		};
		auto it = encodings.find(letter);
		return (it == encodings.end()) ? "" : encodings.find(letter)->second;
	}

	string padWithZeros(const string & word) const
	{
		auto zerosNeeded = 4 - word.length();
		return word + string(zerosNeeded,'0');
	}
};