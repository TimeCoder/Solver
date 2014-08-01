#include "stdafx.h"
#include "Expert.h"
#include "Fact.h"
#include "Rule.h"
#include "FactsGrammar.h"
#include "RulesGrammar.h"

namespace Logic
{
	void Expert::Think(std::string factsString, std::string rulesString, TFacts& newFacts)
	{
		// Парсим факты
		FactsGrammar<std::string::iterator> factsGrammar;
		if (!qi::phrase_parse(std::begin(factsString), std::end(factsString), factsGrammar, qi::space))
		{
			throw std::invalid_argument("Can't parse facts");
		}

		// Парсим правила
		RulesGrammar<std::string::iterator> rulesGrammar;
		if (!qi::phrase_parse(std::begin(rulesString), std::end(rulesString), rulesGrammar, qi::space))
		{
			throw std::invalid_argument("Can't parse rules");
		}

		TFacts facts = factsGrammar.Facts();
		const TRules& rules = rulesGrammar.Rules();

		// Делаем вывод новых фактов
		bool hasNewFacts;
		do
		{
			hasNewFacts = false;

			for (auto rule : rules)
			{
				// Вычисляем новый факт
				auto newFact = rule.Apply(facts);

				// Получен истинный факт, и он еще не известен?
				if (newFact.is_initialized() && newFact.get().IsFalseOn(facts))
				{
					// Заносим его
					facts.push_back(newFact.get());
					newFacts.push_back(newFact.get());
					hasNewFacts = true;
				}
			}

		} while (hasNewFacts); // Пока появляются новые факты
	}

}