/*
 *	gmkaction.hpp
 *	GMK Action
 */

#ifndef __GMK_ACTION_HPP
#define __GMK_ACTION_HPP

#include <gmkresource.hpp>

namespace Gmk
{
	class Action : public GmkResource
	{
	public:
		static const unsigned int ARGUMENT_COUNT = 8;

		enum ActionId
		{
			// TODO See Lib Builder?
		};

		enum ActionKind
		{
			// TODO See Lib Builder
		};

		enum ActionType
		{
			AtNothing,
			AtFunction,
			AtCode
		};

		enum AppliesTo
		{
			ApSelf			= -1,
			ApOther			= -2
		};

	protected:
		void WriteVer81(Stream* stream);
		void ReadVer81(Stream* stream);

	public:
		std::string				functionName;
		std::string				functionCode;
		std::string				argumentValue[ARGUMENT_COUNT];
  		unsigned int			libraryId;
		unsigned int			actionId;
		unsigned int			kind;
		unsigned int			type;
		unsigned int			argumentsUsed;
		unsigned int			argumentKind[ARGUMENT_COUNT];
		unsigned int			appliesToObject;
		bool					relative;
		bool					appliesToSomething;
		bool					question;
		bool					mayBeRelative;
		bool					not;

		Action(Gmk* gmk);
		~Action();
	};
}

#endif
