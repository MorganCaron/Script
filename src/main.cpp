#include <Script.hpp>

std::unique_ptr<Script::Value> printNumber(const Script::Args& args)
{
	std::cout << Script::ensureType<Script::Number>(args[0])->getValue() << std::endl;
	return std::make_unique<Script::Void>(nullptr);
}

std::unique_ptr<Script::Value> printString(const Script::Args& args)
{
	std::cout << Script::ensureType<Script::String>(args[0])->getValue() << std::endl;
	return std::make_unique<Script::Void>(nullptr);
}

int main(const int argc, const char *argv[])
{
	try
	{
		const auto settings = Script::executeCommands(argc, argv);
		if (settings.abort)
			return 0;
		
		auto script = Script::Script{settings};
		script.addFunction(Script::FunctionSignature{"print", {Script::Number::TypeId}}, Script::Function{printNumber, Script::Void::TypeId});
		script.addFunction(Script::FunctionSignature{"print", {Script::String::TypeId}}, Script::Function{printString, Script::Void::TypeId});
		return Script::ensureType<Script::Number>(script.executeFile(settings.filename))->getValue();
	}
	catch (const std::exception& exception)
	{
		CppUtils::Log::Logger::logError("An exception occurred: "s + exception.what());
		return 1;
	}
}
