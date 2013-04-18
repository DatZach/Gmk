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

	}

	Tree::~Tree()
	{
		for(std::size_t i = 0; i < contents.size(); ++i)
			delete contents[i];
	}

	void Tree::WriteVer81(Stream* stream)
	{

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
}
