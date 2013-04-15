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
		bool			fullscreen;
		bool			interpolatePixels;
		bool			noBorder;
		bool			showCursor;
		int				scale;
		bool			sizeable;
		bool			stayOnTop;
		unsigned int	windowColor;

		// TODO Add more

		Settings(Gmk* gmk);
	};
}

#endif
