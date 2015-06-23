#include "StringUtils.h"
#include <sstream>
#include <assert.h>

using namespace std;

namespace bop
{
	StringDelimiter::StringDelimiter(string str, char token)
	{
		_str = str;
		_token = token;
		_begin = 0;
	}

	bool StringDelimiter::hasNext() const
	{
		return _begin < _str.size();
	}

	string StringDelimiter::getNext()
	{
		size_t end = _str.find(_token, _begin + 1);
		if (end == string::npos)
		{
			end = _str.size();
		}
		else
		{
			end;
		}
		string ret = _str.substr(_begin, end - _begin);
		_begin = end + 1;
		return ret;
	}

	string StringUtils::ConvertToUnixLineEndings(const string& crlfFile)
	{
		stringstream sstr;
		size_t begin = 0;
		while (begin < crlfFile.length())
		{
			size_t end = crlfFile.find('\r', begin);
			if (end == string::npos)
			{
				end = crlfFile.length();
				sstr << crlfFile.substr(begin, end - begin);
			}
			else
			{
				assert(crlfFile[end + 1] == '\n');
				sstr << crlfFile.substr(begin, end - begin) << '\n';
			}
			begin = end + 2;
		}
		return sstr.str();
	}
}
