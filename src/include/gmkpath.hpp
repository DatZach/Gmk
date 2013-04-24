/*
 *	gmkpath.hpp
 *	GMK Path
 */

#ifndef __GMK_PATH_HPP
#define __GMK_PATH_HPP

#include <gmkresource.hpp>
#include <gmkroom.hpp>

namespace Gmk
{
	class Path : public GmkResource
	{
	public:
		static const int RoomIndexNone				= -1;

		enum ConnectionKind
		{
			KindStraight,
			KindSmooth
		};

		typedef struct _Point
 		{
			double		x;
			double		y;
			double		speed;
	 	} Point;

	private:
		int						roomIndex;

	protected:
		void WriteVer81(Stream* stream);
		void ReadVer81(Stream* stream);

	public:
		std::string				name;
		unsigned int			connectionKind;
		bool					closed;
		unsigned int			precision;
		Room*					room;
		unsigned int			snapX;
		unsigned int			snapY;
		std::vector<Point>		points;

		Path(Gmk* gmk);
		~Path();

		void Finalize();
	};
}

#endif
