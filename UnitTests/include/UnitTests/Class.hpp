#pragma once

#include <CppUtils.hpp>
#include <Script.hpp>

namespace UnitTests::Class
{
	const auto tests = std::vector<CppUtils::Test::UnitTest>{

		CppUtils::Test::UnitTest("Class", [] {
			static const auto src = "\
			class Person\
			{\
				m_name: String;\
				\
				function constructor(name: String)\
					m_name = name;\
				\
				function getName(): String\
					return m_name;\
			}\
			\
			function main(): Number\
			{\
				const person = Person(\"Mout\");\
				if (person.getName() == \"Mout\")\
					return 42;\
				return 21;\
			}"s;
			auto script = Script::Script{Script::Settings{ .verbose = true, .chrono = true }};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		}),

		CppUtils::Test::UnitTest("Class: Static attribute", [] {
			static const auto src = "\
			class Person\
			{\
				static name = \"Mout\";\
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
				const person = Person();\
				if (person.getName() == \"Mout\")\
					return 42;\
				return 21;\
			}"s;
			auto script = Script::Script{Script::Settings{ .verbose = true, .chrono = true }};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		}),

		CppUtils::Test::UnitTest("Class: Static member", [] {
			static const auto src = "\
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
			}"s;
			auto script = Script::Script{Script::Settings{ .verbose = true, .chrono = true }};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		})

	};
}
