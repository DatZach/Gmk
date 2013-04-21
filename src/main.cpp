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
	gmk->version = Gmk::Ver81;
	gmk->Save("blank.gm81");
	
	std::cout << "Loading... ";
	gmk->Load("out.gm81");
	std::cout << "Done!" << std::endl;

	std::cout << "Saving... ";
	gmk->Save("out.gm81");
	std::cout << "Done!" << std::endl;

	std::cout << "IsLoaded\t\t: " << gmk->IsLoaded() << std::endl;
	std::cout << "Version \t\t: " << gmk->version << std::endl;
	std::cout << "Game ID \t\t: " << gmk->gameId << std::endl;

	delete gmk;

	return 0;
}
