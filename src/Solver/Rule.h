#pragma once
#include "Fact.h"

namespace Logic
{
	class Rule
	{
	public:
		enum class eOperations { AND, OR };

		struct Operand
		{
			eOperations operation;
			Fact fact;
		};

		typedef std::list<Operand> TOperations;

		Fact Premise;
		TOperations Expression;
		Fact Implication;
			
		boost::optional<Fact> Apply(TFacts& knownFacts) const;
	};

	typedef std::list<Rule> TRules;
}