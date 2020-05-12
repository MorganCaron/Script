#include "Script.hpp"

int main(int ac, char *av[])
{
	auto filename = (ac > 1) ? av[1] : "program.script";
	auto script = Script::Script{};
	script.executeFile(filename);
	std::this_thread::sleep_for(3s);
	return 0;
}
