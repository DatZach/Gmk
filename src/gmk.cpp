/*
 *	gmk.cpp
 *	GameMaker (special) K!
 */

#include <iostream>
#include <ctime>
#include <stream.hpp>
#include <gmk.hpp>

namespace Gmk
{
	Gmk::Gmk()
		: version(VerUnknown),
		  gameId(0),
		  guid(),
		  settings(NULL),
		  triggers(),
		  constants(),
		  sounds(),
		  sprites(),
		  backgrounds(),
		  paths(),
		  scripts(),
		  fonts(),
		  timelines(),
		  objects(),
		  rooms(),
		  lastInstancePlacedId(100000),
		  lastTilePlacedId(1000000),
		  includeFiles(),
		  gameInformation(NULL),
		  libraryCreationCode(),
		  roomExecutionOrder(),
		  resourceTree(NULL)
	{
		settings = new Settings(this);
		gameInformation = new GameInformation(this);
		resourceTree = new Tree(this);

		std::srand(static_cast<unsigned int>(time(NULL)));
		gameId = std::rand() % GMK_MAX_ID;
	}

	Gmk::~Gmk()
	{
		CleanMemory();
	}

	bool Gmk::Save(const std::string& filename)
	{
		try
		{
			Stream* stream = new Stream(filename, Stream::SmWrite);

			SaveGmk(stream);

			delete stream;
		}
		catch(std::exception* e)
		{
			std::cerr << "Gmk::Save Error: " << e->what() << std::endl;
			version = VerUnknown;
			return false;
		}

		return true;
	}

	bool Gmk::Load(const std::string& filename)
	{
		CleanMemory();

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
		// Defragment backgrounds
		std::vector<Background*>::iterator itr = backgrounds.begin();
		while(itr != backgrounds.end())
		{
			if (!(*itr)->GetExists())
			{
				delete *itr;
				itr = backgrounds.erase(itr);
				continue;
			}

			++itr;
		}
	}

	bool Gmk::IsLoaded() const
	{
		return version != VerUnknown;
	}

	void Gmk::SaveGmk(Stream* stream)
	{
		const unsigned int Versions[6] = { 0, 530, 600, 701, 800, 810 };
		
		// Write header
		stream->WriteDword(GMK_MAGIC);
		stream->WriteDword(Versions[static_cast<int>(version)]);
		stream->WriteDword(gameId);
		for(unsigned int i = 0; i < GMK_GUID_LENGTH; ++i)
		{
			unsigned char guidByte = gameId >> i / 4;
			guidByte %= ((i >> 6) + guidByte & 0x7F) + 0xFF;
			guidByte ^= (i * guidByte >> 3) & 0xAB;

			stream->WriteByte(guidByte);
		}
		
		switch(version)
		{
			case Ver81:
				SaveVer81(stream);
				break;

			default:
				throw new std::exception("Unsupported version");
		}
	}

	void Gmk::LoadGmk(Stream* stream)
	{
		// Read header
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

	void Gmk::SaveVer81(Stream* stream)
	{
		// Write settings
		stream->WriteDword(800);
		if (settings == NULL)
			throw new std::exception("Settings are not declared");

		settings->Write(stream);

		// Write triggers
		stream->WriteDword(800);
		stream->WriteDword(triggers.size());
		for(std::size_t i = 0; i < triggers.size(); ++i)
			triggers[i]->Write(stream);

		stream->WriteTimestamp();

		// Write constants
		stream->WriteDword(800);
		stream->WriteDword(constants.size());
		for(std::size_t i = 0; i < constants.size(); ++i)
		{
			stream->WriteString(constants[i].first);
			stream->WriteString(constants[i].second);
		}

		stream->WriteTimestamp();

		// Write sounds
		stream->WriteDword(800);
		stream->WriteDword(sounds.size());
		for(std::size_t i = 0; i < sounds.size(); ++i)
			sounds[i]->Write(stream);

		// Write sprites
		stream->WriteDword(800);
		stream->WriteDword(sprites.size());
		for(std::size_t i = 0; i < sprites.size(); ++i)
			sprites[i]->Write(stream);

		// Write backgrounds
		stream->WriteDword(800);
		stream->WriteDword(backgrounds.size());
		for(std::size_t i = 0; i < backgrounds.size(); ++i)
			backgrounds[i]->Write(stream);

		// Write paths
		stream->WriteDword(800);
		stream->WriteDword(paths.size());
		for(std::size_t i = 0; i < paths.size(); ++i)
			paths[i]->Write(stream);

		// Write scripts
		stream->WriteDword(800);
		stream->WriteDword(scripts.size());
		for(std::size_t i = 0; i < scripts.size(); ++i)
			scripts[i]->Write(stream);

		// Write fonts
		stream->WriteDword(800);
		stream->WriteDword(fonts.size());
		for(std::size_t i = 0; i < fonts.size(); ++i)
			fonts[i]->Write(stream);

		// Write timelines
		stream->WriteDword(800);
		stream->WriteDword(timelines.size());
		for(std::size_t i = 0; i < timelines.size(); ++i)
			timelines[i]->Write(stream);

		// Write objects
		stream->WriteDword(800);
		stream->WriteDword(objects.size());
		for(std::size_t i = 0; i < objects.size(); ++i)
			objects[i]->Write(stream);

		// Write rooms
		stream->WriteDword(800);
		stream->WriteDword(rooms.size());
		for(std::size_t i = 0; i < rooms.size(); ++i)
			rooms[i]->Write(stream);

		// Write last ids
		stream->WriteDword(lastInstancePlacedId);
		stream->WriteDword(lastTilePlacedId);

		// Write include files
		stream->WriteDword(800);
		stream->WriteDword(includeFiles.size());
		for(std::size_t i = 0; i < includeFiles.size(); ++i)
			includeFiles[i]->Write(stream);
		
		// Write packages
		stream->WriteDword(700);
		stream->WriteDword(packages.size());
		for(std::size_t i = 0; i < packages.size(); ++i)
			stream->WriteString(packages[i]);

		// Write game information
		stream->WriteDword(800);
		gameInformation->Write(stream);

		// Write library creation code
		stream->WriteDword(500);
		stream->WriteDword(libraryCreationCode.size());
		for(std::size_t i = 0; i < libraryCreationCode.size(); ++i)
			stream->WriteString(libraryCreationCode[i]);

		// Write room execution order -- TODO This should be regenerated every save
		stream->WriteDword(700);
		stream->WriteDword(roomExecutionOrder.size());
		for(std::size_t i = 0; i < roomExecutionOrder.size(); ++i)
			stream->WriteDword(roomExecutionOrder[i]);

		// Write resource tree
		resourceTree->Write(stream);
	}

	void Gmk::LoadVer81(Stream* stream)
	{
		unsigned int count = 0;

		// Load settings
		stream->ReadDword();
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

			constants.push_back(std::pair<std::string, std::string>(name, value));
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

		// Load rooms
		stream->ReadDword();
		count = stream->ReadDword();
		while(count--)
		{
			Room* room = new Room(this);
			room->Read(stream);
			rooms.push_back(room);
		}

		// Load last ids
		lastInstancePlacedId = stream->ReadDword();
		lastTilePlacedId = stream->ReadDword();

		// Load include files
		stream->ReadDword();
		count = stream->ReadDword();
		while(count--)
		{
			IncludeFile* includeFile = new IncludeFile(this);
			includeFile->Read(stream);
			includeFiles.push_back(includeFile);
		}

		// Load packages
		stream->ReadDword();
		count = stream->ReadDword();
		while(count--)
			packages.push_back(stream->ReadString());

		// Read game information
		stream->ReadDword();
		gameInformation = new GameInformation(this);
		gameInformation->Read(stream);

		// Read library creation code
		stream->ReadDword();
		count = stream->ReadDword();
		while(count--)
			libraryCreationCode.push_back(stream->ReadString());

		// Read room execution order
		stream->ReadDword();
		count = stream->ReadDword();
		while(count--)
			roomExecutionOrder.push_back(stream->ReadDword());

		// Read resource tree
		resourceTree = new Tree(this);
		resourceTree->Read(stream);
	}

	void Gmk::CleanMemory()
	{
		if (settings != NULL)
		{
			delete settings;
			settings = NULL;
		}

		for(std::size_t i = 0; i < triggers.size(); ++i)
			delete triggers[i];

		for(std::size_t i = 0; i < sounds.size(); ++i)
			delete sounds[i];

		for(std::size_t i = 0; i < sprites.size(); ++i)
			delete sprites[i];

		for(std::size_t i = 0; i < backgrounds.size(); ++i)
			delete backgrounds[i];

		for(std::size_t i = 0; i < paths.size(); ++i)
			delete paths[i];

		for(std::size_t i = 0; i < scripts.size(); ++i)
			delete scripts[i];

		for(std::size_t i = 0; i < fonts.size(); ++i)
			delete fonts[i];

		for(std::size_t i = 0; i < timelines.size(); ++i)
			delete timelines[i];

		for(std::size_t i = 0; i < objects.size(); ++i)
			delete objects[i];

		for(std::size_t i = 0; i < rooms.size(); ++i)
			delete rooms[i];

		for(std::size_t i = 0; i < includeFiles.size(); ++i)
			delete includeFiles[i];

		if (gameInformation != NULL)
		{
			delete gameInformation;
			gameInformation = NULL;
		}

		if (resourceTree != NULL)
		{
			delete resourceTree;
			resourceTree = NULL;
		}
	}
}
