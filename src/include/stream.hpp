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
	#define BuildByte(a, b, c, d, e, f, g, h)			((static_cast<unsigned int>((a) & 0x01) << 7) | \
														(static_cast<unsigned int>((b) & 0x01) << 6) | \
														(static_cast<unsigned int>((c) & 0x01) << 5) | \
														(static_cast<unsigned int>((d) & 0x01) << 4) | \
														(static_cast<unsigned int>((e) & 0x01) << 3) | \
														(static_cast<unsigned int>((f) & 0x01) << 2) | \
														(static_cast<unsigned int>((g) & 0x01) << 1) | \
														(static_cast<unsigned int>((h) & 0x01) << 0))

	#define GetBit(a, b)								(((a) & (1 << (b))) != 0)

	#define BuildColor(r, g, b)							(((r) << 24) | \
														 ((g) << 16) | \
														 ((b) << 8)  | \
														  0x00)

	#define ColorGetRed(x)								(((x) >> 24) & 0xFF)
	#define ColorGetGreen(x)							(((x) >> 16) & 0xFF)
	#define ColorGetBlue(x)								(((x) >> 8) & 0xFF)

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
		static const time_t GmTimestampEpoch = 0xFFFFFFFF7C5324CFULL;
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
		Stream* ReadBitmap();

		// Writing
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
		void WriteBitmap(Stream* value);
 
		// Compression
		void Deflate();
		void Inflate();

		// Serialization
		Stream* Deserialize(bool decompress = true);
		void Serialize(Stream* stream, bool compress = true);
	};
}

#endif
