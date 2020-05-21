#pragma once

#include <functional>
#include <memory>

#include <CppUtils.hpp>

namespace Language::AST::Scope::Type
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
		virtual std::unique_ptr<ITFunction<R(Args...)>> cloneFunction() const = 0;
	};

	template<typename>
	class DLL_PUBLIC Function;

	template<typename R, typename... Args>
	class DLL_PUBLIC Function<R(Args...)> :public ITFunction<R(Args...)>
	{
	public:
		Function() = default;
		Function(const std::function<R(Args...)>& function): m_function(function)
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

		std::unique_ptr<ITFunction<R(Args...)>> cloneFunction() const override
		{
			return std::make_unique<Function<R(Args...)>>(*this);
		}

	private:
		std::function<R(Args...)> m_function;
	};
}
