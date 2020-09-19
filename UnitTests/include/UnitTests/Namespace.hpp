#pragma once

#include <CppUtils.hpp>
#include <Script.hpp>

namespace UnitTests::Namespace
{
	const auto tests = std::vector<CppUtils::Test::UnitTest>{

		CppUtils::Test::UnitTest("Variable in a namespace", [] {
			static const auto src = "\
			namespace Test\
			{\
				const variable = 42;\
			}\
			\
			function main(): Number\
			{\
				return Test::variable;\
			}"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		})

	};
}
