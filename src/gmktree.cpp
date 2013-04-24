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
			Node::GroupSprites,
			Node::GroupSounds,
			Node::GroupBackgrounds,
			Node::GroupPaths,
			Node::GroupScripts,
			Node::GroupFonts,
			Node::GroupTimelines,
			Node::GroupObjects,
			Node::GroupRooms,
			Node::GroupGameInformation,
			Node::GroupGlobalGameOptions,
			Node::GroupExtensionPackages
		};

		exists = true;

		for(unsigned int i = 0; i < 12; ++i)
			contents.push_back(new Node(i >= 9 ? Node::StatusSecondary : Node::StatusPrimary, order[i], 0, names[i]));
	}

	Tree::~Tree()
	{
		CleanMemory();
	}

	void Tree::CleanMemory()
	{
		for(std::size_t i = 0; i < contents.size(); ++i)
			delete contents[i];

		contents.clear();
	}

	void Tree::WriteVer81(Stream* stream)
	{
		for(unsigned int i = 0; i < 12; ++i)
		{
			stream->WriteDword(contents[i]->status);
			stream->WriteDword(contents[i]->group);
			stream->WriteDword(0);
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
			unsigned int status = stream->ReadDword();
			unsigned int group = stream->ReadDword();
			stream->ReadDword();
			std::string name = stream->ReadString();

			Node* node = new Node(status, group, -1, name);

			ReadRecursiveTree(stream, node, stream->ReadDword());

			contents.push_back(node);
		}
	}

	void Tree::ReadRecursiveTree(Stream* stream, Node* parent, unsigned int count)
	{
		while(count--)
		{
			unsigned int status = stream->ReadDword();
			unsigned int group = stream->ReadDword();
			unsigned int index = stream->ReadDword();
			std::string name = stream->ReadString();

			Node* node = new Node(status, group, index, name);

			ReadRecursiveTree(stream, node, stream->ReadDword());

			parent->contents.push_back(node);
		}
	}

	void Tree::WriteRecursiveTree(Stream* stream, Node* parent, unsigned int count)
	{
		for(unsigned int i = 0; i < count; ++i)
		{
			if (parent->contents[i]->resource == NULL)
				throw new std::exception(("NULL resource \"" + parent->contents[i]->name + "\" in resource tree").c_str());

			stream->WriteDword(parent->contents[i]->status);
			stream->WriteDword(parent->contents[i]->group);
			stream->WriteDword(parent->contents[i]->resource->GetId());
			stream->WriteString(parent->contents[i]->name);

			stream->WriteDword(parent->contents[i]->contents.size());
			WriteRecursiveTree(stream, parent->contents[i], parent->contents[i]->contents.size());
		}
	}

	void Tree::Finalize()
	{
		for(std::size_t i = 0; i < contents.size(); ++i)
			contents[i]->Finalize(this);
	}

	Tree::Node::Node(unsigned int _status, unsigned int _group, unsigned int _index, const std::string& _name)
		: index(_index),
		  name(_name),
		  status(_status),
		  group(_group),
		  resource(NULL),
		  contents()
	{

	}

	Tree::Node::~Node()
	{
		for(std::size_t i = 0; i < contents.size(); ++i)
			delete contents[i];
	}

	void Tree::Node::Finalize(GmkResource* parent)
	{
		// Magic
		static const unsigned int groupKind[GroupCount] =
		{
			RtUnknown,
			RtObject,
			RtSprite,
			RtSound,
			RtRoom,
			RtUnknown,
			RtBackground,
			RtScript,
			RtPath,
			RtFont,
			RtUnknown,
			RtUnknown,
			RtTimeline,
			RtUnknown
		};

		resource = parent->GetResource(groupKind[group], index);

		for(std::size_t i = 0; i < contents.size(); ++i)
			contents[i]->Finalize(parent);
	}
}
