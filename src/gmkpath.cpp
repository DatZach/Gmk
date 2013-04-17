/*
 *	gmkpath.cpp
 *	GMK Path
 */

#include <gmkpath.hpp>

namespace Gmk
{
	Path::Path(Gmk* gmk)
		: GmkResource(gmk),
		  name(""),
		  connectionKind(KindStraight),
		  closed(true),
		  precision(4),
		  roomIndex(-1),
		  snapX(16),
		  snapY(16),
		  points()
	{
		
	}

	Path::~Path()
	{
		
	}

	void Path::WriteVer81(Stream* stream)
	{

	}

	void Path::ReadVer81(Stream* stream)
	{
		Stream* pathStream = stream->Deserialize();

		if (!pathStream->ReadBoolean())
			return;

		name				= pathStream->ReadString();
		pathStream->ReadTimestamp();
		pathStream->ReadDword();
		connectionKind		= pathStream->ReadDword();
		closed				= pathStream->ReadBoolean();
		precision			= pathStream->ReadDword();
		roomIndex			= pathStream->ReadDword();
		snapX				= pathStream->ReadDword();
		snapY				= pathStream->ReadDword();

		unsigned int count = pathStream->ReadDword();
		while(count--)
		{
			Point point;

			point.x = pathStream->ReadDouble();
			point.y = pathStream->ReadDouble();
			point.speed = pathStream->ReadDouble();

			points.push_back(point);
		}

		delete pathStream;
	}
}
