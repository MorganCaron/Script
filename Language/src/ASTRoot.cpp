#include <Language/ASTRoot.hpp>

#include <Language/Instruction/Bracket.hpp>
#include <Language/Instruction/ControlStructure.hpp>
#include <Language/Instruction/FunctionDeclaration.hpp>
#include <Language/Instruction/ImportDeclaration.hpp>
#include <Language/Instruction/VariableDeclaration.hpp>
#include <Language/Instruction/Object.hpp>
#include <Language/Instruction/Operator.hpp>
#include <Language/Instruction/Return.hpp>
#include <Language/Instruction/Value.hpp>

namespace Language
{
	ASTRoot::ASTRoot()
	{
		addNativeRules();
	}

	ASTRoot::ASTRoot(std::string src)
	{
		addNativeRules();
		parse(std::move(src));
	}

	void ASTRoot::parse(const std::string src)
	{
		auto pos = std::size_t{0};
		auto parsingInformations = Parser::ParsingInformations{*this, *this, src, pos};
		const auto length = parsingInformations.src.length();
		
		while (parsingInformations.pos < length)
		{
			auto instruction = Parser::parseInstruction(parsingInformations);
			if (instruction != nullptr)
				addInstruction(std::move(instruction));
			parsingInformations.skipSpaces();
		}
	}

	void ASTRoot::interpret()
	{
		for (auto& instruction : m_instructions)
			static_cast<void>(instruction->interpret());
	}

	void ASTRoot::addNativeRules()
	{
		static const auto nativeInstructions = std::unordered_map<std::string, Parser::InstructionParser>{
			{ "Bracket", &Instruction::Bracket::parse },
			{ "Control structure", &Instruction::ControlStructure::parse },
			{ "Function declaration", &Instruction::FunctionDeclaration::parse },
			{ "Import declaration", &Instruction::ImportDeclaration::parse },
			{ "Variable declaration", &Instruction::VariableDeclaration::parse },
			{ "Object", &Instruction::Object::parse },
			{ "Return", &Instruction::Return::parse },
			{ "Value", &Parser::parseValue }
		};
		addInstructionParsers(nativeInstructions);

		static const auto nativeValues = std::unordered_map<std::string, Parser::ValueParser>{
			{ "Operation", std::bind(&Instruction::Operator::parseOperation, std::placeholders::_1, nullptr, nullptr) }
		};
		addValueParsers(nativeValues);
	}
}
