#include <iostream>
#include <vector>

#include <CppUtils.hpp>
#include <Script.hpp>

int main()
{
	const auto tests = std::vector<CppUtils::Test::UnitTest>{

		CppUtils::Test::UnitTest("Main function", [] {
			static const auto src = "\
			function main() {\
				return 42;\
			}"s;
			auto script = Script::Script{};
			auto result = Script::ensureType<Script::Number>(script.executeCode(src))->getValue();
			std::cout << result << std::endl;
			ASSERT(result == 42);
		}),

		CppUtils::Test::UnitTest("MeshNode", [] {
			using StringMeshNode = CppUtils::Container::MeshNode<std::string, std::string>;
			auto fruit = std::make_shared<StringMeshNode>("fruit");
			auto banana = std::make_shared<StringMeshNode>("banana");
			auto yellow = std::make_shared<StringMeshNode>("yellow");

			banana->attach("Class", fruit);
			banana->attach("Color", yellow);
			fruit->attach("ObjectsWithThisAttribute", banana);
			yellow->attach("ObjectsWithThisAttribute", banana);

			ASSERT(fruit->value == "fruit");
			const auto fruitType = fruit->get("ObjectsWithThisAttribute")[0];
			ASSERT(fruitType->value == "banana");
			const auto bananaColor = fruitType->get("Color")[0];
			ASSERT(bananaColor->value == "yellow");
		})

	};

	return CppUtils::Test::UnitTest::executeTests(tests);
}
