#pragma once
#include <boost/spirit/include/qi.hpp>
#include <boost/bind.hpp>
#include "Fact.h"

namespace Logic
{
	namespace qi = boost::spirit::qi;

	template <typename Iterator>
	class FactsGrammar : public qi::grammar<Iterator>
	{
		TFacts _factsList;
		qi::rule<Iterator> _facts, _fact;
	
	public:
		// "fact1", "fact2", ...
		FactsGrammar() : FactsGrammar::base_type(_facts)
		{
			_fact = qi::as_string[qi::raw[+(qi::alnum | '_')]]
				[boost::bind(&FactsGrammar::AddFact, this, _1)];
			_facts = (*qi::space >> '"' >> _fact >> '"' >> *qi::space) % ',';
		}

		void AddFact(const std::string& factStr)
		{
			_factsList.push_back(Fact::FromString(factStr));
		}

		const TFacts& Facts() const { return _factsList; }
	};
}