#pragma once

#include <CppUtils.hpp>
#include <Script.hpp>

namespace Script::UnitTests::Class
{
	const auto tests = std::vector<CppUtils::Test>{

		CppUtils::Test("Class", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			class Person\
			{\
				const m_name: String;\
				\
				function constructor(const name: String)\
					m_name = name;\
				\
				function getName(): String\
					return m_name;\
			}\
			\
			function main(): Number\
			{\
				const person = new Person(\"Mout\");\
				if (person.getName() == \"Mout\")\
					return 42;\
				return 21;\
			}"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		}),

		CppUtils::Test("Class: Static attribute", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			class Person\
			{\
				static const name = \"Mout\";\
				\
				function constructor()\
					m_name = name;\
				\
				function getName(): String\
					return m_name;\
			}\
			\
			function main(): Number\
			{\
				const person = new Person();\
				if (person.getName() == \"Mout\")\
					return 42;\
				return 21;\
			}"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		}),

		CppUtils::Test("Class: Static member", [] {
			using namespace std::literals;
			static constexpr auto src = "\
			class Person\
			{\
				static function sayHello(): String\
					return \"Hello world!\";\
			}\
			\
			function main(): Number\
			{\
				if (Person::sayHello() != \"Hello world!\")\
					return 21;\
				const person = Person();\
				if (person.sayHello() != \"Hello world!\")\
					return 21;\
				return 42;\
			}"sv;
			auto script = Script{Settings{Settings::Mode::Test}};
			const auto result = ensureType<Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			EXPECT(result == 42);
		})

	};
}
