/*
 *	gmksettings.hpp
 *	GMK Settings
 */

#ifndef __GMK_SETTINGS_HPP
#define __GMK_SETTINGS_HPP

#include <gmkresource.hpp>

namespace Gmk
{
	class Settings : public GmkResource
	{
	protected:
		void WriteVer81(Stream* stream);
		void ReadVer81(Stream* stream);

	public:
		bool			debugEnabled;
		std::string		config;
		bool			useNewAudio;
		unsigned int	studioEdition;
		std::string		displayName;
		unsigned long long	activeTargets;
		bool			fullscreen;
		bool			interpolatePixels;
		bool			noBorder;
		bool			showCursor;
		int				scale;
		bool			sizeable;
		bool			stayOnTop;
		unsigned int	windowColor;
		bool			changeResolution;
		unsigned int	colorDepth;
		unsigned int	resolution;
		unsigned int	frequency;
		bool			noButtons;
		bool			syncVertex;
		bool			noScreenSaver;
		bool			fullscreenKey;
		bool			helpKey;
		bool			quitKey;
		bool			saveKey;
		bool			screenshotKey;
		bool			closeSecondary;
		unsigned int	priority;
		bool			freeze;
		int				showProgress;
		Stream*			frontImage;
		Stream*			backImage;
		Stream*			loadImage;
		bool			loadTransparent;
		unsigned int	loadAlpha;
		bool			scaleProgress;
		Stream*			iconImage;
		bool			displayErrors;
		bool			writeErrors;
		bool			abortErrors;
		bool			variableErrors;
		bool			webGL;
		bool			creationEventOrder;
		std::string		author;
		std::string		version;
		std::string		information;

		// TODO Add more (start with constants)

		Settings(Gmk* gmk);
	};
}

#endif
