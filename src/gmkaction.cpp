/*
 *	gmkaction.cpp
 *	GMK Action
 */

#include <sstream>
#include <gmkaction.hpp>
#include <gmk.hpp>

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

	void Action::SetCode(const std::string& value)
	{
		if (kind != ActionKindCode)
			return;

		argumentValue[0] = value;
	}

	std::string Action::GetCode() const
	{
		return kind == ActionKindCode ? argumentValue[0] : "";
	}

	GmkResource* Action::GetArgumentReference(unsigned int index) const
	{
		if (index >= ARGUMENT_COUNT)
			return NULL;

		unsigned int id = std::atoi(argumentValue[index].c_str());

		switch(argumentKind[index])
		{
			case ArgumentKindSprite:
				return id < gmkHandle->sprites.size() ? gmkHandle->sprites[id] : NULL;

			case ArgumentKindSound:
				return id < gmkHandle->sounds.size() ? gmkHandle->sounds[id] : NULL;

			case ArgumentKindBackground:
				return id < gmkHandle->backgrounds.size() ? gmkHandle->backgrounds[id] : NULL;

			case ArgumentKindPath:
				return id < gmkHandle->paths.size() ? gmkHandle->paths[id] : NULL;

			case ArgumentKindScript:
				return id < gmkHandle->scripts.size() ? gmkHandle->scripts[id] : NULL;

			case ArgumentKindObject:
				return id < gmkHandle->objects.size() ? gmkHandle->objects[id] : NULL;

			case ArgumentKindRoom:
				return id < gmkHandle->rooms.size() ? gmkHandle->rooms[id] : NULL;

			case ArgumentKindFont:
				return id < gmkHandle->fonts.size() ? gmkHandle->fonts[id] : NULL;

			case ArgumentKindTimeline:
				return id < gmkHandle->timelines.size() ? gmkHandle->timelines[id] : NULL;
		}

		return NULL;
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
		{
			if (argumentLink[i] != NULL)
			{
				std::stringstream ss; ss << std::dec << argumentLink[i]->GetId();
				stream->WriteString(ss.str());
			}
			else
				stream->WriteString(argumentValue[i]);

			//stream->WriteString(argumentValue[i]);
		}

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

		// Populate memory links -- TODO Move
		for(int i = 0; i < ARGUMENT_COUNT; ++i)
			argumentLink[i] = GetArgumentReference(i);
	}
}
