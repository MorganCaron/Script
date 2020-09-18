#include <Script.hpp>

std::unique_ptr<Script::Value> print(const Script::Args& args)
{
	if (args.size() != 1)
		throw std::runtime_error{"La fonction print(text); prend 1 argument."};
	if (args[0]->isType(Script::String::TypeId))
		std::cout << Script::ensureType<Script::String>(args[0])->getValue() << std::endl;
	else if (args[0]->isType(Script::Number::TypeId))
		std::cout << Script::ensureType<Script::Number>(args[0])->getValue() << std::endl;
	return std::make_unique<Script::Number>(0);
}

int main(const int argc, const char *argv[])
{
	try
	{
		const auto settings = Script::executeCommands(argc, argv);
		if (settings.abort)
			return 0;
		
		auto script = Script::Script{settings};
		script.addFunction(Script::FunctionSignature{"print"}, std::make_unique<Script::ExternalFunction>(print, Language::AST::Type::VoidType));
		return Script::ensureType<Script::Number>(script.executeFile(settings.filename))->getValue();
	}
	catch (const std::exception& exception)
	{
		CppUtils::Log::Logger::logError("An exception occurred: "s + exception.what());
		return 1;
	}
}
