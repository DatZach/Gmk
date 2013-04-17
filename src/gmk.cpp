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
		: version(VerUnknown),
		  gameId(0),
		  settings(NULL)
	{
		// TODO Set defaults
	}

	Gmk::~Gmk()
	{
		// TODO Clean memory
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
			version = VerUnknown;
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

		// Load sprites
		stream->ReadDword();
		count = stream->ReadDword();
		while(count--)
		{
			Sprite* sprite = new Sprite(this);
			sprite->Read(stream);
			sprites.push_back(sprite);
		}

		// Load backgrounds
		stream->ReadDword();
		count = stream->ReadDword();
		while(count--)
		{
			Background* background = new Background(this);
			background->Read(stream);
			backgrounds.push_back(background);
		}

		// Load paths
		stream->ReadDword();
		count = stream->ReadDword();
		while(count--)
		{
			Path* path = new Path(this);
			path->Read(stream);
			paths.push_back(path);
		}

		// Load scripts
		stream->ReadDword();
		count = stream->ReadDword();
		while(count--)
		{
			Script* script = new Script(this);
			script->Read(stream);
			scripts.push_back(script);
		}

		// Load fonts
		stream->ReadDword();
		count = stream->ReadDword();
		while(count--)
		{
			Font* font = new Font(this);
			font->Read(stream);
			fonts.push_back(font);
		}
	
		// Load timelines
		stream->ReadDword();
		count = stream->ReadDword();
		while(count--)
		{
			Timeline* timeline = new Timeline(this);
			timeline->Read(stream);
			timelines.push_back(timeline);
		}

		// Load objects
		stream->ReadDword();
		count = stream->ReadDword();
		while(count--)
		{
			Object* object = new Object(this);
			object->Read(stream);
			objects.push_back(object);
		}
	}
}
