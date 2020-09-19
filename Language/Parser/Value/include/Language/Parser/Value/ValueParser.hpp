#pragma once

#include <Language/AST/ParsingTools/Context.hpp>
#include <Language/Parser/Operator/OperatorParser.hpp>

namespace Language::Parser::Value
{
	inline std::unique_ptr<AST::Core::Instruction> parseValue(AST::ParsingTools::Context& context)
	{
		auto& [container, scope, cursor, verbose] = context;

		context.skipSpacesAndComments();
		if (cursor.isEndOfString())
			return nullptr;
		
		const auto& parserScope = dynamic_cast<const AST::ParsingTools::ParserScope&>(scope.findScope(AST::ParsingTools::ParserScopeType));
		const auto& valueParsers = parserScope.getValueParsers();
		for (const auto& [parserName, parserFunction] : valueParsers)
		{
			auto startPos = cursor.pos;
			try
			{
				auto instruction = parserFunction(context);
				if (instruction)
					return Operator::parseOperator(context, std::move(instruction));
				cursor.pos = startPos;
			}
			catch (const std::exception& error)
			{
				cursor.pos = startPos;
				throw std::runtime_error{"In "s + parserName + ":\n" + error.what()};
			}
		}
		return nullptr;
	}
}
