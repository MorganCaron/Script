#include "Script.hpp"

int main(int ac, char *av[])
{
	auto filename = (ac > 1) ? av[1] : "program.script";
	auto script = Script::Script{};
	return Language::Scope::Type::ensureType<Language::Scope::Type::Number>(script.executeFile(filename))->getValue();
}
