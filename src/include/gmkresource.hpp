/*
 *	gmkresource.hpp
 *	GMK Resource
 */

#ifndef __GMK_RESOURCE_HPP
#define __GMK_RESOURCE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <stream.hpp>
#include <gmkcommon.hpp>

namespace Gmk
{
	class Gmk;

	class GmkResource
	{
	public:
		enum ResourceType
		{
			RtSprite,
			RtSound,
			RtBackground,
			RtPath,
			RtScript,
			RtFont,
			RtTimeline,
			RtObject,
			RtRoom,
			RtUnknown,
			RtCount
		};

		GmkResource* GetResource(unsigned int type, unsigned int index) const;

	protected:
		Gmk* gmkHandle;
		bool exists;

		virtual void WriteVer81(Stream* stream) = 0;
		virtual void ReadVer81(Stream* stream) = 0;

	public:
		std::string name;

		GmkResource(Gmk* gmk);

		void Write(Stream* stream);
		void Read(Stream* stream);
		virtual void Finalize();

		virtual int GetId() const;
		bool GetExists() const;
	};
}

#endif
