#pragma once
#include <string>

namespace Logic
{
	class Fact;
	typedef std::list<Fact> TFacts;
	
	// Факт
	class Fact
	{
		// Чтобы ускорить рпботу с объектами, храним только Id,
		// а текст заносим в статический репозиторий

		size_t Id;
		static std::map<size_t, std::string> FactsRepository;

	public:
		bool operator == (const Fact& other) const;

		bool IsTrueOn(const TFacts& facts) const;
		bool IsFalseOn(const TFacts& facts) const;

		static Fact FromString(const std::string& str);
		static std::string ToString(Fact fact);
	};
}
