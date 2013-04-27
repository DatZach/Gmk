/*
 *	main.cpp
 *	GMK API Library Test
 */

#include <iostream>
#include <gmk.hpp>

int main(int argc, char* argv[])
{
	std::cout << "GMK API Library Test" << std::endl;

	Gmk::GmkFile* gmk = new Gmk::GmkFile();

	std::cout << "Loading... ";
	gmk->Load("test.gm81");
	std::cout << "Done!" << std::endl;

	std::cout << "Defragmenting... ";
	gmk->DefragmentResources();
	std::cout << "Done!" << std::endl;

	std::cout << "Saving... ";
	gmk->Save("out.gm81");
	std::cout << "Done!" << std::endl;

	delete gmk;

	return 0;
}
