/*
 *	stream.cpp
 *	Binary file stream helper
 */

#include <stream.hpp>
#include <zlib.h>

namespace Gmk
{
	Stream::Stream(const std::string& filename, StreamMode mode)
		: fileStream(), buffer(), streamMode(mode), position(0)
	{
		if (streamMode == SmMemory)
			return;

		std::fstream::openmode openMode = std::fstream::binary;
		if (streamMode == SmRead)
			openMode |= std::fstream::in;
		else
			openMode |= std::fstream::out;

		fileStream.open(filename.c_str(), openMode);
		if (!fileStream)
			throw new std::exception("Cannot open file for streaming!");
	}

	Stream::Stream()
		: fileStream(), buffer(), streamMode(SmMemory), position(0)
	{

	}

	Stream::~Stream()
	{
		if (streamMode != SmMemory)
			fileStream.close();
	}

	void Stream::ExpandMemoryStream(std::size_t length)
	{
		if (streamMode != SmMemory)
			return;

		if (position + length < buffer.size())
			return;

		if (position + length > buffer.size() + length)
			buffer.resize(position + length, 0);
		else
			buffer.resize(buffer.size() + length, 0);
	}

	unsigned char* Stream::DeflateStream(const StreamBuffer& sourceBuffer, std::size_t *deflatedLength)
	{
		// Find the required buffer size
		uLongf destSize = (uLongf)((uLongf)sourceBuffer.size() * 1.001) + 12;
		Bytef* destBuffer = new Bytef[destSize];

		// Deflate
		int result = compress2(destBuffer, &destSize, (const Bytef*)sourceBuffer.data(), sourceBuffer.size(), Z_BEST_COMPRESSION);
		if (result != Z_OK) {
			*deflatedLength = 0;
			return NULL;
		}

		*deflatedLength = (size_t)destSize;

		return (unsigned char*)destBuffer;
	}

	unsigned char* Stream::InflateStream(const StreamBuffer& sourceBuffer, std::size_t *infaltedLength)
	{
		z_stream stream;
		int len = sourceBuffer.size(), offset, retval;
		char* out = new char[len];
		memset(&stream, 0, sizeof(stream));

		stream.next_in	= (Bytef*)sourceBuffer.data();
		stream.avail_in = len;
		stream.next_out = (Bytef*)out;
		stream.avail_out = len;

		inflateInit(&stream);
		retval = inflate(&stream, 1);
		while(stream.avail_in && !retval)
		{
			offset = (int)stream.next_out - (int)out;
			len += 0x800;
			stream.avail_out += 0x800;
			out = (char*)realloc(out, len);

			stream.next_out = (Bytef*)((int)out + offset);
			retval = inflate(&stream, 1);
		}

		if (!retval)
			std::cerr << "[Warning] Unfinished compression?" << std::endl;
		else if (retval != 1)
		{
			std::cerr << "[Error  ] Compression error " << retval << std::endl;
			delete[] out;
		}

		len = stream.total_out;
		out = (char*)realloc((void*)out, len);
		inflateEnd(&stream);

		*infaltedLength = len;

		return (unsigned char*)out;
	}

	void Stream::Rewind()
	{
		if (streamMode == SmMemory)
			position = 0;
		else
		{
			fileStream.seekg(std::fstream::beg);
			fileStream.seekp(std::fstream::beg);
		}
	}

	void Stream::SetPosition(std::size_t value)
	{
		switch(streamMode)
		{
			case SmMemory:
				position = value;
				break;

			case SmRead:
				fileStream.seekg(std::fstream::beg, value);
				break;

			case SmWrite:
				fileStream.seekp(std::fstream::beg, value);
				break;
		}
	}

	std::size_t Stream::GetPosition()
	{
		switch(streamMode)
		{
			case SmMemory:
				return position;

			case SmRead:
				return static_cast<std::size_t>(fileStream.tellg());

			case SmWrite:
				return static_cast<std::size_t>(fileStream.tellp());
		}

		return 0;
	}

	std::size_t Stream::GetLength()
	{
		std::fstream::pos_type length = 0;

		if (streamMode == SmMemory)
			return buffer.size();

		if (streamMode == SmRead)
		{
			std::fstream::pos_type position = fileStream.tellg();
			fileStream.seekg(std::fstream::end);
			length = fileStream.tellg();
			fileStream.seekg(position, std::fstream::beg);
		}
		else
		{
			std::fstream::pos_type position = fileStream.tellp();
			fileStream.seekp(std::fstream::end);
			length = fileStream.tellp();
			fileStream.seekp(position, std::fstream::beg);
		}

		return static_cast<std::size_t>(length);
	}

	Stream::StreamBuffer Stream::GetMemoryBuffer() const
	{
		return buffer;
	}

	const unsigned char* Stream::GetRawMemoryBuffer() const
	{
		if (streamMode != SmMemory)
			return NULL;

		return buffer.data();
	}

	void Stream::ReadData(const StreamBuffer& value)
	{
		if (streamMode == SmMemory)
		{
			// TODO Is this even important?
		}
		else
			fileStream.read(reinterpret_cast<char*>(const_cast<unsigned char*>(value.data())), value.size());
	}

	bool Stream::ReadBoolean()
	{
		return ReadDword() >= 1;
	}
	
	unsigned char Stream::ReadByte()
	{
		unsigned char value = 0;
	
		if (streamMode == SmMemory)
		{
			value = *(unsigned char*)(buffer.data() + position);
			position += sizeof(unsigned char);
		}
		else
			fileStream.read(reinterpret_cast<char*>(&value), sizeof(unsigned char));

		return value;
	}

	unsigned short Stream::ReadWord()
	{
		unsigned short value = 0;

		if (streamMode == SmMemory)
		{
			value = *(unsigned short*)(buffer.data() + position);
			position += sizeof(unsigned short);
		}
		else
			fileStream.read(reinterpret_cast<char*>(&value), sizeof(unsigned short));

		return value;
	}

	unsigned int Stream::ReadDword()
	{
		unsigned int value = 0;

		if (streamMode == SmMemory)
		{
			value = *(unsigned int*)(buffer.data() + position);
			position += sizeof(unsigned int);
		}
		else
			fileStream.read(reinterpret_cast<char*>(&value), sizeof(unsigned int));

		return value;
	}

	unsigned long long Stream::ReadQword()
	{
		unsigned long long value = 0;

		if (streamMode == SmMemory)
		{
			value = *(unsigned long long*)(buffer.data() + position);
			position += sizeof(unsigned long long);
		}
		else
			fileStream.read(reinterpret_cast<char*>(&value), sizeof(unsigned long long));

		return value;
	}

	double Stream::ReadDouble()
	{
		double value = 0.0;

		if (streamMode == SmMemory)
		{
			value = *(double*)(buffer.data() + position);
			position += sizeof(double);
		}
		else
			fileStream.read(reinterpret_cast<char*>(&value), sizeof(double));

		return value;
	}

	float Stream::ReadFloat()
	{
		float value = 0.0f;

		if (streamMode == SmMemory)
		{
			value = *(float*)(buffer.data() + position);
			position += sizeof(float);
		}
		else
			fileStream.read(reinterpret_cast<char*>(&value), sizeof(float));

		return value;
	}

	std::string Stream::ReadString()
	{
		unsigned int length = ReadDword();

		if (streamMode == SmMemory)
		{
			std::string value(reinterpret_cast<const char*>(buffer.data() + position), length);
			position += length;

			return value;
		}
		else
		{
			std::string value(length, '\0');
			fileStream.read(const_cast<char*>(value.data()), length);

			return value;
		}

		return "";
	}

	time_t Stream::ReadTimestamp()
	{
		return (time_t)(8640000000000.0 * ReadDouble() + GmTimestampEpoch);
	}

	Stream* Stream::ReadBitmap()
	{
		if (!ReadBoolean())
			return NULL;

		return Deserialize();
	}

	void Stream::WriteData(const StreamBuffer& value)
	{
		if (streamMode == SmMemory)
		{
			ExpandMemoryStream(value.size());
			std::memcpy(buffer.data() + position, value.data(), value.size());
			position += value.size();
		}
		else
			fileStream.write(reinterpret_cast<const char*>(value.data()), value.size());
	}

	void Stream::WriteBoolean(bool value)
	{
		WriteDword(value ? 1 : 0);
	}

	void Stream::WriteByte(unsigned char value)
	{
		if (streamMode == SmMemory)
		{
			ExpandMemoryStream(sizeof(unsigned char));
			*(unsigned char*)(buffer.data() + position) = value;
			position += sizeof(unsigned char);
		}
		else
			fileStream.write(reinterpret_cast<const char*>(&value), sizeof(unsigned char));
	}

	void Stream::WriteWord(unsigned short value)
	{
		if (streamMode == SmMemory)
		{
			ExpandMemoryStream(sizeof(unsigned short));
			*(unsigned short*)(buffer.data() + position) = value;
			position += sizeof(unsigned short);
		}
		else
			fileStream.write(reinterpret_cast<const char*>(&value), sizeof(unsigned short));
	}

	void Stream::WriteDword(unsigned int value)
	{
		if (streamMode == SmMemory)
		{
			ExpandMemoryStream(sizeof(unsigned int));
			*(unsigned int*)(buffer.data() + position) = value;
			position += sizeof(unsigned int);
		}
		else
			fileStream.write(reinterpret_cast<const char*>(&value), sizeof(unsigned int));
	}

	void Stream::WriteQword(unsigned long long value)
	{
		if (streamMode == SmMemory)
		{
			ExpandMemoryStream(sizeof(unsigned long long));
			*(unsigned long long*)(buffer.data() + position) = value;
			position += sizeof(unsigned long long);
		}
		else
			fileStream.write(reinterpret_cast<const char*>(&value), sizeof(unsigned long long));
	}

	void Stream::WriteDouble(double value)
	{
		if (streamMode == SmMemory)
		{
			ExpandMemoryStream(sizeof(double));
			*(double*)(buffer.data() + position) = value;
			position += sizeof(double);
		}
		else
			fileStream.write(reinterpret_cast<const char*>(&value), sizeof(double));
	}

	void Stream::WriteFloat(float value)
	{
		if (streamMode == SmMemory)
		{
			ExpandMemoryStream(sizeof(float));
			*(float*)(buffer.data() + position) = value;
			position += sizeof(float);
		}
		else
			fileStream.write(reinterpret_cast<const char*>(&value), sizeof(float));
	}

	void Stream::WriteString(const std::string& value)
	{
		WriteDword(value.length());

		for(std::size_t i = 0; i < value.length(); ++i)
			WriteByte(value[i]);
	}

	void Stream::WriteTimestamp()
	{
		WriteDouble((double)(time(NULL) - GmTimestampEpoch) / 8640000000000.0);
	}

	void Stream::WriteBitmap(Stream* value)
	{
		WriteBoolean(value != NULL);
		
		if (value != NULL)
			Serialize(value);
	}

	void Stream::Deflate()
	{
		std::size_t deflatedLength = 0;

		unsigned char* deflatedBuffer = DeflateStream(buffer, &deflatedLength);
		if (deflatedLength == 0)
		{
			delete[] deflatedBuffer;
			return;
		}

		buffer.resize(deflatedLength);
		std::memcpy(buffer.data(), deflatedBuffer, deflatedLength);
		position = 0;

		delete[] deflatedBuffer;
	}
	
	void Stream::Inflate()
	{
		std::size_t inflatedLength = 0;

		unsigned char* inflatedBuffer = InflateStream(buffer, &inflatedLength);
		if (inflatedLength == 0)
		{
			delete[] inflatedBuffer;
			return;
		}

		buffer.resize(inflatedLength);
		std::memcpy(buffer.data(), inflatedBuffer, inflatedLength);
		position = 0;

		delete[] inflatedBuffer;
	}

	Stream* Stream::Deserialize(bool decompress)
	{
		Stream* value = new Stream();

		unsigned int length = ReadDword();
		StreamBuffer tmpBuffer(length, 0);
		ReadData(tmpBuffer);
		value->WriteData(tmpBuffer);
		value->Rewind();

		if (decompress)
			value->Inflate();

		return value;
	}

	void Stream::Serialize(Stream* stream, bool compress)
	{
		if (compress)
			stream->Deflate();

		WriteDword(stream->GetLength());
		WriteData(stream->GetMemoryBuffer());
	}
}
