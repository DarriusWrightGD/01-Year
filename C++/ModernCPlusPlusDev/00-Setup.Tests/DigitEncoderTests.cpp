#include <gtest\gtest.h>
#include <DigitEncoder.h>
using namespace testing;

class DigitEncoderTests : public Test
{
public:
	DigitEncoder digitEncoder;
};


TEST_F(DigitEncoderTests, ReplaceTheConstantsWithDigits)
{
	EXPECT_EQ("1", digitEncoder.encodeDigits("b"));
	EXPECT_EQ("2", digitEncoder.encodeDigits("c"));
	EXPECT_EQ("3", digitEncoder.encodeDigits("d"));
	EXPECT_EQ("4", digitEncoder.encodeDigits("l"));
	EXPECT_EQ("5", digitEncoder.encodeDigits("m"));
	EXPECT_EQ("6", digitEncoder.encodeDigits("r"));
}

TEST_F(DigitEncoderTests, IgnoresNonAlphabetics)
{
	EXPECT_EQ("", digitEncoder.encodeDigits("#"));
}

//Disabling Tests
//TEST_F(DigitEncoderTests, DISABLED_ReplacesMultipleConstantsWithDigits)
//{
//	EXPECT_EQ("A234", digitEncoder.encodeDigits("Acdl"));
//}

TEST_F(DigitEncoderTests, ReplacesMultipleConstantsWithDigits)
{
	EXPECT_EQ("234", digitEncoder.encodeDigits("cdl"));
}

TEST_F(DigitEncoderTests, LimitLengthOfEncodedDigitsToThree)
{
	EXPECT_EQ(3, digitEncoder.encodeDigits("cdlb").length());
}

TEST_F(DigitEncoderTests, IgnoresVowelLikeLetters)
{
	EXPECT_EQ("234", digitEncoder.encodeDigits("aeiouhycdl"));
}

TEST_F(DigitEncoderTests, CombinesDuplicateEncodings)
{
	EXPECT_EQ("123", digitEncoder.encodeDigits("bfcgdt"));
}