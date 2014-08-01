#pragma once
#include "fact.h"

namespace Logic
{
	class Expert
	{
	public:
		void Think(std::string factsString, std::string rulesString, TFacts& newFacts);
	};
}