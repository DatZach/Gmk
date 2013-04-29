/*
 *	main.cpp
 *	GMK API Library Test
 */

//#define USE_THREADS
#define PROFILE

#if defined USE_THREADS || defined _DEBUG || defined PROFILE
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
	LARGE_INTEGER frequency, t1, t2;

	QueryPerformanceFrequency(&frequency);

	std::cout << "GMK API Library Test" << std::endl;

	Gmk::GmkFile* gmk = new Gmk::GmkFile();

	std::cout << "Loading... ";
	QueryPerformanceCounter(&t1);
	gmk->Load("Vivant.gm81");
	QueryPerformanceCounter(&t2);
	std::cout << "Done!" << std::endl;
	std::cout << "Elapsed " << (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart << "ms" << std::endl;

//	return 0;
	
	std::cout << "Defragmenting... ";
	QueryPerformanceCounter(&t1);
	gmk->DefragmentResources();
	QueryPerformanceCounter(&t2);
	std::cout << "Done!" << std::endl;
	std::cout << "Elapsed " << (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart << "ms" << std::endl;
	
#ifdef USE_THREADS
	DWORD threadId;
	HANDLE saveThread = CreateThread(NULL, 0, SaveThread, gmk, 0, &threadId);

	while(WaitForSingleObject(saveThread, 1) != WAIT_OBJECT_0)
		std::cout << "Saving... " << std::floor(gmk->GetProgress()) << "%      \r";

	CloseHandle(saveThread);
#else
	std::cout << "Saving... ";
	QueryPerformanceCounter(&t1);
	gmk->Save("out.gm81");
	QueryPerformanceCounter(&t2);
	std::cout << "Done!" << std::endl;
	std::cout << "Elapsed " << (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart << "ms" << std::endl;
#endif
	

	delete gmk;

#ifdef _DEBUG
	if (_CrtDumpMemoryLeaks() == 0)
		std::cout << "No leaks!" << std::endl;
	else
		std::cout << "Leaks detected!" << std::endl;
#endif

 	return 0;
}
