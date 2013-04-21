/*
 *	gmktree.cpp
 *	GMK Resource Tree
 */

#include <gmktree.hpp>

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
		for(std::size_t i = 0; i < contents.size(); ++i)
			delete contents[i];
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
			stream->WriteDword(parent->contents[i]->index);
			stream->WriteString(parent->contents[i]->name);

			stream->WriteDword(parent->contents[i]->contents.size());
			WriteRecursiveTree(stream, parent->contents[i], parent->contents[i]->contents.size());
		}
	}
}
