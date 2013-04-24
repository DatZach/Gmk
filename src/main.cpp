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

	std::cout << "Loading... ";
	gmk->Load("Vivant.gm81");
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

	delete gmk;

	return 0;
}
