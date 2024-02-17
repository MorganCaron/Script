import CppUtils;
import Script.UnitTests;

inline constexpr auto exitSuccess = 0;
inline constexpr auto exitFailure = 1;

// Todo: std::span<const std::string_view> args
int main([[maybe_unused]] const int argc, [[maybe_unused]] const char* argv[])
{
	try
	{
		CppUtils::Terminal::setConsoleOutputUTF8();
		/*
		auto& settings = CppUtils::UnitTest::executeCommands(argc, argv);
		if (settings.abort)
			return exitSuccess;
		*/
		auto settings = CppUtils::UnitTest::TestSettings{};
		return CppUtils::UnitTest::executeTests(std::move(settings));
	}
	catch (const std::exception& exception)
	{
		CppUtils::logException(exception);
		return exitFailure;
	}
	return exitSuccess;
}
