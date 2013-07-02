/*
 *	gmkexception.cpp
 *	GMK Exception
 */

#include <gmkexception.hpp>

namespace Gmk
{
	GmkException::GmkException(const std::string& _message)
		: message(_message)
	{

	}

	const char* GmkException::what() const
	{
		return message.c_str();
	}
}
