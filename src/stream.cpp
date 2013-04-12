/*
 *	stream.cpp
 *	Binary file stream helper
 */

#include <stream.hpp>

namespace Gmk
{
	Stream::Stream(const std::string& filename)
		: fileStream()
	{
		fileStream.open(filename.c_str(), std::fstream::in | std::fstream::out | std::fstream::binary);
		if (!fileStream)
			throw new std::exception("Cannot open file for streaming!");
	}

	Stream::~Stream()
	{
		fileStream.close();
	}
}
