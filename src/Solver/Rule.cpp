#include "stdafx.h"
#include "Rule.h"

namespace Logic
{
	// Вывод нового факта на основе правила
	boost::optional<Fact> Rule::Apply(TFacts& knownFacts) const
	{
		boost::optional<Fact> result;

		// Начинаем с первого факта в выражении
		bool isTrue = Premise.IsTrueOn(knownFacts);

		for (auto operand : Expression)
		{
			switch (operand.operation)
			{
			case eOperations::AND:
				isTrue &= operand.fact.IsTrueOn(knownFacts);
				break;
			case eOperations::OR:
				isTrue |= operand.fact.IsTrueOn(knownFacts);
				break;
			};
		}

		if (isTrue) result = Implication;

		return result;
	}
}
