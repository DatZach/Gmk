/*
 *	gmk.hpp
 *	Game Maker K?
 */

#ifndef __GMK_GMK_HPP
#define __GMK_GMK_HPP

#include <iostream>
#include <vector>
#include <map>
#include <gmkresource.hpp>
#include <gmksettings.hpp>
#include <gmktrigger.hpp>
#include <gmksound.hpp>
#include <gmksprite.hpp>
#include <gmkbackground.hpp>
#include <gmkpath.hpp>
#include <gmkscript.hpp>

namespace Gmk
{
	class Gmk
	{
	public:
		static const unsigned int GMK_MAGIC			= 1234321;
		static const unsigned int GMK_GUID_LENGTH	= 16;

	private:
		void LoadVer81(Stream* stream);

		void SaveGmk(Stream* stream);
		void LoadGmk(Stream* stream);

	public:
		Version								version;
		unsigned int						gameId;
		unsigned char						guid[GMK_GUID_LENGTH];
		Settings*							settings;
		std::vector<Trigger*>				triggers;
		std::map<std::string, std::string>	constants;
		std::vector<Sound*>					sounds;
		std::vector<Sprite*>				sprites;
		std::vector<Background*>			backgrounds;
		std::vector<Path*>					paths;
		std::vector<Script*>				scripts;
		
		/*std::vector<Font*>					fonts;
		std::vector<Timeline*>				timelines;
		std::vector<Object*>				objects;
		std::vector<Room*>					rooms;
		// Resource files?
		unsigned int						lastInstancePlacedId;
		unsigned int						lastTilePlacedId;
		std::vector<IncludeFile*>			includeFiles;
		std::vector<std::string>			packages;
		GameInformation*					gameInformation;
		std::vector<std::string>			libraryCreationCode;
		std::vector<unsigned int>			roomExceutionOrder;
		*/

		Gmk();
		~Gmk();

		bool Save(const std::string& filename);
		bool Load(const std::string& filename);
		void DefragmentResources();

 		bool IsLoaded() const;
	};
}

#endif
