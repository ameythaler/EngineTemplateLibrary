namespace ETL
{
namespace STLExtensions
{
	ETL_INTERNAL_TEMPLATE_DEF
	bool ETL_INTERNAL_PARAM_STRING::char_in_str(charT c, const charT* s, size_type len) const
	{
		size_type cur = 0;
		while (cur < len)
		{
			if (s[cur] == c)
			{
				return true;
			}
			++cur;
		}
		return false;
	}

	ETL_INTERNAL_TEMPLATE_DEF
	std::vector<ETL_INTERNAL_PARAM_STRING> ETL_INTERNAL_PARAM_STRING::split(charT delim, bool keep_delim) const
	{
		std::vector<ETL_INTERNAL_PARAM_STRING> retVal;
		size_type start = 0;
		size_type strLen = m_String.length();
		size_type cur;
		for (cur = 0; cur < strLen; ++cur)
		{
			if (m_String[cur] == delim) // We've reached a delimiter
			{
				if (cur - start > 0) // There's actually string content here
				{
					if (keep_delim)
					{
						// We need to find the next non-delim char
						while (cur < strLen && m_String[cur] == delim)
						{
							++cur;
						}
						retVal.push_back(substr(start, cur - start));
						start = cur;
					}
					else
					{
						retVal.push_back(substr(start, cur - start));
						start = cur + 1;
					}
				}
				else if (!keep_delim)
				{
					++start; // Discard all delimiter characters
				}
			}
		}
		if (cur - start > 0 && start < strLen) // Handle left over characters
		{
			retVal.push_back(substr(start, cur - start));
		}
		return retVal;
	}

	ETL_INTERNAL_TEMPLATE_DEF
	std::vector<ETL_INTERNAL_PARAM_STRING> ETL_INTERNAL_PARAM_STRING::split(const charT* delims, bool keep_delims) const
	{
		std::vector<ETL_INTERNAL_PARAM_STRING> retVal;
		size_type start = 0;
		size_type strLen = m_String.length();
		size_type delimLen = string_length(delims);
		size_type cur;
		for (cur = 0; cur < strLen; ++cur)
		{
			if (char_in_str(m_String[cur], delims, delimLen)) // We've reached a delimiter
			{
				if (cur - start > 0) // There's actually string content here
				{
					if (keep_delims)
					{
						// We need to find the next non-delim char
						while (cur < strLen && char_in_str(m_String[cur], delims, delimLen))
						{
							++cur;
						}
						retVal.push_back(substr(start, cur - start));
						start = cur;
					}
					else
					{
						retVal.push_back(substr(start, cur - start));
						start = cur + 1;
					}
				}
				else if (!keep_delims)
				{
					++start; // Discard all delimiter characters
				}
			}
		}
		if (cur - start > 0 && start < strLen) // Handle left over characters
		{
			retVal.push_back(substr(start, cur - start));
		}
		return retVal;
	}
}
}