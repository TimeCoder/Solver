#pragma once
#include <boost/spirit/include/qi.hpp>
#include <boost/bind.hpp>
#include "Fact.h"

namespace Logic
{
	namespace qi = boost::spirit::qi;

	// "fact1, fact2 -> fact3", "fact3| fact4 -> fact5", ...
	template <typename Iterator>
	class RulesGrammar : public qi::grammar<Iterator>
	{
		TRules _rulesList;
		Rule _stackRule;
		qi::rule<Iterator> _operand, _expression, _rule, _implication, _rules;

	public:
		RulesGrammar() : RulesGrammar::base_type(_rules)
		{
			_operand = qi::as_string[qi::raw[+(qi::alnum | '_')]];

			_expression = qi::as_string[qi::raw[_operand]]
				[boost::bind(&RulesGrammar::Premise, this, _1)]
			    >> *
				(
				    ',' >> qi::space >> qi::as_string[qi::raw[_operand]]
						[boost::bind(&RulesGrammar::And, this, _1)]
					|
					'|' >> qi::space >> qi::as_string[qi::raw[_operand]]
						[boost::bind(&RulesGrammar::Or, this, _1)]
				);

			_rule = _expression >> *qi::space >> "->" >> *qi::space >> _implication;

			_implication = qi::as_string[qi::raw[_operand]]
				[boost::bind(&RulesGrammar::Implication, this, _1)];

			_rules = (*qi::space >> '"' >> _rule >> '"' >> *qi::space) % ',';
		}

		// Посылка
		void Premise(const std::string& factStr)
		{
			_stackRule.Expression.clear();
			_stackRule.Premise = Fact::FromString(factStr);
		}

		// Операнд И
		void And(const std::string& factStr)
		{
			_stackRule.Expression.push_back(Rule::Operand{ Rule::eOperations::AND, Fact::FromString(factStr) });
		}

		// Оператор ИЛИ
		void Or(const std::string& factStr)
		{
			_stackRule.Expression.push_back(Rule::Operand{ Rule::eOperations::OR, Fact::FromString(factStr) });
		}

		// Вывод
		void Implication(const std::string& factStr)
		{
			_stackRule.Implication = Fact::FromString(factStr);
			_rulesList.push_back(_stackRule);
		}

		const TRules&  Rules() const { return _rulesList; }
	};

}