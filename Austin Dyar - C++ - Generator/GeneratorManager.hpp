// Coder:	Austin Dyar
// Date:	27 July 2018
// File:	GeneratorManager.hpp
// Purpose: Keeps all of the generators inside of a singleton

#ifndef GeneratorManager_HG_
#define GeneratorManager_HG_

#include "Generator.hpp"
#include "DieGenerator.hpp"
#include "FactorialGenerator.hpp"
#include "FibonacciGenerator.hpp"
#include "LinearGenerator.hpp"
#include "PowerGenerator.hpp"
#include "PrimeGenerator.hpp"
#include "SineGenerator.hpp"
#include "PermutationGenerator.hpp"
#include <mutex>

class GeneratorManager {
private:
	static std::unique_ptr<GeneratorManager>	_generateManager;
	static std::once_flag						_once;
	
	static std::vector<Generator*>				_generators;
		
public:
	static GeneratorManager& createManager() {
		std::call_once(_once, []() {
		_generateManager.reset(new GeneratorManager);

		_generators.push_back(new DieGenerator);
		_generators.push_back(new FactorialGenerator);
		_generators.push_back(new FibonacciGenerator);
		_generators.push_back(new LinearGenerator);
		_generators.push_back(new PowerGenerator);
		_generators.push_back(new PrimeGenerator);
		_generators.push_back(new SineGenerator);
		_generators.push_back(new PermutationGenerator);
		});
		return *_generateManager;
	}

	static void createOnce() {
		_once;
	}

	std::vector<Generator*> generators()
	{
		return _generators;
	}

	Generator* get(unsigned int index)
	{
		return _generators[index];
	}
};

std::once_flag GeneratorManager::_once;
std::unique_ptr<GeneratorManager> GeneratorManager::_generateManager;
std::vector<Generator*> GeneratorManager::_generators;

#endif // GeneratorManager_HG_
