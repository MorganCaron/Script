#pragma once

#include <CppUtils.hpp>
#include <Script.hpp>

namespace Script::UnitTests::Variable
{
	const auto tests = std::vector<CppUtils::Test>{

		CppUtils::Test("Constant", [] {
			using namespace std::literals;
			static constexpr auto src = R"(
			function main(): Number
			{
				const variable = 42;
				return variable;
			}
			)"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		}),

		CppUtils::Test("Variable", [] {
			using namespace std::literals;
			static constexpr auto src = R"(
			function main(): Number
			{
				let variable = 42;
				return variable;
			}
			)"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		})

	};
}
