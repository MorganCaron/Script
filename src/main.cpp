import std;
import CppUtils;
import Script;

auto start([[maybe_unused]] std::span<const std::string_view> args) -> int
{
	Script::test();
	return CppUtils::exitSuccess;
}
