/*
 *	gmkobject.cpp
 *	GMK Object
 */

#include <gmkobject.hpp>

namespace Gmk
{
	Object::Object(Gmk* gmk)
		: GmkResource(gmk),
		  name(""),
		  spriteIndex(SpriteIndexNone),
		  solid(false),
		  visible(true),
		  depth(0),
		  persistent(false),
		  parent(ParentObjectNone),
		  mask(MaskIndexNone),
		  events()
	{
		
	}

	Object::~Object()
	{
		for(std::size_t i = 0; i < events.size(); ++i)
		{
			for(std::size_t j = 0; j < events[i].actions.size(); ++j)
				delete events[i].actions[j];
		}
	}

	void Object::WriteVer81(Stream* stream)
	{
		Stream* objectStream = new Stream();

		objectStream->WriteBoolean(exists);
		if (exists)
		{
			objectStream->WriteString(name);
			objectStream->WriteTimestamp();
			objectStream->WriteDword(430);
			objectStream->WriteDword(spriteIndex);
			objectStream->WriteBoolean(solid);
			objectStream->WriteBoolean(visible);
			objectStream->WriteDword(depth);
			objectStream->WriteBoolean(persistent);
			objectStream->WriteDword(parent);
			objectStream->WriteDword(mask);

			objectStream->WriteDword(11);
			for(std::size_t i = 0; i < 12; ++i)
			{
				for(std::size_t j = 0; j < events.size(); ++j)
				{
					if (events[j].eventNumber == i)
					{
						objectStream->WriteDword(events[j].eventKind);
						objectStream->WriteDword(400);

						objectStream->WriteDword(events[j].actions.size());
						for(std::size_t k = 0; k < events[j].actions.size(); ++k)
							events[j].actions[k]->Write(objectStream);
					}
				}

				objectStream->WriteDword(-1);
			}
		}

		stream->Serialize(objectStream);
		delete objectStream;
	}

	void Object::ReadVer81(Stream* stream)
	{
		Stream* objectStream = stream->Deserialize();

		if (!objectStream->ReadBoolean())
		{
			exists = false;
			return;
		}

		name				= objectStream->ReadString();
		objectStream->ReadTimestamp();
		objectStream->ReadDword();
		spriteIndex			= objectStream->ReadDword();
		solid				= objectStream->ReadBoolean();
		visible				= objectStream->ReadBoolean();
		depth				= objectStream->ReadDword();
		persistent			= objectStream->ReadBoolean();
		parent				= objectStream->ReadDword();
		mask				= objectStream->ReadDword();

		unsigned int count = objectStream->ReadDword() + 1;
		for(unsigned int i = 0; i < count; ++i)
		{
			for(;;)
			{
				Event event;

				int first = objectStream->ReadDword();
				if (first == -1)
					break;

				event.eventNumber = i;
				event.eventKind = first;

				objectStream->ReadDword();

				unsigned int actionCount = objectStream->ReadDword();
				while(actionCount--)
				{
					Action* action = new Action(gmkHandle);
					action->Read(objectStream);

					event.actions.push_back(action);
				}

				events.push_back(event);
			}
		}

		delete objectStream;
		exists = true;
	}
}
