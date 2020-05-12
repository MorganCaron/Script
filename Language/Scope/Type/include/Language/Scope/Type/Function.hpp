#pragma once

#include <functional>
#include <memory>

namespace Language::Scope::Type
{
	class IFunction
	{
	public:
		virtual ~IFunction() = default;
	};

	template<typename>
	class ITFunction;

	template<typename R, typename... Args>
	class ITFunction<R(Args...)>: public IFunction
	{
	public:
		virtual ~ITFunction() = default;
		virtual R operator()(Args&&... args) = 0;
		virtual std::unique_ptr<ITFunction<R(Args...)>> cloneFunction() const = 0;
	};

	template<typename>
	class Function;

	template<typename R, typename... Args>
	class Function<R(Args...)> :public ITFunction<R(Args...)>
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
