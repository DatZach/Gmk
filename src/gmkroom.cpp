/*
 *	gmkroom.cpp
 *	GMK Room
 */

#include <gmkroom.hpp>

namespace Gmk
{
	Room::Room(Gmk* gmk)
		: GmkResource(gmk),
		  name(""),
		  caption(""),
		  width(640),
		  height(480),
		  snapY(16),
		  snapX(16),
		  isometricGrid(false),
		  speed(30),
		  persistent(false),
		  backgroundColor(0xC0C0C000),
		  drawBackgroundColor(true),
		  creationCode(""),
		  backgrounds(),
		  viewsEnabled(false),
		  views(),
		  instances(),
		  tiles(),
		  rememberRoomEditorInfo(true),
		  roomEditorWidth(646),
		  roomEditorHeight(488),
		  showGrid(true),
		  showObjects(true),
		  showTiles(true),
		  showBackgrounds(true),
		  showForegrounds(true),
		  showViews(false),
		  deleteUnderlyingObjects(true),
		  deleteUnderlyingTiles(true),
		  tabIndex(0),
		  scrollbarX(0),
		  scrollbarY(0)
	{

	}

	Room::~Room()
	{

	}

	void Room::WriteVer81(Stream* stream)
	{

	}

	void Room::ReadVer81(Stream* stream)
	{
		unsigned int count;
		Stream* roomStream = stream->Deserialize();

		if (!roomStream->ReadBoolean())
			return;

		name					= roomStream->ReadString();
		roomStream->ReadTimestamp();
		roomStream->ReadDword();
		caption					= roomStream->ReadString();
		width					= roomStream->ReadDword();
		height					= roomStream->ReadDword();
		snapY					= roomStream->ReadDword();
		snapX					= roomStream->ReadDword();
		isometricGrid			= roomStream->ReadBoolean();
		speed					= roomStream->ReadDword();
		persistent				= roomStream->ReadBoolean();
		backgroundColor			= roomStream->ReadDword();
		drawBackgroundColor		= roomStream->ReadBoolean();
		creationCode			= roomStream->ReadString();

		count = roomStream->ReadDword();
		while(count--)
		{
			Background background;

			background.visible			= roomStream->ReadBoolean();
			background.foreground		= roomStream->ReadBoolean();
			background.imageIndex		= roomStream->ReadDword();
			background.x				= roomStream->ReadDword();
			background.y				= roomStream->ReadDword();
			background.tileHorizontal	= roomStream->ReadBoolean();
			background.tileVertical		= roomStream->ReadBoolean();
			background.speedHorizontal	= roomStream->ReadDword();
			background.speedVertical	= roomStream->ReadDword();
			background.stretch			= roomStream->ReadBoolean();

			backgrounds.push_back(background);
		}

		viewsEnabled			= roomStream->ReadBoolean();

		count = roomStream->ReadDword();
		while(count--)
		{
			View view;

			view.visible				= roomStream->ReadBoolean();
			view.viewX					= roomStream->ReadDword();
			view.viewY					= roomStream->ReadDword();
			view.viewW					= roomStream->ReadDword();
			view.viewH					= roomStream->ReadDword();
			view.portX					= roomStream->ReadDword();
			view.portY					= roomStream->ReadDword();
			view.portW					= roomStream->ReadDword();
			view.portH					= roomStream->ReadDword();
			view.horizontalBorder		= roomStream->ReadDword();
			view.verticalBorder			= roomStream->ReadDword();
			view.horizontalSpeed		= roomStream->ReadDword();
			view.verticalSpeed			= roomStream->ReadDword();
			view.objectFollowing		= roomStream->ReadDword();

			views.push_back(view);
		}

		count = roomStream->ReadDword();
		while(count--)
		{
			Instance instance;

			instance.x					= roomStream->ReadDword();
			instance.y					= roomStream->ReadDword();
			instance.objectIndex		= roomStream->ReadDword();
			instance.id					= roomStream->ReadDword();
			instance.creationCode		= roomStream->ReadString();
			instance.locked				= roomStream->ReadBoolean();

			instances.push_back(instance);
		}

		count = roomStream->ReadDword();
		while(count--)
		{
			Tile tile;

			tile.x						= roomStream->ReadDword();
			tile.y						= roomStream->ReadDword();
			tile.backgroundIndex		= roomStream->ReadDword();
			tile.tileX					= roomStream->ReadDword();
			tile.tileY					= roomStream->ReadDword();
			tile.width					= roomStream->ReadDword();
			tile.height					= roomStream->ReadDword();
			tile.layer					= roomStream->ReadDword();
			tile.id						= roomStream->ReadDword();
			tile.locked					= roomStream->ReadBoolean();

			tiles.push_back(tile);
		}

		rememberRoomEditorInfo			= roomStream->ReadBoolean();
		roomEditorWidth					= roomStream->ReadDword();
		roomEditorHeight				= roomStream->ReadDword();
		showGrid						= roomStream->ReadBoolean();
		showObjects						= roomStream->ReadBoolean();
		showTiles						= roomStream->ReadBoolean();
		showBackgrounds					= roomStream->ReadBoolean();
		showForegrounds					= roomStream->ReadBoolean();
		showViews						= roomStream->ReadBoolean();
		deleteUnderlyingObjects			= roomStream->ReadBoolean();
		deleteUnderlyingTiles			= roomStream->ReadBoolean();
		tabIndex						= roomStream->ReadDword();
		scrollbarX						= roomStream->ReadDword();
		scrollbarY						= roomStream->ReadDword();

		delete roomStream;
	}
}
