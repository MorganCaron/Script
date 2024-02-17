#pragma once

#include <CppUtils.hpp>
#include <Script.hpp>

namespace Script::UnitTests::Operation
{
	const auto tests = std::vector<CppUtils::Test>{

		CppUtils::Test("Variable = literal", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			function main(): Number\
			{\
				const variable = 42;\
				return variable;\
			}"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		}),

		CppUtils::Test("Variable = Variable", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			function main(): Number\
			{\
				const variable0 = 42;\
				const variable1 = variable0;\
				return variable1;\
			}"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		}),

		CppUtils::Test("Number + Number", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			function main(): Number\
				return 21 + 21;"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		}),

		CppUtils::Test("String + String", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			function main(): String\
				return \"Hello world!\";"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<String>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == "Hello world!");
		}),

		CppUtils::Test("Number == Number", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			function main(): Boolean\
				return 42 == 42;"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Boolean>(script.executeCode(src))->getValue();
			std::cout << std::boolalpha << result << std::endl;
			EXPECT(result == true);
		}),

		CppUtils::Test("String == String", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			function main(): Boolean\
				return \"Hello world!\" == \"Hello world!\";"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Boolean>(script.executeCode(src))->getValue();
			std::cout << std::boolalpha << result << std::endl;
			EXPECT(result == true);
		}),

		CppUtils::Test("Number != Number", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			function main(): Boolean\
				return 42 != 21;"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Boolean>(script.executeCode(src))->getValue();
			std::cout << std::boolalpha << result << std::endl;
			EXPECT(result == true);
		}),

		CppUtils::Test("String != String", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			function main(): Boolean\
				return \"Hello world!\" != \"Hello world!\";"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Boolean>(script.executeCode(src))->getValue();
			std::cout << std::boolalpha << result << std::endl;
			EXPECT(result == false);
		}),

		CppUtils::Test("Operator priorities (A * B + C)", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			function main(): Number\
				return 2 * 3 + 10;"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 16);
		}),

		CppUtils::Test("Operator priorities (A + B * C)", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			function main(): Number\
				return 10 + 2 * 3;"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 16);
		})

	};
}
