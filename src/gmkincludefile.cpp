/*
 *	gmkincludefile.cpp
 *	GMK Include File
 */

#include <gmkincludefile.hpp>

namespace Gmk
{
	IncludeFile::IncludeFile(Gmk* gmk)
		: GmkResource(gmk),
		  filename(""),
		  filepath(""),
		  originalFile(false),
		  originalFileSize(0),
		  data(NULL),
		  exportKind(EkDont),
		  exportPath(""),
		  overwrite(false),
		  freeMemory(true),
		  removeAtEndOfGame(true)
	{

	}

	IncludeFile::~IncludeFile()
	{
		if (data != NULL)
			delete data;
	}

	void IncludeFile::WriteVer81(Stream* stream)
	{

	}

	void IncludeFile::ReadVer81(Stream* stream)
	{
		Stream* includeFileStream = stream->Deserialize();

		includeFileStream->ReadTimestamp();
		includeFileStream->ReadDword();
		filename				= includeFileStream->ReadString();
		filepath				= includeFileStream->ReadString();
		originalFile			= includeFileStream->ReadBoolean();
		originalFileSize		= includeFileStream->ReadDword();
		
		if (includeFileStream->ReadBoolean())
			data = includeFileStream->Deserialize(false);

		exportKind				= includeFileStream->ReadDword();
		exportPath				= includeFileStream->ReadString();
		overwrite				= includeFileStream->ReadBoolean();
		freeMemory				= includeFileStream->ReadBoolean();
		removeAtEndOfGame		= includeFileStream->ReadBoolean();

		delete includeFileStream;
	}
}
