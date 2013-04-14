/*
 *	main.cpp
 *	GMK API Library Test
 */

#include <iostream>
#include <ctime>
#include <stream.hpp>

int main(int argc, char* argv[])
{
	std::cout << "GMK API Library Test" << std::endl;

	try
	{
		// Write a bunch of compressed data
		Gmk::Stream* compressedStream = new Gmk::Stream();
		compressedStream->WriteByte(0x14);
		compressedStream->WriteWord(0x1337);
		compressedStream->WriteDword(1234321);
		compressedStream->WriteBoolean(true);
		compressedStream->WriteFloat(1.37f);
		compressedStream->WriteDouble(13.37);
		compressedStream->WriteString("Hello, World!");
		compressedStream->WriteTimestamp();

		// Write compressed stream to file
		Gmk::Stream* outFileStream = new Gmk::Stream("out.dat", Gmk::Stream::SmWrite);
		outFileStream->WriteDword(1234321);
		outFileStream->Serialize(compressedStream);
		delete outFileStream;
		delete compressedStream;

		Gmk::Stream* inFileStream = new Gmk::Stream("out.dat", Gmk::Stream::SmRead);
		std::cout << std::dec << "Magic number: " << inFileStream->ReadDword() << std::endl;

		Gmk::Stream* decompressedStream = inFileStream->Deserialize();
		std::cout << std::hex << (unsigned int)decompressedStream->ReadByte() << std::endl;
		std::cout << std::hex << decompressedStream->ReadWord() << std::endl;
		std::cout << std::dec << decompressedStream->ReadDword() << std::endl;
		std::cout << std::dec << decompressedStream->ReadBoolean() << std::endl;
		std::cout << std::dec << decompressedStream->ReadFloat() << std::endl;
		std::cout << std::dec << decompressedStream->ReadDouble() << std::endl;
		std::cout << decompressedStream->ReadString() << std::endl;
		time_t timestampAsshole = decompressedStream->ReadTimestamp();
		std::cout << ctime(&timestampAsshole) << std::endl;

		delete decompressedStream;
		delete inFileStream;
	}
	catch(std::exception* e)
	{
		std::cout << e->what() << std::endl;
	}

	std::getchar();

	return 0;
}
