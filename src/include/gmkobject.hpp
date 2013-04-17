/*
 *	gmkobject.hpp
 *	GMK Object
 */

#ifndef __GMK_OBJECT_HPP
#define __GMK_OBJECT_HPP

#include <gmkresource.hpp>

namespace Gmk
{
	class Object : public GmkResource
	{
	public:

	protected:
		void WriteVer81(Stream* stream);
		void ReadVer81(Stream* stream);

	public:
		Object(Gmk* gmk);
		~Object();
	};
}

#endif
