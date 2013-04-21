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
		  clearBackgroundWithWindowColor(true),
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
		Stream* roomStream = new Stream();

		roomStream->WriteBoolean(exists);
		if (exists)
		{
			roomStream->WriteString(name);
			roomStream->WriteTimestamp();
			roomStream->WriteDword(541);
			roomStream->WriteString(caption);
			roomStream->WriteDword(width);
			roomStream->WriteDword(height);
			roomStream->WriteDword(snapY);
			roomStream->WriteDword(snapX);
			roomStream->WriteBoolean(isometricGrid);
			roomStream->WriteDword(speed);
			roomStream->WriteBoolean(persistent);
			roomStream->WriteDword(backgroundColor);
			roomStream->WriteDword(BuildByte(0, 0, 0, 0, 0, 0, !clearBackgroundWithWindowColor, drawBackgroundColor));
			roomStream->WriteString(creationCode);

			roomStream->WriteDword(backgrounds.size());
			for(std::size_t i = 0; i < backgrounds.size(); ++i)
			{
				roomStream->WriteBoolean(backgrounds[i].visible);
				roomStream->WriteBoolean(backgrounds[i].foreground);
				roomStream->WriteDword(backgrounds[i].imageIndex);
				roomStream->WriteDword(backgrounds[i].x);
				roomStream->WriteDword(backgrounds[i].y);
				roomStream->WriteBoolean(backgrounds[i].tileHorizontal);
				roomStream->WriteBoolean(backgrounds[i].tileVertical);
				roomStream->WriteDword(backgrounds[i].speedHorizontal);
				roomStream->WriteDword(backgrounds[i].speedVertical);
				roomStream->WriteBoolean(backgrounds[i].stretch);
			}

			roomStream->WriteBoolean(viewsEnabled);
			roomStream->WriteDword(views.size());
			for(std::size_t i = 0; i < views.size(); ++i)
			{
				roomStream->WriteBoolean(views[i].visible);
				roomStream->WriteDword(views[i].viewX);
				roomStream->WriteDword(views[i].viewY);
				roomStream->WriteDword(views[i].viewW);
				roomStream->WriteDword(views[i].viewH);
				roomStream->WriteDword(views[i].portX);
				roomStream->WriteDword(views[i].portY);
				roomStream->WriteDword(views[i].portW);
				roomStream->WriteDword(views[i].portH);
				roomStream->WriteDword(views[i].horizontalBorder);
				roomStream->WriteDword(views[i].verticalBorder);
				roomStream->WriteDword(views[i].horizontalSpeed);
				roomStream->WriteDword(views[i].verticalSpeed);
				roomStream->WriteDword(views[i].objectFollowing);
			}

			roomStream->WriteDword(instances.size());
			for(std::size_t i = 0; i < instances.size(); ++i)
			{
				roomStream->WriteDword(instances[i].x);
				roomStream->WriteDword(instances[i].y);
				roomStream->WriteDword(instances[i].objectIndex);
				roomStream->WriteDword(instances[i].id);
				roomStream->WriteString(instances[i].creationCode);
				roomStream->WriteBoolean(instances[i].locked);
			}

			roomStream->WriteDword(tiles.size());
			for(std::size_t i = 0; i < tiles.size(); ++i)
			{
				roomStream->WriteDword(tiles[i].x);
				roomStream->WriteDword(tiles[i].y);
				roomStream->WriteDword(tiles[i].backgroundIndex);
				roomStream->WriteDword(tiles[i].tileX);
				roomStream->WriteDword(tiles[i].tileY);
				roomStream->WriteDword(tiles[i].width);
				roomStream->WriteDword(tiles[i].height);
				roomStream->WriteDword(tiles[i].layer);
				roomStream->WriteDword(tiles[i].id);
				roomStream->WriteBoolean(tiles[i].locked);
			}

			roomStream->WriteBoolean(rememberRoomEditorInfo);
			roomStream->WriteDword(roomEditorWidth);
			roomStream->WriteDword(roomEditorHeight);
			roomStream->WriteBoolean(showGrid);
			roomStream->WriteBoolean(showObjects);
			roomStream->WriteBoolean(showTiles);
			roomStream->WriteBoolean(showBackgrounds);
			roomStream->WriteBoolean(showForegrounds);
			roomStream->WriteBoolean(showViews);
			roomStream->WriteBoolean(deleteUnderlyingObjects);
			roomStream->WriteBoolean(deleteUnderlyingTiles);
			roomStream->WriteDword(tabIndex);
			roomStream->WriteDword(scrollbarX);
			roomStream->WriteDword(scrollbarY);
		}

		stream->Serialize(roomStream);
		delete roomStream;
	}

	void Room::ReadVer81(Stream* stream)
	{
		unsigned int count;
		Stream* roomStream = stream->Deserialize();

		if (!roomStream->ReadBoolean())
		{
			exists = false;
			return;
		}

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

		unsigned int bgFlags = roomStream->ReadDword();
		drawBackgroundColor		= GetBit(bgFlags, 0);
		clearBackgroundWithWindowColor = !GetBit(bgFlags, 1);

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
		exists = true;
	}
}
