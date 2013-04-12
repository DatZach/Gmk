/*
 *	main.cpp
 *	GMK API Library Test
 */

#include <iostream>
#include <stream.hpp>

int main(int argc, char* argv[])
{
	std::cout << "GMK API Library Test" << std::endl;

	try
	{
		Gmk::Stream* stream = new Gmk::Stream("wat.bin");

		delete stream;
	}
	catch(std::exception* e)
	{
		std::cout << e->what() << std::endl;
	}

	std::getchar();

	return 0;
}
