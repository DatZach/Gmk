/*
 *	gmktree.cpp
 *	GMK Resource Tree
 */

#include <gmktree.hpp>
#include <gmk.hpp>

namespace Gmk
{
	Tree::Tree(Gmk* gmk)
		: GmkResource(gmk),
		  contents()
	{
		static const std::string names[12] =
		{
			"Sprites",
			"Sounds",
			"Backgrounds",
			"Paths",
			"Scripts",
			"Fonts",
			"Time Lines",
			"Objects",
			"Rooms",
			"Game Information",
			"Global Game Settings",
			"Extension Packages"
		};

		static const unsigned int order[12] =
		{
			GroupSprites,
			GroupSounds,
			GroupBackgrounds,
			GroupPaths,
			GroupScripts,
			GroupFonts,
			GroupTimelines,
			GroupObjects,
			GroupRooms,
			GroupGameInformation,
			GroupGlobalGameOptions,
			GroupExtensionPackages
		};

		exists = true;

		for(unsigned int i = 0; i < 12; ++i)
		{
			Node* node = new Node();

			node->status = i >= 9 ? StatusSecondary : StatusPrimary;
			node->group = order[i];
			node->index = 0;
			node->name = names[i];

			contents.push_back(node);
		}
	}

	Tree::~Tree()
	{
		CleanMemory();
	}

	void Tree::CleanMemory()
	{
		// TODO You orphan nodes on the heap by doing this -- fix leaked memory
		for(std::size_t i = 0; i < contents.size(); ++i)
			delete contents[i];

		contents.clear();
	}

	GmkResource* Tree::GetResource(unsigned int id, unsigned int kind) const
	{
		switch(kind)
		{
			case GroupSprites:
				return id < gmkHandle->sprites.size() ? gmkHandle->sprites[id] : NULL;

			case GroupSounds:
				return id < gmkHandle->sounds.size() ? gmkHandle->sounds[id] : NULL;

			case GroupBackgrounds:
				return id < gmkHandle->backgrounds.size() ? gmkHandle->backgrounds[id] : NULL;

			case GroupPaths:
				return id < gmkHandle->paths.size() ? gmkHandle->paths[id] : NULL;

			case GroupScripts:
				return id < gmkHandle->scripts.size() ? gmkHandle->scripts[id] : NULL;

			case GroupObjects:
				return id < gmkHandle->objects.size() ? gmkHandle->objects[id] : NULL;

			case GroupRooms:
				return id < gmkHandle->rooms.size() ? gmkHandle->rooms[id] : NULL;

			case GroupFonts:
				return id < gmkHandle->fonts.size() ? gmkHandle->fonts[id] : NULL;

			case GroupTimelines:
				return id < gmkHandle->timelines.size() ? gmkHandle->timelines[id] : NULL;
		}

		return NULL;
	}

	void Tree::WriteVer81(Stream* stream)
	{
		for(unsigned int i = 0; i < 12; ++i)
		{
			stream->WriteDword(contents[i]->status);
			stream->WriteDword(contents[i]->group);
			stream->WriteDword(contents[i]->index);
			stream->WriteString(contents[i]->name);

			stream->WriteDword(contents[i]->contents.size());
			WriteRecursiveTree(stream, contents[i], contents[i]->contents.size());
		}
	}

	void Tree::ReadVer81(Stream* stream)
	{
		CleanMemory();

		for(unsigned int i = 0; i < 12; ++i)
		{
			Node* node = new Node();

			node->status = stream->ReadDword();
			node->group = stream->ReadDword();
			node->index = stream->ReadDword();
			node->name = stream->ReadString();

			ReadRecursiveTree(stream, node, stream->ReadDword());

			contents.push_back(node);
		}
	}

	void Tree::ReadRecursiveTree(Stream* stream, Node* parent, unsigned int count)
	{
		while(count--)
		{
			Node* node = new Node();

			node->status = stream->ReadDword();
			node->group = stream->ReadDword();
			node->index = stream->ReadDword();
			node->name = stream->ReadString();

			// TODO This should be moved into finalize for consistency
			node->link = GetResource(node->index, node->group);

			/*if (node->group == GroupBackgrounds)
				node->link = gmkHandle->backgrounds[node->index];
			else
				node->link = NULL;*/

			ReadRecursiveTree(stream, node, stream->ReadDword());

			parent->contents.push_back(node);
		}
	}

	void Tree::WriteRecursiveTree(Stream* stream, Node* parent, unsigned int count)
	{
		for(unsigned int i = 0; i < count; ++i)
		{
			stream->WriteDword(parent->contents[i]->status);
			stream->WriteDword(parent->contents[i]->group);
			//stream->WriteDword(parent->contents[i]->index);
			if (parent->contents[i]->link == NULL)
				stream->WriteDword(parent->contents[i]->index);
			else
				stream->WriteDword(parent->contents[i]->link->GetId());
			stream->WriteString(parent->contents[i]->name);

			stream->WriteDword(parent->contents[i]->contents.size());
			WriteRecursiveTree(stream, parent->contents[i], parent->contents[i]->contents.size());
		}
	}

	void Tree::Finalize()
	{
		
	}
}
