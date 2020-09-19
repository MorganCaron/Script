#pragma once

#include <CppUtils.hpp>
#include <Script.hpp>

namespace UnitTests::Function
{
	const auto tests = std::vector<CppUtils::Test::UnitTest>{

		CppUtils::Test::UnitTest("Main function", [] {
			static const auto src = "\
			function main(): Number\
				return 42;"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		}),

		CppUtils::Test::UnitTest("Internal function call", [] {
			static const auto src = "\
			function foobar(): Number\
				return 42;\
			\
			function main(): Number\
				return foobar();"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		}),

		CppUtils::Test::UnitTest("Internal function call with argument", [] {
			static const auto src = "\
			function foobar(const nb: Number): Number\
				return nb;\
			\
			function main(): Number\
				return foobar(42);"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		}),

		CppUtils::Test::UnitTest("Function polymorphism: Argument type", [] {
			static const auto src = "\
			function foobar(const nb: Number): Number\
				return 21;\
			\
			function foobar(const str: String): Number\
				return 42;\
			\
			function main(): Number\
				return foobar(\"test\");"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		}),

		CppUtils::Test::UnitTest("Function polymorphism: Return type", [] {
			static const auto src = "\
			function foobar(): Number\
				return 42;\
			\
			function foobar(): String\
				return \"fail\";\
			\
			function main(): Number\
				return foobar();"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		}),

		CppUtils::Test::UnitTest("Function template", [] {
			static const auto src = "\
			function foobar<T>(value: T): T\
				return value;\
			\
			function foobar(str: String): String\
				return str;\
			\
			function main(): Number\
				return foobar(42);"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		})
		
	};
}
