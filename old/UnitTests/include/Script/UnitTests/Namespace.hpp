#pragma once

#include <CppUtils.hpp>
#include <Script.hpp>

namespace Script::UnitTests::Namespace
{
	const auto tests = std::vector<CppUtils::Test>{

		CppUtils::Test("Reading a variable in a namespace", [] {
			using namespace std::literals;
			static constexpr auto src = R"(
			namespace Namespace
			{
				const variable = 42;
			}
			
			function main(): Number
				return Namespace::variable;
			)"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		}),

		CppUtils::Test("Reading a variable in a sub-namespace", [] {
			using namespace std::literals;
			static constexpr auto src = R"(
			namespace Namespace
			{
				namespace SubNamespace
				{
					const variable = 42;
				}
			}
			
			function main(): Number
				return Namespace::SubNamespace::variable;
			)"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		}),
		
		CppUtils::Test("Segmented namespace", [] {
			using namespace std::literals;
			static constexpr auto src = R"(
			namespace Namespace
			{
				const variable0 = 21;
			}
			
			namespace Namespace
			{
				const variable1 = variable0 + 21;
			}
			
			function main(): Number
				return Namespace::variable1;
			)"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		})

	};
}
