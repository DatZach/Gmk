/*
 *	gmksettings.cpp
 *	GMK Settings
 */

#include <gmksettings.hpp>

namespace Gmk
{
	Settings::Settings(Gmk* gmk)
		: GmkResource(gmk)
	{

	}

	void Settings::WriteVer81(Stream* stream)
	{

	}

	void Settings::ReadVer81(Stream* stream)
	{
		// Skip version
		stream->ReadDword();

		Stream* settingsStream = stream->Deserialize();

		fullscreen				= settingsStream->ReadBoolean();
		interpolatePixels		= settingsStream->ReadBoolean();
		noBorder				= settingsStream->ReadBoolean();
		showCursor				= settingsStream->ReadBoolean();
		scale					= settingsStream->ReadDword();
		sizeable				= settingsStream->ReadBoolean();
		windowColor				= settingsStream->ReadDword();
		settingsStream->ReadDword();
		settingsStream->ReadDword();

		delete settingsStream;
	}
}
