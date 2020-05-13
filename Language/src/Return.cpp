#include "Language/Return.hpp"

#include "Language/AST.hpp"
#include "Language/Operator.hpp"

namespace Language
{
	std::unique_ptr<Scope::Type::Value> Return::interpret()
	{
		auto value = m_instructions.at(0)->interpret();
		auto stream = std::stringstream{};
		value->print(stream);
		CppUtils::Logger::logInformation(std::string{Keyword::ReturnStatement} + " " + stream.str());
		return value;
	}
}
