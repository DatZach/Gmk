/*
 *	gmkpath.hpp
 *	GMK Path
 */

#include <gmkresource.hpp>

namespace Gmk
{
	class Path : public GmkResource
	{
	protected:
		void WriteVer81(Stream* stream);
		void ReadVer81(Stream* stream);

	public:
		Path(Gmk* gmk);
		~Path();
	};
}
