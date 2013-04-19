/*
 *	gmkgameinfo.cpp
 *	GMK Game Information
 */

#include <gmkgameinfo.hpp>

namespace Gmk
{
	GameInformation::GameInformation(Gmk* gmk)
		: GmkResource(gmk),
		  backgroundColor(0x180000FF),
		  showInSeperateWindow(true),
		  caption("Game Information"),
		  left(-1),
		  top(-1),
		  width(600),
		  height(400),
		  showBorder(true),
		  sizeable(true),
		  alwaysOnTop(false),
		  freeze(true),
		  information("{\\rtf1\\ansi\\ansicpg1252\\deff0\\deflang1033{\\fonttbl{\\f0\\fnil\\fcharset0 Calibri;}}{\\*\\generator Msftedit 5.41.21.2509;}\\viewkind4\\uc1\\pard\\sa200\\sl276\\slmult1\\lang9\\f0\\fs22\\par}\0")
	{
		exists = true;
	}

	GameInformation::~GameInformation()
	{

	}

	void GameInformation::WriteVer81(Stream* stream)
	{

	}

	void GameInformation::ReadVer81(Stream* stream)
	{
		Stream* gameInfoStream = stream->Deserialize();

		backgroundColor				= gameInfoStream->ReadDword();
		showInSeperateWindow		= gameInfoStream->ReadBoolean();
		caption						= gameInfoStream->ReadString();
		left						= gameInfoStream->ReadDword();
		top							= gameInfoStream->ReadDword();
		width						= gameInfoStream->ReadDword();
		height						= gameInfoStream->ReadDword();
		showBorder					= gameInfoStream->ReadBoolean();
		sizeable					= gameInfoStream->ReadBoolean();
		alwaysOnTop					= gameInfoStream->ReadBoolean();
		freeze						= gameInfoStream->ReadBoolean();
		gameInfoStream->ReadTimestamp();
		information					= gameInfoStream->ReadString();

		delete gameInfoStream;
	}
}
