#include "stdafx.h"
#include "Fact.h"

namespace Logic
{
	std::map<size_t, std::string> Fact::FactsRepository;
	
	bool Fact::operator == (const Fact& other) const
	{
		if (this == &other)
			return true;
		return Id == other.Id;
	}

	bool Fact::IsTrueOn(const TFacts& facts) const
	{
		return (std::find(facts.begin(), facts.end(), *this) != facts.end());
	}
	
	bool Fact::IsFalseOn(const TFacts& facts) const
	{
		return !IsTrueOn(facts);
	}

	Fact Fact::FromString(const std::string& str)
	{
		static std::hash<std::string> hash_fn;
		Fact fact; 
		fact.Id = hash_fn(str);
		FactsRepository[fact.Id] = str;
		
		return fact;
	}

	std::string Fact::ToString(Fact fact)
	{
		return FactsRepository[fact.Id];
	}
}