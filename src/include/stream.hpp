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
#include <ctime>

namespace Gmk
{
	class Stream
	{
	public:
		typedef std::vector<unsigned char> StreamBuffer;
		typedef enum _StreamMode {
			SmRead,
			SmWrite,
			SmMemory
		} StreamMode;

	private:
		static const time_t GmTimestampEpoch = 0xFFFFFFFF7C2B517FULL;
		std::fstream fileStream;
		StreamBuffer buffer;
		StreamMode streamMode;
		std::size_t position;

		void ExpandMemoryStream(std::size_t length);

		// Compression
		unsigned char* DeflateStream(const StreamBuffer& sourceBuffer, std::size_t *deflatedLength);
		unsigned char* InflateStream(const StreamBuffer& sourceBuffer, std::size_t *infaltedLength);

	public:
		Stream(const std::string& filename, StreamMode mode);
		Stream();
		~Stream();

		// Operations
		void Rewind();
		void SetPosition(std::size_t value);
		std::size_t GetPosition();
		std::size_t GetLength();
		StreamBuffer GetMemoryBuffer() const;
		const unsigned char* GetRawMemoryBuffer() const;

		// Reading
		Stream* ReadCompressedData();
		void ReadData(const StreamBuffer& value);
		bool ReadBoolean();	
		unsigned char ReadByte();
		unsigned short ReadWord();
		unsigned int ReadDword();
		unsigned long long ReadQword();
		double ReadDouble();
		float ReadFloat();
		std::string ReadString();
		time_t ReadTimestamp();

		// Writing
		void WriteCompressedData(Stream* value);
		void WriteData(const StreamBuffer& value);
		void WriteBoolean(bool value);
		void WriteByte(unsigned char value);
		void WriteWord(unsigned short value);
		void WriteDword(unsigned int value);
		void WriteQword(unsigned long long value);
		void WriteDouble(double value);
		void WriteFloat(float value);
		void WriteString(const std::string& value);
		void WriteTimestamp();
 
		// Compression
		void Deflate();
		void Inflate();

		// Serialization
		Stream* Deserialize(bool decompress = true);
		void Serialize(Stream* stream, bool compress = true);
	};
}

#endif
