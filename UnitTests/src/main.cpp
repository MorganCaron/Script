#include <UnitTests/Class.hpp>
#include <UnitTests/Function.hpp>
#include <UnitTests/Namespace.hpp>
#include <UnitTests/Operation.hpp>
#include <UnitTests/Variable.hpp>

int main()
{
	const auto tests = CppUtils::Container::Vector::merge({
		std::cref(UnitTests::Variable::tests),
		std::cref(UnitTests::Operation::tests),
		std::cref(UnitTests::Function::tests),
		std::cref(UnitTests::Namespace::tests),
		std::cref(UnitTests::Class::tests)
	});

	return CppUtils::Test::UnitTest::executeTests(tests);
}
