/*
 *	gmkaction.cpp
 *	GMK Action
 */

#include <gmkaction.hpp>

namespace Gmk
{
	Action::Action(Gmk* gmk)
		: GmkResource(gmk),
		  functionName(""),
		  functionCode(""),
		  libraryId(0),
		  actionId(0),
		  kind(0),
		  type(0),
		  argumentsUsed(0),
		  appliesToObject(false),
		  relative(false),
		  appliesToSomething(false),
		  question(false),
		  mayBeRelative(false),
		  not(false)
	{
		
	}

	Action::~Action()
	{

	}

	void Action::WriteVer81(Stream* stream)
	{
		stream->WriteDword(440);

		stream->WriteDword(libraryId);
		stream->WriteDword(actionId);
		stream->WriteDword(kind);
		stream->WriteBoolean(mayBeRelative);
		stream->WriteBoolean(question);
		stream->WriteBoolean(appliesToSomething);
		stream->WriteDword(type);
		stream->WriteString(functionName);
		stream->WriteString(functionCode);
		stream->WriteDword(argumentsUsed);

		stream->WriteDword(ARGUMENT_COUNT);
		for(unsigned int i = 0; i < ARGUMENT_COUNT; ++i)
			stream->WriteDword(argumentKind[i]);

		stream->WriteDword(appliesToObject);
		stream->WriteBoolean(relative);

		stream->WriteDword(ARGUMENT_COUNT);
		for(unsigned int i = 0; i < ARGUMENT_COUNT; ++i)
			stream->WriteString(argumentValue[i]);

		stream->WriteBoolean(not);
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
