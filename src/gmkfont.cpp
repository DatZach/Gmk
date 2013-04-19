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
		Stream* fontStream = new Stream();

		fontStream->WriteBoolean(exists);
		if (exists)
		{
			fontStream->WriteString(name);
			fontStream->WriteTimestamp();
			fontStream->WriteDword(800);
			fontStream->WriteString(fontName);
			fontStream->WriteDword(size);
			fontStream->WriteBoolean(bold);
			fontStream->WriteBoolean(italic);
			
			unsigned int value = 0;
			value |= (characterSet & 0xFF) << 16;
			value |= (antiAliasing & 0xFF) << 24;
			value |= characterRangeBegin & 0xFFFF;
			
			fontStream->WriteDword(value);
			fontStream->WriteDword(characterRangeEnd);
		}

		stream->Serialize(fontStream);
		delete fontStream;
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
