/*
 *	gmksound.cpp
 *	GMK Sound
 */

#include <gmksound.hpp>

namespace Gmk
{
	Sound::Sound(Gmk* gmk)
		: GmkResource(gmk),
		  name(""),
		  kind(KindNormal),
		  extension(""),
		  filename(""),
		  data(NULL),
		  effects(EffectNone),
		  volume(1.0),
		  pan(0.0),
		  preload(true)
	{

	}

	Sound::~Sound()
	{
		if (data != NULL)
			delete data;
	}

	void Sound::WriteVer81(Stream* stream)
	{

	}

	void Sound::ReadVer81(Stream* stream)
	{
		Stream* soundStream = stream->Deserialize();

		if (!soundStream->ReadBoolean())
			return;

		name			= soundStream->ReadString();
		soundStream->ReadTimestamp();
		soundStream->ReadDword();
		kind			= soundStream->ReadDword();
		extension		= soundStream->ReadString();
		filename		= soundStream->ReadString();
		if (soundStream->ReadBoolean())
			data			= soundStream->Deserialize(false);
		effects			= soundStream->ReadDword();
		volume			= soundStream->ReadDouble();
		pan				= soundStream->ReadDouble();
		preload			= soundStream->ReadBoolean();

		delete soundStream;
	}
}
