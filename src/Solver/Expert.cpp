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

		// Выводим новые факты
		bool hasNewFacts;
		do
		{
			hasNewFacts = false;

			for (auto rule : rules)
			{
				// С помощью правила Выводим новый факт из уже известных фактов
				auto newFact = rule.Apply(facts);

				// Факт еще не известен?
				if (newFact.is_initialized() && newFact.get().IsFalseOn(facts))
				{
					// Добавляем
					facts.push_back(newFact.get());
					newFacts.push_back(newFact.get());
					hasNewFacts = true;
				}
			}

		} while (hasNewFacts); // Ïîêà ïîÿâëÿþòñÿ íîâûå ôàêòû
	}

}
