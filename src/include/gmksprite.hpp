/*
 *	gmksprite.hpp
 *	GMK Sprite
 */

#ifndef __GMK_SPRITE_HPP
#define __GMK_SPRITE_HPP

#include <gmkresource.hpp>

namespace Gmk
{
	class Sprite : public GmkResource
	{
	public:
		enum Shape
		{
			ShapePrecise,
			ShapeRectangle,
			ShapeDisc,
			ShapeDiamond
		};

		enum BoundingBox
 		{
			BbAutomatic,
			BbFull,
			BbManual
		};

		typedef struct _Subimage
		{
			unsigned int width, height;
			Stream* data;
		} Subimage;

	protected:
		void WriteVer81(Stream* stream);
		void ReadVer81(Stream* stream);

	public:
		std::string				name;
		unsigned int			width;
		unsigned int			height;
		int						bboxLeft;
		int						bboxRight;
		int						bboxBottom;
		int						bboxTop;
		unsigned int			originX;
		unsigned int			originY;
		std::vector<Subimage>	subimages;
		unsigned int			maskShape;
		unsigned int			alphaTolerance;
		bool					seperateMasks;
		unsigned int			boundingBox;

		Sprite(Gmk* gmk);
		~Sprite();
	};
}

#endif
