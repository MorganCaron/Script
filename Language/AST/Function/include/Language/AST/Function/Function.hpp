#pragma once

#include <functional>
#include <memory>

#include <CppUtils.hpp>

#include <Language/AST/Type/Type.hpp>

namespace Language::AST::Function
{
	class DLL_PUBLIC IFunction
	{
	public:
		virtual ~IFunction() = default;
	};

	template<typename>
	class DLL_PUBLIC ITFunction;

	template<typename R, typename... Args>
	class DLL_PUBLIC ITFunction<R(Args...)>: public IFunction
	{
	public:
		virtual ~ITFunction() = default;
		virtual R operator()(Args&&... args) = 0;
		[[nodiscard]] virtual std::unique_ptr<ITFunction<R(Args...)>> cloneFunction() const = 0;
		[[nodiscard]] virtual const CppUtils::Type::TypeId& getReturnType() const = 0;
	};

	template<typename>
	class DLL_PUBLIC Function;

	template<typename R, typename... Args>
	class DLL_PUBLIC Function<R(Args...)>: public ITFunction<R(Args...)>
	{
	public:
		Function() = default;
		explicit Function(const std::function<R(Args...)>& function, CppUtils::Type::TypeId returnType):
			m_function{function},
			m_returnType{std::move(returnType)}
		{}
		Function(const Function&) = default;
		Function &operator=(const Function&) = default;
		virtual ~Function() = default;

		R operator()(Args&&... args) override final
		{
			if (!m_function)
				throw std::runtime_error{"Function not defined."};
			return m_function(std::forward<Args>(args)...);
		}

		[[nodiscard]] std::unique_ptr<ITFunction<R(Args...)>> cloneFunction() const override
		{
			return std::make_unique<Function<R(Args...)>>(*this);
		}

		[[nodiscard]] const CppUtils::Type::TypeId& getReturnType() const noexcept override final
		{
			return m_returnType;
		}

	private:
		std::function<R(Args...)> m_function;
		CppUtils::Type::TypeId m_returnType;
	};
}
