#pragma once

#include <CppUtils.hpp>

#include <Language/AST/Function/FunctionScope.hpp>

namespace Script::Language::AST::Object
{
	class Instance:
		public CppUtils::Type::Named,
		public Function::FunctionScope
	{
	public:
		Instance() = default;
		Instance(const Instance&) = default;
		Instance(Instance&&) noexcept = default;
		virtual ~Instance() = default;
		Instance& operator=(const Instance&) = default;
		Instance& operator=(Instance&&) noexcept = default;
		
		Instance(std::string name, const Function::FunctionScope& functionScope):
			CppUtils::Type::Named{std::move(name)},
			Function::FunctionScope{functionScope}
		{}

		bool operator==(const Instance& rhs) const
		{
			if (getName() != rhs.getName())
				return false;
			return Variable::VariableScope::operator==(rhs);
		}

		void callConstructor(const Type::Args& arguments)
		{
			auto argumentTypes = std::vector<CppUtils::Type::Token>{};
			std::transform(arguments.begin(), arguments.end(), std::back_inserter(argumentTypes), [](const auto& argument) {
				return argument->getType();
			});
			const auto constructorSignature = Function::FunctionSignature{"constructor", std::move(argumentTypes)};
			if (functionExists(constructorSignature))
			{
				const auto& constructor = getFunction(constructorSignature);
				constructor.function(arguments);
			}
		}
	};
}
