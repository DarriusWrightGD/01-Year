#include <gtest\gtest.h>
#include <Soundex.h>
#include <iostream>
using namespace testing;
using std::cout;
using std::endl;

/*
– Write production code only to make a failing test pass.
– Write no more of a unit test than sufficient to fail. Compilation failures are failures.
– Write only the production code needed to pass the one failing test.

1. Retain the first letter. Drop all other occurrences of a, e, i, o, u, y, h, w.
2. Replace consonants with digits (after the first letter):
• b, f, p, v: 1
• c, g, j, k, q, s, x, z: 2
• d, t : 3
• l: 4
• m, n: 5
• r: 6
3. If two adjacent letters encode to the same number,
encode them instead as a single number. Also, do so if two letters with
the same number are separated by h or w (but code them twice if separated by a vowel).
This rule also applies to the first letter.
4. Stop when you have a letter and three digits. Zero-pad if needed
*/



class SoundexTest : public Test
{
public:
	Soundex soundex;
	virtual void SetUp() override
	{
		cout << "Setting up" << endl;
	}
	virtual void TearDown()override
	{
		cout << "Tearing Down" << endl;
	}
};

TEST_F(SoundexTest, RetainsSoleLetterOfOneLetterWord)
{
	EXPECT_EQ("A000", soundex.encode("A"));
}

TEST_F(SoundexTest, PadsWithZerosToEnsureThreeDigits)
{
	EXPECT_EQ("I000", soundex.encode("I"));
}

TEST_F(SoundexTest, ReplaceTheConstantsWithDigits)
{
	EXPECT_EQ("A100", soundex.encode("Ab"));
	EXPECT_EQ("A200", soundex.encode("Ac"));
	EXPECT_EQ("A300", soundex.encode("Ad"));
	EXPECT_EQ("A400", soundex.encode("Al"));
	EXPECT_EQ("A500", soundex.encode("Am"));
	EXPECT_EQ("A600", soundex.encode("Ar"));
}

TEST_F(SoundexTest, IgnoresNonAlphabetics)
{
	EXPECT_EQ("A000", soundex.encode("A#"));
}

//Disabling Tests
//TEST_F(SoundexTest, DISABLED_ReplacesMultipleConstantsWithDigits)
//{
//	EXPECT_EQ("A234", soundex.encode("Acdl"));
//}

TEST_F(SoundexTest, ReplacesMultipleConstantsWithDigits)
{
	EXPECT_EQ("A234", soundex.encode("Acdl"));
}