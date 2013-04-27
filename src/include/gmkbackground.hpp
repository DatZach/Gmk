/*
 *	gmkbackground.hpp
 *	GMK Background
 */

#ifndef __GMK_BACKGROUND_HPP
#define __GMK_BACKGROUND_HPP

#include <gmkresource.hpp>

namespace Gmk
{
	class Background : public GmkResource
	{
	protected:
		void WriteVer81(Stream* stream);
		void ReadVer81(Stream* stream);

	public:
		bool					useAsTileset;
		unsigned int			tileWidth;
		unsigned int			tileHeight;
		unsigned int			tileHorizontalOffset;
		unsigned int			tileVerticalOffset;
		unsigned int			tileHorizontalSeperation;
		unsigned int			tileVerticalSeperation;
		unsigned int			width;
		unsigned int			height;
		Stream*					data;

		Background(GmkFile* gmk);
		~Background();

		int GetId() const;
	};
}

#endif
