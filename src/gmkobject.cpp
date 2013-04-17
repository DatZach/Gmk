/*
 *	gmkobject.cpp
 *	GMK Object
 */

#include <gmkobject.hpp>

namespace Gmk
{
	Object::Object(Gmk* gmk)
		: GmkResource(gmk)
	{
		// TODO Default values
	}

	Object::~Object()
	{
		// TODO Clean memory
	}

	void Object::WriteVer81(Stream* stream)
	{

	}

	void Object::ReadVer81(Stream* stream)
	{
		Stream* objectStream = stream->Deserialize();

		if (!objectStream->ReadBoolean())
			return;



		delete objectStream;
	}
}
