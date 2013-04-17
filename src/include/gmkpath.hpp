/*
 *	gmkpath.hpp
 *	GMK Path
 */

#include <gmkresource.hpp>

namespace Gmk
{
	class Path : public GmkResource
	{
	public:
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

	protected:
		void WriteVer81(Stream* stream);
		void ReadVer81(Stream* stream);

	public:
		std::string				name;
		unsigned int			connectionKind;
		bool					closed;
		unsigned int			precision;
		int						roomIndex;
		unsigned int			snapX;
		unsigned int			snapY;
		std::vector<Point>		points;

		Path(Gmk* gmk);
		~Path();
	};
}
