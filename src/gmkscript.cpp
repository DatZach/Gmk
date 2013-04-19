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
		Stream* scriptStream = new Stream();

		scriptStream->WriteBoolean(exists);
		if (exists)
		{
			scriptStream->WriteString(name);
			scriptStream->WriteTimestamp();
			scriptStream->WriteDword(800);
			scriptStream->WriteString(value);
		}

		stream->Serialize(scriptStream);
		delete scriptStream;
	}

	void Script::ReadVer81(Stream* stream)
	{
		Stream* scriptStream = stream->Deserialize();

		if (!scriptStream->ReadBoolean())
		{
			exists = false;
			return;
		}
	
		name = scriptStream->ReadString();
		scriptStream->ReadTimestamp();
		scriptStream->ReadDword();
		value = scriptStream->ReadString();

		delete scriptStream;
		exists = true;
	}
}
