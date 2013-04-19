/*
 *	gmkresource.cpp
 *	GMK Resource
 */

#include <gmkresource.hpp>
#include <gmk.hpp>

namespace Gmk
{
	GmkResource::GmkResource(Gmk* gmk)
		: version(gmk->version),
		  gmkHandle(gmk),
		  exists(false)
	{

	}

	void GmkResource::Write(Stream* stream)
	{
		switch(version)
		{
			case Ver81:
				WriteVer81(stream);
				break;
		}
	}

	void GmkResource::Read(Stream* stream)
	{
		switch(version)
		{
			case Ver81:
				ReadVer81(stream);
				break;
		}
	}
}
