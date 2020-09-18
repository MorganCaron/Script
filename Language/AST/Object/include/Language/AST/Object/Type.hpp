#pragma once

#include <Language/AST/Type/Type.hpp>
#include <Language/AST/Object/Instance.hpp>

namespace Language::AST::Object::Type
{
	struct InstanceTag { 
		static constexpr const auto Name = "Instance"sv; 
	};

	using Instance = AST::Type::Type<InstanceTag, Instance>;
}
