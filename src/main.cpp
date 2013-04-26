/*
 *	main.cpp
 *	GMK API Library Test
 */

#include <iostream>
#include <gmk.hpp>

int main(int argc, char* argv[])
{
	std::cout << "GMK API Library Test" << std::endl;

	Gmk::Gmk* gmk = new Gmk::Gmk();
#ifndef FUCKIT
	gmk->version = Gmk::Ver81;

	// Create a room
	Gmk::Room* room = new Gmk::Room(gmk);
	room->name = "rmTest";
	room->caption = "Testing stuff!";
	gmk->rooms.push_back(room);

	// Add to the resource tree
	Gmk::Tree::Node* rooms = gmk->resourceTree->GetBranch(Gmk::Tree::Node::GroupRooms);
	rooms->AddResource(room);

	Gmk::Tree::Node* roomsTest = rooms->AddFilter("test");
	Gmk::Room* room2 = new Gmk::Room(gmk);
	room2->name = "room2";
	gmk->rooms.push_back(room2);

	roomsTest->AddResource(room2);

	gmk->Save("manip.gm81");
#else
	
	std::cout << "Loading... ";
	gmk->Load("fuckingworkforonce.gm81");
	std::cout << "Done!" << std::endl;

	std::cout << "Pre defragmentation Background IDs:" << std::endl;
	for(int i = 0; i < gmk->backgrounds.size(); ++i)
		std::cout << gmk->backgrounds[i]->name << "; " << gmk->backgrounds[i]->GetId() << std::endl;

	std::cout << "Defragmenting... ";
	gmk->DefragmentResources();
	std::cout << "Done!" << std::endl;

	std::cout << "Post defragmentation Background IDs:" << std::endl;
	for(int i = 0; i < gmk->backgrounds.size(); ++i)
		std::cout << gmk->backgrounds[i]->name << "; " << gmk->backgrounds[i]->GetId() << std::endl;

	std::cout << "Saving... ";
	gmk->Save("out.gm81");
	std::cout << "Done!" << std::endl;
#endif

	delete gmk;

	return 0;
}
