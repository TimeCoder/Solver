#include "stdafx.h"
#include "Rule.h"

namespace Logic
{
	// Передаются известные факты: дает возможность вычислять любое высказывание 
	// на изолированном множестве посылок
	boost::optional<Fact> Rule::Apply(TFacts& knownFacts) const
	{
		boost::optional<Fact> result;

		// Начинаем движение по выражению, с первого факта
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

		// В итоге истинное выражение? Тогда возвращаем факт
		if (isTrue) result = Implication;

		return result;
	}
}