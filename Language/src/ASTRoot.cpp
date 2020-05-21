#include <Language/ASTRoot.hpp>

#include <Language/Instruction/Bracket.hpp>
#include <Language/Instruction/ControlStructure.hpp>
#include <Language/Instruction/FunctionStatement.hpp>
#include <Language/Instruction/ImportStatement.hpp>
#include <Language/Instruction/Object.hpp>
#include <Language/Instruction/Operator.hpp>
#include <Language/Instruction/Value.hpp>
#include <Language/Instruction/Return.hpp>

namespace Language
{
	ASTRoot::ASTRoot()
	{
		addNativeInstructions();
	}

	ASTRoot::ASTRoot(std::string src)
	{
		addNativeInstructions();
		parse(std::move(src));
	}

	void ASTRoot::parse(const std::string src)
	{
		auto pos = std::size_t{0};
		auto parsingInformations = Parser::ParsingInformations{*this, *this, src, pos};
		const auto length = parsingInformations.src.length();

		CppUtils::Logger::logImportant("#- PARSER_/");
		while (parsingInformations.pos < length)
		{
			auto instruction = parsingInformations.parseInstruction();
			if (instruction != nullptr)
				addInstruction(std::move(instruction));
			parsingInformations.skipSpaces();
		}
	}

	void ASTRoot::interpret()
	{
		CppUtils::Logger::logImportant("#- INTERPRETER_/");
		for (auto& instruction : m_instructions)
			static_cast<void>(instruction->interpret());
	}

	void ASTRoot::addNativeInstructions()
	{
		static const auto nativeInstructions = std::unordered_map<std::string, Parser::InstructionParser>{
			{ "Bracket", &Instruction::Bracket::parse },
			{ "ControlStructure", &Instruction::ControlStructure::parse },
			{ "FunctionStatement", &Instruction::FunctionStatement::parse },
			{ "ImportStatement", &Instruction::ImportStatement::parse },
			{ "Object", &Instruction::Object::parse },
			{ "Return", &Instruction::Return::parse },
			{ "Operation", std::bind(&Instruction::Operator::parseOperation, std::placeholders::_1, nullptr, nullptr) }
		};
		addInstructionParsers(nativeInstructions);
	}
}
