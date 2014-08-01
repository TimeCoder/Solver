#include "stdafx.h"
#include "Expert.h"
#include "Fact.h"

int main()
{
	std::ifstream factsFile("facts.txt");
	std::string factsString((std::istreambuf_iterator<char>(factsFile)), (std::istreambuf_iterator<char>()));

	std::ifstream rulesFile("rules.txt");
	std::string rulesString((std::istreambuf_iterator<char>(rulesFile)), (std::istreambuf_iterator<char>()));

	Logic::TFacts newFacts;
	Logic::Expert expert;

	try
	{
		expert.Think(factsString, rulesString, newFacts);

		std::cout << "New facts:\n";
		for (auto fact : newFacts)
		{
			std::cout << Logic::Fact::ToString(fact) << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}