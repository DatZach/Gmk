/*
 *	gmk.cpp
 *	GameMaker (special) K!
 */

#include <iostream>
#include <stream.hpp>
#include <gmk.hpp>

namespace Gmk
{
	Gmk::Gmk()
		: version(VerUnknown), gameId(0), settings(NULL)
	{

	}

	Gmk::~Gmk()
	{

	}

	bool Gmk::Save(const std::string& filename)
	{
		return false;
	}

	bool Gmk::Load(const std::string& filename)
	{
		try
		{
			Stream* stream = new Stream(filename, Stream::SmRead);

			LoadGmk(stream);

			delete stream;
		}
		catch(std::exception* e)
		{
			std::cerr << "Gmk::Load Error: " << e->what() << std::endl;
			return false;
		}

		return true;
	}

	void Gmk::DefragmentResources()
	{

	}

	bool Gmk::IsLoaded() const
	{
		return version != VerUnknown;
	}

	void Gmk::SaveGmk(Stream* stream)
	{

	}

	void Gmk::LoadGmk(Stream* stream)
	{
		if (stream->ReadDword() != GMK_MAGIC)
			throw new std::exception("Invalid magic!");

		switch(stream->ReadDword())
		{
			case 530:
				version = Ver53a;
				break;

			case 600:
				version = Ver61;
				break;

			case 701:
				version = Ver7;
				break;

			case 800:
				version = Ver8;
				break;

			case 810:
				version = Ver81;
				break;

			default:
				throw new std::exception("Unknown or unsupported version!");
		}

		gameId = stream->ReadDword();
		for(unsigned int i = 0; i < GMK_GUID_LENGTH; ++i)
			guid[i] = stream->ReadByte();

		switch(version)
		{
			case Ver81:
				LoadVer81(stream);
				break;
		}
	}

	void Gmk::LoadVer81(Stream* stream)
	{
		unsigned int count = 0;

		// Load settings
		settings = new Settings(this);
		settings->Read(stream);

		// Load triggers
		stream->ReadDword();
		count = stream->ReadDword();
		while(count--)
		{
			Trigger* trigger = new Trigger(this);
			trigger->Read(stream);
			triggers.push_back(trigger);
		}

		stream->ReadTimestamp();

		// Load constants
		stream->ReadDword();
		count = stream->ReadDword();
		while(count--)
		{
			std::string name = stream->ReadString();
			std::string value = stream->ReadString();

			constants.insert(std::pair<std::string, std::string>(name, value));
		}

		stream->ReadTimestamp();

		// Load sounds
		stream->ReadDword();
		count = stream->ReadDword();
		while(count--)
		{
			Sound* sound = new Sound(this);
			sound->Read(stream);
			sounds.push_back(sound);
		}
	}
}
