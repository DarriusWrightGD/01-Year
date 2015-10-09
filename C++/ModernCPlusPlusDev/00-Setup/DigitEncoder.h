#pragma once
#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

class DigitEncoder
{
 	static const int MAX_ENCODE_DIGITS_LENGTH = 3;
public:
	string encodeDigits(const string & word) const
	{
		string encoding;

		for (auto letter : word)
		{
			if (hasCompletedEncodingDigits(encoding))
			{
				break;
			}
			
			auto encodedDigit = encodeDigit(letter);

			if (encoding.empty() || (getLastDigit(encoding) != encodedDigit))
			{
				encoding += encodedDigit;
			}
		}

		return encoding;
	}
private:
	char lower(char c) const
	{
		return tolower(static_cast<unsigned char>(c));
	}

	bool hasCompletedEncodingDigits(const string & encoding) const
	{
		return encoding.length() == MAX_ENCODE_DIGITS_LENGTH;
	}

	string getLastDigit(const string & encoding) const
	{
		return encoding.substr(encoding.length() - 1);
	}

	string encodeDigit(char letter) const
	{
		const std::unordered_map<char, string> encodings{
			{ 'b', "1" },{ 'f', "1" },{ 'p', "1" },{ 'v', "1" },
			{ 'c', "2" },{ 'g', "2" },{ 'j', "2" },{ 'k', "2" },{ 'q', "2" },{ 's', "2" },{ 'x',"2" },{ 'z', "2" },
			{ 'd', "3" },{ 't', "3" },
			{ 'l', "4" },
			{ 'm',"5" },{ 'n', "5" },
			{ 'r', "6" }
		};
		auto it = encodings.find(lower(letter));
		return (it == encodings.end()) ? "" : encodings.find(letter)->second;
	}
};