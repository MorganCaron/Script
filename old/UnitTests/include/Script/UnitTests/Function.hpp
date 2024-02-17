#pragma once

#include <CppUtils.hpp>
#include <Script.hpp>

namespace Script::UnitTests::Function
{
	const auto tests = std::vector<CppUtils::Test>{

		CppUtils::Test("Main function", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			function main(): Number\
				return 42;"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		}),

		CppUtils::Test("Internal function call", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			function foobar(): Number\
				return 42;\
			\
			function main(): Number\
				return foobar();"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		}),

		CppUtils::Test("Internal function call with argument", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			function foobar(const nb: Number): Number\
				return nb;\
			\
			function main(): Number\
				return foobar(42);"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		}),

		CppUtils::Test("Function polymorphism: Argument type", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			function foobar(const nb: Number): Number\
				return 21;\
			\
			function foobar(const str: String): Number\
				return 42;\
			\
			function main(): Number\
				return foobar(\"test\");"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		}),

		CppUtils::Test("Function polymorphism: Return type", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			function foobar(): Number\
				return 42;\
			\
			function foobar(): String\
				return \"fail\";\
			\
			function main(): Number\
				return foobar();"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		}),

		CppUtils::Test("Function template", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			function foobar<T>(value: T): T\
				return value;\
			\
			function foobar(str: String): String\
				return str;\
			\
			function main(): Number\
				return foobar(42);"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		})
		
	};
}
