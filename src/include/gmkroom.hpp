/*
 *	gmkroom.hpp
 *	GMK Room
 */

#ifndef __GMK_ROOM_HPP
#define __GMK_ROOM_HPP

#include <gmkresource.hpp>

namespace Gmk
{
	class Room : public GmkResource
	{
	public:
		typedef struct _Background
		{
			bool				visible;
			bool				foreground;
			int					imageIndex;
			unsigned int		x;
			unsigned int		y;
			bool				tileHorizontal;
			bool				tileVertical;
			int					speedHorizontal;
			int					speedVertical;
			bool				stretch;
		} Background;

		typedef struct _View
		{
			bool				visible;
			unsigned int		viewX;
			unsigned int		viewY;
			unsigned int		viewW;
			unsigned int		viewH;
			unsigned int		portX;
			unsigned int		portY;
			unsigned int		portW;
			unsigned int		portH;
			unsigned int		horizontalBorder;
			unsigned int		verticalBorder;
			int					horizontalSpeed;
			int					verticalSpeed;
			int					objectFollowing;
	 	} View;

		typedef struct _Instance
		{
			unsigned int		x;
			unsigned int		y;
			unsigned int		objectIndex;
			unsigned int		id;
			std::string			creationCode;
			bool				locked;
	 	} Instance;

		typedef struct _Tile
		{
			unsigned int		x;
			unsigned int		y;
			int					backgroundIndex;
			unsigned int		tileX;
			unsigned int		tileY;
			unsigned int		width;
			unsigned int		height;
			unsigned int		layer;
			unsigned int		id;
			bool				locked;
	 	} Tile;

	protected:
		void WriteVer81(Stream* stream);
		void ReadVer81(Stream* stream);

	public:
		std::string				name;
		std::string				caption;
		unsigned int			width;
		unsigned int			height;
		unsigned int			snapY;
		unsigned int			snapX;
		bool					isometricGrid;
		unsigned int			speed;
		bool					persistent;
		unsigned int			backgroundColor;
		bool					drawBackgroundColor;
		bool					clearBackgroundWithWindowColor;
		std::string				creationCode;
		std::vector<Background>	backgrounds;
		bool					viewsEnabled;
		std::vector<View>		views;
		std::vector<Instance>	instances;
		std::vector<Tile>		tiles;
		bool					rememberRoomEditorInfo;
		unsigned int			roomEditorWidth;
		unsigned int			roomEditorHeight;
		bool					showGrid;
		bool					showObjects;
		bool					showTiles;
		bool					showBackgrounds;
		bool					showForegrounds;
		bool					showViews;
		bool					deleteUnderlyingObjects;
		bool					deleteUnderlyingTiles;
		unsigned int			tabIndex;
		unsigned int			scrollbarX;
		unsigned int			scrollbarY;
		
		Room(Gmk* gmk);
		~Room();
	};
}

#endif
