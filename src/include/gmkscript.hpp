/*
 *	gmkscript.hpp
 *	GMK Script
 */

#ifndef __GMK_SCRIPT_HPP
#define __GMK_SCRIPT_HPP

#include <gmkresource.hpp>

namespace Gmk
{
	class Script : public GmkResource
	{
	protected:
		void WriteVer81(Stream* stream);
		void ReadVer81(Stream* stream);

	public:
		std::string			name;
		std::string			value;

		Script(Gmk* gmk);
		~Script();

		int GetId() const;
	};
}

#endif
