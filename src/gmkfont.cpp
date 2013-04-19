/*
 *	gmkfont.cpp
 *	GMK Font
 */

#include <gmkfont.hpp>

namespace Gmk
{
	Font::Font(Gmk* gmk)
		: GmkResource(gmk),
		  name(""),
		  fontName(""),
		  size(12),
		  bold(false),
		  italic(false),
		  characterRangeBegin(32),
		  characterRangeEnd(127),
		  characterSet(DEFAULT_CHARSET),
		  antiAliasing(Aa3)
	{

	}

	Font::~Font()
	{

	}

	void Font::WriteVer81(Stream* stream)
	{

	}

	void Font::ReadVer81(Stream* stream)
	{
		Stream* fontStream = stream->Deserialize();

		if (!fontStream->ReadBoolean())
		{
			exists = false;
			return;
		}

		name				= fontStream->ReadString();
		fontStream->ReadTimestamp();
		fontStream->ReadDword();
		fontName			= fontStream->ReadString();
		size				= fontStream->ReadDword();
		bold				= fontStream->ReadBoolean();
		italic				= fontStream->ReadBoolean();

		unsigned int value	= fontStream->ReadDword();
		characterSet		= (value >> 16) & 0xFF;
		antiAliasing		= (value >> 24) & 0xFF;
		characterRangeBegin	= value & 0xFFFF;

		characterRangeEnd	= fontStream->ReadDword();

		delete fontStream;
		exists = true;
	}
}
