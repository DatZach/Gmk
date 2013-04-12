/*
 *	stream.hpp
 *	Binary file stream helper
 */

#ifndef __GMK_STREAM_HPP
#define __GMK_STREAM_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace Gmk
{
	typedef std::vector<unsigned char> StreamBuffer;

	class Stream
	{
	private:
		std::fstream fileStream;

	public:
		Stream(const std::string& filename);
		~Stream();

		// Reading
		void ReadData(const StreamBuffer& buffer, std::size_t length);			// TODO buffer.size() instead of length?
		bool ReadBoolean();	
		unsigned char ReadByte();
		unsigned short ReadWord();
		unsigned int ReadDword();
		unsigned long long ReadQword();
		double ReadDouble();
		float ReadFloat();
		std::string ReadString();

		// Writing
		void WriteData(const StreamBuffer& buffer);
		void WriteBoolean(bool value);
		void WriteByte(unsigned char value);
		void WriteWord(unsigned short value);
		void WriteDword(unsigned int value);
		void WriteQword(unsigned long long value);
		void WriteDouble(double value);
		void WriteFloat(float value);
		void WriteString(const std::string& value);

		// Serialization
		bool Deserialize(Stream* dest, bool decompress = true);
		bool Serialize(bool compress = true);
	};
}

#endif
