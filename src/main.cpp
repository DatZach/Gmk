/*
 *	main.cpp
 *	GMK API Library Test
 */

//#define USE_THREADS

#if defined USE_THREADS || defined _DEBUG
#include <Windows.h>
#endif

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <iostream>
#include <gmk.hpp>

#ifdef USE_THREADS
DWORD WINAPI SaveThread(LPVOID lpParam)
{
	Gmk::GmkFile* gmk = reinterpret_cast<Gmk::GmkFile*>(lpParam);
	gmk->Save("out.gm81");

	return 0;
}
#endif

int main(int argc, char* argv[])
{
	std::cout << "GMK API Library Test" << std::endl;

	Gmk::GmkFile* gmk = new Gmk::GmkFile();

	std::cout << "Loading... ";
	gmk->Load("gm7.gmk");
	std::cout << "Done!" << std::endl;

	return 0;
	
	std::cout << "Defragmenting... ";
	gmk->DefragmentResources();
	std::cout << "Done!" << std::endl;
	
#ifdef USE_THREADS
	DWORD threadId;
	HANDLE saveThread = CreateThread(NULL, 0, SaveThread, gmk, 0, &threadId);

	while(WaitForSingleObject(saveThread, 1) != WAIT_OBJECT_0)
		std::cout << "Saving... " << std::floor(gmk->GetProgress()) << "%      \r";

	CloseHandle(saveThread);
#else
	std::cout << "Saving... ";
	gmk->Save("out.gm81");
	std::cout << "Done!" << std::endl;
#endif
	

	delete gmk;

#ifdef _DEBUG
	if (_CrtDumpMemoryLeaks() == 0)
		std::cout << "No leaks!" << std::endl;
#endif

 	return 0;
}
