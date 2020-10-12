#pragma once

#include <string>

#include <CppUtils.hpp>

namespace Language::AST::Variable
{
	struct VariableSignature
	{
		std::string name;
		bool constant;
		CppUtils::Type::TypeId type;

		VariableSignature() = default;
		VariableSignature(std::string c_name, bool c_constant, CppUtils::Type::TypeId c_type):
			name{std::move(c_name)},
			constant{c_constant},
			type{std::move(c_type)}
		{}

		[[nodiscard]] bool operator==(const VariableSignature& rhs) const
		{
			return name == rhs.name;
		}
	};
}
