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
		// TODO declare defaults
	}

	void Settings::WriteVer81(Stream* stream)
	{

	}

	void Settings::ReadVer81(Stream* stream)
	{
		// Read version, it's actually important for once
		unsigned int ver = stream->ReadDword();

		Stream* settingsStream = stream->Deserialize();

		/*
		 *	These are the Studio additions to the GM8.1 GMK format.
		 *		Studio "supports" these values but doesn't build them,
		 *		studio builds using v820.
		 */

		if (ver >= 830)
			debugEnabled = settingsStream->ReadBoolean();

		config = ver < 831 ? "none" : settingsStream->ReadString();

		if (ver >= 832)
			useNewAudio = settingsStream->ReadBoolean();

		if (ver >= 833)
			studioEdition = settingsStream->ReadDword();

		if (ver >= 834)
			displayName = settingsStream->ReadString();

		if (ver >= 835)
			activeTargets = settingsStream->ReadQword();

		fullscreen				= settingsStream->ReadBoolean();
		interpolatePixels		= settingsStream->ReadBoolean();
		noBorder				= settingsStream->ReadBoolean();
		showCursor				= settingsStream->ReadBoolean();
		scale					= settingsStream->ReadDword();
		sizeable				= settingsStream->ReadBoolean();
		stayOnTop				= settingsStream->ReadBoolean();
		windowColor				= settingsStream->ReadDword();
		changeResolution		= settingsStream->ReadBoolean();
		colorDepth				= settingsStream->ReadDword();
		resolution				= settingsStream->ReadDword();
		frequency				= settingsStream->ReadDword();
		noButtons				= settingsStream->ReadBoolean();
		syncVertex				= settingsStream->ReadBoolean();
		noScreenSaver			= settingsStream->ReadBoolean();
		fullscreenKey			= settingsStream->ReadBoolean();
		helpKey					= settingsStream->ReadBoolean();
		quitKey					= settingsStream->ReadBoolean();
		saveKey					= settingsStream->ReadBoolean();
		screenshotKey			= settingsStream->ReadBoolean();
		closeSecondary			= settingsStream->ReadBoolean();
		priority				= settingsStream->ReadDword();
		freeze					= settingsStream->ReadBoolean();
		showProgress			= settingsStream->ReadDword();

		delete settingsStream;
	}
}
