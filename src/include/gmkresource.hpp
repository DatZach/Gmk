/*
 *	gmkresource.hpp
 *	GMK Resource
 */

#ifndef __GMK_RESOURCE_HPP
#define __GMK_RESOURCE_HPP

#include <iostream>
#include <stream.hpp>

namespace Gmk
{
	class Gmk;

	// TODO Move this
	typedef enum _Version
	{
		VerUnknown,
		Ver53a,
		Ver61,
		Ver7,
		Ver8,
		Ver81
	} Version;

	class GmkResource
	{
	private:
		Version version;

	protected:
		virtual void WriteVer81(Stream* stream) = 0;
		virtual void ReadVer81(Stream* stream) = 0;

	public:
		GmkResource(Gmk* gmk);

		void Write(Stream* stream);
		void Read(Stream* stream);
	};
}

#endif
