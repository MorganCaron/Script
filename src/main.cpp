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

int main(int ac, char *av[])
{
	auto filename = (ac > 1) ? av[1] : "program.script";
	auto script = Script::Script{};
	script.addFunction("print", std::make_unique<Script::ExternalFunction>(print));
	return Script::ensureType<Script::Number>(script.executeFile(filename))->getValue();
}
