/*
 *	gmktimeline.cpp
 *	GMK Timeline
 */

#include <gmktimeline.hpp>

namespace Gmk
{
	Timeline::Timeline(Gmk* gmk)
		: GmkResource(gmk),
		  name(""),
		  moments()
	{

	}

	Timeline::~Timeline()
	{
		for(std::size_t i = 0; i < moments.size(); ++i)
		{
			for(std::size_t j = 0; j < moments[i].actions.size(); ++j)
				delete moments[i].actions[j];
		}
	}

	void Timeline::WriteVer81(Stream* stream)
	{

	}

	void Timeline::ReadVer81(Stream* stream)
	{
		Stream* timelineStream = stream->Deserialize();

		if (!timelineStream->ReadBoolean())
			return;

		name				= timelineStream->ReadString();
		timelineStream->ReadTimestamp();
		timelineStream->ReadDword();

		unsigned int count = timelineStream->ReadDword();
		while(count--)
		{
			Moment moment;
			moment.position = timelineStream->ReadDword();
			
			timelineStream->ReadDword();
			unsigned int actionCount = timelineStream->ReadDword();
			while(actionCount--)
			{
				Action* action = new Action(gmkHandle);
				action->Read(timelineStream);

				moment.actions.push_back(action);
			}

			moments.push_back(moment);
		}

		delete timelineStream;
	}
}
