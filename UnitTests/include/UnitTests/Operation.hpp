#pragma once

#include <CppUtils.hpp>
#include <Script.hpp>

namespace UnitTests::Operation
{
	const auto tests = std::vector<CppUtils::Test::UnitTest>{

		CppUtils::Test::UnitTest("Variable = literal", [] {
			static const auto src = "\
			function main(): Number\
			{\
				const variable = 42;\
				return variable;\
			}"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		}),

		CppUtils::Test::UnitTest("Variable = Variable", [] {
			static const auto src = "\
			function main(): Number\
			{\
				const variable0 = 42;\
				const variable1 = variable0;\
				return variable1;\
			}"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		}),

		CppUtils::Test::UnitTest("Number + Number", [] {
			static const auto src = "\
			function main(): Number\
				return 21 + 21;"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		}),

		CppUtils::Test::UnitTest("String + String", [] {
			static const auto src = "\
			function main(): String\
				return \"Hello world!\";"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::String>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == "Hello world!");
		}),

		CppUtils::Test::UnitTest("Number == Number", [] {
			static const auto src = "\
			function main(): Boolean\
				return 42 == 42;"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Boolean>(script.executeCode(src))->getValue();
			std::cout << std::boolalpha << result << std::endl;
			ASSERT(result == true);
		}),

		CppUtils::Test::UnitTest("String == String", [] {
			static const auto src = "\
			function main(): Boolean\
				return \"Hello world!\" == \"Hello world!\";"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Boolean>(script.executeCode(src))->getValue();
			std::cout << std::boolalpha << result << std::endl;
			ASSERT(result == true);
		}),

		CppUtils::Test::UnitTest("Number != Number", [] {
			static const auto src = "\
			function main(): Boolean\
				return 42 != 21;"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Boolean>(script.executeCode(src))->getValue();
			std::cout << std::boolalpha << result << std::endl;
			ASSERT(result == true);
		}),

		CppUtils::Test::UnitTest("String != String", [] {
			static const auto src = "\
			function main(): Boolean\
				return \"Hello world!\" != \"Hello world!\";"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Boolean>(script.executeCode(src))->getValue();
			std::cout << std::boolalpha << result << std::endl;
			ASSERT(result == false);
		}),

		CppUtils::Test::UnitTest("Operator priorities (A * B + C)", [] {
			static const auto src = "\
			function main(): Number\
				return 2 * 3 + 10;"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 16);
		}),

		CppUtils::Test::UnitTest("Operator priorities (A + B * C)", [] {
			static const auto src = "\
			function main(): Number\
				return 10 + 2 * 3;"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 16);
		})

	};
}
