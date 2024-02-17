#pragma once

#include <string>
#include <vector>
#include <numeric>

#include <CppUtils.hpp>

namespace Script::Language::AST::Function
{
	struct FunctionSignature
	{
		const std::string name;
		const std::vector<CppUtils::Type::Token> argumentTypes;
		const std::string printable;
		const CppUtils::Type::Token type;
		
		FunctionSignature(std::string c_name, std::vector<CppUtils::Type::Token> c_argumentTypes):
			name{std::move(c_name)},
			argumentTypes{std::move(c_argumentTypes)},
			printable{getPrintable()},
			type{printable}
		{}

		[[nodiscard]] bool operator==(const FunctionSignature& rhs) const noexcept
		{
			return name == rhs.name && argumentTypes == rhs.argumentTypes;
		}

		struct hash_fn
		{
			[[nodiscard]] constexpr std::size_t operator()(const FunctionSignature &functionSignature) const noexcept
			{
				return functionSignature.type.id;
			}
		};

	private:
		[[nodiscard]] std::string getPrintable() const
		{
			return name + "(" + std::accumulate(argumentTypes.begin(), argumentTypes.end(), std::string{},
				[](std::string buffer, const CppUtils::Type::Token &argumentType) {
					return buffer.empty() ? argumentType.name.data() : (buffer + "," + argumentType.name.data());
				}) + ")";
		}
	};
}
