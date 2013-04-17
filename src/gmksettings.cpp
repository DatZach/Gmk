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

	Settings::~Settings()
	{
		// TODO Clean allocated resources
	}

	void Settings::WriteVer81(Stream* stream)
	{

	}

	void Settings::ReadVer81(Stream* stream)
	{
		// Read version, it's actually important for once
		unsigned int ver = stream->ReadDword();

		Stream* settingsStream = stream->Deserialize();
		Stream* tmpStream = new Stream("settings.bin", Stream::SmWrite);
		tmpStream->WriteData(settingsStream->GetMemoryBuffer());
		delete tmpStream;

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

		// TODO Fix this piece of shit, doesn't work as fucking usual
		/*if (ver > 800)
		{
			if (showProgress)
			{
				backImage = settingsStream->ReadBitmap();
				frontImage = settingsStream->ReadBitmap();
			}

			if (settingsStream->ReadBoolean())
				loadImage = settingsStream->ReadBitmap();
		}
		else
		{
			if (showProgress == 2)
			{
				backImage = settingsStream->ReadBitmap();
				frontImage = settingsStream->ReadBitmap();
			}

			loadImage = settingsStream->ReadBitmap();
		}

		loadTransparent			= settingsStream->ReadBoolean();
		loadAlpha				= settingsStream->ReadDword();
		scaleProgress			= settingsStream->ReadBoolean();
		displayErrors			= settingsStream->ReadBoolean();
		writeErrors				= settingsStream->ReadBoolean();
		abortErrors				= settingsStream->ReadBoolean();
		variableErrors			= settingsStream->ReadBoolean();
		
		if (ver >= 820)
		{
			webGL				= settingsStream->ReadBoolean();
			creationEventOrder	= settingsStream->ReadBoolean();
		}

		if (ver > 800)
		{
			unsigned int consantsCount = settingsStream->ReadDword();
			// TODO read constants
		}*/

		delete settingsStream;
	}
}
