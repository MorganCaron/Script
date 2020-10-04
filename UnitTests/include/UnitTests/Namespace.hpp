#pragma once

#include <CppUtils.hpp>
#include <Script.hpp>

namespace UnitTests::Namespace
{
	const auto tests = std::vector<CppUtils::Test::UnitTest>{

		CppUtils::Test::UnitTest("Reading a variable in a namespace", [] {
			static const auto src = "\
			namespace Namespace\
			{\
				const variable = 42;\
			}\
			\
			function main(): Number\
				return Namespace::variable;"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		}),

		CppUtils::Test::UnitTest("Reading a variable in a sub-namespace", [] {
			static const auto src = "\
			namespace Namespace\
			{\
				namespace SubNamespace\
				{\
					const variable = 42;\
				}\
			}\
			\
			function main(): Number\
				return Namespace::SubNamespace::variable;"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		}),
		
		CppUtils::Test::UnitTest("Segmented namespace", [] {
			static const auto src = "\
			namespace Namespace\
			{\
				const variable0 = 21;\
			}\
			\
			namespace Namespace\
			{\
				const variable1 = variable0 + 21;\
			}\
			\
			function main(): Number\
				return Namespace::variable1;"s;
			auto script = Script::Script{Script::Settings{Script::Settings::Mode::Test}};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		})

	};
}
