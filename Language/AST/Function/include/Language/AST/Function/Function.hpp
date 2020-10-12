#pragma once

#include <functional>
#include <memory>

#include <CppUtils.hpp>
#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Function
{
	using FunctionType = std::function<std::unique_ptr<Type::IValue>(const Type::Args&)>;

	struct DLL_PUBLIC Function
	{
		FunctionType function;
		CppUtils::Type::TypeId returnType;
	};
}
