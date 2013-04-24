/*
 *	gmktree.hpp
 *	GMK Resource Tree
 */

#ifndef __GMK_TREE_HPP
#define __GMK_TREE_HPP

#include <gmkresource.hpp>

namespace Gmk
{
	class Tree : public GmkResource
	{
	public:
		enum Status
		{
			StatusPrimary = 1,
			StatusGroup,
			StatusSecondary
		};

		enum Group
		{
			GroupObjects = 1,
			GroupSprites,
			GroupSounds,
			GroupRooms,
			GroupBackgrounds = 6,
			GroupScripts,
			GroupPaths,
			GroupDataFiles,
			GroupFonts = GroupDataFiles,
			GroupGameInformation,
			GroupGameOptions,
			GroupGlobalGameOptions = GroupGameOptions,
			GroupTimelines,
			GroupExtensionPackages
		};

		// TODO Class this
		typedef struct _Node
		{
			GmkResource*			link;
			unsigned int			status;
			unsigned int			group;
			unsigned int			index;
			std::string				name;
			std::vector<_Node*>		contents;
		} Node;
	
	private:
		void CleanMemory();
		GmkResource* GetResource(unsigned int id, unsigned int kind) const;

		void ReadRecursiveTree(Stream* stream, Node* parent, unsigned int count);
		void WriteRecursiveTree(Stream* stream, Node* parent, unsigned int count);

	protected:
		void WriteVer81(Stream* stream);
		void ReadVer81(Stream* stream);

	public:
		std::vector<Node*>			contents;

		Tree(Gmk* gmk);
		~Tree();

		void Finalize();
	};
}

#endif
