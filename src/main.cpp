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
	gmk->Load("spawnpoints.gm81");

	std::cout << "IsLoaded\t\t: " << gmk->IsLoaded() << std::endl;
	std::cout << "Version \t\t: " << gmk->version << std::endl;
	std::cout << "Game ID \t\t: " << gmk->gameId << std::endl;
	std::cout << "Fullscreen \t\t: " << gmk->settings->fullscreen << std::endl;

	std::getchar();

	delete gmk;

	return 0;
}
