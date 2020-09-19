#pragma once

#include <string_view>

#include <CppUtils.hpp>
#include <Language/AST/Core/InstructionContainer.hpp>
#include <Language/AST/Scope/BaseScope.hpp>
#include <Language/AST/Instruction/Operator.hpp>

using namespace std::literals;

namespace Language::AST::ParsingTools
{
	struct Context
	{
		explicit Context(Core::InstructionContainer& c_container, Scope::BaseScope& c_scope, CppUtils::Parser::Cursor c_cursor, bool c_verbose):
			container{c_container}, scope{c_scope}, cursor{c_cursor}, verbose{c_verbose}
		{}

	private:
		bool parseComment()
		{
			if (cursor.isEndOfString())
				return false;
			
			auto& [src, pos] = cursor;
			
			if (pos + 1 < src.size() && cursor.getChar() == '/' && src.at(pos + 1) == '/')
			{
				pos += 2;
				while (!cursor.isEndOfString() && cursor.getChar() != '\n')
					++pos;
				if (cursor.getChar() == '\n')
					++pos;
				return true;
			}
			if (pos + 1 < src.size() && cursor.getChar() == '/' && src.at(pos + 1) == '*')
			{
				pos += 2;
				while (pos + 1 < src.size() && (cursor.getChar() != '*' || src.at(pos + 1) != '/'))
					++pos;
				if (pos + 1 == src.size())
					throw std::runtime_error{"Commentaire jamais ferme."};
				else
					pos += 2;
				return true;
			}
			return false;
		}
		
	public:
		void skipSpacesAndComments()
		{
			do
			{
				if (!cursor.isEndOfString() && std::isspace(cursor.getChar()))
					cursor.skipSpaces();
			} while (parseComment());
		}

		void parseSemicolon()
		{
			skipSpacesAndComments();
			if (cursor.isEndOfString() || cursor.getChar() != ';')
				CppUtils::Log::Logger::logWarning("You forgot a semicolon after an instruction.\nSemicolons avoid misunderstandings by separating each instruction separately.\nWithout a semicolon, Script may think that two instructions form an operation if an operator is found between them.");
			else if (verbose)
				CppUtils::Log::Logger::logInformation(";", false);
			++cursor.pos;
		}

		Core::InstructionContainer& container;
		Scope::BaseScope& scope;
		CppUtils::Parser::Cursor cursor;
		bool verbose;
	};

	using DeclarationParser = std::function<std::unique_ptr<Core::Instruction>(Context&)>;
	using InstructionParser = std::function<std::unique_ptr<Core::Instruction>(Context&)>;
	using ValueParser = std::function<std::unique_ptr<Core::Instruction>(Context&)>;
	using OperatorParser = std::function<std::unique_ptr<Core::Instruction>(Context&, std::unique_ptr<Core::Instruction>&&)>;
}
