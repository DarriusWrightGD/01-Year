#include <gtest\gtest.h>
/*
– Write production code only to make a failing test pass.
– Write no more of a unit test than sufficient to fail. Compilation failures are failures. 
– Write only the production code needed to pass the one failing test.
*/

class Soundex {

};

TEST(SoundexEncoding, RetainsSoleLetterOfOneLetterWord)
{
	Soundex soundex;
}	