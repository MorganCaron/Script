import CppUtils;
import CppUtils.Main;
import Script;

auto start([[maybe_unused]] std::span<const std::string_view> args) -> int
{
	CppUtils::Terminal::setConsoleOutputUTF8();
	std::cout << "Hello World!" << std::endl;
	return 0;
}
