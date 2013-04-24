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
		Stream* timelineStream = new Stream();

		timelineStream->WriteBoolean(exists);
		if (exists)
		{
			timelineStream->WriteString(name);
			timelineStream->WriteTimestamp();
			timelineStream->WriteDword(500);

			timelineStream->WriteDword(moments.size());
			for(std::size_t i = 0; i < moments.size(); ++i)
			{
				timelineStream->WriteDword(moments[i].position);

				timelineStream->WriteDword(400);
				timelineStream->WriteDword(moments[i].actions.size());
				for(std::size_t j = 0; j < moments[i].actions.size(); ++j)
					moments[i].actions[j]->Write(timelineStream);
			}
		}

		stream->Serialize(timelineStream);
		delete timelineStream;
	}

	void Timeline::ReadVer81(Stream* stream)
	{
		Stream* timelineStream = stream->Deserialize();

		if (!timelineStream->ReadBoolean())
		{
			exists = false;
			return;
		}

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
		exists = true;
	}

	void Timeline::Finalize()
	{
		for(std::size_t i = 0; i < moments.size(); ++i)
		{
			for(std::size_t j = 0; j < moments[i].actions.size(); ++j)
				moments[i].actions[j]->Finalize();
		}
	}
}
