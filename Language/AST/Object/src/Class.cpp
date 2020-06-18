#include <Language/AST/Object/Class.hpp>

#include <Language/AST/Object/ObjectScope.hpp>
#include <Language/AST/Function/FunctionDeclaration.hpp>

namespace Language::AST::Object
{
	Class::Class(Class const &src):
		Instance{src},
		Core::Instruction{src},
		Core::InstructionContainer{src}
	{
		for (const std::pair<const std::string, std::unique_ptr<Function::FunctionType>>& pair : getFunctions())
			addFunction(pair.first, std::make_unique<Function::FunctionDeclaration>(static_cast<const Function::FunctionDeclaration&>(*pair.second)));
	}

	Class &Class::operator=(Class const &rhs)
	{
		Instance::operator=(rhs);
		Core::Instruction::operator=(rhs);
		Core::InstructionContainer::operator=(rhs);
		for (const std::pair<const std::string, std::unique_ptr<Function::FunctionType>>& pair : getFunctions())
			addFunction(pair.first, std::make_unique<Function::FunctionDeclaration>(static_cast<const Function::FunctionDeclaration&>(*pair.second)));
		return *this;
	}

	void Class::indexe()
	{
		CppUtils::Logger::logInformation("Declare "s + Keyword.data() + " " + getName().data() + "{", false);
		auto& objectScope = dynamic_cast<ObjectScope&>(getScope().findScope(ObjectScopeType));
		objectScope.addInstance(this);
		CppUtils::Logger::logInformation("}");
		m_instructions[0]->indexe();
	}

	std::unique_ptr<Type::IValue> Class::interpret()
	{
		return std::make_unique<Type::Number>(0);
	}
}
