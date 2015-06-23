// StringUtils.h
// Various utility functions for strings.
// Taken from Iridescence.
// Kelvin Jin (5/29/2015)

#ifndef _STRING_UTILS_H_
#define _STRING_UTILS_H_

#include <string>

namespace bop
{
	/**
	 * A class which may be used to split strings by a given token character.
	 * For example, string "cats and dogs" with whitespace tokens gives
	 * "cats", "and", and "dogs" with each call to getNext().
	 */
	class StringDelimiter
	{
		std::string _str;
		char _token;
		unsigned _begin;
	public:
		// Constructs a new StringDelimiter object with given string str and splitting token.
		StringDelimiter(std::string str, char token);

		// Returns true if there is still another delimitable portion of the given string.
		bool hasNext() const;

		// Gets the next delimited string.
		std::string getNext();
	};

	/**
	 * Various utility functions for strings.
	 */
	class StringUtils
	{
	public:
		// Simply converts all occurrences of "\r\n" to "\n". NOP on files that already have UNIX file endings.
		static std::string ConvertToUnixLineEndings(const std::string& crlfFile);
	};
}

#endif
