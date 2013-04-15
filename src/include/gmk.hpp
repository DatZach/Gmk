/*
 *	gmk.hpp
 *	Game Maker K?
 */

#ifndef __GMK_GMK_HPP
#define __GMK_GMK_HPP

#include <iostream>
#include <vector>
#include <gmkresource.hpp>
#include <gmksettings.hpp>

namespace Gmk
{
	class Gmk
	{
	private:
		static const unsigned int GMK_MAGIC			= 1234321;
		static const unsigned int GMK_GUID_LENGTH	= 16;

	private:
		void SaveGmk(Stream* stream);
		void LoadGmk(Stream* stream);

	public:
		Version				version;
		unsigned int		gameId;
		unsigned char		guid[GMK_GUID_LENGTH];
		Settings*			settings;

		Gmk();
		~Gmk();

		bool Save(const std::string& filename);
		bool Load(const std::string& filename);
		void DefragmentResources();

 		bool IsLoaded() const;
	};
}

#endif
