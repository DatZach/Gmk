/*
 *	gmkscript.cpp
 *	GMK Script
 */

#include <gmkscript.hpp>

namespace Gmk
{
	Script::Script(Gmk* gmk)
		: GmkResource(gmk),
		  name(""),
		  value("")
	{
		
	}

	Script::~Script()
	{

	}

	void Script::WriteVer81(Stream* stream)
	{

	}

	void Script::ReadVer81(Stream* stream)
	{
		Stream* scriptStream = stream->Deserialize();

		if (!scriptStream->ReadBoolean())
			return;
	
		name = scriptStream->ReadString();
		scriptStream->ReadTimestamp();
		scriptStream->ReadDword();
		value = scriptStream->ReadString();

		delete scriptStream;
	}
}
