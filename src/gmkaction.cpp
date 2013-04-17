/*
 *	gmkaction.cpp
 *	GMK Action
 */

#include <gmkaction.hpp>

namespace Gmk
{
	Action::Action(Gmk* gmk)
		: GmkResource(gmk)
	{
		// TODO Default values
	}

	Action::~Action()
	{

	}

	void Action::WriteVer81(Stream* stream)
	{

	}

	void Action::ReadVer81(Stream* stream)
	{
		unsigned int count;

		// Skip version
		stream->ReadDword();

		libraryId				= stream->ReadDword();
		actionId				= stream->ReadDword();
		kind					= stream->ReadDword();
		mayBeRelative			= stream->ReadBoolean();
		question				= stream->ReadBoolean();
		appliesToSomething		= stream->ReadBoolean();
		type					= stream->ReadDword();
		functionName			= stream->ReadString();
		functionCode			= stream->ReadString();
		argumentsUsed			= stream->ReadDword();

		count = stream->ReadDword();
		for(unsigned int i = 0; i < count; ++i)
			argumentKind[i] = stream->ReadDword();

		appliesToObject			= stream->ReadDword();
		relative				= stream->ReadBoolean();

		count = stream->ReadDword();
		for(unsigned int i = 0; i < count; ++i)
			argumentValue[i] = stream->ReadString();

		not						= stream->ReadBoolean();
	}
}
