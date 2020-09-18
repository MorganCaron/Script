#pragma once

#include <CppUtils.hpp>
#include <Script.hpp>

namespace UnitTests::Variable
{
	const auto tests = std::vector<CppUtils::Test::UnitTest>{

		CppUtils::Test::UnitTest("Constant", [] {
			static const auto src = "\
			function main(): Number\
			{\
				const variable = 42;\
				return variable;\
			}"s;
			auto script = Script::Script{Script::Settings{ .verbose = true, .chrono = true }};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		}),

		CppUtils::Test::UnitTest("Variable", [] {
			static const auto src = "\
			function main(): Number\
			{\
				let variable = 42;\
				return variable;\
			}"s;
			auto script = Script::Script{Script::Settings{ .verbose = true, .chrono = true }};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		})

	};
}
