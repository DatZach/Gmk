/*
 *	gmkexception.hpp
 *	GMK Exception
 */

#ifndef __GMK_EXCEPTION_HPP
#define __GMK_EXCEPTION_HPP

#include <iostream>
#include <exception>

namespace Gmk
{
	class GmkException : public std::exception
	{
	private:
		std::string message;

	public:
		GmkException(const std::string& _message);

		const char* what() const;
	};
}

#endif
