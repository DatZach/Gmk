/*
 *	gmkbackground.cpp
 *	GMK Background
 */

#include <gmkbackground.hpp>

namespace Gmk
{
	Background::Background(Gmk* gmk)
		: GmkResource(gmk),
		  name(""),
		  useAsTileset(false),
		  tileWidth(16),
		  tileHeight(16),
		  tileHorizontalOffset(0),
		  tileVerticalOffset(0),
		  tileHorizontalSeperation(0),
		  tileVerticalSeperation(0),
		  width(0),
		  height(0),
		  data(NULL)
	{
		
	}

	Background::~Background()
	{
		if (data != NULL)
			delete data;
	}

	void Background::WriteVer81(Stream* stream)
	{

	}

	void Background::ReadVer81(Stream* stream)
	{
		Stream* backgroundStream = stream->Deserialize();

		if (!backgroundStream->ReadBoolean())
			return;

		name						= backgroundStream->ReadString();
		backgroundStream->ReadTimestamp();
		backgroundStream->ReadDword();
		useAsTileset				= backgroundStream->ReadBoolean();
		tileWidth					= backgroundStream->ReadDword();
		tileHeight					= backgroundStream->ReadDword();
		tileHorizontalOffset		= backgroundStream->ReadDword();
		tileVerticalOffset			= backgroundStream->ReadDword();
		tileHorizontalSeperation	= backgroundStream->ReadDword();
		tileVerticalSeperation		= backgroundStream->ReadDword();
		backgroundStream->ReadDword();
		width						= backgroundStream->ReadDword();
		height						= backgroundStream->ReadDword();

		if (width != 0 && height != 0)
			data = backgroundStream->Deserialize(false);

		delete backgroundStream;
	}
}
