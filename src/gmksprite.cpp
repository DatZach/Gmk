/*
 *	gmksprite.cpp
 *	GMK Sprite
 */

#include <gmksprite.hpp>

namespace Gmk
{
	Sprite::Sprite(Gmk* gmk)
		: GmkResource(gmk),
		  name(""),
		  width(0),
		  height(0),
		  bboxLeft(0),
		  bboxRight(0),
		  bboxBottom(0),
		  bboxTop(0),
		  originX(0),
		  originY(0),
		  subimages(),
		  maskShape(ShapePrecise),
		  seperateMasks(false),
		  boundingBox(BbAutomatic)
	{

	}

	Sprite::~Sprite()
	{
		for(std::size_t i = 0; i < subimages.size(); ++i)
		{
			if (subimages[i].data == NULL)
				continue;

			delete subimages[i].data;
		}
	}

	void Sprite::WriteVer81(Stream* stream)
	{

	}

	void Sprite::ReadVer81(Stream* stream)
	{
		Stream* spriteStream = stream->Deserialize();

		if (!spriteStream->ReadBoolean())
			return;

		name					= spriteStream->ReadString();
		spriteStream->ReadTimestamp();
		spriteStream->ReadDword();
		originX					= spriteStream->ReadDword();
		originY					= spriteStream->ReadDword();

		unsigned int count = spriteStream->ReadDword();
		while(count--)
		{
			Subimage subimage;

			spriteStream->ReadDword();
			subimage.width = spriteStream->ReadDword();
			subimage.height = spriteStream->ReadDword();

			if (subimage.width != 0 && subimage.height != 0)
				subimage.data = spriteStream->Deserialize(false);
			else
				subimage.data = NULL;

			subimages.push_back(subimage);

			width = subimage.width;
			height = subimage.height;
		}

		maskShape				= spriteStream->ReadDword();
		alphaTolerance			= spriteStream->ReadDword();
		seperateMasks			= spriteStream->ReadBoolean();
		boundingBox				= spriteStream->ReadDword();
		bboxLeft				= spriteStream->ReadDword();
		bboxRight				= spriteStream->ReadDword();
		bboxBottom				= spriteStream->ReadDword();
		bboxTop					= spriteStream->ReadDword();

		delete spriteStream;
	}
}
