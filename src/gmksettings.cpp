/*
 *	gmksettings.cpp
 *	GMK Settings
 */

#include <gmksettings.hpp>

namespace Gmk
{
	Settings::Settings(Gmk* gmk)
		: GmkResource(gmk),
		  fullscreen(false),
		  interpolatePixels(false),
		  noBorder(false),
		  showCursor(true),
		  scale(ScalingKeepAspectRatio),
		  sizeable(false),
		  stayOnTop(false),
		  windowColor(0x00000000),
		  changeResolution(false),
		  colorDepth(Cd16Bit),
		  resolution(ResolutionNoChange),
		  frequency(FrequencyNoChange),
		  noButtons(false),
		  vsync(false),
		  noScreenSaver(true),
		  fullscreenKey(true),
		  helpKey(true),
		  quitKey(true),
		  screenshotKey(true),
		  closeSecondary(true),
		  priority(PriorityNormal),
		  freeze(false),
		  showProgress(LpbtDefault),
		  frontImage(NULL),
		  backImage(NULL),
		  loadTransparent(false),
		  loadAlpha(0xFF),
		  scaleProgress(true),
		  iconImage(NULL),									// TODO Default icon
		  displayErrors(true),
		  writeErrors(false),
		  abortErrors(false),
		  treatUninitializedVariablesAsZero(false),
		  argumentError(true),
		  author(""),
		  versionString("100"),
		  information(""),
		  major(1),
		  minor(0),
		  release(0),
		  build(0),
		  company(""),
		  product(""),
		  copyright(""),
		  description("")
	{

	}

	Settings::~Settings()
	{
		if (frontImage != NULL)
			delete frontImage;

		if (backImage != NULL)
			delete backImage;

		if (loadImage != NULL)
			delete loadImage;

		if (iconImage != NULL)
			delete iconImage;
	}

	void Settings::WriteVer81(Stream* stream)
	{
		Stream* settingsStream = new Stream();

		settingsStream->WriteBoolean(fullscreen);
		settingsStream->WriteBoolean(interpolatePixels);
		settingsStream->WriteBoolean(noBorder);
		settingsStream->WriteBoolean(showCursor);
		settingsStream->WriteDword(scale);
		settingsStream->WriteBoolean(sizeable);
		settingsStream->WriteBoolean(stayOnTop);
		settingsStream->WriteDword(windowColor);
		settingsStream->WriteBoolean(changeResolution);
		settingsStream->WriteDword(colorDepth);
		settingsStream->WriteDword(resolution);
		settingsStream->WriteDword(frequency);
		settingsStream->WriteBoolean(noButtons);
		settingsStream->WriteBoolean(vsync);
		settingsStream->WriteBoolean(noScreenSaver);
		settingsStream->WriteBoolean(fullscreenKey);
		settingsStream->WriteBoolean(helpKey);
		settingsStream->WriteBoolean(quitKey);
		settingsStream->WriteBoolean(saveKey);
		settingsStream->WriteBoolean(screenshotKey);
		settingsStream->WriteBoolean(closeSecondary);
		settingsStream->WriteDword(priority);
		settingsStream->WriteBoolean(freeze);
		settingsStream->WriteDword(showProgress);

		if (showProgress == LpbtCustom)
		{
			settingsStream->WriteBitmap(backImage);
			settingsStream->WriteBitmap(frontImage);
		}

		if (loadImage != NULL)
		{
			settingsStream->WriteBoolean(true);
			settingsStream->WriteBitmap(loadImage);
		}
		else
			settingsStream->WriteBoolean(false);

		settingsStream->WriteBoolean(loadTransparent);
		settingsStream->WriteDword(loadAlpha);
		settingsStream->WriteBoolean(scaleProgress);

		settingsStream->Serialize(iconImage, false);
		
		settingsStream->WriteBoolean(displayErrors);
		settingsStream->WriteBoolean(writeErrors);
		settingsStream->WriteBoolean(abortErrors);
		settingsStream->WriteDword(BuildByte(0, 0, 0, 0, 0, 0, argumentError, treatUninitializedVariablesAsZero));

		settingsStream->WriteString(author);
		settingsStream->WriteString(versionString);
		settingsStream->WriteTimestamp();
		settingsStream->WriteString(information);
		settingsStream->WriteDword(major);
		settingsStream->WriteDword(minor);
		settingsStream->WriteDword(release);
		settingsStream->WriteDword(build);
		settingsStream->WriteString(company);
		settingsStream->WriteString(product);
		settingsStream->WriteString(copyright);
		settingsStream->WriteString(description);
		settingsStream->WriteTimestamp();

		stream->Serialize(settingsStream);
		delete settingsStream;
	}

	void Settings::ReadVer81(Stream* stream)
	{
		Stream* settingsStream = stream->Deserialize();

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
		vsync					= settingsStream->ReadBoolean();
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

		if (showProgress == LpbtCustom)
		{
			backImage = settingsStream->ReadBitmap();
			frontImage = settingsStream->ReadBitmap();
		}

		if (settingsStream->ReadBoolean())
			loadImage = settingsStream->ReadBitmap();

		loadTransparent			= settingsStream->ReadBoolean();
		loadAlpha				= settingsStream->ReadDword();
		scaleProgress			= settingsStream->ReadBoolean();

		iconImage				= settingsStream->Deserialize(false);

		displayErrors			= settingsStream->ReadBoolean();
		writeErrors				= settingsStream->ReadBoolean();
		abortErrors				= settingsStream->ReadBoolean();
		
		unsigned int errorFlags = settingsStream->ReadDword();

		treatUninitializedVariablesAsZero = (errorFlags & 0x01) == 0x01;
		argumentError = (errorFlags & 0x02) == 0x02;

		author					= settingsStream->ReadString();
		versionString			= settingsStream->ReadString();
		settingsStream->ReadTimestamp();
		information				= settingsStream->ReadString();
		major					= settingsStream->ReadDword();
		minor					= settingsStream->ReadDword();
		release					= settingsStream->ReadDword();
		build					= settingsStream->ReadDword();
		company					= settingsStream->ReadString();
		product					= settingsStream->ReadString();
		copyright				= settingsStream->ReadString();
		description				= settingsStream->ReadString();
		settingsStream->ReadTimestamp();

		delete settingsStream;
	}
}
